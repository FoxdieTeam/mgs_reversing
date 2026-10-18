// "Mystery" soldier (ミステリー兵) of the VR missions: the differences to enemy/action.c are under #ifdef VR_MYSTERY.

#ifdef VR_EXE
#define VR_MYSTERY
#include "enemy/action.c"
#else
// (VR only) this file is empty in the main executable build
#endif
