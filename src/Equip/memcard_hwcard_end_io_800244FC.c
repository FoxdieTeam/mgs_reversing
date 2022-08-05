#include "linker.h"
#include "memcard/memcard.h"
#include "psyq.h"
#include "mts/mts_new.h"

extern const char aHwCardError[];
extern const char aCHTO[];
extern const char aHwCardNew[];
extern const char aSwCardError[];
extern const char aCSTO[];
extern const char aSwCardNew[];

void memcard_hwcard_read_write_handler_8002546C(int op);

extern TMemCardFunc gHwCard_do_op_800B52E8;
extern TMemCardFunc gSwCard_do_op_800B52EC;

// ?? something strange going on with these types
extern volatile TMemCardSetFunc gSwCardLastOp_800B52F0;
extern volatile TMemCardSetFunc gHwCardLastOp_800B52F4;

void memcard_hwcard_do_op_800244DC(TMemCardSetFunc op)
{
    gHwCardLastOp_800B52F4 = op;
}

void memcard_swcard_do_op_800244EC(TMemCardSetFunc op)
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
    gHwCard_do_op_800B52E8 = (TMemCardFunc)memcard_hwcard_do_op_800244DC;
    gSwCard_do_op_800B52EC = (TMemCardFunc)memcard_swcard_do_op_800244EC;
}

extern const char aEasyFormatTest[];
extern const char aR[];
extern const char aAccessWait[];
extern const char aCardNormal[];
extern const char aCardUnformat[];
extern const char aCardError[];

long card_read_8009901C(long chan, long block, unsigned char *buf);

int memcard_easy_format_test_800246C0(int hCard)
{
    char pData[128]; // [sp+10h] [-80h] BYREF

    mts_printf_8008BBA0(aEasyFormatTest);
    memset_8008E688(pData, 0, 128);
    mts_printf_8008BBA0(aR);

    while ((char *)gHwCard_do_op_800B52E8 != (char *)memcard_hwcard_do_op_800244DC ||
           (char *)gSwCard_do_op_800B52EC != (char *)memcard_swcard_do_op_800244EC)
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

    if (gHwCardLastOp_800B52F4 != (volatile TMemCardSetFunc)1) // ?
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
