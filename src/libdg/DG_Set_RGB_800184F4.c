#include "linker.h"

// Force gp
unsigned char SECTION(".sbss") DG_r_800AB97C;
unsigned char SECTION(".sbss") DG_b_800AB97D;
unsigned char SECTION(".sbss") DG_g_800AB97E;

extern unsigned char SECTION(".sbss") DG_r_800AB97C;
extern unsigned char SECTION(".sbss") DG_b_800AB97D;
extern unsigned char SECTION(".sbss") DG_g_800AB97E;

void DG_SetBackgroundRGB_80018464(int r, int g, int b);

void DG_Set_RGB_800184F4(int r,int b, int g)
{
    DG_r_800AB97C = r;
    DG_g_800AB97E = g;
    DG_b_800AB97D = b;
    DG_SetBackgroundRGB_80018464(r, b, g);
}