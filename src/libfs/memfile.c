#include "libfs.h"

extern int         dword_800BDFB8;
extern int         dword_800BDFBC;
extern FS_MEMFILE *dword_800BDFC0;
extern int         dword_800BDFC4;

#define FS_MEMFILE_BASE ((FS_MEMFILE *)0x80700000)

void FS_EnableMemfile( int read, int write )
{
    dword_800BDFB8 = read;  // cache_read_enable
    dword_800BDFBC = write; // clear_cache_buffer

    if (write != 0)
    {
        printf("Cache Buffer Cleared\n");
        dword_800BDFC4 = 0x80700c00;
        // Debug build address
        FS_MEMFILE_BASE->id = 0;
        dword_800BDFC0 = FS_MEMFILE_BASE;
    }

    if (read)
    {
        printf("Cache Read Enable\n");
    }
}

void FS_ClearMemfile( void )
{
    // Debug build address
    FS_MEMFILE_BASE->id = 0;
}

int FS_WriteMemfile( int id, int **buf_ptr, int size )
{
    int         ptr;
    int         ptr_off;
    FS_MEMFILE *memfile;

    *buf_ptr = 0;

    if (dword_800BDFBC != 0)
    {
        memfile = dword_800BDFC0;
        ptr = dword_800BDFC4;

        size = (size + 16) / 16 * 16;
        ptr_off = ptr + size;
        if (ptr_off <= 0x807FFFFF && memfile - FS_MEMFILE_BASE < 256)
        {
            memfile->id = id;
            memfile->ptr = (int *)ptr;
            memfile->size = size;

            *buf_ptr = (int *)ptr;
            dword_800BDFC0 = memfile + 1;
            dword_800BDFC0->id = 0;
            dword_800BDFC4 = ptr_off;
            return 1;
        }
    }

    return 0;
}

int FS_ReadMemfile( int id, int **buf_ptr )
{
    FS_MEMFILE *memfile;
    int         idtemp;

    *buf_ptr = 0;
    memfile = FS_MEMFILE_BASE;

    if (dword_800BDFB8 && memfile->id)
    {
        do
        {
            idtemp = memfile->id;
            if (idtemp == id)
            {
                *buf_ptr = memfile->ptr;
                return memfile->size;
            }
            memfile++;
            idtemp = memfile->id;
        } while (idtemp != 0);
    }

    return 0;
}
