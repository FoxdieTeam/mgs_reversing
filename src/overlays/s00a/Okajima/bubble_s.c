#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _BubbleSWork
{
    GV_ACT   actor;
    int      map;
    int      name;
    DG_PRIM *prim[4];
    RECT     rect[4];
    SVECTOR  pos[4];
    SVECTOR  speed;
    int      f80[4];
    int      count[4];
    int      fA0;
    int      fA4;
    int      fA8;
    int      ripple;
    int      bounded;
    SVECTOR  bounds[2];
    int      fC4;
} BubbleSWork;

extern MATRIX  DG_ZeroMatrix_8009D430;
extern int     GV_Time_800AB330;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_Clock_800AB920;
extern int     GM_CurrentMap_800AB9B0;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern OBJECT *GM_PlayerBody_800ABA20;

#define EXEC_LEVEL      4

#define UP_SPEED        15
#define MIN_BUBBLE_SIZE 20
#define MAX_BUBBLE_SIZE 40
#define RANDAM_WIDTH    16

GV_ACT * NewRipple_800D7F30(MATRIX *, int);

void BubbleSShadePacks_800D5324(POLY_FT4 *packs, int shade)
{
    setRGB0(packs, shade, shade, shade);
}

int BubbleSGetSvecs_800D5334(char *opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(result, svec);

        svec++;
        count++;
    }

    return count;
}

void BubbleSInitPacks_800D5388(POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 0, 0, 0);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;

        packs->clut = tex->clut;
        packs->tpage |= 0x20;

        packs++;
    }
}

void BubbleSPrimsRectSet_800D5414(BubbleSWork *work, int i)
{
    SVECTOR     speed;
    int         size,dis;
    int         rtemp1;
    MATRIX      mat;

    work->count[i]++;

    size=work->count[i]/8+MIN_BUBBLE_SIZE;
    if(size > MAX_BUBBLE_SIZE) size = MAX_BUBBLE_SIZE;


    speed.vx=work->speed.vx+GV_RandS(RANDAM_WIDTH);
    speed.vy=work->speed.vy+UP_SPEED;
    speed.vz=work->speed.vz+GV_RandS(RANDAM_WIDTH);

    work->pos[i].vx+=speed.vx;
    work->pos[i].vy+=speed.vy;
    work->pos[i].vz+=speed.vz;

    rtemp1=size+(GV_RandU(4096)%size)/4;

    work->rect[i].x=rtemp1/2;
    work->rect[i].y=size/2;
    work->rect[i].w=rtemp1;
    work->rect[i].h=size;

    if (work->fC4 == 0)
    {
        if (work->pos[i].vy > work->bounds[1].vy)
        {
            work->f80[i] = 0;
            work->fA4--;

            if (work->ripple != 0)
            {
                mat = DG_ZeroMatrix_8009D430;
                mat.t[0] = work->pos[i].vx;
                mat.t[1] = work->pos[i].vy;
                mat.t[2] = work->pos[i].vz;

                NewRipple_800D7F30(&mat, 2000);
            }

        }
        return;
    }

    dis = work->pos[i].vy - GM_PlayerPosition_800ABA10.vy;
    if ( dis < 0 )
    {
        dis = GM_PlayerPosition_800ABA10.vy - work->pos[i].vy;
    }

    if ( dis > 3000)
    {
        work->f80[i] = 0;

        if (--work->fA4 <= 0)
        {
            GV_DestroyActor(&work->actor);
        }
    }
}

int BubbleSBoundInCheck_800D5678(SVECTOR *bound, SVECTOR *check)
{
    if ( !(check->vx <= bound[0].vx)  )
    {
        if ( check->vy > bound[0].vy )
        {
            if ( !(check->vz <= bound[0].vz) )
            {
                if ( check->vx < bound[1].vx )
                {
                    if ( !(bound[1].vy <= check->vy) )
                    {
                        if ( !(check->vz >= bound[1].vz) )
                        {
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int BubbleSCheckMessage_800D5708(unsigned short name, int n_hashes, unsigned short *hashes)
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

void BubbleSAct_800D57A0(BubbleSWork *work)
{
    SVECTOR        headpos;
    unsigned short hash[2];
    int            found;
    int            i;
    int            interp;
    POLY_FT4      *poly;

    GM_CurrentMap_800AB9B0 = work->map;

    work->fA0++;

    hash[0] = GV_StrCode("バブルはじけろ"); // bubble popped
    hash[1] = GV_StrCode("kill");

    found = BubbleSCheckMessage_800D5708(work->name, 2, hash);

    switch (found)
    {
    case 0:
    case 1:
        GV_DestroyActor(&work->actor);
        return;
    }

    headpos.vx = GM_PlayerBody_800ABA20->objs->objs[6].world.t[0];
    headpos.vy = GM_PlayerBody_800ABA20->objs->objs[6].world.t[1];
    headpos.vz = GM_PlayerBody_800ABA20->objs->objs[6].world.t[2];

    if (work->fC4 == 0)
    {
        if (BubbleSBoundInCheck_800D5678(work->bounds, &headpos))
        {
            if (work->fA8 == 0)
            {
                work->fA8 = 1;
                work->fA0 = 0;
            }
        }
        else if (work->fA8 == 1)
        {
            work->fA8 = 0;
        }

        if (work->fC4 == 0)
        {
            if (work->fA8 != 0)
            {
                if (work->fA4 < 4 && GV_RandU(32) == 0)
                {
                    work->fA4++;

                    for (i = 0; i < 4; i++)
                    {
                        if (!work->f80[i])
                        {
                            work->f80[i] = 1;
                            work->count[i] = 0;
                            work->pos[i] = headpos;
                            break;
                        }
                    }
                }
            }
            else if (work->fA4 < 4 && (GV_Time_800AB330 & 0x10))
            {
                work->fA4++;

                for (i = 0; i < 4; i++)
                {
                    if (!work->f80[i])
                    {
                        work->f80[i] = 1;
                        work->count[i] = 0;

                        interp = (work->bounds[1].vx - work->bounds[0].vx) * GV_RandU(4096);
                        work->pos[i].vx = work->bounds[0].vx + (interp >> 12);

                        work->pos[i].vy = work->bounds[0].vy;

                        interp = (work->bounds[1].vz - work->bounds[0].vz) * GV_RandU(4096);
                        work->pos[i].vz = work->bounds[0].vz + (interp >> 12);
                        break;
                    }
                }
            }
        }
    }

    for (i = 0; i < 4; i++)
    {
        poly = &work->prim[i]->packs[GV_Clock_800AB920]->poly_ft4;
        if (work->f80[i])
        {
            BubbleSShadePacks_800D5324(poly, 64);
            BubbleSPrimsRectSet_800D5414(work, i);
        }
        else
        {
            BubbleSShadePacks_800D5324(poly, 0);
        }
    }
}

void BubbleSDestroyPrim_800D5ACC(BubbleSWork *work, int index)
{
    DG_PRIM *prim;

    prim = work->prim[index];
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

void BubbleSDie_800D5B10(BubbleSWork *work)
{
    int      i;
    DG_PRIM *prim;

    for (i = 0; i < 4; i++)
    {
        prim = work->prim[i];
        if (prim)
        {
            DG_DequeuePrim(prim);
            DG_FreePrim(prim);
        }
    }
}

int BubbleSInitPrims_800D5B74(BubbleSWork *work)
{
    DG_TEX  *tex;
    int      i;
    int      k500;
    DG_PRIM *prim;

    tex = DG_GetTexture(GV_StrCode("awa_s"));
    if (!tex)
    {
        return -1;
    }

    for (i = 0; i < 4; i++)
    {
        k500 = 100;

        prim = DG_GetPrim(0x412, 1, 0, &work->pos[i], &work->rect[i]);
        work->prim[i] = prim;
        if (prim == NULL)
        {
            if (i > 0)
            {
                BubbleSDestroyPrim_800D5ACC(work, i);
            }

            return -1;
        }

        prim->field_2E_k500 = k500;

        BubbleSInitPacks_800D5388(&prim->packs[0]->poly_ft4, 1, tex);
        BubbleSInitPacks_800D5388(&prim->packs[1]->poly_ft4, 1, tex);
    }

    return 0;
}

int BubbleSGetResources_800D5C94(BubbleSWork *work, int name, int map)
{
    char *opt;
    int i;

    work->fC4 = 0;

    work->name = name;
    work->map = map;

    GM_CurrentMap_800AB9B0 = map;

    opt = GCL_GetOption('b');
    if (opt != 0)
    {
        work->bounded = 1;
        BubbleSGetSvecs_800D5334(opt, work->bounds);
    } else
    {
        work->bounded = 0;
    }

    opt = GCL_GetOption('r');
    if (opt != 0)
    {
        work->ripple = GCL_StrToInt(opt);
    }
    else
    {
        work->ripple = 0;
    }

    opt = GCL_GetOption('s');
    if (opt != 0)
    {
        BubbleSGetSvecs_800D5334(opt, &work->speed);
    }
    else
    {
        work->speed = DG_ZeroVector_800AB39C;
    }

    if (BubbleSInitPrims_800D5B74(work) < 0)
    {
        return -1;
    }

    work->fA8 = 0;
    work->fA4 = 0;

    for (i = 0; i < 4; i++)
    {
        work->f80[i] = 0;
    }

    return 0;
}

GV_ACT * NewBubbleS_800D5D9C(int name, int where, int argc, char **argv)
{
    BubbleSWork *work;

    work = (BubbleSWork *)GV_NewActor(EXEC_LEVEL, sizeof(BubbleSWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BubbleSAct_800D57A0, (TActorFunction)BubbleSDie_800D5B10, "bubble_s.c");

        if (BubbleSGetResources_800D5C94(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
