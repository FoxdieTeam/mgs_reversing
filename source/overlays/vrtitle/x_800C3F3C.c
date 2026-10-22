// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (rank_800CF3FC), adapted from the asm.
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

extern PocketObj *vrtitle_dword_800D9CF8; // head of the doubly linked list

// Scales the colours of all pocket objects with id < 0x80 by num / den
void vrtitle_800C3F3C( int num, int den )
{
    PocketObj *obj;
    POLY_FT4  *ft4;
    POLY_GT4  *gt4;
    int        i;

    obj = vrtitle_dword_800D9CF8;
    ft4 = NULL;
    gt4 = NULL;
    for ( ; obj != NULL; obj = obj->next )
    {
        if ( obj->enabled == 0 || obj->id >= 0x80 )
        {
            continue;
        }

        if ( obj->kind == 1 )
        {
            gt4 = obj->entries;
        }
        else
        {
            ft4 = obj->entries;
        }

        i = obj->count;
        i--; // FIXME: separate decrement keeps the count load in the loop register
        for ( ; i >= 0; i-- )
        {
            if ( obj->kind == 1 )
            {
                gt4->r0 = gt4->r0 * num / den;
                gt4->g0 = gt4->g0 * num / den;
                gt4->b0 = gt4->b0 * num / den;
                gt4->r1 = gt4->r1 * num / den;
                gt4->g1 = gt4->g1 * num / den;
                gt4->b1 = gt4->b1 * num / den;
                gt4->r2 = gt4->r2 * num / den;
                gt4->g2 = gt4->g2 * num / den;
                gt4->b2 = gt4->b2 * num / den;
                gt4->r3 = gt4->r3 * num / den;
                gt4->g3 = gt4->g3 * num / den;
                gt4->b3 = gt4->b3 * num / den;
                gt4++;
            }
            else
            {
                ft4->r0 = ft4->r0 * num / den;
                ft4->g0 = ft4->g0 * num / den;
                ft4->b0 = ft4->b0 * num / den;
                ft4++;
            }
        }
    }
}
