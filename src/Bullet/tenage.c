#include "tenage.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "chara/snake/sna_init.h"
#include "Bullet/blast.h"
#include "Game/object.h"
#include "Game/control.h"
#include "Okajima/chafgrnd.h"
#include "Okajima/stngrnd.h"
#include "Weapon/weapon.h"
#include "SD/g_sound.h"
#include "strcode.h"

extern int            GM_PlayerStatus;
extern int            dword_800BDD28;
extern BLAST_DATA     blast_data_8009F4B8[8];
extern SVECTOR        GM_PlayerPosition_800ABA10;
extern CONTROL       *tenage_ctrls_800BDD30[16];
extern int            tenage_ctrls_count_800BDD70;

/*---------------------------------------------------------------------------*/
// the projectile for all types of grenades

typedef struct TenageWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS object;
    MATRIX         light[2];
    int            fuse_time;
    int            bounces;
    SVECTOR        step;
    int            type;
    int            homing_arg3;
    int            do_sound;
    int            side;
    int            control_index;
} TenageWork;

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

/*---------------------------------------------------------------------------*/

STATIC void TenageAct(TenageWork *work)
{
    MATRIX rotation;
    SVECTOR vec;
    CONTROL *control;
#ifdef VR_EXE
    int vy, level;
#endif

    work->control.step = work->step;

    control = &work->control;

    if (GM_lpfnBombHoming)
    {
        GM_lpfnBombHoming(control, work->fuse_time, &work->homing_arg3);
    }

    if ((work->control.mov.pad != 0) || (GM_GameStatus < 0))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    work->step = work->control.step;

#ifdef VR_EXE
    vy = control->step.vy;
    control->step.vy = 0;
#endif

    GM_ActControl(control);

#ifdef VR_EXE
    vy = vy + control->mov.vy;
    level = control->levels[0] + 100;
    if (level >= vy)
    {
        control->field_57 |= 1;
        vy = level;
    }
    else
    {
        level = control->levels[1] - 100;
        if (level <= vy)
        {
            control->field_57 |= 2;
            vy = level;
        }
    }
    control->mov.vy = vy;
    DG_SetPos2(&control->mov, &control->rot);
#endif

    GM_ActObject2((OBJECT *)&work->object);
    DG_GetLightMatrix(&control->mov, work->light);

    if (!(GM_GameStatus & (STATE_PADRELEASE | STATE_PADDEMO | STATE_DEMO)) && !(GM_PlayerStatus & PLAYER_PAD_OFF))
    {
        work->fuse_time--;
    }

#ifdef VR_EXE
    else if ((GM_GameStatus & (STATE_PADRELEASE | STATE_PADDEMO)) == STATE_PADDEMO && !(GM_PlayerStatus & PLAYER_PAD_OFF))
    {
        work->fuse_time--;
    }
#endif

    if (work->fuse_time <= 0 || dword_800BDD28 == 1)
    {
        ReadRotMatrix(&rotation);

        GM_uBombHoming = work->homing_arg3;

        switch (work->type)
        {
        case GRD_STUN:
            NewStanBlast(&rotation);
            break;

        case GRD_CHAFF:
            NewChaffGrd(&rotation);
            break;

        case GRD_TBOMB:
            NewBlast2(&rotation, &blast_data_8009F4B8[6], work->do_sound, work->side);
            break;

        default:
            NewBlast2(&rotation, &blast_data_8009F4B8[0], work->do_sound, work->side);
            break;
        }

        HZD_8002A258(work->control.map->hzd, &work->control.event);
        GV_DestroyActor(&work->actor);

        GM_uBombHoming = 0;
        return;
    }

    if (control->field_57 && work->step.vy <= 0)
    {
        work->step.vy = -work->step.vy / 8;
        work->step.vz /= 4;
        work->step.vx /= 4;

        if (work->step.vy < 5)
        {
            work->step = DG_ZeroVector;
        }

        if (++work->bounces < 3)
        {
            if (!GM_lpfnBombBound || !GM_lpfnBombBound(0, control, &work->homing_arg3))
            {
                GM_SeSet(&control->mov, SE_GRENADE_HIT);
            }

            if (work->do_sound != 0)
            {
                GM_SetNoise(128, 12, &control->mov);
            }
        }
    }
    else
    {
        work->step.vy -= 16;
    }

    if (control->field_58 > 0 && GM_CheckControlTouches(control, 300))
    {
        HZD_800272E0(control->field_70[0], &vec);
        DG_ReflectVector(&vec, &work->step, &work->step);

        work->step.vx /= 4;
        work->step.vz /= 4;

        if (++work->bounces < 3)
        {
            if (!GM_lpfnBombBound || !GM_lpfnBombBound(1, control, &work->homing_arg3))
            {
                GM_SeSet(&control->mov, SE_GRENADE_HIT);
            }
        }
    }
}

STATIC void TenageDie(TenageWork *work)
{
    GM_FreeControl(&work->control);
    GM_ClearBulName(work->control.name);
    GM_FreeObject((OBJECT *)&work->object);

    if (work->control_index >= 0)
    {
        tenage_ctrls_800BDD30[work->control_index] = 0;
        tenage_ctrls_count_800BDD70--;
    }
}

STATIC int TenageGetNextControl(void)
{
    int i;

    for (i = 0; i < (int)(sizeof(tenage_ctrls_800BDD30) / sizeof(CONTROL *)); i++)
    {
        if (tenage_ctrls_800BDD30[i] == 0)
        {
            return i;
        }
    }

    return -1;
}

STATIC int TenageGetResources(TenageWork *work, SVECTOR *pos, SVECTOR *step, int type, int model, int int_5, int side)
{
    CONTROL *control;

    control = &work->control;
    if (GM_InitControl(control, GM_Next_BulName_8004FBA0(), 0) >= 0)
    {
        if (int_5 != 0)
        {
            GM_ConfigControlHazard(control, 100, 50, 50);
        }
        else
        {
            GM_ConfigControlHazard(control, 100, -1, -1);
        }
        control->field_59 = 4;
        if (side == PLAYER_SIDE)
        {
            control->mov = GM_PlayerPosition_800ABA10;
            GM_ConfigControlTrapCheck(control);
            GM_ActControl(control);
        }
        GM_ConfigControlVector(control, pos, (SVECTOR *)&DG_ZeroVector);
        work->step = *step;
        GM_InitObjectNoRots(&work->object, model, BODY_FLAG, 0);
        if (work->object.objs)
        {
            DG_SetPos2(&control->mov, &control->rot);
            DG_PutObjs((work->object).objs);
            GM_ConfigObjectLight((OBJECT *)&work->object, work->light);

            work->control_index = TenageGetNextControl();
            if (work->control_index >= 0)
            {
                tenage_ctrls_800BDD30[work->control_index] = control;
                control->mov.pad = 0;
                tenage_ctrls_count_800BDD70 = tenage_ctrls_count_800BDD70 + 1;
                return 0;
            }
        }
    }
    return -1;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewTenage(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model)
{
    TenageWork *work;

    if (tenage_ctrls_count_800BDD70 == 16)
    {
        return NULL;
    }

    work = GV_NewActor(GV_ACTOR_LEVEL5, sizeof(TenageWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, TenageAct, TenageDie, "tenage.c");

        if (TenageGetResources(work, pos, step, type, model, 1, PLAYER_SIDE) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->fuse_time = fuse_time;
        work->bounces = 0;
        work->type = type;
        work->do_sound = 1;
        work->side = PLAYER_SIDE;
    }

    return &work->actor;
}

GV_ACT *NewTenage2(SVECTOR *pos, SVECTOR *step, int fuse_time)
{
    return NewTenage(pos, step, fuse_time, GRD_GRENADE, KMD_GRENADE);
}

// enemy's grenades, probably
GV_ACT *NewTenage3(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model, int do_sound, int player_side)
{
    TenageWork *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(TenageWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)TenageAct,
                         (GV_ACTFUNC)TenageDie, "tenage.c");

        if (TenageGetResources(work, pos, step, type, model, 0, ENEMY_SIDE) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->fuse_time = fuse_time;
        work->bounces = 0;
        work->type = type;
        work->do_sound = do_sound & 1;
        work->side = player_side & 1;
    }

    return (GV_ACT *)work;
}
