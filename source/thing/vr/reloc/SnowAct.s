	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	SnowAct
SnowAct:
	lui	$2,%hi(GM_lpsvectWind)
	lw	$2,%lo(GM_lpsvectWind)($2)
	addiu	$29,$29,-40
	sw	$19,28($29)
	addu	$19,$4,$0
	sw	$31,32($29)
	sw	$18,24($29)
	sw	$17,20($29)
	bne	$2,$0,$LSnowAct_0
	sw	$16,16($29)
	j	$LSnowAct_1
	sw	$0,9544($19)
$LSnowAct_0:
	lw	$2,9544($19)
	addiu	$3,$0,1
	beq	$2,$3,$LSnowAct_1
	nop
	sw	$3,9544($19)
$LSnowAct_1:
	lw	$18,64($19)
	nop
	blez	$18,$LSnowAct_7
	addiu	$16,$19,72
	addiu	$17,$19,104
$LSnowAct_2:
	lw	$2,9556($19)
	nop
	bne	$2,$0,$LSnowAct_3
	addu	$4,$19,$0
	lw	$3,0($17)
	addiu	$17,$17,292
	lw	$2,36($3)
	addiu	$16,$16,292
	ori	$2,$2,0x100
	j	$LSnowAct_6
	sw	$2,36($3)
$LSnowAct_3:
	lw	$2,0($17)
	addu	$5,$16,$0
	lw	$3,36($2)
	addiu	$6,$0,-257
	and	$3,$3,$6
	jal	Snow_800C59C8
	sw	$3,36($2)
	bne	$2,$0,$LSnowAct_4
	addu	$4,$16,$0
	addiu	$5,$16,8
	jal	GV_AddVec3
	addu	$6,$16,$0
	addiu	$4,$16,16
	addiu	$5,$16,24
	jal	GV_AddVec3
	addu	$6,$4,$0
	addu	$4,$16,$0
$LSnowAct_4:
	jal	DG_SetPos2
	addiu	$5,$16,16
	lw	$2,9548($19)
	nop
	beq	$2,$0,$LSnowAct_5
	addiu	$5,$0,32
	lui	$2,%hi(GV_Clock)
	lw	$2,%lo(GV_Clock)($2)
	lw	$3,0($17)
	sll	$2,$2,2
	addu	$3,$3,$2
	lw	$4,64($3)
	jal	Snow_800C5234
	addiu	$6,$19,9416
$LSnowAct_5:
	lw	$4,0($17)
	addiu	$17,$17,292
	jal	DG_PutPrim
	addiu	$16,$16,292
$LSnowAct_6:
	addiu	$18,$18,-1
	bgtz	$18,$LSnowAct_2
	nop
$LSnowAct_7:
	lw	$31,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
