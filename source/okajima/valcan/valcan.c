#include "valcan.h"

#include "mts/mts.h"
#include "libgcl/libgcl.h"

#include "takabe/fadeio.h"      // for NewFadeInOut

SVECTOR valcan_shadow_offsets_800C35E0[2] = {{500, 0, 1000}, {-500, 0, 1000}};
SVECTOR valcan_target_size_800C35F0 = {500, 1000, 500};
SVECTOR valcan_target2_size_800C35F8 = {800, 2000, 800};

int     SECTION(".bss") valcan_dead_800E3468;
int     SECTION(".bss") valcan_800E346C;
SVECTOR SECTION(".bss") valcan_pos_800E3470;

void AN_Breath(MATRIX *matrix);

int Valcan_800D8D20(CONTROL *control, SVECTOR *svec1)
{
    SVECTOR svec2;

    GV_SubVec3(svec1, &control->mov, &svec2);
    return ratan2(svec2.vx, svec2.vz) & 0xFFF;
}

void ValcanQueueDynamicSegment_800D8D5C(Work *work, int flag)
{
    HZD_QueueDynamicSegment2(GM_GetMap(work->field_20)->hzd, &work->field_928, flag);
}

void ValcanDequeueDynamicSegment_800D8DA0(Work *work)
{
    HZD_DequeueDynamicSegment(GM_GetMap(work->field_20)->hzd, &work->field_928);
}

void Valcan_800D8DD8(Work *work)
{
    SVECTOR svec1, svec2;

    svec1.vx = -500;
    svec1.vy = 0;
    svec1.vz = -1000;

    svec2.vx = 500;
    svec2.vy = 0;
    svec2.vz = -1000;

    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(&svec1, &svec1, 2);

    work->field_928.p1.y = 500;
    work->field_928.p1.h = 1500;
    work->field_928.p2.y = 500;
    work->field_928.p2.h = 1500;

    work->field_928.p1.x = svec1.vx;
    work->field_928.p2.x = svec2.vx;
    work->field_928.p1.z = svec1.vz;
    work->field_928.p2.z = svec2.vz;

    HZD_SetDynamicSegment(&work->field_928, &work->field_928);
}

// Identical to blood_cl.c: GetInts
void ValcanGetInts_800D8E88(unsigned char *opt, int *out)
{
    char *res;

    while ((res = GCL_NextStr()) != NULL)
    {
        *out = GCL_StrToInt(res);
        out++;
    }
}

void s15c_valcan_800D8ECC(Work *work)
{
    SVECTOR  off[2];
    MATRIX   rot;
    SVECTOR *vec;

    rot = DG_ZeroMatrix;
    RotMatrixYXZ_gte(&work->field_6CC, &rot);
    DG_SetPos(&rot);
    DG_PutVector(valcan_shadow_offsets_800C35E0, off, 2);

    vec = work->field_6D4;

    vec[0].vx = work->field_6C4.vx + off[0].vx;
    vec[3].vx = work->field_6C4.vx - off[0].vx;
    vec[0].vz = work->field_6C4.vz + off[0].vz;
    vec[3].vz = work->field_6C4.vz - off[0].vz;
    vec[1].vx = work->field_6C4.vx + off[1].vx;
    vec[2].vx = work->field_6C4.vx - off[1].vx;
    vec[1].vz = work->field_6C4.vz + off[1].vz;
    vec[2].vz = work->field_6C4.vz - off[1].vz;
    vec[0].vy = work->field_6D4[1].vy = work->field_6D4[2].vy = work->field_6D4[3].vy =
        work->field_6C4.vy - work->control.height;
}

// Identical to item_init_prim_buffer_800336A4
void Valcan_800D9028(POLY_FT4 *prims, DG_TEX *tex)
{
    char t_u0; // $a1
    char t_v0; // $v1
    char t_u1; // $a0
    char t_v2; // $v1

    setPolyFT4(prims);
    setSemiTrans(prims, 1);

    t_u0 = tex->off_x;
    t_u1 = t_u0 + tex->w;

    t_v0 = tex->off_y;
    t_v2 = t_v0 + tex->h;

    setUV4(prims, t_u0, t_v0, t_u1, t_v0, t_u0, t_v2, t_u1, t_v2);

    prims->tpage = tex->tpage;
    prims->clut = tex->clut;
}


void ValcanAct_800D9088(Work *work)
{
    CONTROL *control;

    if (GM_Vitality <= 0)
    {
        GCL_ExecProc(work->field_8D4, NULL);
    }
    if (!(GV_Time & 3))
    {
        AN_Breath(&work->field_A0.objs->objs[6].world);
    }
    if (work->field_7D4 != 2)
    {
        control = &work->control;
        GM_CurrentMap = work->field_20;
        Valcan_800D9B5C(work);
        s15c_valcan_800D8ECC(work);
        if (work->field_81C == 0)
        {
            GM_ActControl(control);
            GM_ActObject2(&work->field_A0);
            GM_MoveTarget(work->field_664, &control->mov);
            GM_MoveTarget(work->field_668, &control->mov);
            GM_PushTarget(work->field_668);
            if (GM_Item == IT_ThermG)
            {
                DG_AmbientObjs(work->field_A0.objs);
            }
            else
            {
                DG_UnAmbientObjs(work->field_A0.objs);
            }
            DG_GetLightMatrix2(&control->mov, work->field_624);
        }
    }
    valcan_pos_800E3470 = work->control.mov;
    if (work->field_81C == 1)
    {
        work->field_81C = 2;
    }
    if (work->field_81C == 2)
    {
        work->field_81C = 3;
        work->field_8D8 = 30;
        NewFadeInOut(FADEIO_MODE_TOBLACK, 20);
    }
    if (work->field_81C == 3)
    {
        if (work->field_8D8-- < 0)
        {
            valcan_dead_800E3468 = work->field_81C;
            GV_DestroyActor(work);
        }
    }
    ValcanDequeueDynamicSegment_800D8DA0(work);
    Valcan_800D8DD8(work);
    if (GV_DiffDirAbs(work->control.rot.vy,
                      Valcan_800D8D20(&work->control, &GM_PlayerPosition)) < 1024)
    {
        ValcanQueueDynamicSegment_800D8D5C(work, 0xdf);
    }
    else
    {
        ValcanQueueDynamicSegment_800D8D5C(work, 0xdb);
    }
}


int ValcanGetResources_800D92A8(Work *work, int name, int where)
{
    int            args[15];
    CONTROL       *control;
    DG_PRIM       *prim;
    DG_TEX        *tex;
    OBJECT        *object1, *object2;
    unsigned char *option;
    int            i, j;
    int            k500;

    work->field_20 = where;
    GM_CurrentMap = where;

    option = (unsigned char *)GCL_GetOption('s');
    if (option)
    {
        work->field_7D4 = GCL_StrToInt(option);
    }
    else
    {
        work->field_7D4 = 1;
    }

    control = &work->control;
    if (work->field_7D4 != 2)
    {
        k500 = 500;
        if (GM_InitControl(control, name, where) < 0)
        {
            return -1;
        }

        GM_ConfigControlAttribute(control, 5);
        GM_ConfigControlHazard(control, -1, -2, -1);
        GM_ConfigControlInterp(control, 4);

        option = (unsigned char *)GCL_GetOption('h');
        if (option)
        {
            work->field_6A8 = GCL_StrToInt(option);
            work->field_6A8 = work->field_6A8 / 8 * 8;
        }
        else
        {
            work->field_6A8 = 1024;
        }

        for (j = 0; j < 4; j++)
        {
            for (i = 0; i < 4; i++)
            {
                work->field_6F8[i][j][0] = i * 7000 - 10500;
                work->field_6F8[i][j][1] = j * 6000 - 7500;
            }
        }

        option = (unsigned char *)GCL_GetOption('p');
        if (option)
        {
            ValcanGetInts_800D8E88(option, args);
        }

        work->field_738 = args[0];
        work->field_73A = args[1];

        work->control.mov.vx = work->field_6F8[work->field_738][work->field_73A][0];
        work->control.mov.vy = 0;
        work->control.mov.vz = work->field_6F8[work->field_738][work->field_73A][1];

        option = (unsigned char *)GCL_GetOption('q');
        if (option)
        {
            ValcanGetInts_800D8E88(option, args);
        }

        work->field_73C = args[0];
        work->field_73E = args[1];

        work->field_6C4 = work->control.mov;
        work->field_6CC = work->control.rot;

        option = (unsigned char *)GCL_GetOption('n');
        if (option)
        {
            work->field_8D0 = GCL_StrToInt(option);
        }

        option = (unsigned char *)GCL_GetOption('i');
        if (option)
        {
            work->field_8D4 = GCL_StrToInt(option);
        }

        object1 = &work->field_A0;
        GM_InitObject(object1, GV_StrCode("val_wep"), 0x22D,
                      GV_StrCode("val_15a"));
        GM_ConfigObjectJoint(object1);
        GM_ConfigMotionControl(object1, &work->field_268, GV_StrCode("val_15a"),
                               &work->field_2B8, NULL, control, &work->field_524);
        GM_ConfigObjectLight(object1, work->field_624);

        object2 = &work->field_184;
        GM_InitObject(object2, GV_StrCode("barrel"), 0x22D, 0);
        GM_ConfigObjectLight(object2, work->field_624);
        GM_ConfigObjectJoint(object2);

        Valcan_800D9B3C(work);
        s15c_valcan_800D8ECC(work);

        work->field_6F4 = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, work->field_6D4, NULL);
        if (work->field_6F4 == NULL)
        {
            return -1;
        }

        prim->raise = k500;

        tex = DG_GetTexture(GV_StrCode("shadow"));
        if (tex == NULL)
        {
            return -1;
        }

        Valcan_800D9028(prim->packs[0], tex);
        Valcan_800D9028(prim->packs[1], tex);

        setRGB0((POLY_FT4 *)prim->packs[0], 150, 150, 150);
        setRGB0((POLY_FT4 *)prim->packs[1], 150, 150, 150);

        work->field_878 = GM_PlayerPosition;

        NewFadeInOut(FADEIO_MODE_FROMBLACK, 20);
    }

    ValcanQueueDynamicSegment_800D8D5C(work, 0xDF);
    return 0;
}

void ValcanDie_800D96E8(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->field_A0);
    GM_FreeObject(&work->field_184);
    GM_FreePrim(work->field_6F4);
    GM_FreeTarget(work->field_664);
    GM_FreeTarget(work->field_668);
    GCL_ExecProc(work->field_8D0, NULL);
    ValcanDequeueDynamicSegment_800D8DA0(work);
}

int ValcanGetResources2_800D9774(Work *work)
{
    TARGET *target, *target2;

    target = GM_AllocTarget();
    work->field_664 = target;

    if (target != NULL)
    {
        GM_SetTarget(target, 0x15, 2, &valcan_target_size_800C35F0);
        GM_SetPowerTarget(target, POWER_DECREASE, -1, work->field_6A8, 0xFF, &DG_ZeroVector);
        work->field_900 = work->field_6A8;

        target2 = GM_AllocTarget();
        work->field_668 = target2;

        if (target2 != NULL)
        {
            GM_SetTarget(target2, 8, 0, &valcan_target2_size_800C35F8);
            target2->flag = 1;
            return 0;
        }
    }

    return -1;
}

int ValcanGetResources_800D9830(Work *work, int name, int where)
{
    valcan_dead_800E3468 = 0;
    if (ValcanGetResources_800D92A8(work, name, where) < 0)
    {
        return -1;
    }
    return 0;
}

void *NewValcan_800D9864(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, ValcanAct_800D9088, ValcanDie_800D96E8, "valcan.c");
        if (ValcanGetResources_800D9830(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
        if (ValcanGetResources2_800D9774(work) < 0)
        {
            return NULL;
        }
    }

    return (void *)work;
}

