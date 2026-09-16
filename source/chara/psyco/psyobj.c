#include "psyco.h"

#include "anime/animconv/anime.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "okajima/spark.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS body;
    MATRIX         light[ 2 ];
    TARGET        *target;
    TARGET         target2;
    HOMING        *hom;
    DG_PRIM       *prim;
    SVECTOR        verts[ 4 ];
    u_short        flag;
    int            vital;
    int            hit;
    int            radius;
    SVECTOR        step;
    char           unused[ 12 ];
    int            field_198;
    int            field_19C;
    int            proc_id;
    PSYOBJ        *obj;
    int            count;
} Work;

/*---------------------------------------------------------------------------*/

static int psyobj_count = 0;
static int target_vital = 36;

static PSYOBJ objlist[ 32 ];

/*---------------------------------------------------------------------------*/

extern void AN_Unknown_800CCA40( SVECTOR *pos );

/*---------------------------------------------------------------------------*/

PSYOBJ *PSYOBJ_FindObject( int name )
{
    PSYOBJ *obj;
    int i;

    obj = objlist;
    for ( i = 0; i < psyobj_count; i++ )
    {
        if ( obj->name == name ) return obj;
        obj++;
    }

    return NULL;
}

void PSYOBJ_Init( void )
{
    PSYOBJ *obj;
    int i;

    obj = objlist;
    for ( i = 0; i < 32; )
    {
        i++;
        obj->name = 0;
        obj->pos = obj->rot = DG_ZeroVector;
        obj->control = NULL;
        obj++;
    }
}

/*---------------------------------------------------------------------------*/

static inline char GetFlag( int flag, int bit )
{
    return !!( flag & ( 1 << bit ) );
}

/*---------------------------------------------------------------------------*/

static int GetRaise( DG_MDL *mdl )
{
    int raise;

    raise = 0;
    if ( mdl->flag & 0x300 )
    {
        raise = ( 4 - ( ( mdl->flag >> 12 ) & 3 ) ) * 250;
        if ( !( mdl->flag & 0x100 ) ) raise *= -1;
    }
    return raise;
}

static int s07b_800D2E14( Work *work )
{
    DG_OBJS *objs;
    DG_OBJ *obj;
    int i;
    DG_DEF *def;
    DG_MDL *model;

    objs = work->body.objs;
    obj = objs->objs;
    for ( i = objs->n_models; i > 0; i-- )
    {
        DG_FreeObjPacket( obj, 0 );
        DG_FreeObjPacket( obj, 1 );
        obj++;
    }

    def = objs->def = GV_GetCache( GV_CacheID( GV_StrCode( "07b_o11" ), 'k' ) );
    model = def->models;
    obj = objs->objs;
    for ( i = def->n_x_models; i > 0; i-- )
    {
        obj->model = model;
    
        if ( model->extend < 0 )
        {
            obj->extend = NULL;
        }
        else
        {
            obj->extend = objs->objs + model->extend;
        }

        obj->raise = GetRaise( model );
        obj->n_packs = model->n_faces;

        obj++;
        model++;
    }

    return 0;
}

static void s07b_800D2F2C( Work *work )
{
    SVECTOR tmp;
    TARGET *trg;

    work->obj->flag &= ~0x80;

    if ( ( GM_PlayerStatus & PLAYER_INVINCIBLE ) ||
         ( GM_GameStatus & STATE_PADRELEASE ) ||
         !( work->obj->flag & 0x10 ) ) return;

    GV_SubVec3( &work->control.mov, &GM_PlayerPosition, &tmp );
    if ( GV_VecLen3( &tmp ) > 1000 ) return;

    trg = &work->target2;
    trg->damaged = 0;
    trg->vital = target_vital;
    GM_MoveTarget( trg, &work->control.mov );
    trg->force.vx = work->control.step.vx / 4;
    trg->force.vy = work->control.step.vy / 4;
    trg->force.vz = work->control.step.vz / 4;

    work->target->class &= ~TARGET_POWER;

    if ( GM_PowerTarget( trg ) )
    {
        GM_SeSetMode( &work->control.mov, SE_HIT, GM_SEMODE_BOMB );
        work->obj->flag |= 0x80;
    }

    work->target->class |= TARGET_POWER;
}

static void s07b_800D30B4( Work *work )
{
    MATRIX mat;
    SVECTOR pos;
    GCL_ARGS arg;
    long data[ 1 ];
    TARGET *trg;
    int a_mode;

    trg = work->target;

    work->obj->flag &= ~0x40;
    if ( !( work->obj->flag & 0x20 ) )
    {
        trg->damaged = 0;
        trg->class &= ~TARGET_POWER;
        return;
    }

    trg->class |= TARGET_POWER;
    if ( !( trg->damaged & TARGET_POWER ) ) return;
    trg->damaged &= ~TARGET_POWER;
    if ( GetFlag( work->obj->flag, 15 ) ) trg->vital += trg->damage;

    a_mode = trg->a_mode;
    trg->damage = 0;
    trg->a_mode = 0;

    if ( a_mode == 1 )
    {
        GM_SeSet( &work->control.mov, 40 );
        NewSpark( &work->body.objs->world, 0 );
        GM_SeSet( &work->control.mov, 39 );
        if ( !( GetFlag( work->obj->flag, 15 ) ) ) trg->vital--;
    }
    else if ( a_mode == 2 )
    {
        if ( !( GetFlag( work->obj->flag, 15 ) ) ) trg->vital -= 255;
    }

    work->obj->flag |= 0x40;
    
    if ( trg->vital > 0 || ( GetFlag( work->obj->flag, 15 ) ) ) return;
            
    GM_SeSet( &work->control.mov, 184 );

    work->obj->flag |= 0x8100;
    s07b_800D2E14( work );
            
    ReadRotMatrix( &mat );
    pos = work->control.mov;
    pos.vy += 500;
    NewAnime_8005E090( &pos );
    AN_Unknown_800CCA40( &pos );

    if ( work->proc_id >= 0 )
    {
        arg.argc = 1;
        arg.argv = data;
        data[ 0 ] = GetFlag( work->obj->flag, 8 );
        GCL_ExecProc( work->proc_id, &arg );
    }
}

static void s07b_800D3308( Work *work )
{
    MATRIX world;
    int levels[ 2 ];
    MATRIX mat;

    if ( !( work->obj->flag & 0x8 ) )
    {
        DG_InvisiblePrim( work->prim );
        return;
    }

    if ( work->control.r_sphere == -2 )
    {
        ReadRotMatrix( &mat );
        levels[ 0 ] = -32000;
        levels[ 1 ] = 32000;
        HZD_LevelHazardCheck( work->control.map->hzd, &work->control.mov, HZD_CHK_FLOOR );
        HZD_GetLevelHeight( levels );
        DG_SetPos( &mat );
        work->control.levels[ 0 ] = levels[ 0 ];
    }

    DG_VisiblePrim( work->prim );

    world = DG_ZeroMatrix;
    DG_COPY_VEC( (VECTOR *)world.t, &work->control.mov );
    world.t[ 1 ] = work->control.levels[ 0 ];
    work->prim->world = world;
}

static void s07b_800D3494( Work *work )
{
    TARGET *trg;

    trg = work->target;
    if ( !( work->obj->flag & 0x800 ) )
    {
        work->hit = 0;
        trg->class &= ~TARGET_PUSH;
        trg->damaged &= ~TARGET_PUSH;
        trg->offset = DG_ZeroVector;
        trg->force = DG_ZeroVector;
    }
    else
    {
        trg->class |= TARGET_PUSH;
        trg->damaged |= TARGET_PUSH;
        work->control.step = work->step;
        work->hit = 0;

        if ( trg->damaged & TARGET_PUSH )
        {
            trg->damaged &= ~TARGET_PUSH;
            work->control.step.vx += trg->offset.vx;
            work->control.step.vz += trg->offset.vz;
            work->hit = 1;
        }

        trg->force = DG_ZeroVector;

        if ( GM_PushTarget( trg ) )
        {
            work->control.step.vx /= 2;
            work->control.step.vz /= 2;
            work->hit = 1;
        }
    }
}

static void Act( Work *work )
{
    if ( work->obj->flag & 0x10000 )
    {
        work->control.r_sphere = -2;
        work->control.s_sphere = -2;
    }
    else if ( work->control.step.vx == 0 &&
              work->control.step.vy == 0 &&
              work->control.step.vz == 0 )
    {
        work->control.r_sphere = -2;
        work->control.s_sphere = -2;
    }
    else
    {
        work->control.r_sphere = work->radius;
        work->control.s_sphere = work->radius;
    }

    GM_ActControl( &work->control );
    GM_ActObject2( (OBJECT *)&work->body );

    if ( work->count < 4 )
    {
        DG_GetLightMatrix( &work->control.mov, work->light );
        work->count++;
    }

    GM_MoveTarget( work->target, &work->control.mov );
    s07b_800D3308( work );

    if ( work->hom != NULL )
    {
        if ( work->obj->flag & 0x400 )
        {
            work->hom->flag = 1;
        }
        else
        {
            work->hom->flag = 0;
        }
    }

    s07b_800D2F2C( work );
    s07b_800D30B4( work );
    s07b_800D3494( work );
}

static void Die( Work *work )
{
    work->obj->pos = work->control.mov;
    work->obj->rot = work->control.rot;
    work->obj->control = NULL;

    GM_FreeObject( (OBJECT *)&work->body );
    if ( work->target != NULL ) GM_FreeTarget( work->target );
    GM_FreePrim( work->prim );

    if ( work->flag & 0x4 )
    {
        if ( work->hom != NULL ) GM_FreeHomingTarget( work->hom );
    }

    GM_FreeControl( &work->control );
    psyobj_count--;
}

static int InitShadow( Work *work )
{
    DG_PRIM *prim;
    DG_TEX *tex;
    int i;
    POLY_FT4 *pack;
    SVECTOR *vert;

    prim = GM_MakePrim( DG_PRIM_POLY_FT4, 1, work->verts, NULL );
    if ( prim == NULL ) return -1;

    tex = DG_GetTexture( GV_StrCode( "shadow" ) );
    if ( tex == NULL ) return -1;

    for ( i = 0; i < 2; i++ )
    {
        pack = prim->packs[ i ];
        setPolyFT4( pack );
        setSemiTrans( pack, 1 );
        setRGB0( pack, 72, 72, 72 );
        DG_SetPacketTexture4( pack, tex );
    }

    vert = work->verts;
    for ( i = 0; i < 4; i++ )
    {
        *vert = DG_ZeroVector;
        vert->vx = ( i & 1 ) ? 450 : -450;
        vert->vz = ( i & 2 ) ? 450 : -450;
        vert->vy = 0;
        vert++;
    }

    DG_RaisePrim( prim, 500 );
    work->prim = prim;

    work->obj->flag |= 0x8;
    return 0;
}

static int InitTarget( Work *work )
{
    SVECTOR size;
    TARGET *trg;
    int class, level, i, p_mode, a_mode;

    if ( GCL_GetOption( 't' ) )
    {
        GCL_StrToSV( GCL_NextStr(), (short *)&size );
    }
    else
    {
        size = DG_ZeroVector;
    }

    work->target = trg = GM_AllocTarget();
    if ( trg == NULL ) return -1;

    class = TARGET_SEEK;
    if ( work->flag & 0x1 )
    {
        class |= TARGET_POWER;
        work->obj->flag |= 0x20;
    }
    if ( work->flag & 0x2 ) class |= TARGET_PUSH;

    GM_SetTarget( trg, class, NO_SIDE, &size );
    GM_SetPowerTarget( trg, POWER_CONST, -1, work->vital, 0, &DG_ZeroVector );

    if ( work->flag & 0x4 )
    {
        work->hom = GM_AllocHomingTarget( &work->body.objs->world, &work->control );
        work->hom->flag = 0;
    }
    else
    {
        work->hom = NULL;
    }

    if ( GCL_GetOption( 'a' ) )
    {
        GCL_StrToSV( GCL_NextStr(), (short *)&size );
    }
    else
    {
        size = DG_ZeroVector;
    }

    if ( GCL_GetOption( 'x' ) )
    {
        level = GM_GameLevel;
        if ( level < 0 ) level = 0;

        for ( i = 0; i < level; i++ )
        {
            GCL_GetNextInt();
        }

        target_vital = GCL_GetNextInt();
    }

    trg = &work->target2;
    if ( work->obj->flag & 0x2000 )
    {
        a_mode = 2;
        p_mode = POWER_DECREASE;
    }
    else
    {
        a_mode = 3;
        p_mode = POWER_CONST;
    }

    GM_SetTarget( trg, TARGET_POWER, ENEMY_SIDE, &size );
    GM_SetPowerTarget( trg, p_mode, a_mode, target_vital, 0, &DG_ZeroVector );
    return 0;
}

static void InitFlag( Work *work )
{
    char *opt;
    int i, flag;

    work->flag = 0;
    work->vital = 0;

    opt = GCL_GetOption( 'f' );
    if ( opt == NULL ) return;

    for ( i = 0; i < 6; i++ )
    {
        if ( i < 3 )
        {
            flag = GCL_StrToInt( opt );
            if ( flag != 0 )
            {
                work->flag |= 1 << i;
                if ( i == 0 )
                {
                    if ( flag >= 2 ) work->obj->flag |= 0x8000;
                    if ( flag == 3 ) work->obj->flag |= 0x100;
                }
            }
        }
        else if ( i == 3 )
        {
            work->vital = GCL_StrToInt( opt );
        }
        else if ( i == 4 )
        {
            if ( !GCL_StrToInt( opt ) ) work->obj->flag &= ~0x8;
        }
        else if ( i == 5 )
        {
            if ( GCL_StrToInt( opt ) ) work->obj->flag |= 0x2000;
        }
        opt = GCL_NextStr();
    }
}

static int GetResources( Work *work, int name, int where )
{
    SVECTOR tmp;
    PSYOBJ *obj;
    CONTROL *control;
    OBJECT_NO_ROTS *body;
    u_short model;

    if ( GCL_GetOption( 'c' ) && GCL_StrToInt( GCL_NextStr() ) != 0 )
    {
        psyobj_count = 0;
        work->flag = 0xFFFF;
        return -1;
    }

    control = &work->control;
    if ( GM_InitControl( control, 0, where ) < 0 ) return -1;

    obj = &objlist[ psyobj_count ];
    psyobj_count++;

    obj->name = name;
    GM_ConfigControlString( control, GCL_GetOption( 'p' ), GCL_GetOption( 'd' ) );
    obj->pos = control->mov;
    obj->rot = control->rot;
    obj->flag = 0;
    obj->control = control;
    work->obj = obj;

    if ( GCL_GetOption( 'h' ) )
    {
        GCL_StrToSV( GCL_NextStr(), (short *)&tmp );
        GM_ConfigControlHazard( control, tmp.vz, tmp.vx, tmp.vy );
        work->radius = tmp.vx;
    }
    else
    {
        GM_ConfigControlHazard( control, 0, -2, -2 );
        work->radius = -2;
    }

    control->seg_flag = HZD_SEG_NO_MISSILE;

    body = &work->body;
    if ( !GCL_GetOption( 'm' ) ) return -1;

    model = GCL_StrToInt( GCL_NextStr() ) & 0xFFFF;
    GM_InitObjectNoRots( body, model, 0x6D, 0 );
    GM_ConfigObjectLight( (OBJECT* )body, work->light );

    if ( GCL_GetOption( 'e' ) )
    {
        work->proc_id = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->proc_id = -1;
    }

    if ( InitShadow( work ) < 0 ) return -1;
    InitFlag( work );
    if ( InitTarget( work ) < 0 ) return -1;

    work->hit = 0;
    work->field_198 = 32;
    work->field_19C = 0;
    return 0;
}

void *NewPsychoObject( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "psyobj.c" );
        if ( GetResources( work, name, where ) < 0 )
        {
            GV_DestroyActor( work );
            if ( work->flag == 0xFFFF ) return (void *)work;
            return NULL;
        }
    }
    return (void *)work;
}
