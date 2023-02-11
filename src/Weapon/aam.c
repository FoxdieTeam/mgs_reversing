#include "aam.h"
#include "Bullet/amissile.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/target.h"
#include "Game/vibrate.h"
#include "Game/linkvarbuf.h"

// stinger

extern char  aStinger_0[]; // = "stinger"
extern char  aAamC[];      // = "aam.c"
extern short d_800AB9EC_mag_size;
extern short d_800ABA2C_ammo;

extern int dword_8009F490;

extern UnkCameraStruct gUnkCameraStruct_800B77B8;

extern int DG_CurrentGroupID_800AB968;
extern int GM_CurrentMap_800AB9B0;

extern GM_Target *target_800BDF00;

extern GM_Target *StnTarget_800AB8A0;
GM_Target *StnTarget_800AB8A0;

extern int dword_800AB8A4;

SVECTOR svector_800AB8A4;

extern char byte_8009F40C[];
extern char byte_8009F414[];

void aam_act_800670CC(Actor_Aam *actor)
{
    int sVar3;
    int iVar6;
    unsigned int uVar7;
    MATRIX MStack88;
    MATRIX MStack56;
    SVECTOR local_18;

    if (!actor->field_5C_stnsight)
    {
        actor->field_5C_stnsight = NewStnSight_800693E0(actor->field_44_ctrl);
    }

    GM_CurrentMap_800AB9B0 = actor->field_44_ctrl->field_2C_map->field_0_map_index_bit;
    DG_GroupObjs(actor->field_20_obj.objs, DG_CurrentGroupID_800AB968);

    if (actor->field_48_parent_obj->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(actor->field_20_obj.objs);
    }
    else
    {
        DG_VisibleObjs(actor->field_20_obj.objs);
    }

    iVar6 = actor->field_58;
    uVar7 = *actor->field_50;

    if (iVar6 > 0)
    {
        if (iVar6 >= 27)
        {
            gUnkCameraStruct_800B77B8.field_28.vx += (30 - iVar6) * -36;
        }
        else if (iVar6 > 14)
        {
            gUnkCameraStruct_800B77B8.field_28.vx += (iVar6 - 12) * -12;
        }

        actor->field_58--;
    }

    if (!actor->field_58 && (uVar7 & 2) && !dword_8009F490)
    {
        actor->field_58 = 30;

        sVar3 = GM_Weapons[WEAPON_STINGER];

        if (sVar3 > 0)
        {
            if (target_800BDF00 != 0)
            {
                StnTarget_800AB8A0 = target_800BDF00;
            }
            else
            {
                StnTarget_800AB8A0 = 0;
            }

            local_18.vx = actor->field_44_ctrl->field_8_rotator.vx - 1024;
            local_18.vy = actor->field_44_ctrl->field_8_rotator.vy;
            local_18.vz = 0;

            RotMatrixYXZ_80093798(&local_18, &MStack88);
            local_18.vx = 0;
            DG_SetPos2_8001BC8C(&gUnkCameraStruct_800B77B8.field_0, &local_18);
            DG_MovePos_8001BD20(&svector_800AB8A4);
            ReadRotMatrix_80092DD8(&MStack56);

            MStack88.t[0] = MStack56.t[0];
            MStack88.t[1] = MStack56.t[1];
            MStack88.t[2] = MStack56.t[2];

            if (NewAMissile_8006DC50(&MStack88, actor->field_54))
            {
                GM_Weapons[WEAPON_STINGER] = --sVar3;
                GM_SeSet_80032858(&actor->field_44_ctrl->field_0_position, 0x4c);
                GM_SetNoise(200, 2, &actor->field_44_ctrl->field_0_position);

                vibrate_init2_8005D58C(byte_8009F40C, 1);
                vibrate_init2_8005D58C(byte_8009F414, 2);
            }
        }
    }
}

void aam_kill_800673B0(Actor_Aam *actor)
{
    GM_FreeObject_80034BF8(&actor->field_20_obj);
    if (actor->field_5C_stnsight)
    {
        GV_DestroyOtherActor_800151D8(&actor->field_5C_stnsight->field_0_actor);
    }
}

int aam_loader_800673F0(Actor_Aam *actor_aam, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_aam->field_20_obj;

    int id;
    actor_aam->field_5C_stnsight = 0;

    id = GV_StrCode_80016CCC(aStinger_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, id, WEAPON_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}

Actor_Aam * NewAAM_80067480(GM_Control *ctrl, OBJECT *parent_object, int num_parent, void *a4, int a5)
{
    Actor_Aam *actor_aam = (Actor_Aam *)GV_NewActor_800150E4(6, sizeof(Actor_Aam));
    if (actor_aam)
    {
        GV_SetNamedActor_8001514C(&actor_aam->field_0_actor, (TActorFunction)aam_act_800670CC,
                                  (TActorFunction)aam_kill_800673B0, aAamC);
        if (aam_loader_800673F0(actor_aam, parent_object, num_parent) < 0)
        {
            GV_DestroyActor_800151C8(&actor_aam->field_0_actor);
            return 0;
        }

        actor_aam->field_44_ctrl = ctrl;
        actor_aam->field_48_parent_obj = parent_object;
        actor_aam->field_4C_num_parent = num_parent;
        actor_aam->field_50 = a4;
        actor_aam->field_54 = a5;
        actor_aam->field_58 = 0;
    }

    d_800ABA2C_ammo = 0;
    d_800AB9EC_mag_size = 0;

    return actor_aam;
}
