#include "linker.h"
#include "bullet.h"

extern const char   aBulletC[];

extern SVECTOR svec_8009F6AC[4];

//------------------------------------------------------------------------------

void bullet_80075314(SVECTOR *pVec, short amount)
{
    svec_8009F6AC[0].vx = amount;
    svec_8009F6AC[1].vx = -amount;
    svec_8009F6AC[2].vz = amount;
    svec_8009F6AC[3].vz = -amount;
    DG_PutVector_8001BE48(svec_8009F6AC, pVec, 4);
}

#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_helper_80075358.s") // 188 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_helper_80075414.s")     // 208 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_helper_800754E4.s")     // 300 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_helper_80075610.s") // 332 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader3_8007575C.s")        // 1656 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_80075DD4.s")            // 912 bytes
void                             bullet_act_80075DD4(Actor_Bullet *actor);

void bullet_kill_80076164(int param_1)
{
    DG_PRIM *prim;

    prim = *(DG_PRIM **)(param_1 + 0x8c);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}

extern int SECTION(".data") aDdd_8009F6EC[]; // TODO: define as SVECTOR*

int        bullet_SetTarget_800761A0( Actor_Bullet *actor, int target_flags )
{
    SVECTOR pos;

    GM_SetTarget_8002DC74( &actor->f044_target, 4, target_flags, (SVECTOR *)aDdd_8009F6EC );

    pos.vx = actor->f120_target_pos.vx >> 3; // divide 8 won't match
    pos.vy = actor->f120_target_pos.vy >> 3;
    pos.vz = actor->f120_target_pos.vz >> 3;

    if ( actor->f14C_flags & 0x800 )
    {
        GM_Target_8002DCCC( &actor->f044_target, 0, 2, actor->f154_unk, 0, &pos );
    }
    else
    {
        GM_Target_8002DCCC( &actor->f044_target, 0, 1, actor->f154_unk, 0, &pos );
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_80076274.s") // 428 bytes
int                              bullet_loader2_80076274(Actor_Bullet *actor, MATRIX *param_2, int param_3, int param_4, int param_5);
//#pragma INCLUDE_ASM("asm/Okajima/NewBulletEnemy_80076420.s") // 356 bytes

Actor_Bullet *NewBulletEnemy_80076420(MATRIX *arg0, int arg1, int arg2, int arg3, int arg4)
{
	Actor_Bullet  *actor;
	SVECTOR       vec;

	actor = (Actor_Bullet *)GV_NewActor_800150E4( 5, sizeof(Actor_Bullet) );
	if ( actor != NULL )
	{
		GV_SetNamedActor_8001514C( (GV_ACT *)actor,
								   (TActorFunction)&bullet_act_80075DD4,
								   (TActorFunction)&bullet_kill_80076164,
								   (char *)aBulletC );
		vec.vx = arg0->m[0][0];
		vec.vy = arg0->m[1][0];
		vec.vz = arg0->m[2][0];
		actor->f160_vec_len = GV_VecLen3_80016D80( &vec );
		actor->f150_unk = 10;
		actor->f154_unk = 64;
		if ( arg3 == 2 )
		{
			actor->f158_unk = 100000;
			actor->f15C_unk = 5000;
		}
		else if ( arg3 == 1 )
		{
			actor->f158_unk = 10000;
			actor->f15C_unk = 5000;
		}
		else
		{
			actor->f158_unk = 10000;
			actor->f15C_unk = 750;
		}
		actor->f168_unk = arg4;
		if ( bullet_loader2_80076274( actor, arg0, arg2, arg3, arg1 ) < 0 )
		{
			GV_DestroyActor_800151C8( (GV_ACT *)actor );
			return NULL;
		}
		if ( bullet_SetTarget_800761A0( actor, arg1 ) < 0 )
		{
			GV_DestroyActor_800151C8( (GV_ACT *)actor );
		}
		actor->f14C_flags = 0x100;
		actor->f144_unk = arg3;
		actor->f134_unk = arg2;
		actor->f148_unk = arg1;
	}
	return actor;
}

#pragma INCLUDE_ASM("asm/Okajima/bullet_init_80076584.s")    // 388 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewBulletEx_80076708.s")    // 548 bytes
#pragma INCLUDE_ASM("asm/Okajima/sub_8007692C.s")            // 192 bytes
