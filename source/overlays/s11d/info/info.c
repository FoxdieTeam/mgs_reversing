#include "info.h"

// External function declarations
extern int sub_800D1804(int param);
extern void sub_800D189C(void);

// Info system global variables
static int info_int_800C3350;  // Flag/state
static int info_int_800C3354;  // Counter/parameter
static int info_int_800C3358;  // Result/state

// Initialization function - sets up info system with parameters
void s11d_info_800CDAAC(int param1, int param2)
{
    if (info_int_800C3350 == 0)
    {
        info_int_800C3350 = 1;
        info_int_800C3354 = param1;
        info_int_800C3358 = sub_800D1804(param2);
    }
}

// Cleanup function - resets info system state
void s11d_info_800CDAF8(void)
{
    if (info_int_800C3354 != 0)
    {
        if (info_int_800C3350 != 0)
        {
            if (info_int_800C3358 != 0)
            {
                sub_800D189C();
                info_int_800C3358 = 0;
            }
            info_int_800C3350 = 0;
        }
    }
}

// Counter decrement function - decrements counter and cleans up if zero
void s11d_info_800CDB5C(void)
{
    if (info_int_800C3354 != 0)
    {
        info_int_800C3354--;
        if (info_int_800C3354 == 0)
        {
            info_int_800C3358 = 0;
            info_int_800C3350 = 0;
        }
    }
}
