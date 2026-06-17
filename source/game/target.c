#include "target.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "game.h"
#include "linkvar.h"

// Instead of dynamically allocating TARGETs,
// the game uses the big TARGET array GM_TargetDatas.
//
// This also makes it easier to iterate over all TARGETs in use.
//
// Therefore each entry in this array will be either:
// - already used up (returned by GM_AllocTarget and not yet freed)
// - not used (target->class == 0)
//
// When allocating new TARGETs, the game will try to find a "free" slot in this array.
// It tries to do it efficiently (without having to scan the whole array too often).
// The game tries to ensure that slots [0, GM_TargetCount)
// are all actively used, while the latter part of the array is free.
// However, deallocating TARGETs can result in "holes" in that contiguous prefix.
//
// Two indicies are maintained:
// - GM_TargetCount:
//      slots [0, GM_TargetCount) are potentially used
//      slots [GM_TargetCount, TARGET_MAX) are definitely not used
// - GM_StaleTargetCount:
//      how many slots [0, GM_TargetCount) are not used
//
// In most cases the game will just take GM_TargetCount+1
// as a next used slot. If a TARGET is freed in the middle of the array
// (gets orphaned: GM_StaleTargetCount) the code will try
// to "plug" the hole when allocating the next target.
//
// Example:
//   - [Target1, Target2, Target3, FREE, FREE, FREE, FREE...]
//     GM_TargetCount = 3, GM_StaleTargetCount = 0
//
//   - GM_AllocTarget()
//
//   - [Target1, Target2, Target3, Target4, FREE, FREE, FREE...]
//     GM_TargetCount = 4, GM_StaleTargetCount = 0
//
//   - GM_FreeTarget(Target3)
//
//   - [Target1, Target2, FREE, Target4, FREE, FREE, FREE...]
//     GM_TargetCount = 4, GM_StaleTargetCount = 1
//
//   - GM_AllocTarget()
//
//   - [Target1, Target2, Target5, Target4, FREE, FREE, FREE...]
//     GM_TargetCount = 4, GM_StaleTargetCount = 0
//
//   - GM_FreeTarget(Target4)
//
//   - [Target1, Target2, Target5, FREE, FREE, FREE, FREE...]
//     GM_TargetCount = 3, GM_StaleTargetCount = 0
//
extern TARGET GM_TargetDatas[TARGET_MAX];

STATIC int SECTION(".sbss") GM_TargetCount;
STATIC int SECTION(".sbss") GM_StaleTargetCount;

static inline int Conflict(int center1, int size1, int center2, int size2)
{
    size1 += size2;
    return center1 - size1 <= center2 && center2 - size1 <= center1;
}

static inline int MapConflict(int map1, int map2)
{
    return (GM_PlayerMap & map1) && (GM_PlayerMap & map2);
}

// Checks if two targets intersect.
// For an intersection, the two targets must be:
// 1. On opposing sides (PLAYER_SIDE & ENEMY_SIDE)
// 2. Contained within one's bounds
// 3. On the same map(s)
static int TargetConflict(TARGET *a, TARGET *b)
{
    return (((a->side & b->side) == 0) &&
            Conflict(a->center.vx, a->size.vx, b->center.vx, b->size.vx) &&
            Conflict(a->center.vz, a->size.vz, b->center.vz, b->size.vz) &&
            Conflict(a->center.vy, a->size.vy, b->center.vy, b->size.vy) &&
            MapConflict(a->map, b->map));
}

// Checks if a target with no side intersects with a given target.
// Similar to TargetConflict, but `a` must be on NO_SIDE.
static int TargetConflictMap(TARGET *a, TARGET *b)
{
    return (a->side == NO_SIDE &&
            Conflict(a->center.vx, a->size.vx, b->center.vx, b->size.vx) &&
            Conflict(a->center.vz, a->size.vz, b->center.vz, b->size.vz) &&
            Conflict(a->center.vy, a->size.vy, b->center.vy, b->size.vy) &&
            MapConflict(a->map, b->map));
}

void GM_InitTargetSystem(void)
{
    GM_TargetCount = 0;
    GM_StaleTargetCount = 0;
}

TARGET *GM_AllocTarget(void)
{
    TARGET *target;
    int     i;

    // The game tries to maintain that slots [0, GM_TargetCount)
    // in GM_TargetDatas are all used up. However some "holes" could appear.

    // Are there no "holes" to plug in the GM_TargetDatas array?
    if (GM_StaleTargetCount == 0)
    {
        // There are no "holes" in the GM_TargetDatas array
        // so let's just take the next slot and increment GM_TargetCount

        if (GM_TargetCount >= TARGET_MAX)
        {
            // Out of memory...
            return NULL;
        }

        target = &GM_TargetDatas[GM_TargetCount];
        target->class = TARGET_AVAIL;
        GM_TargetCount++;
        return target;
    }

    // There are "holes" in the GM_TargetDatas array, let's
    // try to find one and use it up.

    target = GM_TargetDatas;
    if (GM_TargetCount > 0)
    {
        for (i = GM_TargetCount; i > 0; i--, target++)
        {
            if (target->class == TARGET_STALE)
            {
                // Found unused slot, let's use it.
                target->class = TARGET_AVAIL;
                GM_StaleTargetCount--;
                return target;
            }
        }
    }

    // This should be unreachable, we should have found a slot above.
    GM_StaleTargetCount = 0;
    return NULL;
}

void GM_FreeTarget(TARGET *target)
{
    // The game tries to maintain that slots [0, GM_TargetCount)
    // in GM_TargetDatas are all used up. However some "holes" could appear
    // due to freeing a TARGET here:

    if (target)
    {
        if (target == &GM_TargetDatas[GM_TargetCount - 1])
        {
            // Freeing the last used TARGET doesn't result
            // in a "hole", just adjust the lastSlotUsed.
            GM_TargetCount--;
        }
        else
        {
            // Freeing this TARGET resulted in a "hole" in the array:
            GM_StaleTargetCount++;
        }
        target->class = TARGET_STALE; // mark as a free slot
    }
}

void GM_MoveTarget(TARGET *target, SVECTOR *center)
{
    target->center = *center;
    target->map = GM_CurrentMap;
}

TARGET *GM_CaptureTarget(TARGET *target)
{
    TARGET *iter;
    int     i;

    iter = GM_TargetDatas;
    for (i = GM_TargetCount; i > 0; iter++, i--)
    {
        // Skip if we are checking the current target
        if (target == iter)
        {
            continue;
        }

        // Skip if wrong class
        if (!(iter->class & TARGET_CAPTURE))
        {
            continue;
        }

        // Return if this is the first intersection for the class
        if (TargetConflict(iter, target) && !(iter->damaged & TARGET_CAPTURE))
        {
            iter->damaged |= TARGET_CAPTURE;
            iter->a_mode = target->a_mode;
            iter->field_18 = target->field_18;
            iter->field_1C = target->field_1C;
            iter->faint -= target->faint;
            iter->captured = 1;

            target->damaged |= TARGET_CAPTURE;

            return iter;
        }
    }

    return NULL;
}

TARGET *GM_C4Target(TARGET *target)
{
    TARGET *iter;
    int     i;

    iter = GM_TargetDatas;
    for (i = GM_TargetCount; i > 0; iter++, i--)
    {
        // Skip if we are checking the current target
        if (target == iter)
        {
            continue;
        }

        // Skip if wrong class
        if (!(iter->class & TARGET_C4))
        {
            continue;
        }

        // Return if this is the first intersection for the class
        if (TargetConflict(iter, target) && !(iter->damaged & TARGET_C4))
        {
            iter->damaged |= TARGET_C4;
            target->damaged |= TARGET_C4;
            return iter;
        }
    }

    return NULL;
}

int GM_TouchTarget(TARGET *target)
{
    TARGET *iter;
    int     i;
    int     hp, oldhp;

    if (!(target->class & TARGET_TOUCH))
    {
        return 0;
    }

    if (target->damaged & TARGET_TOUCH)
    {
        return 1;
    }

    iter = GM_TargetDatas;
    i = GM_TargetCount;

    hp = target->vital;

    iter = GM_TargetDatas;
    for (i = GM_TargetCount; i > 0; iter++, i--)
    {
        // Skip if we are checking the current target
        if (target == iter)
        {
            continue;
        }

        // Skip if wrong class
        if (!(iter->class & TARGET_TOUCH))
        {
            continue;
        }

        // Touch if there is an intersection for the class
        if (TargetConflict(iter, target))
        {
            oldhp = iter->vital;
            iter->vital -= hp;
            iter->damage += oldhp - iter->vital;

            iter->damaged |= TARGET_TOUCH;
            target->damaged |= TARGET_TOUCH;
        }
    }

    // Return whether any target was touched
    return (target->damaged & TARGET_TOUCH) >> 7;
}

static inline int UpdatePowerParam( int type, int a, int b )
{
    switch ( type & 0x3 )
    {
    case POWER_ONCE:
        return 0;
    case POWER_DECREASE:
        return a - b;
    case POWER_THRESHOLD:
        return ( a > b ) ? a : 0;
    case POWER_CONST:
    default:
        return a;
    }
}

#define SCALE_VXZ(in, scale, out)           \
do                                          \
{                                           \
    int angle;                              \
    angle = GV_VecDir2(in);        \
    GV_DirVec2(angle, scale, out); \
} while (0)

int GM_PowerTarget(TARGET *target)
{
    SVECTOR dist;
    SVECTOR scaled;
    int     hp, hp2;
    int     p_mode;
    TARGET *iter;
    int     i;
    int     hp_diff;

    hp = target->vital;
    p_mode = target->p_mode;

    iter = GM_TargetDatas;
    for (i = GM_TargetCount; i > 0; iter++, i--)
    {
        if (target == iter)
        {
            continue;
        }

        if (!(iter->class & TARGET_POWER))
        {
            continue;
        }

        if (!TargetConflict(iter, target))
        {
            continue;
        }

        iter->damaged |= TARGET_POWER;

        hp2 = iter->vital;
        iter->vital = UpdatePowerParam(iter->p_mode, hp2, hp);
        hp = UpdatePowerParam(p_mode, hp, hp2);

        iter->damage += hp2 - iter->vital;
        iter->faint -= target->faint;
        iter->a_mode = target->a_mode;
        iter->weapon = target->weapon;

        if (p_mode & POWER_EXPLODE)
        {
            GV_SubVec3(&iter->center, &target->center, &dist);
            SCALE_VXZ(&dist, target->force.vx, &scaled);
            GV_AddVec3(&iter->force, &scaled, &iter->force);
        }
        else
        {
            GV_AddVec3(&iter->force, &target->force, &iter->force);
        }

        if (hp < 0)
        {
            break;
        }
    }

    hp_diff = target->vital - hp;
    target->vital = hp;

    if (hp_diff > 0)
    {
        target->damaged |= TARGET_POWER;
    }

    return hp_diff;
}

static inline int Push(int center1, int size1, int center2, int size2)
{
    size1 += size2;
    size2 = center2 - center1;
    if (size2 >= 0)
    {
        size1 -= size2;
        if (size1 < 0) size1 = 0;
        return size1;
    }
    else
    {
        size2 += size1;
        if (size2 < 0) size2 = 0;
        return -size2;
    }
}

static inline int PushTarget(TARGET *off, TARGET *def)
{
    int x, z, x2, z2;
    int dir;

    x = Push(def->center.vx, def->size.vx, off->center.vx, off->size.vx);
    if (x == 0) return 0;

    z = Push(def->center.vz, def->size.vz, off->center.vz, off->size.vz);
    if (z == 0) return 0;

    if (def->flag & 2) return 1;

    x2 = abs(x);
    z2 = abs(z);

    if (x2 <= z2)
    {
        x /= 2;
        off->offset.vx += x;
        def->offset.vx -= x;
        dir = (x > 0) ? 2 : 4;
    }
    else
    {
        z /= 2;
        off->offset.vz += z;
        def->offset.vz -= z;
        dir = (z > 0) ? 1 : 3;
    }

    if (def->flag & 1) off->offset.pad = dir;
    return 1;
}

int GM_PushTarget(TARGET *target)
{
    TARGET *iter;
    int     count;

    if (!(target->class & TARGET_PUSH))
    {
        return 0;
    }

    target->offset = DG_ZeroVector;
    target->offset.pad = 0;

    iter = GM_TargetDatas;

    for (count = GM_TargetCount; count > 0; iter++, count--)
    {
        iter->push_side = NO_SIDE;

        if ((target == iter) || !(iter->class & TARGET_PUSH) || !TargetConflictMap(iter, target))
        {
            continue;
        }

        if (PushTarget(target, iter))
        {
            iter->damaged |= TARGET_PUSH;
            target->damaged |= TARGET_PUSH;
            iter->push_side = target->side;
        }
    }

    return (short)(target->damaged & TARGET_PUSH) > 0;
}

void GM_SetTarget(TARGET *target, int class, int side, SVECTOR *size)
{
    short cur_map = GM_CurrentMap;
    target->class = class;
    target->side = side;
    target->damaged = 0;
    target->map = cur_map;
    target->size = *size;
    target->flag = 0;
}

void GM_SetCaptureTarget(TARGET *target, int a_mode, int faint, int *a4, SVECTOR *a5)
{
    target->field_18 = a4;
    target->a_mode = a_mode;
    target->faint = faint;
    target->field_1C = a5;
}

void GM_SetPowerTarget(TARGET *target, int p_mode, int a_mode, int vital, int faint, SVECTOR *force)
{
    target->p_mode = p_mode;
    target->a_mode = a_mode;
    target->vital = vital;
    target->damage = 0;
    target->faint = faint;
    target->force = *force;
    target->weapon = WP_None;
}

void GM_TargetBody(TARGET *target, MATRIX *body)
{
    target->body = body;
}

static void SetFromToTarget(SVECTOR *from, SVECTOR *to, TARGET *targ)
{
    int f, t, s;

    f = from->vx; t = to->vx; s = (f - t) / 2;
    targ->center.vx = (f + t) / 2;
    targ->size.vx = abs(s);
    f = from->vy; t = to->vy; s = (f - t) / 2;
    targ->center.vy = (f + t) / 2;
    targ->size.vy = abs(s);
    f = from->vz; t = to->vz; s = (f - t) / 2;
    targ->center.vz = (f + t) / 2;
    targ->size.vz = abs(s);
}

static int OnlineTarget(SVECTOR *from, SVECTOR *to, TARGET *def, SVECTOR *hit)
{
    int cx, cy, cz, sx, sy, sz, df, f0;
    int c1, c2;

    f0 = from->vx;
    if ((df = to->vx - f0) == 0) goto cutx_failed;
    cx = def->center.vx; sx = def->size.vx;    
    if (cx < f0)                                                                
    {                                                                                                          
        cx += sx;                                                                 
        if (cx > f0) cx = f0;                                                                                                                                                                         
    }                                                                                                          
    else                                                                                                       
    {                                                                                                          
        cx -= sx;                                                                 
        if (cx < f0) cx = f0;                                                                                                                                                              
    }
    c1 = from->vy + (to->vy - from->vy) * (cx - f0) / df;
    if (c1 < def->center.vy - def->size.vy ||
        c1 > def->center.vy + def->size.vy) goto cutx_failed;
    c2 = from->vz + (to->vz - from->vz) * (cx - f0) / df;
    if (c2 < def->center.vz - def->size.vz ||
        c2 > def->center.vz + def->size.vz) goto cutx_failed;
    hit->vx = cx;
    hit->vy = c1;
    hit->vz = c2;
    return 1;
cutx_failed:
    f0 = from->vy;
    if ((df = to->vy - f0) == 0) goto cuty_failed;
    cy = def->center.vy; sy = def->size.vy;    
    if (cy < f0)                                                                
    {                                                                                                          
        cy += sy;                                                                 
        if (cy > f0) cy = f0;                                                                                                                                                                         
    }                                                                                                          
    else                                                                                                       
    {                                                                                                          
        cy -= sy;                                                                 
        if (cy < f0) cy = f0;                                                                                                                                                              
    }
    c1 = from->vz + (to->vz - from->vz) * (cy - f0) / df;
    if (c1 < def->center.vz - def->size.vz ||
        c1 > def->center.vz + def->size.vz) goto cuty_failed;
    c2 = from->vx + (to->vx - from->vx) * (cy - f0) / df;
    if (c2 < def->center.vx - def->size.vx ||
        c2 > def->center.vx + def->size.vx) goto cuty_failed;
    hit->vy = cy;
    hit->vz = c1;
    hit->vx = c2;
    return 1;
cuty_failed:
    f0 = from->vz;
    if ((df = to->vz - f0) == 0) goto cutz_failed;
    cz = def->center.vz; sz = def->size.vz;
    if (cz < f0)                                                                
    {                                                                                                          
        cz += sz;                                                                 
        if (cz > f0) cz = f0;                                                                                                                                                                         
    }                                                                                                          
    else                                                                                                       
    {                                                                                                          
        cz -= sz;                                                                 
        if (cz < f0) cz = f0;                                                                                                                                                              
    }
    c1 = from->vx + (to->vx - from->vx) * (cz - f0) / df;
    if (c1 < def->center.vx - def->size.vx ||
        c1 > def->center.vx + def->size.vx) goto cutz_failed;
    c2 = from->vy + (to->vy - from->vy) * (cz - f0) / df;
    if (c2 < def->center.vy - def->size.vy ||
        c2 > def->center.vy + def->size.vy) goto cutz_failed;
    hit->vz = cz;
    hit->vx = c1;
    hit->vy = c2;
    return 1;
cutz_failed:
    return 0;
}

int GM_OnlineTargetCheck(SVECTOR *from, SVECTOR *to, int map, SVECTOR *hit, int side)
{
    TARGET tmp;
    TARGET *iter;
    int found, i;

    tmp.map = map;
    tmp.side = NO_SIDE;

    SetFromToTarget(from, to, &tmp);

    iter = GM_TargetDatas;
    found = 0;
    for (i = GM_TargetCount; i > 0; i--)
    {
        if (iter->side != side && (iter->class & TARGET_SEEK))
        {
            if (TargetConflict(iter, &tmp) && OnlineTarget(from, to, iter, hit))
            {
                SetFromToTarget(from, hit, &tmp);
                found = 1;
            }
        }

        iter++;
    }

    return found;
}

int GM_OnlineTargetCheckAny(SVECTOR *from, SVECTOR *to, int map, SVECTOR *hit)
{
    TARGET tmp;
    TARGET *iter;
    int i;

    tmp.map = map;
    tmp.side = NO_SIDE;

    SetFromToTarget(from, to, &tmp);

    iter = GM_TargetDatas;
    for (i = GM_TargetCount; i > 0; i--)
    {
        if ((iter->flag & 0x1) && (iter->class & TARGET_SEEK))
        {
            if (TargetConflict(iter, &tmp) && OnlineTarget(from, to, iter, hit))
            {
                return 1;
            }
        }

        iter++;
    }

    return 0;
}

void GM_GetTargets(int *count, TARGET **targets)
{
    *count = GM_TargetCount;
    *targets = GM_TargetDatas;
}
