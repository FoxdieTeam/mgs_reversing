#include "libgv/libgv.h"
#include "Game/camera.h"

typedef struct EvPanelChild
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
} EvPanelChild;

typedef struct EvPanelWork
{
    GV_ACT       actor;
    DG_PRIM     *field_20;
    DG_PRIM     *field_24;
    int          field_28;
    int          field_2C;
    int          field_30;
    int          field_34;
    short        field_38;
    short        field_3A;
    int          field_3C;
    short        field_40;
    short        field_42;
    short        field_44;
    short        field_46;
    int          field_48;
    int          field_4C;
    int          field_50;
    int          field_54;
    int          field_58;
    int          field_5C;
    int          field_60;
    int          field_64;
    int          field_68;
    int          field_6C;
    int          field_70;
    int          field_74;
    int          field_78;
    int          field_7C;
    int          field_80;
    int          field_84;
    int          field_88;
    int          field_8C;
    int          field_90;
    int          field_94;
    int          field_98;
    int          field_9C;
    int          field_A0;
    int          field_A4;
    int          field_A8;
    int          field_AC;
    int          field_B0;
    EvPanelChild field_B4_children[0];
} EvPanelWork;

int  THING_Gcl_GetIntDefault(int, int);
void s03e_evpanel_800C3B74(EvPanelWork *);
void s03e_evpanel_800C457C(EvPanelWork *);
int  s03e_evpanel_800C496C(EvPanelWork *, int, int, int);

extern char      s03e_dword_800CBFA8[];
extern char      s03e_aReqdoorclose_800CBF58[];
extern GM_Camera GM_Camera_800B77E8;

#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C33E0.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C3488.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C36B0.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C3778.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C37FC.s")

void s03e_evpanel_800C3898(EvPanelWork *work)
{
    GV_MSG msg;

    msg.address = work->field_3A;
    msg.message[0] = 0xDD2;
    msg.message[1] = 0x21CA;
    msg.message_len = 2;

    GV_SendMessage_80016504(&msg);

    work->field_42 = 2;
    work->field_38 = 0x258;
}

void s03e_evpanel_800C38F4(EvPanelWork *work)
{
    GV_MSG msg;

    msg.address = work->field_3A;
    msg.message[0] = 0xD5CC;
    msg.message[1] = 0x21CA;
    msg.message_len = 2;

    GV_SendMessage_80016504(&msg);

    printf(s03e_aReqdoorclose_800CBF58);
    work->field_42 = 1;
}

void s03e_evpanel_800C3950(EvPanelWork *work, short arg1)
{
    GV_MSG msg;

    if (work->field_46 != 0)
    {
        msg.address = work->field_46;
        msg.message[0] = 0xBCD2;
        msg.message[1] = arg1;
        msg.message_len = 2;

        GV_SendMessage_80016504(&msg);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C3994.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C39F8.s")

void s03e_evpanel_800C3AD0(EvPanelWork *work)
{
    GM_Camera_800B77E8.field_18_flags = work->field_4C;
    GM_Camera_800B77E8.field_2A = 2;
    GM_Camera_800B77E8.field_26 = 0x1E;

    sub_8002FD84(1, NULL);
}

#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C3B14.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C3B74.s")

void s03e_evpanel_800C457C(EvPanelWork *work)
{
    DG_PRIM *prim;

    prim = work->field_20;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    prim = work->field_24;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C45E4.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C470C.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C47D0.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_evpanel_800C496C.s")

GV_ACT *s03e_evpanel_800C4AD8(int name, int where, int argc, char **argv)
{
    EvPanelWork *work;
    int          count;

    count = THING_Gcl_GetIntDefault('n', 3);
    work = (EvPanelWork *)GV_NewActor_800150E4(4, sizeof(EvPanelWork) + count * sizeof(EvPanelChild));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s03e_evpanel_800C3B74,
                                  (TActorFunction)s03e_evpanel_800C457C, s03e_dword_800CBFA8);
        if (s03e_evpanel_800C496C(work, where, name, count) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
