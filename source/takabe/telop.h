#ifndef __MGS_TAKABE_TELOP_H__
#define __MGS_TAKABE_TELOP_H__

void *NewTelopSet(int name, int where, int argc, char **argv);
void *NewTelop2(int x, int y, int timer, int reload, int arg4, int arg5);
void *NewTelop(int x, int y, int timer, int reload, int tex); // SHUTTER?

#endif // __MGS_TAKABE_TELOP_H__
