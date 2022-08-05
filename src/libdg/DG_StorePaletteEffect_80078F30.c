#include "psyq.h"

extern RECT rect_8009F72C;
extern RECT rect_8009F734;

extern u_long image_data_800B3818[256];

void DG_StorePaletteEffect_80078F30(void)
{
    RECT rect1 = rect_8009F72C;
    RECT rect2 = rect_8009F734;

    int count = 0xf;

    for (; count > 0; count--)
    {
        DrawSync(0);
        StoreImage2_8009209C(&rect2, image_data_800B3818);
        DrawSync(0);
        LoadImage2_80091FB0(&rect1, image_data_800B3818);
        rect2.y += 2;
        rect1.y += 2;
    }
}
