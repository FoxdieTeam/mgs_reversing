// "Minene" soldier of the VR ninja-play missions: the differences to the plain VR check are under #ifdef VR_MINENE.

#ifdef VR_EXE
#define VR_MINENE
#include "enemy/check.c"
#else
// (VR only) this file is empty in the main executable build
#endif
