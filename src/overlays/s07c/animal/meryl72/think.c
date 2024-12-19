#include "meryl72.h"

#define TH1_PHASE0 0
#define TH1_PHASE1 1
#define TH1_PHASE2 2
#define TH1_PHASE3 3


void s07c_meryl72_unk2_800CC9A8(Meryl72Work *work)
{
    work->target_addr = work->player_addr;
    work->target_pos  = work->player_pos;
    work->target_map  = work->player_map;
}

void s07c_meryl72_unk2_800CC9E0(Meryl72Work *work)
{
    int x;

    x = work->next_node + 1;
    if ( x >= work->n_patrols )
    {
        x = 0;
    }
    work->next_node   = x;
    work->target_pos  = work->nodes[ x ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map  = work->start_map;
}

void s07c_meryl72_unk2_800CCA68(Meryl72Work *work)
{
    work->target_pos  = work->nodes[ work->next_node ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map  = work->start_map;
}

void s07c_meryl72_unk2_800CCAD8( Meryl72Work* work )
{
    work->target_pos.vx = -5500;
    work->target_pos.vz = -18000;
    work->target_pos.vy =  0;
    work->target_addr   = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map    = work->start_map;
}

void s07c_meryl72_unk2_800CCB2C( Meryl72Work *work, int index )
{
    int proc_id;

    proc_id = work->fC1C[ index ];
    if ( proc_id >= 0 )
    {
        GCL_ExecProc( proc_id, NULL );
    }
}

int s07c_meryl72_unk2_800CCB64( Meryl72Work *work )
{
    SVECTOR  diff;
    SVECTOR *mov;
    HZD_HDL *hzd;
    int      to_addr, from_addr;
    int      reach;
    int      link;
    HZD_ZON *zone;

    mov = &work->control.mov;
    hzd = work->control.map->hzd;

    to_addr = work->target_addr;
    from_addr = HZD_GetAddress( hzd, mov, work->fB5C );

    work->fB5C = from_addr;
    reach = HZD_ReachTo( hzd, from_addr, work->fB60 );

    if ( to_addr != work->fB4C || reach <= 0 )
    {
        work->fB4C = to_addr;

        if ( HZD_ReachTo( hzd, from_addr, to_addr ) < 2 )
        {
            work->fB6C = work->target_pos;
            work->fB60 = to_addr;
            GV_SubVec3(&work->fB6C, mov, &diff);
            work->pad.dir = GV_VecDir2(&diff);
            return -1;
        }

        link = HZD_LinkRoute( hzd, from_addr, to_addr, mov );
        zone = &hzd->header->zones[ link ];

        work->fB6C.vx = zone->x;
        work->fB6C.vy = zone->y;
        work->fB6C.vz = zone->z;

        work->fB60 = ( link & 0xff ) | ( ( link & 0xff ) << 8 );
    }

    GV_SubVec3( &work->fB6C, &work->control.mov, &diff );
    return GV_VecDir2( &diff );
}

int s07c_meryl72_unk2_800CCCC8( Meryl72Work *work )
{
    if ( ( work->count3 % 32 ) == 0 )
    {
        work->fB5C = -1;
        work->fB4C = -1;
        s07c_meryl72_unk2_800CCB64( work );
    }

    work->pad.dir = s07c_meryl72_unk2_800CCB64( work );
    return work->pad.dir < 0;
}

int s07c_meryl72_unk2_800CCD1C(Meryl72Work *work, int range)
{
    SVECTOR diff;
    int     dx, dz;

    diff.vx = dx = work->target_pos.vx - work->control.mov.vx;
    diff.vz = dz = work->target_pos.vz - work->control.mov.vz;

    if (dx > -range && dx < range && dz > -range && dz < range)
    {
        return 1;
    }

    work->pad.dir = GV_VecDir2(&diff);
    return 0;
}

void s07c_meryl72_unk2_800CCD98( Meryl72Work *work )
{
    if ( !work->fB96 )
    {
        if ( work->count3 == 0 )
        {
            s07c_meryl72_unk2_800CCB2C( work, 1 ) ;
            GM_GameStatus |= PLAYER_CAN_USE_CONTROLLER_PORT_2;
        }
        
        if ( work->count3 == 1 )
        {
            work->pad.dir = work->sn_dir;
            GM_GameStatus |= ( PLAYER_CAN_USE_CONTROLLER_PORT_2 | PLAYER_PREVENT_WEAPON_SWITCH | PLAYER_THROWING | PLAYER_KNOCKING | PLAYER_GAMEOVER ) ;
        }
        
        if ( work->count3 == 60 )
        {
            GM_VoxStream_80037E40( work->voices[ 0 ], 0 ) ;
        }
        
        if ( work->count3 > 60 && GM_StreamStatus_80037CD8() == -1 )
        {
            s07c_meryl72_unk2_800CCB2C( work, 0 );
            s07c_meryl72_unk2_800CCB2C( work, 4 );
            work->think3 = 1;
            work->count3 = 0;
            return;
        }
    }
    else
    {
        work->next_node = 2;
        s07c_meryl72_unk2_800CC9E0( work );
        work->think1 = 1;
        work->think2 = 2;
        work->think3 = 4;
        work->count3 = 0;
        return;
    }    
    work->count3++;
}

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
