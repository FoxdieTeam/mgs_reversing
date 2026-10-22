// Overlays that link this object: vcd_n01, vcd_n02, vcd_n03.
// It is enemy/watcher.c compiled with VR_MINENE defined (the "minene" soldier revision (VR ninja-play missions));
// all other VR overlays use the plain VR_EXE build of the same file (enemy/watcher.obj).
// "Minene" soldier of the VR ninja-play missions: a revision of the watcher (enemy/watcher.c):  the differences to the plain VR watcher are under #ifdef VR_MINENE.

#ifdef VR_EXE
#define VR_MINENE
#include "enemy/watcher.c"
#else
// (VR only) this file is empty in the main executable build
#endif
