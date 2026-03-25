#include "linkvar.h"
#include "game/game.h"
#include "libgcl/libgcl.h"

typedef struct _S11ObjsObj1
{
    OBJECT  object;
    SVECTOR pos;
    SVECTOR rot;
    SVECTOR step;
    SVECTOR turn;
    int     time;
    int     state;
} S11ObjsObj1;

typedef struct _S11ObjsObj2
{
    OBJECT  object;
    SVECTOR pos;
    SVECTOR rot;
    SVECTOR step;
    SVECTOR turn;
    int     time;
    VECTOR  scale;
    MATRIX  light[2];
    int     state;
} S11ObjsObj2;

typedef struct _Work
{
    GV_ACT      actor;
    int         map;
    int         name;
    S11ObjsObj1 obj1[15];
    S11ObjsObj2 obj2[16];
    int         f259C;
    int         f25A0;
    int         f25A4;
    int         f25A8;
    int         f25AC;
} Work;

#define EXEC_LEVEL      5
#define MODEL_FLAG      ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_ONEPIECE )

#define ATTACK_DAMAGE   (256)

DG_OBJS *Takabe_MakePreshade(int model, LIT *lit);

SVECTOR positions[] =
{
    {0xFA24, 0x0000, 0xFA24},
    {0xFA24, 0x0000, 0xFA24},
    {0xF9A7, 0x0000, 0x0659},
    {0x06D6, 0x0BB8, 0x0FA0},
    {0x222E, 0x0BB8, 0x0FA0},
    {0x1A5E, 0x07D0, 0x1D4C},
    {0x1A5E, 0x0FA0, 0x1D4C},
    {0x02EE, 0x09C4, 0x1D4C},
    {0x0ABE, 0x0DAC, 0x2AF8},
    {0x04E2, 0x0000, 0x2328},
    {0xFD12, 0x03E8, 0x1D4C},
    {0x109A, 0x03E8, 0x1D4C},
    {0x1482, 0x03E8, 0x157C},
    {0x04E2, 0x03E8, 0x1770},
    {0xF542, 0x0000, 0x2CEC}
};

SVECTOR rotations[] =
{
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {4096, 0, 4096},
    {4096, 0, 0}
};

static void InitPreshadeObject(OBJECT *object, int model, u_long flag)
{
    GV_ZeroMemory(object, sizeof(OBJECT));

    object->flag = flag;
    object->map_name = GM_CurrentMap;
    object->objs = Takabe_MakePreshade(model, GM_GetMap(GM_CurrentMap)->lit);
}

static int CheckMessages(u_short name, int n_hashes, u_short *hashes)
{
    GV_MSG  *msg;
    int      n_msgs;
    int      found;
    int      hash;
    int      i;

    n_msgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; n_msgs > 0; n_msgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < n_hashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

static void Act(Work *work)
{
    SVECTOR      rot;
    SVECTOR      step;
    u_short      hashes[2];
    TARGET       target;
    SVECTOR      size;
    S11ObjsObj1 *obj1;
    int          i;
    S11ObjsObj2 *obj2;

    GM_CurrentMap = work->map;

    if (work->f25A0 > 2)
    {
        return;
    }

    hashes[0] = GV_StrCode("壊れろ");
    hashes[1] = GV_StrCode("crash");

    switch (CheckMessages(work->name, 2, hashes))
    {
    case 0:
    case 1:
        work->f25A0++;
        break;
    }

    if (work->f25A0 == 1 && work->f25AC < 30)
    {
        if ((GM_PlayerControl->mov.vx > -1875 && GM_PlayerControl->mov.vx < 3000))
        {
            if (GM_PlayerControl->mov.vz > 1250)
            {
                if (GM_PlayerControl->mov.vz < 3125)
                {
                    if (GM_CurrentItemId == IT_Scope  ||
                        GM_CurrentItemId == IT_Camera ||
                        GM_CurrentItemId == IT_NVG    ||
                        GM_CurrentItemId == IT_ThermG)
                    {
                        GM_CurrentItemId = IT_None;
                    }

                    if (GM_CurrentWeaponId == WP_Rifle ||
                        GM_CurrentWeaponId == WP_Stinger)
                    {
                        GM_CurrentWeaponId = WP_None;
                    }

                    if (GM_PlayerControl->mov.vx > 1875)
                    {
                        GM_PlayerControl->mov.vx = 3000;
                    }
                    else if (GM_PlayerControl->mov.vz >= 2188)
                    {
                        GM_PlayerControl->mov.vz = 3125;
                    }
                    else
                    {
                        GM_PlayerControl->mov.vz = 1250;
                    }

                    if (work->f25AC == 0)
                    {
                        size.vx = 100;
                        size.vy = 100;
                        size.vz = 100;
                        GM_SetTarget(&target, TARGET_POWER, ENEMY_SIDE, &size);
                        GM_Target_8002DCCC(&target, 1, 2, ATTACK_DAMAGE, 0, &DG_ZeroVector);
                        GM_MoveTarget(&target, &GM_PlayerControl->mov);
                        GM_PowerTarget(&target);
                    }
                }
            }
        }

        work->f25AC++;
    }

    if (work->f25A0 == 2)
    {
        DG_InvisibleObjs(work->obj1[0].object.objs);
        DG_VisibleObjs(work->obj1[1].object.objs);

        obj1 = work->obj1 + 3;
        for (i = 0; i < 12; i++, obj1++)
        {
            DG_InvisibleObjs(obj1->object.objs);
        }

        obj2 = work->obj2;
        for (i = 0; i < 16; i++, obj2++)
        {
            DG_InvisibleObjs(obj2->object.objs);
        }

        work->f25A0 = 3;
    }
    else
    {
        DG_VisibleObjs(work->obj1[0].object.objs);
        DG_InvisibleObjs(work->obj1[1].object.objs);
    }

    if (work->f25A0 != 1)
    {
        return;
    }

    if (work->f25A4 == 13 && work->f25A8 == 16)
    {
        return;
    }

    step.vx = 0;
    step.vz = 0;
    rot.vz = 0;

    obj1 = work->obj1 + 2;
    for (i = 0; i < 13; i++, obj1++)
    {
        if (i != 0)
        {
            switch (obj1->state)
            {
            case 0:
                if (obj1->time-- < 0)
                {
                    obj1->state = 1;

                    step.vy = GV_RandU(128) + 200;
                    rot.vx = GV_RandS(256);
                    rot.vy = GV_RandU(4096);

                    DG_SetPos2(&DG_ZeroVector, &rot);
                    DG_PutVector(&step, &obj1->step, 1);

                    obj1->turn.vx = GV_RandS(16);
                    obj1->turn.vy = GV_RandS(16);
                    obj1->turn.vz = GV_RandS(16);
                }
                break;
            case 1:
                GV_AddVec3(&obj1->rot, &obj1->turn, &obj1->rot);
                GV_AddVec3(&obj1->pos, &obj1->step, &obj1->pos);
                obj1->step.vy -= 15;

                if (obj1->pos.vy < -15000)
                {
                    obj1->state = 2;
                    DG_InvisibleObjs(obj1->object.objs);
                }
                break;
            case 2:
                if (obj1->pos.pad == 0)
                {
                    work->f25A4++;
                    obj1->pos.pad = 1;
                }

                DG_InvisibleObjs(obj1->object.objs);
                break;
            }
        }
        else
        {
            switch(obj1->state)
            {
            case 0:
                if (obj1->time-- < 0)
                {
                    obj1->state = 1;
                    obj1->step = DG_ZeroVector;
                    obj1->turn.vx = -2;
                    obj1->turn.vy = -4;
                    obj1->turn.vz = -8;
                }
                break;
            case 1:
                obj1->turn.vz -= 3;
                GV_AddVec3(&obj1->rot, &obj1->turn, &obj1->rot);

                if (obj1->rot.vz < -455)
                {
                    GM_SeSet2(0, 63, 195);
                    obj1->state = 2;

                    obj1->rot.vx = -114;
                    obj1->rot.vy = -228;
                    obj1->rot.vz = -455;

                    obj1->turn.vx = 0;
                    obj1->turn.vy = 0;
                    obj1->turn.vz = 40;
                }
                break;
            case 2:
                obj1->turn.vz -= 3;
                GV_AddVec3(&obj1->rot, &obj1->turn, &obj1->rot);

                if (obj1->rot.vz < -455)
                {
                    GM_SeSet2(0, 32, 195);
                    obj1->state = 3;

                    obj1->rot.vx = -114;
                    obj1->rot.vy = -228;
                    obj1->rot.vz = -455;

                    obj1->turn.vx = 0;
                    obj1->turn.vy = 0;
                    obj1->turn.vz = 20;
                }
                break;
            case 3:
                obj1->turn.vz -= 3;
                GV_AddVec3(&obj1->rot, &obj1->turn, &obj1->rot);

                if (obj1->rot.vz < -455)
                {
                    GM_SeSet2(0, 16, 195);
                    obj1->state = 4;

                    obj1->rot.vx = -114;
                    obj1->rot.vy = -228;
                    obj1->rot.vz = -455;
                }
                break;
            case 4:
                if (obj1->pos.pad == 0)
                {
                    work->f25A4++;
                    obj1->pos.pad = 1;
                }

                DG_VisibleObjs(obj1->object.objs);
                break;
            }
        }

        DG_SetPos2(&obj1->pos, &obj1->rot);
        GM_ActObject2(&obj1->object);
    }

    obj2 = work->obj2;
    for (i = 0; i < 16; i++, obj2++)
    {
        switch (obj2->state)
        {
        case 0:
            if (obj2->time-- < 0)
            {
                DG_VisibleObjs(obj2->object.objs);
                obj2->state = 1;

                step.vy = GV_RandU(128) + 300;
                rot.vx = GV_RandS(256) + 256;
                rot.vy = GV_RandU(4096);

                DG_SetPos2(&DG_ZeroVector, &rot);
                DG_PutVector(&step, &obj2->step, 1);

                obj2->turn.vx = GV_RandS(128);
                obj2->turn.vy = GV_RandS(128);
                obj2->turn.vz = GV_RandS(128);
            }
            break;
        case 1:
            GV_AddVec3(&obj2->rot, &obj2->turn, &obj2->rot);
            GV_AddVec3(&obj2->pos, &obj2->step, &obj2->pos);
            obj2->step.vy -= 15;

            if (obj2->pos.vy < -15000)
            {
                obj2->state = 2;
                DG_InvisibleObjs(obj2->object.objs);
            }
            break;
        case 2:
            if (obj2->pos.pad == 0)
            {
                work->f25A8++;
                obj2->pos.pad = 1;
            }

            DG_InvisibleObjs(obj2->object.objs);
            break;
        }

        DG_SetPos2(&obj2->pos, &obj2->rot);
        GM_ActObject2(&obj2->object);
        ScaleMatrix(&obj2->object.objs->world, &obj2->scale);
    }
}

static void InitObjects(Work *work)
{
    int          models[15];
    int          times[15];
    S11ObjsObj1 *obj1;
    SVECTOR     *pos;
    SVECTOR     *rot;
    int          i;
    S11ObjsObj2 *obj2;

    models[0] = GV_StrCode("11h_o1");
    models[1] = GV_StrCode("11h_o2");
    models[2] = GV_StrCode("11h_o3");
    models[3] = GV_StrCode("11h_o4");
    models[4] = GV_StrCode("11h_o5");
    models[5] = GV_StrCode("11h_o6");
    models[6] = GV_StrCode("11h_o7");
    models[7] = GV_StrCode("11h_o8");
    models[8] = GV_StrCode("11h_o9");
    models[9] = GV_StrCode("11h_o10");
    models[10] = GV_StrCode("11h_o11");
    models[11] = GV_StrCode("11h_o12");
    models[12] = GV_StrCode("11h_o13");
    models[13] = GV_StrCode("11h_o14");
    models[14] = GV_StrCode("11h_o15");

    times[12] = 2;
    times[5] = 5;
    times[4] = 8;
    times[13] = 10;
    times[6] = 13;
    times[10] = 17;
    times[8] = 20;
    times[3] = 23;
    times[7] = 27;
    times[9] = 31;
    times[14] = 35;
    times[2] = 35;
    times[11] = 0;
    times[0] = -1;
    times[1] = -1;

    obj1 = work->obj1;
    pos = positions;
    rot = rotations;

    for (i = 0; i < 15; i++, pos++, rot++)
    {
        obj1->pos = *pos;
        obj1->pos.pad = 0;
        obj1->rot = *rot;

        if ((i == 2) && (work->f25A0 >= 2))
        {
            obj1->rot.vx = -114;
            obj1->rot.vy = -228;
            obj1->rot.vz = -455;
        }

        DG_SetPos2(&obj1->pos, &obj1->rot);
        InitPreshadeObject(&obj1->object, models[i], MODEL_FLAG);
        GM_ActObject2(&obj1->object);

        obj1->time = times[i];
        obj1->state = 0;
        obj1++;
    }

    obj2 = work->obj2;
    rot = rotations;

    for (i = 0; i < 16; i++, pos++, rot++)
    {
        obj2->pos.pad = 0;
        obj2->pos = positions[(GV_RandU(4096) % 6) + 9];
        obj2->rot = *rot;

        DG_SetPos2(pos, rot);
        GM_InitObject(&obj2->object, models[(GV_RandU(4096) % 7) + 2], MODEL_FLAG, 0);
        GM_ConfigObjectLight(&obj2->object, obj2->light);
        DG_InvisibleObjs(obj2->object.objs);
        GM_ActObject2(&obj2->object);

        obj2->time = times[i];
        obj2->state = 0;

        obj2->scale.vx = GV_RandU(1024) + 512;
        obj2->scale.vy = GV_RandU(1024) + 512;
        obj2->scale.vz = GV_RandU(1024) + 512;
        obj2++;
    }
}

static void Die(Work *work)
{
    S11ObjsObj1 *obj1;
    S11ObjsObj2 *obj2;
    int          i;

    obj1 = work->obj1;
    for (i = 0; i < 15; i++)
    {
        GM_FreeObject(&obj1->object);
        obj1++;
    }

    obj2 = work->obj2;
    for (i = 0; i < 16; i++)
    {
        GM_FreeObject(&obj2->object);
        obj2++;
    }
}

static int GetResources(Work *work, int map)
{
    char        *opt;
    S11ObjsObj1 *obj1;
    S11ObjsObj2 *obj2;
    int          i;

    opt = GCL_GetOption('s');
    if (opt)
    {
        work->f259C = GCL_StrToInt(opt);
    }
    else
    {
        work->f259C = 1;
    }

    work->f25A0 = work->f259C;
    work->f25A4 = 0;
    work->f25A8 = 0;

    work->map = map;
    GM_CurrentMap = map;

    InitObjects(work);

    if (work->f25A0 >= 2)
    {
        obj1 = work->obj1 + 3;
        for (i = 0; i < 13; i++, obj1++)
        {
            DG_InvisibleObjs(obj1->object.objs);
        }

        obj2 = work->obj2;
        for (i = 0; i < 16; i++, obj2++)
        {
            DG_InvisibleObjs(obj2->object.objs);
        }
    }

    work->f25AC = 0;
    return 0;
}

void *NewStage11Objects(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        work->name = name;
        GV_SetNamedActor(work, Act, Die, "s11_objs.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
