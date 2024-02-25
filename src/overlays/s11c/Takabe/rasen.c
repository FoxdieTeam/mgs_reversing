#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/camera.h"

// Actor created by NewRasen_800CBA7C
typedef struct _RasenWork
{
    GV_ACT actor;
} RasenWork;

typedef struct _Rasen2Item
{
    DG_OBJS   *objs;
    DG_DEF    *def;
    LitHeader *lit;
} Rasen2Item;

// Actor created by NewRasen2_800CB008
typedef struct _Rasen2Work
{
    GV_ACT         actor;
    int            field_20;
    int            field_24;
    int            field_28;
    int            field_2C;    // count of used items in field_B0, field_30
    unsigned short field_30[2]; // unknown how large
    char           pad_34[0x7C];
    Rasen2Item     field_B0[1]; // unknown how large
    char           pad_BC[0xB4];
    DG_OBJS       *field_170[3][16];
    int            field_230;
    int            field_234;
    GV_ACT        *field_238;
} Rasen2Work;

#define EXEC_LEVEL 1

int rasen_800C3404 = 0;
int rasen_800C3408 = 0;
int rasen_800C340C = 0;

int s11c_dword_800C3410 = 0x00000000;
int s11c_dword_800C3414 = 0x00000000;

SVECTOR rasen_800C3418 = {35536, 35536, 35536};
SVECTOR rasen_800C3420 = {30000, 30000, 30000};

int SECTION("overlay.bss") s11c_dword_800D2C74;
int SECTION("overlay.bss") s11c_dword_800D2C78;
int SECTION("overlay.bss") s11c_dword_800D2C7C;
int SECTION("overlay.bss") s11c_dword_800D2C80;

typedef struct RasenUnk_800D2C84
{
    SVECTOR field_0;
    SVECTOR field_8;
    int     field_10;
    int     field_14;
    int     field_18;
    int     field_1C;
} RasenUnk_800D2C84;

RasenUnk_800D2C84 SECTION("overlay.bss") rasen_800D2C84;

unsigned short SECTION("overlay.bss")
    rasen_el_800D2CA4[4]; // TODO: rename to rasen_* ? or move to rasen_el? - everything will come clear in s11a where
                          // there's only rasen.c, no rasen_el.c

void Takabe_FreeObjs_800DC820(DG_OBJS *objs);
void Takabe_RefreshObjectPacks_800DC854(DG_OBJS *objs);
void Takabe_ReshadeModel_800DC854(DG_OBJS *objs, LitHeader *lit);
void s00a_unknown3_800DC918();

extern GM_Camera GM_Camera_800B77E8;
extern MATRIX    DG_ZeroMatrix_8009D430;
extern CONTROL  *GM_WhereList_800B56D0[96];
extern int       gControlCount_800AB9B4;

#pragma INCLUDE_ASM("asm/overlays/s11c/s11c_rasen_800CA3A4.s")

void Rasen2SearchWhereList_800CA568(Rasen2Work *work, MAP *toFind, MAP *map)
{
    CONTROL **control;
    int       count;

    control = GM_WhereList_800B56D0;
    if (rasen_800C3408 == 1)
    {
        for (count = gControlCount_800AB9B4; count > 0; count--, control++)
        {
            if ((*control)->field_30_scriptData > 0 && (*control)->field_30_scriptData < 64 &&
                (*control)->field_0_mov.vy > 0 && (*control)->field_2C_map == toFind)
            {
                (*control)->field_0_mov.vy -= 32000;
                (*control)->field_2C_map = map;
            }
        }
    }
    else if (rasen_800C3408 == 2)
    {
        for (count = gControlCount_800AB9B4; count > 0; count--, control++)
        {
            if ((*control)->field_30_scriptData > 0 && (*control)->field_30_scriptData < 64 &&
                (*control)->field_0_mov.vy < 0 && (*control)->field_2C_map == toFind)
            {
                (*control)->field_0_mov.vy += 32000;
                (*control)->field_2C_map = map;
            }
        }
    }
}

void Rasen2UpdateChnlQueue_800CA678(Rasen2Work *work, int bitmask1, int bitmask2)
{
    DG_PRIM **primIter;
    DG_PRIM  *curPrim;
    int       count;
    DG_CHNL  *chnl;

    chnl = DG_Chanl(0);

    primIter = (DG_PRIM **)&chnl->mQueue[chnl->mFreePrimCount]; // per comment in DG_CHNL: "queue can contain DG_PRIM as
                                                                // well, probably void*"
    if (rasen_800C3408 == 1)
    {
        for (count = chnl->mTotalQueueSize - chnl->mFreePrimCount; count > 0; count--)
        {
            curPrim = *primIter;
            primIter++;
            if (curPrim->world.t[1] >= 0)
            {
                if (curPrim->group_id & bitmask1)
                {
                    curPrim->world.t[1] -= 32000;
                    curPrim->group_id = (curPrim->group_id | bitmask2) & ~bitmask1;
                }
                else if (curPrim->group_id == 0)
                {
                    curPrim->world.t[1] -= 32000;
                }
            }
        }
    }
    else if (rasen_800C3408 == 2)
    {
        for (count = chnl->mTotalQueueSize - chnl->mFreePrimCount; count > 0; count--)
        {
            curPrim = *primIter;
            primIter++;
            if (curPrim->world.t[1] <= 0)
            {
                if (curPrim->group_id & bitmask1)
                {
                    curPrim->world.t[1] += 32000;
                    curPrim->group_id = (curPrim->group_id | bitmask2) & ~bitmask1;
                }
                else if (curPrim->group_id == 0)
                {
                    curPrim->world.t[1] += 32000;
                }
            }
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11c/s11c_rasen_800CA79C.s")
void s11c_rasen_800CA79C(Rasen2Work *);

void RasenFreeObjs_800CB31C(DG_OBJS *objs);

void Rasen2Die_800CAB74(Rasen2Work *work)
{
    int i, j;

    GM_Camera_800B77E8.field_18_flags &= ~2;
    GM_SetCameraCallbackFunc_8002FD84(1, NULL);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 16; j++)
        {
            RasenFreeObjs_800CB31C(work->field_170[i][j]);
        }
    }
    for (i = work->field_2C - 1; i >= 0; i--)
    {
        Takabe_FreeObjs_800DC820(work->field_B0[i].objs);
    }
    s00a_unknown3_800DC918();
    if (work->field_238 != NULL)
    {
        GV_DestroyActor_800151C8(work->field_238);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11c/s11c_rasen_800CAC64.s")
int s11c_rasen_800CAC64(Rasen2Work *, int, int);

GV_ACT *NewRasen2_800CB008(int arg0, int arg1)
{
    Rasen2Work *work;

    work = (Rasen2Work *)GV_NewActor_800150E4(5, sizeof(Rasen2Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s11c_rasen_800CA79C, (TActorFunction)Rasen2Die_800CAB74,
                                  "rasen.c");
        if (s11c_rasen_800CAC64(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        work->field_230 = 0;
        work->field_234 = 0;
    }
    return &work->actor;
}

void Rasen2_800CB0A4(Rasen2Work *work)
{
    int i, j;

    for (j = 0; j < work->field_2C; j++)
    {
        Takabe_ReshadeModel_800DC854(work->field_B0[j].objs, work->field_B0[j].lit);
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 16; j++)
        {
            Takabe_RefreshObjectPacks_800DC854(work->field_170[i][j]);
        }
    }
}

void Rasen2_800CB150(Rasen2Work *work)
{
    DG_DEF     *def;
    DG_OBJS    *objs;
    LitHeader  *lit;
    Rasen2Item *item;
    int         i;

    item = work->field_B0;
    for (i = 0; i < work->field_2C; item++, i++)
    {
        item->def = def = GV_GetCache_8001538C(GV_CacheID_800152DC(work->field_30[i], 'k'));
        item->lit = lit = GV_GetCache_8001538C(GV_CacheID_800152DC(work->field_30[i], 'l'));
        item->objs = objs = DG_MakeObjs_80031760(def, 0x57, 0);
        if (lit != NULL)
        {
            DG_MakePreshade_80031F04(objs, lit->lights, lit->field_0_num_lights);
        }
        else
        {
            DG_MakePreshade_80031F04(objs, NULL, NULL);
        }
        DG_InvisibleObjs(item->objs);
    }
}

DG_OBJS *Rasen2_800CB250(int index, Rasen2Work *work)
{
    DG_OBJS    *new_objs;
    DG_OBJ     *curObj1, *curObj2;
    DG_OBJ     *objIter1, *objIter2;
    Rasen2Item *item;
    int         i;

    item = &work->field_B0[index];
    new_objs = DG_MakeObjs_80031760(item->def, 0x57, 0);
    objIter1 = new_objs->objs;
    objIter2 = item->objs->objs;
    for (i = new_objs->n_models; i > 0; i--)
    {
        curObj2 = objIter2++;
        curObj1 = objIter1++;
        while (curObj1 != NULL)
        {
            curObj1->rgbs = curObj2->rgbs;
            curObj1 = curObj1->extend;
            curObj2 = curObj2->extend;
        }
    }
    DG_SetPos_8001BC44(&DG_ZeroMatrix_8009D430);
    DG_PutObjs_8001BDB8(new_objs);
    DG_QueueObjs_80018178(new_objs);
    DG_GroupObjs(new_objs, GM_CurrentMap_800AB9B0);
    return new_objs;
}

// ===================================
// Rasen2 ends here, Rasen starts here
// ===================================

void RasenFreeObjs_800CB31C(DG_OBJS *objs)
{
    DG_DequeueObjs_800181E4(objs);
    objs->objs[0].rgbs = NULL;
    DG_FreeObjs_800318D0(objs);
}

void Rasen_800CB34C()
{
    SVECTOR svec;

    if (rasen_800C340C == 2)
    {
        GM_Camera_800B77E8.field_0 = rasen_800D2C84.field_0;
        GM_Camera_800B77E8.field_8 = rasen_800D2C84.field_8;
        GM_Camera_800B77E8.field_28 = 0;
        GV_SubVec3_80016D40(&GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_0, &svec);
        GV_OriginPadSystem_80016C78(GV_VecDir2_80016EF8(&svec) + 2048);
        GCL_Command_camera_helper_80030888(&rasen_800C3418, &rasen_800C3420, 0);
        GCL_Command_camera_helper2_800308E0(&rasen_800C3418, &rasen_800C3420, 0);
        GM_Camera_800B77E8.field_10.vy = rasen_800D2C84.field_18;
    }
    else if (rasen_800C340C == 1)
    {
        GM_Camera_800B77E8.field_0 = rasen_800D2C84.field_0;
        GM_Camera_800B77E8.field_8 = rasen_800D2C84.field_8;
        GM_Camera_800B77E8.field_28 = 0;
        GV_OriginPadSystem_80016C78(rasen_800D2C84.field_18 + 2048);
        GM_Camera_800B77E8.field_10.vy = rasen_800D2C84.field_18;
    }
    else
    {
        GM_Camera_800B77E8.field_0 = rasen_800D2C84.field_0;
        GM_Camera_800B77E8.field_8 = rasen_800D2C84.field_8;
        GM_Camera_800B77E8.field_28 = 0;
        GV_OriginPadSystem_80016C78(0);
        GM_Camera_800B77E8.field_10.vy = 2048;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11c/s11c_rasen_800CB530.s")
void s11c_rasen_800CB530(RasenWork *work);

void RasenAct_800CBA54(RasenWork *work)
{
    s11c_rasen_800CB530(work);
}

void RasenDie_800CBA74(RasenWork *work)
{
}

GV_ACT *NewRasen_800CBA7C(void)
{
    RasenWork *work;

    work = (RasenWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(RasenWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)RasenAct_800CBA54, (TActorFunction)RasenDie_800CBA74,
                                  "rasen.c");
    }

    GV_ZeroMemory_8001619C(&rasen_800D2C84, sizeof(rasen_800D2C84));
    return &work->actor;
}
