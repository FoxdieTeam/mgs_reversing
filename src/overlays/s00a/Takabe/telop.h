#ifndef _TELOP_H_
#define _TELOP_H_

void *NewTelopSet_800DDB34(int name, int where, int argc, char **argv);
void *NewTelop2_800DDC60(int x, int y, int timer, int reload, int arg4, int arg5);
void *NewTelop_800DDD7C(int x, int y, int timer, int reload, int tex); // SHUTTER?

#endif // _TELOP_H_
