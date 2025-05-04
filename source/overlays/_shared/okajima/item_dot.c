#include "common.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "linkvar.h"

typedef struct _ItemDotWork
{
    GV_ACT  actor;
    CONTROL control;
    int     name;
    int     fA0;
    int     fA4;
    int     fA8;
} ItemDotWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

int ItemDotCheckMessages_800CC4C8(unsigned short name, int n_hashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage(name, &msg);
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

    hash[0] = GV_StrCode("kill");
    if (ItemDotCheckMessages_800CC4C8(work->name, 1, hash) == 0)
    {
        work->fA8 = 1;
        work->control.skip_flag |= CTRL_SKIP_TRAP;
        GM_ConfigControlAttribute(&work->control, RADAR_OFF);
        GM_ActControl(&work->control);
        GV_DestroyActor(&work->actor);
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

    if (GM_CurrentItemId == IT_MineDetector)
    {
        if (work->fA4 == 0)
        {
            work->fA4 = 1;
            GM_ConfigControlAttribute(&work->control, RADAR_VISIBLE);
            GM_ActControl(&work->control);
        }
    }
    else if (work->fA4 == 1)
    {
        work->fA4 = 0;
        GM_ConfigControlAttribute(&work->control, RADAR_OFF);
        GM_ActControl(&work->control);
    }
}

int ItemDotGetSvecs_800CC688(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;

    while ((res = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(res, out);
        out++;
        count++;
    }

    return count;
}

int ItemDotGetResources_800CC6DC(ItemDotWork *work, int name, int map)
{
    char *opt;

    work->name = name;

    if (GM_InitControl(&work->control, name, map) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(&work->control, -1, -2, -1);

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        ItemDotGetSvecs_800CC688(opt, &work->control.mov);
    }

    opt = GCL_GetOption('m');
    if (opt != NULL)
    {
        work->fA0 = 1;
        GM_ConfigControlAttribute(&work->control, RADAR_OFF);
    }
    else
    {
        GM_ConfigControlAttribute(&work->control, RADAR_VISIBLE);
        work->fA0 = 0;
    }

    opt = GCL_GetOption('n');
    if (opt != NULL)
    {
        work->fA8 = 1;
    }
    else
    {
        work->fA8 = 0;
    }

    work->fA4 = 0;

    GM_ActControl(&work->control);
    return 0;
}

void ItemDotDie_800CC7B0(ItemDotWork *work)
{
    GM_FreeControl(&work->control);
}

void *NewItemDot_800CC7D0(int name, int where)
{
    ItemDotWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(ItemDotWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, ItemDotAct_800CC560, ItemDotDie_800CC7B0, "item_dot.c");

        if (ItemDotGetResources_800CC6DC(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
