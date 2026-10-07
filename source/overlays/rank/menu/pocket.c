#include <stdio.h>
#include "mts/mts.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/radio.h"
#include "menu/menuman.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT    actor;
    KCB       kcb;
    int       proc_id;
    int       field_50;
    MenuPrim *prim_ptr;
    MenuPrim  prim;
    char      primbuf[ 2 ][ 0x2000 ];
} Work;

const char rank_dword_800E03BC[] = "id::%d\n";
const char rank_dword_800E03C4[] = "------------\n";
const char rank_dword_800E03D4[] = "SERIAL:0x%08x=%d(10)\n";
const char rank_dword_800E03EC[] = "------------CHANGE BIGBOSS\n";
const char rank_dword_800E0408[] = "------------%08x\n";
const char rank_dword_800E041C[] = "-----------------------------\n";

/*---------------------------------------------------------------------------*/

extern GV_PAD *GM_CurrentPadData;

extern char  rank_dword_800C326C[];
extern char  rank_dword_800E06E4[];

extern int    rank_dword_800E1870;
extern int    rank_dword_800E1874;
extern int    rank_dword_800E1878;
extern int    rank_dword_800E187C;
extern RadioFileModeStruElem *rank_dword_800E189C;
extern int    rank_dword_800E18A0;
extern int    rank_dword_800C330C[];

void rank_800CD1A8( MenuPrim *prim, RadioFileModeStruElem *elem );
void rank_800CD230( MenuPrim *prim, RadioFileModeStruElem *elem );
void rank_800CD32C( MenuPrim *prim, RadioFileModeStruElem *elem );
void rank_800CDFC8( MenuPrim *prim, SELECT_INFO *info );

/*---------------------------------------------------------------------------*/

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CBD14.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC014.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC104.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC19C.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC1E0.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC260.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC3D4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC658.s")

int rank_800CC70C( int arg0 )
{
    rank_dword_800E1874 = arg0;
    mts_slp_tsk();
    return rank_dword_800E1878;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC738.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC798.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CC7C0.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CCDC4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CCEC4.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CCF10.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CCF64.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CCFC4.s")

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CD074.s")
void rank_800CD074( Work *work );

void rank_800CD178( int *arr, int len )
{
    int i;

    for ( i = 0; i < len; i++, arr += 2 )
    {
        arr[ 0 ] += arr[ 1 ];
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CD1A8.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CD230.s")
#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CD32C.s")
void rank_800CD474( MenuPrim *prim, RadioFileModeStruElem *elem )
{
    RadioFileModeUnk1 *unk;

    unk = elem->field_C_unk1;
    if ( elem->field_0 == 1 )
    {
        rank_800CD178( &unk->field_4, 2 );
    }

    *(short *)unk->field_14 = unk->field_4 >> 16;
    *(short *)( unk->field_14 + 2 ) = unk->field_C >> 16;
    rank_800CDFC8( prim, (SELECT_INFO *)unk->field_14 );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CD4E4.s")
void rank_800CD4E4( void );

void rank_800CD540( void )
{
    GV_FreeMemory( GV_PACKET_MEMORY0, rank_dword_800E189C );
}

void rank_800CD568( int idx, int x, int y, int divisor, int idx2 )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeUnk2          *unk;
    RadioFileModeStruElem      *elem;

    rfm = (RadioFileModeStru_800ABB7C *)rank_dword_800E189C;
    unk = &rfm->field_c0_array[ idx ];
    elem = &rfm->field_0_array[ idx ];

    unk->field_4 = (const char *)rank_dword_800C330C[ idx2 ];

    elem->field_8_pFn = rank_800CD1A8;
    elem->field_C_unk1 = (RadioFileModeUnk1 *)unk;

    if ( idx2 < 0 )
    {
        elem->field_0 = 0;
        return;
    }

    if ( divisor <= 0 )
    {
        unk->field_8 = x * 65536;
        unk->field_10 = y * 65536;
        elem->field_0 = 2;
    }
    else
    {
        unk->field_C = ( x * 65536 - unk->field_8 ) / divisor;
        unk->field_14 = ( y * 65536 - unk->field_10 ) / divisor;
        elem->field_0 = 1;
    }

    unk->field_18 = 0x748956;
    elem->field_4 = divisor;
}
void rank_800CD688( int idx, int x, int y, int divisor, SELECT_INFO *info )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeUnk1          *unk;
    RadioFileModeStruElem      *elem;

    rfm = (RadioFileModeStru_800ABB7C *)rank_dword_800E189C;
    elem = &rfm->field_0_array[ idx ];
    unk = &rfm->field_220_unk1;

    elem->field_8_pFn = rank_800CD474;
    elem->field_C_unk1 = unk;

    if ( divisor <= 0 )
    {
        unk->field_4 = x * 65536;
        unk->field_C = y * 65536;
        elem->field_0 = 2;
    }
    else
    {
        unk->field_8 = ( x * 65536 - unk->field_4 ) / divisor;
        unk->field_10 = ( y * 65536 - unk->field_C ) / divisor;
        elem->field_0 = 1;
    }

    unk->field_14 = (int)info;
    elem->field_4 = divisor;
}

void rank_800CD760( int idx, int x0, int y0, int x1, int y1, int divisor )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeUnk1          *unk;
    RadioFileModeStruElem      *elem;

    rfm = (RadioFileModeStru_800ABB7C *)rank_dword_800E189C;
    elem = &rfm->field_0_array[ idx ];
    unk = &rfm->field_130_array[ idx - 5 ];

    elem->field_8_pFn = rank_800CD230;
    elem->field_C_unk1 = unk;
    if ( divisor <= 0 )
    {
        unk->field_4 = x0 * 65536;
        unk->field_C = y0 * 65536;
        unk->field_14 = x1 * 65536;
        unk->field_1C = y1 * 65536;
        elem->field_0 = 2;
    }
    else
    {
        unk->field_8 = ( x0 * 65536 - unk->field_4 ) / divisor;
        unk->field_10 = ( y0 * 65536 - unk->field_C ) / divisor;
        unk->field_18 = ( x1 * 65536 - unk->field_14 ) / divisor;
        unk->field_20 = ( y1 * 65536 - unk->field_1C ) / divisor;
        elem->field_0 = 1;
    }

    unk->field_24 = 0x3d482e;
    elem->field_4 = divisor;
}

void rank_800CD8D8( int index )
{
    RadioFileModeStruElem *entry;

    entry = &rank_dword_800E189C[ index ];
    entry->field_0 = 0;
}

void rank_800CD8F0( int x0, int y0, int x1, int y1, int divisor )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeStruElem      *elem;
    RadioFileModeUnk1          *unk;

    rfm = (RadioFileModeStru_800ABB7C *)rank_dword_800E189C;
    elem = &rfm->field_0_array[ 11 ];
    unk = (RadioFileModeUnk1 *)&rfm->field_220_unk1.field_18;

    elem->field_8_pFn = rank_800CD32C;
    elem->field_C_unk1 = unk;

    if ( divisor <= 0 )
    {
        unk->field_4 = x0 * 65536;
        unk->field_C = y0 * 65536;
        unk->field_14 = x1 * 65536;
        unk->field_1C = y1 * 65536;
        elem->field_0 = 2;
    }
    else
    {
        unk->field_8 = ( x0 * 65536 - unk->field_4 ) / divisor;
        unk->field_10 = ( y0 * 65536 - unk->field_C ) / divisor;
        unk->field_18 = ( x1 * 65536 - unk->field_14 ) / divisor;
        unk->field_20 = ( y1 * 65536 - unk->field_1C ) / divisor;
        elem->field_0 = 1;
    }

    elem->field_4 = divisor;
}

void rank_800CDA44( void *prim )
{
    RadioFileModeStruElem *entry;
    int i;

    entry = rank_dword_800E189C;
    for ( i = 0; i < 12; i++, entry++ )
    {
        if ( entry->field_0 == 0 ) continue;

        if ( entry->field_4 < 0 )
        {
            entry->field_4++;
        }
        else
        {
            entry->field_8_pFn( prim, entry );
            if ( entry->field_0 == 1 && --entry->field_4 == 0 ) entry->field_0 = 2;
        }
    }
}

void rank_800CDB1C( SPRT *sprt )
{
    LSTORE( 0x80808080, &sprt->r0 );
    setSprt( sprt );
    setClut( sprt, 960, 510 );
}

void rank_800CDB44( Work *work, char *string )
{
    KCB *kcb;
    int height;

    kcb = &work->kcb;

    height = kcb->height;
    kcb->height = 14;
    font_clear( kcb );
    kcb->height = height;

    font_draw_string( kcb, 0, 0, string, 0 );
    font_update( kcb );
}

void rank_800CDBB0( Work *work, u_long *ot )
{
    KCB *kcb;
    SPRT *sprt;

    kcb = &work->kcb;
    _NEW_PRIM( sprt, work->prim_ptr );
    rank_800CDB1C( sprt );
    setXY0( sprt, 160 - kcb->max_width / 2, 200 );
    setUV0( sprt, 0, 4 );
    setWH( sprt, 252, 14 );
    addPrim( ot, sprt );
}

void rank_800CDC70( SELECT_INFO *info )
{
    if ( info != NULL ) GV_FreeMemory( GV_PACKET_MEMORY0, info );
}

void rank_800CDC98( SELECT_INFO **info, int num )
{
    if ( *info != NULL ) return;
    *info = GV_AllocMemory( GV_PACKET_MEMORY0, sizeof(SELECT_INFO) + num * sizeof(MENU_CURPOS) );
    if ( *info == NULL ) printf( rank_dword_800E06E4 );
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CDCF4.s")

void rank_800CDEB8( Work *work, char **menu_text, int menu_num, int initial, char *message, SELECT_INFO *info )
{
    MENU_CURPOS *menu;
    int i;

    menu = info->menu;
    for ( i = 0; i < menu_num; i++ )
    {
        strcpy( menu->mes, menu_text[ i ] );
        menu->num = i;
        menu++;
    }

    info->kcb = &work->kcb;
    info->max_num = menu - info->menu;
    info->current = initial;
    info->top = 0;
    info->message = message;
    info->field_E = 1;
    info->xofs = 160;
    info->yofs = 128;
    info->width = 64;
    info->height = 32;
    info->move_dir = 0;
    info->enable = 1;
}

void rank_800CDFC8( MenuPrim *prim, SELECT_INFO *info )
{
    int        i;
    int        xpos, ypos;
    TextConfig config;

    config.flags = 0x12;
    if ( info->enable != 0 )
    {
        config.color = 0x66748956;
    }
    else
    {
        config.color = 0x663d482e;
    }
    config.xpos = info->xofs;
    config.ypos = info->yofs;
    _menu_number_draw_string2( prim, &config, info->message );

    if ( info->max_num == 1 )
    {
        xpos = info->xofs;
    }
    else
    {
        xpos = info->xofs - info->width / 2;
    }

    for ( i = 0; i < info->max_num; i++, xpos += info->width )
    {
        config.xpos = xpos;
        ypos = info->yofs;
        config.ypos = ypos + 12;

        if ( i == info->current )
        {
            config.color = 0x66748956;
            if ( info->enable != 0 )
            {
                ypos += 16;
                rank_800CD8F0( config.xpos, ypos, info->height, 12, 2 );
            }
        }
        else
        {
            config.color = 0x663d482e;
        }
        _menu_number_draw_string2( prim, &config, info->menu[ i ].mes );
    }
}

int rank_800CE148( GV_PAD *pad, int *res, SELECT_INFO *info )
{
    u_short status;

    status = pad->status;
    if ( info->max_num > 1 )
    {
        if ( status & PAD_LEFT )
        {
            if ( info->current != 0 )
            {
                GM_SeSet2( 0, 63, SE_MENU_CURSOR );
                info->current = 0;
            }
        }
        else if ( status & PAD_RIGHT )
        {
            if ( info->current == 0 )
            {
                GM_SeSet2( 0, 63, SE_MENU_CURSOR );
                info->current = 1;
            }
        }
    }

    if ( pad->press & PAD_CIRCLE )
    {
        *res = info->menu[ info->current ].num;
        GM_SeSet2( 0, 63, SE_MENU_SELECT );
        return 1;
    }

    if ( pad->press & PAD_CROSS )
    {
        GM_SeSet2( 0, 63, SE_MENU_EXIT );
        *res = info->field_E;
        return 1;
    }

    return 0;
}

void rank_800CE260( MenuPrim *prim, u_long *ot )
{
    POLY_F3 *poly;

    if ( ( GV_Time % 16 ) >= 4 )
    {
        _NEW_PRIM( poly, prim );

        poly->x1 = 288;
        poly->y1 = 210;
        poly->x0 = poly->x1 - 4;
        poly->x2 = poly->x1 + 4;
        poly->y2 = poly->y1 - 4;
        poly->y0 = poly->y2;

        LSTORE( 0x80808080, &poly->r0 );
        setPolyF3( poly );
        addPrim( ot, poly );
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800CE330.s")
int rank_800CE330( Work *work, GV_PAD *pad, int field_50 );

void rank_800CEBA8( Work *work )
{
    u_long *ot;

    work->prim_ptr->next = work->prim_ptr->buf[ GV_Clock ];
    work->prim_ptr->end = work->prim_ptr->next + 0x2000;

    ot = DG_Chanl( 1 )->ot[ GV_Clock ];
    work->prim_ptr->ot = ot;

    if ( rank_800CE330( work, &GM_CurrentPadData[ 2 ], work->field_50 ) )
    {
        GV_DestroyActor( work );
    }
}

void rank_800CEC40( Work *work )
{
    GCL_ARGS arg;
    long data[ 2 ];

    GV_ResetPacketMemory();
    GV_PauseLevel &= ~GV_PAUSE_STOP;
    DG_RestartMainChanlSystem();

    if ( work->proc_id >= 0 )
    {
        arg.argc = 2;
        arg.argv = data;
        data[ 0 ] = rank_dword_800E1870;
        data[ 1 ] = rank_dword_800C326C[ 1 ] - 48;
        GCL_ForceExecProc( work->proc_id, &arg );
    }
}

void *rank_800CECC0( int arg0 )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_MANAGER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, rank_800CEBA8, rank_800CEC40, "pocket.c" );

        if ( GCL_GetOption( 'p' ) )
        {
            work->proc_id = GCL_GetNextInt();
        }
        else
        {
            work->proc_id = -1;
        }

        work->prim.buf[ 0 ] = work->primbuf[ 0 ];
        work->prim.buf[ 1 ] = work->primbuf[ 1 ];
        work->prim_ptr = &work->prim;

        GV_PauseLevel |= GV_PAUSE_STOP;

        DG_StopMainChanlSystem();
        DG_BackGroundBlack();
        GV_SetPacketTempMemory();

        rank_800CD074( work );
        rank_800CD4E4();

        work->field_50 = arg0;

        if ( arg0 == 0 )
        {
            rank_dword_800E187C = 2;
        }
        else
        {
            rank_dword_800E187C = 3;
        }

        rank_dword_800E1878 = -1;

        mts_wup_tsk( 8 /* MTSID_POCKET */ );

        rank_dword_800E18A0 = 0;
    }
    return (void *)work;
}

void *rank_800CEDCC( void )
{
    return rank_800CECC0( 0 );
}

void *rank_800CEDEC( void )
{
    return rank_800CECC0( 1 );
}
