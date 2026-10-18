	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C4298
njp_800C4298:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	bne	$5,$0,$Lnjp_800C4298_2
	sw	$17,20($29)
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x1
	bne	$2,$0,$Lnjp_800C4298_1
	addu	$4,$16,$0
	addiu	$17,$0,7
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x100
	beq	$2,$0,$Lnjp_800C4298_0
	addiu	$4,$16,32
	addiu	$17,$0,183
$Lnjp_800C4298_0:
	jal	GM_SeSet
	addu	$5,$17,$0
	lui	$2,%hi(njp_dword_800ABBD0)
	lhu	$2,%lo(njp_dword_800ABBD0)($2)
	lui	$4,0x1
	addiu	$2,$2,-2048
	jal	njp_GM_SetPlayerStatusFlag
	sh	$2,110($16)
	addu	$4,$16,$0
$Lnjp_800C4298_1:
	addiu	$5,$0,21
	addiu	$2,$0,300
	sh	$2,2436($16)
	lui	$2,%hi(njp_800C4750)
	addiu	$2,$2,%lo(njp_800C4750)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6994)
	addiu	$2,$2,%lo(njp_800C6994)
	addiu	$6,$0,4
	sh	$0,2434($16)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($16)
$Lnjp_800C4298_2:
	lw	$2,76($16)
	nop
	lw	$4,8($2)
	jal	GM_CheckBehindCamera
	addiu	$5,$16,32
	lh	$2,2454($16)
	nop
	slti	$2,$2,8
	beq	$2,$0,$Lnjp_800C4298_5
	lui	$2,%hi(njp_pVec_800ABBCC)
	lw	$4,%lo(njp_pVec_800ABBCC)($2)
	nop
	beq	$4,$0,$Lnjp_800C4298_5
	nop
	lh	$3,0($4)
	nop
	bgez	$3,$Lnjp_800C4298_3
	nop
	addiu	$3,$3,7
$Lnjp_800C4298_3:
	lhu	$2,100($16)
	sra	$3,$3,3
	addu	$2,$2,$3
	sh	$2,100($16)
	lh	$2,4($4)
	nop
	bgez	$2,$Lnjp_800C4298_4
	nop
	addiu	$2,$2,7
$Lnjp_800C4298_4:
	sra	$2,$2,3
	lhu	$3,104($16)
	lhu	$4,2454($16)
	addu	$3,$3,$2
	addiu	$4,$4,1
	sh	$3,104($16)
	sh	$4,2454($16)
$Lnjp_800C4298_5:
	lw	$31,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.text
