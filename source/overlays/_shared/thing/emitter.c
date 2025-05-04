#include "emitter.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  vecs[8];
    char     pad[0x4];
} Work;

/*---------------------------------------------------------------------------*/

static RECT rect_800C3320 = { 1000, 1000, 2000, 2000 };

static void ShadePacks( POLY_FT4 *packs, int n_packs, DG_TEX *unused, char shade )
{
    DG_TEX *tex;

    tex = DG_GetTexture( GV_StrCode( "sfex0236" ) );

    for ( n_packs--; n_packs >= 0; packs++, n_packs-- )
    {
        setPolyFT4( packs );
        setSemiTrans( packs, 1 );

        packs->r0 = shade;
        packs->g0 = shade;
        packs->b0 = shade;

        DG_SetPacketTexture( packs, tex ) ;

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;
    }
}

static void Die( Work *work )
{
    GM_FreePrim( work->prim ) ;
}

static int GetVecs( char *param, SVECTOR *out )
{
    int   count;
    char *res;

    count = 0;
    while ( 1 )
    {
        res = GCL_GetParamResult();
        if ( res == NULL )
        {
            break;
        }

        GCL_StrToSV( res, out );

        out++;
        count++;
    }

    return count;
}

static int GetResources( Work *work, int map, int count )
{
    int n;
    DG_PRIM *prim;
    DG_TEX  *tex;

    n = 1000;

    GM_CurrentMap = map;

    work->prim = DG_GetPrim( DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, count, 0, work->vecs, &rect_800C3320 );
    prim = work->prim;
    if ( prim == NULL )
    {
        return -1;
    }

    prim->field_2E_k500 = n;

    tex = DG_GetTexture( GV_StrCode( "sfex0236" ) );
    if ( tex == NULL )
    {
        return -1;
    }

    ShadePacks( &prim->packs[0]->poly_ft4, count, tex, 64 );
    ShadePacks( &prim->packs[1]->poly_ft4, count, tex, 72 );

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewEmitter( int name, int where, int argc, char **argv )
{
    Work *work;
    int   count;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if (work != NULL)
    {
        GV_SetNamedActor( &( work->actor ), NULL, Die, "emitter.c" );

        count = GetVecs( GCL_GetOption( 'p' ), work->vecs );
        if ( GetResources( work, where, count ) < 0 )
        {
            GV_DestroyActor( &( work->actor ) );
            return NULL;
        }
    }

    return (void *)work;
}
