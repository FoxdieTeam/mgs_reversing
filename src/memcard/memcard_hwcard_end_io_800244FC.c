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

extern TMemCardFunc gHwCard_do_op_800B52E8[4];

//extern TMemCardFunc gSwCardLastOp_800B52F0;

void memcard_hwcard_do_op_800244DC(TMemCardFunc op)
{
    gHwCard_do_op_800B52E8[3] = op;
    asm(""); // TODO: Fix me, hack to force delay slot to not be used
}

void memcard_swcard_do_op_800244EC(TMemCardFunc op)
{
    gHwCard_do_op_800B52E8[2] = op;
    asm(""); // TODO: Fix me, hack to force delay slot to not be used
}

void memcard_hwcard_end_io_800244FC()
{
    gHwCard_do_op_800B52E8[0](1);
}

void memcard_hwcard_end_write_80024524()
{
    mts_printf_8008BBA0(aHwCardError);
    gHwCard_do_op_800B52E8[0](2);
}

void memcard_hwcard_timeout_8002455C()
{
    mts_printf_8008BBA0(aCHTO);
    gHwCard_do_op_800B52E8[0](3);
}

void memcard_hwcard_new_80024594()
{
    mts_printf_8008BBA0(aHwCardNew);
    gHwCard_do_op_800B52E8[0](4);
}

void memcard_swcard_end_io_800245CC()
{
    gHwCard_do_op_800B52E8[1](1);
}

void memcard_swcard_end_write_800245F4()
{
    mts_printf_8008BBA0(aSwCardError);
    gHwCard_do_op_800B52E8[1](2);
}

void memcard_swcard_timeout_8002462C()
{
    mts_printf_8008BBA0(aCSTO);
    gHwCard_do_op_800B52E8[1](3);
}

void memcard_swcard_new_80024664()
{
    mts_printf_8008BBA0(aSwCardNew);
    gHwCard_do_op_800B52E8[1](4);
}

