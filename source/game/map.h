#ifndef __MGS_GAME_MAP_H__
#define __MGS_GAME_MAP_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libhzd/libhzd.h"
#include "libdg/libdg.h"

// This is originally a u_long *,
// with (DG_LIT *)( lit + 1 ) used to access the lights
typedef struct LIT
{
    int    n_lights;
    DG_LIT lights[0];
} LIT;

typedef struct MAP
{
    int      index;
    u_short  name;
    u_short  used;
    HZD_HDL *hzd;
    LIT     *lit;
    int      zone;
} MAP;

// Local to game/area.c
#define MAX_HISTORY 8
typedef struct AreaHistory
{
    short history[MAX_HISTORY];
} AreaHistory;

MAP     *GM_FindMap(int name);
int      GM_AddMap(int name);
int      GM_DelMap(int name);
MAP     *GM_GetMap(int id);
MAP     *GM_DefineMap(void);
int      GM_ReloadMap(int preshade);
void     GM_UpdateMap(void);
void     GM_ResetMap(void);
HZD_HDL *GM_IterHazard(HZD_HDL *cur);
void     GM_ResetMapHazard(void);
void     GM_ResetMapModel(void);
MAP     *GM_FindMapZone(int zone);
MAP     *GM_CreateMap(void);
void     GM_ReshadeObjs(DG_OBJS *objs);
void     GM_ReshadeMapAll(void);

#endif // __MGS_GAME_MAP_H__
