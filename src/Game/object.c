#include "object.h"

#include <sys/types.h>
#include <kernel.h>
#include <libapi.h>

#include "common.h"
#include "game.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "motion.h"

/*-----sbss---------------------------------------*/
extern int GM_CurrentMap;

int SECTION(".sbss") fc_rt;     // Unused?
int SECTION(".sbss") mt_rt1;    // Unused?
int SECTION(".sbss") mt_rt2;
int SECTION(".sbss") fc_cnt;    // Unused?
int SECTION(".sbss") mt_count;

STATIC int SECTION(".sbss") dword_800ABAC4;
/*------------------------------------------------*/

//not sure if this one belongs here
SVECTOR *sub_80034834(SVECTOR *arg0, SVECTOR *arg1, SVECTOR arg2)
{
    SVECTOR vec;

    // TODO: this should be able to be matched without casting to unsigned short
    vec.vx = FP_Subtract((unsigned short)arg2.vx, (unsigned short)arg1->vx);
    vec.vy = FP_Subtract((unsigned short)arg2.vy, (unsigned short)arg1->vy);
    vec.vz = FP_Subtract((unsigned short)arg2.vz, (unsigned short)arg1->vz);

    *arg0 = vec;
    return arg0;
}

void sub_800348F4(OBJECT *obj)
{
    long intime, outtime;
    intime = GetRCnt(RCntCNT1);

    SetSpadStack(SPAD_STACK_ADDR);
    sub_8003556C(obj->m_ctrl); // motion streaming related
    ResetSpadStack();

    obj->is_end = obj->m_ctrl->info1.time;
    obj->time2 = obj->m_ctrl->info2.time;
//#ifdef DEBUG
    outtime = GetRCnt(RCntCNT1);
    mt_rt2 += (outtime - intime) & 0xffff;
    mt_count++;
//#endif
    if (obj->m_ctrl->interp)
        obj->m_ctrl->interp--; /* 補完カウンタ変更 */
    return;
}

/*----------------------------------------------------------------*/

void GM_InitObjectNoRots( OBJECT_NO_ROTS *obj, int model, int flag, int motion )
{
    //ASSERT( model != 0 );
    GV_ZeroMemory( obj, sizeof(OBJECT_NO_ROTS) );
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
    GV_ZeroMemory( obj->rots, sizeof(SVECTOR) * DG_MAX_JOINTS );
    GM_InitObjectNoRots( (OBJECT_NO_ROTS *)obj, model, flag, motion );
}

/*--------- M.Sonoyama 実験中 --------------*/

// adds initial step to mutation from another function
void GM_ActMotion(OBJECT *obj)
{
    SVECTOR step;

    if (obj->m_ctrl)
    {
        step = *obj->m_ctrl->step;
        sub_800348F4(obj);
        GV_AddVec3(&step, obj->m_ctrl->step, obj->m_ctrl->step);
    }
}

// sets objects name and objs group id
// if object has a motion control its step is zero'd
void GM_ActObject(OBJECT *obj)
{
    DG_PutObjs(obj->objs);

    if (obj->map_name != GM_CurrentMap)
    {
        int group_id = GM_CurrentMap;
        obj->map_name = GM_CurrentMap;
        obj->objs->group_id = group_id;
    }

    if (obj->m_ctrl)
    {
        *obj->m_ctrl->step = DG_ZeroVector;
    }
}

// sets objects name objs groups id
// if object has a motion control a separate function
// to set up motion is called
void GM_ActObject2(OBJECT *obj)
{
    DG_PutObjs(obj->objs);

    if (obj->map_name != GM_CurrentMap)
    {
        int group_id = GM_CurrentMap;
        obj->map_name = GM_CurrentMap;
        obj->objs->group_id = group_id;
    }

    if (obj->m_ctrl)
    {
        sub_800348F4(obj);
    }
}

// frees an objs object
void GM_FreeObject(OBJECT *obj)
{
    DG_OBJS *objs = obj->objs;

    if (objs)
    {
        DG_DequeueObjs(objs);
        DG_FreeObjs(objs);
    }
}

// configures object flag attribute
void GM_ConfigObjectFlags(OBJECT *obj, int flags)
{
    obj->flag = flags;
    obj->objs->flag = flags;
}

// configures object light attribute
void GM_ConfigObjectLight(OBJECT *obj, MATRIX *light)
{
    obj->light = light;
    obj->objs->light = light;
}

// configures object step attribute but is stubbed in game
void GM_ConfigObjectStep(OBJECT *obj, SVECTOR *step)
{
    /* do nothing */
}

// configures object's root to the parents world attribute
// also sets the light depending on if parent exists or not
void GM_ConfigObjectRoot(OBJECT *obj, OBJECT *parent_obj, int num_parent)
{
    MATRIX  *light;
    DG_OBJS *objs = obj->objs;

    if (!parent_obj || num_parent < 0)
    {
        light = &DG_LightMatrix;
        objs->root = 0;
    }
    else
    {
        objs->root = &parent_obj->objs->objs[num_parent].world;
        light = parent_obj->light;
    }

    obj->light = light;
    objs->light = light;
}

// configures object rots attribute
void GM_ConfigObjectJoint(OBJECT *obj)
{
    obj->objs->rots = obj->rots;
}

// configures object flag slide attribute
void GM_ConfigObjectSlide(OBJECT *obj)
{
    obj->objs->movs = obj->rots;
}

// configures the attributes of an objects motion control struct
void GM_ConfigObjectAction(OBJECT *obj, int action_flag, int motion, int interp)
{
    if (obj->m_ctrl)
    {
        sub_8003501C(obj->m_ctrl, action_flag, motion);
        obj->action_flag = action_flag;
        obj->is_end = 0;
        obj->m_ctrl->interp = interp;
    }
}

//
void GM_ConfigObjectOverride(OBJECT *obj, int a1, int motion, int interp, int a4)
{
    if (a4)
    {
        if (!obj->m_ctrl)
            return;
        sub_800350D4(obj->m_ctrl, a1, motion);
    }
    else
    {
        obj->m_ctrl->info2.field_14 = 0;
        if (!obj->m_ctrl->info1.field_14)
        {
            obj->m_ctrl->info1.field_14 = 2;
        }
    }

    obj->field_10 = a1;
    obj->time2 = 0;
    obj->m_ctrl->interp = interp;
    obj->m_ctrl->info1.field_8 = a4;
    obj->m_ctrl->info2.field_8 = ~a4;
}

// calls configObjectAction with given values
int GM_ConfigObjectMotion(OBJECT *obj, int action_flag, int motion)
{
    GM_ConfigObjectAction(obj, obj->action_flag, 0, motion);
    return 0;
}

// gets the objects buffer from cache and allocates memory for
// creating a new object. Dequeues existing objects that it may have
int GM_ConfigObjectModel(OBJECT_NO_ROTS *obj, int model)
{
    int      id;
    void    *buf;
    DG_OBJS *objs;
    DG_OBJS *current_objs = obj->objs;

    id = GV_CacheID(model, 'k');
    buf = GV_GetCache(id);
    objs = DG_MakeObjs(buf, obj->flag, 0);

    if (!objs)
        return -1;

    if (current_objs)
    {
        DG_DequeueObjs(current_objs);
        DG_FreeObjs(current_objs);
    }

    obj->objs = objs;
    objs->light = obj->light;
    objs->group_id = obj->map_name;
    DG_QueueObjs(objs);

    return 0;
}
