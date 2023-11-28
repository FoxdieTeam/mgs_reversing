#include "linker.h"
#include "memcard.h"
#include "psyq.h"
#include "mts/mts_new.h"
#include <KERNEL.H>
#include <SYS/FILE.H>
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

static inline void memcard_access_wait()
{
    printf("[R]");

    while ((gHwCard_do_op_800B52E8 != memcard_hwcard_do_op_800244DC) ||
           (gSwCard_do_op_800B52EC != memcard_swcard_do_op_800244EC))
    {
        printf("ACCESS WAIT..\n");
        mts_wait_vbl_800895F4(2);
    }

    gHwCardLastOp_800B52F4 = 0;
    gSwCardLastOp_800B52F0 = 0;
}

void memcard_hwcard_do_op_800244DC(int op)
{
    gHwCardLastOp_800B52F4 = op;
}

void memcard_swcard_do_op_800244EC(int op)
{
    gSwCardLastOp_800B52F0 = op;
}

void memcard_hwcard_end_io_800244FC()
{
    gHwCard_do_op_800B52E8(1);
}

void memcard_hwcard_end_write_80024524()
{
    printf("*** hw card error\n");
    gHwCard_do_op_800B52E8(2);
}

void memcard_hwcard_timeout_8002455C()
{
    printf("[C.H.T.O]");
    gHwCard_do_op_800B52E8(3);
}

void memcard_hwcard_new_80024594()
{
    printf("*** hw card new\n");
    gHwCard_do_op_800B52E8(4);
}

void memcard_swcard_end_io_800245CC()
{
    gSwCard_do_op_800B52EC(1);
}

void memcard_swcard_end_write_800245F4()
{
    printf("*** sw card error\n");
    gSwCard_do_op_800B52EC(2);
}

void memcard_swcard_timeout_8002462C()
{
    printf("[C.S.T.O]");
    gSwCard_do_op_800B52EC(3);
}

void memcard_swcard_new_80024664()
{
    printf("*** sw card new\n");
    gSwCard_do_op_800B52EC(4);
}

void memcard_set_sw_hw_card_fns_8002469C()
{
    gHwCard_do_op_800B52E8 = memcard_hwcard_do_op_800244DC;
    gSwCard_do_op_800B52EC = memcard_swcard_do_op_800244EC;
}

int memcard_easy_format_test_800246C0(int hCard)
{
    char pData[128]; // [sp+10h] [-80h] BYREF

    printf("easy_format_test\n");
    memset(pData, 0, sizeof(pData));

    memcard_access_wait();

    _card_read(hCard, 0, pData);

    do
    {
        mts_wait_vbl_800895F4(1);
    } while (!gHwCardLastOp_800B52F4);

    if (gHwCardLastOp_800B52F4 != 1)
    {
        printf("card_error\n");
        return 2;
    }
    else
    {
        if (pData[0] == 'M' && pData[1] == 'C')
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

int memcard_loaddir_800247E8(int port, int *pFreeBlockCount)
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

        do
        {
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

void memcard_load_files_80024960(int idx)
{
    int freeBlockCount;
    gMemCards_800B52F8[idx].field_0_card_idx = idx;
    gMemCards_800B52F8[idx].field_1_last_op = 1;
    gMemCards_800B52F8[idx].field_2_file_count = memcard_loaddir_800247E8(idx, &freeBlockCount);
    gMemCards_800B52F8[idx].field_3_free_blocks = 15 - freeBlockCount;
}

int memcard_retry_helper_800249CC(int state)
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

void memcard_reset_status_80024A3C()
{
    gMemCards_800B52F8[0].field_1_last_op = 2;
    gMemCards_800B52F8[1].field_1_last_op = 2;
}

void memcard_retry_80025178(int port);

static inline void memcard_wait()
{
    printf("[R]");

    while ((gHwCard_do_op_800B52E8 != memcard_hwcard_do_op_800244DC) ||
           (gSwCard_do_op_800B52EC != memcard_swcard_do_op_800244EC))
    {
        printf("ACCESS WAIT..\n");
        mts_wait_vbl_800895F4(2);
    }

    gHwCardLastOp_800B52F4 = 0;
    gSwCardLastOp_800B52F0 = 0;
}

int memcard_check_80024A54(int port)
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
        mts_wait_vbl_800895F4(1);

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
                memcard_retry_80025178(port);
                return;

            case 4:
                break;

            default:
                return; // FIXME: Return without value in function that returns long???
        }

    loop_24:
        memcard_wait();
        _card_clear(chan);

        do
        {
            mts_wait_vbl_800895F4(1);
        } while ((hw_card_op = !gHwCardLastOp_800B52F4));
        hw_card_op = gHwCardLastOp_800B52F4;

        if (hw_card_op == 1)
        {
            gMemCards_800B52F8[port].field_1_last_op = 4;

            memcard_wait();
            _card_load(chan);

            do
            {
                mts_wait_vbl_800895F4(1);
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

void memcard_init_80024E48()
{
    int idx; // $s1

    if (!gmem_card_system_inited_8009D524)
    {
        gmem_card_system_inited_8009D524 = !gmem_card_system_inited_8009D524;
        gHwCardLastOp_800B52F4 = 1;

        gSwCardLastOp_800B52F0 = 1;
        memcard_set_sw_hw_card_fns_8002469C();

        EnterCriticalSection();

        gHardware_end_io_800B52C8 = OpenEvent(
            0xF0000011, 4, 0x1000, (openevent_cb_t)memcard_hwcard_end_io_800244FC); // f = hardware, 11 = HwCARD, 4 = EvSpIOE = end io
        gHardware_end_write_800B52CC =
            OpenEvent(0xF0000011, 0x8000, 0x1000, (openevent_cb_t)memcard_hwcard_end_write_80024524); // EvSpIOEW = end write
        gHardware_timeout_800B52D0 =
            OpenEvent(0xF0000011, 0x100, 0x1000, (openevent_cb_t)memcard_hwcard_timeout_8002455C); // EvSpTIMOUT
        gHardware_new_device_800B52D4 =
            OpenEvent(0xF0000011, 0x2000, 0x1000, (openevent_cb_t)memcard_hwcard_new_80024594); // EvSpNEW new device

        gSoftware_end_io_800B52D8 = OpenEvent(
            0xF4000001, 4, 0x1000, (openevent_cb_t)memcard_swcard_end_io_800245CC); // f4 = bios/software, 1 = SwCARD, EvSpIOE
        gSoftware_end_write_800B52DC =
            OpenEvent(0xF4000001, 0x8000, 0x1000, (openevent_cb_t)memcard_swcard_end_write_800245F4);
        gSoftware_timeout_800B52E0 = OpenEvent(0xF4000001, 0x100, 0x1000, (openevent_cb_t)memcard_swcard_timeout_8002462C);
        gSoftware_new_device_800B52E4 = OpenEvent(0xF4000001, 0x2000, 0x1000, (openevent_cb_t)memcard_swcard_new_80024664);

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
        mts_set_vsync_task_800892B8();
        memcard_reset_status_80024A3C();

        for (idx = 0; idx < 2; idx++)
        {
            if (!memcard_check_80024A54(idx))
            {
                long v2 = memcard_easy_format_test_800246C0(idx);
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

void memcard_exit_800250C4()
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

void memcard_retry_80025178(int port)
{
    int op;
    int count;
    int i;

    switch (gMemCards_800B52F8[port].field_1_last_op)
    {
    case 1:
    case 4:
        op = gMemCards_800B52F8[port].field_1_last_op;
        memcard_retry_helper_800249CC(op);
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

        do
        {
            mts_wait_vbl_800895F4(1);
        }
        while (!gSwCardLastOp_800B52F0);

        op = gSwCardLastOp_800B52F0;

        if (op == 1 || op == 4)
        {
            break;
        }

        mts_wait_vbl_800895F4(3);
    }

    memcard_retry_helper_800249CC(op);
}

mem_card *memcard_get_files_80025350(int idx)
{
    mem_card *pCardBase = gMemCards_800B52F8;
    mem_card *pCard = &pCardBase[idx];

    if (pCard->field_1_last_op == 1 || pCard->field_1_last_op == 4)
    {
        memcard_load_files_80024960(idx);
        pCard->field_1_last_op = 1;
        return pCard;
    }
    return 0;
}

int memcard_delete_800253C4(int idx, const char *pFileName)
{
    char tmp[32];

    mem_card *pCardBase = gMemCards_800B52F8;
    mem_card *pCard = &pCardBase[idx];

    if (pCard->field_1_last_op == 1)
    {
        sprintf(tmp, "bu%02X:%s", 0x10 * idx, pFileName);
        if (erase(tmp))
        {
            printf("Deleted File %s", pFileName);
            return 1;
        }
        printf("ERROR : can't delete %s\n", pFileName);
    }
    return 0;
}

void memcard_hwcard_read_write_handler_8002546C(int op)
{
    if (op == 1)
    {
        gMemCard_io_size_800B5648 -= 128;
        if (!gMemCard_io_size_800B5648)
        {
            gHwCard_do_op_800B52E8 = memcard_hwcard_do_op_800244DC;
        }
    }
    else
    {
        gMemCard_io_size_800B5648 = -1;
        memcard_set_sw_hw_card_fns_8002469C();
    }
}

void memcard_swcard_read_write_handler_800254D4(int op)
{
    if (op == 1)
    {
        printf("MEMCARD READ/WRITE end\n");
    }
    else
    {
        printf("ERROR : MEMCARD READ/WRITE\n");
    }
    gSwCard_do_op_800B52EC = (TMemCardFunc)memcard_swcard_do_op_800244EC;
}

void memcard_set_read_write_8002551C(int fileSize)
{
    gHwCard_do_op_800B52E8 = memcard_hwcard_read_write_handler_8002546C;
    gSwCard_do_op_800B52EC = memcard_swcard_read_write_handler_800254D4;
    gMemCard_io_size_800B5648 = fileSize;
}

#define ROUND_UP(val,rounding) (((val) + (rounding) - 1) / (rounding) * (rounding))

void memcard_write_8002554C(int idx, const char *pFileName, int seekPos, char *pBuffer, int bufferSize)
{
    int blocks = ROUND_UP(bufferSize, 8192) / 8192;
    int hFile;
    char name[32];

    sprintf(name, "bu%02X:%s", idx * 16, pFileName);

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

    printf("MEMCARD WRITE %s FD %d SIZE %d\n", pFileName, hFile, bufferSize);
    bufferSize = ROUND_UP(bufferSize, 128);
    if (seekPos > 0)
    {
        lseek(hFile, seekPos, SEEK_SET);
    }
    memcard_set_read_write_8002551C(bufferSize);
    write(hFile, pBuffer, bufferSize);
    close(hFile);
    printf("WRITING FILE %s...\n", pFileName);
}

void memcard_read_8002569C(int idx, const char *pFilename, int seekPos, char *pBuffer, int bufferSize)
{
    char name[32];
    int hFile;

    sprintf(name, "bu%02x:%s", idx * 16, pFilename);
    hFile = open(name, FREAD | FASYNC);
    if (hFile < 0)
    {
        printf("MEMCARD READ ERROR FD %d\n", hFile);
        gMemCard_io_size_800B5648 = -1;
        return;
    }
    bufferSize = ROUND_UP(bufferSize, 128);
    printf("MEMCARD READ %s FD %d SIZE %d\n", pFilename, hFile, bufferSize);
    if (seekPos > 0)
    {
        lseek(hFile, seekPos, SEEK_SET);
    }
    memcard_set_read_write_8002551C(bufferSize);
    read(hFile, pBuffer, bufferSize);
    close(hFile);
    printf("READING FILE %s...\n", pFilename);
}

int memcard_get_status_800257B0()
{
    return gMemCard_io_size_800B5648;
}

int memcard_format_800257C0(int idx)
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
