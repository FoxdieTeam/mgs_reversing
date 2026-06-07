#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    MATRIX  *world;
    RECT     rect;
    SVECTOR  pos;
    SVECTOR  last_pos;
    short    state;
    int     *force;
    int      bright;
    int      time;
    DG_TEX  *tex;
} Work;

void s08c_800C4220( MATRIX *pos ); // anime/effect/rcm2.c

static void Update0( Work *work )
{
    if ( *work->force > 0 )
    {
        work->state = 2;
        return;
    }

    if ( *work->force < 0 )
    {
        work->state = 3;
        return;
    }

    work->bright += 8;
    if ( work->bright > 150 )
    {
        work->state = 1;
    }
}

static void Update1( Work *work )
{
    if ( *work->force < 0 )
    {
        work->state = 3;
        return;
    }

    if ( work->bright < 160 && *work->force > 0 )
    {
        work->state = 2;
        return;
    }

    work->bright -= 4;
    if ( work->bright < 50 )
    {
        work->state = 0;
    }
}

static void Update2( Work *work )
{
    if ( *work->force < 0 )
    {
        work->state = 3;
        return;
    }

    work->bright += 16;
    if ( work->bright > 180 )
    {
        work->bright = 180;
        work->state = 1;
    }
}

static void Update3( Work *work )
{
    work->bright -= 16;
    if ( work->bright < 0 )
    {
        work->bright = 0;
        if ( *work->force >= 0 )
        {
            work->state = 2;
        }
    }
}

static void Update( Work *work )
{
    switch ( work->state )
    {
    case 0:
        Update0( work );
        break;
    case 1:
        Update1( work );
        break;
    case 2:
        Update2( work );
        break;
    case 3:
        Update3( work );
        break;
    }
}

static void Shade( Work *work )
{
    POLY_FT4 *pack;

    pack = work->prim->packs[ GV_Clock ];
    setRGB0( pack, work->bright, work->bright, work->bright );
}

static void Move( Work *work )
{
    SVECTOR *last_pos = &work->last_pos;
    SVECTOR pos;
    int diff;

    pos.vx = work->world->t[ 0 ];
    pos.vy = work->world->t[ 1 ];
    pos.vz = work->world->t[ 2 ];

    diff = ABS( pos.vx - last_pos->vx );
    if ( diff > 20 )
    {
        work->last_pos = pos;
        s08c_800C4220( work->world );
        return;
    }

    diff = ABS( pos.vy - last_pos->vy );
    if ( diff > 40 )
    {
        work->last_pos = pos;
        s08c_800C4220( work->world );
        return;
    }

    diff = ABS( pos.vz - last_pos->vz );
    if ( diff > 50 )
    {
        work->last_pos = pos;
        s08c_800C4220( work->world );
    }
}

static void Act( Work *work )
{
    Update( work );
    Shade( work );
    Move( work );
    work->time++;
}

static void Die( Work *work )
{
    GM_FreePrim( work->prim );
}

static void InitPack( POLY_FT4 *pack, DG_TEX *tex )
{
    setPolyFT4( pack );
    setRGB0( pack, 128, 128, 128 );
    setSemiTrans( pack, 1 );
    DG_SetPacketTexture4( pack, tex );
    pack->tpage = ( pack->tpage & ~( 3 << 5 ) ) | ( 1 << 5 );
}

static int GetResources( Work *work, MATRIX *world, int *force )
{
    RECT rect = {20, 20, 40, 40};
    SVECTOR pos = {0, 0, 100};
    DG_PRIM *prim;
    DG_TEX *tex;

    work->force = force;
    work->world = world;
    work->rect = rect;
    work->pos = pos;

    prim = work->prim = GM_MakePrim( DG_PRIM_RECTANGLE | DG_PRIM_POLY_FT4, 1, &work->pos, &work->rect );
    if ( prim == NULL )
    {
        return -1;
    }

    DG_RaisePrim( prim, 250 );
    prim->root = world;

    tex = work->tex = DG_GetTexture( GV_StrCode( "rcm_l" ) );
    if ( tex == NULL )
    {
        return -1;
    }

    InitPack( prim->packs[0], tex );
    InitPack( prim->packs[1], tex );
    return 0;
}

void *NewTenmetu( MATRIX *world, int *force )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_USER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "tenmetu.c" );
        if ( GetResources( work, world, force ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
