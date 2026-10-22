// vrsave: VR save menu, derives the three digits of the displayed stage name from the stage numbers.
#include "overlays/vrsave/vrsave.h"

void vrsave_800CAF68(VR_SAVEMNGR_WORK *work)
{
    int a;
    int b;

    if (work->field_2F4 < 5)
    {
        if (work->field_2F0 < 20)
        {
            work->field_300 = work->field_2F0;
            a = 3;
            if (!(work->field_2F4 & 1))
            {
                a = 4;
            }
            work->field_2F8 = a;
            b = 1;
            if (work->field_2F4 < 3)
            {
                b = 2;
            }
            work->field_2FC = b;
        }
        else
        {
            work->field_300 = work->field_2F0 % 10;
            work->field_2FC = work->field_2F0 / 10;
            if (work->field_2F4 < 3)
            {
                work->field_2F8 = work->field_2F4;
            }
            else
            {
                work->field_2F8 = work->field_2F4 + 2;
            }
        }
    }
    else
    {
        work->field_2FC = 0;
        work->field_2F8 = work->field_2F4 + 2;
        work->field_300 = work->field_2F0 % 10;
        if (work->field_2F4 < 7)
        {
            work->field_300 = 0;
            work->field_2FC = work->field_2F0 % 10;
        }
        if (work->field_300 == 0 && work->field_2F8 == 12)
        {
            work->field_300 = 10;
        }
    }

    if (work->field_2FC >= 10)
    {
        work->field_2FC = 9;
    }
    if (work->field_2F8 >= 17)
    {
        work->field_2F8 = 16;
    }
}
