#include "linker.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _ShakemdlWork
{
    GV_ACT actor;
    int    name;
    int    f24;
    int    f28;
    int    f2C;
    int    f30;
    int    f34;
    void  *f38;
    short  f3C[16];
    short  f5C[16];
    void  *ptr;
} ShakemdlWork;

extern const char s16b_dword_800C58A0[]; // = "shakemdl.c"

int  s16b_800C4364(int param, int def);
int  s16b_800C43A4(int param);
void s16b_800C5728(ShakemdlWork *, short *);
void s16b_800C57A4(ShakemdlWork *);
int  s16b_800C5664(ShakemdlWork *work);

#define EXEC_LEVEL 5

void ShakemdlAct_800C5288(ShakemdlWork *work)
{
    GV_MSG *msg;
    int     count;
    short  *var_s4;
    int     temp_v0;
    short  *var_s0;
    short  *var_s1;
    int     i;

    count = GV_ReceiveMessage_80016620(work->name, &msg);

    for (; count > 0; count--, msg++)
    {
        switch (msg->message[0])
        {
        case 0x3223:
            GV_DestroyActor_800151C8(&work->actor);
            return;

        case 0xD368:
            work->f30 = msg->message[1];
            work->f34 = msg->message[2];
            work->f24 = 1;
            break;

        case 0x9873:
            work->f24 = 0;
            break;
        }
    }

    var_s4 = (short *)0x1F800000;

    if (work->f24 != 0)
    {
        work->f28 = sub_8002646C(work->f28, work->f30, work->f34);
        temp_v0 = work->f28;

        var_s0 = work->f3C;
        var_s1 = work->f5C;

        for (i = 16; i > 0; i--)
        {
            *var_s4++ = (rsin(*var_s0) * temp_v0) >> 12;
            *var_s0++ += *var_s1++;
        }

        s16b_800C5728(work, (short *)0x1F800000);

        if ((work->f28 == 0) && (work->f30 == 0))
        {
            work->f24 = 0;
        }
    }
}

void ShakemdlDie_800C5418(ShakemdlWork *work)
{
    s16b_800C57A4(work);

    if (work->ptr)
    {
        GV_Free_80016230(work->ptr);
    }
}

int ShakemdlGetResources_800C5454(ShakemdlWork *work, int name)
{
    short *var_s1;
    short *var_s2;
    int    i;

    work->f38 = GV_GetCache_8001538C(GV_CacheID_800152DC(name, 'k'));

    if (s16b_800C5664(work))
    {
        return -1;
    }

    var_s2 = work->f3C;
    var_s1 = work->f5C;

    for (i = 16; i > 0; i--)
    {
        *var_s2++ = GV_RandU_80017090(0x1000U);
        *var_s1++ = GV_RandU_80017090(0x40U) + 0x10;
    }

    return 0;
}

GV_ACT *NewShakemdl_800C54E8(int name, int where, int argc, char **argv)
{
    ShakemdlWork *work;
    int           model;
    int           work_2;

    work = (ShakemdlWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(ShakemdlWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)ShakemdlAct_800C5288, (TActorFunction)ShakemdlDie_800C5418, s16b_dword_800C58A0);

        model = s16b_800C43A4('m');
        work->f2C = s16b_800C43A4('a');

        if (ShakemdlGetResources_800C5454(work, model) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->name = name;
        work->f24 = s16b_800C4364('f', 1);
        work_2 = s16b_800C4364('s', 50);
        work->f28 = work_2;
        work->f30 = work_2;
    }

    return &work->actor;
}

GV_ACT *NewShakemdl_800c55b0(int arg0, int arg1, int arg2)
{
    ShakemdlWork *work;

    work = (ShakemdlWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(ShakemdlWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)ShakemdlAct_800C5288, (TActorFunction)ShakemdlDie_800C5418, s16b_dword_800C58A0);

        work->f2C = arg1;

        if (ShakemdlGetResources_800C5454(work, arg0) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->name = 0x7743;
        work->f24 = 1;
        work->f28 = arg2;
        work->f30 = arg2;
    }

    return &work->actor;
}

#pragma INCLUDE_ASM("asm/overlays/s16b/s16b_800C5664.s");
#pragma INCLUDE_ASM("asm/overlays/s16b/s16b_800C5728.s");
#pragma INCLUDE_ASM("asm/overlays/s16b/s16b_800C57A4.s");