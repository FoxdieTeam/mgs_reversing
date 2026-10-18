	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C5BA4
vcd_n05_800C5BA4:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$18,24($29)
	addu	$18,$5,$0
	addiu	$6,$0,159
	addu	$5,$0,$0
	addiu	$4,$17,2304
	sw	$31,28($29)
	sw	$16,16($29)
$Lvcd_n05_800C5BA4_0:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$5,$5,1
	or	$3,$3,$6
	sh	$3,0($2)
	slti	$2,$5,5
	bne	$2,$0,$Lvcd_n05_800C5BA4_0
	addiu	$4,$4,4
	lui	$2,%hi(GODZ_EYE_LENGTH)
	lhu	$2,%lo(GODZ_EYE_LENGTH)($2)
	bne	$18,$0,$Lvcd_n05_800C5BA4_1
	sh	$2,2972($17)
	addiu	$4,$17,156
	addiu	$2,$0,5
	sh	$2,2272($17)
	lui	$2,%hi(godzact_data+10)
	addu	$6,$0,$0
	lh	$5,%lo(godzact_data+10)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	lhu	$2,2904($17)
	nop
	sh	$2,110($17)
$Lvcd_n05_800C5BA4_1:
	jal	GodzCheckDamage
	addu	$4,$17,$0
	bne	$2,$0,$Lvcd_n05_800C5BA4_8
	slti	$2,$18,16
	bne	$2,$0,$Lvcd_n05_800C5BA4_8
	slti	$2,$18,31
	bne	$2,$0,$Lvcd_n05_800C5BA4_3
	addiu	$16,$17,40
	slti	$2,$18,61
	beq	$2,$0,$Lvcd_n05_800C5BA4_2
	nop
	lhu	$2,2($16)
	j	$Lvcd_n05_800C5BA4_4
	addiu	$2,$2,32
$Lvcd_n05_800C5BA4_2:
	slti	$2,$18,76
	beq	$2,$0,$Lvcd_n05_800C5BA4_5
	andi	$2,$18,0x1
$Lvcd_n05_800C5BA4_3:
	lhu	$2,2($16)
	nop
	addiu	$2,$2,-32
$Lvcd_n05_800C5BA4_4:
	andi	$2,$2,0xfff
	sh	$2,2($16)
	andi	$2,$18,0x1
$Lvcd_n05_800C5BA4_5:
	bne	$2,$0,$Lvcd_n05_800C5BA4_6
	slti	$2,$18,77
	addiu	$4,$17,32
	jal	GM_SeSet
	addiu	$5,$0,46
	addu	$4,$17,$0
	jal	GODZ_SetPutChar
	addiu	$5,$0,3
	slti	$2,$18,77
$Lvcd_n05_800C5BA4_6:
	bne	$2,$0,$Lvcd_n05_800C5BA4_7
	addiu	$4,$17,156
	addu	$5,$0,$0
	lui	$2,%hi(GodzAct_800C590C)
	addiu	$2,$2,%lo(GodzAct_800C590C)
	sw	$2,2284($17)
	sw	$0,2292($17)
	sh	$0,112($17)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($17)
$Lvcd_n05_800C5BA4_7:
	lhu	$2,2($16)
	nop
	sh	$2,110($17)
$Lvcd_n05_800C5BA4_8:
	lw	$31,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.text
