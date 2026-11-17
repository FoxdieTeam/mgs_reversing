#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT          actor;
    CONTROL         control;
    OBJECT          body;
    DG_OBJS         objs;
    MOTION_CONTROL  m_ctrl;
    MOTION_SEGMENT  m_segs1[17];
    MOTION_SEGMENT  m_segs2[17];
    SVECTOR         rots[16];
    int             field_760;
    int             field_764;
    int             pad_768;
} Work;

/*---------------------------------------------------------------------------*/

static void CopyMotionSegs( MOTION_SEGMENT *dst, MOTION_SEGMENT *src, int mask )
{
    int i;

    for ( i = 0; i < 16; i++, dst++, src++ ) {
        if ( mask & 1 ) {
            dst->base = src->base;
        }
        mask >>= 1;
    }
}

static void Act( Work *work )
{
    int i;

    if ( GM_PlayerBody == NULL ) return;
    if ( GM_PlayerControl == NULL ) return;
    if ( GM_uTenageMotion == -1 ) return;

    if ( work->field_760 == 0 ) {
        for ( i = 0; i < 16; i++ ) {
            work->rots[i] = GM_PlayerBody->objs->rots[i];
            work->body.height = GM_PlayerBody->height;
        }
        *work->body.objs->waist_rot = *GM_PlayerBody->objs->waist_rot;
        if ( GM_PlayerBody->action2 == 50 ) {
            work->field_760 = 1;
            work->field_764 = 0;
        }
    }
    else if ( work->field_760 == 1 ) {
        int motion = work->field_764;
        int mask;

        work->field_764 = motion + 1;
        mask = GM_PlayerBody->m_ctrl->info1.mask;
        if ( motion == 0 ) {
            CopyMotionSegs( work->body.m_ctrl->info1.m_segs, GM_PlayerBody->m_ctrl->info1.m_segs, mask );
            GM_ConfigObjectAction( &work->body, GM_uTenageMotion, 0, 4 );
        }
        GM_ActMotion( &work->body );
        GM_PlayerBody->height = work->body.height;
        {
            int m = mask;
            for ( i = 0; i < 16; i++ ) {
                if ( m & 1 ) {
                    GM_PlayerBody->objs->rots[i] = work->rots[i];
                }
                m >>= 1;
            }
        }
        *GM_PlayerBody->objs->waist_rot = *work->body.objs->waist_rot;
        if ( work->body.m_ctrl->info1.frames_left == 2 || GM_PlayerBody->action2 != 50 ) {
            CopyMotionSegs( GM_PlayerBody->m_ctrl->info1.m_segs, work->body.m_ctrl->info1.m_segs, mask );
            GM_PlayerBody->m_ctrl->interp = 4;
            work->field_760 = 2;
        }
    } else {
        if ( GM_PlayerBody->action2 != 50 ) {
            work->field_760 = 0;
        }
    }
}

static void Die( Work *work )
{
    GM_FreeControl( &work->control );
    GM_FreeObject( &work->body );
}

static int GetResources( Work *work, int name )
{
    work->body.objs = &work->objs;
    GM_ConfigMotionControl( &work->body, &work->m_ctrl, name,
        work->m_segs1, work->m_segs2, &work->control, work->rots );
    work->field_760 = 0;
    work->field_764 = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewM1Throw( int name )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof( Work ) );
    if ( work != NULL ) {
        GV_SetNamedActor( &work->actor, Act, Die, "m1throw.c" );
        if ( GetResources( work, name ) >= 0 ) {
            return (void *)work;
        }
        GV_DestroyActor( &work->actor );
    }
    return NULL;
}
