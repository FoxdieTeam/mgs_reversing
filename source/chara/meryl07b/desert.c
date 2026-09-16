#include "anime/animconv/anime.h"
#include "game/game.h"
#include "okajima/bullet.h"

/*---------------------------------------------------------------------------*/

#define BODY_DATA   GV_StrCode( "desert" )
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

#define BULLET_FLAG ( BULLET_FLASH | BULLET_RECOILSPARK )

typedef struct _Work {
    GV_ACT         actor;
    OBJECT_NO_ROTS body;
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    int            unit;
    u_long        *trigger;
    int            side;
} Work;

static SVECTOR desert_pos = {20, -370, 60};
static u_short desert_damage = 96;

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    MATRIX world;
    SVECTOR rot;
    int trigger;
    DG_OBJS *objs;

    GM_SetCurrentMap( work->root_ctrl->map->index );
    DG_GroupObjsEx( work->body.objs );

    trigger = *work->trigger;

    if ( work->root_obj->objs->flag & DG_FLAG_INVISIBLE )
    {
        DG_InvisibleObjs( work->body.objs );
    }
    else
    {
        DG_VisibleObjs( work->body.objs );
    }

    if ( trigger & 2 )
    {
        objs = work->body.objs;
        rot.vx = 1024;
        rot.vy = rot.vz = 0;
        DG_SetPos( &objs->world );
        DG_MovePos( &desert_pos );
        DG_RotatePos( &rot );
        ReadRotMatrix( &world );

        NewBulletEx( BULLET_FLAG, &world, ENEMY_SIDE, 0, 0, 100, desert_damage, 10000, 750 );
        GM_SeSet( &work->root_ctrl->mov, SE_SOCOM_SHOT2 );
        AN_SocomFlash( &objs->world, &world, 0 );
    }
}

static void Die( Work *work )
{
    GM_FreeObject( (OBJECT *)&work->body );
}

static int GetResources( Work *work, OBJECT *root_obj, int unit )
{
    OBJECT_NO_ROTS *body;

    body = &work->body;
    GM_InitObjectNoRots( body, BODY_DATA, BODY_FLAG, 0 );
    GM_ConfigObjectRoot( (OBJECT *)body, root_obj, unit );
    return 0;
}

void *NewDesertEagle( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *trigger, int side )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "desert.c" );
        if ( GetResources( work, root_obj, unit ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        work->root_ctrl = root_ctrl;
        work->root_obj = root_obj;
        work->unit = unit;
        work->trigger = trigger;
        work->side = side;
    }
    return (void *)work;
}
