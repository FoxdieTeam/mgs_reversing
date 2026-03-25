#ifndef __MGS_TAKABE_THING_H__
#define __MGS_TAKABE_THING_H__

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
void THING_Msg_SendMessage(unsigned short address, unsigned short message);

void THING_Hzd_800C45C4(HZD_SEG *seg, MATRIX *trans, SVECTOR *arg2, SVECTOR *arg3);
void THING_Hzd_800C46D8(HZD_FLR *flr, SVECTOR *arg1, SVECTOR *arg2);
// int THING_Hzd_800C4820(HZD_SEG *find, int count, HZD_SEG *segs);
// int THING_Hzd_800C4848(HZD_FLR *find, int count, HZD_FLR *flrs);
void THING_Hzd_800C4874(int n_segs, HZD_SEG *segs, int n_flrs, HZD_FLR *flrs);
void THING_Hzd_800C49AC(HZD_SEG *seg);

#endif // __MGS_TAKABE_THING_H__
