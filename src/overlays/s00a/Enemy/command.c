#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/map.h"

typedef struct _Work
{
    GV_ACT         actor;
    unsigned short unk; //0x20
    unsigned short unk2; //0x22
    int            name; //0x24
} Work;


//probably something obvious
typedef struct Struct_800E0D98
{
    int field_0x00;
    int field_0x04;
    int field_0x08;
    int field_0x0C;
} Struct_800E0D98;

extern SVECTOR DG_ZeroVector_800AB39C;

extern int dword_800E01F4;

extern int dword_800E0940;
extern int dword_800E095C;

extern int dword_800E0D90; //maybe COM_PlayerAddress

extern Struct_800E0D98 dword_800E0D98; //maybe EnemyCommand


extern int dword_800E0CA0;

extern int dword_800E0D2C;
extern int dword_800E0D30;

extern int dword_800E0D88;
extern int dword_800E0D8C;

extern short dword_800E0E3C;

extern int COM_PlayerMap_800E0F1C;
extern int TOPCOMMAND_800E0F20;
extern int dword_800E0F28;

extern SVECTOR COM_PlayerPosition_800E0F30;

extern int COM_NOISEMODE_DIS_800E0F38;
extern int COM_GameStatus_800E0F3C;

extern int COM_PlayerAddressOne_800E0F40;

extern int dword_800E0F60;
extern int dword_800E0F64;
extern int dword_800E0F68;


extern short sub_800CEDE8( int ops, void *val, int where );
extern short sub_800CED88( int ops, SVECTOR* svec );
extern int   sub_800D0128( int ops );
extern void  sub_800D018C( Work* work ) ;
extern void  sub_800D0344( void ) ;
extern void  sub_800CFEA8( void ) ;
extern void  sub_800D0218( void ) ;
extern void  sub_800CFA94( Work* work ) ;
extern void  sub_800CEC90( void ) ;
extern void  sub_800CECF4( void ) ;

void CommandAct_800D0258( Work* work )
{
    if (GM_CheckMessage_8002631C( &work->actor , work->name, 0x3223) != NULL)
    {
        GV_DestroyActor_800151C8( &work->actor );
        return;
    }
    
    sub_800D018C( work );
    sub_800D0344();
    sub_800CFEA8();
    sub_800D0218();
    sub_800CFA94( work );
    sub_800CEC90();
    sub_800CECF4();
    dword_800E0D98.field_0x0C++;
}

void CommandDie_800D02EC(void)
{
    return;
}

static inline void v_option( int where )
{
    void *s0;
    int ops;
    s0 = &dword_800E0D98;
    *(int*)(s0 + 0xC) = 0;
    *(int*)(s0 + 0x18) = 0;
    TOPCOMMAND_800E0F20 = 0;

    ((int*)&TOPCOMMAND_800E0F20)[1] = 0;
    *(MAP**)(s0 + 0xA0) = Map_FromId_800314C0( where );

    ops = GCL_GetParam_80020968( 'v' );
    if ( ops ) 
    {
        *(short*)(s0 + 0x54) = sub_800CEDE8( ops, (s0 + 0x5A) , where );
    } 
    else 
    {
        *(short*)(s0 + 0x54) = 1;
        *(short*)(s0 + 0x58) = 0;
    }
}

static inline void set_game_status()
{
    int ops;
    COM_GameStatus_800E0F3C = 0;

    ops = GCL_GetParam_80020968( 'a' );
    if ( ops )
    {
        COM_GameStatus_800E0F3C |= GCL_GetNextInt_800209E8( (unsigned char*)ops );
    } 
}

static inline void j_option()
{
    int ops;

    ops = GCL_GetParam_80020968( 'j' );
    if ( ops )
    {
        *(&dword_800E0E3C + 1) = sub_800CED88( ops, (SVECTOR*)&dword_800E0E3C );
    } 
    else
    {
        void* temp = &dword_800E0D98;
        *(short*)(temp + 0xA6) = 1;
        *(short*)(temp + 0xA8) = 0;
        *(short*)(temp + 0xAA) = 0;
    }
}

static inline void nmcs_option( int where )
{
    void *s0;
    int ops, ops2, ops3, ops4;
    
    s0 = &dword_800E0D98;
    *(short*)(s0 + 0xA4) = where;
    *(int*)(s0 + 0x08) = 0;
    
    ops = GCL_GetParam_80020968( 'n' );
    if ( ops )
    {
        *(int*)(s0 + 0x08) = sub_800D0128( ops );
    }

    ops2 = GCL_GetParam_80020968( 'm' );
    if ( ops2 )
    {
        *(int*)(s0 + 0x08) += sub_800D0128( ops2 );
    }

    *(int*)s0 = 0;
    
    ops3 = GCL_GetParam_80020968( 'c' );
    if ( ops3 )
    {
        *(int*)s0 = sub_800D0128( ops3 );
    }
    
    *(int*)(s0 + 0x04) = 0;
    
    ops4 = GCL_GetParam_80020968( 's' );
    if ( ops4 )
    {
        *(int*)(s0 + 0x04) = sub_800D0128( ops4 );
    }
}

static inline void wz_option( void* in )
{
    void* s0;
    int ops;
    s0 = &dword_800E0D98;
    printf( in, *(short*)( s0 + 0x88 ), *(short*)( s0 + 0x8A ), *(short*)( s0 + 0x8C ), dword_800E0F60  ); 
    
    *(int *)(s0 + 0x1C) = 0x1E;

    *(short*)(s0 + 0x56) = 0;
    *(int*)(s0 + 0x16C)  = 0;
    *(int*)(s0 + 0x174)  = 0;
    
    dword_800E0F28 = 0;
    *(short*)(s0 + 0x178)  = 0;
    dword_800E0D8C = *(short*)(s0 + 0x88);
    dword_800E0D88 = *(short*)(s0 + 0x88) + 0x1F4;

    ops = GCL_GetParam_80020968( 'w' );
    if ( ops )
    {
        *(short*)(s0 + 0x178) = GCL_GetNextInt_800209E8( (unsigned char*)ops );
    }

    ops = GCL_GetParam_80020968( 'z' );
    if ( ops )
    {
        *(int*)(s0 + 0x178) = GCL_GetNextInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    } 
    else 
    {
        *(int*)(s0 + 0x178) = -1;
    }
}


static inline void switch_test( short val )
{
    switch ( val )
    {
        case 0:
            dword_800E0F60 = 4;
            break;
        case 1:
            dword_800E0F60 = 3;
            break;
        case 2:
            dword_800E0F60 = val;
            break;
        default:
            dword_800E0F60 = 4;
    }
}

void CommandGetResources_800D04F4( Work *work, int name, int where )
{
    int   ops2, ops3, ops4, ops5;
    void *s0;
    void* s1;
    void *a2;
    void *v1;
    int   a3;
    
    a3 = 0;
    a2 = &dword_800E0D98;
    work->name = name;

    dword_800E0F64 = 0;
    *(short*)(a2 + 0x17A) = 1;
    dword_800E0D90 = 0;
    *(int*)  (a2 + 0x14)  = 0;
    *(int*)  (a2 + 0x170) = 0;
    
    *(short*)(a2 + 0x180) = 0;
    *(short*)(a2 + 0x182) = 0;
    *(int*)  (a2 + 0x40)  = 0;
    
    COM_PlayerPosition_800E0F30 = DG_ZeroVector_800AB39C;
    COM_PlayerMap_800E0F1C = where;
    dword_800E0F68 = 0;
    dword_800E0CA0 = 0;
    dword_800E0D30 = 0;
    dword_800E0D2C = 0;

    for ( ; a3 < 8 ; a3++ )
    {
        *(int*)(a2 + (a3 * 16) + 0xC8) = 0;
        *(int*)(a2 + (a3 * 16) + 0xCC) = 0;
        *(int*)(a2 + (a3 * 16) + 0xD0) = 0;
        *(int*)(a2 + (a3 * 16) + 0xD4) = 0;
    }

    v1 = &dword_800E0D98;
    for ( a3 = 0 ; a3 < 8 ; a3++ )
    {
        *(int*)(v1 + (a3 * 4) + 0x68)  = a3;
        *(int*)(v1 + (a3 * 4) + 0x20)  = 0;
        *(int*)(v1 + (a3 * 4) + 0x148) = 0xFF;
    }
    v_option( where );

    s1 = &dword_800E0D98;
    *(int*)(s1 + 0x94) = 5;
    
    ops2 = GCL_GetParam_80020968( 'b');
    if ( ops2 )
    {
        *(int*)(s1 + 0x94) = GCL_GetNextInt_800209E8( (unsigned char*)ops2 );
    }
    
    *(short*)(s1 + 0x88) = 0xFA0;
    *(short*)(s1 + 0x8A) = 0xFA0;
    *(short*)(s1 + 0x8C) = 0xFA0;

    ops3 = GCL_GetParam_80020968( 'l' );
    if ( ops3 ) 
    {
        GCL_GetSV_80020A14( (unsigned char*)ops3, (SVECTOR* )(s1 + 0x88) );
    }

    //loc_800D06A0:
    s0 = &COM_NOISEMODE_DIS_800E0F38;
    *(int*)s0 = 0x1F40;

    ops4 = GCL_GetParam_80020968( 'y' );
    if ( ops4 )
    {
        *(int*)s0 = GCL_GetNextInt_800209E8( (unsigned char*)ops4 );
    }

    printf( ( void* )&dword_800E0940 , *(int*)s0 );
    *(short*)(s1 + 0x8E) = 0;

    ops5 = GCL_GetParam_80020968( 't' );
    if ( ops5 ) {
        *(short*)(s1 + 0x8E) = GCL_GetNextInt_800209E8( (unsigned char*)ops5 );
    }
    
    switch_test( *(short*)(s1 + 0x8E) );


    wz_option( &dword_800E095C );
    set_game_status();
    j_option();
    nmcs_option( where );
}

void *NewCommander_800D0908( int name, int where, int argc, char **argv )
{
    Work *work ;

    work = (Work *)GV_NewActor_800150E4( 4, sizeof( Work ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )CommandAct_800D0258, ( TActorFunction )CommandDie_800D02EC, "command.c");
        CommandGetResources_800D04F4( work, name, where );
    }
    return (void *)work ;
}