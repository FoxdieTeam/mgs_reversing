// Overlays that link this object: vcd_n01, vcd_n02, vcd_n03.
// It is enemy/think.c compiled with VR_MINENE defined (the "minene" soldier revision (VR ninja-play missions));
// all other VR overlays use the plain VR_EXE build of the same file (enemy/think.obj).
// "Minene" soldier of the VR ninja-play missions: the differences to the plain VR think are under #ifdef VR_MINENE.

#ifdef VR_EXE
#define VR_MINENE
#include "enemy/think.c"
#else
// (VR only) this file is empty in the main executable build
#endif
