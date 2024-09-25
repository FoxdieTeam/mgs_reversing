#include "psyq.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "inline_n.h"

/*possible funcs
 HZD_GetLevelHazard
 HZD_GetLevelHeight
 HZD_LevelHazardCheckOne
 HZD_GetLevelAtr
*/

/**
 * Used in collision detection, called every frame for Snake and each enemy on the map.
 *
 * In Snake's case, the first argument is snake->control->field_0_vec.
 * Whether for Snake or not, the second argument is always the scratchpad
 * address 0x1f80000c.
 *
 * Disabling this function badly messes up collision detection for both Snake
 * and his enemies, ie Snake will constantly fall into and come back out from
 * the floor as he runs around.
 */
STATIC void HZD_CopyVector2(SVECTOR *src, SVECTOR *dst)
{
    dst->vx = src->vx;
    dst->vz = src->vy;
    dst->vy = src->vz;
}

//probably uses inlines
int HZD_80029384(HZD_FLR *floor)
{
    int a2, a3, t0, v1;

    a2 = *( int * )0x1F80000C;
    t0 = floor->p1.long_access[0];
    v1 = floor->p2.long_access[0];

    gte_ldsxy3( t0, v1, a2 );
    gte_nclip();
    a3 = floor->p3.long_access[0];
    gte_stopz( 0x1F800008 );

    if ( *( int * )0x1F800008 >= 0 )
    {

        gte_ldsxy3( v1, a3, a2 );
        gte_nclip();
        floor = ( HZD_FLR * )floor->p4.long_access[0];
        gte_stopz( 0x1F800008 );

        if ( *( int * )0x1F800008 < 0 ) return 0;

        gte_ldsxy3( a3, floor, a2 );
        gte_nclip();
        gte_stopz( 0x1F800008 );

        if ( *( int * )0x1F800008 < 0 ) return 0;

        gte_ldsxy3( floor, t0, a2 );
        gte_nclip();
        gte_stopz( 0x1F800008 );

        return *( int * )0x1F800008 >= 0;
    }
    else
    {
        gte_ldsxy3( v1, a3, a2 );
        gte_nclip();
        floor = ( HZD_FLR * )floor->p4.long_access[0];
        gte_stopz( 0x1F800008 );

        if (*( int * )0x1F800008 > 0 ) return 0;

        gte_ldsxy3( a3, floor, a2 );
        gte_nclip();
        gte_stopz( 0x1F800008 );

        if (* ( int * )0x1F800008 > 0 ) return 0;

        gte_NormalClip( floor, t0, a2, 0x1F800008 );
        return *( int * )0x1F800008 <= 0;
    }

}

static inline void HZD_80029514_helper(void)
{
    // what were the original parameters for this crap? trying to make
    // the source and destination two arguments swaps the registers
    short *scratch2 = ( short * )SCRPAD_ADDR;

    scratch2[3] = *(short *)0x1f800038;
    scratch2[2] = -*(short *)0x1f80003a;
}

static inline void assign_subtract( int idx, short idx2, short idx3, short *val )
{
    ((short*)SCRPAD_ADDR)[idx] = ((short*)SCRPAD_ADDR)[idx2] - val[idx3];
}

int HZD_80029514(HZD_FLR *floor)
{
    short *test;
    int x, y;

    assign_subtract( 26, 6, 0, ( short * )&floor->p1 );
    assign_subtract( 27, 7, 1, ( short * )&floor->p1 );

    //todo: fix below, probably some inline
    test = ( short * )0x1F800038;
    test[0] = floor->p1.h;
    do {} while(0);
    test[y = 1] = floor->p2.h;

    HZD_80029514_helper();

    gte_ldsxy3(0, *( int * )0x1F800034, *( int* )0x1F800004);
    gte_nclip();
    gte_stopz( 0x1F800008 );

    x = *(int * )0x1F800008;
    return floor->p1.y - x / floor->p3.h;
}

void HZD_80029604(HZD_FLR *floor)
{
    int  y, h;
    int *scratch;

    h = floor->b1.h; // TODO: What's "h"?
    if ((h & 1) || HZD_80029384(floor))
    {
        if (h & 2)
        {
            y = floor->b1.y;
        }
        else
        {
            y = HZD_80029514(floor);
        }
        scratch = (int *)SCRPAD_ADDR;
        if (*(short *)0x1F800010 >= y)
        {
            if (scratch[17] < y)
            {
                scratch[17] = y;
                scratch[15] = (int)floor;
            }
        }
        else if (y < scratch[18])
        {
            scratch[18] = y;
            scratch[16] = (int)floor;
        }
    }
}

static inline int HZD_800296C4_helper(HZD_FLR *floor, SVECTOR *arg1)
{
    if ((floor->b1.z > arg1->vy) || (floor->b2.z < arg1->vy) ||
        (floor->b1.x > arg1->vx) || (floor->b2.x < arg1->vx))
    {
        return 0;
    }

    return 1;
}

int HZD_800296C4(HZD_HDL *hdl, SVECTOR *svec, int flags)
{
    HZD_AREA *pArea;
    int      *pScr;
    HZD_FLR  *floor;
    int       count;
    HZD_FLR **ppFloors;
    int      *pScr2;

    pArea = hdl->area;

    HZD_CopyVector2(svec, (SVECTOR *)getScratchAddr(3));

    pScr = (int *)getScratchAddr(0);
    pScr[16] = 0;
    pScr[15] = 0;
    pScr[17] = 0xFFF0BDC0;
    pScr[18] = 0xF4240;

    if (flags & 1)
    {
        floor = pArea->floors;

        for (count = pArea->n_floors; count > 0; count--, floor++)
        {
            if (HZD_800296C4_helper(floor, (SVECTOR *)getScratchAddr(3)))
            {
                HZD_80029604(floor);
            }
        }
    }

    if (flags & 2)
    {
        ppFloors = hdl->dynamic_floors;

        for (count = hdl->dynamic_floor_index; count > 0; count--, ppFloors++)
        {
            if (HZD_800296C4_helper(*ppFloors, (SVECTOR *)getScratchAddr(3)))
            {
                HZD_80029604(*ppFloors);
            }
        }
    }

    pScr2 = (int *)getScratchAddr(0);
    if (pScr2[16] == 0)
    {
        return pScr2[15] != 0;
    }

    return (pScr2[15] == 0) ? 2 : 3;
}

void HZD_800298C0(void *ptr)
{
    int *spad_addr = (int *)SCRPAD_ADDR;
    ((int *)ptr)[0] = spad_addr[0x0f];
    ((int *)ptr)[1] = spad_addr[0x10];
}

void HZD_800298DC(HZD_VEC *vec)
{
    int *spad_addr = (int *)SCRPAD_ADDR;
    vec->long_access[0] = spad_addr[0x11];
    vec->long_access[1] = spad_addr[0x12];
}

int HZD_SlopeFloorLevel(SVECTOR *arg0, SVECTOR *arg1)
{
    HZD_CopyVector2(arg0, (SVECTOR *)(SCRPAD_ADDR + 0xC));
    return HZD_80029514((HZD_FLR *)arg1);
}

static inline int HZD_8002992C_helper(HZD_FLR *floor, SVECTOR *arg1)
{
    if ((floor->b1.z > arg1->vy) || (floor->b2.z < arg1->vy) ||
        (floor->b1.x > arg1->vx) || (floor->b2.x < arg1->vx))
    {
        return 0;
    }

    return 1;
}

int HZD_8002992C(HZD_FLR *floor, SVECTOR *arg1)
{
    int *pScr;
    int *pScr2;

    HZD_CopyVector2(arg1, (SVECTOR *)getScratchAddr(3));

    pScr = (int *)getScratchAddr(0);
    pScr[16] = 0;
    pScr[15] = 0;
    pScr[17] = 0xFFF0BDC0;
    pScr[18] = 0xF4240;

    if (HZD_8002992C_helper(floor, (SVECTOR *)getScratchAddr(3)))
    {
        HZD_80029604(floor);
    }

    pScr2 = (int *)getScratchAddr(0);

    if (pScr2[16] == 0)
    {
        return pScr2[15] != 0;
    }

    return (pScr2[15] == 0) ? 2 : 3;
}

int HZD_80029A2C(void)
{
    HZD_FLR *floor;
    int      h;

    // Only a single place in code writes a pointer to 0x1F80003C
    // (in HZD_80029604) and it's a HZD_FLR pointer.
    floor = *(HZD_FLR **)0x1F80003C;
    if (!floor)
    {
        return 0;
    }

    h = floor->b1.h;
    return h >> 8;
}
