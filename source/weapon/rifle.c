#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "linkvar.h"
#include "sd/g_sound.h"

extern GM_CAMERA GM_Camera;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern int      DG_CurrentGroupID;

extern void *NewBullet(MATRIX *pMtx, int a2, int a3, int noiseLen);

/*---------------------------------------------------------------------------*/
// PSG1 Rifle

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define RIFLE_MODEL     GV_StrCode("rifle")

#define SEGMENT_ATR     ( HZD_SEG_NO_PLAYER )

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

#define MAGAZINE_SIZE   5

typedef struct _Work
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
} Work;

/*---------------------------------------------------------------------------*/

STATIC SVECTOR dword_8009F41C[2] = {
    { 0, 0,    0, 0 },
    { 0, 0, 3000, 0 }
};

static int GetZoomLimit(void)
{
    MATRIX *eye;
    MATRIX mtx;
    SVECTOR vec[2];
    int var_s2;
    int length;

    if ((GM_GameStatus < 0) || !GM_PlayerControl)
    {
        eye = &DG_Chanl(0)->field_30_eye;
    }
    else
    {
        eye = &mtx;
        mtx = GM_PlayerBody->objs->world;
        mtx.t[0] = gUnkCameraStruct_800B77B8.eye.vx;
        mtx.t[1] = gUnkCameraStruct_800B77B8.eye.vy;
        mtx.t[2] = gUnkCameraStruct_800B77B8.eye.vz;
    }

    DG_SetPos(eye);
    DG_PutVector(dword_8009F41C, vec, 2);

    var_s2 = 0;

    if (HZD_LineCheck(GM_PlayerControl->map->hzd, &vec[0], &vec[1], HZD_CHECK_ALL, SEGMENT_ATR))
    {
        HZD_LineNearVec(&vec[1]);
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

STATIC SVECTOR svector_800AB8D4 = { 5, 300, 80, 0 };

static void Act(Work *work)
{
    MATRIX mtx, mtx2;
    SVECTOR vec;

    int temp_s1;
    int temp_s2;
    int temp_v0;
    int temp_v0_2;
    short zoomLevel;

    GM_CurrentMap = work->control->map->index;
    DG_GroupObjs(work->object.objs, DG_CurrentGroupID);

    if (!(work->parent->objs->flag & DG_FLAG_INVISIBLE))
    {
        DG_VisibleObjs(work->object.objs);
        GM_Camera.zoom = 320;
        return;
    }

    DG_InvisibleObjs(work->object.objs);

    temp_s2 = *work->flags;

    if ((GM_Camera.first_person == 1) &&
        !work->field_5c &&
        (temp_s2 & 1) &&
        (work->parent->objs->flag & DG_FLAG_INVISIBLE))
    {
        work->field_5c = (void *)NewRifleSight(1);
        sd_set_cli(0x01ffff20, SD_ASYNC);
    }

    if (temp_s2 & 1)
    {
        temp_v0 = work->field_58;
        work->field_58++;

        if (temp_v0 >= 9)
        {
            temp_v0_2 = GetZoomLimit();
            zoomLevel = GM_Camera.zoom;

            if (zoomLevel < temp_v0_2)
            {
                GM_Camera.zoom += GM_Camera.zoom / 3;

                if (temp_v0_2 < GM_Camera.zoom)
                {
                    GM_Camera.zoom = temp_v0_2;
                }
            }
            else
            {
                GM_Camera.zoom = GV_NearExp4(zoomLevel, temp_v0_2);
            }
        }
    }

    temp_s1 = GM_Magazine;

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

        NewBullet(&mtx, work->which_side, 0, 2);

        GM_SeSet2(0, 63, SE_PSG1_SHOT);
        GM_SetNoise(100, 2, &work->control->mov);

        GM_Magazine = --temp_s1;
        GM_Weapons[WP_Rifle]--;
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);

    if (GM_CurrentWeaponId != WP_Rifle)
    {
        GM_Camera.zoom = 320;
    }

    sd_set_cli(0x01ffff21, SD_ASYNC);

    if ((GV_ACT *)work->field_5c)
    {
        GV_DestroyOtherActor((GV_ACT *)work->field_5c);
    }
}

static int GetResources(Work *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *obj = &work->object;

    GM_InitObjectNoRots(obj, RIFLE_MODEL, BODY_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, parent, num_parent);
    work->field_5c = 0;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewRifle(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    Work *work;
    int mag_size, ammo;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "rifle.c");

        if (GetResources(work, parent, num_parent) < 0)
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

    mag_size = GM_Magazine ? (MAGAZINE_SIZE + 1) : MAGAZINE_SIZE;
    ammo = GM_Weapons[WP_Rifle];

    if (mag_size > 0 && mag_size < ammo)
    {
        ammo = mag_size;
    }

    GM_MagazineMax = mag_size;
    GM_Magazine = ammo;

    return (void *)work;
}
