#include <stddef.h> // for NULL
#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "strcode.h"

typedef struct VoicesysWork {
    GV_ACT actor;
    int    name;
    int    game_over;
} VoicesysWork;

#define EXEC_LEVEL 3

typedef struct VoiceSysGlobal {
    int flags;
    int voxCode1;
    int field_8; // some sort of timer?
    int field_C; // some sort of timer?
    int index1; // into voxCodes
    int voxCode2;
    int field_18; // some sort of timer?
    int index2; // into voxCodes
    int voxCode3;
    int field_24; // some sort of mode?
    int field_28; // some sort of mode?
    int voxCodes[33];
} VoiceSysGlobal;

VoiceSysGlobal SECTION("overlay.bss") voicesys_800DBD60;

extern int GM_GameOverTimer;
extern int GV_PauseLevel_800AB928;

int *Voicesys_800CE278(int unused)
{
    GV_ZeroMemory(&voicesys_800DBD60, sizeof(VoiceSysGlobal));
    voicesys_800DBD60.voxCode2 = -1;
    voicesys_800DBD60.voxCodes[0] = -1;
    voicesys_800DBD60.field_C = 0;
    voicesys_800DBD60.index1 = 0;
    voicesys_800DBD60.field_24 = 0;
    voicesys_800DBD60.field_8 = 5;
    GM_StreamPlayStop_80037D64();
    return voicesys_800DBD60.voxCodes;
}

void Voicesys_800CE2D0()
{
    if (voicesys_800DBD60.field_28 == 0)
    {
        voicesys_800DBD60.field_C++;
    }
}

void Voicesys_800CE300()
{
    voicesys_800DBD60.field_24 = 1;
}

void Voicesys_800CE310()
{
    voicesys_800DBD60.field_24 = 2;
}

void Voicesys_800CE320(int flags)
{
    voicesys_800DBD60.flags = flags;
}

void Voicesys_800CE32C()
{
    int voxCode;
    int status;

    if (voicesys_800DBD60.field_8 != 0)
    {
        voicesys_800DBD60.field_8--;
        return;
    }
    status = GM_StreamStatus_80037CD8();
    switch (status)
    {
    case 0:
        if (voicesys_800DBD60.field_24 == 2)
        {
            GM_StreamPlayStop_80037D64();
            voicesys_800DBD60.field_8 = 1;
        }
        break;
    case 1:
        if (GV_PauseLevel_800AB928 == 0)
        {
            if (voicesys_800DBD60.field_24 == 2)
            {
                GM_StreamPlayStop_80037D64();
                voicesys_800DBD60.field_8 = 0;
            }
            if (!(voicesys_800DBD60.flags & 2))
            {
                if (voicesys_800DBD60.field_C != 0)
                {
                    voicesys_800DBD60.field_C--;
                    GM_StreamPlayStart_80037D1C();
                    voicesys_800DBD60.voxCode1 = -1;
                }
            }
            else if (voicesys_800DBD60.field_18 != 0)
            {
                voicesys_800DBD60.field_18--;
                GM_StreamPlayStart_80037D1C();
            }
            voicesys_800DBD60.field_24 = 0;
        }
        return;
    case 2:
        if (voicesys_800DBD60.field_24 != 0)
        {
            GM_StreamPlayStop_80037D64();
            voicesys_800DBD60.field_8 = 5;
        }
        else if (voicesys_800DBD60.field_28 == 1)
        {
            voicesys_800DBD60.field_28 = status;
        }
        break;
    default:
        if (voicesys_800DBD60.field_28 != 2)
        {
            if (!(voicesys_800DBD60.flags & 2))
            {
                voxCode = voicesys_800DBD60.voxCode2;
                if (voxCode != -1)
                {
                    GM_VoxStream_80037E40(voxCode, 0x40000000);
                    voicesys_800DBD60.voxCode1 = voxCode;
                    if (!(voicesys_800DBD60.flags & 1))
                    {
                        voicesys_800DBD60.voxCode2 = voicesys_800DBD60.voxCodes[++voicesys_800DBD60.index1];
                    }
                }
            }
            else if (voicesys_800DBD60.field_18 <= 0)
            {
                voxCode = voicesys_800DBD60.voxCode1;
                voicesys_800DBD60.flags &= ~2;
                if (voxCode != -1)
                {
                    GM_VoxStream_80037E40(voxCode, 0x40000000);
                }
            }
            else
            {
                voxCode = voicesys_800DBD60.voxCode3;
                if (voxCode != -1)
                {
                    GM_VoxStream_80037E40(voxCode, 0x40000000);
                    voicesys_800DBD60.voxCode3 = voicesys_800DBD60.voxCodes[++voicesys_800DBD60.index2];
                }
            }
        }
        break;
    }
    
    voicesys_800DBD60.field_24 = 0;
}

void Voicesys_800CE58C(int index)
{
    int status;

    status = GM_StreamStatus_80037CD8();
    if (voicesys_800DBD60.field_28 == 0)
    {
        voicesys_800DBD60.field_C = 0;
        voicesys_800DBD60.index1 = index;
        voicesys_800DBD60.voxCode2 = voicesys_800DBD60.voxCodes[index];
        if (status != 2)
        {
            GM_StreamPlayStop_80037D64();
        }
    }
}

void Voicesys_800CE5F8(int index, int field_18)
{
    int status;

    status = GM_StreamStatus_80037CD8();
    if (voicesys_800DBD60.field_28 == 0)
    {
        voicesys_800DBD60.index2 = index;
        voicesys_800DBD60.voxCode3 = voicesys_800DBD60.voxCodes[index];
        voicesys_800DBD60.field_18 = field_18;
        if (status != 2)
        {
            GM_StreamPlayStop_80037D64();
            voicesys_800DBD60.field_8 = 5;
        }
        voicesys_800DBD60.flags |= 2;
    }
}

int Voicesys_800CE694()
{
    return (voicesys_800DBD60.flags & 2) > 0;
}

void Voicesys_800CE6AC(int arg0)
{
    if (voicesys_800DBD60.field_28 == 0 && (voicesys_800DBD60.flags & 2))
    {
        voicesys_800DBD60.field_18 = 0;
        if (GM_StreamStatus_80037CD8() != 2)
        {
            GM_StreamPlayStop_80037D64();
            voicesys_800DBD60.field_8 = 5;
            return;
        }
        if (arg0 == 1)
        {
            Voicesys_800CE300();
        }
    }
}

void Voicesys_800CE734()
{
    if (voicesys_800DBD60.field_28 == 0)
    {
        voicesys_800DBD60.field_28 = 1;
    }
}

void VoicesysDie_800CE758(VoicesysWork *work)
{
}

void VoicesysAct_800CE760(VoicesysWork *work)
{
    GV_MSG *msg;
    int count;

    if (GM_GameOverTimer > 0)
    {
        work->game_over = 1;
        return;
    }
    
    for (count = GV_ReceiveMessage(work->name, &msg); count > 0; count--, msg++)
    {
        switch (msg->message[0])
        {
        case 0x8298:
            Voicesys_800CE2D0();
            break;
        case 0x4B0D:
            Voicesys_800CE5F8(msg->message[1], 1);
            break;
        case 0xF7E9:
            Voicesys_800CE300();
            break;
        case HASH_KILL:
            GM_StreamPlayStop_80037D64();
            GV_DestroyActor(&work->actor);
            return;
        }
    }
    
    if (!work->game_over)
    {
        Voicesys_800CE32C();
    }
}

void VoicesysDie_800CE87C(VoicesysWork *work)
{
    VoicesysDie_800CE758(work);
}

int VoicesysGetResources_800CE89C(VoicesysWork *work, int name, int arg2)
{
    int *arr;
    int i;
    unsigned char *param;

    if (GCL_GetOption('v'))
    {
        arr = Voicesys_800CE278(0);
        for (i = 32; i > 0; i--, arr++) 
        {
            param = GCL_GetParamResult();
            if (param == NULL)
            {
                *arr = -1;
                break;
            }
                
            *arr = GCL_StrToInt(param);
        }
    }
    Voicesys_800CE58C(0);
    work->name = name;
    return 0;
}

GV_ACT *NewVoicesys_800CE944(int name, int arg1)
{
    VoicesysWork *work;

    work = (VoicesysWork*) GV_NewActor(EXEC_LEVEL, sizeof(VoicesysWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)VoicesysAct_800CE760, (TActorFunction)VoicesysDie_800CE87C, "voicesys.c");
        if (VoicesysGetResources_800CE89C(work, name, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
