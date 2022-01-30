#include "linker.h"
#include "memcard.h"

void memcard_hwcard_read_write_handler_8002546C(int op);

extern TMemCardFunc gHwCard_do_op_800B52E8;

void memcard_hwcard_end_io_800244FC()
{
    gHwCard_do_op_800B52E8(1);
}
