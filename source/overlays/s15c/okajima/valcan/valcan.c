#include "mgstype.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

#include "okajima/bullet.h"     // for NewBulletEx
#include "okajima/blood.h"      // for NewBlood
#include "takabe/fadeio.h"      // for NewFadeInOut

typedef struct _Work
{
    GV_ACT         actor;              /* 0x000 */
    int            map;                /* 0x020 */
    CONTROL        control;            /* 0x024 */
    OBJECT         body;               /* 0x0A0 */
    OBJECT         barrel;             /* 0x184 */
    MOTION_CONTROL m_ctrl;             /* 0x268 */
    MOTION_SEGMENT m_segs[17];         /* 0x2B8 */
    SVECTOR        aim_pos;            /* 0x51C */
    SVECTOR        rots[16];           /* 0x524 */
    SVECTOR        adjust[16];         /* 0x5A4 */
    MATRIX         light[2];           /* 0x624 */
    TARGET        *target;             /* 0x664 */
    TARGET        *push_target;        /* 0x668 */
    int            field_66C;          /* 0x66C vertical speed */
    int            field_670;          /* 0x670 */
    char           pad674[0x10];
    int            mode;               /* 0x684 */
    int            action;             /* 0x688 */
    int            aim_dis;            /* 0x68C */
    int            sweep_time;         /* 0x690 */
    int            field_694;          /* 0x694 */
    int            field_698;          /* 0x698 */
    int            field_69C;          /* 0x69C */
    int            path_index;         /* 0x6A0 */
    int            field_6A4;          /* 0x6A4 */
    int            max_life;           /* 0x6A8 */
    int            field_6AC;          /* 0x6AC */
    int            field_6B0;          /* 0x6B0 */
    int            barrel_speed;       /* 0x6B4 */
    int            field_6B8;          /* 0x6B8 */
    int            barrel_tick;        /* 0x6BC */
    int            field_6C0;          /* 0x6C0 */
    SVECTOR        shadow_pos;         /* 0x6C4 */
    SVECTOR        shadow_rot;         /* 0x6CC */
    SVECTOR        shadow_quad[4];     /* 0x6D4 */
    DG_PRIM       *shadow_prim;        /* 0x6F4 */
    short          grid[4][4][2];      /* 0x6F8 x/z of the cell centers */
    union
    {
        struct
        {
            short  x;                  /* 0x738 */
            short  z;                  /* 0x73A */
        } idx;
        int packed;
    } cell;                            /* 0x738 */
    short          field_73C;          /* 0x73C */
    short          field_73E;          /* 0x73E */
    int            field_740;          /* 0x740 */
    int            field_744[4];       /* 0x744 */
    short          field_754;          /* 0x754 */
    short          field_756;          /* 0x756 */
    int            field_758;          /* 0x758 */
    int            field_75C;          /* 0x75C */
    char           pad760[4];
    int            field_764;          /* 0x764 */
    int            field_768;          /* 0x768 */
    int            field_76C;          /* 0x76C */
    int            field_770;          /* 0x770 */
    int            field_774;          /* 0x774 */
    int            field_778;          /* 0x778 saved mode */
    int            field_77C;          /* 0x77C saved action */
    int            field_780;          /* 0x780 */
    int            field_784;          /* 0x784 */
    int            field_788;          /* 0x788 */
    int            field_78C;          /* 0x78C */
    int            field_790;          /* 0x790 */
    int            field_794;          /* 0x794 */
    int            field_798;          /* 0x798 */
    int            field_79C;          /* 0x79C */
    short          field_7A0;          /* 0x7A0 current cell x */
    short          field_7A2;          /* 0x7A2 current cell z */
    SVECTOR        field_7A4;          /* 0x7A4 */
    SVECTOR        field_7AC;          /* 0x7AC */
    int            field_7B4;          /* 0x7B4 */
    char           pad7B8[0x1C];
    int            field_7D4;          /* 0x7D4 */
    int            field_7D8;          /* 0x7D8 */
    char           path[32][2];        /* 0x7DC cells to visit (21 used) */
    int            field_81C;          /* 0x81C */
    int            field_820;          /* 0x820 */
    int            field_824;          /* 0x824 */
    int            field_828;          /* 0x828 */
    int            field_82C;          /* 0x82C */
    int            field_830;          /* 0x830 */
    int            field_834;          /* 0x834 */
    int            field_838;          /* 0x838 */
    int            field_83C;          /* 0x83C */
    int            field_840;          /* 0x840 */
    char           pad844[0x34];
    SVECTOR        field_878;          /* 0x878 */
    char           pad880[0x50];
    int            field_8D0;          /* 0x8D0 */
    int            field_8D4;          /* 0x8D4 */
    int            field_8D8;          /* 0x8D8 */
    int            field_8DC;          /* 0x8DC */
    int            field_8E0;          /* 0x8E0 */
    int            field_8E4;          /* 0x8E4 */
    int            field_8E8;          /* 0x8E8 */
    int            field_8EC;          /* 0x8EC */
    int            field_8F0;          /* 0x8F0 */
    MENU_BAR_CONF  lifebar;            /* 0x8F4 */
    int            life;               /* 0x900 */
    int            bar_life;           /* 0x904 */
    char           pad908[4];
    int            field_90C;          /* 0x90C */
    SVECTOR        field_910;          /* 0x910 */
    int            field_918;          /* 0x918 */
    int            field_91C;          /* 0x91C */
    int            field_920;          /* 0x920 */
    int            field_924;          /* 0x924 */
    HZD_SEG        seg;                /* 0x928 */
    int            field_938;          /* 0x938 */
    int            field_93C;          /* 0x93C */
    int            field_940;          /* 0x940 */
    int            field_944;          /* 0x944 */
    int            field_948;          /* 0x948 */
    int            field_94C;          /* 0x94C */
    int            field_950;          /* 0x950 */
} Work;

#define SEGMENT_ATR ( HZD_SEG_NO_NAVIGATE )

SVECTOR s15c_dword_800C35E0[2] = {{500, 0, 1000}, {-500, 0, 1000}};
SVECTOR s15c_dword_800C35F0 = {500, 1000, 500};
SVECTOR s15c_dword_800C35F8 = {800, 2000, 800};
SVECTOR s15c_dword_800C3600 = {10, -2500, -70};
SVECTOR s15c_dword_800C3608 = {0, 0, 100};
SVECTOR s15c_dword_800C3610 = {64512, 0, 0};

int     SECTION(".bss") s15c_dword_800E346C;
int     SECTION(".bss") s15c_dword_800E3470;
SVECTOR SECTION(".bss") s15c_dword_800E3474;
char    SECTION(".bss") s15c_dword_800E347C[8]; // could be smaller, it only has to be 6 bytes large
int     SECTION(".bss") s15c_dword_800E3484;
int     SECTION(".bss") s15c_dword_800E3488;

const char s15c_dword_800E2E38[] = {0x0, 0xb3, 'B', 0x8c};
const char s15c_aValwep_800E2E3C[] = "val_wep";
const char s15c_aVala_800E2E44[] = "val_15a";
const char s15c_aBarrel_800E2E4C[] = "barrel";
const char s15c_aShadow_800E2E54[] = "shadow";
const char s15c_dword_800E2E5C[] = {'v', 'a', 'l', 'c'};
const char s15c_dword_800E2E60[] = {'a', 'n', '.', 'c'};
const char s15c_dword_800E2E64[] = {0x0, 0x19, 0x0, 0xae};
const char s15c_aRaven_800E2E68[] = {'R', 'A', 'V', 'E', 'N', 0x0, 0x0, 0x2};

extern int     s15c_dword_800E345C[4];


extern int              amissile_alive_8009F490;
extern SVECTOR          svector_8009F478;
extern SVECTOR          svector_8009F494;
extern int              dword_8009F46C[];
extern int              dword_8009F480;
extern int              dword_8009F49C;

void    AN_Breath(MATRIX *matrix);
void    AN_HeadMark(MATRIX *world, int index);

int Valcan_800D8D20(CONTROL *control, SVECTOR *svec1)
{
    SVECTOR svec2;

    GV_SubVec3(svec1, &control->mov, &svec2);
    return ratan2(svec2.vx, svec2.vz) & 0xFFF;
}

void ValcanQueueDynamicSegment_800D8D5C(Work *work, int flag)
{
    HZD_QueueDynamicSegment2(GM_GetMap(work->map)->hzd, &work->seg, flag);
}

void ValcanDequeueDynamicSegment_800D8DA0(Work *work)
{
    HZD_DequeueDynamicSegment(GM_GetMap(work->map)->hzd, &work->seg);
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

    work->seg.p1.y = 500;
    work->seg.p1.h = 1500;
    work->seg.p2.y = 500;
    work->seg.p2.h = 1500;

    work->seg.p1.x = svec1.vx;
    work->seg.p2.x = svec2.vx;
    work->seg.p1.z = svec1.vz;
    work->seg.p2.z = svec2.vz;

    HZD_SetDynamicSegment(&work->seg, &work->seg);
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
    SVECTOR  pos[2];
    MATRIX   world;
    SVECTOR *quad;

    world = DG_ZeroMatrix;
    RotMatrixYXZ_gte(&work->shadow_rot, &world);
    DG_SetPos(&world);
    DG_PutVector(s15c_dword_800C35E0, pos, 2);

    quad = work->shadow_quad;
    quad[0].vx = work->shadow_pos.vx + pos[0].vx;
    quad[3].vx = work->shadow_pos.vx - pos[0].vx;
    quad[0].vz = work->shadow_pos.vz + pos[0].vz;
    quad[3].vz = work->shadow_pos.vz - pos[0].vz;
    quad[1].vx = work->shadow_pos.vx + pos[1].vx;
    quad[2].vx = work->shadow_pos.vx - pos[1].vx;
    quad[1].vz = work->shadow_pos.vz + pos[1].vz;
    quad[2].vz = work->shadow_pos.vz - pos[1].vz;
    quad[0].vy = quad[1].vy = quad[2].vy = quad[3].vy =
        work->shadow_pos.vy - work->control.height;
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

void Valcan_800D9B5C(Work *);

void ValcanAct_800D9088(Work *work)
{
    CONTROL *control;

    if (GM_Vitality <= 0)
    {
        GCL_ExecProc(work->field_8D4, NULL);
    }
    if (!(GV_Time & 3))
    {
        AN_Breath(&work->body.objs->objs[6].world);
    }
    if (work->field_7D4 != 2)
    {
        control = &work->control;
        GM_CurrentMap = work->map;
        Valcan_800D9B5C(work);
        s15c_valcan_800D8ECC(work);
        if (work->field_81C == 0)
        {
            GM_ActControl(control);
            GM_ActObject2(&work->body);
            GM_MoveTarget(work->target, &control->mov);
            GM_MoveTarget(work->push_target, &control->mov);
            GM_PushTarget(work->push_target);
            if (GM_Item == IT_ThermG)
            {
                DG_AmbientObjs(work->body.objs);
            }
            else
            {
                DG_UnAmbientObjs(work->body.objs);
            }
            DG_GetLightMatrix2(&control->mov, work->light);
        }
    }
    s15c_dword_800E3474 = work->control.mov;
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
            s15c_dword_800E346C = work->field_81C;
            GV_DestroyActor(&work->actor);
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

void Valcan_800D9B3C(Work *work);

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

    work->map = where;
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
            work->max_life = GCL_StrToInt(option);
            work->max_life = work->max_life / 8 * 8;
        }
        else
        {
            work->max_life = 1024;
        }

        for (j = 0; j < 4; j++)
        {
            for (i = 0; i < 4; i++)
            {
                work->grid[i][j][0] = i * 7000 - 10500;
                work->grid[i][j][1] = j * 6000 - 7500;
            }
        }

        option = (unsigned char *)GCL_GetOption('p');
        if (option)
        {
            ValcanGetInts_800D8E88(option, args);
        }

        work->cell.idx.x = args[0];
        work->cell.idx.z = args[1];

        work->control.mov.vx = work->grid[work->cell.idx.x][work->cell.idx.z][0];
        work->control.mov.vy = 0;
        work->control.mov.vz = work->grid[work->cell.idx.x][work->cell.idx.z][1];

        option = (unsigned char *)GCL_GetOption('q');
        if (option)
        {
            ValcanGetInts_800D8E88(option, args);
        }

        work->field_73C = args[0];
        work->field_73E = args[1];

        work->shadow_pos = work->control.mov;
        work->shadow_rot = work->control.rot;

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

        object1 = &work->body;
        GM_InitObject(object1, GV_StrCode(s15c_aValwep_800E2E3C), 0x22D,
                      GV_StrCode(s15c_aVala_800E2E44));
        GM_ConfigObjectJoint(object1);
        GM_ConfigMotionControl(object1, &work->m_ctrl, GV_StrCode(s15c_aVala_800E2E44),
                               work->m_segs, NULL, control, work->rots);
        GM_ConfigObjectLight(object1, work->light);

        object2 = &work->barrel;
        GM_InitObject(object2, GV_StrCode(s15c_aBarrel_800E2E4C), 0x22D, 0);
        GM_ConfigObjectLight(object2, work->light);
        GM_ConfigObjectJoint(object2);

        Valcan_800D9B3C(work);
        s15c_valcan_800D8ECC(work);

        work->shadow_prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, work->shadow_quad, NULL);
        if (work->shadow_prim == NULL)
        {
            return -1;
        }

        prim->raise = k500;

        tex = DG_GetTexture(GV_StrCode(s15c_aShadow_800E2E54));
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
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->barrel);
    GM_FreePrim(work->shadow_prim);
    GM_FreeTarget(work->target);
    GM_FreeTarget(work->push_target);
    GCL_ExecProc(work->field_8D0, NULL);
    ValcanDequeueDynamicSegment_800D8DA0(work);
}

int ValcanGetResources2_800D9774(Work *work)
{
    TARGET *target, *target2;

    target = GM_AllocTarget();
    work->target = target;

    if (target != NULL)
    {
        GM_SetTarget(target, TARGET_AVAIL | TARGET_POWER | TARGET_SEEK, ENEMY_SIDE, &s15c_dword_800C35F0);
        GM_SetPowerTarget(target, POWER_DECREASE, -1, work->max_life, 0xFF, &DG_ZeroVector);
        work->life = work->max_life;

        target2 = GM_AllocTarget();
        work->push_target = target2;

        if (target2 != NULL)
        {
            GM_SetTarget(target2, TARGET_PUSH, NO_SIDE, &s15c_dword_800C35F8);
            target2->flag = 1;
            return 0;
        }
    }

    return -1;
}

int ValcanGetResources_800D9830(Work *work, int name, int where)
{
    s15c_dword_800E346C = 0;
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
        GV_SetNamedActor(&work->actor, ValcanAct_800D9088, ValcanDie_800D96E8, s15c_dword_800E2E5C);
        if (ValcanGetResources_800D9830(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        if (ValcanGetResources2_800D9774(work) < 0)
        {
            return NULL;
        }
    }

    return (void *)work;
}

void Valcan_800D990C(Work *work)
{
    int rest;
    int now;

    now = (work->life << 10) / work->max_life / 8 * 8;
    if (now < 0)
    {
        now = 0;
        work->target->vital = 0;
        work->life = 0;
    }

    rest = work->bar_life;
    if (rest < now)
    {
        rest = now;
    }
    if (now < rest)
    {
        work->bar_life -= 8;
    }

    if (rest < 8 || now < 8)
    {
        rest = 8;
        now = 8;
    }

    MENU_DrawBar2(28, rest, now, 1024, &work->lifebar);
}

void Valcan_800D99F0(Work *work)
{
    MENU_BAR_CONF *bar;

    work->bar_life = (work->life << 10) / work->max_life / 8 * 8;
    memcpy(s15c_dword_800E347C, s15c_aRaven_800E2E68, 6); // 6 == strlen("RAVEN") + 1
    work->lifebar.name = s15c_dword_800E347C;

    // Set the left and right RGB values for the health bar gradient
    bar = &work->lifebar;
    bar->left[0] = 16;
    bar->left[1] = 111;
    bar->left[2] = 159;
    bar->right[0] = 31;
    bar->right[1] = 223;
    bar->right[2] = 127;
}

void Valcan_800D9AB8(Work *work)
{
    CONTROL *control;

    control = &work->control;
    control->height = work->body.height;
    control->r_sphere = GV_NearExp2(control->r_sphere, 450);

    if (work->field_66C < 0 && control->grounded != 0)
    {
        work->field_66C = 0;
    }
    work->field_66C -= 16;

    control->step.vy = work->field_66C;
}

void Valcan_800DD578(Work *work);

void Valcan_800D9B3C(Work *work)
{
    Valcan_800DD578(work);
}

void s15c_crow_800DD03C(Work *work);

void Valcan_800D9B5C(Work *work)
{
    SVECTOR unused;

    s15c_crow_800DD03C(work);
    switch (work->field_90C)
    {
    case 0:
        work->field_90C = 1;
        break;

    case 1:
        work->field_90C = 2;
        Valcan_800D99F0(work);

    case 2:
        Valcan_800D990C(work);
        break;
    }

    Valcan_800D9AB8(work);

    unused.vx = 0;
    unused.vy = -730;
    unused.vz = -150;

    work->barrel.objs->root = &work->body.objs->objs[4].world;
    GM_ActObject2(&work->barrel);

    if (GM_Item == IT_ThermG)
    {
        DG_AmbientObjs(work->barrel.objs);
    }
    else
    {
        DG_UnAmbientObjs(work->barrel.objs);
    }

    DG_GetLightMatrix2(&work->control.mov, work->light);

    switch (work->field_91C)
    {
    case 1:
        work->barrel_speed = 0;
        work->field_91C = 2;
        work->field_918 = 0;
        GM_SeSetMode(&work->field_910, 180, GM_SEMODE_BOMB);

    case 2:
        work->field_918++;
        work->barrel_speed += 20;
        if (work->field_918 >= 16)
        {
            work->field_91C = 3;
            work->field_918 = 0;
        }
        break;
    case 3:
        if (mts_get_tick_count() - work->barrel_tick >= 4)
        {
            work->barrel_tick = mts_get_tick_count();
            GM_SeSetMode(&work->field_910, 179, GM_SEMODE_BOMB);
        }
        break;

    default:
        work->barrel_speed -= 6;
        if (work->barrel_speed < 0)
        {
            work->barrel_speed = 0;
        }
        else if (mts_get_tick_count() - work->barrel_tick > work->field_918 + 4)
        {
            work->field_918 += 6;
            work->barrel_tick = mts_get_tick_count();
        }
        break;
    }
    work->barrel.rots[1].vy += work->barrel_speed;
}

void Valcan_800D9D90(Work *work)
{
    RADAR_SIGHT_PARAM *r_param;

    work->control.radar_param.dir = work->control.rot.vy + work->adjust[6].vy;

    r_param = &work->control.radar_param;
    r_param->dis = work->field_944;
    r_param->range = work->field_948;
    r_param->r = 0;
}

int Valcan_800D9DC0(Work *work, int param_2)
{
    SVECTOR svec1, pos;
    int     vx, vy, vz;

    svec1.vx = work->body.objs->objs[4].world.t[0];
    svec1.vy = work->body.objs->objs[4].world.t[1];
    svec1.vz = work->body.objs->objs[4].world.t[2];

    if (param_2)
    {
        pos = GM_PlayerPosition;
    }
    else
    {
        pos = work->aim_pos;
    }

    vx = (svec1.vx - pos.vx) >> 4;
    vy = (svec1.vy - pos.vy) >> 4;
    vz = (svec1.vz - pos.vz) >> 4;
    return SquareRoot0(vx * vx + vy * vy + vz * vz) * 16;
}

// Identical to Eventmouse_800C9288
void Valcan_800D9EBC(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    SVECTOR diff;
    int     y;

    GV_SubVec3(to, from, &diff);
    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    y = diff.vy;
    diff.vy = 0;

    out->vx = (ratan2(GV_VecLen3(&diff), y) & 0xFFF) - 1024;
    out->vz = 0;
}

void Valcan_800D9F3C(Work *work, int count)
{
    SVECTOR *out;
    int      i;

    out = work->adjust;
    work->sweep_time = 0;
    for (i = 0; i < count; i++, out++)
    {
        *out = DG_ZeroVector;
    }
}

void Valcan_800D9F8C(Work *work)
{
    if (dword_8009F46C[0] == 1)
    {
        work->aim_pos = svector_8009F478;
        return;
    }
    work->field_82C = 0;
    if (amissile_alive_8009F490 == 1)
    {
        work->aim_pos = svector_8009F494;
        return;
    }
    work->field_838 = 0;
    work->aim_pos = GM_PlayerPosition;
}

void Valcan_800DA044(Work *work)
{
    // FIXME: why does this function do everything on stack?
    // FIXME: is there a better for loop match (without those strange break/continues)?
    short sp0[6];

    sp0[4] = (work->grid[1][0][0] - work->grid[0][0][0]) / 2;
    sp0[5] = (work->grid[0][1][1] - work->grid[0][0][1]) / 2;

    sp0[0] = 0;
    for (;;)
    {
        if (work->control.mov.vx >= work->grid[sp0[0]][0][0] + sp0[4])
        {
            if (++sp0[0] < 4)
            {
                continue;
            }
        }
        break;
    }

    sp0[1] = 0;
    for (;;)
    {
        if (work->control.mov.vz >= work->grid[0][sp0[1]][1] + sp0[5])
        {
            if (++sp0[1] < 4)
            {
                continue;
            }
        }
        break;
    }

    work->field_7A0 = sp0[0];
    work->field_7A2 = sp0[1];
}

void Valcan_800DA140(Work *work)
{
    if (work->sweep_time >= 48)
    {
        if (work->sweep_time < 144)
        {
            work->adjust[6].vy -= 8;
        }
        else if (work->sweep_time < 192)
        {
            work->adjust[6].vy += 8;
        }
    }
    else
    {
        work->adjust[6].vy += 8;
    }

    if (++work->sweep_time >= 192)
    {
        work->sweep_time = 0;
    }
}

int Valcan_800DA1AC(int arg0, int arg1)
{
    if (arg0 < 2)
    {
        arg0 = 1 - arg0;
    }

    arg0 = 1 - arg0 % 2 * 2;
    arg1 = 1 - (arg1 - (arg1 / 2 * 2)) * 2;

    return (arg0 * arg1 + 1) / 2 + 2;
}

void Valcan_800DA21C(Work *work) // it possibly returns a BulletWork*
{
    MATRIX  rotmat;
    SVECTOR svec;

    Valcan_800D9EBC(&work->control.mov, &GM_PlayerPosition, &svec);
    DG_SetPos2(&GM_PlayerPosition, &svec);
    ReadRotMatrix(&rotmat);
    NewBulletEx(BULLET_BLAST, &rotmat, 2, 0, 0, 30, 90, 30000, 100);
}

int s15c_crow_800DA2A8(Work *work)
{
    SVECTOR val;
    SVECTOR idx;
    SVECTOR ref;
    int     z;

    if (work->field_93C != 1 && GV_RandU(4) > 0)
    {
        return -1;
    }

    if ((u_int)(work->field_770 - 2) < 2)
    {
        idx.vx = work->cell.idx.x;
        idx.vy = work->cell.idx.z;
    }
    else
    {
        idx.vx = work->field_73C;
        idx.vy = work->field_73E;
    }

    val.vx = work->grid[idx.vx][idx.vy][0];
    val.vy = work->grid[idx.vx][idx.vy][1];
    ref = work->aim_pos;

    switch (work->field_740)
    {
    case 0:
    case 1:
        if (s15c_dword_800E345C[0] != 0 && (u_int)(u_short)idx.vy < 2 && idx.vx == 1)
        {
            return -1;
        }

        if (s15c_dword_800E345C[3] != 0 && (u_int)((u_short)idx.vy - 2) < 2 &&
            idx.vx == 2)
        {
            return -1;
        }

        z = val.vy;

        if (z < ref.vz && z < 9000)
        {
            return Valcan_800DA1AC(work->field_740, 3);
        }

        if (ref.vz < z && z > -6000)
        {
            return Valcan_800DA1AC(work->field_740, 2);
        }
        break;

    case 2:
    case 3:
        if (s15c_dword_800E345C[1] != 0 && (u_int)((u_short)idx.vx - 2) < 2 &&
            idx.vy == 1)
        {
            return -1;
        }

        if (s15c_dword_800E345C[2] != 0 && (u_int)(u_short)idx.vx < 2 && idx.vy == 2)
        {
            return -1;
        }

        z = val.vx;

        if (z < ref.vx && z < 9000)
        {
            return Valcan_800DA1AC(work->field_740, 1);
        }

        if (ref.vx < z && z > -9000)
        {
            return Valcan_800DA1AC(work->field_740, 0);
        }
        break;
    }

    return -1;
}

int Valcan_800DA558(Work *work, int arg1)
{
    SVECTOR svec1;
    SVECTOR svec2;
    SVECTOR svec3;
    int     diffdir;
    int     var_s0;
    int     flag;

    svec1.vx = work->body.objs->objs[4].world.t[0];
    svec1.vy = work->body.objs->objs[4].world.t[1];
    svec1.vz = work->body.objs->objs[4].world.t[2];

    Valcan_800D9EBC(&svec1, &work->aim_pos, &svec2);
    diffdir =
        GV_DiffDirAbs(svec2.vy, work->control.rot.vy + work->adjust[1].vy + work->adjust[6].vy);
    if (arg1 != 0)
    {
        svec3.vx = -800;
        svec3.vy = 0;
        svec3.vz = 0;
        DG_SetPos2(&svec1, &svec2);
        DG_PutVector(&svec3, &svec1, 1);
    }

    flag = 0;
    var_s0 = 0;
    if (dword_8009F46C[0] == 1 || amissile_alive_8009F490 == 1)
    {
        if (HZD_OnlineHazardCheck(work->control.map->hzd, &svec1, &work->aim_pos, HZD_CHK_SEGMENT, SEGMENT_ATR) == 0)
        {
            if (HZD_OnlineHazardCheck(work->control.map->hzd, &svec1, &GM_PlayerPosition, HZD_CHK_SEGMENT, SEGMENT_ATR) == 0)
            {
                var_s0 = Valcan_800D9DC0(work, 1);
                if (var_s0 < work->aim_dis)
                {
                    work->aim_pos = GM_PlayerPosition;
                    flag = 1;
                }
            }
            if (work->field_93C != 0 && amissile_alive_8009F490 == 1)
            {
                work->field_838 = amissile_alive_8009F490;
                return 1;
            }
        }
        else if (HZD_OnlineHazardCheck(work->control.map->hzd, &svec1, &GM_PlayerPosition, HZD_CHK_SEGMENT, SEGMENT_ATR) == 0)
        {
            var_s0 = Valcan_800D9DC0(work, 1);
            flag = 1;
            work->aim_pos = GM_PlayerPosition;
        }
        else
        {
            work->field_788 = 0;
            return 0;
        }
    }
    else if (HZD_OnlineHazardCheck(work->control.map->hzd, &svec1, &GM_PlayerPosition, HZD_CHK_SEGMENT, SEGMENT_ATR) != 0)
    {
        work->field_788 = 0;
        return 0;
    }
    else
    {
        var_s0 = Valcan_800D9DC0(work, 1);
        flag = 1;
    }

    if (!flag)
    {
        if (diffdir > 512)
        {
            return work->aim_dis < 3500;
        }

        work->field_7A4 = svec2;

        if (dword_8009F46C[0] == 1 && work->field_950 < 0)
        {
            work->field_82C = dword_8009F46C[0];
        }
        else if (amissile_alive_8009F490 == 1)
        {
            work->field_838 = 1;
        }
        else
        {
            work->field_93C = 0;
        }
        return 1;
    }
    else if (var_s0 < 3000)
    {
        if (diffdir < 256)
        {
            if (!(GM_PlayerStatus & (PLAYER_INVINCIBLE | PLAYER_DAMAGED | PLAYER_NOT_PLAYABLE)))
            {
                GM_SeSet2(0, 0x7F, SE_HIT);
                Valcan_800DA21C(work);
            }
        }
        return 1;
    }
    else if (diffdir > 512)
    {
        if (work->aim_dis < 4000 || work->field_924 > 0)
        {
            return 1;
        }

        return 0;
    }
    else
    {
        work->field_7A4 = svec2;
        work->field_93C = 0;
    }
    return 1;
}

void Valcan_800DA8E4(Work *work)
{
    SVECTOR  svecs[2];
    CONTROL *control;

    control = &work->control;

    svecs[0].vx = GV_RandU(512);
    svecs[0].vy = GV_RandU(512) + 256;
    svecs[0].vz = 500;
    svecs[1].vx = GV_RandU(256);
    svecs[1].vy = GV_RandU(256);
    svecs[1].vz = 200;

    DG_SetPos2(&control->mov, &control->rot);
    DG_PutVector(svecs, svecs, 2);

    DG_SetTmpLight(svecs, 500, 1000);
    DG_SetTmpLight(svecs, 500, 500);
}

void s15c_crow_800DA990(Work *work)
{
    MATRIX  mtx;
    SVECTOR rot;
    short   level;
    int     damage;

    if (work->field_830 == 0 && work->field_82C == 1)
    {
        work->field_830 = 1;
        work->field_834 = GV_RandU(work->field_770 != 3 ? 2 : 0x20) + 3;
    }

    if (work->field_830 == 1)
    {
        work->field_834--;

        if (work->field_834 == 0)
        {
            dword_8009F480 = 1;
            work->field_950 = 3;
            work->field_82C = 0;
            work->field_830 = 0;
        }
    }

    if (work->field_83C == 0 && work->field_838 == 1)
    {
        work->field_83C = 1;
        work->field_840 = GV_RandU(2) + 12;
    }

    if (work->field_83C == 1)
    {
        work->field_840--;

        if (work->field_840 == 0)
        {
            dword_8009F49C = 1;
            work->field_838 = 0;
            work->field_83C = 0;
        }
    }

    if (work->field_6A4 % 5 != 0)
    {
        return;
    }

    if (work->field_8DC++ >= 2)
    {
        work->field_8DC = 0;

        if (work->field_8F0 != 0)
        {
            if (work->field_6A4 % 100 == 0)
            {
                switch (GV_RandU(4))
                {
                case 0:
                    GM_SeSetMode(&work->field_910, 0x83, GM_SEMODE_BOMB);
                    break;

                case 1:
                    GM_SeSetMode(&work->field_910, 0x88, GM_SEMODE_BOMB);
                    break;

                case 2:
                case 3:
                    GM_SeSetMode(&work->field_910, 0x85, GM_SEMODE_BOMB);
                    break;
                }
            }
            else if (work->field_6A4 % 100 == 50)
            {
                if (GV_RandU(2) == 0)
                {
                    GM_SeSetMode(&work->field_910, 0x84, GM_SEMODE_BOMB);
                }
            }
        }
    }

    level = GM_GameLevel + 1;

    switch (level)
    {
    case 0:
    case 1:
    default:
        damage = 90;
        break;

    case 2:
        damage = 135;
        break;

    case 3:
        damage = 180;
        break;

    case 4:
        damage = 225;
        break;
    }

    if (work->field_91C == 0)
    {
        work->field_91C = 1;
        return;
    }

    if (GM_GameLevel == 3)
    {
        work->adjust[1].vy += GV_RandS(0x20);
    }

    DG_SetPos(&work->body.objs->objs[4].world);
    DG_MovePos(&s15c_dword_800C3600);
    rot.vx = 0x400;
    rot.vy = 0;
    rot.vz = 0;
    DG_RotatePos(&rot);
    ReadRotMatrix(&mtx);
    NewBulletEx(BULLET_FLASHHEAVY | BULLET_RECOILSPARK | BULLET_BLAST, &mtx, 2, 1, 0, 0x1E, damage,
                0x7530, 1000);
    Valcan_800DA8E4(work);
}


void Valcan_800DACCC(Work *work)
{
    if (work->field_758 != 0)
    {
        return;
    }

    switch (work->field_740)
    {
    case 0:
        Valcan_800DA044(work);
        work->control.mov.vz = work->grid[work->field_7A0][work->field_7A2][1];
        if (work->shadow_pos.vx < work->field_754)
        {
            work->field_758 = -1;
        }
        break;
    case 1:
        Valcan_800DA044(work);
        work->control.mov.vz = work->grid[work->field_7A0][work->field_7A2][1];
        if (work->shadow_pos.vx > work->field_754)
        {
            work->field_758 = -1;
        }
        break;
    case 2:
        Valcan_800DA044(work);
        work->control.mov.vx = work->grid[work->field_7A0][work->field_7A2][0];
        if (work->shadow_pos.vz < work->field_756)
        {
            work->field_758 = -1;
        }
        break;
    case 3:
        Valcan_800DA044(work);
        work->control.mov.vx = work->grid[work->field_7A0][work->field_7A2][0];
        if (work->shadow_pos.vz > work->field_756)
        {
            work->field_758 = -1;
        }
        break;
    }
}

int Valcan_800DAE38()
{
    return GV_RandU(4096) % 3 + 1;
}

int s15c_crow_800DAE7C(Work *work)
{
    int ret;

    work->field_828 = 0;
    ret = s15c_crow_800DA2A8(work);
    work->field_79C = ret;

    if (ret != -1)
    {
        return ret;
    }

    switch (work->field_740)
    {
    case 0:
        if (work->cell.idx.x == 1)
        {
            work->field_828 = 1;
            return 1;
        }

        if (s15c_dword_800E345C[2] != 0 && work->cell.packed == 0x20002)
        {
            return Valcan_800DAE38();
        }
        break;

    case 1:
        if (work->cell.idx.x == 2)
        {
            work->field_828 = 1;
            return 1;
        }

        if (s15c_dword_800E345C[1] != 0 && work->cell.packed == 0x10001)
        {
            return Valcan_800DAE38();
        }
        break;

    case 2:
        if (work->cell.idx.z == 1)
        {
            work->field_828 = 1;
            return 1;
        }

        if (s15c_dword_800E345C[0] != 0 && work->cell.packed == 0x20001)
        {
            return Valcan_800DAE38();
        }
        break;

    case 3:
        if (work->cell.idx.z == 2)
        {
            work->field_828 = 1;
            return 1;
        }

        if (s15c_dword_800E345C[3] != 0 && work->cell.packed == 0x10002)
        {
            return Valcan_800DAE38();
        }
        break;
    }

    return 0;
}
int s15c_crow_800DAFCC(Work *work)
{
    work->field_828 = 1;

    if (work->cell.idx.z == 0)
    {
        if (work->cell.idx.x == 0 && work->field_73C == 0)
        {
            if (work->field_73E == 1)
            {
                work->field_76C = 0;
                work->field_774 = work->field_770;

                if (s15c_dword_800E345C[0] != 0 && s15c_dword_800E345C[2] != 0)
                {
                    work->field_770 = 3;
                }
                else
                {
                    work->field_770 = 2;
                }

                work->field_6A4 = 0;
                work->field_69C = 0;
            }

            if ((u_int)work->field_740 < 2)
            {
                return Valcan_800DA1AC(work->field_740, 3);
            }

            if (work->field_740 == 2)
            {
                return 1;
            }

            work->field_828 = 0;
            return 0;
        }

        if ((u_int)(work->field_740 - 2) < 2)
        {
            return Valcan_800DA1AC(work->field_740, 0);
        }

        if (work->field_740 == 1)
        {
            return 1;
        }

        if (work->cell.idx.x == 1)
        {
            return 3;
        }

        work->field_828 = 0;
        return 0;
    }

    if ((u_int)work->field_740 < 2)
    {
        if (s15c_dword_800E345C[3] != 0)
        {
            int pair = work->cell.packed;

            if ((pair == 0x30001 && work->field_740 == 1) ||
                (pair == 0x30003 && work->field_740 == 0))
            {
                return 0;
            }
        }

        if (s15c_dword_800E345C[0] != 0)
        {
            int pair = work->cell.packed;

            if (pair == 0x20001)
            {
                return Valcan_800DA1AC(work->field_740, 0);
            }

            if (pair == 0x10000 && work->field_740 == 1)
            {
                return 0;
            }

            if (pair == 0x10002 && work->field_740 == 0)
            {
                return 0;
            }
        }

        return Valcan_800DA1AC(work->field_740, 2);
    }

    if (work->field_740 == 3)
    {
        return 1;
    }

    if (work->cell.idx.z == 1)
    {
        if (work->cell.idx.x == 0)
        {
            return 1;
        }

        return 3;
    }

    if (s15c_dword_800E345C[0] != 0 && work->cell.packed == 0x20001)
    {
        return Valcan_800DA1AC(work->field_740, 0);
    }

    work->field_828 = 0;
    return 0;
}
int s15c_crow_800DB200(Work *work)
{
    work->field_828 = 0;
    work->field_69C++;

    switch (work->field_740)
    {
    case 0:
        if (work->cell.idx.x == 1 && s15c_dword_800E345C[0] != 0 &&
            s15c_dword_800E345C[2] != 0)
        {
            work->field_770 = 3;
            work->field_6A4 = 0;
            work->field_69C = 0;
            return 3;
        }
        break;

    case 1:
        if (work->cell.idx.x == 2)
        {
            return 1;
        }
        break;

    case 2:
        if (work->cell.idx.z == 1)
        {
            return 2;
        }
        break;

    case 3:
        if (work->cell.idx.z == 2)
        {
            return 1;
        }
        break;
    }

    return 0;
}

int Valcan_800DB2E4(Work *work)
{
    short diffs[2];
    int   flag;
    Valcan_800DA044(work);

    if (work->path[work->path_index][0] == work->field_7A0 &&
        work->path[work->path_index][1] == work->field_7A2)
    {
        if (++work->path_index >= 21)
        {
            work->path_index = 0;
        }
    }

    diffs[0] = work->path[work->path_index][0] - work->field_7A0;
    diffs[1] = work->path[work->path_index][1] - work->field_7A2;

    flag = 0;

    if (diffs[0] > 0)
    {
        if (work->field_740 >= 2 && work->field_740 <= 3)
        {
            flag = Valcan_800DA1AC(work->field_740, 1);
        }
        else if (work->field_740 == 0)
        {
            flag = 1;
        }
    }
    else if (diffs[0] < 0)
    {
        if (work->field_740 < 2 || work->field_740 > 3)
        {
            if (work->field_740 == 1)
            {
                flag = 1;
            }
        }
        else
        {
            flag = Valcan_800DA1AC(work->field_740, 0);
        }
    }
    else if (diffs[1] > 0)
    {
        if (work->field_740 < 0 || work->field_740 > 1)
        {
            if (work->field_740 == 2)
            {
                flag = 1;
            }
        }
        else
        {
            flag = Valcan_800DA1AC(work->field_740, 3);
        }
    }
    else if (diffs[1] < 0)
    {
        if (work->field_740 >= 0 && work->field_740 <= 1)
        {
            flag = Valcan_800DA1AC(work->field_740, 2);
        }
        else if (work->field_740 == 3)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        Valcan_800D9F3C(work, 16);
    }

    return flag;
}

int Valcan_800DB470(Work *work)
{
    switch (work->field_770)
    {
    case 0:
        return s15c_crow_800DAE7C(work);
    case 1:
        return s15c_crow_800DAFCC(work);
    case 2:
        return s15c_crow_800DB200(work);
    case 3:
        return Valcan_800DB2E4(work);
    default:
        return 0;
    }
}

void Valcan_800DB500(Work *work)
{
    work->cell.idx.x = work->field_73C;
    work->cell.idx.z = work->field_73E;

    // We love switches!!!
    switch (work->field_770)
    {
    case 3:
    case 0:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_73C = 1;
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 2;
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_73E = 1;
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73E = 2;
            }
            break;
        }
        break;
    case 1:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_73C = 0;
                if (--work->field_73E < 0)
                {
                    work->field_73E = 1;
                }
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 3;
                if (--work->field_73E < 0)
                {
                    work->field_73C = 2;
                    work->field_73E = 0;
                }
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_73C--;
                work->field_73E = 0;
                if (work->field_73C < 0)
                {
                    work->field_73C = 0;
                    work->field_73E = 1;
                }
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73C--;
                work->field_73E = 3;
                if (work->field_73C < 0)
                {
                    work->field_73C = 0;
                    work->field_73E = 2;
                }
            }
            break;
        }
        break;
    case 2:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_768 = 3;

                work->field_73C = 0;
                work->field_73E = 1;
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 2;
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_768 = 1;
                work->field_73C = 1;
                work->field_73E = 0;
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73E = 2;
            }
            break;
        }
        break;
    }
}

void Valcan_800DB868(Work *work)
{
    int diff1, diff2;

    if (work->field_770 == 2)
    {
        work->field_76C = 0;
    }
    else if (work->field_770 == 3 || (work->field_770 == 1 && work->field_774 != 0))
    {
        work->field_76C = 500;
    }
    else if ((work->field_770 == 0 && work->field_774 == 2) || (work->field_770 == 1 && work->field_774 == 0))
    {
        work->field_76C = 0;
    }
    else
    {
        work->field_76C = 2800;
    }

    diff1 = work->field_73C - work->cell.idx.x;
    diff2 = work->field_73E - work->cell.idx.z;
    if (diff1 < 0)
    {
        work->field_740 = 0;
        work->field_754 = work->grid[work->field_73C][work->field_73E][0] + work->field_76C;
    }
    else if (diff1 > 0)
    {
        work->field_740 = 1;
        work->field_754 = work->grid[work->field_73C][work->field_73E][0] - work->field_76C;
    }
    else if (diff2 < 0)
    {
        work->field_740 = 2;
        work->field_756 = work->grid[work->field_73C][work->field_73E][1] + work->field_76C;
    }
    else if (diff2 > 0)
    {
        work->field_740 = 3;
        work->field_756 = work->grid[work->field_73C][work->field_73E][1] - work->field_76C;
    }
}

void s15c_crow_800DB9F0(Work *work)
{
    int dir = work->field_764;

    if ((work->field_770 == 1 && work->field_774 != 0) || work->field_770 == 2 ||
        work->field_770 == 3 || work->field_76C == 0 || work->field_774 == 2 ||
        work->field_774 == 3)
    {
        if ((u_int)(work->field_774 - 2) < 2)
        {
            work->field_774 = work->field_770;
        }

        switch (work->field_740)
        {
        case 0:
            work->field_768 = (dir > 0) ? 2 : 3;
            break;

        case 1:
            work->field_768 = (dir > 0) ? 3 : 2;
            break;

        case 2:
            if (dir > 0)
            {
                work->field_768 = 1;
            }
            else
            {
                work->field_768 = 0;
            }
            break;

        case 3:
            if (dir > 0)
            {
                work->field_768 = 0;
            }
            else
            {
                work->field_768 = 1;
            }
            break;
        }

        work->control.turn.vy = work->field_744[work->field_768];
        Valcan_800DB500(work);
        Valcan_800DB868(work);
        work->field_758 = 0;
        work->field_75C = 0;
    }
    else
    {
        work->field_75C--;

        if (work->field_75C >= 8)
        {
            work->control.turn.vy -= dir * 14;
            return;
        }

        if (work->field_75C >= 0)
        {
            switch (work->field_740)
            {
            case 0:
                if (dir > 0)
                {
                    work->field_768 = 2;
                }
                else
                {
                    work->field_768 = 3;
                }

                work->control.mov.vx =
                    (work->control.mov.vx +
                     work->grid[work->field_73C][work->field_73E][0]) / 2;
                break;

            case 1:
                if (dir > 0)
                {
                    work->field_768 = 3;
                }
                else
                {
                    work->field_768 = 2;
                }

                work->control.mov.vx =
                    (work->control.mov.vx +
                     work->grid[work->field_73C][work->field_73E][0]) / 2;
                break;

            case 2:
                if (dir > 0)
                {
                    work->field_768 = 1;
                }
                else
                {
                    work->field_768 = 0;
                }

                work->control.mov.vz =
                    (work->control.mov.vz +
                     work->grid[work->field_73C][work->field_73E][1]) / 2;
                break;

            case 3:
                if (dir > 0)
                {
                    work->field_768 = 0;
                }
                else
                {
                    work->field_768 = 1;
                }

                work->control.mov.vz =
                    (work->control.mov.vz +
                     work->grid[work->field_73C][work->field_73E][1]) / 2;
                break;
            }

            work->control.turn.vy = work->field_744[work->field_768];
            return;
        }

        Valcan_800DB500(work);
        Valcan_800DB868(work);
        work->field_758 = 0;
        work->field_75C = 0;
    }
}

void s15c_crow_800DBCB4(Work *work)
{
    if ((work->field_770 == 1 && work->field_774 != 0) || work->field_770 == 2 ||
        work->field_770 == 3 || work->field_76C == 0 || work->field_774 == 2 ||
        work->field_774 == 3)
    {
        if ((u_int)(work->field_774 - 2) < 2)
        {
            work->field_774 = work->field_770;
        }

        switch (work->field_740)
        {
        case 0:
            work->field_768 = 1;
            work->control.turn.vy = work->field_744[1];
            break;

        case 1:
            work->field_768 = 0;
            work->control.turn.vy = work->field_744[0];
            break;

        case 2:
            work->field_768 = 3;
            work->control.turn.vy = work->field_744[3];
            break;

        case 3:
            work->field_768 = 2;
            work->control.turn.vy = work->field_744[2];
            break;
        }

        work->control.rot.vy = work->control.turn.vy;
        Valcan_800DB500(work);
        Valcan_800DB868(work);
        work->field_758 = 0;
        work->field_75C = 0;
    }
    else
    {
        work->field_75C--;

        if (work->field_75C >= 40)
        {
            work->control.turn.vy += 0x10;
            return;
        }

        if (work->field_75C >= 8)
        {
            work->control.turn.vy -= 0x40;
            return;
        }

        if (work->field_75C >= 0)
        {
            switch (work->field_740)
            {
            case 0:
                work->control.mov.vz =
                    (work->control.mov.vz +
                     work->grid[work->cell.idx.x][work->cell.idx.z][1]) / 2;
                work->control.turn.vy = work->field_744[1];
                work->field_768 = 1;
                break;

            case 1:
                work->control.mov.vz =
                    (work->control.mov.vz +
                     work->grid[work->cell.idx.x][work->cell.idx.z][1]) / 2;
                work->control.turn.vy = work->field_744[0];
                work->field_768 = 0;
                break;

            case 2:
                work->control.mov.vx =
                    (work->control.mov.vx +
                     work->grid[work->cell.idx.x][work->cell.idx.z][0]) / 2;
                work->control.turn.vy = work->field_744[3];
                work->field_768 = 3;
                break;

            case 3:
                work->control.mov.vx =
                    (work->control.mov.vx +
                     work->grid[work->cell.idx.x][work->cell.idx.z][0]) / 2;
                work->control.turn.vy = work->field_744[2];
                work->field_768 = 2;
                break;
            }

            return;
        }

        Valcan_800DB500(work);
        Valcan_800DB868(work);
        work->field_758 = 0;
        work->field_75C = 0;
    }
}

void Valcan_800DBF74(Work *work)
{
    int sqrt;
    int vx, vy;
    int diff1, diff2;
    int tan1, tan2;

    work->control.mov.vx = work->field_7AC.vx;
    work->control.mov.vz = work->field_7AC.vz;

    Valcan_800D9F3C(work, 16);

    diff1 = work->aim_pos.vx - work->shadow_pos.vx;
    diff2 = work->aim_pos.vz - work->shadow_pos.vz;
    tan1 = ratan2(diff1, diff2);

    vy = (tan1 + GV_RandS(64)) & 0xFFF;

    sqrt = SquareRoot0(diff2 * diff2 + diff1 * diff1);
    diff1 = work->aim_pos.vy - work->shadow_pos.vy;
    tan2 = ratan2(sqrt, diff1);

    vx = (GV_RandS(8) + tan2 - 1008) & 0xFFF;

    work->adjust[4].vx = vx - 32;
    work->adjust[7].vx = vx - 64;
    work->adjust[6].vx = vx - 32;
    work->adjust[9].vx = -512;

    work->control.turn.vy = vy;
    work->control.turn.vx = 0;
}

void Valcan_800DC06C(Work *work, int index, int blood_count)
{
    MATRIX mat;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos(&s15c_dword_800C3608);

    s15c_dword_800C3610.vx += GV_RandS(128);
    s15c_dword_800C3610.vy += GV_RandS(128);
    s15c_dword_800C3610.vz += GV_RandS(512);
    DG_RotatePos(&s15c_dword_800C3610);

    ReadRotMatrix(&mat);
    NewBlood(&mat, blood_count);
}

void Valcan_800DC124(Work *work)
{
    if (work->field_94C >= 30 && Valcan_800DA558(work, 1) && (work->field_940 >= 0x1E || work->aim_dis < 0x1F41))
    {
        work->field_7AC = work->control.mov;
        work->field_698 = 0;
        work->field_7B4 = work->control.turn.vy;
        work->field_778 = work->mode;
        work->field_77C = work->action;

        if (work->field_6C0 > 150)
        {
            work->field_6C0 = 0;
            work->field_940 = 0;
            GM_SeSet2(0, 0x3F, SE_EXCLAMATION);
            AN_HeadMark(&work->body.objs->objs[6].world, 0);
            if (work->field_8E4++ >= 2)
            {
                work->field_8E4 = 0;
                switch (work->field_770)
                {
                case 1:
                    GM_SeSetMode(&work->field_910, 0x80, GM_SEMODE_BOMB);
                    break;
                case 2:
                    GM_SeSetMode(&work->field_910, 0x81, GM_SEMODE_BOMB);
                    break;
                case 3:
                    GM_SeSetMode(&work->field_910, 0x89, GM_SEMODE_BOMB);
                    break;
                }
            }
        }

        work->mode = 1;
        work->action = 12;
    }
}

void Valcan_800DC290(Work *work, int arg1, int arg2)
{
    if (work->field_670 != arg1)
    {
        work->field_920 = 0;
        work->field_670 = arg1;
        GM_ConfigObjectAction(&work->body, arg1, 0, 4);
    }
    else if (work->body.is_end == 1)
    {
        work->action = arg2;
    }
}

void Valcan_800DC2EC(Work *work, int action)
{
    work->field_670 = action;
    GM_ConfigObjectAction(&work->body, action, 0, 4);
}

void s15c_crow_800DC318(Work *work)
{
    int tick;

    switch (work->action)
    {
    case 0:
        work->field_91C = 0;

        if (work->life <= 0)
        {
            work->action = 0;
        }
        else
        {
            work->action = 1;
        }
        /* fallthrough */

    case 1:
        Valcan_800DC2EC(work, 0);
        break;

    case 2:
        work->field_91C = 0;
        work->action = 3;
        work->field_694 = GV_RandU(0x80) + 0x40;
        /* fallthrough */

    case 3:
        Valcan_800DC2EC(work, 0);

        if (work->field_694-- <= 0)
        {
            work->action = 4;
        }
        break;

    case 4:
        if (GM_GameLevel == 3 && GV_Time % 256 < 0xF0)
        {
            s15c_crow_800DA990(work);
        }
        else
        {
            work->field_91C = 0;
        }

        work->action = 5;
        Valcan_800DC290(work, 1, 4);

        tick = work->field_920 % 22;

        if (tick == 0)
        {
            GM_SeSetMode(&work->field_910, 0xBE, GM_SEMODE_BOMB);
        }
        else if (tick == 11)
        {
            GM_SeSetMode(&work->field_910, 0xBF, GM_SEMODE_BOMB);
        }

        work->field_920++;
        break;

    case 5:
        Valcan_800DC290(work, 1, 4);
        break;

    case 6:
        Valcan_800DC290(work, 1, 0);
        break;

    case 8:
        work->field_91C = 0;
        work->action = 9;
        Valcan_800DC290(work, 2, 8);

        tick = work->field_920 % 30;

        if (tick == 0)
        {
            GM_SeSetMode(&work->field_910, 0xBE, GM_SEMODE_BOMB);
        }
        else if (tick == 15)
        {
            GM_SeSetMode(&work->field_910, 0xBF, GM_SEMODE_BOMB);
        }

        work->field_920++;
        break;

    case 9:
        Valcan_800DC290(work, 2, 8);
        break;

    case 12:
        work->field_6B0 = 1;
        work->field_694 = 8;
        work->action = 13;
        /* fallthrough */

    case 13:
        Valcan_800DC2EC(work, 3);

        if (work->field_694-- <= 0)
        {
            work->action = 14;
            work->field_6B0 = 2;
        }
        break;

    case 14:
        s15c_crow_800DA990(work);
        Valcan_800DC290(work, 4, 14);
        break;

    case 17:
        work->field_6B0 = 1;
        work->field_694 = 8;
        work->action = 18;
        /* fallthrough */

    case 18:
        Valcan_800DC2EC(work, 3);

        if (work->field_694-- <= 0)
        {
            work->action = 19;
            work->field_6B0 = 2;
        }
        break;

    case 19:
        s15c_crow_800DA990(work);
        Valcan_800DC290(work, 5, 20);
        break;

    case 20:
        work->field_694 = 8;
        work->field_6B0 = 3;
        s15c_crow_800DA990(work);
        work->action = 21;
        break;

    case 21:
        s15c_crow_800DA990(work);
        Valcan_800DC2EC(work, 2);

        if (work->field_694-- <= 0)
        {
            work->field_91C = 0;
            work->field_6B0 = 0;
            work->control.turn.vy = work->field_744[work->field_740];
        }
        break;

    case 22:
        work->field_6B0 = 1;
        work->field_694 = 8;
        work->action = 23;
        /* fallthrough */

    case 23:
        Valcan_800DC2EC(work, 3);

        if (work->field_694-- <= 0)
        {
            work->action = 24;
            work->field_6B0 = 2;
        }
        break;

    case 24:
        s15c_crow_800DA990(work);
        Valcan_800DC290(work, 6, 25);
        break;

    case 25:
        work->field_694 = 8;
        work->field_6B0 = 3;
        s15c_crow_800DA990(work);
        work->action = 26;
        break;

    case 26:
        s15c_crow_800DA990(work);
        Valcan_800DC2EC(work, 2);

        if (work->field_694-- <= 0)
        {
            work->field_91C = 0;
            work->field_6B0 = 0;
            work->control.turn.vy = work->field_744[work->field_740];
        }
        break;

    case 27:
        work->field_91C = 0;
        Valcan_800DC290(work, 7, 28);
        work->field_694 = 8;
        work->field_6B0 = 1;
        break;

    case 28:
        Valcan_800DC2EC(work, 2);

        if (work->field_694-- <= 0)
        {
            work->field_6B0 = 0;
        }
        break;

    case 29:
        work->field_91C = 0;
        Valcan_800DC290(work, 8, 30);
        work->field_694 = 8;
        work->field_6B0 = 1;
        break;

    case 30:
        Valcan_800DC2EC(work, 2);

        if (work->field_694-- <= 0)
        {
            work->field_6B0 = 0;
        }
        break;
    }
}


void s15c_crow_800DC7A0(Work *work)
{
    short level;

    if (work->field_94C < 300)
    {
        work->field_94C++;
    }

    if (work->field_950 >= -9)
    {
        work->field_950--;
    }

    if (work->field_6B0 == 0)
    {
        switch (work->field_770)
        {
        case 1:
            if (work->field_774 != 0)
            {
                work->action = 4;
            }
            else
            {
                work->action = 8;
            }
            break;

        case 2:
            work->action = 4;
            break;

        case 3:
            work->action = 4;
            s15c_crow_800DA990(work);
            break;

        default:
            work->action = 8;
            break;
        }
    }

    if (work->action != 0x11)
    {
        Valcan_800DACCC(work);
    }

    if (work->field_758 == -1)
    {
        if (work->field_770 == 1 && work->field_774 == 0)
        {
            work->field_774 = 1;
        }

        if (work->field_770 == 0)
        {
            level = GM_GameLevel + 1;

            switch (level)
            {
            case 0:
            case 1:
            default:
                if (work->max_life / 2 + 1 >= work->life)
                {
                    work->field_6A4 = 0;
                    work->field_774 = work->field_770;
                    work->field_770 = 1;
                }
                break;

            case 2:
                if (work->max_life * 4 / 5 + 1 >= work->life)
                {
                    work->field_6A4 = 0;
                    work->field_774 = work->field_770;
                    work->field_770 = 1;
                }
                break;

            case 3:
                if (work->max_life * 5 / 6 + 1 >= work->life)
                {
                    work->field_6A4 = 0;
                    work->field_774 = work->field_770;
                    work->field_770 = 1;
                }
                break;

            case 4:
                work->field_6A4 = 0;
                work->field_774 = work->field_770;
                work->field_770 = 3;
                break;
            }
        }

        work->field_758 = Valcan_800DB470(work);

        if (work->field_758 == 0)
        {
            Valcan_800DB500(work);
            Valcan_800DB868(work);
        }

        work->field_75C = 0x48;
        work->field_788 = 1;
    }

    if (work->field_6B0 == 0 || work->field_770 == 3)
    {
        switch (work->field_758)
        {
        case 1:
            s15c_crow_800DBCB4(work);
            break;

        case 2:
            work->field_764 = 1;
            s15c_crow_800DB9F0(work);
            break;

        case 3:
            work->field_764 = -1;
            s15c_crow_800DB9F0(work);
            break;
        }
    }

    if (work->field_788 != 0 && work->field_794 == 1)
    {
        work->field_788 = 2;
    }

    if (work->field_770 == 3)
    {
        work->field_788 = 0;
    }

    if (GM_GameStatus & STATE_STUN)
    {
        GM_SeSet2(0, 0x3F, 0x88);
    }

    switch (work->field_788)
    {
    case 1:
        if (work->field_770 == 2 && work->field_69C > 0)
        {
            switch (work->field_740)
            {
            case 0:
            case 1:
                if (s15c_dword_800E345C[0] >= 2 && work->cell.packed == 1)
                {
                    work->field_828 = 1;
                }
                else
                {
                    work->control.turn.vy = work->field_744[3];
                }
                break;

            case 2:
            case 3:
                if (s15c_dword_800E345C[2] >= 2 && work->cell.packed == 0x20000)
                {
                    work->field_828 = 1;
                }
                else
                {
                    work->control.turn.vy = work->field_744[1];
                }
                break;
            }

            work->control.mov.vz = work->grid[work->cell.idx.x][work->cell.idx.z][1];
            work->control.mov.vx = work->grid[work->cell.idx.x][work->cell.idx.z][0];
        }

        if (work->field_828 == 0)
        {
            if (work->field_8E8++ >= 3)
            {
                work->field_8E8 = 0;

                if (GV_RandU(2) != 0)
                {
                    GM_SeSetMode(&work->field_910, 0x86, GM_SEMODE_BOMB);
                }
                else
                {
                    GM_SeSetMode(&work->field_910, 0x82, GM_SEMODE_BOMB);
                }
            }

            work->action = 0x11;
        }

        work->field_788 = 0;
        break;

    case 2:
        Valcan_800DC124(work);
        break;

    default:
        if (work->field_794 == 1)
        {
            Valcan_800DC124(work);
        }
        break;
    }
}

#define ABS(x) (((x) >= 0) ? (x) : -(x))

static inline int Valcan_800DCC84_helper(int a)
{
    return (a & 0xFFF) + 0x1000;
}

void Valcan_800DCC84(Work *work)
{
    int temp_a0;
    int temp_v0;

    if (work->field_794 == 1)
    {
        work->control.radar_atr |= RADAR_UNK4;
        Valcan_800DBF74(work);
    }
    else if (work->field_698 == 0)
    {
        work->field_698 = GV_RandU(4) + 26;
    }

    if (work->field_698 > 0)
    {
        work->field_698--;
        work->control.turn.vy += GV_RandS(8);
        if (work->field_794 == 1)
        {
            work->field_698 = 0;
        }
    }
    if (work->field_940 > 120)
    {
        if (work->field_770 >= 2 && work->field_770 <= 3)
        {
            temp_a0 = Valcan_800DCC84_helper((unsigned short)work->control.turn.vy);
            temp_v0 = Valcan_800DCC84_helper(work->field_744[work->field_768]);
        }
        else
        {
            temp_a0 = Valcan_800DCC84_helper((unsigned short)work->control.turn.vy);
            temp_v0 = Valcan_800DCC84_helper(work->field_7B4);
        }

        if (ABS(temp_a0 - temp_v0) < 256 || work->field_940 > 600)
        {
            work->field_940 = 0;
            work->field_6C0 = 0;
            work->field_698 = 1;
        }
    }
    if (work->field_698 == 1)
    {
        work->control.radar_atr &= ~RADAR_UNK4;
        Valcan_800D9F3C(work, 16);
        work->field_788 = 0;
        work->field_6B0 = 0;
        work->mode = work->field_778;
        work->action = work->field_77C;
        if (work->field_770 >= 2 && work->field_770 <= 3)
        {
            work->control.turn.vy = work->field_744[work->field_768];
            if (work->field_770 == 2)
            {
                work->field_774 = work->field_770;
            }
        }
        else
        {
            work->control.turn.vy = work->field_7B4;
        }
        work->field_6A4 = 0;
    }
}

void Valcan_800DCE60(Work *work)
{
    if (work->field_698 == 0)
    {
        work->field_7AC = work->control.mov;
        work->field_698 = 35;
        GM_SeSet2(0, 0x3F, 0x8A);
        if (GV_RandU(2) == 0)
        {
            work->action = 27;
        }
        else
        {
            work->action = 29;
        }
    }
    if (work->field_698 > 0)
    {
        work->field_698--;
        if (work->field_698 >= 16 && !(work->field_698 & 1))
        {
            Valcan_800DC06C(work, GV_RandU(8), 2);
        }
        if (work->field_698 == 1)
        {
            work->mode = work->field_780;
            work->action = work->field_784;
            Valcan_800D9F3C(work, 16);
            work->field_6B0 = 0;
            work->field_6A4 = 0;
            work->field_788 = 0;
            if (work->field_770 >= 2 && work->field_770 <= 3)
            {
                work->control.turn.vy = work->field_744[work->field_768];
                if (work->field_770 == 2)
                {
                    work->field_774 = 2;
                }
            }
        }
    }
}

void Valcan_800DCF8C(Work *work)
{
    work->field_798 = work->field_794;
    work->field_794 = Valcan_800DA558(work, 0);
    switch (work->mode)
    {
    case 0:
        work->field_8F0 = 0;
        s15c_crow_800DC7A0(work);
        Valcan_800DA140(work);
        break;
    case 1:
        work->field_8F0 = 1;
        Valcan_800DCC84(work);
        break;
    case 3:
        work->field_8F0 = 0;
        Valcan_800DCE60(work);
        break;
    }
    s15c_crow_800DC318(work);
}

void s15c_crow_800DD03C(Work *work)
{
    SVECTOR diff;
    int     n;

    if (mts_get_tick_count() - work->field_8EC > work->field_8E0)
    {
        work->field_8E0 = GV_RandU(0x40) + 0x78;
        work->field_8EC = mts_get_tick_count();

        if ((u_int)(work->field_770 - 2) < 2 && work->field_924 == -1)
        {
            GM_SeSetMode(&work->field_910, 0x87, GM_SEMODE_BOMB);
        }
    }

    dword_8009F480 = 0;
    dword_8009F49C = 0;
    work->field_6C0++;
    work->aim_dis = Valcan_800D9DC0(work, 0);
    work->shadow_pos = work->control.mov;
    work->shadow_rot = work->control.rot;
    Valcan_800D9F8C(work);

    if (dword_8009F46C[0] == 1 && (GV_PadData[2].status & PAD_TRIANGLE))
    {
        diff.vx = (work->control.mov.vx - svector_8009F478.vx) / 3;
        diff.vy = 0;
        diff.vz = (work->control.mov.vz - svector_8009F478.vz) / 3;
        work->field_910.vx = svector_8009F478.vx + diff.vx;
        work->field_910.vy = svector_8009F478.vy;
        work->field_910.vz = svector_8009F478.vz + diff.vz;
    }
    else
    {
        diff.vx = (work->control.mov.vx - GM_PlayerPosition.vx) / 4;
        diff.vy = 0;
        diff.vz = (work->control.mov.vz - GM_PlayerPosition.vz) / 4;
        work->field_910.vx = GM_PlayerPosition.vx + diff.vx;
        work->field_910.vy = GM_PlayerPosition.vy;
        work->field_910.vz = GM_PlayerPosition.vz + diff.vz;
    }

    Valcan_800DCF8C(work);
    work->field_6A4++;

    if (work->aim_dis >= 0x2329)
    {
        work->field_940++;
    }

    if (work->push_target->damaged & 8)
    {
        work->push_target->damaged &= ~8;
    }

    if ((u_int)((u_short)work->target->a_mode - 3) < 2 && (work->target->damaged & 4))
    {
        work->target->damaged &= ~4;
        work->target->vital = work->life;
    }

    if ((work->target->damaged & 4) && work->field_6B8 == 0)
    {
        work->field_944 = 0;
        work->field_948 = 0;
        work->field_698 = 0;

        if (work->target->damage >= 0x101)
        {
            work->target->damage = 0x100;
        }

        switch (work->target->a_mode)
        {
        case 1:
            work->life -= 8;
            work->target->vital = work->life;
            break;

        case 2:
            work->life -= work->target->damage / 3;
            work->target->vital = work->life;
            break;
        }

        work->field_780 = work->mode;
        work->field_784 = work->action;
        Valcan_800D9F3C(work, 0x10);
        work->field_6B8 = 1;

        if (GM_GameLevel != 3)
        {
            work->mode = 3;
        }
        else
        {
            GM_SeSet2(0, 0x3F, 0x8A);
        }

        work->field_924 = 0x5A;
        work->field_6A4 = 0;
        work->field_69C = 0;
        work->field_93C = 1;
    }

    work->target->damage = 0;
    if (work->field_924 > 0)
    {
        work->field_924--;
        n = 0x5A - work->field_924;

        if (GM_GameLevel == 3 && n < 0x1E)
        {
            Valcan_800DC06C(work, GV_RandU(8), 2);
        }

        work->field_944 = n * 15000 / 90;
        work->field_948 = n * 1024 / 90;
    }

    if (work->field_924 == 0)
    {
        work->field_924 = -1;
        work->target->damaged &= ~4;
        work->field_944 = 0x3A98;
        work->field_6B8 = 0;
        work->field_948 = 0x400;
    }

    if (work->life <= 0 && work->field_81C == 0)
    {
        Valcan_800DC06C(work, GV_RandU(8), 2);
        work->field_81C = 1;
    }
    else
    {
        Valcan_800D9D90(work);
    }
}

void Valcan_800DD578(Work *work)
{
    work->field_69C = 0;
    work->path_index = 0;
    work->sweep_time = 0;
    work->field_698 = 0;
    work->field_6A4 = 0;
    work->field_694 = 0;
    work->field_6B8 = 0;
    work->field_6B0 = 0;
    work->field_670 = 9;
    GM_ConfigMotionAdjust(&work->body, work->adjust);
    Valcan_800D9F3C(work, 16);
    Valcan_800DC2EC(work, 0);
    work->field_758 = 0;
    work->field_744[0] = 3072;
    work->field_744[1] = 1024;
    work->field_744[2] = 2048;
    work->field_744[3] = 0;
    Valcan_800DB868(work);
    work->field_768 = work->field_740;
    work->control.rot.vx = 0;
    work->control.rot.vy = work->field_744[work->field_740];
    work->control.rot.vz = 0;
    work->control.turn.vx = 0;
    work->control.turn.vy = work->field_744[work->field_740];
    work->control.turn.vz = 0;
    work->field_76C = 2800;
    work->field_774 = 0;
    work->field_778 = 0;
    work->field_77C = 0;
    work->field_770 = 0;
    work->field_788 = 0;
    work->field_78C = 0;
    work->field_790 = 0;
    work->field_794 = 0;
    work->field_798 = 0;
    work->field_81C = 0;
    work->field_828 = 0;
    work->field_830 = 0;
    work->field_834 = 0;
    work->field_83C = 0;
    work->field_840 = 0;
    work->field_8F0 = 0;
    work->field_90C = 0;
    work->field_918 = 0;
    work->field_91C = 0;
    work->field_920 = 0;
    work->field_924 = -1;
    work->barrel_speed = 0;
    work->barrel_tick = 0;
    work->field_6C0 = 1000;
    work->field_93C = 0;
    work->field_940 = 0;
    work->field_8DC = 0;
    work->field_8E4 = 0;
    work->field_8E8 = 0;
    work->field_8E0 = GV_RandU(16) + 40;
    work->field_8EC = mts_get_tick_count();
    work->barrel_tick = mts_get_tick_count();
    work->field_94C = 0;
    work->path[0][0] = 0;
    work->path[0][1] = 3;
    work->path[1][0] = 1;
    work->path[1][1] = 1;
    work->path[2][0] = 2;
    work->path[2][1] = 2;
    work->path[3][0] = 3;
    work->path[3][1] = 3;
    work->path[4][0] = 1;
    work->path[4][1] = 1;
    work->path[5][0] = 0;
    work->path[5][1] = 0;
    work->path[6][0] = 2;
    work->path[6][1] = 2;
    work->path[7][0] = 3;
    work->path[7][1] = 0;
    work->path[8][0] = 2;
    work->path[8][1] = 2;
    work->path[9][0] = 3;
    work->path[9][1] = 3;
    work->path[10][0] = 1;
    work->path[10][1] = 1;
    work->path[11][0] = 2;
    work->path[11][1] = 0;
    work->path[12][0] = 0;
    work->path[12][1] = 3;
    work->path[13][0] = 3;
    work->path[13][1] = 0;
    work->path[14][0] = 0;
    work->path[14][1] = 1;
    work->path[15][0] = 2;
    work->path[15][1] = 2;
    work->path[16][0] = 1;
    work->path[16][1] = 1;
    work->path[17][0] = 0;
    work->path[17][1] = 3;
    work->path[18][0] = 3;
    work->path[18][1] = 2;
    work->path[19][0] = 1;
    work->path[19][1] = 3;
    work->path[20][0] = 3;
    work->path[20][1] = 0;
    work->mode = 0;
    work->action = 0;
    work->field_944 = 15000;
    work->field_948 = 1024;
    Valcan_800D9D90(work);
    GM_AlertMode = 4;
}
