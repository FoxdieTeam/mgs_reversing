	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C6900
njp_800C6900:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addiu	$5,$0,2
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x10
	bne	$2,$0,$Lnjp_800C6900_0
	nop
	jal	njp_sna_8004EC00
	addu	$4,$16,$0
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
	j	$Lnjp_800C6900_1
	nop
$Lnjp_800C6900_0:
	jal	njp_sna_80051BA4
	addu	$4,$16,$0
	bne	$2,$0,$Lnjp_800C6900_1
	nop
	jal	njp_800C65D4
	addu	$4,$16,$0
	jal	njp_sna_80051FD0
	addu	$4,$16,$0
$Lnjp_800C6900_1:
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
	.globl	njp_800C6994
njp_800C6994:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,28($29)
	sw	$18,24($29)
	sw	$17,20($29)
	lw	$2,2320($16)
	nop
	lhu	$17,0($2)
	lhu	$18,2($2)
	andi	$3,$17,0x10
	bne	$3,$0,$Lnjp_800C6994_0
	nop
	jal	njp_sna_8004EC00
	nop
	addiu	$2,$0,2
	j	$Lnjp_800C6994_4
	sh	$2,2452($16)
$Lnjp_800C6994_0:
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,16
	beq	$2,$0,$Lnjp_800C6994_1
	andi	$2,$18,0xf000
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addiu	$5,$0,21
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	andi	$2,$18,0xf000
$Lnjp_800C6994_1:
	bne	$2,$0,$Lnjp_800C6994_2
	andi	$2,$17,0xf000
	bne	$2,$0,$Lnjp_800C6994_3
	nop
$Lnjp_800C6994_2:
	jal	njp_GM_ClearPlayerStatusFlag
	lui	$4,0x1
	addiu	$2,$0,450
	sh	$2,2436($16)
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
	jal	GM_ExitBehindCamera
	nop
$Lnjp_800C6994_3:
	jal	njp_sna_80051BA4
	addu	$4,$16,$0
$Lnjp_800C6994_4:
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
	.globl	njp_800C6A60
njp_800C6A60:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x10
	bne	$2,$0,$Lnjp_800C6A60_0
	lui	$3,%hi(GM_SnakeCamera)
	jal	njp_sna_8004EC00
	nop
	lui	$3,%hi(GM_SnakeCamera)
$Lnjp_800C6A60_0:
	addiu	$3,$3,%lo(GM_SnakeCamera)
	lhu	$2,2($3)
	addu	$4,$16,$0
	addiu	$2,$2,320
	jal	njp_sna_8004EE28
	sh	$2,2($3)
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.text
