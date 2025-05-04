#include "common.h"
#include "mts/mts.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

void *NewEventmouse_800CA6F4(HZD_PTP *points, int n_points, int, int, int, int);

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work {
    GV_ACT actor;
} Work;

void KeyItemAct_800C8888(Work *work)
{
}

void KeyItemDie_800C8890(Work *work)
{
}

void KeyItemExecProc_800C8898(int proc_id, SVECTOR *vec)
{
    GCL_ARGS args;
    long     val[4];

    val[0] = vec->vx;
    val[1] = vec->vy;
    val[2] = vec->vz;
    val[3] = vec->pad;

    args.argc = 4;
    args.argv = val;
    GCL_ExecProc(proc_id, &args);
}

int KeyItemGetSvecs_800C88F4(char *opt, SVECTOR *out)
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

void KeyItemRun_800C8948(int where)
{
    SVECTOR  sp18[16];
    int      sp98[16];
    int      spD8[16];
    MAP     *map;
    int      sp11C;
    int      proc2;
    int      proc3;
    int      proc4;
    int      proc5;
    int      sp130;
    int      time;
    int      i;
    int      var_fp;
    int      n_route;
    int      n_vecs;
    int      proc1;
    int      flag;
    char    *opt;
    int     *rnd;
    int      tmp;
    HZD_PAT *route;

    time = mts_get_tick_count() % 256;
    for (i = 0; i < time; i++)
    {
        GV_RandU(4096);
    }

    sp130 = 0;
    sp11C = 100;
    var_fp = 3;
    n_route = 0;
    n_vecs = 0;
    proc1 = 0;
    flag = 0;
    proc2 = 0;
    proc3 = 0;
    proc4 = 0;
    proc5 = 0;
    map = GM_GetMap(where);

    opt = GCL_GetOption('m');
    if (opt != NULL)
    {
        sp130 = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('c');
    if (opt != NULL)
    {
        n_vecs = KeyItemGetSvecs_800C88F4(opt, sp18);
    }

    for (i = 0; i < n_vecs; i++)
    {
        sp98[i] = i;
        spD8[i] = 0;
    }

    for (i = 0; i < n_vecs; i++)
    {
        rnd = &sp98[GV_RandU(4096) % n_vecs];
        tmp = sp98[i];
        sp98[i] = *rnd;
        *rnd = tmp;
    }

    opt = GCL_GetOption('h');
    if (opt != NULL)
    {
        proc1 = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('i');
    if (opt != NULL)
    {
        proc2 = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('j');
    if (opt != NULL)
    {
        proc3 = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('k');
    if (opt != NULL)
    {
        proc4 = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('l');
    if (opt != NULL)
    {
        proc5 = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('g');
    if (opt != NULL)
    {
        GCL_StrToInt(opt);
    }

    for (i = 0; i < n_vecs; i++)
    {
        switch (i)
        {
        case 0:
            if (sp130 == 1)
            {
                opt = GCL_GetOption('s');
                if (opt != 0)
                {
                    sp11C = GCL_StrToInt(opt);
                }

                opt = GCL_GetOption('f');
                if (opt != 0)
                {
                    var_fp = GCL_StrToInt(opt);
                }

                opt = GCL_GetOption('r');
                if (opt != 0)
                {
                    n_route = GCL_StrToInt(opt);
                }

                route = &map->hzd->header->routes[n_route];
                NewEventmouse_800CA6F4(route->points, route->n_points, sp11C, var_fp, proc1, 0);
            }
            else
            {
                if ((sp18[sp98[0]].vy > -10) && (sp18[sp98[0]].vz > -18010))
                {
                    sp18[sp98[0]].pad = 500;
                }
                else if (sp18[sp98[i]].vz > 5990)
                {
                    if (sp18[sp98[i]].vz < 7001)
                    {
                        sp18[sp98[i]].pad = 500;
                    }
                    else
                    {
                        sp18[sp98[i]].pad = 1000;
                    }
                }
                else if ((sp18[sp98[i]].vx > 11990) && (sp18[sp98[i]].vz > -4010))
                {
                    sp18[sp98[i]].pad = 1000;
                }
                else
                {
                    sp18[sp98[i]].pad = 1000;
                }

                KeyItemExecProc_800C8898(proc1, &sp18[sp98[i]]);
            }
            break;

        case 1:
            if (flag == 0)
            {
                sp18[sp98[i]].pad = 500;
                flag = 1;
                KeyItemExecProc_800C8898(proc2, &sp18[sp98[i]]);
            }
            break;

        case 2:
            sp18[sp98[i]].pad = 500;
            KeyItemExecProc_800C8898(proc3, &sp18[sp98[i]]);
            break;

        default:
            if (GV_RandU(2) == 0)
            {
                sp18[sp98[i]].pad = 500;
                KeyItemExecProc_800C8898(proc4, &sp18[sp98[i]]);
            }
            else
            {
                sp18[sp98[i]].pad = 500;
                KeyItemExecProc_800C8898(proc5, &sp18[sp98[i]]);
            }
            break;
        }
    }
}

void *NewKeyItem_800C8E18(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, KeyItemAct_800C8888, KeyItemDie_800C8890, "key_item.c");
        KeyItemRun_800C8948(where);
        GV_DestroyActor(&work->actor);
    }

    return (void *)work;
}
