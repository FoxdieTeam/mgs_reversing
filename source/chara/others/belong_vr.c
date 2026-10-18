// Revision of the "belong" actor (付随物) used by the VR missions of vcd_n03 (and friends): the attached model can
// additionally hide a unit (EQ_InvisibleUnit) of its parent. The differences are under #ifdef VR_BELONG in belong.c.

#ifdef VR_EXE
#define VR_BELONG
#include "chara/others/belong.c"
#else
// (VR only) this file is empty in the main executable build
#endif
