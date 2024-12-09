#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Bullet/bakudan.h"
#include "Bullet/jirai.h"
#include "Game/camera.h"
#include "Game/hittable.h"
#include "Game/linkvarbuf.h"

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
    char           pad_34[0x1C];
    unsigned short field_50[3][16];
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

Rasen2Work *SECTION("overlay.bss") s11c_dword_800D2C74;
int         SECTION("overlay.bss") s11c_dword_800D2C78;
int         SECTION("overlay.bss") s11c_dword_800D2C7C;
int         SECTION("overlay.bss") s11c_dword_800D2C80;

typedef struct RasenUnk_800D2C84
{
    SVECTOR field_0;
    SVECTOR field_8;
    SVECTOR field_10;
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

extern GM_Camera       GM_Camera_800B77E8;
extern MATRIX          DG_ZeroMatrix;
extern CONTROL        *GM_WhereList_800B56D0[96];
extern int             gControlCount_800AB9B4;
extern int             bakudan_count_8009F42C;
extern HITTABLE        c4_actors_800BDD78[C4_COUNT];
extern HITTABLE   stru_800BDE78[8];
extern int             counter_8009F448;
extern CONTROL        *GM_PlayerControl_800AB9F4;
extern int             DG_CurrentGroupID_800AB968;
extern int             GM_PlayerMap_800ABA0C;
extern int             GM_PlayerStatus_800ABA50;
extern SVECTOR         DG_ZeroVector;
extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern int             GV_PauseLevel_800AB928;
extern SVECTOR         GM_PlayerPosition_800ABA10;

void Rasen2IterBakudanJirai_800CA3A4(Rasen2Work *work, MAP *oldMap, MAP *newMap)
{
    BakudanWork *bakudan;
    JiraiWork   *jirai;
    HITTABLE    *pItem;
    TARGET      *target;
    int          i;
    int          yoff;
    int          bitmask;

    if (rasen_800C3408 == 1)
    {
        yoff = -32000;
        bitmask = 0;
    }
    else
    {
        yoff = 32000;
        bitmask = 0x8000;
    }

    if (bakudan_count_8009F42C != 0)
    {
        for (pItem = c4_actors_800BDD78, i = C4_COUNT; i > 0; pItem++, i--)
        {
            bakudan = (BakudanWork *)pItem->actor;
            if (bakudan != NULL && bakudan->control.map == oldMap && bakudan->transform == NULL)
            {
                if ((bakudan->control.mov.vy ^ bitmask) & 0x8000)
                {
                    GV_DestroyOtherActor(&bakudan->actor);
                }
                else
                {
                    bakudan->control.map = newMap;
                    bakudan->control.mov.vy += yoff;
                    bakudan->map_index = newMap->index;
                }
            }
        }
    }

    if (counter_8009F448 != 0)
    {
        for (pItem = stru_800BDE78, i = 8; i > 0; pItem++, i--)
        {
            jirai = (JiraiWork *)pItem->actor;
            if (jirai != NULL && jirai->control.map == oldMap)
            {
                if ((jirai->control.mov.vy ^ bitmask) & 0x8000)
                {
                    GV_DestroyOtherActor(&jirai->actor);
                }
                else
                {
                    target = jirai->target;
                    jirai->control.map = newMap;
                    jirai->control.mov.vy += yoff;
                    jirai->map = newMap->index;
                    if (target != NULL)
                    {
                        target->center.vy += yoff;
                        jirai->target->map = newMap->index;
                    }
                }
            }
        }
    }
}

void Rasen2SearchWhereList_800CA568(Rasen2Work *work, MAP *toFind, MAP *map)
{
    CONTROL **control;
    int       count;

    control = GM_WhereList_800B56D0;
    if (rasen_800C3408 == 1)
    {
        for (count = gControlCount_800AB9B4; count > 0; count--, control++)
        {
            if ((*control)->name > 0 && (*control)->name < 64 &&
                (*control)->mov.vy > 0 && (*control)->map == toFind)
            {
                (*control)->mov.vy -= 32000;
                (*control)->map = map;
            }
        }
    }
    else if (rasen_800C3408 == 2)
    {
        for (count = gControlCount_800AB9B4; count > 0; count--, control++)
        {
            if ((*control)->name > 0 && (*control)->name < 64 &&
                (*control)->mov.vy < 0 && (*control)->map == toFind)
            {
                (*control)->mov.vy += 32000;
                (*control)->map = map;
            }
        }
    }
}

void Rasen2UpdateChnlQueue_800CA678(Rasen2Work *work, int bitmask1, int bitmask2)
{
    DG_PRIM **primIter;
    DG_PRIM  *curPrim;
    int       count;
    DG_CHANL *chanl;

    chanl = DG_Chanl(0);

    primIter = (DG_PRIM **)&chanl->mQueue[chanl->mFreePrimCount];
    // per comment in DG_CHANL: "queue can contain DG_PRIM as
    // well, probably void*"

    if (rasen_800C3408 == 1)
    {
        for (count = chanl->mTotalQueueSize - chanl->mFreePrimCount; count > 0; count--)
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
        for (count = chanl->mTotalQueueSize - chanl->mFreePrimCount; count > 0; count--)
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

void Rasen2_800CB0A4(Rasen2Work *work);

void Rasen2Act_800CA79C(Rasen2Work *work)
{
    GV_MSG *msgs;
    int     msgs_count;
    int     msg_arg2;

    MAP *old_map;
    MAP *new_map;

    int mapid;
    int playermap;

    int i, j, j2;

    int          vy;
    unsigned int vy2;

    if (work->field_230 == 0)
    {
        work->field_230 = 1;
        Rasen2_800CB0A4(work);
    }

    for (msgs_count = GV_ReceiveMessage(work->field_24, &msgs); msgs_count > 0; msgs_count--, msgs++)
    {
        if (msgs->message[0] == 0x4548)
        {
            msg_arg2 = msgs->message[1];
            if (msg_arg2 == -1)
            {
                GM_Camera_800B77E8.flags &= ~2;
            }
            else
            {
                rasen_800C340C = msg_arg2;
                GM_Camera_800B77E8.flags |= 2;
            }
        }
        else if (msgs->message[0] == 0x72D2)
        {
            rasen_800D2C84.field_10.vx = msgs->message[1];
            rasen_800D2C84.field_10.vy = msgs->message[2] + s11c_dword_800C3414;
            rasen_800D2C84.field_10.vz = msgs->message[3];
            if (rasen_800C3408 == 1)
            {
                rasen_800D2C84.field_10.vy -= 32000;
            }
            else if (rasen_800C3408 == 2)
            {
                rasen_800D2C84.field_10.vy += 32000;
            }
        }
    }

    if (rasen_800C3408 != 0)
    {
        mapid = rasen_el_800D2CA4[rasen_800C3404];
        old_map = GM_PlayerControl_800AB9F4->map;
        new_map = Map_FromId_800314C0(mapid);

        DG_CurrentGroupID_800AB968 = mapid;
        playermap = GM_PlayerMap_800ABA0C;
        GM_CurrentMap_800AB9B0 = mapid;
        GM_PlayerMap_800ABA0C = mapid;
        GM_PlayerControl_800AB9F4->map->used = 0;
        GM_PlayerControl_800AB9F4->map = new_map;
        new_map->used = 1;

        DG_ResetFixedLight();
        DG_SetFixedLight(GM_PlayerControl_800AB9F4->map->lit->lights,
                         GM_PlayerControl_800AB9F4->map->lit->n_lights);

        Rasen2IterBakudanJirai_800CA3A4(work, old_map, new_map);
        Rasen2SearchWhereList_800CA568(work, old_map, new_map);
        Rasen2UpdateChnlQueue_800CA678(work, playermap, mapid);
    }

    vy = GM_PlayerControl_800AB9F4->mov.vy;
    if (vy >= 0)
    {
        vy /= 4000;
    }
    else
    {
        vy = vy / 4000 - 1;
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 16; j++)
        {
            DG_InvisibleObjs(work->field_170[i][j]);
        }
    }

    if ((GM_PlayerStatus_800ABA50 & PLAYER_FIRST_PERSON) && !(GM_Camera_800B77E8.flags & 0x100))
    {
        if (GM_PlayerMap_800ABA0C & work->field_28)
        {
            for (i = 0; i < 8; i++)
            {
                vy2 = vy + 4 + i;
                j2 = vy2 % 16;
                if (vy2 < 16)
                {
                    DG_VisibleObjs(work->field_170[rasen_800C3404][j2]);
                }
            }
        }
    }
    else if (GM_PlayerMap_800ABA0C & work->field_28)
    {
        for (i = 0; i < 8; i++)
        {
            vy2 = vy + 4 + i;
            j2 = vy2 % 16;
            if (vy2 < 16)
            {
                DG_VisibleObjs(work->field_170[rasen_800C3404][j2]);
            }
        }
    }
}

void RasenFreeObjs_800CB31C(DG_OBJS *objs);

void Rasen2Die_800CAB74(Rasen2Work *work)
{
    int i, j;

    GM_Camera_800B77E8.flags &= ~2;
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
        GV_DestroyActor(work->field_238);
    }
}

void     Rasen_800CB34C();
void     Rasen2_800CB150(Rasen2Work *work);
DG_OBJS *Rasen2_800CB250(int index, Rasen2Work *work);
GV_ACT  *NewRasen_800CBA7C(void);

int Rasen2GetResources_800CAC64(Rasen2Work *work, int name, int where)
{
    DG_OBJS       *objs;
    int            map;
    int            i;
    int            j;
    unsigned short map_index_bit;
    unsigned char *param;

    map = where;
    if (!GCL_GetOption('n'))
    {
        return -1;
    }

    map_index_bit =
        Map_FindByNum_80031504(GCL_StrToInt(GCL_GetParamResult()))->index;
    rasen_el_800D2CA4[0] = map_index_bit;
    work->field_28 |= map_index_bit;

    map_index_bit =
        Map_FindByNum_80031504(GCL_StrToInt(GCL_GetParamResult()))->index;
    rasen_el_800D2CA4[1] = map_index_bit;
    work->field_28 |= map_index_bit;

    map_index_bit =
        Map_FindByNum_80031504(GCL_StrToInt(GCL_GetParamResult()))->index;
    rasen_el_800D2CA4[2] = map_index_bit;
    work->field_28 |= map_index_bit;

    if (GCL_GetOption('m'))
    {
        map = Map_FindByNum_80031504(GCL_StrToInt(GCL_GetParamResult()))->index;
    }

    GM_CurrentMap_800AB9B0 = map;
    work->field_20 = map;
    work->field_24 = name;

    for (i = 0; i < 3; i++)
    {
        if (map == rasen_el_800D2CA4[i])
        {
            rasen_800C3404 = i;
        }
    }

    if (GCL_GetOption('o'))
    {
        work->field_2C = 0;
        for (i = 0; i < 16; i++)
        {
            param = GCL_GetParamResult();
            if (param != NULL)
            {
                work->field_30[i] = GCL_StrToInt(param);
                work->field_2C++;
            }
        }
    }

    if (GCL_GetOption('l'))
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 16; j++)
            {
                work->field_50[i][j] = GCL_StrToInt(GCL_GetParamResult());
            }
        }
    }
    Rasen2_800CB150(work);

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 16; j++)
        {
            work->field_170[i][j] = objs = Rasen2_800CB250(work->field_50[i][j], work);

            objs->world = DG_ZeroMatrix;
            objs->world.t[1] = 4000 * j - 32250;
            objs->group_id = rasen_el_800D2CA4[i];
        }
    }

    if (GCL_GetOption('c'))
    {
        rasen_800C340C = GCL_StrToInt(GCL_GetParamResult());
    }

    GM_SetCameraCallbackFunc_8002FD84(1, Rasen_800CB34C);

    GM_Camera_800B77E8.flags |= 2;

    if (work->field_2C > 10)
    {
        s11c_dword_800C3410 = 2250;
    }
    else
    {
        s11c_dword_800C3410 = 0;
    }

    s11c_dword_800D2C74 = work;

    work->field_238 = NewRasen_800CBA7C();

    rasen_800D2C84.field_0 = GM_Camera_800B77E8.eye;
    rasen_800D2C84.field_8 = GM_Camera_800B77E8.center;

    return 0;
}

GV_ACT *NewRasen2_800CB008(int name, int where)
{
    Rasen2Work *work;

    work = (Rasen2Work *)GV_NewActor(5, sizeof(Rasen2Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)Rasen2Act_800CA79C,
                         (GV_ACTFUNC)Rasen2Die_800CAB74, "rasen.c");
        if (Rasen2GetResources_800CAC64(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
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
        item->def = def = GV_GetCache(GV_CacheID(work->field_30[i], 'k'));
        item->lit = lit = GV_GetCache(GV_CacheID(work->field_30[i], 'l'));
        item->objs = objs = DG_MakeObjs(def, 0x57, 0);
        if (lit != NULL)
        {
            DG_MakePreshade(objs, lit->lights, lit->n_lights);
        }
        else
        {
            DG_MakePreshade(objs, NULL, NULL);
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
    new_objs = DG_MakeObjs(item->def, 0x57, 0);
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
    DG_SetPos(&DG_ZeroMatrix);
    DG_PutObjs(new_objs);
    DG_QueueObjs(new_objs);
    DG_GroupObjs(new_objs, GM_CurrentMap_800AB9B0);
    return new_objs;
}

// ===================================
// Rasen2 ends here, Rasen starts here
// ===================================

void RasenFreeObjs_800CB31C(DG_OBJS *objs)
{
    DG_DequeueObjs(objs);
    objs->objs[0].rgbs = NULL;
    DG_FreeObjs(objs);
}

void Rasen_800CB34C()
{
    SVECTOR svec;

    if (rasen_800C340C == 2)
    {
        GM_Camera_800B77E8.eye = rasen_800D2C84.field_0;
        GM_Camera_800B77E8.center = rasen_800D2C84.field_8;
        GM_Camera_800B77E8.field_28 = 0;
        GV_SubVec3(&GM_Camera_800B77E8.center, &GM_Camera_800B77E8.eye, &svec);
        GV_OriginPadSystem(GV_VecDir2(&svec) + 2048);
        GM_CameraSetBounds_80030888(&rasen_800C3418, &rasen_800C3420, 0);
        GM_CameraSetLimits_800308E0(&rasen_800C3418, &rasen_800C3420, 0);
        GM_Camera_800B77E8.rotate.vy = rasen_800D2C84.field_18;
    }
    else if (rasen_800C340C == 1)
    {
        GM_Camera_800B77E8.eye = rasen_800D2C84.field_0;
        GM_Camera_800B77E8.center = rasen_800D2C84.field_8;
        GM_Camera_800B77E8.field_28 = 0;
        GV_OriginPadSystem(rasen_800D2C84.field_18 + 2048);
        GM_Camera_800B77E8.rotate.vy = rasen_800D2C84.field_18;
    }
    else
    {
        GM_Camera_800B77E8.eye = rasen_800D2C84.field_0;
        GM_Camera_800B77E8.center = rasen_800D2C84.field_8;
        GM_Camera_800B77E8.field_28 = 0;
        GV_OriginPadSystem(0);
        GM_Camera_800B77E8.rotate.vy = 2048;
    }
}

void RasenAct_800CB530(RasenWork *work)
{
    SVECTOR svec1;
    SVECTOR svec2;
    SVECTOR svec3;
    SVECTOR svec4;
    SVECTOR svec5;
    int     levels[2];

    SVECTOR *field_10;

    int level;

    svec1 = DG_ZeroVector;
    do
    {
    } while (0);

    if (rasen_800D2C84.field_1C != 0)
    {
        if (gUnkCameraStruct_800B77B8.eye.vy - GM_PlayerControl_800AB9F4->mov.vy >= 0)
        {
            if (gUnkCameraStruct_800B77B8.eye.vy - GM_PlayerControl_800AB9F4->mov.vy > 20000)
            {
                goto add_vec; // FIXME: match without goto
            }
        }
        else
        {
            if (GM_PlayerControl_800AB9F4->mov.vy - gUnkCameraStruct_800B77B8.eye.vy > 20000)
            {
            add_vec:
                GV_AddVec3(&gUnkCameraStruct_800B77B8.eye, &GM_Camera_800B77E8.pan,
                           &gUnkCameraStruct_800B77B8.eye);
            }
        }
    }

    rasen_800D2C84.field_1C = 0;
    if (GV_PauseLevel_800AB928)
    {
        return;
    }
    rasen_800C3408 = 0;

    if (GM_WhereList_800B56D0[0]->name)
    {
        if (GM_UnkFlagBE || GM_Camera_800B77E8.first_person == 0 || (GM_Camera_800B77E8.flags & 0x200))
        {
            level = GM_PlayerControl_800AB9F4->levels[0] + 1100;

            if (level >= 16000 - s11c_dword_800C3410 && rasen_800C3404 < 2)
            {
                svec1.vy = -32000;
                sub_8003049C(&svec1);
                GM_Camera_800B77E8.pan.pad = 0;
                rasen_800D2C84.field_1C = 1;
                rasen_800C3408 = 1;
                GM_PlayerControl_800AB9F4->mov.vy -= 32000;
                rasen_800C3404++;
                GM_PlayerPosition_800ABA10.vy -= 32000;
            }
            else if (level < -16000 - s11c_dword_800C3410 && rasen_800C3404 > 0)
            {
                svec1.vy = 32000;
                sub_8003049C(&svec1);
                GM_Camera_800B77E8.pan.pad = 0;
                rasen_800D2C84.field_1C = 1;
                rasen_800C3408 = 2;
                GM_PlayerControl_800AB9F4->mov.vy += 32000;
                rasen_800C3404--;
                GM_PlayerPosition_800ABA10.vy += 32000;
            }
        }
    }

    if (rasen_800C340C == 2)
    {
        field_10 = &rasen_800D2C84.field_10; // why???
        if (rasen_800C3408 == 1)
        {
            field_10->vy -= 32000;
            rasen_800D2C84.field_0.vy -= 32000;
            rasen_800D2C84.field_8.vy -= 32000;
        }
        else if (rasen_800C3408 == rasen_800C340C)
        {
            field_10->vy += 32000;
            rasen_800D2C84.field_0.vy += 32000;
            rasen_800D2C84.field_8.vy += 32000;
        }
        GV_NearExp4V(&rasen_800D2C84.field_0.vx, &field_10->vx, 3);
        GV_NearExp4V(&rasen_800D2C84.field_8.vx, &gUnkCameraStruct_800B77B8.center.vx, 3);
        GV_SubVec3(&rasen_800D2C84.field_8, &rasen_800D2C84.field_0, &svec2);
        rasen_800D2C84.field_18 = GV_VecDir2(&svec2);
    }
    else if (rasen_800C340C == 1)
    {
        svec3 = DG_ZeroVector;
        svec3.vy = gUnkCameraStruct_800B77B8.center.vy + 2000;
        svec3.vx += 500;
        svec3.vz -= 500;

        GV_SubVec3(&gUnkCameraStruct_800B77B8.center, &svec3, &svec4);
        GV_LenVec3(&svec4, &svec4, GV_VecLen3(&svec4), 3000);
        GV_SubVec3(&svec3, &svec4, &rasen_800D2C84.field_0);
        rasen_800D2C84.field_8 = gUnkCameraStruct_800B77B8.center;
        rasen_800D2C84.field_18 = GV_VecDir2(&svec4);
    }
    else
    {
        svec5 = gUnkCameraStruct_800B77B8.center;
        svec5.vz += 400;

        if (HZD_LevelTestHazard(Map_FromId_800314C0(rasen_el_800D2CA4[rasen_800C3404])->hzd, &svec5, 3) & 2)
        {
            svec5.vy += 6000;
            HZD_LevelMinMaxHeights(levels);
            if (svec5.vy > levels[1])
            {
                svec5.vy = levels[1];
            }
        }
        else
        {
            svec5.vy += 6000;
        }
        svec5.vy -= 300;
        rasen_800D2C84.field_0 = svec5;
        rasen_800D2C84.field_8 = gUnkCameraStruct_800B77B8.center;
    }

    GM_Camera_800B77E8.pan.pad = 0;
}

void RasenAct_800CBA54(RasenWork *work)
{
    RasenAct_800CB530(work);
}

void RasenDie_800CBA74(RasenWork *work)
{
}

GV_ACT *NewRasen_800CBA7C(void)
{
    RasenWork *work;

    work = (RasenWork *)GV_NewActor(EXEC_LEVEL, sizeof(RasenWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)RasenAct_800CBA54,
                         (GV_ACTFUNC)RasenDie_800CBA74, "rasen.c");
    }

    GV_ZeroMemory(&rasen_800D2C84, sizeof(rasen_800D2C84));
    return &work->actor;
}
