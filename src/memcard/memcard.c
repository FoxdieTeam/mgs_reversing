#include "linker.h"
#include "memcard.h"
#include "psyq.h"
#include "mts/mts_new.h"
#include <kernel.h>
#include <sys/file.h>
#include "psyq.h"

int gmem_card_system_inited_8009D524 = 0;

extern mem_card gMemCards_800B52F8[2];
extern long            gHardware_end_io_800B52C8;
extern long            gHardware_end_write_800B52CC;
extern long            gHardware_timeout_800B52D0;
extern long            gHardware_new_device_800B52D4;
extern long            gSoftware_end_io_800B52D8;
extern long            gSoftware_end_write_800B52DC;
extern long            gSoftware_timeout_800B52E0;
extern long            gSoftware_new_device_800B52E4;
extern TMemCardFunc    gHwCard_do_op_800B52E8;
extern TMemCardFunc    gSwCard_do_op_800B52EC;
extern volatile int    gSwCardLastOp_800B52F0;
extern volatile int    gHwCardLastOp_800B52F4;
extern volatile long   gMemCard_io_size_800B5648;

// #define STATIC static
#define STATIC

STATIC void memcard_hwcard_do_op(int op);
STATIC void memcard_swcard_do_op(int op);

STATIC int memcard_retry_helper(int state);
STATIC void memcard_retry(int port);

static inline void memcard_access_wait(void)
{
    printf("[R]");

    while ((gHwCard_do_op_800B52E8 != memcard_hwcard_do_op) ||
           (gSwCard_do_op_800B52EC != memcard_swcard_do_op))
    {
        printf("ACCESS WAIT..\n");
        mts_wait_vbl(2);
    }

    gHwCardLastOp_800B52F4 = 0;
    gSwCardLastOp_800B52F0 = 0;
}

STATIC void memcard_hwcard_do_op(int op)
{
    gHwCardLastOp_800B52F4 = op;
}

STATIC void memcard_swcard_do_op(int op)
{
    gSwCardLastOp_800B52F0 = op;
}

STATIC void memcard_hwcard_end_io()
{
    gHwCard_do_op_800B52E8(1);
}

STATIC void memcard_hwcard_end_write()
{
    printf("*** hw card error\n");
    gHwCard_do_op_800B52E8(2);
}

STATIC void memcard_hwcard_timeout()
{
    printf("[C.H.T.O]");
    gHwCard_do_op_800B52E8(3);
}

STATIC void memcard_hwcard_new()
{
    printf("*** hw card new\n");
    gHwCard_do_op_800B52E8(4);
}

STATIC void memcard_swcard_end_io()
{
    gSwCard_do_op_800B52EC(1);
}

STATIC void memcard_swcard_end_write()
{
    printf("*** sw card error\n");
    gSwCard_do_op_800B52EC(2);
}

STATIC void memcard_swcard_timeout()
{
    printf("[C.S.T.O]");
    gSwCard_do_op_800B52EC(3);
}

STATIC void memcard_swcard_new()
{
    printf("*** sw card new\n");
    gSwCard_do_op_800B52EC(4);
}

STATIC void memcard_set_sw_hw_card_fns(void)
{
    gHwCard_do_op_800B52E8 = memcard_hwcard_do_op;
    gSwCard_do_op_800B52EC = memcard_swcard_do_op;
}

STATIC int memcard_easy_format_test(int hCard)
{
    char buffer[128];

    printf("easy_format_test\n");
    memset(buffer, 0, sizeof(buffer));

    memcard_access_wait();

    _card_read(hCard, 0, buffer);

    do {
        mts_wait_vbl(1);
    } while (!gHwCardLastOp_800B52F4);

    if (gHwCardLastOp_800B52F4 != 1)
    {
        printf("card_error\n");
        return 2;
    }
    else
    {
        if (buffer[0] == 'M' && buffer[1] == 'C')
        {
            printf("card_normal\n");
            return 1;
        }
        else
        {
            printf("card_unformat\n");
            return 5;
        }
    }
}

STATIC int memcard_loaddir(int port, int *pFreeBlockCount)
{
    struct DIRENTRY dir;
    char name[32];
    int files;
    int blocks;

    blocks = 0;

    sprintf(name, "bu%02X:*", port * 16);
    printf("load_dir %s start\n", name);

    if (firstfile(name, &dir))
    {
        files = 0;

        do {
            memcpy(gMemCards_800B52F8[port].field_4_blocks[files].field_0_name, dir.name, sizeof(dir.name));
            gMemCards_800B52F8[port].field_4_blocks[files].field_14 = 0;
            gMemCards_800B52F8[port].field_4_blocks[files].field_18_size = dir.size;
            blocks += (dir.size + 8191) / 8192;
            files++;
        }
        while (nextfile(&dir));

        printf("TOTAL %d FILES used %d block\n", files, blocks);
        *pFreeBlockCount = blocks;
        return files;
    }

    printf("NO FILE\n");
    *pFreeBlockCount = 0;
    return 0;
}

STATIC void memcard_load_files(int idx)
{
    int freeBlockCount;
    gMemCards_800B52F8[idx].field_0_card_idx = idx;
    gMemCards_800B52F8[idx].field_1_last_op = 1;
    gMemCards_800B52F8[idx].field_2_file_count = memcard_loaddir(idx, &freeBlockCount);
    gMemCards_800B52F8[idx].field_3_free_blocks = 15 - freeBlockCount;
}

STATIC int memcard_retry_helper(int state)
{
    switch (state)
    {
    case 1:
        return 0;
    case 4:
        return 0x01000000;
    case 2:
        return 0xc0000002;
    case 3:
        return 0xc0000003;
    default:
        return 0x80000000;
    }
}

void memcard_reset_status(void)
{
    gMemCards_800B52F8[0].field_1_last_op = 2;
    gMemCards_800B52F8[1].field_1_last_op = 2;
}

static inline void memcard_wait(void)
{
    printf("[R]");

    while ((gHwCard_do_op_800B52E8 != memcard_hwcard_do_op) ||
           (gSwCard_do_op_800B52EC != memcard_swcard_do_op))
    {
        printf("ACCESS WAIT..\n");
        mts_wait_vbl(2);
    }

    gHwCardLastOp_800B52F4 = 0;
    gSwCardLastOp_800B52F0 = 0;
}

int memcard_check(int port)
{
    int chan;
    int retries;
    int sw_card_op;
    int hw_card_op;

    chan = port * 16;
    retries = 0;

    if ((gMemCards_800B52F8[port].field_1_last_op == 5) || (gMemCards_800B52F8[port].field_1_last_op == 2))
    {
        goto loop_24;
    }

    while (1)
    {
        memcard_wait();
        _card_info(chan);

        if ((retries++) > 10)
        {
            printf("MEMCARD:RETRY OVER!!\n");
            return 0x80000002;
        }

        // FIXME: why does THIS need a goto while the others need a do while?
    retry1:
        mts_wait_vbl(1);

        if ((sw_card_op = !gSwCardLastOp_800B52F0))
            goto retry1;

        sw_card_op = gSwCardLastOp_800B52F0;
        switch (sw_card_op)
        {
            case 1:
                if (gMemCards_800B52F8[port].field_1_last_op == 5)
                {
                    return 0x80000001;
                }

                if (gMemCards_800B52F8[port].field_1_last_op == 4)
                {
                    goto exit;
                }

                sw_card_op = 1;
                gMemCards_800B52F8[port].field_1_last_op = sw_card_op;
                return 0;

            case 2:

            case 3:
                gMemCards_800B52F8[port].field_1_last_op = sw_card_op;
                memcard_retry(port);
                return;

            case 4:
                break;

            default:
                return; // FIXME: Return without value in function that returns long???
        }

    loop_24:
        memcard_wait();
        _card_clear(chan);

        do {
            mts_wait_vbl(1);
        } while ((hw_card_op = !gHwCardLastOp_800B52F4));
        hw_card_op = gHwCardLastOp_800B52F4;

        if (hw_card_op == 1)
        {
            gMemCards_800B52F8[port].field_1_last_op = 4;

            memcard_wait();
            _card_load(chan);

            do {
                mts_wait_vbl(1);
            } while ((sw_card_op = !gSwCardLastOp_800B52F0));

            sw_card_op = gSwCardLastOp_800B52F0;

            if (sw_card_op == 4)
            {
                gMemCards_800B52F8[port].field_1_last_op = 5;

                {
                    register int ret asm("v0");
                    ret = 0x80000000;
                    asm("" :: "r"(ret));
                }

                return 0x80000001; // or "return ret | 1;" (with ret variable outside block)
            }

            if (sw_card_op == 1)
            {
                gMemCards_800B52F8[port].field_1_last_op = 4;
                break;
            }

            printf("RETRY(new)\n");
        }
        else
        {
            printf("RETRY\n");
        }
    }

exit:
    return 0x1000000;
}

void memcard_init(void)
{
    int idx; // $s1

    if (!gmem_card_system_inited_8009D524)
    {
        gmem_card_system_inited_8009D524 = !gmem_card_system_inited_8009D524;
        gHwCardLastOp_800B52F4 = 1;

        gSwCardLastOp_800B52F0 = 1;
        memcard_set_sw_hw_card_fns();

        EnterCriticalSection();

        gHardware_end_io_800B52C8 = OpenEvent(
            HwCARD, EvSpIOE, EvMdINTR, (openevent_cb_t)memcard_hwcard_end_io);
        gHardware_end_write_800B52CC =
            OpenEvent(HwCARD, EvSpERROR, EvMdINTR, (openevent_cb_t)memcard_hwcard_end_write);
        gHardware_timeout_800B52D0 =
            OpenEvent(HwCARD, EvSpTIMOUT, EvMdINTR, (openevent_cb_t)memcard_hwcard_timeout);
        gHardware_new_device_800B52D4 =
            OpenEvent(HwCARD, EvSpNEW, EvMdINTR, (openevent_cb_t)memcard_hwcard_new);

        gSoftware_end_io_800B52D8 = OpenEvent(
            SwCARD, EvSpIOE, EvMdINTR, (openevent_cb_t)memcard_swcard_end_io);
        gSoftware_end_write_800B52DC =
            OpenEvent(SwCARD, EvSpERROR, EvMdINTR, (openevent_cb_t)memcard_swcard_end_write);
        gSoftware_timeout_800B52E0 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdINTR, (openevent_cb_t)memcard_swcard_timeout);
        gSoftware_new_device_800B52E4 = OpenEvent(SwCARD, EvSpNEW, EvMdINTR, (openevent_cb_t)memcard_swcard_new);

        EnableEvent(gHardware_end_io_800B52C8);
        EnableEvent(gHardware_end_write_800B52CC);
        EnableEvent(gHardware_timeout_800B52D0);
        EnableEvent(gHardware_new_device_800B52D4);

        EnableEvent(gSoftware_end_io_800B52D8);
        EnableEvent(gSoftware_end_write_800B52DC);
        EnableEvent(gSoftware_timeout_800B52E0);
        EnableEvent(gSoftware_new_device_800B52E4);

        ExitCriticalSection();

        idx = 0;

        InitCARD(0);
        StartCARD();
        _bu_init();
        mts_set_vsync_task();
        memcard_reset_status();

        for (idx = 0; idx < 2; idx++)
        {
            if (!memcard_check(idx))
            {
                long v2 = memcard_easy_format_test(idx);
                if (v2 == 5)
                {
                    gMemCards_800B52F8[idx].field_1_last_op = 5;
                }
                else if (v2 == 1)
                {
                    gMemCards_800B52F8[idx].field_1_last_op = 1;
                }
                else
                {
                    gMemCards_800B52F8[idx].field_1_last_op = 2;
                }
            }
            else
            {
                gMemCards_800B52F8[idx].field_1_last_op = 5;
            }
        }
    }
}

void memcard_exit(void)
{
    StopCARD();
    EnterCriticalSection();
    CloseEvent(gHardware_end_io_800B52C8);
    CloseEvent(gHardware_end_write_800B52CC);
    CloseEvent(gHardware_timeout_800B52D0);
    CloseEvent(gHardware_new_device_800B52D4);
    CloseEvent(gSoftware_end_io_800B52D8);
    CloseEvent(gSoftware_end_write_800B52DC);
    CloseEvent(gSoftware_timeout_800B52E0);
    CloseEvent(gSoftware_new_device_800B52E4);
    ExitCriticalSection();
    gmem_card_system_inited_8009D524 = 0;
}

void memcard_retry(int port)
{
    int op;
    int count;
    int i;

    switch (gMemCards_800B52F8[port].field_1_last_op)
    {
    case 1:
    case 4:
        op = gMemCards_800B52F8[port].field_1_last_op;
        memcard_retry_helper(op);
        return;

    case 3:
        count = 1;
        break;

    case 2:
        count = 20;
        break;
    }

    for (i = 0; i < count; i++)
    {
        memcard_access_wait();
        _card_info(port * 16);

        do {
            mts_wait_vbl(1);
        }
        while (!gSwCardLastOp_800B52F0);

        op = gSwCardLastOp_800B52F0;

        if (op == 1 || op == 4)
        {
            break;
        }

        mts_wait_vbl(3);
    }

    memcard_retry_helper(op);
}

mem_card *memcard_get_files(int idx)
{
    mem_card *pCardBase = gMemCards_800B52F8;
    mem_card *pCard = &pCardBase[idx];

    if (pCard->field_1_last_op == 1 || pCard->field_1_last_op == 4)
    {
        memcard_load_files(idx);
        pCard->field_1_last_op = 1;
        return pCard;
    }
    return 0;
}

int memcard_delete(int idx, const char *filename)
{
    char tmp[32];

    mem_card *pCardBase = gMemCards_800B52F8;
    mem_card *pCard = &pCardBase[idx];

    if (pCard->field_1_last_op == 1)
    {
        sprintf(tmp, "bu%02X:%s", 0x10 * idx, filename);
        if (erase(tmp))
        {
            printf("Deleted File %s", filename);
            return 1;
        }
        printf("ERROR : can't delete %s\n", filename);
    }
    return 0;
}

STATIC void memcard_hwcard_read_write_handler(int op)
{
    if (op == 1)
    {
        gMemCard_io_size_800B5648 -= 128;
        if (!gMemCard_io_size_800B5648)
        {
            gHwCard_do_op_800B52E8 = memcard_hwcard_do_op;
        }
    }
    else
    {
        gMemCard_io_size_800B5648 = -1;
        memcard_set_sw_hw_card_fns();
    }
}

STATIC void memcard_swcard_read_write_handler(int op)
{
    if (op == 1)
    {
        printf("MEMCARD READ/WRITE end\n");
    }
    else
    {
        printf("ERROR : MEMCARD READ/WRITE\n");
    }
    gSwCard_do_op_800B52EC = (TMemCardFunc)memcard_swcard_do_op;
}

STATIC void memcard_set_read_write(int fileSize)
{
    gHwCard_do_op_800B52E8 = memcard_hwcard_read_write_handler;
    gSwCard_do_op_800B52EC = memcard_swcard_read_write_handler;
    gMemCard_io_size_800B5648 = fileSize;
}

#define ROUND_UP(val,rounding) (((val) + (rounding) - 1) / (rounding) * (rounding))

void memcard_write(int idx, const char *filename, int seekPos, char *pBuffer, int bufferSize)
{
    int blocks = ROUND_UP(bufferSize, 8192) / 8192;
    int hFile;
    char name[32];

    sprintf(name, "bu%02X:%s", idx * 16, filename);

    hFile = open(name, (blocks << 16) | O_CREAT);
    if (hFile < 0)
    {
        printf("Warning : MEMCARD create error ... overwrite\n");
    }
    close(hFile);

    hFile = open(name, O_NOWAIT | O_WRONLY);
    if (hFile < 0)
    {
        printf("MEMCARD WRITE ERROR FD %d\n", hFile);
        gMemCard_io_size_800B5648 = -1;
        return;
    }

    printf("MEMCARD WRITE %s FD %d SIZE %d\n", filename, hFile, bufferSize);
    bufferSize = ROUND_UP(bufferSize, 128);
    if (seekPos > 0)
    {
        lseek(hFile, seekPos, SEEK_SET);
    }
    memcard_set_read_write(bufferSize);
    write(hFile, pBuffer, bufferSize);
    close(hFile);
    printf("WRITING FILE %s...\n", filename);
}

void memcard_read(int idx, const char *filename, int seekPos, char *pBuffer, int bufferSize)
{
    char name[32];
    int hFile;

    sprintf(name, "bu%02x:%s", idx * 16, filename);
    hFile = open(name, FREAD | FASYNC);
    if (hFile < 0)
    {
        printf("MEMCARD READ ERROR FD %d\n", hFile);
        gMemCard_io_size_800B5648 = -1;
        return;
    }
    bufferSize = ROUND_UP(bufferSize, 128);
    printf("MEMCARD READ %s FD %d SIZE %d\n", filename, hFile, bufferSize);
    if (seekPos > 0)
    {
        lseek(hFile, seekPos, SEEK_SET);
    }
    memcard_set_read_write(bufferSize);
    read(hFile, pBuffer, bufferSize);
    close(hFile);
    printf("READING FILE %s...\n", filename);
}

int memcard_get_status(void)
{
    return gMemCard_io_size_800B5648;
}

int memcard_format(int idx)
{
    int  retries;
    char cardPath[32];

    retries = 4;
    sprintf(cardPath, "bu%02x:", idx * 16);

    if (gMemCards_800B52F8[idx].field_1_last_op == 5)
    {
    retry:
        if (format(cardPath) != 0)
        {
            printf("FORMATED %d\n", idx);
            gMemCards_800B52F8[idx].field_1_last_op = 1;
            return 1;
        }
        retries--;
        if (retries <= 0)
        {
            printf("ERROR : MEMCARD FORMAT\n");
            return 0;
        }
        goto retry; // TODO: find a match without goto
    }

    printf("ERROR : MEMCARD FORMATED CARD\n");
    return 0;
}
