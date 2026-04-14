#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"
#include "takabe/pfall.h"       // for NewPaperFall
#include "takabe/thing.h"       // for THING_Gcl_GetSVector

// clang-format off

#define RevisionDir( a )  a &= 4095
#define INIT_VEC(vec,xx,yy,zz) {(vec).vx = xx;(vec).vy = yy;(vec).vz = zz;}

/*----------------------------------------------------------------*/
extern void fprintf( long stream, char *format, ... );
#define FPRI(a) fprintf(1,(a))

#define PAPER_X 300
#define PAPER_Y 300
#define PAPER_Z 300


/*----------------------------------------------------------------*/
typedef struct  {
    GV_ACT      actor ;

    TARGET      *target ;
    MATRIX      mat ;
    SVECTOR     set;
    SVECTOR     size;
    int         map ;
    int         count ;
} Work ;

/*----------------------------------------------------------------*/
static void Act( Work *work )
{
    TARGET      *trg ;

    //OPERATOR() ;

    GM_SetCurrentMap( work->map ) ;

    trg = work->target ;

// clang-format on
    if ( work->count )
    {
        work->count--;
    }
    else
    {
        trg->class = TARGET_POWER;
    }

    if (trg->damaged & TARGET_POWER)
    {
        trg->damaged &= ~TARGET_POWER;

        if (trg->life != 0)
        {
            trg->life = 0;

            if (work->count == 0)
            {
                MATRIX world;

                GM_SeSet(&work->set, SE_UNK064);

                world = DG_ZeroMatrix;
                world.t[0] = work->mat.t[0];
                world.t[1] = work->mat.t[1];
                world.t[2] = work->mat.t[2];
                RotMatrixY(ratan2(trg->scale.vx, trg->scale.vz), &world);
                NewPaperFall(&world);

                work->count = 25;
                trg->class = TARGET_AVAIL;
            }

            trg->scale = DG_ZeroVector;
        }
    }

    GM_MoveTarget(trg, &work->set);
    GM_PushTarget(trg);
}

static void Die(Work *work)
{
    GM_FreeTarget(work->target);
}

static void InitTarget(Work *work)
{
    SVECTOR scale;
    SVECTOR size;
    TARGET *target;

    scale = DG_ZeroVector;
    INIT_VEC(size, PAPER_X, 500, PAPER_Z);

    work->target = target = GM_AllocTarget();
    target->scale = DG_ZeroVector;
    GM_SetTarget(target, TARGET_POWER, NO_SIDE, &size);
    GM_Target_8002DCCC(target, 1, -1, 0, 0, &scale);
}

static int GetResources(Work *work, int name, int where)
{
    THING_Gcl_GetSVector('p', &work->set);
    InitTarget(work);
    RotMatrix(&DG_ZeroVector, &work->mat);
    work->mat.t[0] = work->set.vx;
    work->mat.t[1] = work->set.vy;
    work->mat.t[2] = work->set.vz;
    return 0;
}

/*----------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void *NewPaper(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "paper.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        work->count = 0;
        work->map = where;
    }

    return work;
}
