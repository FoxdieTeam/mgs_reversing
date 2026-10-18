// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (no C twin in the main tree, rank overlay asm: rank_800CEE0C, rank_800CEE90), VR revision adapted from the asm
#include "game/game.h"
#include "libgv/libgv.h"
#include "overlays/vrtitle/vrpocket.h"

#define POCKET_OBJ_MAX_PKT_BACK 8

extern int        vrtitle_dword_800D9CFC; // number of live objects
extern PocketObj *vrtitle_dword_800D9D00; // head of the doubly linked list

// Allocates a pocket object and links it at the head of the list
PocketObj *vrtitle_800C988C( void )
{
    PocketObj *obj;
    PocketObj *head;

    if ( vrtitle_dword_800D9CFC != POCKET_OBJ_MAX_PKT_BACK )
    {
        obj = GV_Malloc( sizeof( PocketObj ) );
        if ( obj != NULL )
        {
            GV_ZeroMemory( obj, sizeof( PocketObj ) );
            head = vrtitle_dword_800D9D00;
            obj->next = NULL;
            obj->prev = NULL;
            vrtitle_dword_800D9D00 = obj;
            obj->next = head;
            head->prev = obj;
            vrtitle_dword_800D9CFC++;
            return obj;
        }
    }

    return NULL;
}

// Unlinks and frees a pocket object
void vrtitle_800C9910( PocketObj *obj )
{
    PocketObj *next;

    if ( obj == vrtitle_dword_800D9D00 )
    {
        next = obj->next;
        vrtitle_dword_800D9D00 = next;
        next->prev = NULL;
    }
    else
    {
        obj->prev->next = obj->next;
        obj->next->prev = obj->prev;
    }

    if ( obj->id < 0x80 )
    {
        GV_DelayedFree( obj->entries );
    }

    GV_DelayedFree( obj );
    vrtitle_dword_800D9CFC--;
}
