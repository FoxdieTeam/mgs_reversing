#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct FadeIoPrims
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} FadeIoPrims;

typedef struct FadeIoWork
{
    GV_ACT       actor;
    int          field_20;
    FadeIoPrims *field_24_prims;
    int          field_28_where;
    int          field_2c;
    int          field_30;
    int          field_34_name;
    int          field_38;
} FadeIoWork;

extern int GV_Clock_800AB920;
extern int GV_PassageTime_800AB924;
extern int GV_PauseLevel_800AB928;
extern int GM_GameStatus_800AB3CC;

unsigned short s16b_dword_800C3250[] = {HASH_KILL, 0x71F1};

static int s16b_dword_800C58AC[2];

int s16b_800C43A4(char param);
int s16b_800C44DC(unsigned short name, int hash_count, unsigned short *hashes);

#define EXEC_LEVEL 3

void FadeIoAct_800C3E7C(FadeIoWork *work)
{
    int   status;
    char *ot;
    int   shade;

    if (GV_PauseLevel_800AB928 == 0)
    {
        status = s16b_800C44DC(work->field_20, 2, s16b_dword_800C3250);
        if (status == 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return;
        }

        if (status == 1)
        {
            work->field_2c = 0;
            work->field_34_name |= 0x1;
        }
    }

    ot = DG_ChanlOTag(1);
    addPrim(ot, &work->field_24_prims->tile[GV_Clock_800AB920]);
    addPrim(ot, &work->field_24_prims->tpage[GV_Clock_800AB920]);

    if (work->field_2c > work->field_28_where)
    {
        work->field_2c = work->field_28_where;
    }

    shade = (work->field_2c * 255) / work->field_28_where;
    if (work->field_34_name & 0x1)
    {
        shade = 255 - shade;
    }

    if (GV_PauseLevel_800AB928 == 0)
    {
        if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_32))
        {
            work->field_2c++;
        }
        else
        {
            work->field_38 += GV_PassageTime_800AB924;
            work->field_2c += work->field_38 >> 1;
            work->field_38 &= 0x1;
        }
    }

    work->field_30 = shade;
    setRGB0(&work->field_24_prims->tile[GV_Clock_800AB920], shade, shade, shade);

    if ((work->field_34_name & 0x1) && (work->field_2c >= work->field_28_where))
    {
        GV_DestroyActor_800151C8(&work->actor);
    }
}

void FadeIoDie_800C40D0(FadeIoWork *work)
{
    if (work->field_24_prims)
    {
        GV_DelayedFree_80016254(work->field_24_prims);
    }
}

int FadeIoGetResources_800C4100(FadeIoWork *work, int name, int where)
{
    FadeIoPrims *prims;

    prims = GV_Malloc_8001620C(sizeof(FadeIoPrims));
    work->field_24_prims = prims;
    if (prims == NULL)
    {
        return -1;
    }
    if (name & 2)
    {
        setDrawTPage(&prims->tpage[0], 0, 1, getTPage(0, 1, 0, 0));
        setDrawTPage(&prims->tpage[1], 0, 1, getTPage(0, 1, 0, 0));
    }
    else
    {
        setDrawTPage(&prims->tpage[0], 0, 1, getTPage(0, 2, 0, 0));
        setDrawTPage(&prims->tpage[1], 0, 1, getTPage(0, 2, 0, 0));
    }
    setTile(&prims->tile[0]);
    setSemiTrans(&prims->tile[0], 1);

    prims->tile[0].w = 0x140;
    prims->tile[0].h = 0xE0;
    prims->tile[0].x0 = 0;
    prims->tile[0].y0 = 0;
    prims->tile[1] = prims->tile[0];
    if (!(name & 1))
    {
        prims->tile[0].r0 = 0;
        prims->tile[0].g0 = 0;
        prims->tile[0].b0 = 0;
        prims->tile[1].r0 = 0;
        prims->tile[1].g0 = 0;
        prims->tile[1].b0 = 0;
        work->field_30 = 0;
    }
    else
    {
        prims->tile[0].r0 = 0xFF;
        prims->tile[0].g0 = 0xFF;
        prims->tile[0].b0 = 0xFF;
        prims->tile[1].r0 = 0xFF;
        prims->tile[1].g0 = 0xFF;
        prims->tile[1].b0 = 0xFF;
        work->field_30 = 0xFF;
    }
    work->field_34_name = name;
    work->field_28_where = where;
    work->field_2c = 1;
    return 0;
}

GV_ACT *NewFadeIo_800C4224(int name, int where, int argc, char **argv)
{
    FadeIoWork *work;

    work = (FadeIoWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(FadeIoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)FadeIoAct_800C3E7C, (TActorFunction)FadeIoDie_800C40D0,
                                  "fadeio.c");
        if (FadeIoGetResources_800C4100(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->field_20 = 0x62FE;
    }
    return &work->actor;
}

GV_ACT *NewFadeIo_800C42BC(int name, int where, int argc, char **argv)
{
    FadeIoWork *work;

    work = (FadeIoWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(FadeIoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)FadeIoAct_800C3E7C, (TActorFunction)FadeIoDie_800C40D0, "fadeio.c");

        if (FadeIoGetResources_800C4100(work, s16b_800C43A4('m'), s16b_800C43A4('s')) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->field_20 = name;
    }

    return &work->actor;
}

int s16b_800C4364(char param, int def)
{
    if (GCL_GetParam_80020968(param))
    {
        return GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    return def;
}

int s16b_800C43A4(char param)
{
    return s16b_800C4364(param, 0);
}

unsigned short s16b_800C43C8(char param, unsigned short def)
{
    char *param2;

    param2 = (char *)GCL_GetParam_80020968(param);
    if (param2)
    {
        return GCL_GetNextInt_800209E8(param2);
    }

    return def;
}

int s16b_800C440C(char param)
{
    return s16b_800C43C8(param, 0);
}

void s16b_800C4430(char param, short x, short y, short z, SVECTOR *vec)
{
    if (GCL_GetParam_80020968(param))
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), vec);
        return;
    }

    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

void s16b_800C44AC(char param, SVECTOR *vec)
{
    s16b_800C4430(param, 0, 0, 0, vec);
}

int s16b_800C44DC(unsigned short name, int hash_count, unsigned short *hashes)
{
    GV_MSG *msg;
    int     msg_count;
    int     found;
    int     hash;
    int     i;

    msg_count = GV_ReceiveMessage_80016620(name, &msg);
    found = -1;

    for (; msg_count > 0; msg_count--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < hash_count; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
                s16b_dword_800C58AC[0] = msg->message[1];
            }
        }
    }

    return found;
}

int s16b_800C4584(void)
{
    return s16b_dword_800C58AC[0];
}

void s16b_800C4594(short address, short message)
{
    GV_MSG msg;

    msg.address = address;
    msg._len = 1;
    msg.message[0] = message;
    GV_SendMessage_80016504(&msg);
}

void s16b_800C45C4(HZD_SEG *seg, MATRIX *trans, SVECTOR *arg2, SVECTOR *arg3)
{
    SVECTOR sp10;
    SVECTOR sp18;
    int     height;
    int     y;

    if (trans)
    {
        DG_SetPos_8001BC44(trans);
        DG_PutVector_8001BE48(arg2, &sp10, 1);
        DG_PutVector_8001BE48(arg3, &sp18, 1);
    }
    else
    {
        sp10 = *arg2;
        sp18 = *arg3;
    }

    height = sp10.vy - sp18.vy;
    y = sp18.vy;

    if (height <= 0)
    {
        y = sp10.vy;
        height = -height;
    }

    seg->p1.x = sp10.vx;
    seg->p1.z = sp10.vz;
    seg->p2.x = sp18.vx;
    seg->p2.z = sp18.vz;
    seg->p2.y = y;
    seg->p1.y = y;
    seg->p2.h = height;
    seg->p1.h = height;

    HZD_SetDynamicSegment_8006FEE4(seg, seg);
}

void s16b_800C46D8(HZD_FLR *flr, SVECTOR *arg1, SVECTOR *arg2)
{
    short y;

    flr->p1.x = arg1->vx - arg2->vx;
    flr->p1.z = arg1->vz - arg2->vz;

    flr->p2.x = arg1->vx + arg2->vx;
    flr->p2.z = arg1->vz - arg2->vz;

    flr->p4.x = arg1->vx - arg2->vx;
    flr->p4.z = arg1->vz + arg2->vz;

    flr->p3.x = arg1->vx + arg2->vx;
    flr->p3.z = arg1->vz + arg2->vz;

    y = arg1->vy + arg2->vy;

    flr->p1.h = 0;
    flr->p2.h = 0;
    flr->p3.h = 0xFF;

    flr->p4.y = y;
    flr->p3.y = y;
    flr->p2.y = y;
    flr->p1.y = y;

    flr->b1.x = arg1->vx - arg2->vx;
    flr->b1.z = arg1->vz - arg2->vz;
    flr->b1.y = arg1->vy - arg2->vy;

    flr->b2.x = arg1->vx + arg2->vx;
    flr->b2.z = arg1->vz + arg2->vz;
    flr->b2.y = arg1->vy + arg2->vy;
}
