#ifndef __MGS_TAKABE_FADEIO_H__
#define __MGS_TAKABE_FADEIO_H__

#define FADEIO_MODE_TOBLACK     (0x0000)
#define FADEIO_MODE_TOWHITE     (0x0001)

void *NewFadeInOut(int mode, int shade);
void *NewFadeInOutSet(int name, int where);

#endif // __MGS_TAKABE_FADEIO_H__
