// "Minene" soldier of the VR ninja-play missions: a revision of the watcher (enemy/watcher.c):  the differences to the plain VR watcher are under #ifdef VR_MINENE.

#ifdef VR_EXE
#define VR_MINENE
#include "enemy/watcher.c"
#else
// (VR only) this file is empty in the main executable build
#endif
