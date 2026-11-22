#include <sys/types.h>
#include <kernel.h>
#include <libapi.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

#include "game.h"

/*----------------------------------------------------------------*/

int SECTION(".sbss") fc_rt;     // Unused?
int SECTION(".sbss") mt_rt1;    // Unused?
int SECTION(".sbss") mt_rt2;
int SECTION(".sbss") fc_cnt;    // Unused?
int SECTION(".sbss") mt_count;

STATIC int SECTION(".sbss") dword_800ABAC4;

/*----------------------------------------------------------------*/

static inline short SetPItoPI( short v )
{
    v &= 4095;
    if ( v > 2048 ) v -= 4096;
    return v;
}

SVECTOR *sub_80034834( SVECTOR *out, SVECTOR *v1, SVECTOR v2 )
{
    SVECTOR tmp;

    tmp.vx = SetPItoPI( ( v2.vx & 0xffff ) - v1->vx );
    tmp.vy = SetPItoPI( ( v2.vy & 0xffff ) - v1->vy );
    tmp.vz = SetPItoPI( ( v2.vz & 0xffff ) - v1->vz );

    *out = tmp;
    return out;
}

void GM_ActObjectMotion( OBJECT *obj )
{
    long intime, outtime;
    intime = GetRCnt( RCntCNT1 );

    SetSpadStack( SPAD_STACK_ADDR );
    GM_PlayAction( obj->m_ctrl );
    ResetSpadStack();

    obj->is_end = obj->m_ctrl->info1.time;
    obj->time2 = obj->m_ctrl->info2.time;
//#ifdef DEBUG
    outtime = GetRCnt( RCntCNT1 );
    mt_rt2 += ( outtime - intime ) & 0xffff;
    mt_count++;
//#endif
    if ( obj->m_ctrl->interp )
        obj->m_ctrl->interp--; /* 補完カウンタ変更 */
    return;
}

/*----------------------------------------------------------------*/

void GM_InitObjectNoRots( OBJECT_NO_ROTS *obj, int model, int flag, int motion )
{
    ASSERT( model != 0 );
    GV_ZeroMemory( obj, sizeof( OBJECT_NO_ROTS ) );
    obj->flag = flag;
    obj->light = &DG_LightMatrix;
    obj->map_name = GM_CurrentMap;
    /*
        モデル／モーション初期化
    */
    GM_ConfigObjectModel( obj, model );
}

void GM_InitObject( OBJECT *obj, int model, int flag, int motion )
{
    GV_ZeroMemory( obj->rots, sizeof( SVECTOR ) * DG_MAX_JOINTS );
    GM_InitObjectNoRots( ( OBJECT_NO_ROTS * )obj, model, flag, motion );
}

/*--------- M.Sonoyama 実験中 --------------*/

/* モーション処理を行なう */
void GM_ActMotion( OBJECT *obj )
{
    SVECTOR step;

    if ( obj->m_ctrl != NULL ) {
        step = *obj->m_ctrl->step;
        GM_ActObjectMotion( obj );
        GV_AddVec3( &step, obj->m_ctrl->step, obj->m_ctrl->step );
    }
}

void GM_ActObject( OBJECT *obj )
{
    DG_PutObjs( obj->objs );

    if ( obj->map_name != GM_CurrentMap ) {
        obj->map_name = GM_CurrentMap;
        DG_GroupObjs( obj->objs, GM_CurrentMap );
    }

    if ( obj->m_ctrl != NULL ) {
        *obj->m_ctrl->step = DG_ZeroVector;
    }
}

void GM_ActObject2( OBJECT *obj )
{
    DG_PutObjs( obj->objs );

    if ( obj->map_name != GM_CurrentMap ) {
        obj->map_name = GM_CurrentMap;
        DG_GroupObjs( obj->objs, GM_CurrentMap );
    }

    if ( obj->m_ctrl != NULL ) {
        GM_ActObjectMotion( obj );
    }
}

void GM_FreeObject( OBJECT *obj )
{
    DG_OBJS *objs = obj->objs;

    if ( objs ) {
        DG_DequeueObjs( objs );
        DG_FreeObjs( objs );
    }
}

/*----------------------------------------------------------------*/

void GM_ConfigObjectFlags( OBJECT *obj, int flags )
{
    obj->flag = flags;
    obj->objs->flag = flags;
}

void GM_ConfigObjectLight( OBJECT *obj, MATRIX *light )
{
    obj->light = light;
    obj->objs->light = light;
}

void GM_ConfigObjectStep( OBJECT *obj, SVECTOR *step )
{
    /* do nothing */
}

void GM_ConfigObjectRoot( OBJECT *obj, OBJECT *org, int unit )
{
    MATRIX  *light;
    DG_OBJS *objs = obj->objs;

    if ( org == NULL || unit < 0 ) {
        light = &DG_LightMatrix;
        objs->root = NULL;
    } else {
        objs->root = &org->objs->objs[unit].world;
        light = org->light;
    }

    obj->light = light;
    objs->light = light;
}

void GM_ConfigObjectJoint( OBJECT *obj )
{
    obj->objs->rots = obj->rots;
}

void GM_ConfigObjectSlide( OBJECT *obj )
{
    obj->objs->movs = obj->rots;
}

void GM_ConfigObjectAction( OBJECT *obj, int action, int time, int interp )
{
    if ( obj->m_ctrl ) {
        GM_ConfigAction( obj->m_ctrl, action, time );
        obj->action = action;
        obj->is_end = 0;
        obj->m_ctrl->interp = interp;
    }
}

void GM_ConfigObjectOverride( OBJECT *obj, int action, int time, int interp, u_long mask )
{
    if ( mask != 0 ) {
        if ( obj->m_ctrl == NULL ) return;
        GM_ConfigActionOverride( obj->m_ctrl, action, time );
    } else {
        obj->m_ctrl->info2.field_14 = 0;
        if ( obj->m_ctrl->info1.field_14 == 0 ) {
            obj->m_ctrl->info1.field_14 = 2;
        }
    }

    obj->action2 = action;
    obj->time2 = 0;
    obj->m_ctrl->interp = interp;
    obj->m_ctrl->info1.mask = mask;
    obj->m_ctrl->info2.mask = ~mask;
}

int GM_ConfigObjectMotion( OBJECT *obj, int action, int interp )
{
    GM_ConfigObjectAction( obj, obj->action, 0, interp );
    return 0;
}

int GM_ConfigObjectModel( OBJECT_NO_ROTS *obj, int model )
{
    DG_DEF  *def;
    DG_OBJS *objs;
    DG_OBJS *current_objs = obj->objs;

    def = GV_GetCache( GV_CacheID( model, 'k' ) );
    objs = DG_MakeObjs( def, obj->flag, 0 );

    if ( objs == NULL )
        return -1;

    if ( current_objs ) {
        DG_DequeueObjs( current_objs );
        DG_FreeObjs( current_objs );
    }

    obj->objs = objs;
    objs->light = obj->light;
    objs->group_id = obj->map_name;
    DG_QueueObjs( objs );

    return 0;
}
