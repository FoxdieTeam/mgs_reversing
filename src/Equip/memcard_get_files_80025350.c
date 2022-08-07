#include "linker.h"
#include "mts/mts_new.h"
#include "memcard/memcard.h"
#include "psyq.h"

extern long gHardware_end_io_800B52C8;
extern long gHardware_end_write_800B52CC;
extern long gHardware_timeout_800B52D0;
extern long gHardware_new_device_800B52D4;

extern long gSoftware_end_io_800B52D8;
extern long gSoftware_end_write_800B52DC;
extern long gSoftware_timeout_800B52E0;
extern long gSoftware_new_device_800B52E4;

extern TMemCardFunc             gHwCard_do_op_800B52E8;
extern TMemCardFunc             gSwCard_do_op_800B52EC;
extern volatile TMemCardSetFunc gSwCardLastOp_800B52F0;
extern volatile TMemCardSetFunc gHwCardLastOp_800B52F4;

extern struct mem_card gMemCards_800B52F8[2];

extern volatile long gMemCard_io_size_800B5648;

extern const char SECTION(".rdata") aBu02xS[];
extern const char SECTION(".rdata") aDeletedFileS[];
extern const char SECTION(".rdata") aErrorCanTDelet[];

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
            gHwCard_do_op_800B52E8 = (TMemCardFunc)memcard_hwcard_do_op_800244DC;
        }
    }
    else
    {
        gMemCard_io_size_800B5648 = -1;
        memcard_set_sw_hw_card_fns_8002469C();
    }
}

extern const char aMemcardReadWri[];
extern const char aErrorMemcardRe[];

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
