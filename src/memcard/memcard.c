#include "linker.h"
#include "memcard.h"
#include "psyq.h"
#include "mts/mts_new.h"
#include <KERNEL.H>
#include <SYS/FILE.H>
#include "psyq.h"

extern int             gmem_card_system_inited_8009D524;
extern struct mem_card gMemCards_800B52F8[2];
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

extern const char aHwCardError[];
extern const char aCHTO[];
extern const char aHwCardNew[];
extern const char aSwCardError[];
extern const char aCSTO[];
extern const char aSwCardNew[];
extern const char aBu02x[];            // = "bu%02X:*";
extern const char aBu02x_0[];          // = "bu%02x:";
extern const char aFormatedD[];        // = "FORMATED %d\n";
extern const char aErrorMemcardFo[];   // = "ERROR : MEMCARD FORMAT\n";
extern const char aErrorMemcardFo_0[]; // = "ERROR : MEMCARD FORMATED CARD\n";
extern const char aLoadDirSStart[];    // = "load_dir %s start\n";
extern const char aTotalDFilesUse[];   // = "TOTAL %d FILES used %d block\n";
extern const char aNoFile[];           // = "NO FILE\n";
extern const char aEasyFormatTest[];
extern const char aR[];
extern const char aAccessWait[];
extern const char aCardNormal[];
extern const char aCardUnformat[];
extern const char aCardError[];
extern const char aDeletedFileS[];
extern const char aErrorCanTDelet[];
extern const char aMemcardReadWri[];
extern const char aErrorMemcardRe[];
extern const char aBu02xS[];         // = "bu%02X:%s"
extern const char aWarningMemcard[]; // = "Warning : MEMCARD create error ... overwrite\n"
extern const char aMemcardWriteEr[]; // = "MEMCARD WRITE ERROR FD %d\n"
extern const char aMemcardWriteSF[]; // = "MEMCARD WRITE %s FD %d SIZE %d\n"
extern const char aWritingFileS[];   // = "WRITING FILE %s...\n"
extern const char aBu02xS_0[];
extern const char aMemcardReadErr[];
extern const char aMemcardReadSFd[];
extern const char aReadingFileS[];

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
    mts_printf_8008BBA0(aHwCardError);
    gHwCard_do_op_800B52E8(2);
}

void memcard_hwcard_timeout_8002455C()
{
    mts_printf_8008BBA0(aCHTO);
    gHwCard_do_op_800B52E8(3);
}

void memcard_hwcard_new_80024594()
{
    mts_printf_8008BBA0(aHwCardNew);
    gHwCard_do_op_800B52E8(4);
}

void memcard_swcard_end_io_800245CC()
{
    gSwCard_do_op_800B52EC(1);
}

void memcard_swcard_end_write_800245F4()
{
    mts_printf_8008BBA0(aSwCardError);
    gSwCard_do_op_800B52EC(2);
}

void memcard_swcard_timeout_8002462C()
{
    mts_printf_8008BBA0(aCSTO);
    gSwCard_do_op_800B52EC(3);
}

void memcard_swcard_new_80024664()
{
    mts_printf_8008BBA0(aSwCardNew);
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

    mts_printf_8008BBA0(aEasyFormatTest);
    memset(pData, 0, sizeof(pData));
    mts_printf_8008BBA0(aR);

    while (gHwCard_do_op_800B52E8 != memcard_hwcard_do_op_800244DC ||
           gSwCard_do_op_800B52EC != memcard_swcard_do_op_800244EC)
    {
        mts_printf_8008BBA0(aAccessWait);
        mts_wait_vbl_800895F4(2);
    }

    gHwCardLastOp_800B52F4 = 0;
    gSwCardLastOp_800B52F0 = 0;

    card_read_8009901C(hCard, 0, pData);

    do
    {
        mts_wait_vbl_800895F4(1);
    } while (!gHwCardLastOp_800B52F4);

    if (gHwCardLastOp_800B52F4 != 1)
    {
        mts_printf_8008BBA0(aCardError);
        return 2;
    }
    else
    {
        if (pData[0] == 'M' && pData[1] == 'C')
        {
            mts_printf_8008BBA0(aCardNormal);
            return 1;
        }
        else
        {
            mts_printf_8008BBA0(aCardUnformat);
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

    sprintf_8008E878(name, aBu02x, port * 16);
    mts_printf_8008BBA0(aLoadDirSStart, name);

    if (firstfile_80099AEC(name, &dir))
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
        while (nextfile_800995EC(&dir));

        mts_printf_8008BBA0(aTotalDFilesUse, files, blocks);
        *pFreeBlockCount = blocks;
        return files;
    }

    mts_printf_8008BBA0(aNoFile);
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

void memcard_reset_status_80024A3C(void)
{
    gMemCards_800B52F8[0].field_1_last_op = 2;
    gMemCards_800B52F8[1].field_1_last_op = 2;
}

#pragma INCLUDE_ASM("asm/memcard/memcard_check_80024A54.s") // 1012 bytes

void memcard_init_80024E48()
{
    int idx; // $s1

    if (!gmem_card_system_inited_8009D524)
    {
        gmem_card_system_inited_8009D524 = !gmem_card_system_inited_8009D524;
        gHwCardLastOp_800B52F4 = 1;

        gSwCardLastOp_800B52F0 = 1;
        memcard_set_sw_hw_card_fns_8002469C();

        EnterCriticalSection_8009952C();

        gHardware_end_io_800B52C8 = OpenEvent_8009946C(
            0xF0000011, 4, 0x1000, memcard_hwcard_end_io_800244FC); // f = hardware, 11 = HwCARD, 4 = EvSpIOE = end io
        gHardware_end_write_800B52CC =
            OpenEvent_8009946C(0xF0000011, 0x8000, 0x1000, memcard_hwcard_end_write_80024524); // EvSpIOEW = end write
        gHardware_timeout_800B52D0 =
            OpenEvent_8009946C(0xF0000011, 0x100, 0x1000, memcard_hwcard_timeout_8002455C); // EvSpTIMOUT
        gHardware_new_device_800B52D4 =
            OpenEvent_8009946C(0xF0000011, 0x2000, 0x1000, memcard_hwcard_new_80024594); // EvSpNEW new device

        gSoftware_end_io_800B52D8 = OpenEvent_8009946C(
            0xF4000001, 4, 0x1000, memcard_swcard_end_io_800245CC); // f4 = bios/software, 1 = SwCARD, EvSpIOE
        gSoftware_end_write_800B52DC =
            OpenEvent_8009946C(0xF4000001, 0x8000, 0x1000, memcard_swcard_end_write_800245F4);
        gSoftware_timeout_800B52E0 = OpenEvent_8009946C(0xF4000001, 0x100, 0x1000, memcard_swcard_timeout_8002462C);
        gSoftware_new_device_800B52E4 = OpenEvent_8009946C(0xF4000001, 0x2000, 0x1000, memcard_swcard_new_80024664);

        EnableEvent_800994AC(gHardware_end_io_800B52C8);
        EnableEvent_800994AC(gHardware_end_write_800B52CC);
        EnableEvent_800994AC(gHardware_timeout_800B52D0);
        EnableEvent_800994AC(gHardware_new_device_800B52D4);

        EnableEvent_800994AC(gSoftware_end_io_800B52D8);
        EnableEvent_800994AC(gSoftware_end_write_800B52DC);
        EnableEvent_800994AC(gSoftware_timeout_800B52E0);
        EnableEvent_800994AC(gSoftware_new_device_800B52E4);

        ExitCriticalSection_8009953C();

        idx = 0;

        InitCARD_8009908C(0);
        StartCARD_800990F8();
        bu_init_80098FEC();
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
    StopCARD_80099130();
    EnterCriticalSection_8009952C();
    CloseEvent_8009947C(gHardware_end_io_800B52C8);
    CloseEvent_8009947C(gHardware_end_write_800B52CC);
    CloseEvent_8009947C(gHardware_timeout_800B52D0);
    CloseEvent_8009947C(gHardware_new_device_800B52D4);
    CloseEvent_8009947C(gSoftware_end_io_800B52D8);
    CloseEvent_8009947C(gSoftware_end_write_800B52DC);
    CloseEvent_8009947C(gSoftware_timeout_800B52E0);
    CloseEvent_8009947C(gSoftware_new_device_800B52E4);
    ExitCriticalSection_8009953C();
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
        mts_printf_8008BBA0(aR);

        while ((gHwCard_do_op_800B52E8 != &memcard_hwcard_do_op_800244DC) ||
               (gSwCard_do_op_800B52EC != &memcard_swcard_do_op_800244EC))
        {
            mts_printf_8008BBA0(aAccessWait);
            mts_wait_vbl_800895F4(2);
        }

        gHwCardLastOp_800B52F4 = 0;
        gSwCardLastOp_800B52F0 = 0;
        card_info_80098FFC(port * 16);

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

struct mem_card *memcard_get_files_80025350(int idx)
{
    struct mem_card *pCardBase = gMemCards_800B52F8;
    struct mem_card *pCard = &pCardBase[idx];

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

    struct mem_card *pCardBase = gMemCards_800B52F8;
    struct mem_card *pCard = &pCardBase[idx];

    if (pCard->field_1_last_op == 1)
    {
        sprintf_8008E878(tmp, aBu02xS, 0x10 * idx, pFileName);
        if (erase_800995FC(tmp))
        {
            mts_printf_8008BBA0(aDeletedFileS, pFileName);
            return 1;
        }
        mts_printf_8008BBA0(aErrorCanTDelet, pFileName);
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
        mts_printf_8008BBA0(aMemcardReadWri);
    }
    else
    {
        mts_printf_8008BBA0(aErrorMemcardRe);
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

    sprintf_8008E878(name, aBu02xS, idx * 16, pFileName);

    hFile = open_8009958C(name, (blocks << 16) | O_CREAT);
    if (hFile < 0)
    {
        mts_printf_8008BBA0(aWarningMemcard);
    }
    close_800995CC(hFile);

    hFile = open_8009958C(name, O_NOWAIT | O_WRONLY);
    if (hFile < 0)
    {
        mts_printf_8008BBA0(aMemcardWriteEr, hFile);
        gMemCard_io_size_800B5648 = -1;
        return;
    }

    mts_printf_8008BBA0(aMemcardWriteSF, pFileName, hFile, bufferSize);
    bufferSize = ROUND_UP(bufferSize, 128);
    if (seekPos > 0)
    {
        lseek_8009959C(hFile, seekPos, SEEK_SET);
    }
    memcard_set_read_write_8002551C(bufferSize);
    write_800995BC(hFile, pBuffer, bufferSize);
    close_800995CC(hFile);
    mts_printf_8008BBA0(aWritingFileS, pFileName);
}

void memcard_read_8002569C(int idx, const char *pFilename, int seekPos, char *pBuffer, int bufferSize)
{
    char name[32];
    int hFile;

    sprintf_8008E878(name, aBu02xS_0, idx * 16, pFilename);
    hFile = open_8009958C(name, FREAD | FASYNC);
    if (hFile < 0)
    {
        mts_printf_8008BBA0(aMemcardReadErr, hFile);
        gMemCard_io_size_800B5648 = -1;
        return;
    }
    bufferSize = ROUND_UP(bufferSize, 128);
    mts_printf_8008BBA0(aMemcardReadSFd, pFilename, hFile, bufferSize);
    if (seekPos > 0)
    {
        lseek_8009959C(hFile, seekPos, SEEK_SET);
    }
    memcard_set_read_write_8002551C(bufferSize);
    read_800995AC(hFile, pBuffer, bufferSize);
    close_800995CC(hFile);
    mts_printf_8008BBA0(aReadingFileS, pFilename);
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
    sprintf_8008E878(cardPath, aBu02x_0, idx * 16);

    if (gMemCards_800B52F8[idx].field_1_last_op == 5)
    {
    retry:
        if (format_800995DC(cardPath) != 0)
        {
            mts_printf_8008BBA0(aFormatedD, idx);
            gMemCards_800B52F8[idx].field_1_last_op = 1;
            return 1;
        }
        retries--;
        if (retries <= 0)
        {
            mts_printf_8008BBA0(aErrorMemcardFo);
            return 0;
        }
        goto retry; // TODO: find a match without goto
    }

    mts_printf_8008BBA0(aErrorMemcardFo_0);
    return 0;
}
