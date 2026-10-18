// vrsave: any direction or button held on the pad of port 3.
#include "libgv/libgv.h"

int vrsave_800CB6E0(void)
{
    return GV_PadData[2].status & (PAD_UDLR | PAD_ABXY);
}
