// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (no C twin in the main tree, rank overlay asm: rank_800CEE0C, rank_800CEE90), VR revision adapted from the asm
#include "game/game.h"
#include "libgv/libgv.h"
#include "overlays/vrtitle/vrpocket.h"

extern int        vrtitle_dword_800D9CF4; // number of live objects
extern PocketObj *vrtitle_dword_800D9CF8; // head of the doubly linked list

// Allocates a pocket object and links it at the head of the list
PocketObj *vrtitle_800C2F0C( void )
{
    PocketObj *obj;
    PocketObj *head;

    if ( vrtitle_dword_800D9CF4 != POCKET_OBJ_MAX )
    {
        obj = GV_Malloc( sizeof( PocketObj ) );
        if ( obj != NULL )
        {
            GV_ZeroMemory( obj, sizeof( PocketObj ) );
            head = vrtitle_dword_800D9CF8;
            obj->next = NULL;
            obj->prev = NULL;
            vrtitle_dword_800D9CF8 = obj;
            obj->next = head;
            head->prev = obj;
            vrtitle_dword_800D9CF4++;
            return obj;
        }
    }

    return NULL;
}

// Unlinks and frees a pocket object
void vrtitle_800C2F90( PocketObj *obj )
{
    PocketObj *next;

    if ( obj == vrtitle_dword_800D9CF8 )
    {
        next = obj->next;
        vrtitle_dword_800D9CF8 = next;
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
    vrtitle_dword_800D9CF4--;
}
