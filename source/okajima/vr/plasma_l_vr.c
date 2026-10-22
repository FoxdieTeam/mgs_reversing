// VR build of plasma_l.c (cyborg ninja effects): the same source as the s08b overlay, whose relocatable asm (INCLUDE_ASM_RELOC)
// is only used with VR_EXE. Lives outside of source/overlays so that the importer shares the object between the VR overlays.

#ifdef VR_EXE
#include "overlays/s08b/okajima/plasma_l.c"
#else
// (VR only) this file is empty in the main executable build
#endif
