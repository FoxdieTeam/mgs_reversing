#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

typedef struct _ItemDotWork
{
    GV_ACT  actor;
    CONTROL control;
    int     name;
    int     fA0;
    int     fA4;
    int     fA8;
} ItemDotWork;

#define EXEC_LEVEL 4

int ItemDotCheckMessages_800CC4C8(unsigned short name, int n_hashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage_80016620(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
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

void ItemDotAct_800CC560(ItemDotWork *work)
{
    unsigned short hash[1];

    hash[0] = GV_StrCode_80016CCC("kill");
    if (ItemDotCheckMessages_800CC4C8(work->name, 1, hash) == 0)
    {
        work->fA8 = 1;
        work->control.skip_flag |= CTRL_SKIP_TRAP;
        GM_ConfigControlAttribute_8002623C(&work->control, RADAR_OFF);
        GM_ActControl_80025A7C(&work->control);
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    if (work->fA8 != 1)
    {
        work->control.skip_flag &= ~CTRL_SKIP_TRAP;
    }
    else
    {
        work->control.skip_flag |= CTRL_SKIP_TRAP;
    }

    if (work->fA0 == 0)
    {
        return;
    }

    if (GM_CurrentItemId == ITEM_MINE_D)
    {
        if (work->fA4 == 0)
        {
            work->fA4 = 1;
            GM_ConfigControlAttribute_8002623C(&work->control, RADAR_VISIBLE);
            GM_ActControl_80025A7C(&work->control);
        }
    }
    else if (work->fA4 == 1)
    {
        work->fA4 = 0;
        GM_ConfigControlAttribute_8002623C(&work->control, RADAR_OFF);
        GM_ActControl_80025A7C(&work->control);
    }
}

int ItemDotGetSvecs_800CC688(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;

    while ((res = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(res, out);
        out++;
        count++;
    }

    return count;
}

int ItemDotGetResources_800CC6DC(ItemDotWork *work, int name, int map)
{
    char *opt;

    work->name = name;

    if (GM_InitControl_8002599C(&work->control, name, map) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(&work->control, -1, -2, -1);

    opt = GCL_GetOption_80020968('p');
    if (opt != NULL)
    {
        ItemDotGetSvecs_800CC688(opt, &work->control.mov);
    }

    opt = GCL_GetOption_80020968('m');
    if (opt != NULL)
    {
        work->fA0 = 1;
        GM_ConfigControlAttribute_8002623C(&work->control, RADAR_OFF);
    }
    else
    {
        GM_ConfigControlAttribute_8002623C(&work->control, RADAR_VISIBLE);
        work->fA0 = 0;
    }

    opt = GCL_GetOption_80020968('n');
    if (opt != NULL)
    {
        work->fA8 = 1;
    }
    else
    {
        work->fA8 = 0;
    }

    work->fA4 = 0;

    GM_ActControl_80025A7C(&work->control);
    return 0;
}

void ItemDotDie_800CC7B0(ItemDotWork *work)
{
    GM_FreeControl_800260CC(&work->control);
}

GV_ACT * NewItemDot_800CC7D0(int name, int where)
{
    ItemDotWork *work;

    work = (ItemDotWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(ItemDotWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)ItemDotAct_800CC560, (TActorFunction)ItemDotDie_800CC7B0, "item_dot.c");

        if (ItemDotGetResources_800CC6DC(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
