#include "linker.h"
#include "memcard.h"

void mts_printf_8008BBA0(const char* formatStr, ...);
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
extern TMemCardSetFunc gSwCardLastOp_800B52F0;
extern TMemCardSetFunc gHwCardLastOp_800B52F4;

void memcard_hwcard_do_op_800244DC(TMemCardSetFunc op)
{
    gHwCardLastOp_800B52F4 = op;
    asm(""); // TODO: Fix me, hack to force delay slot to not be used
}

void memcard_swcard_do_op_800244EC(TMemCardSetFunc op)
{
    gSwCardLastOp_800B52F0 = op;
    asm(""); // TODO: Fix me, hack to force delay slot to not be used
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
