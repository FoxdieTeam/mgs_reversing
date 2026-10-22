// Bloody Meryl of the VR "godzilla" mission (vcd_n05): the s10a code with a few differences (#ifdef VR_MEL10)
#ifdef VR_EXE
#define VR_MEL10
#include "overlays/s10a/okajima/meryl10/mel10.c"
#else
// (VR only) this file is empty in the main executable build
#endif
