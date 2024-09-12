#include "aam.h"
#include "stnsight.h"

#include "common.h"
#include "Bullet/amissile.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/target.h"
#include "Game/vibrate.h"
#include "Game/linkvarbuf.h"
#include "Weapon/weapon.h"
#include "SD/g_sound.h"

// stinger

extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;

extern int amissile_alive_8009F490;

extern UnkCameraStruct gUnkCameraStruct_800B77B8;

extern int DG_CurrentGroupID_800AB968;
extern int GM_CurrentMap_800AB9B0;

extern TARGET *target_800BDF00;
extern int dword_800AB8A4;

TARGET *StnTarget_800AB8A0 = NULL;
SVECTOR svector_800AB8A4 = {-300, 200, 0, 0};

char byte_8009F40C[] = {0, 2, 127, 4, 0};
char byte_8009F414[] = {145, 4, 75, 10, 0};

void AamAct_800670CC(AamWork *work)
{
    MATRIX       world;
    MATRIX       pos;
    SVECTOR      rot;
    unsigned int trigger;
    int          ammo;

    if (!work->sight)
    {
        work->sight = NewStnSight_800693E0(work->control);
    }

    GM_SetCurrentMap(work->control->map->index);
    DG_GroupObjs(work->object.objs, DG_CurrentGroupID_800AB968);

    if (work->parent->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else
    {
        DG_VisibleObjs(work->object.objs);
    }


    trigger = *work->trigger;

    if (work->cooldown > 0)
    {
        if (work->cooldown >= 27)
        {
            gUnkCameraStruct_800B77B8.rotate2.vx += (30 - work->cooldown) * -36;
        }
        else if (work->cooldown > 14)
        {
            gUnkCameraStruct_800B77B8.rotate2.vx += (work->cooldown - 12) * -12;
        }

        work->cooldown--;
    }

    if ((work->cooldown == 0) && (trigger & WEAPON_TRIG) && !amissile_alive_8009F490)
    {
        work->cooldown = 30;

        ammo = GM_Weapons[WEAPON_STINGER];

        if (ammo > 0)
        {
            if (target_800BDF00 != 0)
            {
                StnTarget_800AB8A0 = target_800BDF00;
            }
            else
            {
                StnTarget_800AB8A0 = 0;
            }

            rot.vx = work->control->rot.vx - 1024;
            rot.vy = work->control->rot.vy;
            rot.vz = 0;

            RotMatrixYXZ(&rot, &world);
            rot.vx = 0;
            DG_SetPos2(&gUnkCameraStruct_800B77B8.eye, &rot);
            DG_MovePos(&svector_800AB8A4);
            ReadRotMatrix(&pos);

            world.t[0] = pos.t[0];
            world.t[1] = pos.t[1];
            world.t[2] = pos.t[2];

            if (NewAMissile_8006DC50(&world, work->side))
            {
                GM_Weapons[WEAPON_STINGER] = --ammo;

                GM_SeSet(&work->control->mov, SE_MISSILE_FIRED);
                GM_SetNoise(200, 2, &work->control->mov);

                NewPadVibration_8005D58C(byte_8009F40C, 1);
                NewPadVibration_8005D58C(byte_8009F414, 2);
            }
        }
    }
}

void AamDie_800673B0(AamWork *work)
{
    GM_FreeObject((OBJECT *)&work->object);

    if (work->sight)
    {
        GV_DestroyOtherActor(work->sight);
    }
}

int AamGetResources_800673F0(AamWork *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *object;
    int             model;

    object = &work->object;
    work->sight = NULL;

    model = GV_StrCode("stinger");
    GM_InitObjectNoRots(object, model, WEAPON_FLAG, 0);

    if (!object->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)object, parent, num_parent);
    return 0;
}

GV_ACT *NewAAM_80067480(CONTROL *ctrl, OBJECT *parent, int num_parent, unsigned int *trigger, int side)
{
    AamWork *work;

    work = (AamWork *)GV_NewActor(6, sizeof(AamWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)AamAct_800670CC, (TActorFunction)AamDie_800673B0, "aam.c");

        if (AamGetResources_800673F0(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = ctrl;
        work->parent = parent;
        work->num_parent = num_parent;
        work->trigger = trigger;
        work->side = side;
        work->cooldown = 0;
    }

    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;

    return &work->actor;
}
