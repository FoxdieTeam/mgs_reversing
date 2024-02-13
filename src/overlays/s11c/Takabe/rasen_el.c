#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/camera.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct RasenElWork
{
    GV_ACT   actor;
    int      map;
    int      name;
    OBJECT   object;
    MATRIX   light[2];
    HZD_HDL *hzd[2];
    HZD_FLR  flr1[2];
    HZD_FLR  flr2[2];
    SVECTOR  f214;
    SVECTOR  f21C;
    int      f224;
    int      f228;
    int      f22C;
    int      f230;
    int      f234;
    int      f238;
    int      f23C;
    int      f240;
    int      f244;
    int      f248;
    DG_PRIM *f24C;
    SVECTOR  f250[12];
    SVECTOR  f2B0;
    SVECTOR  f2B8;
    DG_TEX  *f2C0;
    int      f2C4;
    int      f2C8;
    int      f2CC;
    int      f2D0;
    int      f2D4;
    int      f2D8;
    int      f2DC;
    SVECTOR  f2E0;
    char     pad[0x10];
} RasenElWork;

extern int       GM_CurrentMap_800AB9B0;
extern int       GM_PlayerStatus_800ABA50;
extern GM_Camera GM_Camera_800B77E8;

extern unsigned short rasen_el_800D2CA4[];

int            THING_Gcl_GetInt(int);
int            THING_Gcl_GetIntDefault(int, int);
int            THING_Gcl_GetSVector(int, SVECTOR *);
unsigned short THING_Gcl_GetShort(int);

void Takabe_FreeObjs_800DC820(DG_OBJS *objs);

void s11c_800CCFCC(RasenElWork *, int);
void s11c_800CD0C4(RasenElWork *);
void s11c_800CDAB4(RasenElWork *);

void s16b_800C46D8(HZD_FLR *, SVECTOR *, SVECTOR *);
void s11c_800CD120(RasenElWork *work);
void s11c_800CD17C(OBJECT *, int, int);

DG_OBJS * s00a_unknown3_800DC7DC(int model, LitHeader *lit);

#define EXEC_LEVEL 6

// used somewhere
int s11c_dword_800C342C = 0x085BACDC;
int s11c_dword_800C3430 = 0xDBC9804B;
int s11c_dword_800C3434 = 0x5F2BE0CF;

const int s11c_dword_800D2BB4 = 0x800CC534;
const int s11c_dword_800D2BB8 = 0x800CC58C;
const int s11c_dword_800D2BBC = 0x800CC5F8;
const int s11c_dword_800D2BC0 = 0x800CC650;
const int s11c_dword_800D2BC4 = 0x800CC748;
const int s11c_dword_800D2BC8 = 0x800CC768;

#pragma INCLUDE_ASM("asm/overlays/s11c/RasenElAct_800CC454.s")
void RasenElAct_800CC454(RasenElWork *work);

void RasenElDie_800CCAC4(RasenElWork *work)
{
    DG_PRIM *prim;

    if (GM_Camera_800B77E8.field_18_flags & 0x200)
    {
        GM_SetCameraCallbackFunc_8002FD84(0, 0);
        GM_Camera_800B77E8.field_22 = 0;
        GM_Camera_800B77E8.field_18_flags &= ~0x200;
        GM_PlayerStatus_800ABA50 &= ~PLAYER_PAD_OFF;
        work->f248 = 3;
    }

    s11c_800CD120(work);

    if (work->f234 & 1)
    {
        Takabe_FreeObjs_800DC820(work->object.objs);
    }
    else
    {
        GM_FreeObject_80034BF8(&work->object);
    }

    prim = work->f24C;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int RasenElGetResources_800CCB9C(RasenElWork *work, int name, int map)
{
    SVECTOR sp10;
    SVECTOR sp18;
    OBJECT *object;
    int     model;
    int     texid;
    int     f230;

    GM_CurrentMap_800AB9B0 = map;

    work->map = map;
    work->name = name;
    work->f234 = 0;

    work->hzd[0] = Map_FromId_800314C0(rasen_el_800D2CA4[0])->field_8_hzd;
    work->hzd[1] = Map_FromId_800314C0(rasen_el_800D2CA4[1])->field_8_hzd;

    object = &work->object;

    model = THING_Gcl_GetShort('m');
    if (model != 0)
    {
        GM_InitObject_80034A18(object, model, 0x5D, 0);
        GM_ConfigObjectLight_80034C44(object, work->light);
    }
    else
    {
        model = THING_Gcl_GetShort('n');
        if (model == 0)
        {
            return -1;
        }

        s11c_800CD17C(object, model, 0x57);
        work->f234 |= 1;
    }

    THING_Gcl_GetSVector('p', &work->f214);

    work->f224 = THING_Gcl_GetInt('h') * 10;
    work->f22C = THING_Gcl_GetIntDefault('c', 300);
    work->f2C8 = THING_Gcl_GetShort('o');
    work->f2CC = THING_Gcl_GetShort('u');

    sp10.vx = object->objs->def->min.vx + 100;
    sp10.vz = object->objs->def->min.vz + 100;
    sp10.vy = 1;

    sp18 = work->f214;
    s16b_800C46D8(&work->flr2[0], &sp18, &sp10);
    sp18.vy -= 32000;
    s16b_800C46D8(&work->flr2[1], &sp18, &sp10);

    s11c_800CCFCC(work, work->f214.vy);
    s11c_800CD0C4(work);

    work->f230 = 0;
    work->f2C4 = 3;
    work->f238 = 0;

    if (GCL_GetOption_80020968('i'))
    {
        f230 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        if (f230 >= 0)
        {
            work->f2C4 = 1;
        }
        else
        {
            f230 = -f230;
        }

        work->f230 = f230;
    }

    if (GCL_GetOption_80020968('w'))
    {
        work->f23C = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f234 |= 4;
    }

    work->f228 = (work->f224 * work->f230) / work->f22C;
    work->f21C = work->f214;
    work->f21C.vy += work->f228;

    if (GCL_GetOption_80020968('b'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->f2E0);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->f2B0);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->f2B8);
        texid = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        texid = 0xB41;

        work->f2E0.vx = -600;
        work->f2E0.vy = 1650;
        work->f2E0.vz = 550;

        work->f2B0.vx = -750;
        work->f2B0.vy = 1500;
        work->f2B0.vz = 1750;

        work->f2B8.vx = 400;
        work->f2B8.vy = 600;
        work->f2B8.vz = 0;
    }

    work->f2C0 = DG_GetTexture_8001D830(texid);

    s11c_800CDAB4(work);

    work->f2DC = 2;
    work->f240 = 60;
    work->f244 = 0;

    return 0;
}

GV_ACT * NewRasenEl_800CCF38(int arg0, int arg1)
{
    RasenElWork *work;

    work = (RasenElWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(RasenElWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)RasenElAct_800CC454, (TActorFunction)RasenElDie_800CCAC4, "rasen_el.c");

        if (RasenElGetResources_800CCB9C(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

void s11c_800CCFCC(RasenElWork *work, int height)
{
    HZD_FLR *dst;
    HZD_FLR *src;
    int      i;

    dst = work->flr1;
    src = work->flr2;
    for (i = 0; i < 2; i++)
    {
        dst->b1 = src->b1;
        dst->b1.y += height;

        dst->b2 = src->b2;
        dst->b2.y += height;

        dst->p1 = src->p1;
        dst->p1.y += height;

        dst->p2 = src->p2;
        dst->p2.y += height;

        dst->p3 = src->p3;
        dst->p3.y += height;

        dst->p4 = src->p4;
        dst->p4.y += height;

        dst->b1.h |= ~0x3FFF;

        dst++;
        src++;
    }
}

void s11c_800CD0C4(RasenElWork *work)
{
    HZD_FLR *floor;
    int      i;

    floor = work->flr1;
    for (i = 0; i < 2; i++)
    {
        HZD_QueueDynamicFloor_8006FF9C(work->hzd[i], floor);
        floor++;
    }
}

void s11c_800CD120(RasenElWork *work)
{
    HZD_FLR *floor;
    int      i;

    floor = work->flr1;
    for (i = 0; i < 2; i++)
    {
        HZD_DequeueDynamicFloor_8006FFE8(work->hzd[i], floor);
        floor++;
    }
}

void s11c_800CD17C(OBJECT *object, int model, int flag)
{
    GV_ZeroMemory_8001619C(object, sizeof(OBJECT));

    object->flag = flag;
    object->map_name = GM_CurrentMap_800AB9B0;
    object->objs = s00a_unknown3_800DC7DC(model, Map_FromId_800314C0(GM_CurrentMap_800AB9B0)->field_C_lit);
}

void s11c_800CD1E4(int proc, int value)
{
    GCL_ARGS args;
    u_long   data;

    data = value;
    if (proc != 0)
    {
        args.argc = 1;
        args.argv = &data;
        GCL_ExecProc_8001FF2C(proc, &args);
    }
}

const char s11c_aCancel_800D2BD8[] = "cancel\n";
const char s11c_dword_800D2BE0[] = "cancel cause of item\n";

#pragma INCLUDE_ASM("asm/overlays/s11c/s11c_800CD21C.s")
#pragma INCLUDE_ASM("asm/overlays/s11c/s11c_800CD340.s")

void s11c_800CD868(POLY_FT4 *packs, DG_TEX *tex)
{
    int i;
    int x, y, w, h;

    for (i = 0; i < 3; i++)
    {
        setPolyFT4(packs);

        x = tex->field_8_offx;
        w = tex->field_A_width + x;
        packs->u0 = packs->u2 = x;
        packs->u1 = packs->u3 = w;

        y = tex->field_9_offy;
        h = tex->field_B_height + 1;
        packs->v0 = packs->v1 = y + (h * i) / 3;
        packs->v2 = packs->v3 = y + (h * (i + 1)) / 3 - 1;

        packs->tpage = tex->field_4_tPage;
        packs->clut = tex->field_6_clut;

        setRGB0(packs, 128, 128, 128);
        packs++;
    }
}

void s11c_800CD958(RasenElWork *work)
{
    SVECTOR  vec;
    SVECTOR *iter;
    int      i;

    vec.vx = work->f2B0.vx - work->f2B8.vx / 2;
    vec.vy = work->f2B0.vy + work->f2B8.vy / 2;
    vec.vz = work->f2B0.vz - work->f2B8.vz / 2;

    iter = work->f250;
    for (i = 0; i < 3; i++)
    {
        iter[0].vx = vec.vx + work->f2B8.vx;
        iter[0].vy = vec.vy;
        iter[0].vz = vec.vz;
        iter[1] = vec;

        vec.vy -= work->f2B8.vy / 3;

        iter[2].vx = vec.vx + work->f2B8.vx;
        iter[2].vy = vec.vy;
        iter[2].vz = vec.vz;
        iter[3] = vec;

        iter += 4;
    }
}

void s11c_800CDAB4(RasenElWork *work)
{
    DG_PRIM *prim;

    prim = DG_GetPrim(0x1012, 3, 0, work->f250, NULL);
    work->f24C = prim;

    s11c_800CD868(&prim->field_40_pBuffers[0]->poly_ft4, work->f2C0);
    s11c_800CD868(&prim->field_40_pBuffers[1]->poly_ft4, work->f2C0);

    s11c_800CD958(work);

    prim->group_id = rasen_el_800D2CA4[0] | rasen_el_800D2CA4[1];
    prim->field_2E_k500 = 0;
    prim->root = &work->object.objs->world;
}

void s11c_800CDB6C(RasenElWork *work)
{
    DG_PRIM  *prim;
    POLY_FT4 *pack0;
    POLY_FT4 *pack1;
    int       i;
    int       color;

    prim = work->f24C;
    pack1 = &work->f24C->field_40_pBuffers[0]->poly_ft4;
    pack0 = &work->f24C->field_40_pBuffers[1]->poly_ft4;

    for (i = 0; i < 3; i++)
    {
        if (i == work->f2DC)
        {
            setRGB0(pack1, 97, 128, 138);
            color = LLOAD(&pack1->r0);
            LSTORE(color, &pack0->r0);
        }
        else
        {
            setRGB0(pack1, 32, 32, 32);
            color = LLOAD(&pack1->r0);
            LSTORE(color, &pack0->r0);
        }

        pack1++;
        pack0++;
    }
}
