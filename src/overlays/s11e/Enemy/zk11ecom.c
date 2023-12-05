#include "../../s00a/Enemy/enemy.h"

extern TOPCOMMAND_STRUCT s11e_dword_800DF3A8;


#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A20.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A64.s")



//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A84.s")
void ZAKO11E_SetTopCommAL_800D9A84( int alert )
{
    s11e_dword_800DF3A8.alert = alert;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D9A90.s")
void ZAKO11E_SetTopCommMD_800D9A90( int mode )
{
    s11e_dword_800DF3A8.mode = mode;
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
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DACA0.s")

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DAF38.s")
/*
extern void s11e_zk11ecom_800DABF4();
extern void s11e_zk11ecom_800DAC5C();
extern const char s11e_aZkecomc_800DED84[];

GV_ACT *s11e_zk11ecom_800DAF38(int name, int where, int argc, char **argv)
{
    CommanderWork *work ;

    work = (ZakoCommanderWork *)GV_NewActor_800150E4( 4, sizeof( ZakoCommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )s11e_zk11ecom_800DABF4, ( TActorFunction )s11e_zk11ecom_800DAC5C, s11e_aZkecomc_800DED84 );
        s11e_zk11ecom_800DACA0( work, name, where );
    }
    return &work->actor;
}
*/