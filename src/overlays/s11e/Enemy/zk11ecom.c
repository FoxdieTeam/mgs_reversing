#include "../../s00a/Enemy/enemy.h"

extern ZAKO_COMMAND ZakoCommand_800DF280;
extern TOPCOMMAND_STRUCT TOPCOMMAND_800DF3A8;

extern int s11e_dword_800DF39C; 
extern int s11e_dword_800DF3A0; 
extern int s11e_dword_800DF3B0;
extern int s11e_dword_800DF3B4;

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A20.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A64.s")



//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A84.s")
void ZAKO11E_SetTopCommAL_800D9A84( int alert )
{
    TOPCOMMAND_800DF3A8.alert = alert;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A90.s")
void ZAKO11E_SetTopCommMD_800D9A90( int mode )
{
    TOPCOMMAND_800DF3A8.mode = mode;
}

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A9C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9AE8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9B60.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9BD4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9C34.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9C8C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9D7C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9DBC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9E10.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9E64.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9EB8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9F0C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9F60.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9FF0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA044.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA0A8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA16C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA2BC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA3A0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA4B8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA4D0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA534.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA690.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA784.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA7F8.s")

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA85C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DABF4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DAC5C.s")


extern int s11e_zk11ecom_800D9C34( int, short * );
extern int s11e_zk11ecom_800D9BD4( int, A4_STRUCT * );
extern int s11e_zk11ecom_800DA7F8( int );

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DACA0.s")

extern const char s11e_aZoned_800DED64[]; // = "zone=%d ";
extern const char s11e_aEnemyvoicexx_800DED70[]; // = "ENEMY VOICE [0x%x]\n";
void s11e_zk11ecom_800DACA0( ZakoCommanderWork *work, int name, int where )
{
    int i;
    int ops;

    s11e_dword_800DF3B4 = 0;
    
    ZakoCommand_800DF280.field_0x20 = 0;
    ZakoCommand_800DF280.field_0x18 = 0;
    ZakoCommand_800DF280.field_0x10 = 0;
    ZakoCommand_800DF280.field_0x60 = 0;

    for ( i = 0 ; i < 8 ; i++ )
    {
        ZakoCommand_800DF280.field_0x8C[i].field_00 = 0;
        ZakoCommand_800DF280.field_0x8C[i].field_04 = 0;
        ZakoCommand_800DF280.field_0x8C[i].field_08 = 0;
        ZakoCommand_800DF280.field_0x8C[i].watcher  = 0;
    }

    for ( i = 0 ; i < 8 ; i++ )
    {
        ZakoCommand_800DF280.field_0x40[i]  = i;
    }

    ZakoCommand_800DF280.field_0x0C = 0;
    ZakoCommand_800DF280.field_0x1C = 0;
    
    TOPCOMMAND_800DF3A8.mode = 0;
    TOPCOMMAND_800DF3A8.alert = 0;

    ZakoCommand_800DF280.field_0x64 = Map_FromId_800314C0( where );

    ops = GCL_GetOption_80020968( 'v' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x34 = s11e_zk11ecom_800D9C34( ops, ZakoCommand_800DF280.field_0x38 );
    }
    else
    {
        ZakoCommand_800DF280.field_0x34 = 1;
        ZakoCommand_800DF280.field_0x38[0] = 0;
    }

    for ( i = 0 ; i < ZakoCommand_800DF280.field_0x34 ; i++ )
    {
        fprintf( 1, s11e_aZoned_800DED64, ZakoCommand_800DF280.field_0x38[i] );
    }

    ZakoCommand_800DF280.field_0x36 = 0;
    s11e_dword_800DF3B0 = 0;

    ops = GCL_GetOption_80020968( 'j' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x68.n_entry = s11e_zk11ecom_800D9BD4( ops, &ZakoCommand_800DF280.field_0x68 );
    }
    else
    {
        ZakoCommand_800DF280.field_0x68.n_entry = 1;
        ZakoCommand_800DF280.field_0x68.field_04->field_00 = 0;
        ZakoCommand_800DF280.field_0x68.field_04->field_02 = 0;
    }

    ZakoCommand_800DF280.field_0x68.map_id  = where;
    ZakoCommand_800DF280.field_0x114  = 0;

    ops = GCL_GetOption_80020968( 'b' );
    if ( ops )
    {
        int res = GCL_StrToInt_800209E8( (unsigned char*)ops );
        ZakoCommand_800DF280.field_0x114 = res;
        printf( s11e_aEnemyvoicexx_800DED70, res );
    }

    ops = GCL_GetOption_80020968( 'e' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x118 = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }
    else
    {
        ZakoCommand_800DF280.field_0x118 = -1;
    }

    ops = GCL_GetOption_80020968( 'm' );
    if ( ops )
    {
        s11e_dword_800DF3A0 = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }
    else
    {
        s11e_dword_800DF3A0 = -1;
    }

    ops = GCL_GetOption_80020968( 'k' );
    if ( ops )
    {
        s11e_dword_800DF39C = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }
    else
    {
        s11e_dword_800DF39C = -1;
    }

    ZakoCommand_800DF280.field_0x08 = 0;
    ops = GCL_GetOption_80020968( 'n' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x08 = s11e_zk11ecom_800DA7F8( ops );
    }

    ZakoCommand_800DF280.field_0x00  = 0;
    ZakoCommand_800DF280.field_0x04  = 0;
    ZakoCommand_800DF280.field_0x110 = 0;
    GM_VoxStream_80037E40( ZakoCommand_800DF280.field_0x114, 0x40000000);    
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DAF38.s")

extern void s11e_zk11ecom_800DABF4();
extern void s11e_zk11ecom_800DAC5C();
extern const char s11e_aZkecomc_800DED84[];

GV_ACT *s11e_zk11ecom_800DAF38(int name, int where, int argc, char **argv)
{
    ZakoCommanderWork *work ;

    work = (ZakoCommanderWork *)GV_NewActor_800150E4( 4, sizeof( ZakoCommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )s11e_zk11ecom_800DABF4, ( TActorFunction )s11e_zk11ecom_800DAC5C, s11e_aZkecomc_800DED84 );
        s11e_zk11ecom_800DACA0( work, name, where );
    }
    return &work->actor;
}
