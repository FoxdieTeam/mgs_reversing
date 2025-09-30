#ifndef __MGS_TAKABE_SHAKEMDL_H__
#define __MGS_TAKABE_SHAKEMDL_H__

void *NewShakeModelGCL( int name, int where, int argc, char **argv );
void *NewShakeModel( int model, int axis, int scale );

#endif // __MGS_TAKABE_SHAKEMDL_H__
