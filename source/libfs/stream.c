#include "libfs.h"

#include <stdio.h>
#include <sys/types.h>
#include <libapi.h>
#include <libetc.h>
#include <libcd.h>

#include "common.h"
#include "mts/mts.h"
#include "sd/sd_cli.h"

extern int   fs_stream_ref_count;
extern int   fs_stream_read;
extern int   fs_stream_sector;
extern void *fs_stream_heap;
extern char *fs_stream_heap_end;
extern int   fs_stream_heap_size;
extern void *fs_stream_unused;
extern char *fs_stream_top;
extern int  *fs_stream_write_ptr;
extern char *fs_stream_bottom;
extern int   fs_stream_task_state;

STATIC int  fs_stream_last_time = -1;
STATIC int  fs_stream_next_time = 0;
STATIC int  fs_stream_stop = 0;
STATIC int  fs_stream_end = 1;
STATIC int *fs_stream_unread = NULL;

static int StreamReadyCallback( CDBIOS_TASK *task )
{
    int retval;

    char *charPtr1;
    int   size;
    char *charPtr2;

    char *streamHeap, *streamHeapEnd;
    int  *memcpySrc, *memcpyDst;
    int   ptrDiff1, ptrDiff2, ptrDiff3;

    retval = 1;

    fs_stream_write_ptr = task->buffer + task->buffer_size * 4;

    if (fs_stream_stop == 0 && fs_stream_end == 0)
    {
        charPtr1 = fs_stream_bottom;

        for (;; fs_stream_bottom = charPtr1)
        {
            size = *(int *)charPtr1 >> 8;
            charPtr2 = charPtr1 + size;

            if ((char *)&fs_stream_write_ptr[-1] >= charPtr2)
            {
                charPtr1 = charPtr2;

                if (*charPtr2 != 0xF0)
                {
                    continue;
                }

                fs_stream_end = 1;
                fs_stream_bottom = charPtr2;
                goto exit;
            }

            if (fs_stream_heap_end >= charPtr2 &&
                fs_stream_heap_end >= (char *)(fs_stream_write_ptr + 2048 / sizeof(int)))
            {
                break;
            }

            ptrDiff1 = (char *)fs_stream_heap + size - charPtr1;
            if (ptrDiff1 < 0)
            {
                ptrDiff1 = ptrDiff1 + fs_stream_heap_size;
            }

            ptrDiff2 = (char *)fs_stream_top - charPtr1;
            if (ptrDiff2 < 0)
            {
                ptrDiff2 += fs_stream_heap_size;
            }

            if (ptrDiff2 < ptrDiff1)
            {
                fs_stream_unread = (int *)charPtr1;
                goto exit;
            }

            memcpyDst = fs_stream_heap;
            memcpySrc = (int *)charPtr1;
            while (memcpySrc < fs_stream_write_ptr)
            {
                *memcpyDst = *memcpySrc;
                memcpySrc++;
                memcpyDst++;
            }

            streamHeap = fs_stream_heap;
            task->buffer = memcpyDst;

            *(int *)charPtr1 = -1;
            retval = 2;

            fs_stream_write_ptr = memcpyDst;
            fs_stream_heap_end =
                (char *)memcpyDst + ((fs_stream_heap_size - ((char *)memcpyDst - streamHeap)) & ~0x7FF);
            fs_stream_bottom = streamHeap;
            goto skip_heap_end_adjustment;
        }

        if ((char *)fs_stream_write_ptr >= fs_stream_heap_end)
        {
            streamHeapEnd = (char *)fs_stream_heap + fs_stream_heap_size;
            if ((int)fs_stream_write_ptr < (unsigned)streamHeapEnd)
            {
                *fs_stream_write_ptr = -1;
            }

            retval = 2;
            fs_stream_heap_end = streamHeapEnd;

            task->buffer = fs_stream_heap;
            fs_stream_bottom = fs_stream_heap;
            fs_stream_write_ptr = fs_stream_heap;
        }

    skip_heap_end_adjustment:
        ptrDiff3 = -(int)fs_stream_write_ptr + (int)fs_stream_top;
        if (ptrDiff3 < 0)
        {
            ptrDiff3 = ptrDiff3 + fs_stream_heap_size;
        }
        if (ptrDiff3 > 2048)
        {
            return retval;
        }
    }

exit:
    fs_stream_read = 0;
    fs_stream_sector = task->sector + 1;
    return 0;
}

static void StartRead( void )
{
    int temp_a0;
    int var_v1;
    int* temp_v0;
    int* var_a1;
    int* var_v1_2;
    int new_var;

    if (fs_stream_unread != NULL)
    {
        temp_v0 = fs_stream_unread;

        var_v1 = (int)(fs_stream_heap + (temp_v0[0] >> 8)) - (int)temp_v0;

        if (var_v1 < 0)
        {
            var_v1 += fs_stream_heap_size;
        }

        temp_a0 = (int)fs_stream_top - (int)temp_v0;

        if (temp_a0 < 0)
        {
            temp_a0 += fs_stream_heap_size;
        }

        if (temp_a0 < var_v1)
        {
            return;
        }

        SwEnterCriticalSection();

        var_a1 = fs_stream_heap;
        var_v1_2 = temp_v0;

        while (var_v1_2 < (int *)fs_stream_write_ptr)
        {
            *var_a1++ = *var_v1_2++;
        }

        fs_stream_write_ptr = var_a1;
        *temp_v0 = -1;
        fs_stream_unread = NULL;
        new_var = (fs_stream_heap_size - ((int)var_a1 - (int)fs_stream_heap)) & ~0x7FF;
        fs_stream_heap_end = (char *)var_a1 + new_var;
        fs_stream_bottom = fs_stream_heap;

        SwExitCriticalSection();
    }

    fs_stream_read = 1;
    CDBIOS_ReadRequest(fs_stream_write_ptr, fs_stream_sector, 0, &StreamReadyCallback);
}

void FS_StreamTaskStart( int sector )
{
    fs_stream_end = 0;
    fs_stream_stop = 0;

    fs_stream_sector = sector;

    fs_stream_last_time = -1;
    fs_stream_next_time = 0;

    fs_stream_unread = NULL;

    fs_stream_task_state = -1;

    fs_stream_top = fs_stream_heap;
    fs_stream_bottom = fs_stream_heap;
    fs_stream_write_ptr = fs_stream_heap;

    StartRead();
}

int FS_StreamTaskState( void )
{
    return fs_stream_task_state;
}

void FS_StreamTaskInit( void )
{
    /* do nothing */
}

int FS_StreamSync( void )
{
    int   stream_read;
    int   stream_end;
    char *ptr;
    int   type;
    int   size;
    int   remaining;

    stream_read = fs_stream_read;
    stream_end = fs_stream_end;

    if ((stream_end != 0) || (fs_stream_stop != 0))
    {
        fs_stream_task_state = 0;
        return 0;
    }

    if (fs_stream_task_state == -1)
    {
        if (stream_read == 1)
        {
            return 1;
        }

        fs_stream_task_state = 1;
        fs_stream_unused = fs_stream_heap;
    }

    ptr = fs_stream_top;
    while (ptr != fs_stream_bottom)
    {
        type = *(int *)ptr & 0xFF;
        size = *(int *)ptr >> 8;

        if (type == 0xFF)
        {
            ptr = fs_stream_heap;
        }
        else if (type == 0)
        {
            ptr += size;

            if (ptr == (fs_stream_heap + fs_stream_heap_size))
            {
                ptr = fs_stream_heap;
            }
        }
        else
        {
            break;
        }
    }
    fs_stream_top = ptr;

    if (stream_read == 0 && stream_end == 0)
    {
        remaining = (char *)fs_stream_write_ptr - fs_stream_top;

        if (remaining < 0)
        {
            remaining += fs_stream_heap_size;
        }

        if (remaining < ((fs_stream_heap_size * 2) / 3))
        {
            StartRead();
        }
    }

    return 1;
}

void FS_StreamCD( void )
{
    /* do nothing */
}

// warning/bug here is probably in OG code, unless this is an incorrect match
int FS_StreamGetTop( int is_demo )
{
    int file_id;

#ifndef NO_WARNING_WORKAROUNDS
    file_id = *&file_id;
#endif

    switch (is_demo)
    {
    case 0:
        file_id = FS_FILEID_VOX;
        break;
    case 1:
        file_id = FS_FILEID_DEMO;
        break;
    }

    return fs_file_info[file_id].pos;
}

int FS_StreamInit( void *heap, int size )
{
    fs_stream_heap = heap;
    fs_stream_heap_size = size;
    fs_stream_heap_end = heap + size;
    printf("stream init %X %X\n", (unsigned int)heap, size);
    fs_stream_ref_count = 0;
    return 1;
}

void FS_StreamStop( void )
{
    fs_stream_stop = 1;
    fs_stream_end = 1;
    fs_stream_task_state = 0;
    CDBIOS_ForceStop();
}

void FS_StreamOpen( void )
{
    mts_lock_sem(1);
    ++fs_stream_ref_count;
    mts_unlock_sem(1);
}

void FS_StreamClose( void )
{
    mts_lock_sem(1);
    --fs_stream_ref_count;
    mts_unlock_sem(1);
}

int FS_StreamIsEnd( void )
{
    return fs_stream_ref_count == 0;
}

void *FS_StreamGetData( int target_type )
{
    char *ptr;
    int   type;
    int   size;

    if (fs_stream_stop != 0)
    {
        return NULL;
    }

    ptr = fs_stream_top;
    while (ptr != fs_stream_bottom)
    {
        type = *(int *)ptr & 0xFF;
        size = *(int *)ptr >> 8;

        if (type == 0xff)
        {
            ptr = fs_stream_heap;
        }
        else
        {
            if (type == target_type)
            {
                *ptr = type | 0x80;
                return ptr + 4;
            }

            ptr += size;

            if (ptr >= (char *)fs_stream_heap + fs_stream_heap_size)
            {
                ptr = fs_stream_heap;
            }
        }
    }

    return NULL;
}

int FS_StreamGetSize( void *stream )
{
    int *tag;

    tag = (int *)((char *)stream - 4);
    return *tag >> 8;
}

void FS_StreamUngetData( void *stream )
{
    int *tag;
    int  val;

    tag = (int *)((char *)stream - 4);
    val = *tag;

    if (val & 0x80)
    {
        *(char *)tag = val & ~0x80;
    }
}

void FS_StreamClear( void *stream )
{
    int *tag;

    tag = (int *)((char *)stream - 4);
    *tag &= ~0xff;
}

void FS_StreamClearType( void *stream, int target_type )
{
    char *ptr;
    char *end;
    int   size;
    int   type;

    if (fs_stream_stop != 0)
    {
        return;
    }

    ptr = fs_stream_top;
    end = (char *)stream - 4;

    while ((ptr != end) && (ptr != fs_stream_bottom))
    {
        size = *(int *)ptr >> 8;
        type = *(int *)ptr & 0xF;

        if (type == target_type)
        {
            ptr[0] = 0;
            printf("clear %X\n", size);
        }

        ptr += size;

        if (ptr == (fs_stream_heap + fs_stream_heap_size))
        {
            ptr = fs_stream_heap;
        }
    }
}

void FS_StreamDump( void )
{
    char *ptr;
    int   type;
    int   size;

    ptr = fs_stream_top;

    printf("now_data_top %X loaded_header %X\n", (unsigned int)ptr, (unsigned int)fs_stream_bottom);
    printf("Tick %d\n", FS_StreamGetTick());

    while (ptr != fs_stream_bottom)
    {
        type = *(int *)ptr & 0xFF;
        size = *(int *)ptr >> 8;

        if (type == 0xFF)
        {
            ptr = fs_stream_heap;
        }
        else
        {
            if (type == 5)
            {
                printf("%08X TYPE %X size %d time %d\n", (unsigned int)ptr, 5, size, *(int *)(ptr + 4));
            }
            else
            {
                printf("%08X TYPE %X size %d\n", (unsigned int)ptr, type, size);
            }

            ptr += size;

            if (ptr == (fs_stream_heap + fs_stream_heap_size))
            {
                ptr = fs_stream_heap;
            }
        }
    }
}

int FS_StreamGetEndFlag( void )
{
    return fs_stream_end;
}

int FS_StreamIsForceStop( void )
{
    return fs_stream_stop;
}

// TODO: the var might be part of a struct and the code
// takes a ptr to that struct, unknown currently
static inline int *GetTicksPtr( void )
{
    return &fs_stream_last_time;
}

void FS_StreamTickStart( void )
{
    *GetTicksPtr() = VSync(-1);
}

// for some reason no ptr access here
void FS_StreamSoundMode( void )
{
    fs_stream_last_time = -1;
    fs_stream_next_time = 1;
}

int FS_StreamGetTick( void )
{
    int now = mts_get_tick_count();
    int ticks;

    if (fs_stream_next_time != 0)
    {
        ticks = get_str_counter();

        if (ticks < 0)
        {
            if (fs_stream_last_time < 0)
            {
                return -1;
            }

            return now - fs_stream_last_time + fs_stream_next_time;
        }

        fs_stream_last_time = now;
        fs_stream_next_time = (ticks * 64) / 105 + 1;
        return fs_stream_next_time;
    }

    return now - fs_stream_last_time;
}
