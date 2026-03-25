#include "game/game.h"
#include "libgcl/libgcl.h"

typedef struct _S11ObjsObj1
{
    /* 0x000 */ OBJECT  object;
    /* 0x0E4 */ SVECTOR pos;
    /* 0x0EC */ SVECTOR rot;
    /* 0x0F4 */ char    pad1[0x10];
    /* 0x104 */ int     f104;
    /* 0x104 */ int     f108;
} S11ObjsObj1;

typedef struct _S11ObjsObj2
{
    /* 0x000 */ OBJECT  object;
    /* 0x0E4 */ SVECTOR pos;
    /* 0x0EC */ SVECTOR rot;
    /* 0x0F4 */ char    pad1[0x10];
    /* 0x104 */ int     f104;
    /* 0x108 */ VECTOR  f108;
    /* 0x118 */ MATRIX  light[2];
    /* 0x158 */ int     f158;
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

SVECTOR s11g_dword_800C3484[] =
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

SVECTOR s11g_dword_800C34FC[] =
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

DG_OBJS *Takabe_MakePreshade(int model, LIT *lit);

#define EXEC_LEVEL 5

#define MODEL_FLAG ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_ONEPIECE )

/* TODO: static */
void InitPreshadeObject(OBJECT *object, int model, u_long flag)
{
    GV_ZeroMemory(object, sizeof(OBJECT));

    object->flag = flag;
    object->map_name = GM_CurrentMap;
    object->objs = Takabe_MakePreshade(model, GM_GetMap(GM_CurrentMap)->lit);
}

/* TODO: static */
int CheckMessages11G(u_short name, int n_hashes, u_short *hashes)
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

const char s11g_dword_800DCF30[] = "壊れろ";
const char s11g_aCrash_800DCF38[] = "crash";
const int s11g_dword_800DCF40 = 0x800CAA28;
const int s11g_dword_800DCF44 = 0x800CAA88;
const int s11g_dword_800DCF48 = 0x800CAAE8;
const int s11g_dword_800DCF4C = 0x800CAB58;
const int s11g_dword_800DCF50 = 0x800CABB8;

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_s11_objs_800CA560.s")
int s11g_s11_objs_800CA560(Work *work);

/* TODO: static */
void InitObjects(Work *work)
{
    int          models[15];
    int          ids[15];
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

    ids[12] = 2;
    ids[5] = 5;
    ids[4] = 8;
    ids[13] = 10;
    ids[6] = 13;
    ids[10] = 17;
    ids[8] = 20;
    ids[3] = 23;
    ids[7] = 27;
    ids[9] = 31;
    ids[14] = 35;
    ids[2] = 35;
    ids[11] = 0;
    ids[0] = -1;
    ids[1] = -1;

    obj1 = work->obj1;
    pos = s11g_dword_800C3484;
    rot = s11g_dword_800C34FC;

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

        obj1->f104 = ids[i];
        obj1->f108 = 0;
        obj1++;
    }

    obj2 = work->obj2;
    rot = s11g_dword_800C34FC;

    for (i = 0; i < 16; i++, pos++, rot++)
    {
        obj2->pos.pad = 0;
        obj2->pos = s11g_dword_800C3484[(GV_RandU(4096) % 6) + 9];
        obj2->rot = *rot;

        DG_SetPos2(pos, rot);
        GM_InitObject(&obj2->object, models[(GV_RandU(4096) % 7) + 2], MODEL_FLAG, 0);
        GM_ConfigObjectLight(&obj2->object, obj2->light);
        DG_InvisibleObjs(obj2->object.objs);
        GM_ActObject2(&obj2->object);

        obj2->f104 = ids[i];
        obj2->f158 = 0;

        obj2->f108.vx = GV_RandU(1024) + 512;
        obj2->f108.vy = GV_RandU(1024) + 512;
        obj2->f108.vz = GV_RandU(1024) + 512;
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
        GV_SetNamedActor(work, s11g_s11_objs_800CA560, Die, "s11_objs.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
