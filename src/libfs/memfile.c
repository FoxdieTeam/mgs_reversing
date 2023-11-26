#include "libfs.h"

extern int         dword_800BDFB8;
extern int         dword_800BDFBC;
extern FS_MEMFILE *dword_800BDFC0;
extern int         dword_800BDFC4;

#define FS_MEMFILE_BASE ((FS_MEMFILE *)0x80700000)

void FS_EnableMemfile_800799A8(int cache_read_enable, int clear_cache_buffer)
{
    dword_800BDFB8 = cache_read_enable;
    dword_800BDFBC = clear_cache_buffer;

    if (clear_cache_buffer != 0)
    {
        printf("Cache Buffer Cleared\n");
        dword_800BDFC4 = 0x80700c00;
        // Debug build address
        FS_MEMFILE_BASE->field_0 = 0;
        dword_800BDFC0 = FS_MEMFILE_BASE;
    }

    if (cache_read_enable)
    {
        printf("Cache Read Enable\n");
    }
}

void FS_ClearMemfile_80079A1C()
{
    // Debug build address
    FS_MEMFILE_BASE->field_0 = 0;
}

int FS_WriteMemfile_80079A2C(int field_0, int *field_4_ptr, int off)
{
    int         field_4;
    int         field_4_off;
    FS_MEMFILE *memfile;

    *field_4_ptr = 0;

    if (dword_800BDFBC != 0)
    {
        memfile = dword_800BDFC0;
        field_4 = dword_800BDFC4;

        off = (off + 16) / 16 * 16;
        field_4_off = field_4 + off;
        if (field_4_off <= 0x807FFFFF && memfile - FS_MEMFILE_BASE < 256)
        {
            memfile->field_0 = field_0;
            memfile->field_4 = field_4;
            memfile->field_8 = off;

            *field_4_ptr = field_4;
            dword_800BDFC0 = memfile + 1;
            dword_800BDFC0->field_0 = 0;
            dword_800BDFC4 = field_4_off;
            return 1;
        }
    }

    return 0;
}

int FS_ReadMemfile_80079AE4(int arg0, int *arg1)
{
    FS_MEMFILE *memfile;
    int         field_0;

    *arg1 = 0;
    memfile = FS_MEMFILE_BASE;

    if (dword_800BDFB8 && memfile->field_0)
    {
        do
        {
            field_0 = memfile->field_0;
            if (field_0 == arg0)
            {
                *arg1 = memfile->field_4;
                return memfile->field_8;
            }
            memfile++;
            field_0 = memfile->field_0;
        } while (field_0 != 0);
    }

    return 0;
}
