#include "red_alrt.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

RedAlrtWork *d03a_dword_800C3270 = NULL;

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_Clock_800AB920;
extern int     GV_PauseLevel_800AB928;
extern int     GM_CurrentMap_800AB9B0;

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

void d03a_red_alrt_800C4414(RedAlrtWork *work)
{
    SVECTOR color;

    if (GV_PauseLevel_800AB928 != 0)
    {
        return;
    }

    work->time++;
    if (work->length >= work->time)
    {
        color.vx = work->f30.vx + ((work->f38.vx - work->f30.vx) * work->time) / work->length;
        color.vy = work->f30.vy + ((work->f38.vy - work->f30.vy) * work->time) / work->length;
        color.vz = work->f30.vz + ((work->f38.vz - work->f30.vz) * work->time) / work->length;
    }
    else
    {
        color.vx = work->f38.vx;
        color.vy = work->f38.vy;
        color.vz = work->f38.vz;
    }

    setRGB0(&work->prims->tile[GV_Clock_800AB920], color.vx, color.vy, color.vz);
}

void d03a_red_alrt_800C45CC(RedAlrtWork *work, int length, short x, short y, short z)
{
    work->length = length;
    work->f38.vx = x;
    work->f38.vy = y;
    work->f38.vz = z;
}

void RedAlertAct_800C45E4(RedAlrtWork *work)
{
    unsigned short hashes[5];
    int            found;
    char          *ot;

    GM_CurrentMap_800AB9B0 = work->map;

    if (work->f6C == 1 && --work->f68 < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
    }

    hashes[0] = GV_StrCode_80016CCC("開く"); // close
    hashes[1] = GV_StrCode_80016CCC("閉める"); // open
    hashes[2] = GV_StrCode_80016CCC("open");
    hashes[3] = GV_StrCode_80016CCC("close");
    hashes[4] = GV_StrCode_80016CCC("kill");

    found = d03a_red_alrt_800C437C(work->name, 5, hashes);

    switch (found)
    {
    case 0:
    case 2:
        work->f5C = 1;
        break;

    case 1:
    case 3:
    case 4:
        work->f5C = 0;
        break;
    }

    if (work->f5C == -1 || work->f5C == 0 || work->f5C == 1)
    {
        ot = DG_ChanlOTag(0);
        addPrim(ot, &work->prims->tile[GV_Clock_800AB920]);
        addPrim(ot, &work->prims->tpage[GV_Clock_800AB920]);

        d03a_red_alrt_800C4414(work);

        if (work->time >= work->length)
        {
            work->time = 0;
            work->f30 = work->f38;

            switch (work->f40)
            {
            case 0:
                if (work->f5C == 0)
                {
                    d03a_red_alrt_800C45CC(work, work->f24, 0, 0, 0);
                }
                else
                {
                    d03a_red_alrt_800C45CC(work, work->f24, work->color1.vx, work->color1.vy, work->color1.vz);
                }
                break;

            case 1:
                if (work->f5C == 0)
                {
                    d03a_red_alrt_800C45CC(work, work->f24, 0, 0, 0);
                }
                else
                {
                    d03a_red_alrt_800C45CC(work, work->f24, work->color2.vx, work->color2.vy, work->color2.vz);
                }
                break;
            }

            work->f40++;

            if (work->f5C == -1)
            {
                work->f5C = -2;
            }

            if (work->f5C == 0)
            {
                work->f5C = -1;
            }

            if (work->f40 > 1)
            {
                work->f40 = 0;
            }
        }
    }

    d03a_dword_800C3270 = work;
}

void RedAlertDie_800C48D0(RedAlrtWork *work)
{
    if (work->prims)
    {
        GV_DelayedFree_80016254(work->prims);
    }

    d03a_dword_800C3270 = NULL;
}

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

int d03a_red_alrt_800C4958(RedAlrtWork *work, int name, int map)
{
    int           opt;
    RedAlrtPrims *prims;

    work->f6C = 0;
    work->name = name;
    work->map = map;

    GM_CurrentMap_800AB9B0 = map;

    opt = GCL_GetOption_80020968('t');
    if (opt != 0)
    {
        work->f60 = GCL_StrToInt_800209E8((char *)opt);
        if (work->f60 < 2)
        {
            work->f60 = 1;
        }
    } else
    {
        work->f60 = 64;
    }

    opt = GCL_GetOption_80020968('c');
    if (opt != 0)
    {
        d03a_red_alrt_800C4904(opt, &work->color1);
    }
    else
    {
        work->color1.vx = 0;
        work->color1.vy = 0;
        work->color1.vz = 0;

        work->color2.vx = 255;
        work->color2.vy = 0;
        work->color2.vz = 0;
    }

    opt = GCL_GetOption_80020968('s');
    if (opt != 0)
    {
        work->f64 = GCL_StrToInt_800209E8((char *)opt) % 3;
    }
    else
    {
        work->f64 = 1;
    }

    if (work->f64 == 2)
    {
        work->color1.vx = 255 - work->color1.vx;
        work->color1.vy = 255 - work->color1.vy;
        work->color1.vz = 255 - work->color1.vz;

        work->color2.vx = 255 - work->color2.vx;
        work->color2.vy = 255 - work->color2.vy;
        work->color2.vz = 255 - work->color2.vz;
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

    prims->tile[0].r0 = 0;
    prims->tile[0].g0 = 0;
    prims->tile[0].b0 = 0;

    prims->tile[1].r0 = 0;
    prims->tile[1].g0 = 0;
    prims->tile[1].b0 = 0;

    work->f30 = DG_ZeroVector_800AB39C;

    work->f38.vx = 0;
    work->f38.vy = 0;
    work->f38.vz = 0;

    work->length = 1;
    work->f40 = 0;
    work->f5C = 0;
    work->f24 = work->f60;

    return 0;
}

int d03a_red_alrt_800C4BB0(RedAlrtWork *work, int name, int length, SVECTOR *color1, SVECTOR *color2, int arg5, int arg6)
{
    RedAlrtPrims *prims;

    work->f6C = 1;
    work->name = name;
    work->f60 = length;
    work->map = GM_CurrentMap_800AB9B0;
    work->f68 = arg6;
    work->color1 = *color1;
    work->color2 = *color2;
    work->f64 = arg5;

    if (arg5 == 2)
    {
        work->color1.vx = 255 - work->color1.vx;
        work->color1.vy = 255 - work->color1.vy;
        work->color1.vz = 255 - work->color1.vz;

        work->color2.vx = 255 - work->color2.vx;
        work->color2.vy = 255 - work->color2.vy;
        work->color2.vz = 255 - work->color2.vz;
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

    prims->tile[0].r0 = work->color1.vx;
    prims->tile[0].g0 = work->color1.vy;
    prims->tile[0].b0 = work->color1.vz;

    prims->tile[1].r0 = work->color1.vx;
    prims->tile[1].g0 = work->color1.vy;
    prims->tile[1].b0 = work->color1.vz;

    work->f30 = work->color1;
    work->f38 = work->color2;
    work->time = 0;
    work->length = length;
    work->f40 = 0;
    work->f24 = work->f60;
    work->f5C = 1;

    return 0;
}

GV_ACT * NewRedAlert_800C4DF0(int name, int where, int argc, char **argv)
{
    RedAlrtWork *work;

    work = (RedAlrtWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(RedAlrtWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)RedAlertAct_800C45E4, (TActorFunction)RedAlertDie_800C48D0, "red_alrt.c");

        if (d03a_red_alrt_800C4958(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT * NewRedAlert2_800C4E84(int name, int length, SVECTOR *color1, SVECTOR *color2, int arg4, int arg5)
{
    RedAlrtWork *work;

    work = (RedAlrtWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(RedAlrtWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)RedAlertAct_800C45E4, (TActorFunction)RedAlertDie_800C48D0, "red_alrt.c");

        if (d03a_red_alrt_800C4BB0(work, name, length, color1, color2, arg4, arg5) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

void RedAlert_800C4F48(void)
{
    if (d03a_dword_800C3270)
    {
        d03a_dword_800C3270->f5C = 0;
    }
}
