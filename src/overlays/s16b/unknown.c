#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

int SECTION("overlay.bss") THING_msg_result[2];

int THING_Gcl_GetIntDefault(char param, int def)
{
    if (GCL_GetOption_80020968(param))
    {
        return GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    return def;
}

// name from memleaks
int THING_Gcl_GetInt(char param)
{
    return THING_Gcl_GetIntDefault(param, 0);
}

unsigned short THING_Gcl_GetShortDefault(char param, unsigned short def)
{
    char *param2;

    param2 = GCL_GetOption_80020968(param);
    if (param2)
    {
        return GCL_StrToInt_800209E8(param2);
    }

    return def;
}

unsigned short THING_Gcl_GetShort(char param)
{
    return THING_Gcl_GetShortDefault(param, 0);
}

void THING_Gcl_GetSVectorDefault(char param, short x, short y, short z, SVECTOR *vec)
{
    if (GCL_GetOption_80020968(param))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), vec);
        return;
    }

    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

void THING_Gcl_GetSVector(char param, SVECTOR *vec)
{
    THING_Gcl_GetSVectorDefault(param, 0, 0, 0, vec);
}

// name from memleaks
int THING_Msg_CheckMessage(unsigned short name, int hash_count, unsigned short *hashes)
{
    GV_MSG *msg;
    int     msg_count;
    int     found;
    int     hash;
    int     i;

    msg_count = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; msg_count > 0; msg_count--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < hash_count; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
                THING_msg_result[0] = msg->message[1];
            }
        }
    }

    return found;
}

int THING_Msg_GetResult(void)
{
    return THING_msg_result[0];
}

void s16b_800C4594(unsigned short address, unsigned short message)
{
    GV_MSG msg;

    msg.address = address;
    msg._len = 1;
    msg.message[0] = message;
    GV_SendMessage(&msg);
}

void s16b_800C45C4(HZD_SEG *seg, MATRIX *trans, SVECTOR *arg2, SVECTOR *arg3)
{
    SVECTOR sp10;
    SVECTOR sp18;
    int     height;
    int     y;

    if (trans)
    {
        DG_SetPos_8001BC44(trans);
        DG_PutVector_8001BE48(arg2, &sp10, 1);
        DG_PutVector_8001BE48(arg3, &sp18, 1);
    }
    else
    {
        sp10 = *arg2;
        sp18 = *arg3;
    }

    height = sp10.vy - sp18.vy;
    y = sp18.vy;

    if (height <= 0)
    {
        y = sp10.vy;
        height = -height;
    }

    seg->p1.x = sp10.vx;
    seg->p1.z = sp10.vz;
    seg->p2.x = sp18.vx;
    seg->p2.z = sp18.vz;
    seg->p2.y = y;
    seg->p1.y = y;
    seg->p2.h = height;
    seg->p1.h = height;

    HZD_SetDynamicSegment_8006FEE4(seg, seg);
}

void s16b_800C46D8(HZD_FLR *flr, SVECTOR *arg1, SVECTOR *arg2)
{
    short y;

    flr->p1.x = arg1->vx - arg2->vx;
    flr->p1.z = arg1->vz - arg2->vz;

    flr->p2.x = arg1->vx + arg2->vx;
    flr->p2.z = arg1->vz - arg2->vz;

    flr->p4.x = arg1->vx - arg2->vx;
    flr->p4.z = arg1->vz + arg2->vz;

    flr->p3.x = arg1->vx + arg2->vx;
    flr->p3.z = arg1->vz + arg2->vz;

    y = arg1->vy + arg2->vy;

    flr->p1.h = 0;
    flr->p2.h = 0;
    flr->p3.h = 0xFF;

    flr->p4.y = y;
    flr->p3.y = y;
    flr->p2.y = y;
    flr->p1.y = y;

    flr->b1.x = arg1->vx - arg2->vx;
    flr->b1.z = arg1->vz - arg2->vz;
    flr->b1.y = arg1->vy - arg2->vy;

    flr->b2.x = arg1->vx + arg2->vx;
    flr->b2.z = arg1->vz + arg2->vz;
    flr->b2.y = arg1->vy + arg2->vy;
}
