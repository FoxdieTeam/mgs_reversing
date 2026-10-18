	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C4750
njp_800C4750:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lh	$2,2452($16)
	lhu	$3,2452($16)
	beq	$2,$0,$Lnjp_800C4750_0
	addiu	$2,$3,-1
	sh	$2,2452($16)
$Lnjp_800C4750_0:
	jal	njp_sub_800507D8
	addu	$4,$16,$0
	bne	$2,$0,$Lnjp_800C4750_3
	lui	$4,%hi(njp_dword_800ABBC4)
	lw	$3,%lo(njp_dword_800ABBC4)($4)
	addiu	$2,$0,2
	beq	$3,$2,$Lnjp_800C4750_1
	addiu	$2,$0,4
	bne	$3,$2,$Lnjp_800C4750_2
	nop
$Lnjp_800C4750_1:
	lhu	$2,%lo(njp_dword_800ABBC4)($4)
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_wall_move_80052BA8)
	addiu	$5,$5,%lo(njp_sna_anim_wall_move_80052BA8)
	jal	njp_sna_start_anim_8004E1F4
	sh	$2,2480($16)
$Lnjp_800C4750_2:
	lui	$4,%hi(njp_dword_800ABBD0)
	lw	$2,%lo(njp_dword_800ABBD0)($4)
	lh	$3,42($16)
	addiu	$2,$2,-2048
	beq	$2,$3,$Lnjp_800C4750_3
	nop
	lhu	$2,%lo(njp_dword_800ABBD0)($4)
	sh	$0,2454($16)
	addiu	$2,$2,-2048
	sh	$2,110($16)
$Lnjp_800C4750_3:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C47EC
njp_800C47EC:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lh	$2,2452($16)
	lhu	$3,2452($16)
	beq	$2,$0,$Lnjp_800C47EC_0
	addiu	$2,$3,-1
	sh	$2,2452($16)
$Lnjp_800C47EC_0:
	jal	njp_sub_800507D8
	addu	$4,$16,$0
	bne	$2,$0,$Lnjp_800C47EC_5
	nop
	lw	$2,76($16)
	nop
	lw	$4,8($2)
	jal	GM_CheckBehindCamera
	addiu	$5,$16,32
	lui	$2,%hi(njp_dword_800ABBC4)
	lw	$3,%lo(njp_dword_800ABBC4)($2)
	addiu	$2,$0,1
	bne	$3,$2,$Lnjp_800C47EC_1
	lui	$5,%hi(njp_dword_800ABBD0)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_wall_crouch_80052CCC)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_wall_crouch_80052CCC)
	j	$Lnjp_800C47EC_5
	nop
$Lnjp_800C47EC_1:
	lw	$2,%lo(njp_dword_800ABBD0)($5)
	lh	$3,42($16)
	addiu	$2,$2,-2048
	bne	$2,$3,$Lnjp_800C47EC_2
	lui	$2,%hi(njp_bss_48)
	lui	$3,%hi(njp_pVec_800ABBCC)
	lw	$4,%lo(njp_bss_48)($2)
	lw	$2,%lo(njp_pVec_800ABBCC)($3)
	nop
	beq	$4,$2,$Lnjp_800C47EC_3
	lui	$2,%hi(njp_dword_800ABBC4)
$Lnjp_800C47EC_2:
	lhu	$2,%lo(njp_dword_800ABBD0)($5)
	sh	$0,2454($16)
	addiu	$2,$2,-2048
	sh	$2,110($16)
	lui	$2,%hi(njp_dword_800ABBC4)
$Lnjp_800C47EC_3:
	lw	$3,%lo(njp_dword_800ABBC4)($2)
	addiu	$2,$0,2
	bne	$3,$2,$Lnjp_800C47EC_4
	addiu	$17,$0,23
	addiu	$17,$0,22
$Lnjp_800C47EC_4:
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addu	$5,$17,$0
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
$Lnjp_800C47EC_5:
	lw	$31,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.text
