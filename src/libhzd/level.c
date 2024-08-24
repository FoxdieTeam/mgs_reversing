#include "psyq.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "inline_n.h"

#define SCRPAD_ADDR 0x1F800000

/*possible funcs
 HZD_GetLevelHazard
 HZD_GetLevelHeight
 HZD_LevelHazardCheckOne
 HZD_GetLevelAtr
*/

/**
 * Used in collision detection, called every frame for Snake and each enemy on the map.
 *
 * In Snake's case, the first argument is snake->control->field_0_vec. Whether for Snake or not, the second
 * argument is always the scratchpad address 0x1f800000c.
 *
 * Disabling this function badly messes up collision detection for both Snake and his enemies, ie Snake will constantly
 * fall into and come back out from the floor as he runs around.
 */
void CopyVectorFromScratchpad_80029360(SVECTOR *vec_1, SVECTOR *vec_2)
{
    vec_2->vx = vec_1->vx;
    vec_2->vz = vec_1->vy;
    vec_2->vy = vec_1->vz;
}


//probably uses inlines
int HZD_sub_80029384( HZD_FLR *a0 )
{
    int a2, a3, t0, v1;

    a2 = *( int * )0x1F80000C;
    t0 = a0->p1.long_access[0];
    v1 = a0->p2.long_access[0];

    gte_ldsxy3( t0, v1, a2 );
    gte_nclip();
    a3 = a0->p3.long_access[0];
    gte_stopz( 0x1F800008 );

    if ( *( int * )0x1F800008 >= 0 )
    {

        gte_ldsxy3( v1, a3, a2 );
        gte_nclip();
        a0 = ( HZD_FLR * )a0->p4.long_access[0];
        gte_stopz( 0x1F800008 );

        if ( *( int * )0x1F800008 < 0 ) return 0;

        gte_ldsxy3( a3, a0, a2 );
        gte_nclip();
        gte_stopz( 0x1F800008 );

        if ( *( int * )0x1F800008 < 0 ) return 0;

        gte_ldsxy3( a0, t0, a2 );
        gte_nclip();
        gte_stopz( 0x1F800008 );

        return *( int * )0x1F800008 >= 0;
    }
    else
    {
        gte_ldsxy3( v1, a3, a2 );
        gte_nclip();
        a0 = ( HZD_FLR * )a0->p4.long_access[0];
        gte_stopz( 0x1F800008 );

        if (*( int * )0x1F800008 > 0 ) return 0;

        gte_ldsxy3( a3, a0, a2 );
        gte_nclip();
        gte_stopz( 0x1F800008 );

        if (* ( int * )0x1F800008 > 0 ) return 0;

        gte_NormalClip( a0, t0, a2, 0x1F800008 );
        return *( int * )0x1F800008 <= 0;
    }

}

static inline void helper_80029514()
{
    // what were the original parameters for this crap? trying to make
    // the source and destination two arguments swaps the registers
    short *scratch2 = ( short * )0x1f800000;

    scratch2[3] = *(short *)0x1f800038;
    scratch2[2] = -*(short *)0x1f80003a;
}

static inline void assign_subtract( int idx, short idx2, short idx3, short *val )
{
    ((short*)0x1F800000)[idx] = ((short*)0x1F800000)[idx2] - val[idx3];
}

int HZD_sub_80029514( HZD_FLR *a0 )
{
    short *test;
    int x, y;

    assign_subtract( 26, 6, 0, ( short * )&a0->p1 );
    assign_subtract( 27, 7, 1, ( short * )&a0->p1 );

    //todo: fix below, probably some inline
    test = ( short * )0x1F800038;
    test[0] = a0->p1.h;
    do {} while(0);
    test[y = 1] = a0->p2.h;

    helper_80029514();

    gte_ldsxy3(0, *( int * )0x1F800034, *( int* )0x1F800004);
    gte_nclip();
    gte_stopz( 0x1F800008 );

    x = *(int * )0x1F800008;
    return a0->p1.y - x / a0->p3.h;
}

void sub_80029604(HZD_FLR *pHzdFlr)
{
    int  y, h;
    int *scratch;

    h = pHzdFlr->b1.h; // TODO: What's "h"?
    if ((h & 1) || HZD_sub_80029384(pHzdFlr))
    {
        if (h & 2)
        {
            y = pHzdFlr->b1.y;
        }
        else
        {
            y = HZD_sub_80029514(pHzdFlr);
        }
        scratch = (int *)0x1F800000;
        if (*(short *)0x1F800010 >= y)
        {
            if (scratch[17] < y)
            {
                scratch[17] = y;
                scratch[15] = (int)pHzdFlr;
            }
        }
        else if (y < scratch[18])
        {
            scratch[18] = y;
            scratch[16] = (int)pHzdFlr;
        }
    }
}

static inline int sub_helper_800296C4(HZD_FLR *pAltimetry, SVECTOR *arg1)
{
    if ((pAltimetry->b1.z > arg1->vy) || (pAltimetry->b2.z < arg1->vy) ||
        (pAltimetry->b1.x > arg1->vx) || (pAltimetry->b2.x < arg1->vx))
    {
        return 0;
    }

    return 1;
}

int sub_800296C4(HZD_HDL *pHzdMap, SVECTOR *param_2, int flags)
{
    HZD_AREA *pArea;
    int      *pScr;
    HZD_FLR  *pAltimetry;
    int       count;
    HZD_FLR **ppAltimetry;
    int      *pScr2;

    pArea = pHzdMap->f04_area;

    CopyVectorFromScratchpad_80029360(param_2, (SVECTOR *)getScratchAddr(3));

    pScr = (int *)getScratchAddr(0);
    pScr[16] = 0;
    pScr[15] = 0;
    pScr[17] = 0xFFF0BDC0;
    pScr[18] = 0xF4240;

    if (flags & 1)
    {
        pAltimetry = pArea->altimetry;

        for (count = pArea->n_altimetry; count > 0; count--, pAltimetry++)
        {
            if (sub_helper_800296C4(pAltimetry, (SVECTOR *)getScratchAddr(3)))
            {
                sub_80029604(pAltimetry);
            }
        }
    }

    if (flags & 2)
    {
        ppAltimetry = pHzdMap->f1C_dynamic_floors;

        for (count = pHzdMap->f0C_dynamic_floor_index; count > 0; count--, ppAltimetry++)
        {
            if (sub_helper_800296C4(*ppAltimetry, (SVECTOR *)getScratchAddr(3)))
            {
                sub_80029604(*ppAltimetry);
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

void sub_800298C0(void *ptr)
{
    int *scratchpad = (int *)SCRPAD_ADDR;
    ((int *)ptr)[0] = scratchpad[15];
    ((int *)ptr)[1] = scratchpad[16];
}

void sub_800298DC(HZD_VEC *vec)
{
    int *blah = (int *)SCRPAD_ADDR;
    vec->long_access[0] = blah[0x11];
    vec->long_access[1] = blah[0x12];
}

int HZD_SlopeFloorLevel_800298F8(SVECTOR *param_1, SVECTOR *arg1)
{
    CopyVectorFromScratchpad_80029360(param_1, (SVECTOR *)(SCRPAD_ADDR + 0xC));
    return HZD_sub_80029514((HZD_FLR *)arg1);
}

static inline int sub_helper_8002992C(HZD_FLR *pAltimetry, SVECTOR *arg1)
{
    if ((pAltimetry->b1.z > arg1->vy) || (pAltimetry->b2.z < arg1->vy) ||
        (pAltimetry->b1.x > arg1->vx) || (pAltimetry->b2.x < arg1->vx))
    {
        return 0;
    }

    return 1;
}

int sub_8002992C(HZD_FLR *pAltimetry, SVECTOR *arg1)
{
    int *pScr;
    int *pScr2;

    CopyVectorFromScratchpad_80029360(arg1, (SVECTOR *)getScratchAddr(3));

    pScr = (int *)getScratchAddr(0);
    pScr[16] = 0;
    pScr[15] = 0;
    pScr[17] = 0xFFF0BDC0;
    pScr[18] = 0xF4240;

    if (sub_helper_8002992C(pAltimetry, (SVECTOR *)getScratchAddr(3)))
    {
        sub_80029604(pAltimetry);
    }

    pScr2 = (int *)getScratchAddr(0);

    if (pScr2[16] == 0)
    {
        return pScr2[15] != 0;
    }

    return (pScr2[15] == 0) ? 2 : 3;
}

int sub_80029A2C()
{
    HZD_FLR *hzdFlr;
    int      h;

    // Only a single place in code writes a pointer to 0x1F80003C
    // (in sub_80029604) and it's a HZD_FLR pointer.
    hzdFlr = *(HZD_FLR **)0x1F80003C;
    if (!hzdFlr)
    {
        return 0;
    }

    h = hzdFlr->b1.h;
    return h >> 8;
}
