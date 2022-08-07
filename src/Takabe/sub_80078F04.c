#include "linker.h"
#include "psyq.h"

extern RECT rect_8009F734;

extern u_long image_data_800B3818[256];

void sub_80078F04(void)
{
    StoreImage_8008FB70(&rect_8009F734, image_data_800B3818);
}
