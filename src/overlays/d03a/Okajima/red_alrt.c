#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _RedAlrtPrims
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} RedAlrtPrims;

typedef struct _RedAlrtWork
{
    GV_ACT        actor;
    RedAlrtPrims *prims;
    int           f24;
    int           f28;
    int           f2C;
    SVECTOR       f30;
    SVECTOR       f38;
    int           f40;
    SVECTOR       color;
    SVECTOR       f4C;
    int           map;
    int           f58;
    int           f5C;
    int           f60;
    int           f64;
    int           f68;
    int           f6C;
} RedAlrtWork;

extern int GM_CurrentMap_800AB9B0;

extern const char aRedAlrtC[]; // = "red_alrt.c"

#define EXEC_LEVEL 3

// Identical to THING_Msg_CheckMessage minus returning the message value.
int d03a_red_alrt_800C437C(unsigned short name, int nhashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage_80016620(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < nhashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

#pragma INCLUDE_ASM("asm/overlays/d03a/d03a_red_alrt_800C4414.s")

void d03a_red_alrt_800C45CC(RedAlrtWork *work, int arg1, short x, short y, short z)
{
    work->f28 = arg1;
    work->f38.vx = x;
    work->f38.vy = y;
    work->f38.vz = z;
}

#pragma INCLUDE_ASM("asm/overlays/d03a/d03a_red_alrt_800C45E4.s")
void d03a_red_alrt_800C45E4(RedAlrtWork *work);

#pragma INCLUDE_ASM("asm/overlays/d03a/d03a_red_alrt_800C48D0.s")
void d03a_red_alrt_800C48D0(RedAlrtWork *work);

int d03a_red_alrt_800C4904(int opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(result, svec);

        svec++;
        count++;
    }

    return count;
}

#pragma INCLUDE_ASM("asm/overlays/d03a/d03a_red_alrt_800C4958.s")
int d03a_red_alrt_800C4958(RedAlrtWork *, int, int);

int d03a_red_alrt_800C4BB0(RedAlrtWork *work, int arg1, int arg2, SVECTOR *color, SVECTOR *arg4, int arg5, int arg6)
{
    RedAlrtPrims *prims;

    work->f6C = 1;
    work->f58 = arg1;
    work->f60 = arg2;
    work->map = GM_CurrentMap_800AB9B0;
    work->f68 = arg6;
    work->color = *color;
    work->f4C = *arg4;
    work->f64 = arg5;

    if (arg5 == 2)
    {
        work->color.vx = 255 - work->color.vx;
        work->color.vy = 255 - work->color.vy;
        work->color.vz = 255 - work->color.vz;

        work->f4C.vx = 255 - work->f4C.vx;
        work->f4C.vy = 255 - work->f4C.vy;
        work->f4C.vz = 255 - work->f4C.vz;
    }

    prims = GV_Malloc_8001620C(sizeof(RedAlrtPrims));
    work->prims = prims;
    if (prims == NULL)
    {
        return -1;
    }

    setDrawTPage(&prims->tpage[0], 0, 1, work->f64 << 5);
    setDrawTPage(&prims->tpage[1], 0, 1, work->f64 << 5);

    setTile(&prims->tile[0]);
    setSemiTrans(&prims->tile[0], 1);

    prims->tile[0].x0 = -160;
    prims->tile[0].y0 = -112;
    prims->tile[0].w = 320;
    prims->tile[0].h = 224;

    prims->tile[1] = prims->tile[0];

    prims->tile[0].r0 = work->color.vx;
    prims->tile[0].g0 = work->color.vy;
    prims->tile[0].b0 = work->color.vz;

    prims->tile[1].r0 = work->color.vx;
    prims->tile[1].g0 = work->color.vy;
    prims->tile[1].b0 = work->color.vz;

    work->f30 = work->color;
    work->f38 = work->f4C;
    work->f2C = 0;
    work->f28 = arg2;
    work->f40 = 0;
    work->f24 = work->f60;
    work->f5C = 1;

    return 0;
}

GV_ACT * d03a_red_alrt_800C4DF0(int arg0, int arg1)
{
    RedAlrtWork *work;

    work = (RedAlrtWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(RedAlrtWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)d03a_red_alrt_800C45E4, (TActorFunction)d03a_red_alrt_800C48D0, aRedAlrtC);

        if (d03a_red_alrt_800C4958(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT * d03a_red_alrt_800C4E84(int arg0, int arg1, SVECTOR *color, SVECTOR *arg3, int arg4, int arg5)
{
    RedAlrtWork *work;

    work = (RedAlrtWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(RedAlrtWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)d03a_red_alrt_800C45E4, (TActorFunction)d03a_red_alrt_800C48D0, aRedAlrtC);

        if (d03a_red_alrt_800C4BB0(work, arg0, arg1, color, arg3, arg4, arg5) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
