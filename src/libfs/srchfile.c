#include "libfs.h"

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "mts/mts.h"    // for mts_wait_vbl

extern const char *MGS_DiskName[3]; /* in main.c */

/*---------------------------------------------------------------------------*/

// Used for reading words LSB (little-endian) or MSB (big-endian) words
// from the ISO-9660 file system records. The PSX is a little-endian machine
// so the big-endian implementation is just for future portability.
#ifdef WORDS_BIGENDIAN
/* read 16-bit value */
#define read_lsb_ushort(p)  (p[1] | (p[0] << 8))
#define read_msb_ushort(p)  (p[0] | (p[1] << 8))
/* read 32-bit value */
#define read_lsb_ulong(p)   (p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24))
#define read_msb_ulong(p)   (p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24))
#else
/* read 16-bit value */
#define read_lsb_ushort(p)  (p[0] | (p[1] << 8))
#define read_msb_ushort(p)  (p[1] | (p[0] << 8))
/* read 32-bit value */
#define read_lsb_ulong(p)   (p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24))
#define read_msb_ulong(p)   (p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24))
#endif

/*---------------------------------------------------------------------------*/
/**
 * Copies ISO-9660 filename up until the first ';' character, trimming
 * the version number from the path, or until the NULL terminator is hit.
 *
 * @param[out]  dest    output string pointer
 * @param[in]   src     input string pointer
 * @param[in]   length  input string length
 */
STATIC void FS_GetFileName(char *dest, char *src, int length)
{
    while (length > 0)
    {
        *dest++ = *src++;
        if (*src == '\0')
        {
            break;
        }

        --length;
        if (*src == ';')
        {
            break;
        }
    }
    *dest = 0;
}

/*---------------------------------------------------------------------------*/
/**
 * Reads CD-ROM data from a given LBA (Logical Block Address).
 *
 * @param[out]  buffer  the memory location to write to
 * @param[in]   sector  sector number from whence to read
 * @param[in]   size    number of bytes to read
 */
STATIC int FS_ReadCdSector(void *buffer, int sector, int size)
{
    CDBIOS_ReadRequest(buffer, sector + 150, size, NULL);

    while (1)
    {
        if (CDBIOS_ReadSync() <= 0)
        {
            break;
        }
        mts_wait_vbl(1);
    }
    return 1;
}

/*---------------------------------------------------------------------------*/
/**
 * Gets a pointer to the FS_FILE_INFO record by filename.
 *
 * @param[in]   filename        filename to query
 * @param[in]   finfo           pointer to FS_FILE_INFO array
 *
 * @retval      non-NULL        pointer to FS_FILE_INFO record
 * @retval      NULL            file not found
 */
STATIC FS_FILE_INFO *FS_GetFileInfo(char *filename, FS_FILE_INFO *finfo)
{
    FS_FILE_INFO *ip;

    for (ip = finfo; ip->name; ip++)
    {
        if (strcmp(filename, ip->name) == 0)
        {
            return ip;
        }
    }
    return NULL;
}

// See: https://psx-spx.consoledev.net/cdromdrive/#cdrom-iso-file-and-directory-descriptors
static inline char GetXaAttribute(int dir_record, int name_length, int base_length)
{
    int xa_record;
    int padding;

    xa_record = name_length;
    xa_record += dir_record;
    xa_record = xa_record + base_length;

    padding = name_length & 1;
    xa_record = xa_record - padding;
    return *((char *)xa_record + 3);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Scans the game data directory records.
 *
 * Interates over all files listed in the game's data directory and
 * sets the LBA offset of each corresponding entry in fs_file_info.
 *
 * The LBA will be set to 0 for any filenames beginning with 'Z' that
 * do not have proper CD-XA attributes in the "System Use" section
 * of the ISO-9660 directory record.
 *
 * @param[in]       buffer  ISO-9660 directory record table
 * @param[in,out]   finfo   FS_FILE_INFO table to initialize
 *
 * @retval          -1      on failure
 * @retval          >= 0    disc number (0: Disc 1, 1: Disc 2)
 */
STATIC int FS_ReadCdDirectory(char *buffer, FS_FILE_INFO *finfo)
{
    int base_length;            /* minimum record length */
    int name_length;
    char name_buf[32];
    char *name_ptr;             /* file identifier */
    char *dir_record;           /* directory record */
    FS_FILE_INFO *file_info;
    FS_FILE_INFO *found;
    char *record_lba_ptr;
    char *top_ptr, *size_ptr;
    int record_lba;
    int top, size;
    int retval;                 /* disc id, -1 for error */
    int disk_no;
    const char **disk_name;     /* list of executable names */
    const char *exe_name;       /* executable name (eg. SLPS_999.99) */

    file_info = finfo;
    dir_record = buffer;
    retval = -1;

    /* iterate over the directory records */
    while (dir_record[0] != 0)
    {
        name_length = dir_record[32];

        /* skip the "." ('\0') and ".." ('\1') entries */
        if (name_length != 1)
        {
            name_ptr = &dir_record[33];
            FS_GetFileName(name_buf, name_ptr, name_length);

            /* check if the record is a file */
            if ((dir_record[25] & 2) == 0)
            {
                found = FS_GetFileInfo(name_buf, file_info);

                /* write the position to the table entry */
                if (found)
                {
                    base_length = 35;

                    /* check XA data for correct attributes */
                    if (name_buf[0] == 'Z' &&
                        GetXaAttribute((int)dir_record, name_length, base_length) == 0x0D)
                    {
                        // if GetXaAttribute() returned 0x0D, it's a normal file (0x0D55).
                        // MGS's XA data (ZMOVIE.STR) typically has attribute 0x2555.
                        found->pos = 0;
                    }
                    else
                    {
                        /* get the file's position */
                        record_lba_ptr = &dir_record[2];
                        record_lba = read_lsb_ulong(record_lba_ptr);
                        found->pos = record_lba + 150;
                    }
                }
                else
                {
                    /* check the hard-coded executable filename(s) */
                    disk_name = MGS_DiskName;
                    exe_name = *disk_name;
                    disk_no = 0;

                    while (exe_name != NULL)
                    {
                        if (strcmp(name_buf, *disk_name) == 0)
                        {
                            retval = disk_no;
                        }

                        disk_name++;
                        exe_name = *disk_name;
                        disk_no++;
                    }
                }

                top_ptr = &dir_record[2];
                top = read_lsb_ulong(top_ptr);

                size_ptr = &dir_record[10];
                size = read_lsb_ulong(size_ptr);

                printf("FILE %s : top %d size %d set %d\n", name_buf, top, size, found->pos);
            }
        }

        /* advance to the next record */
        dir_record += dir_record[0];
    }

    return retval;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Initializes the CD-ROM file position table.
 *
 * @param[out]      buffer  temporary load buffer
 *                          (needs to be at least 2048 bytes)
 * @param[in,out]   finfo   FS_FILE_INFO table to initialize
 *
 * @retval          -1      on failure
 * @retval          >= 0    disc number (0: Disc 1, 1: Disc 2)
 */
int FS_CdMakePositionTable(char *buffer, FS_FILE_INFO *finfo)
{
    char *path_table_ptr;
    char *dir_lba_ptr;
    int read_sector;
    int path_table_size;    /* in bytes */
    int retval;             /* disc id, -1 for error */
    int path_entry_size;
    int dir_name_length;    /* maximum of 8 chars */
    char *dir_buffer;
    char dir_name[16];

    /* read ISO-9660 volume descriptor */
    FS_ReadCdSector(buffer, 16, FS_SECTOR_SIZE);

    /* check system identifier */
    if (strncmp(buffer + 0x08, "PLAYSTATION", 11) != 0)
    {
        /* not a PlayStation-format disc */
        return -1;
    }

    /* read ISO-9660 path table */
    path_table_size = *(int *)(buffer + 0x84);
    FS_ReadCdSector(buffer, *(int *)(buffer + 0x8C), path_table_size);

    /* align to the next multiple of 4 */
    dir_buffer = buffer + ((((unsigned int)path_table_size + 3) >> 2) << 2);

    retval = -1;
    path_table_ptr = buffer;

    while (path_table_size > 0)
    {
        dir_name_length = *path_table_ptr;
        path_entry_size = 8 + dir_name_length;

        FS_GetFileName(dir_name, path_table_ptr + 8, dir_name_length);

        /* get directory LBA number */
        dir_lba_ptr = path_table_ptr + 2;
        read_sector = read_lsb_ulong(dir_lba_ptr);

        /* found the game's data directory? */
        if (strcmp(dir_name, "MGS") == 0)
        {
            printf("MGS read_sector %d\n", read_sector);
            FS_ReadCdSector(dir_buffer, read_sector, FS_SECTOR_SIZE);
            retval = FS_ReadCdDirectory(dir_buffer, finfo);
        }

        /* account for the padding field if the length is odd */
        if (path_entry_size & 1)
        {
            path_entry_size = 8 + dir_name_length + 1;
        }

        path_table_size -= path_entry_size;
        path_table_ptr += path_entry_size;
    }

    return retval;
}
