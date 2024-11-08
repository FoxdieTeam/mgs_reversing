#include "libfs.h"

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "mts/mts.h"

extern const char *MGS_DiskName[3]; /* in main.c */

STATIC void CDFS_ParseFileName(char *pOutput, char *pInput, int input_len)
{
    while (input_len > 0)
    {
        *pOutput++ = *pInput++;
        if (!*pInput)
        {
            break;
        }

        --input_len;
        if (*pInput == ';')
        {
            break;
        }
    }
    *pOutput = 0;
}

STATIC int FS_CdMakePositionTable_helper2(void *pBuffer, int startSector, int sectorSize)
{
    CDBIOS_ReadRequest(pBuffer, startSector + 150, sectorSize, 0);

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

STATIC FS_FILE_INFO *FS_FindDirEntry(char *filename, FS_FILE_INFO *file_info)
{
    FS_FILE_INFO *ip;

    for (ip = file_info; ip->name; ip++)
    {
        if (!strcmp(filename, ip->name))
        {
            return ip;
        }
    }

    return 0;
}

// See: https://psx-spx.consoledev.net/cdromdrive/#cdrom-iso-file-and-directory-descriptors
static inline char getXAUserID(int directoryRecord, int fileIdentifierLength, int basicRecordLength)
{
    int xaRecord;
    int padding;

    xaRecord = fileIdentifierLength;
    xaRecord += directoryRecord;
    xaRecord = xaRecord + basicRecordLength;

    padding = fileIdentifierLength & 1;
    xaRecord = xaRecord - padding;
    return *((char *)xaRecord + 3);
}

#define byteswap_ulong(p) p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24)

STATIC int FS_CdMakePositionTable_helper(char *inDirectoryRecord, FS_FILE_INFO *file_info)
{
    FS_FILE_INFO    *foundRecord;
    const char     **diskNameIterator;
    const char      *currentStringPtr;
    int              fileIdentifierLength;
    char             parsedFileName[32];
    char            *sectorBaseValues;
    char            *topValues;
    char            *sizeValues;
    int              sectorBase;
    int              top;
    int              size;
    int              returnValue;
    int              stringCount;
    int              basicRecordLength;
    char            *fileIdentifier;
    char            *directoryRecord;
    FS_FILE_INFO    *directoryRecords;

    directoryRecords = file_info;
    directoryRecord = inDirectoryRecord;
    returnValue = -1;

    while (*directoryRecord != 0)
    {
        fileIdentifierLength = directoryRecord[32];

        if (fileIdentifierLength != 1)
        {
            fileIdentifier = directoryRecord + 33;
            CDFS_ParseFileName(parsedFileName, fileIdentifier, fileIdentifierLength);

            if ((directoryRecord[25] & 2) == 0)
            {
                foundRecord = FS_FindDirEntry(parsedFileName, directoryRecords);

                if (foundRecord)
                {
                    basicRecordLength = 35;

                    if (parsedFileName[0] == 'Z' && getXAUserID((int)directoryRecord, fileIdentifierLength, basicRecordLength) == 0xd)
                    {
                        foundRecord->sector = 0;
                    }
                    else
                    {
                        sectorBaseValues = (directoryRecord + 2);
                        sectorBase = byteswap_ulong(sectorBaseValues);
                        foundRecord->sector = sectorBase + 150;
                    }
                }
                else
                {
                    diskNameIterator = MGS_DiskName;
                    currentStringPtr = *diskNameIterator;
                    stringCount = 0;

                    while (currentStringPtr)
                    {
                        if (strcmp(parsedFileName, diskNameIterator[0]) == 0)
                        {
                            returnValue = stringCount;
                        }

                        diskNameIterator++;
                        currentStringPtr = *diskNameIterator;
                        stringCount++;
                    }
                }

                topValues = (directoryRecord + 2);
                top = byteswap_ulong(topValues);

                sizeValues = (directoryRecord + 10);
                size = byteswap_ulong(sizeValues);

                printf("FILE %s : top %d size %d set %d\n", parsedFileName, top, size, foundRecord->sector);
            }
        }

        directoryRecord += *directoryRecord;
    }

    return returnValue;
}

int FS_CdMakePositionTable(char *pHeap, FS_FILE_INFO *file_info)
{
    char *buffer2;
    char *dir_block_ptr;
    int directory_block;
    int path_table_size;
    int ret;
    int uVar7;
    int directory_length;
    char *directory_block_data;
    char directory_name[16];

    FS_CdMakePositionTable_helper2(pHeap, 16, 2048);

    if (strncmp(pHeap + 8, "PLAYSTATION", 11))
    {
        return -1;
    }

    path_table_size = *(int *)(pHeap + 0x84);

    FS_CdMakePositionTable_helper2(pHeap, *(int *)(pHeap + 0x8c), path_table_size);
    directory_block_data = pHeap + ((((unsigned int)path_table_size + 3) >> 2) << 2);

    ret = -1;
    buffer2 = pHeap;

    while (path_table_size > 0)
    {
        directory_length = *buffer2;
        uVar7 = directory_length + 8;

        CDFS_ParseFileName(directory_name, buffer2 + 8, directory_length);

        dir_block_ptr = buffer2 + 2;
        directory_block = *dir_block_ptr | (*(dir_block_ptr + 1) << 8) | (*(dir_block_ptr + 2) << 16) | (*(dir_block_ptr + 3) << 24);

        if (!strcmp(directory_name, "MGS"))
        {
            printf("MGS read_sector %d\n", directory_block);
            FS_CdMakePositionTable_helper2(directory_block_data, directory_block, 2048);
            ret = FS_CdMakePositionTable_helper(directory_block_data, file_info);
        }

        if (uVar7 & 1)
        {
            uVar7 = directory_length + 9;
        }

        path_table_size -= uVar7;
        buffer2 += uVar7;
    }

    return ret;
}
