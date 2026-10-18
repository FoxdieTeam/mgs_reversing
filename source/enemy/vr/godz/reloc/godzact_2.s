	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	GodzAct_800C6814
GodzAct_800C6814:
	addiu	$29,$29,-40
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$18,24($29)
	addu	$18,$5,$0
	sw	$19,28($29)
	addiu	$19,$16,2248
	sw	$31,32($29)
	sw	$17,20($29)
	lw	$2,2940($16)
	lw	$3,2304($16)
	sh	$0,2278($16)
	ori	$2,$2,0x8
	sw	$2,2940($16)
	lwl	$8,47($3)
	lwr	$8,44($3)
	lwl	$9,51($3)
	lwr	$9,48($3)
	swl	$8,103($16)
	swr	$8,100($16)
	swl	$9,107($16)
	swr	$9,104($16)
	bne	$18,$0,$LGodzAct_800C6814_14
	addiu	$17,$16,32
	lw	$3,20($19)
	nop
	sltiu	$2,$3,6
	beq	$2,$0,$LGodzAct_800C6814_32
	lui	$2,%hi(GodzAct_800C6814_jtbl_800DE720)
	addiu	$2,$2,%lo(GodzAct_800C6814_jtbl_800DE720)
	sll	$3,$3,2
	addu	$3,$3,$2
	lw	$2,0($3)
	nop
	jr	$2
	nop
$LGodzAct_800C6814_0:
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,52
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,34
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+68)
	lh	$5,%lo(GodzActTable+68)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,139
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	GODZ_PutBlood
	addu	$6,$0,$0
	j	$LGodzAct_800C6814_13
	addiu	$2,$0,17
$LGodzAct_800C6814_1:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,37
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+74)
	lh	$5,%lo(GodzActTable+74)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	lw	$2,2304($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$LGodzAct_800C6814_3
	addu	$4,$16,$0
	lui	$2,%hi(linkvarbuf+28)
	lh	$3,%lo(linkvarbuf+28)($2)
	addiu	$2,$0,9
	bne	$3,$2,$LGodzAct_800C6814_2
	addiu	$5,$0,6
	addu	$4,$16,$0
	j	$LGodzAct_800C6814_4
	addiu	$6,$0,2
$LGodzAct_800C6814_2:
	j	$LGodzAct_800C6814_4
	addiu	$6,$0,1
$LGodzAct_800C6814_3:
	addiu	$5,$0,5
	addu	$6,$0,$0
$LGodzAct_800C6814_4:
	jal	GODZ_PutBlood
	nop
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$LGodzAct_800C6814_5
	addiu	$4,$16,32
	lui	$2,%hi(GodzCommand+12)
	lw	$3,%lo(GodzCommand+12)($2)
	addiu	$2,$0,1
	bne	$3,$2,$LGodzAct_800C6814_6
	addiu	$5,$0,139
$LGodzAct_800C6814_5:
	addiu	$5,$0,132
$LGodzAct_800C6814_6:
	jal	GM_SeSetMode
	addiu	$6,$0,1
	j	$LGodzAct_800C6814_13
	addiu	$2,$0,100
$LGodzAct_800C6814_7:
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$LGodzAct_800C6814_8
	addiu	$4,$16,32
	lui	$2,%hi(GodzCommand+12)
	lw	$3,%lo(GodzCommand+12)($2)
	addiu	$2,$0,1
	bne	$3,$2,$LGodzAct_800C6814_9
	addiu	$5,$0,139
$LGodzAct_800C6814_8:
	addiu	$5,$0,132
$LGodzAct_800C6814_9:
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,35
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+70)
	lh	$5,%lo(GodzActTable+70)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	GODZ_PutBlood
	addu	$6,$0,$0
	j	$LGodzAct_800C6814_13
	addiu	$2,$0,36
$LGodzAct_800C6814_10:
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,142
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,36
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+72)
	lh	$5,%lo(GodzActTable+72)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	GODZ_PutBlood
	addu	$6,$0,$0
	j	$LGodzAct_800C6814_13
	addiu	$2,$0,37
$LGodzAct_800C6814_11:
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,144
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,29
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+58)
	lh	$5,%lo(GodzActTable+58)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	j	$LGodzAct_800C6814_13
	addiu	$2,$0,67
$LGodzAct_800C6814_12:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,30
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+60)
	lh	$5,%lo(GodzActTable+60)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$2,$0,15
$LGodzAct_800C6814_13:
	sh	$2,2922($16)
$LGodzAct_800C6814_14:
	lw	$3,20($19)
	nop
	sltiu	$2,$3,6
	beq	$2,$0,$LGodzAct_800C6814_32
	lui	$2,%hi(GodzAct_800C6814_jtbl_800DE720+24)
	addiu	$2,$2,%lo(GodzAct_800C6814_jtbl_800DE720+24)
	sll	$3,$3,2
	addu	$3,$3,$2
	lw	$2,0($3)
	nop
	jr	$2
	nop
$LGodzAct_800C6814_15:
	slti	$2,$18,12
	beq	$2,$0,$LGodzAct_800C6814_16
	addiu	$2,$18,-7
	lhu	$2,78($17)
	nop
	addiu	$2,$2,170
	sh	$2,78($17)
	addiu	$2,$18,-7
$LGodzAct_800C6814_16:
	sltiu	$2,$2,23
	beq	$2,$0,$LGodzAct_800C6814_17
	slti	$2,$18,20
	jal	GodzAttackTouch
	addu	$4,$16,$0
	slti	$2,$18,20
$LGodzAct_800C6814_17:
	beq	$2,$0,$LGodzAct_800C6814_32
	addiu	$2,$0,-32767
	j	$LGodzAct_800C6814_32
	sh	$2,84($16)
$LGodzAct_800C6814_18:
	addiu	$2,$0,58
	bne	$18,$2,$LGodzAct_800C6814_21
	slti	$2,$18,15
	addiu	$4,$16,32
	addiu	$5,$0,199
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$4,%hi(godz_act_data_133C)
	addiu	$4,$4,%lo(godz_act_data_133C)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(godz_act_data_1350)
	addiu	$4,$4,%lo(godz_act_data_1350)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$LGodzAct_800C6814_20
	addiu	$5,$0,8
	bne	$3,$4,$LGodzAct_800C6814_19
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$LGodzAct_800C6814_21
	slti	$2,$18,15
	lui	$2,%hi(GM_NoiseLength)
$LGodzAct_800C6814_19:
	sw	$5,%lo(GM_NoiseLength)($2)
	lui	$2,%hi(GM_NoisePosition)
	sw	$4,%lo(GM_NoisePower)($6)
	addiu	$11,$2,%lo(GM_NoisePosition)
	lwl	$8,35($16)
	lwr	$8,32($16)
	lwl	$9,39($16)
	lwr	$9,36($16)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
$LGodzAct_800C6814_20:
	slti	$2,$18,15
$LGodzAct_800C6814_21:
	beq	$2,$0,$LGodzAct_800C6814_33
	slti	$2,$18,17
	lhu	$2,72($17)
	nop
	addiu	$2,$2,-30
	j	$LGodzAct_800C6814_32
	sh	$2,72($17)
$LGodzAct_800C6814_22:
	addiu	$2,$18,-7
	sltiu	$2,$2,23
	beq	$2,$0,$LGodzAct_800C6814_23
	slti	$2,$18,15
	jal	GodzAttackTouch
	addu	$4,$16,$0
	slti	$2,$18,15
$LGodzAct_800C6814_23:
	beq	$2,$0,$LGodzAct_800C6814_24
	addiu	$3,$0,-32767
	lhu	$2,72($17)
	sh	$3,52($17)
	addiu	$2,$2,-30
	sh	$2,72($17)
$LGodzAct_800C6814_24:
	addiu	$2,$0,84
	bne	$18,$2,$LGodzAct_800C6814_27
	addiu	$2,$0,89
	addiu	$4,$16,32
	addiu	$5,$0,199
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$4,%hi(godz_act_data_133C)
	addiu	$4,$4,%lo(godz_act_data_133C)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(godz_act_data_1350)
	addiu	$4,$4,%lo(godz_act_data_1350)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$LGodzAct_800C6814_26
	addiu	$5,$0,8
	bne	$3,$4,$LGodzAct_800C6814_25
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$LGodzAct_800C6814_27
	addiu	$2,$0,89
	lui	$2,%hi(GM_NoiseLength)
$LGodzAct_800C6814_25:
	sw	$5,%lo(GM_NoiseLength)($2)
	lui	$2,%hi(GM_NoisePosition)
	sw	$4,%lo(GM_NoisePower)($6)
	addiu	$11,$2,%lo(GM_NoisePosition)
	lwl	$8,35($16)
	lwr	$8,32($16)
	lwl	$9,39($16)
	lwr	$9,36($16)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
$LGodzAct_800C6814_26:
	addiu	$2,$0,89
$LGodzAct_800C6814_27:
	bne	$18,$2,$LGodzAct_800C6814_33
	slti	$2,$18,17
	addiu	$4,$16,32
	addiu	$5,$0,199
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$LGodzAct_800C6814_32
	addiu	$5,$0,8
	bne	$3,$4,$LGodzAct_800C6814_28
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$LGodzAct_800C6814_33
	slti	$2,$18,17
	lui	$2,%hi(GM_NoiseLength)
$LGodzAct_800C6814_28:
	sw	$5,%lo(GM_NoiseLength)($2)
	lui	$2,%hi(GM_NoisePosition)
	sw	$4,%lo(GM_NoisePower)($6)
	addiu	$11,$2,%lo(GM_NoisePosition)
	lwl	$8,35($16)
	lwr	$8,32($16)
	lwl	$9,39($16)
	lwr	$9,36($16)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	j	$LGodzAct_800C6814_33
	slti	$2,$18,17
$LGodzAct_800C6814_29:
	addiu	$2,$18,-7
	sltiu	$2,$2,23
	beq	$2,$0,$LGodzAct_800C6814_30
	slti	$2,$18,20
	jal	GodzAttackTouch
	addu	$4,$16,$0
	slti	$2,$18,20
$LGodzAct_800C6814_30:
	beq	$2,$0,$LGodzAct_800C6814_32
	addiu	$2,$0,-32767
	j	$LGodzAct_800C6814_32
	sh	$2,52($17)
$LGodzAct_800C6814_31:
	lw	$2,2940($16)
	nop
	ori	$2,$2,0x4
	sw	$2,2940($16)
$LGodzAct_800C6814_32:
	slti	$2,$18,17
$LGodzAct_800C6814_33:
	bne	$2,$0,$LGodzAct_800C6814_34
	nop
	lb	$2,87($17)
	nop
	beq	$2,$0,$LGodzAct_800C6814_34
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,71($17)
	swr	$8,68($17)
	swl	$9,75($17)
	swr	$9,72($17)
$LGodzAct_800C6814_34:
	lh	$2,2922($16)
	nop
	bne	$18,$2,$LGodzAct_800C6814_36
	addiu	$4,$16,32
	addiu	$5,$0,199
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$4,%hi(godz_act_data_133C)
	addiu	$4,$4,%lo(godz_act_data_133C)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(godz_act_data_1350)
	addiu	$4,$4,%lo(godz_act_data_1350)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$LGodzAct_800C6814_36
	addiu	$5,$0,8
	bne	$3,$4,$LGodzAct_800C6814_35
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$LGodzAct_800C6814_36
	lui	$2,%hi(GM_NoiseLength)
$LGodzAct_800C6814_35:
	sw	$5,%lo(GM_NoiseLength)($2)
	lui	$2,%hi(GM_NoisePosition)
	sw	$4,%lo(GM_NoisePower)($6)
	addiu	$11,$2,%lo(GM_NoisePosition)
	lwl	$8,35($16)
	lwr	$8,32($16)
	lwl	$9,39($16)
	lwr	$9,36($16)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
$LGodzAct_800C6814_36:
	lh	$2,182($16)
	nop
	beq	$2,$0,$LGodzAct_800C6814_39
	addiu	$2,$0,1
	lw	$3,2304($16)
	sh	$2,2278($16)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,47($3)
	swr	$8,44($3)
	swl	$9,51($3)
	swr	$9,48($3)
	lw	$2,2304($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$LGodzAct_800C6814_37
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(GodzAct_800C70F4)
	j	$LGodzAct_800C6814_38
	addiu	$2,$2,%lo(GodzAct_800C70F4)
$LGodzAct_800C6814_37:
	addu	$5,$0,$0
	lui	$2,%hi(GodzAct_800C6440)
	addiu	$2,$2,%lo(GodzAct_800C6440)
$LGodzAct_800C6814_38:
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$LGodzAct_800C6814_39:
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
	.set	macro
	.set	reorder
	.rdata
	.word	0			# (the original has a zero word in front of the table)
	.align	2
GodzAct_800C6814_jtbl_800DE720:
	.word	$LGodzAct_800C6814_0
	.word	$LGodzAct_800C6814_1
	.word	$LGodzAct_800C6814_10
	.word	$LGodzAct_800C6814_7
	.word	$LGodzAct_800C6814_11
	.word	$LGodzAct_800C6814_12
	.word	$LGodzAct_800C6814_15
	.word	$LGodzAct_800C6814_18
	.word	$LGodzAct_800C6814_29
	.word	$LGodzAct_800C6814_22
	.word	$LGodzAct_800C6814_31
	.word	$LGodzAct_800C6814_31
	.align	2
	.text
