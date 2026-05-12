#include "anime.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define MAX_LOOP        4
#define MAX_SCRIPT      4
#define PRIM_TYPE       (DG_PRIM_OFFSET | DG_PRIM_POLY_FT4)

#define SCRIPT_RANDOM   0x80

#define MAX_SCRIPTACT   15

typedef struct _Unit
{
    int     count;
    int     anime;
    SVECTOR speed;
    u_char  r, g, b;
    u_char  now_loop;
    u_char *data;
    u_char *dataptr;
    short   loop_count[ MAX_LOOP ];
    u_char *loop_s[ MAX_LOOP ];
} Unit;

typedef struct _Work
{
    GV_ACT    actor;
    DG_TEX   *tex;
    DG_PRIM  *prim;
    RECT      rect;
    MATRIX   *world;
    int       map;
    u_char    which;
    short     dev_x, dev_y;
    short     n_anime;
    short     amb;
    short     n_verts;
    short     raise;
    SVECTOR  *vertices;
    Unit      unit[ 0 ];
} Work;

/*---------------------------------------------------------------------------*/

static void TextPack( POLY_FT4 *pack, DG_TEX *tex, int anim, Work *work )
{
    int ax, ay;
    int x, y, w, h;
    int amb;

    ax = anim % work->dev_x;
    ay = anim / work->dev_x;

    x = tex->off_x;
    w = tex->w + 1;
    pack->u0 = pack->u2 = x + ( w * ax ) / work->dev_x;
    pack->u1 = pack->u3 = x + ( w * ( ax + 1 ) ) / work->dev_x - 1;

    y = tex->off_y;
    h = tex->h + 1;
    pack->v0 = pack->v1 = y + ( h * ay ) / work->dev_y;
    pack->v2 = pack->v3 = y + ( h * ( ay + 1 ) ) / work->dev_y - 1;

    pack->tpage = tex->tpage;
    pack->clut = tex->clut;

    amb = work->amb;
    if ( ( amb & 0xfffc ) == 0 )
    {
        pack->tpage &= ~( 3 << 5 );
        pack->tpage |= work->amb << 5;
    }
}

static void UpdatePack( Work *work, int index )
{
    Unit     *unit;
    POLY_FT4 *pack;

    unit = work->unit;
    if ( work->which & ( GV_Clock + 1 ) )
    {
        pack = (POLY_FT4 *)work->prim->packs[ GV_Clock ] + index;
        TextPack( pack, work->tex, unit->anime, work );
        work->which &= ~( GV_Clock + 1 );
    }
}

static short NextShort( u_char *data, int code )
{
    short count;

    count = data[ 0 ] * 256 | data[ 1 ];
    if ( code & SCRIPT_RANDOM )
    {
        if ( count < 0 )
        {
            return -( rand() % -count );
        }
        else
        {
            return rand() % count;
        }
    }

    return count;
}

static void SetVec( SVECTOR *vec, u_char *data, int code )
{
    vec->vx = NextShort( data + 0, code );
    vec->vy = NextShort( data + 2, code );
    vec->vz = NextShort( data + 4, code );
}

static void AddVec( SVECTOR *vec, u_char *data, int code )
{
    vec->vx += NextShort( data + 0, code );
    vec->vy += NextShort( data + 2, code );
    vec->vz += NextShort( data + 4, code );
}

static int ScriptA( Work *work, int index )
{
    Unit  *unit;
    u_char n;

    unit = work->unit + index;
    n = unit->dataptr[ 1 ];
    if ( n == 0xff )
    {
        unit->anime++;
        if ( unit->anime >= work->n_anime ) unit->anime = 0;
    }
    else if ( n == 0xfe )
    {
        unit->anime = rand() % work->n_anime;
    }
    else
    {
        unit->anime = n;
    }

    work->which = 3;
    unit->dataptr += 2;
    return 0;
}

static int ScriptW( Work *work, int index )
{
    Unit *unit;

    unit = work->unit + index;
    unit->count = NextShort( unit->dataptr + 1, unit->dataptr[ 0 ] );

    unit->dataptr += 3;
    return 1;
}

static int ScriptP( Work *work, int index )
{
    Unit *unit;

    unit = work->unit + index;
    SetVec( work->vertices + index, unit->dataptr + 1, unit->dataptr[ 0 ] );

    unit->dataptr += 7;
    return 0;
}

static int ScriptM( Work *work, int index )
{
    Unit *unit;

    unit = work->unit + index;
    AddVec( work->vertices + index, unit->dataptr + 1, unit->dataptr[ 0 ] );

    unit->dataptr += 7;
    return 0;
}

static int ScriptS( Work *work, int index )
{
    Unit *unit;

    unit = work->unit + index;
    SetVec( &unit->speed, unit->dataptr + 1, unit->dataptr[ 0 ] );

    unit->dataptr += 7;
    return 0;
}

static int ScriptG( Work *work, int index )
{
    Unit *unit;

    unit = work->unit + index;
    AddVec( &unit->speed, unit->dataptr + 1, unit->dataptr[ 0 ] );

    unit->dataptr += 7;
    return 0;
}

static int ScriptT( Work *work, int index )
{
    Unit     *unit;
    int       i;
    POLY_FT4 *pack;

    unit = work->unit + index;
    work->amb = unit->dataptr[ 1 ];

    if ( !( work->amb & 0xfffc ) )
    {
        for ( i = 0; i < 2; i++ )
        {
            pack = (POLY_FT4 *)work->prim->packs[ i ];
            pack += index;
            setSemiTrans( pack, 1 );
            pack->tpage &= ~( 3 << 5 );
            pack->tpage |= work->amb << 5;
        }
    }
    else
    {
        for ( i = 0; i < 2; i++ )
        {
            pack = (POLY_FT4 *)work->prim->packs[ i ];
            pack += index;
            setSemiTrans( pack, 0 );
        }
    }

    unit->dataptr += 2;
    return 0;
}

static int ScriptV( Work *work, int index )
{
    u_char  v[3];
    Unit   *unit;
    u_char *dataptr;
    int     i;

    unit = work->unit + index;
    dataptr = unit->dataptr;

    for ( i = 0; i < 3; i++ )
    {
        dataptr++;
        v[ i ] = *dataptr;
    }

    unit->r += v[ 0 ];
    unit->g += v[ 1 ];
    unit->b += v[ 2 ];

    unit->dataptr += 4;
    return 0;
}

static void ShadePacks( Work *work )
{
    POLY_FT4 *pack;
    Unit     *unit;
    int       i;

    pack = work->prim->packs[ GV_Clock ];
    unit = work->unit;
    for ( i = work->n_verts; i > 0; i-- )
    {
        setRGB0( pack, unit->r, unit->g, unit->b );
        pack++;
        unit++;
    }
}

static int ScriptF( Work *work, int index )
{
    Unit *unit;
    short radius;

    unit = work->unit + index;
    radius = NextShort( unit->dataptr + 1, 0 );
    DG_SetTmpLight( work->vertices + index, 512, radius );

    unit->dataptr += 3;
    return 0;
}

static int ScriptZ( Work *work, int index )
{
    short   size[ 2 ];
    Unit   *unit;
    u_char *dataptr;
    int     i;
    RECT   *rect;

    unit = work->unit + index;
    dataptr = unit->dataptr + 1;

    for ( i = 0; i < 2; i++ )
    {
        size[ i ] = NextShort( dataptr, 0 );
        dataptr += 2;
    }

    rect = &work->rect;
    rect->w += size[ 0 ];
    rect->h += size[ 1 ];
    rect->x = rect->w / 2;
    rect->y = rect->h / 2;

    unit->dataptr += 5;
    return 0;
}

static int ScriptN( Work *work, int index )
{
    Unit *unit;

    unit = work->unit + index;
    GM_SeSet( work->vertices + index, unit->dataptr[ 1 ] );

    unit->dataptr += 2;
    return 0;
}

static int ScriptO( Work *work, int index )
{
    Unit *unit;
    short n;
    int   now_loop;

    unit = work->unit + index;
    n = NextShort( unit->dataptr + 1, 0 );
    unit->dataptr += 3;

    unit->now_loop++;
    now_loop = unit->now_loop;
    unit->loop_count[ now_loop ] = n;
    unit->loop_s[ now_loop ] = unit->dataptr;
    return 0;
}

static int ScriptC( Work *work, int index )
{
    Unit *unit;
    int   now_loop, count;

    unit = work->unit + index;
    now_loop = unit->now_loop;
    count = --unit->loop_count[ now_loop ];
    if ( count > 0 )
    {
        unit->dataptr = unit->loop_s[ now_loop ];
    }
    else if ( count == 0 )
    {
        unit->now_loop--;
        unit->dataptr++;
    }
    else
    {
        unit->dataptr = unit->loop_s[ now_loop ];
    }

    return 0;
}

static int ScriptL( Work *work, int index )
{
    Unit *unit;

    unit = work->unit + index;
    unit->dataptr = unit->data;
    return 1;
}

static int ScriptE( Work *work, int index )
{
    DG_InvisiblePrim( work->prim );
    GV_DestroyActor( work );
    return 1;
}

static void ApplySpeed( SVECTOR *vert, Unit *unit )
{
    vert->vx += unit->speed.vx;
    vert->vy += unit->speed.vy;
    vert->vz += unit->speed.vz;
}

/*----------------------------------------------------------------*/

static int ( *ScriptAct[] )( Work *, int ) = {
    ScriptA,
    ScriptW,
    ScriptP,
    ScriptM,
    ScriptS,
    ScriptG,
    ScriptT,
    ScriptV,
    ScriptF,
    ScriptZ,
    ScriptN,
    ScriptO,
    ScriptC,
    ScriptL,
    ScriptE
};

/*----------------------------------------------------------------*/

static void Act( Work *work )
{
    Unit    *unit;
    SVECTOR *verts;
    int      i, n;

    DG_VisiblePrim( work->prim );

    unit = work->unit;
    verts = work->vertices;
    for ( i = 0; i < work->n_verts; i++ )
    {
        if ( unit->count <= 0 )
        {
            do
            {
                n = *unit->dataptr & 0x7F;
                if ( n < 0 || n > MAX_SCRIPTACT )
                {
                    fprintf( 1, " SCRIPT ACT ERR!! \n" );
                    GV_DestroyActor( work );
                    break;
                }
            } while ( !(( *ScriptAct[ n - 1 ] )( work, i )) );
        }

        ApplySpeed( verts, unit );
        UpdatePack( work, i );
        verts++;
        unit->count--;
        unit++;
    }

    ShadePacks( work );
    GM_CurrentMap = work->map;

    if ( work->world != NULL )
    {
        DG_SetPos( work->world );
        DG_PutPrim( &work->prim->world );
    }
}

/*---------------------------------------------------------------------------*/

static void Die( Work *work )
{
    GM_FreePrim( work->prim );
}

/*---------------------------------------------------------------------------*/

static int MakeBinData( Work *work, ANIMATION *animation )
{
    int        i;
    u_char    *dataptr, *scriptptr[ MAX_SCRIPT ];
    PRESCRIPT *pre;
    int        scriptnum;
    Unit      *unit;

    dataptr = animation->script;
    scriptnum = (int)dataptr[ 2 ];

    dataptr += 3;
    for ( i = 0; i < scriptnum; i++ )
    {
        int offset;
        offset = dataptr[ 0 ] * 256 + dataptr[ 1 ];
        scriptptr[ i ] = animation->script + offset;
        dataptr += 2;
    }

    pre = animation->pre_script;
    unit = work->unit;
    for ( i = 0; i < work->n_verts; i++ )
    {
        unit->dataptr = unit->data = scriptptr[ pre->scr_num ];
        pre++;
        unit++;
    }

    return 0;
}

static void InitPacks( Work *work, u_char v )
{
    POLY_FT4 *packs[ 2 ];
    DG_PRIM  *prim;
    DG_TEX   *tex;
    Unit     *unit;
    int       i, j;
    int       x_off, y_off;
    POLY_FT4 *pack;
    int       x, y, w, h;
    int       amb;

    prim = work->prim;
    tex = work->tex;

    packs[ 0 ] = prim->packs[ 0 ];
    packs[ 1 ] = prim->packs[ 1 ];

    DG_RaisePrim( prim, work->raise );

    unit = work->unit;
    for ( i = 0; i < work->n_verts; i++ )
    {
        x_off = unit->anime % work->dev_x;
        y_off = unit->anime / work->dev_x;

        for ( j = 0; j < 2; j++ )
        {
            pack = &packs[j][ i ];
            setPolyFT4( pack );

            x = tex->off_x;
            w = tex->w + 1;
            pack->u0 = pack->u2 = x + ( w * x_off ) / work->dev_x;
            pack->u1 = pack->u3 = x + ( w * ( x_off + 1 ) ) / work->dev_x - 1;

            y = tex->off_y;
            h = tex->h + 1;
            pack->v0 = pack->v1 = y + ( h * y_off ) / work->dev_y;
            pack->v2 = pack->v3 = y + ( h * ( y_off + 1 ) ) / work->dev_y - 1;

            pack->tpage = tex->tpage;
            pack->clut = tex->clut;

            amb = work->amb;
            if ( ( amb & 0xfffc ) == 0 )
            {
                setSemiTrans( pack, 1 );
                pack->tpage &= ~( 3 << 5 );
                pack->tpage |= work->amb << 5;
            }
            else
            {
                setSemiTrans( pack, 0 );
            }

            setRGB0( pack, v, v, v );
        }

        unit++;
    }
}

static int GetResources( Work *work, int map, ANIMATION *animation )
{
    int        n_verts;
    PRESCRIPT *pre;
    Unit      *unit;
    RECT      *rect;
    int        i;

    work->which = 3;
    work->map = map;
    work->dev_x = animation->texdev_x;
    work->dev_y = animation->texdev_y;
    work->n_anime = animation->n_anime;
    work->amb = animation->amb;
    work->n_verts = n_verts = animation->n_verts;
    work->raise = animation->raise;

    pre = animation->pre_script;

    for ( i = 0; i < n_verts; i++ )
    {
        work->vertices[ i ] = pre->pos;
        pre++;
    }

    rect = &work->rect;
    rect->x = animation->size_w / 2;
    rect->y = animation->size_h / 2;
    rect->w = animation->size_w;
    rect->h = animation->size_h;

    work->prim = GM_MakePrim( PRIM_TYPE, n_verts, work->vertices, rect );
    if ( work->prim == NULL )
    {
        return -1;
    }

    work->tex = DG_GetTexture( animation->tex );

    unit = work->unit;
    pre = animation->pre_script;

    for ( i = 0; i < n_verts; i++ )
    {
        unit->count = 0;
        unit->anime = pre->s_anim;
        unit->speed = pre->speed;
        unit->r = unit->g = unit->b = animation->v;
        unit->now_loop = -1;

        unit++;
        pre++;
    }

    InitPacks( work, animation->v );
    DG_InvisiblePrim( work->prim );

    if ( MakeBinData( work, animation ) < 0 )
    {
        return -1;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewAnime( MATRIX *world, int map, ANIMATION *animation )
{
    int   n_verts;
    Work *work;

    n_verts = animation->n_verts;
    work = GV_NewActor( EXEC_LEVEL, sizeof(Work) + ( sizeof(Unit) + sizeof(SVECTOR) ) * n_verts );
    if ( work != NULL )
    {
        work->vertices = (SVECTOR *)(work->unit + n_verts);
        GV_SetNamedActor( &work->actor, Act, Die, "anime.c" );

        if ( GetResources( work, map, animation ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        else
        {
            work->world = world;
        }
    }

    return (void *)work;
}

void *NewAnime2( MATRIX *world, int map, ANIMATION *animation )
{
    Work *work;

    work = (Work *)NewAnime( NULL, map, animation );
    if ( work != NULL && world != NULL )
    {
        work->prim->world = *world;
    }

    return (void *)work;
}
