#include "psyq.h"

extern RECT rect_8009F72C;

extern u_long image_data_800B3818[256];

static inline ushort modify_data(ushort data, ushort param_2)
{
    ushort high = data & 0x8000;
    
    if ((data & 0x7fff) != 0) {
        return high | param_2;
    } else {
        return high;
    }
}

void sub_80079004(ushort param_1)
{
    RECT rect = rect_8009F72C;
    int count, count2;
    ushort *ptr;
    
    count = 15;
    
    for (; count > 0; count--) {
        DrawSync(0);
        StoreImage2_8009209C(&rect, image_data_800B3818);
        DrawSync(0);

        ptr = (ushort *)image_data_800B3818;
        count2 = 512;

        for (; count2 > 0; count2--) {
            *ptr++ = modify_data(*ptr, param_1);
        }
        
        LoadImage2_80091FB0(&rect, image_data_800B3818);
        rect.y += 2;
    }
}
