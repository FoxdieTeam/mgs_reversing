// "Mystery" soldier (ミステリー兵) of the VR missions: a revision of the watcher (enemy/watcher.c).
// The differences to the plain VR watcher are under #ifdef VR_MYSTERY in watcher.c.

#ifdef VR_EXE
#define VR_MYSTERY
#include "enemy/watcher.c"
#else
// (VR only) this file is empty in the main executable build
#endif
