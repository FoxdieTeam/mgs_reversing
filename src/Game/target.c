#include "target.h"

#include "common.h"
#include "Game/game.h"

// Instead of dynamically allocating TARGETs,
// the game uses the big TARGET array gTargets_800B64E0.
//
// This also makes it easier to iterate over all TARGETs in use.
//
// Therefore each entry in this array will be either:
// - already used up (returned by GM_AllocTarget and not yet freed)
// - not used (target->class == 0)
//
// When allocating new TARGETs, the game will try to find a "free" slot in this array.
// It tries to do it efficiently (without having to scan the whole array too often).
// The game tries to ensure that slots [0, gTargets_lastSlotUsed_800ABA68)
// are all actively used, while the latter part of the array is free.
// However, deallocating TARGETs can result in "holes" in that contiguous prefix.
//
// Two indicies are maintained:
// - gTargets_lastSlotUsed_800ABA68:
//      slots [0, gTargets_lastSlotUsed_800ABA68) are potentially used
//      slots [gTargets_lastSlotUsed_800ABA68, TARGET_ARRAY_LENGTH) are definitely not used
// - gTargets_orphanedSlots_800ABA6C:
//      how many slots [0, gTargets_lastSlotUsed_800ABA68) are not used
//
// In most cases the game will just take gTargets_lastSlotUsed_800ABA68+1
// as a next used slot. If a TARGET is freed in the middle of the array
// (gets orphaned: gTargets_orphanedSlots_800ABA6C) the code will try
// to "plug" the hole when allocating the next target.
//
// Example:
//   - [Target1, Target2, Target3, FREE, FREE, FREE, FREE...]
//     gTargets_lastSlotUsed_800ABA68 = 3, gTargets_orphanedSlots_800ABA6C = 0
//
//   - GM_AllocTarget()
//
//   - [Target1, Target2, Target3, Target4, FREE, FREE, FREE...]
//     gTargets_lastSlotUsed_800ABA68 = 4, gTargets_orphanedSlots_800ABA6C = 0
//
//   - GM_FreeTarget(Target3)
//
//   - [Target1, Target2, FREE, Target4, FREE, FREE, FREE...]
//     gTargets_lastSlotUsed_800ABA68 = 4, gTargets_orphanedSlots_800ABA6C = 1
//
//   - GM_AllocTarget()
//
//   - [Target1, Target2, Target5, Target4, FREE, FREE, FREE...]
//     gTargets_lastSlotUsed_800ABA68 = 4, gTargets_orphanedSlots_800ABA6C = 0
//
//   - GM_FreeTarget(Target4)
//
//   - [Target1, Target2, Target5, FREE, FREE, FREE, FREE...]
//     gTargets_lastSlotUsed_800ABA68 = 3, gTargets_orphanedSlots_800ABA6C = 0
//
extern TARGET gTargets_800B64E0[TARGET_ARRAY_LENGTH];

int SECTION(".sbss") gTargets_lastSlotUsed_800ABA68;
int SECTION(".sbss") gTargets_orphanedSlots_800ABA6C;

extern int     GM_PlayerMap_800ABA0C;

static inline int BoundContains(int asize, int bsize, int apos, int bpos)
{
    int size;

    size = asize + bsize;
    return ( bpos >= ( apos - size ) ) && ( apos >= ( bpos - size ) );
}

static inline int MapContains(int a, int b)
{
    return (GM_PlayerMap_800ABA0C & a) && (GM_PlayerMap_800ABA0C & b);
}

// Checks if two targets intersect.
// For an intersection, the two targets must be:
// 1. On opposing sides (PLAYER_SIDE & ENEMY_SIDE)
// 2. Contained within one's bounds
// 3. On the same map(s)
int GM_TargetIntersects(TARGET *a, TARGET *b)
{
    return (((a->side & b->side) == 0) &&
            BoundContains(a->size.vx, b->size.vx, a->center.vx, b->center.vx) &&
            BoundContains(a->size.vz, b->size.vz, a->center.vz, b->center.vz) &&
            BoundContains(a->size.vy, b->size.vy, a->center.vy, b->center.vy) &&
            MapContains(a->map, b->map));
}

// Checks if a target with no side intersects with a given target.
// Similar to GM_TargetIntersects, but `a` must be on NO_SIDE.
int GM_TargetIntersectsNoSide(TARGET *a, TARGET *b)
{
    return (a->side == NO_SIDE &&
            BoundContains(a->size.vx, b->size.vx, a->center.vx, b->center.vx) &&
            BoundContains(a->size.vz, b->size.vz, a->center.vz, b->center.vz) &&
            BoundContains(a->size.vy, b->size.vy, a->center.vy, b->center.vy) &&
            MapContains(a->map, b->map));
}

void GM_ResetTargets(void)
{
    gTargets_lastSlotUsed_800ABA68 = 0;
    gTargets_orphanedSlots_800ABA6C = 0;
}

TARGET *GM_AllocTarget(void)
{
    TARGET *target;
    int     i;

    // The game tries to maintain that slots [0, gTargets_lastSlotUsed_800ABA68)
    // in gTargets_800B64E0 are all used up. However some "holes" could appear.

    // Are there no "holes" to plug in the gTargets_800B64E0 array?
    if (gTargets_orphanedSlots_800ABA6C == 0)
    {
        // There are no "holes" in the gTargets_800B64E0 array
        // so let's just take the next slot and increment gTargets_lastSlotUsed_800ABA68

        if (gTargets_lastSlotUsed_800ABA68 >= TARGET_ARRAY_LENGTH)
        {
            // Out of memory...
            return NULL;
        }

        target = &gTargets_800B64E0[gTargets_lastSlotUsed_800ABA68];
        target->class = TARGET_AVAIL;
        gTargets_lastSlotUsed_800ABA68++;
        return target;
    }

    // There are "holes" in the gTargets_800B64E0 array, let's
    // try to find one and use it up.

    target = gTargets_800B64E0;
    if (gTargets_lastSlotUsed_800ABA68 > 0)
    {
        for (i = gTargets_lastSlotUsed_800ABA68; i > 0; i--, target++)
        {
            if (target->class == TARGET_STALE)
            {
                // Found unused slot, let's use it.
                target->class = TARGET_AVAIL;
                gTargets_orphanedSlots_800ABA6C--;
                return target;
            }
        }
    }

    // This should be unreachable, we should have found a slot above.
    gTargets_orphanedSlots_800ABA6C = 0;
    return NULL;
}

void GM_FreeTarget(TARGET *target)
{
    // The game tries to maintain that slots [0, gTargets_lastSlotUsed_800ABA68)
    // in gTargets_800B64E0 are all used up. However some "holes" could appear
    // due to freeing a TARGET here:

    if (target)
    {
        if (target == &gTargets_800B64E0[gTargets_lastSlotUsed_800ABA68 - 1])
        {
            // Freeing the last used TARGET doesn't result
            // in a "hole", just adjust the lastSlotUsed.
            gTargets_lastSlotUsed_800ABA68--;
        }
        else
        {
            // Freeing this TARGET resulted in a "hole" in the array:
            gTargets_orphanedSlots_800ABA6C++;
        }
        target->class = TARGET_STALE; // mark as a free slot
    }
}

void GM_MoveTarget(TARGET *target, SVECTOR *center)
{
    target->center = *center;
    target->map = GM_CurrentMap_800AB9B0;
}

TARGET *GM_CaptureTarget(TARGET *target)
{
    TARGET *iter;
    int     i;

    iter = gTargets_800B64E0;
    for (i = gTargets_lastSlotUsed_800ABA68; i > 0; iter++, i--)
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
        if (GM_TargetIntersects(iter, target) && !(iter->damaged & TARGET_CAPTURE))
        {
            iter->damaged |= TARGET_CAPTURE;
            iter->a_mode = target->a_mode;
            iter->field_18 = target->field_18;
            iter->field_1C = target->field_1C;
            iter->field_2A -= target->field_2A;
            iter->field_42 = 1;

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

    iter = gTargets_800B64E0;
    for (i = gTargets_lastSlotUsed_800ABA68; i > 0; iter++, i--)
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
        if (GM_TargetIntersects(iter, target) && !(iter->damaged & TARGET_C4))
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

    iter = gTargets_800B64E0;
    i = gTargets_lastSlotUsed_800ABA68;

    hp = target->field_26_hp;

    iter = gTargets_800B64E0;
    for (i = gTargets_lastSlotUsed_800ABA68; i > 0; iter++, i--)
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
        if (GM_TargetIntersects(iter, target))
        {
            oldhp = iter->field_26_hp;
            iter->field_26_hp -= hp;
            iter->field_28 += oldhp - iter->field_26_hp;

            iter->damaged |= TARGET_TOUCH;
            target->damaged |= TARGET_TOUCH;
        }
    }

    // Return whether any target was touched
    return (target->damaged & TARGET_TOUCH) >> 7;
}

static inline int sub_helper_8002D7DC(int which, int a, int b)
{
    switch (which & 0x3)
    {
    case 0:
        return 0;

    case 1:
        return a - b;

    case 2:
        return (a > b) ? a : 0;

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
    int     f24;
    TARGET *iter;
    int     i;
    int     hp_diff;

    hp = target->field_26_hp;
    f24 = target->field_24;

    iter = gTargets_800B64E0;
    for (i = gTargets_lastSlotUsed_800ABA68; i > 0; iter++, i--)
    {
        if (target == iter)
        {
            continue;
        }

        if (!(iter->class & TARGET_POWER))
        {
            continue;
        }

        if (!GM_TargetIntersects(iter, target))
        {
            continue;
        }

        iter->damaged |= TARGET_POWER;

        hp2 = iter->field_26_hp;
        iter->field_26_hp = sub_helper_8002D7DC(iter->field_24, hp2, hp);
        hp = sub_helper_8002D7DC(f24, hp, hp2);

        iter->field_28 += hp2 - iter->field_26_hp;
        iter->field_2A -= target->field_2A;
        iter->a_mode = target->a_mode;
        iter->field_44 = target->field_44;

        if (f24 & 0x4)
        {
            GV_SubVec3(&iter->center, &target->center, &dist);
            SCALE_VXZ(&dist, target->field_2C_vec.vx, &scaled);
            GV_AddVec3(&iter->field_2C_vec, &scaled, &iter->field_2C_vec);
        }
        else
        {
            GV_AddVec3(&iter->field_2C_vec, &target->field_2C_vec, &iter->field_2C_vec);
        }

        if (hp < 0)
        {
            break;
        }
    }

    hp_diff = target->field_26_hp - hp;
    target->field_26_hp = hp;

    if (hp_diff > 0)
    {
        target->damaged |= TARGET_POWER;
    }

    return hp_diff;
}

static inline int sub_helper2_8002DA14( TARGET *target, TARGET *target2, int use_z )
{
    int a, b;
    int v0, v1;

    b = use_z ? target2->size.vz : target2->size.vx;
    a = use_z ? target->size.vz : target->size.vx;

    v1 = use_z ? target2->center.vz : target2->center.vx;
    v0 = use_z ? target->center.vz : target->center.vx;

    b = b + a;
    a = v0 - v1;


    if (a >= 0)
    {
        b -= a;
        if (b < 0)
        {
            b = 0;
        }
        return b;
    }
    else
    {
        a += b;
        if (a < 0)
        {
            a = 0;
        }
        return -a;
    }
}

static inline int sub_helper_8002DA14(TARGET *target, TARGET *iter)
{
    int val, val2;
    int which;

    val = sub_helper2_8002DA14(target, iter, 0);
    if (val == 0)
    {
        return 0;
    }

    val2 = sub_helper2_8002DA14(target, iter, 1);
    if (val2 == 0)
    {
        return 0;
    }

    if (!(iter->field_3C & 2))
    {
        // this is NOT an inline, /= 2 does not work otherwise
        if (abs(val) <= abs(val2))
        {
            val /= 2;
            target->field_34_vec.vx += val;
            iter->field_34_vec.vx -= val;

            if (val > 0)
            {
                which = 2;
            }
            else
            {
                which = 4;
            }
        }
        else
        {
            val2 /= 2;
            target->field_34_vec.vz += val2;
            iter->field_34_vec.vz -= val2;

            if (val2 > 0)
            {
                which = 1;
            }
            else
            {
                which = 3;
            }
        }

        if (iter->field_3C & 1)
        {
            target->field_34_vec.pad = which;
        }
    }

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

    target->field_34_vec = DG_ZeroVector;
    target->field_34_vec.pad = 0;

    iter = gTargets_800B64E0;

    for (count = gTargets_lastSlotUsed_800ABA68; count > 0; iter++, count--)
    {
        iter->field_40 = 0;

        if ((target == iter) || !(iter->class & TARGET_PUSH) || !GM_TargetIntersectsNoSide(iter, target))
        {
            continue;
        }

        if (sub_helper_8002DA14(target, iter))
        {
            iter->damaged |= TARGET_PUSH;
            target->damaged |= TARGET_PUSH;
            iter->field_40 = target->side;
        }
    }

    return (short)(target->damaged & TARGET_PUSH) > 0;
}

void GM_SetTarget(TARGET *target, int class, int side, SVECTOR *size)
{
    short cur_map = GM_CurrentMap_800AB9B0;
    target->class = class;
    target->side = side;
    target->damaged = 0;
    target->map = cur_map;
    target->size = *size;
    target->field_3C = 0;
}

void GM_Target_8002DCB4(TARGET *target, int a2, int a3, int *a4, SVECTOR *a5)
{
    target->field_18 = a4;
    target->a_mode = a2;
    target->field_2A = a3;
    target->field_1C = a5;
}

void GM_Target_8002DCCC(TARGET *target, int a2, int a3, int hp, int a5, SVECTOR *a6)
{
    target->field_24 = a2;
    target->a_mode = a3;
    target->field_26_hp = hp;
    target->field_28 = 0;
    target->field_2A = a5;
    target->field_2C_vec = *a6;
    target->field_44 = -1;
}

void sub_8002DD14(TARGET *target, MATRIX *pMatrix)
{
    target->field_20 = pMatrix;
}

void sub_8002DD1C(SVECTOR *svec1, SVECTOR *svec2, TARGET *target)
{
    int coord1, coord2;
    int diff;

    coord1 = svec1->vx;
    coord2 = svec2->vx;
    diff = (coord1 - coord2) / 2;
    target->center.vx = (coord1 + coord2) / 2;
    target->size.vx = abs(diff);

    coord1 = svec1->vy;
    coord2 = svec2->vy;
    diff = (coord1 - coord2) / 2;
    target->center.vy = (coord1 + coord2) / 2;
    target->size.vy = abs(diff);

    coord1 = svec1->vz;
    coord2 = svec2->vz;
    diff = (coord1 - coord2) / 2;
    target->center.vz = (coord1 + coord2) / 2;
    target->size.vz = abs(diff);
}

#define sub_8002DDE0_helper(AXIS1, AXIS2, AXIS3)                                                                       \
    {                                                                                                                  \
        int vec1_axis1, vec1_axis2, vec1_axis3;                                                                        \
        int outvec_axis1, outvec_axis3;                                                                                \
        int outvec_addend_axis2;                                                                                       \
        int multiplier;                                                                                                \
        int target_field_10_axis1;                                                                                     \
        vec1_axis1 = vec1->AXIS1;                                                                                      \
        divisor = vec2->AXIS1 - vec1_axis1;                                                                            \
        if (divisor != 0)                                                                                              \
        {                                                                                                              \
            outvec_axis1 = target->center.AXIS1;                                                                  \
            target_field_10_axis1 = target->size.AXIS1;                                                       \
            if (target->center.AXIS1 < vec1_axis1)                                                                \
            {                                                                                                          \
                outvec_axis1 += target_field_10_axis1;                                                                 \
                if (vec1_axis1 < outvec_axis1)                                                                         \
                {                                                                                                      \
                    outvec_axis1 = vec1_axis1;                                                                         \
                }                                                                                                      \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                outvec_axis1 -= target_field_10_axis1;                                                                 \
                if (outvec_axis1 < vec1_axis1)                                                                         \
                {                                                                                                      \
                    outvec_axis1 = vec1_axis1;                                                                         \
                }                                                                                                      \
            }                                                                                                          \
            multiplier = outvec_axis1 - vec1_axis1;                                                                    \
            vec1_axis2 = vec1->AXIS2;                                                                                  \
            outvec_addend_axis2 = (vec2->AXIS2 - vec1_axis2) * multiplier / divisor;                                   \
            if (vec1_axis2 + outvec_addend_axis2 >= target->center.AXIS2 - target->size.AXIS2 &&         \
                target->center.AXIS2 + target->size.AXIS2 >= vec1_axis2 + outvec_addend_axis2)           \
            {                                                                                                          \
                vec1_axis3 = vec1->AXIS3;                                                                              \
                outvec_axis3 = vec1_axis3;                                                                             \
                outvec_axis3 += (vec2->AXIS3 - outvec_axis3) * multiplier / divisor;                                   \
                if (outvec_axis3 >= target->center.AXIS3 - target->size.AXIS3 &&                         \
                    target->center.AXIS3 + target->size.AXIS3 >= outvec_axis3)                           \
                {                                                                                                      \
                    do                                                                                                 \
                    {                                                                                                  \
                        outvec->AXIS1 = outvec_axis1;                                                                  \
                        outvec->AXIS2 = vec1_axis2 + outvec_addend_axis2;                                              \
                        outvec->AXIS3 = outvec_axis3;                                                                  \
                    } while (0);                                                                                       \
                    return 1;                                                                                          \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
    }

int sub_8002DDE0(SVECTOR *vec1, SVECTOR *vec2, TARGET *target, SVECTOR *outvec)
{
    int divisor;
    sub_8002DDE0_helper(vx, vy, vz);
    sub_8002DDE0_helper(vy, vz, vx);
    sub_8002DDE0_helper(vz, vx, vy);
    return 0;
}

int GM_Target_8002E1B8(SVECTOR *pVec, SVECTOR *pVec1, int map_bit, SVECTOR *pVec2, int side)
{
    TARGET *iter;
    int     i;
    int     bResult;
    TARGET  target;

    target.map = map_bit;
    target.side = NO_SIDE;
    sub_8002DD1C(pVec, pVec1, &target);

    iter = gTargets_800B64E0;
    i = gTargets_lastSlotUsed_800ABA68;
    for (bResult = 0; i > 0; ++iter)
    {
        if (iter->side != side && (iter->class & TARGET_SEEK) != 0)
        {
            if (GM_TargetIntersects(iter, &target))
            {
                if (sub_8002DDE0(pVec, pVec1, iter, pVec2))
                {
                    sub_8002DD1C(pVec, pVec2, &target);
                    bResult = 1;
                }
            }
        }
        --i;
    }
    return bResult;
}

int sub_8002E2A8(SVECTOR *arg0, SVECTOR *arg1, int map, SVECTOR *arg3)
{
    TARGET  target;
    TARGET *iter;
    int     count;

    target.map = map;
    target.side = NO_SIDE;

    sub_8002DD1C(arg0, arg1, &target);

    iter = gTargets_800B64E0;
    count = gTargets_lastSlotUsed_800ABA68;

    while (count > 0)
    {
        if (((iter->field_3C & 0x1) != 0) &&
            ((iter->class & TARGET_SEEK) != 0) &&
            GM_TargetIntersects(iter, &target) &&
            sub_8002DDE0(arg0, arg1, iter, arg3))
        {
            return 1;
        }

        iter++;
        count--;
    }

    return 0;
}

void GM_Target_8002E374(int *ppDownCount, TARGET **targets)
{
    *ppDownCount = gTargets_lastSlotUsed_800ABA68;
    *targets = gTargets_800B64E0;
}
