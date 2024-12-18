#include "meryl72.h"

#define TH1_PHASE0 0
#define TH1_PHASE1 1
#define TH1_PHASE2 2
#define TH1_PHASE3 3

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CC9A8.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CC9E0.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCA68.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCAD8.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCB2C.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCB64.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCCC8.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCD1C.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCD98.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCEC4.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCF5C.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CCFE0.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD038.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD14C.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD260.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD2E0.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD380.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD3C4.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD408.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD474.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD76C.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD7C4.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CD80C.s")

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CDA88.s")
void s07c_meryl72_unk2_800CDA88(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CDC34.s")
void s07c_meryl72_unk2_800CDC34(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CDEC4.s")
void s07c_meryl72_unk2_800CDEC4(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CDFC8.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE08C.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE124.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE198.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE218.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE314.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE3BC.s")
#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE450.s")

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE524.s")
void s07c_meryl72_unk2_800CE524( Meryl72Work* work );

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE5AC.s")
void s07c_meryl72_unk2_800CE5AC( Meryl72Work* work );

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE5FC.s")
void s07c_meryl72_unk2_800CE5FC( Meryl72Work* work );

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE64C.s")
void s07c_meryl72_unk2_800CE64C( Meryl72Work* work );

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE69C.s")
void s07c_meryl72_unk2_800CE69C( Meryl72Work* work );

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CE738.s")
void s07c_meryl72_unk2_800CE738( Meryl72Work* work );

void s07c_meryl72_unk2_800CE7D4(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 4:
        s07c_meryl72_unk2_800CDC34(work);
        break;

    case 5:
        s07c_meryl72_unk2_800CDA88(work);
        break;
    }
}

void s07c_meryl72_unk2_800CE824(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 4:
        s07c_meryl72_unk2_800CDEC4(work);
        break;

    case 5:
        s07c_meryl72_unk2_800CDA88(work);
        break;
    }
}

void Think1_Phase0_800CE874( Meryl72Work* work )
{
    if (work->think2 == 0)
    {
        s07c_meryl72_unk2_800CE524( work );
    }
}

void Think1_Phase1_800CE8A4( Meryl72Work* work )
{
    switch (work->think2)
    {
    case 2:
        s07c_meryl72_unk2_800CE69C( work );
        return;
    case 3:
        s07c_meryl72_unk2_800CE738( work );
        return;
    }
}

void Think1_Phase2_800CE8F4( Meryl72Work* work )
{
    switch ( work->think2 )
    {
    case 1:
        s07c_meryl72_unk2_800CE5FC( work );
        return;
    case 2:
        s07c_meryl72_unk2_800CE7D4( work );
        return;
    case 3:
        s07c_meryl72_unk2_800CE738( work );
        return;
    }
}

void Think1_Phase3_800CE970( Meryl72Work* work )
{
    switch ( work->think2 )
    {
    case 0:
        s07c_meryl72_unk2_800CE5AC( work );
        return;
    case 1:
        s07c_meryl72_unk2_800CE64C( work );
        return;
    case 2:
        s07c_meryl72_unk2_800CE824( work );
        return;
    case 3:
        s07c_meryl72_unk2_800CE738( work );
        return;
    }
}

void	Meryl72Think_800CEA04( Meryl72Work* work )
{
	int	i ;

	work->pad.dir = -1 ;
	work->pad.press = 0 ;
/*
	if ( ToilletArea( &ENEMYPOS ) ) {
		work->control.radar_atr = RADAR_SIGHT | RADAR_ALL_MAP ;
	} else {
		work->control.radar_atr = RADAR_VISIBLE | RADAR_SIGHT | RADAR_ALL_MAP ;
	}
*/

	switch ( work->think1 ) {
	    case TH1_PHASE0 :		/* トイレから出る */
			Think1_Phase0_800CE874( work ) ;
		break ;
	    case TH1_PHASE1 :		/* スネークが準備するまで待つ */
			Think1_Phase1_800CE8A4( work ) ;
		break ;
	    case TH1_PHASE2 :		/* スネークについていく */
			Think1_Phase2_800CE8F4( work ) ;
		break ;
	    case TH1_PHASE3 :		/* 所.. */
            Think1_Phase3_800CE970( work ) ;
        break ;
    }

    for ( i = 0 ; i < 3 ; i++ )
    {
        if ( --work->fC10[i] < 0 )
        {
            work->fC10[i] = 0 ;
        }
    }
}
