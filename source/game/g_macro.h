#ifndef __MGS_G_MACRO_H__
#define __MGS_G_MACRO_H__

#ifndef __MGS_GAME_H__
#error "g_macro.h must be included via game.h!"
#endif

/*---------------------------------------------------------------------------*/
#ifndef __GAME_GAMED_C__
#ifndef __GAME_CONTROL_C__ // HACK: for GM_CurrentMap

// clang-format off

extern int GM_AlertMax;                 // for GM_SetAlert
extern int GM_NoisePower;               // for GM_SetNoise
extern int GM_NoiseLength;              //      〃
extern SVECTOR GM_NoisePosition;        //      〃

static inline void *GM_MakePrimChanl( int type, int n_prims, SVECTOR *pos, RECT *rect, int chanl )
{
    DG_PRIM *prim;

    prim = DG_MakePrim( type, n_prims, chanl, pos, rect );
    if ( prim ) {
        DG_QueuePrim( prim );
        DG_GroupPrim( prim, GM_CurrentMap );
    }
    return prim;
}

static inline void *GM_MakePrim( int type, int n_prims, SVECTOR *pos, RECT *rect )
{
    return GM_MakePrimChanl( type, n_prims, pos, rect, 0 ) ;
}

static inline void GM_FreePrim( DG_PRIM *prim )
{
    if ( prim != NULL ) {
        DG_DequeuePrim( prim ) ;
        DG_FreePrim( prim ) ;
    }
}

static inline void GM_ConfigPrimRoot( DG_PRIM *prim, OBJECT *obj, int unit )
{
    prim->root = &( obj->objs->objs[ unit ].world ) ;
}

static inline void GM_SetCurrentMap( int map )
{
    GM_CurrentMap = map ;
}

static inline int GM_GetCurrentMap()
{
    return GM_CurrentMap ;
}

#if 0
/* Currently unused. */
static  inline  void    GM_SetAlert( alert )
int                     alert ;
{
        if ( alert > 256 ) alert = 256 ;
        if ( alert > GM_AlertMax ) GM_AlertMax = alert ;
}
#endif

static inline void GM_SetAlertMax( int alert )
{
    if ( GM_AlertMax < alert ) GM_AlertMax = alert;
}

static inline void GM_SetNoise( int power, int length, SVECTOR *pos )
{
    int old ;

    old = GM_NoisePower ;
    if ( power < old ) return ;
    if ( power == old && length < GM_NoiseLength ) return ;
    GM_NoisePower = power ;
    GM_NoiseLength = length ;
    GM_NoisePosition = *pos ;
}

// clang-format on
#endif // __GAME_CONTROL_C__
#endif // __GAME_GAMED_C__
/*---------------------------------------------------------------------------*/

static inline void SetTargetClass( TARGET *target, unsigned int flag )
{
    target->class |= ( flag );
}

static inline void UnsetTargetClass( TARGET *target, unsigned int flag )
{
    target->class &= ~( flag );
}

/*---------------------------------------------------------------------------*/
#endif // __MGS_G_MACRO_H__
