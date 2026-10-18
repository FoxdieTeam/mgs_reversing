	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C33C8
njp_800C33C8:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$4,$0,1
	sw	$31,28($29)
	sw	$18,24($29)
	jal	njp_GM_CheckPlayerStatusFlag
	sw	$17,20($29)
	bne	$2,$0,$Lnjp_800C33C8_6
	nop
	lw	$2,2320($16)
	nop
	lhu	$2,2($2)
	nop
	andi	$2,$2,0x4
	beq	$2,$0,$Lnjp_800C33C8_0
	addiu	$2,$0,10
	sw	$2,2312($16)
$Lnjp_800C33C8_0:
	lw	$2,2308($16)
	nop
	beq	$2,$0,$Lnjp_800C33C8_3
	nop
	lw	$3,2200($16)
	nop
	lhu	$2,38($3)
	nop
	addiu	$2,$2,-1
	sh	$2,38($3)
	lw	$2,2200($16)
	nop
	lhu	$2,38($2)
	nop
	andi	$2,$2,0x3f
	bne	$2,$0,$Lnjp_800C33C8_1
	lui	$2,%hi(GM_GameStatus)
	lw	$3,%lo(GM_GameStatus)($2)
	lui	$4,0x200
	or	$3,$3,$4
	sw	$3,%lo(GM_GameStatus)($2)
$Lnjp_800C33C8_1:
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C33C8_2
	nop
	lui	$17,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($17)
	nop
	bne	$2,$0,$Lnjp_800C33C8_2
	nop
	jal	njp_sub_8004F454
	addu	$4,$16,$0
	addu	$4,$16,$0
	jal	njp_sna_set_invuln_8004F2A0
	addu	$5,$0,$0
	addu	$4,$16,$0
	lui	$5,0x8
	addiu	$2,$0,-1
	jal	njp_sna_set_flags1_8004E2F4
	sw	$2,%lo(GM_GameOverTimer)($17)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4E38)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4E38)
	addiu	$2,$0,3
	sw	$2,2528($16)
	addiu	$2,$0,10
	sw	$2,2312($16)
$Lnjp_800C33C8_2:
	lw	$2,2308($16)
	nop
	beq	$2,$0,$Lnjp_800C33C8_3
	lui	$2,%hi(linkvarbuf+30)
	lh	$3,%lo(linkvarbuf+30)($2)
	addiu	$2,$0,-1
	bne	$3,$2,$Lnjp_800C33C8_3
	addiu	$2,$0,10
	sw	$2,2312($16)
$Lnjp_800C33C8_3:
	lw	$17,2312($16)
	addiu	$2,$0,10
	bne	$17,$2,$Lnjp_800C33C8_6
	nop
	lw	$4,2308($16)
	nop
	bne	$4,$0,$Lnjp_800C33C8_4
	addiu	$18,$16,32
	addu	$4,$18,$0
	addiu	$5,$16,156
	jal	NewKogaku2
	addiu	$6,$0,6
	beq	$2,$0,$Lnjp_800C33C8_6
	sw	$2,2308($16)
	addu	$4,$18,$0
	addiu	$5,$0,78
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$3,%hi(dword_800ABA1C)
	addiu	$2,$0,1
	sw	$2,%lo(dword_800ABA1C)($3)
	lui	$2,%hi(linkvarbuf+30)
	sh	$17,%lo(linkvarbuf+30)($2)
	lui	$2,%hi(snainit_item_800A9420)
	j	$Lnjp_800C33C8_5
	sw	$17,%lo(snainit_item_800A9420)($2)
$Lnjp_800C33C8_4:
	jal	GV_DestroyActorQuick
	nop
	addiu	$4,$16,32
	addiu	$5,$0,78
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$2,%hi(dword_800ABA1C)
	lui	$3,%hi(linkvarbuf+30)
	sw	$0,%lo(dword_800ABA1C)($2)
	addiu	$2,$0,-1
	sw	$0,2308($16)
	sh	$2,%lo(linkvarbuf+30)($3)
	lui	$3,%hi(snainit_item_800A9420)
	addiu	$2,$0,-1
	sw	$2,%lo(snainit_item_800A9420)($3)
$Lnjp_800C33C8_5:
	sw	$0,2312($16)
$Lnjp_800C33C8_6:
	lw	$31,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C35BC
njp_800C35BC:
	addiu	$29,$29,-72
	sw	$18,64($29)
	addu	$18,$4,$0
	addu	$2,$5,$0
	sw	$17,60($29)
	addu	$17,$6,$0
	sw	$31,68($29)
	bltz	$2,$Lnjp_800C35BC_0
	sw	$16,56($29)
	addiu	$16,$29,48
	addu	$4,$16,$0
	addiu	$5,$29,16
	sh	$0,52($29)
	sh	$0,48($29)
	jal	RotMatrixYXZ
	sh	$2,50($29)
	addiu	$4,$29,16
	addu	$5,$16,$0
	addu	$6,$16,$0
	sh	$0,50($29)
	sh	$0,48($29)
	jal	ApplyMatrixSV
	sh	$17,52($29)
	addiu	$4,$18,100
	addu	$5,$16,$0
	jal	GV_AddVec3
	addu	$6,$4,$0
$Lnjp_800C35BC_0:
	lw	$31,68($29)
	lw	$18,64($29)
	lw	$17,60($29)
	lw	$16,56($29)
	jr	$31
	addiu	$29,$29,72
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3640
njp_800C3640:
	addiu	$29,$29,-24
	sw	$31,16($29)
	addiu	$2,$0,13
	beq	$5,$2,$Lnjp_800C3640_3
	addu	$3,$0,$0
	slti	$2,$5,14
	beq	$2,$0,$Lnjp_800C3640_0
	addiu	$2,$0,5
	beq	$5,$2,$Lnjp_800C3640_1
	nop
	j	$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_0:
	addiu	$2,$0,14
	beq	$5,$2,$Lnjp_800C3640_4
	addiu	$2,$0,3
	j	$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_1:
	bne	$6,$0,$Lnjp_800C3640_2
	addiu	$2,$0,10
	j	$Lnjp_800C3640_6
	addiu	$3,$0,168
$Lnjp_800C3640_2:
	bne	$6,$2,$Lnjp_800C3640_6
	nop
	j	$Lnjp_800C3640_6
	addiu	$3,$0,169
$Lnjp_800C3640_3:
	addiu	$2,$0,3
	bne	$6,$2,$Lnjp_800C3640_6
	nop
	j	$Lnjp_800C3640_6
	addiu	$3,$0,205
$Lnjp_800C3640_4:
	beq	$6,$2,$Lnjp_800C3640_5
	nop
	bne	$6,$5,$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_5:
	addiu	$3,$0,205
$Lnjp_800C3640_6:
	beq	$3,$0,$Lnjp_800C3640_7
	addu	$5,$3,$0
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C3640_7:
	lw	$31,16($29)
	nop
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C36EC
njp_800C36EC:
	addiu	$29,$29,-24
	sw	$31,16($29)
	addiu	$2,$0,26
	bne	$5,$2,$Lnjp_800C36EC_1
	addu	$3,$0,$0
	addiu	$2,$0,3
	beq	$6,$2,$Lnjp_800C36EC_0
	addiu	$2,$0,14
	bne	$6,$2,$Lnjp_800C36EC_1
	nop
$Lnjp_800C36EC_0:
	addiu	$3,$0,205
$Lnjp_800C36EC_1:
	beq	$3,$0,$Lnjp_800C36EC_2
	addu	$5,$3,$0
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C36EC_2:
	lw	$31,16($29)
	nop
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.text
