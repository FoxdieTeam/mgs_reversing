#ifndef _THING_H_
#define _THING_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libhzd/libhzd.h"

int            THING_Gcl_GetIntDefault(char param, int def);
int            THING_Gcl_GetInt(char param);
unsigned short THING_Gcl_GetShortDefault(char param, unsigned short def);
unsigned short THING_Gcl_GetShort(char param);
void           THING_Gcl_GetSVectorDefault(char param, short x, short y, short z, SVECTOR *vec);
void           THING_Gcl_GetSVector(char param, SVECTOR *vec);

int THING_Msg_CheckMessage(unsigned short name, int hash_count, unsigned short *hashes);
int THING_Msg_GetResult(void);

void s16b_800C4594(unsigned short address, unsigned short message);
void s16b_800C45C4(HZD_SEG *seg, MATRIX *trans, SVECTOR *arg2, SVECTOR *arg3);
void s16b_800C46D8(HZD_FLR *flr, SVECTOR *arg1, SVECTOR *arg2);

#endif // _THING_H_
