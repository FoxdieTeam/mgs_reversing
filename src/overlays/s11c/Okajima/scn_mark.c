#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _ScnMarkWork
{
    GV_ACT actor;
    int    map;
    int    name;
    char   pad[0x10];
    int    f38;
    char   pad2[0x4];
} ScnMarkWork;

extern int     GM_CurrentMap_800AB9B0;
extern int     GM_PlayerMap_800ABA0C;
extern OBJECT *GM_PlayerBody_800ABA20;

void * AN_Unknown_800CA1EC(MATRIX *pos, int mark);

#define EXEC_LEVEL 4

int ScnMarkCheckMessages_800C93CC(unsigned short name, int n_hashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     n_msgs;
    int     found;
    int     hash;
    int     i;

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

void ScnMarkAct_800C9464(ScnMarkWork *work)
{
    unsigned short hashes[7];
    int            found;

    GM_CurrentMap_800AB9B0 = GM_PlayerMap_800ABA0C;

    hashes[0] = GV_StrCode("B_MARK");
    hashes[1] = GV_StrCode("Q_MARK");
    hashes[2] = GV_StrCode("BY_MARK");
    hashes[3] = GV_StrCode("QY_MARK");
    hashes[4] = GV_StrCode("BW_MARK");
    hashes[5] = GV_StrCode("QW_MARK");
    hashes[6] = GV_StrCode("HEART_MARK");
    found = ScnMarkCheckMessages_800C93CC(work->name, 7, hashes);

    if (found != -1)
    {
        AN_Unknown_800CA1EC(&GM_PlayerBody_800ABA20->objs->objs[6].world, found % 7);
    }
}

int ScnMarkGetResources_800C9564(ScnMarkWork *work, int map, int name)
{
    work->map = map;
    work->name = name;
    work->f38 = 0;
    return 0;
}

void ScnMarkDie_800C9578(ScnMarkWork *work)
{
}

GV_ACT *NewScnMark_800C9580(int name, int where)
{
    ScnMarkWork *work;

    work = (ScnMarkWork *)GV_NewActor(EXEC_LEVEL, sizeof(ScnMarkWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)ScnMarkAct_800C9464, (GV_ACTFUNC)ScnMarkDie_800C9578, "scn_mark.c");

        if (ScnMarkGetResources_800C9564(work, where, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
