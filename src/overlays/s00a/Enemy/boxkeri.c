#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct BoxKeriWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS field_20_obj;
    SVECTOR        field_44;
    SVECTOR        field_48;
    MATRIX         field_54;
    short          field_74;
    short          field_76;
    short          field_78;
    short          field_7A;
    MATRIX         field_7C_mat[2];
} BoxKeriWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

const char aBoxkeriSnake[] = "スネーク";
const char sBoxkeriDanbowl[] = "段ボール";
const char aCbBox[] = "cb_box";
const char aBoxkeriC[] = "boxkeri.c";

extern CONTROL   *GM_PlayerControl_800AB9F4;
extern SVECTOR    GM_PlayerPosition_800ABA10;
extern int        GM_PlayerMap_800ABA0C;

void BoxKeriAct_800D219C(BoxKeriWork *work)
{
    int field_74;

    field_74 = work->field_74;
    if (field_74 > 40)
    {
        GV_DestroyActor(&work->actor);
        return;
    }
    if (field_74 < 9)
    {
        work->field_7A += 80;
        work->field_78 += 256;
    }
    else if (field_74 < 12)
    {
        work->field_78 -= 128;
    }
    else if (field_74 < 15)
    {
        work->field_78 += 64;
    }
    else if (field_74 < 18)
    {
        work->field_78 -= 32;
    }
    else if (field_74 < 19)
    {
        work->field_78 += 32;
    }
    else if (field_74 & 1)
    {
        DG_InvisibleObjs(work->field_20_obj.objs);
    }
    else
    {
        DG_VisibleObjs(work->field_20_obj.objs);
    }

    switch (work->field_76)
    {
    case 0:
        if (field_74 < 9)
        {
            work->field_7A += 5;
        }
        work->field_48.vz = -work->field_7A;
        work->field_44.vx = -work->field_78;
        break;

    case 1:
        work->field_48.vx = -work->field_7A;
        work->field_44.vz = work->field_78;
        break;

    case 2:
        if (field_74 < 9)
        {
            work->field_7A += 100;
        }
        work->field_48.vz = work->field_7A;
        work->field_44.vx = work->field_78;
        break;

    case 3:
        work->field_48.vx = work->field_7A;
        work->field_44.vz = -work->field_78;
        break;
    }

    GM_CurrentMap = GM_PlayerMap_800ABA0C;

    DG_SetPos(&work->field_54);
    DG_MovePos(&work->field_48);
    DG_RotatePos(&work->field_44);
    DG_PutObjs(work->field_20_obj.objs);
    DG_GetLightMatrix2(&GM_PlayerPosition_800ABA10, work->field_7C_mat);

    work->field_74++;
}

void BoxKeriDie_800D23D0(BoxKeriWork *work)
{
    GM_FreeObject((OBJECT *)&work->field_20_obj);
}

void s00a_boxkeri_800D23F0()
{
    GV_MSG msg;

    msg.address = GV_StrCode(aBoxkeriSnake);
    msg.message[0] = GV_StrCode(sBoxkeriDanbowl);
    msg.message[1] = 1;
    msg.message_len = 2;
    GV_SendMessage(&msg);
}

int s00a_boxkeri_800D2440(SVECTOR *pos, SVECTOR *svec2)
{
    SVECTOR svec;

    GV_SubVec3(svec2, pos, &svec);
    return GV_VecDir2(&svec);
}

int BoxKeriGetResources_800D2474(BoxKeriWork *work, MATRIX *arg1, SVECTOR *arg2)
{
    OBJECT_NO_ROTS *obj;
    int             dir;

    obj = &work->field_20_obj;
    GM_CurrentMap = GM_PlayerMap_800ABA0C;
    GM_InitObjectNoRots(obj, GV_StrCode(aCbBox), 0x6D, 0);
    GM_ConfigObjectLight((OBJECT *)obj, work->field_7C_mat);

    work->field_20_obj.objs->objs[0].raise = 500;

    work->field_44 = DG_ZeroVector;
    work->field_48 = DG_ZeroVector;

    work->field_78 = 0;
    work->field_7A = 0;

    dir = GV_DiffDirU(GM_PlayerControl_800AB9F4->rot.vy,
                               s00a_boxkeri_800D2440(&GM_PlayerPosition_800ABA10, arg2));
    if (dir < 512 || dir >= 3607)
    {
        work->field_76 = 0;
    }
    else
    {
        if (dir >= 1536)
        {
            if (dir >= 2584)
            {
                work->field_76 = 3;
            }
            else
            {
                work->field_76 = 2;
            }
        }
        else
        {
            work->field_76 = 1;
        }
    }

    work->field_54 = *arg1;
    work->field_74 = 0;
    s00a_boxkeri_800D23F0();
    return 0;
}

GV_ACT *NewBoxKeri_800D2600(MATRIX *mat, SVECTOR *svec)
{
    BoxKeriWork *work;

    work = (BoxKeriWork *)GV_NewActor(EXEC_LEVEL, sizeof(BoxKeriWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, BoxKeriAct_800D219C, BoxKeriDie_800D23D0, aBoxkeriC);
        if (BoxKeriGetResources_800D2474(work, mat, svec) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
