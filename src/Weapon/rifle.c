#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "Game/object.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"

extern GM_Camera GM_Camera_800B77E8;

extern int              GM_GameStatus;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern OBJECT          *GM_PlayerBody_800ABA20;

extern int      DG_CurrentGroupID_800AB968;
extern int      GM_CurrentMap_800AB9B0;
extern short    GM_Magazine_800AB9EC;
extern short    GM_MagazineMax_800ABA2C;

extern GV_ACT *bullet_init_80076584(MATRIX *pMtx, int a2, int a3, int noiseLen);

/*---------------------------------------------------------------------------*/
// PSG1 Rifle

typedef struct _RifleWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent;
    int            num_parent;
    int           *flags;
    int            which_side;
    int            field_58;
    void          *field_5c;
} RifleWork;

#define EXEC_LEVEL      6
#define MAGAZINE_SIZE   5

/*---------------------------------------------------------------------------*/

SVECTOR dword_8009F41C[2] = {
    { 0, 0,    0, 0 },
    { 0, 0, 3000, 0 }
};

STATIC int RifleGetZoomLength(void)
{
    MATRIX *pMtx;
    MATRIX mtx;
    SVECTOR vec[2];
    int var_s2;
    int length;

    if ((GM_GameStatus < 0) || !GM_PlayerControl_800AB9F4)
    {
        pMtx = &DG_Chanl(0)->field_30_eye;
    }
    else
    {
        pMtx = &mtx;
        mtx = GM_PlayerBody_800ABA20->objs->world;
        mtx.t[0] = gUnkCameraStruct_800B77B8.eye.vx;
        mtx.t[1] = gUnkCameraStruct_800B77B8.eye.vy;
        mtx.t[2] = gUnkCameraStruct_800B77B8.eye.vz;
    }

    DG_SetPos(pMtx);
    DG_PutVector(dword_8009F41C, vec, 2);

    var_s2 = 0;

    if (HZD_80028454(GM_PlayerControl_800AB9F4->map->hzd, &vec[0], &vec[1], 15, 4))
    {
        HZD_GetSpadVector(&vec[1]);
        var_s2 = 1;
    }

    length = 3000;

    if (var_s2)
    {
        GV_SubVec3(&vec[1], &vec[0], &vec[0]);
        length = GV_VecLen3(&vec[0]);
    }

    if (length < 1000)
    {
        length = 320;
    }

    return length;
}

/*---------------------------------------------------------------------------*/

SVECTOR svector_800AB8D4 = { 5, 300, 80, 0 };

STATIC void RifleAct(RifleWork *work)
{
    MATRIX mtx, mtx2;
    SVECTOR vec;

    int temp_s1;
    int temp_s2;
    int temp_v0;
    int temp_v0_2;
    short zoomLevel;

    GM_CurrentMap_800AB9B0 = work->control->map->index;
    DG_GroupObjs(work->object.objs, DG_CurrentGroupID_800AB968);

    if (!(work->parent->objs->flag & DG_FLAG_INVISIBLE))
    {
        DG_VisibleObjs(work->object.objs);
        GM_Camera_800B77E8.zoom = 320;
        return;
    }

    DG_InvisibleObjs(work->object.objs);

    temp_s2 = *work->flags;

    if ((GM_Camera_800B77E8.first_person == 1) &&
        !work->field_5c &&
        (temp_s2 & 1) &&
        (work->parent->objs->flag & DG_FLAG_INVISIBLE))
    {
        work->field_5c = (void *)NewRifleSight(1);
        sd_set_cli(0x01ffff20, 0);
    }

    if (temp_s2 & 1)
    {
        temp_v0 = work->field_58;
        work->field_58++;

        if (temp_v0 >= 9)
        {
            temp_v0_2 = RifleGetZoomLength();
            zoomLevel = GM_Camera_800B77E8.zoom;

            if (zoomLevel < temp_v0_2)
            {
                GM_Camera_800B77E8.zoom += GM_Camera_800B77E8.zoom / 3;

                if (temp_v0_2 < GM_Camera_800B77E8.zoom)
                {
                    GM_Camera_800B77E8.zoom = temp_v0_2;
                }
            }
            else
            {
                GM_Camera_800B77E8.zoom = GV_NearExp4(zoomLevel, temp_v0_2);
            }
        }
    }

    temp_s1 = GM_Magazine_800AB9EC;

    if (!temp_s1 && (temp_s2 & 2))
    {
        GM_SeSet(&work->control->mov, SE_KARASHT);
        GM_SetNoise(5, 2, &work->control->mov);
    }
    else if ((temp_s1 > 0) && (temp_s2 & 2))
    {
        vec.vx = work->control->rot.vx - 0x400;
        vec.vy = work->control->rot.vy;
        vec.vz = 0;

        RotMatrixYXZ(&vec, &mtx);

        DG_SetPos(&work->parent->objs->objs[work->num_parent].world);
        DG_MovePos(&svector_800AB8D4);

        ReadRotMatrix(&mtx2);

        mtx.t[0] = mtx2.t[0];
        mtx.t[1] = mtx2.t[1];
        mtx.t[2] = mtx2.t[2];

        bullet_init_80076584(&mtx, work->which_side, 0, 2);

        GM_SeSet2(0, 63, SE_PSG1_SHOT);
        GM_SetNoise(100, 2, &work->control->mov);

        GM_Magazine_800AB9EC = --temp_s1;
        GM_Weapons[WEAPON_PSG1]--;
    }
}

STATIC void RifleDie(RifleWork *work)
{
    GM_FreeObject((OBJECT *)&work->object);

    if (GM_CurrentWeaponId != WEAPON_PSG1)
    {
        GM_Camera_800B77E8.zoom = 320;
    }

    sd_set_cli(0x01ffff21, 0);

    if ((GV_ACT *)work->field_5c)
    {
        GV_DestroyOtherActor((GV_ACT *)work->field_5c);
    }
}

STATIC int RifleGetResources(RifleWork *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *obj = &work->object;

    int id = GV_StrCode("rifle");
    GM_InitObjectNoRots(obj, id, WEAPON_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, parent, num_parent);
    work->field_5c = 0;

    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewRifle(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    RifleWork  *work;
    int         mag_size, ammo;

    work = (RifleWork *)GV_NewActor(EXEC_LEVEL, sizeof(RifleWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)&RifleAct,
                         (GV_ACTFUNC)&RifleDie, "rifle.c");

        if (RifleGetResources(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->flags = flags;
        work->which_side = which_side;
        work->field_58 = 0;
    }

    mag_size = GM_Magazine_800AB9EC ? (MAGAZINE_SIZE + 1) : MAGAZINE_SIZE;
    ammo = GM_Weapons[WEAPON_PSG1];

    if (mag_size > 0 && mag_size < ammo)
    {
        ammo = mag_size;
    }

    GM_MagazineMax_800ABA2C = mag_size;
    GM_Magazine_800AB9EC = ammo;

    return &work->actor;
}
