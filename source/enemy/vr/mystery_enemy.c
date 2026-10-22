// Overlays that link this object: vefgh_01..10, vijkl_01/03/06/07/10, vr_grn02.
// It is enemy/enemy.c compiled with VR_MYSTERY defined (the "mystery" soldier revision);
// all other VR overlays use the plain VR_EXE build of the same file (enemy/enemy.obj).
// "Mystery" soldier (ミステリー兵) of the VR missions: the differences to enemy/enemy.c are under #ifdef VR_MYSTERY.

#ifdef VR_EXE
#define VR_MYSTERY
#include "enemy/enemy.c"
#else
// (VR only) this file is empty in the main executable build
#endif
