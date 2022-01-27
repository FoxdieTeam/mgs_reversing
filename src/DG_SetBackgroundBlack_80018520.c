#include "linker.h"
#include "libdg.h"
#include "dgd.h"

extern void DG_SetBackgroundRGB_80018464(int r, int g, int b);

// Force gp
unsigned char SECTION(".sbss") DG_r_800AB97C;
unsigned char SECTION(".sbss") DG_b_800AB97D;
unsigned char SECTION(".sbss") DG_g_800AB97E;

extern unsigned char SECTION(".sbss") DG_r_800AB97C;
extern unsigned char SECTION(".sbss") DG_b_800AB97D;
extern unsigned char SECTION(".sbss") DG_g_800AB97E;

void DG_SetBackgroundBlack_80018520(void)
{
  DG_SetBackgroundRGB_80018464(0, 0, 0);
}
void DG_BackGroundNormal_80018548()
{
  DG_SetBackgroundRGB_80018464(DG_r_800AB97C, DG_b_800AB97D, DG_g_800AB97E);
}

void sub_80018574(unsigned char *a1)
{
  // TODO: Structure
  a1[4] = DG_r_800AB97C;
  a1[5] = DG_b_800AB97D;
  a1[6] = DG_g_800AB97E;
}

extern TChanl_Fn SECTION(".data") off_8009D35C[];

TChanl_Fn DG_SetPipelineFunc_80018598(int idx, TChanl_Fn newFunc)
{
  TChanl_Fn oldFunc = off_8009D35C[idx];
  off_8009D35C[idx] = newFunc;
  return oldFunc;
}

void DG_BoundStart_800185B4(void)
{

}
