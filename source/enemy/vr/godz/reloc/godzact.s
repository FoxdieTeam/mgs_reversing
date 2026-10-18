	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C4DB8
vcd_n05_800C4DB8:
	addiu	$29,$29,-32
	sw	$16,24($29)
	addu	$16,$4,$0
	addiu	$7,$0,159
	addu	$6,$0,$0
	addiu	$4,$16,2304
	sw	$31,28($29)
$Lvcd_n05_800C4DB8_0:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$6,$6,1
	or	$3,$3,$7
	sh	$3,0($2)
	slti	$2,$6,5
	bne	$2,$0,$Lvcd_n05_800C4DB8_0
	addiu	$4,$4,4
	lw	$2,2940($16)
	nop
	ori	$2,$2,0x1
	sw	$2,2940($16)
	lui	$2,%hi(GodzCommand+32)
	lw	$2,%lo(GodzCommand+32)($2)
	nop
	bne	$2,$0,$Lvcd_n05_800C4DB8_2
	lui	$2,%hi(GODZ_EYE_LENGTH)
	addiu	$7,$0,64
	addu	$6,$0,$0
	addiu	$4,$16,2304
$Lvcd_n05_800C4DB8_1:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$6,$6,1
	or	$3,$3,$7
	sh	$3,0($2)
	slti	$2,$6,5
	bne	$2,$0,$Lvcd_n05_800C4DB8_1
	addiu	$4,$4,4
	lui	$2,%hi(GODZ_EYE_LENGTH)
$Lvcd_n05_800C4DB8_2:
	lhu	$2,%lo(GODZ_EYE_LENGTH)($2)
	bne	$5,$0,$Lvcd_n05_800C4DB8_3
	sh	$2,2972($16)
	addiu	$4,$16,156
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data)
	sh	$0,2272($16)
	lh	$5,%lo(godzact_data)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	lui	$4,%hi(godz_str_okiagari)
	lh	$5,108($16)
	jal	printf
	addiu	$4,$4,%lo(godz_str_okiagari)
$Lvcd_n05_800C4DB8_3:
	jal	GodzCheckDamage
	addu	$4,$16,$0
	bne	$2,$0,$Lvcd_n05_800C4DB8_4
	addiu	$4,$16,156
	jal	GodzCheckPad
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800C4DB8_5
	addiu	$4,$16,156
$Lvcd_n05_800C4DB8_4:
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data)
	sh	$0,2274($16)
	lh	$5,%lo(godzact_data)($2)
	addiu	$7,$0,4
	jal	GM_ConfigObjectOverride
	sw	$0,16($29)
	sw	$0,2288($16)
	sw	$0,2296($16)
	sh	$0,2274($16)
	sh	$0,112($16)
	j	$Lvcd_n05_800C4DB8_10
	sh	$0,108($16)
$Lvcd_n05_800C4DB8_5:
	lh	$5,2904($16)
	nop
	bltz	$5,$Lvcd_n05_800C4DB8_9
	nop
	lh	$4,42($16)
	jal	GV_DiffDirAbs
	nop
	slti	$2,$2,256
	beq	$2,$0,$Lvcd_n05_800C4DB8_8
	nop
	lw	$2,2892($16)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$Lvcd_n05_800C4DB8_6
	addiu	$4,$16,156
	addiu	$2,$0,2
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+4)
	lh	$5,%lo(godzact_data+4)($2)
	j	$Lvcd_n05_800C4DB8_7
	addu	$6,$0,$0
$Lvcd_n05_800C4DB8_6:
	addu	$6,$0,$0
	addiu	$2,$0,1
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+2)
	lh	$5,%lo(godzact_data+2)($2)
$Lvcd_n05_800C4DB8_7:
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C4FA0)
	addiu	$2,$2,%lo(vcd_n05_800C4FA0)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
	j	$Lvcd_n05_800C4DB8_9
	nop
$Lvcd_n05_800C4DB8_8:
	lhu	$2,2904($16)
	nop
	sh	$2,110($16)
$Lvcd_n05_800C4DB8_9:
	lhu	$2,42($16)
	nop
	sh	$2,2968($16)
$Lvcd_n05_800C4DB8_10:
	lw	$31,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C4FA0
vcd_n05_800C4FA0:
	addiu	$29,$29,-56
	sw	$17,28($29)
	addu	$17,$4,$0
	addiu	$6,$0,159
	addu	$5,$0,$0
	addiu	$4,$17,2304
	sw	$31,52($29)
	sw	$22,48($29)
	sw	$21,44($29)
	sw	$20,40($29)
	sw	$19,36($29)
	sw	$18,32($29)
	sw	$16,24($29)
$Lvcd_n05_800C4FA0_0:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$5,$5,1
	or	$3,$3,$6
	sh	$3,0($2)
	slti	$2,$5,5
	bne	$2,$0,$Lvcd_n05_800C4FA0_0
	addiu	$4,$4,4
	lw	$2,2940($17)
	nop
	ori	$2,$2,0x1
	sw	$2,2940($17)
	lui	$2,%hi(GodzCommand+32)
	lw	$2,%lo(GodzCommand+32)($2)
	nop
	bne	$2,$0,$Lvcd_n05_800C4FA0_2
	lui	$2,%hi(GODZ_EYE_LENGTH)
	addiu	$6,$0,64
	addu	$5,$0,$0
	addiu	$4,$17,2304
$Lvcd_n05_800C4FA0_1:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$5,$5,1
	or	$3,$3,$6
	sh	$3,0($2)
	slti	$2,$5,5
	bne	$2,$0,$Lvcd_n05_800C4FA0_1
	addiu	$4,$4,4
	lui	$2,%hi(GODZ_EYE_LENGTH)
$Lvcd_n05_800C4FA0_2:
	lhu	$2,%lo(GODZ_EYE_LENGTH)($2)
	addu	$4,$17,$0
	jal	GodzCheckDamage
	sh	$2,2972($17)
	bne	$2,$0,$Lvcd_n05_800C4FA0_6
	addiu	$4,$17,156
	jal	GodzCheckPad
	addu	$4,$17,$0
	bne	$2,$0,$Lvcd_n05_800C4FA0_6
	addiu	$4,$17,156
	addiu	$21,$0,-1
	addiu	$19,$17,32
	lh	$18,2904($17)
	lw	$2,2892($17)
	lh	$22,2272($17)
	andi	$2,$2,0x1
	beq	$2,$0,$Lvcd_n05_800C4FA0_3
	addiu	$20,$17,128
	addiu	$2,$0,2
	beq	$22,$2,$Lvcd_n05_800C4FA0_3
	addu	$6,$0,$0
	sh	$2,2272($17)
	lui	$2,%hi(godzact_data+4)
	lh	$5,%lo(godzact_data+4)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$Lvcd_n05_800C4FA0_3:
	bltz	$18,$Lvcd_n05_800C4FA0_5
	addiu	$16,$17,156
	lb	$16,88($19)
	nop
	blez	$16,$Lvcd_n05_800C4FA0_4
	nop
	jal	GV_VecDir2
	addu	$4,$20,$0
	addu	$21,$2,$0
	slti	$2,$16,2
	bne	$2,$0,$Lvcd_n05_800C4FA0_4
	nop
	jal	GV_VecDir2
	addiu	$4,$19,104
	addu	$4,$18,$0
	addu	$20,$2,$0
	jal	GV_DiffDirAbs
	addu	$5,$20,$0
	addu	$4,$18,$0
	addu	$5,$21,$0
	jal	GV_DiffDirAbs
	addu	$16,$2,$0
	slt	$16,$16,$2
	beq	$16,$0,$Lvcd_n05_800C4FA0_4
	nop
	addu	$21,$20,$0
$Lvcd_n05_800C4FA0_4:
	bgez	$18,$Lvcd_n05_800C4FA0_7
	addu	$4,$18,$0
	addiu	$16,$17,156
$Lvcd_n05_800C4FA0_5:
	addu	$4,$16,$0
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C4DB8)
	addiu	$2,$2,%lo(vcd_n05_800C4DB8)
	sw	$2,2284($17)
	sw	$0,2292($17)
	sh	$0,112($17)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($17)
	addu	$4,$16,$0
$Lvcd_n05_800C4FA0_6:
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data)
	sh	$0,2274($17)
	lh	$5,%lo(godzact_data)($2)
	addiu	$7,$0,4
	jal	GM_ConfigObjectOverride
	sw	$0,16($29)
	sw	$0,2288($17)
	sw	$0,2296($17)
	sh	$0,2274($17)
	sh	$0,112($17)
	j	$Lvcd_n05_800C4FA0_16
	sh	$0,108($17)
$Lvcd_n05_800C4FA0_7:
	jal	GodzCheckDir
	addu	$5,$21,$0
	addu	$3,$2,$0
	addiu	$2,$0,1
	beq	$3,$2,$Lvcd_n05_800C4FA0_8
	addiu	$2,$0,2
	beq	$3,$2,$Lvcd_n05_800C4FA0_9
	addiu	$2,$21,1024
	j	$Lvcd_n05_800C4FA0_10
	nop
$Lvcd_n05_800C4FA0_8:
	addiu	$2,$21,-1024
$Lvcd_n05_800C4FA0_9:
	andi	$18,$2,0xfff
$Lvcd_n05_800C4FA0_10:
	lw	$2,156($17)
	nop
	lh	$2,50($2)
	nop
	bne	$2,$0,$Lvcd_n05_800C4FA0_11
	nop
	sh	$18,10($19)
$Lvcd_n05_800C4FA0_11:
	sh	$18,78($19)
	addiu	$2,$0,1
	bne	$22,$2,$Lvcd_n05_800C4FA0_12
	addu	$16,$0,$0
	j	$Lvcd_n05_800C4FA0_13
	addiu	$16,$0,40
$Lvcd_n05_800C4FA0_12:
	addiu	$2,$0,2
	bne	$22,$2,$Lvcd_n05_800C4FA0_13
	nop
	addiu	$16,$0,100
$Lvcd_n05_800C4FA0_13:
	jal	rsin
	addu	$4,$18,$0
	mult	$16,$2
	mflo	$2
	bgez	$2,$Lvcd_n05_800C4FA0_14
	nop
	addiu	$2,$2,4095
$Lvcd_n05_800C4FA0_14:
	sra	$2,$2,12
	sh	$2,68($19)
	jal	rcos
	addu	$4,$18,$0
	mult	$16,$2
	mflo	$2
	bgez	$2,$Lvcd_n05_800C4FA0_15
	nop
	addiu	$2,$2,4095
$Lvcd_n05_800C4FA0_15:
	sra	$2,$2,12
	sh	$2,72($19)
	lhu	$2,42($17)
	nop
	sh	$2,2968($17)
$Lvcd_n05_800C4FA0_16:
	lw	$31,52($29)
	lw	$22,48($29)
	lw	$21,44($29)
	lw	$20,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C5278
vcd_n05_800C5278:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lvcd_n05_800C5278_0
	sw	$31,20($29)
	addiu	$4,$16,156
	addiu	$2,$0,3
	sw	$2,2268($16)
	addiu	$2,$0,35
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+70)
	addu	$6,$0,$0
	lh	$5,%lo(godzact_data+70)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$Lvcd_n05_800C5278_0:
	jal	GodzCheckDamage
	addu	$4,$16,$0
	bne	$2,$0,$Lvcd_n05_800C5278_1
	nop
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C5278_1
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C6440)
	addiu	$2,$2,%lo(vcd_n05_800C6440)
	sw	$0,2896($16)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C5278_1:
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
	.globl	vcd_n05_800C5308
vcd_n05_800C5308:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lvcd_n05_800C5308_0
	sw	$31,20($29)
	addiu	$4,$16,156
	lui	$2,%hi(godzact_data)
	addu	$6,$0,$0
	sh	$0,2272($16)
	lh	$5,%lo(godzact_data)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$Lvcd_n05_800C5308_0:
	lhu	$2,2904($16)
	nop
	sh	$2,110($16)
	lw	$2,2888($16)
	lui	$3,0x1000
	and	$2,$2,$3
	bne	$2,$0,$Lvcd_n05_800C5308_1
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C4DB8)
	addiu	$2,$2,%lo(vcd_n05_800C4DB8)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C5308_1:
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
	.globl	vcd_n05_800C5388
vcd_n05_800C5388:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lvcd_n05_800C5388_2
	sw	$31,20($29)
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800C5388_0
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,46
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+92)
	lh	$5,%lo(godzact_data+92)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$16,32
	j	$Lvcd_n05_800C5388_1
	addiu	$5,$0,135
$Lvcd_n05_800C5388_0:
	addu	$6,$0,$0
	addiu	$2,$0,47
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+94)
	lh	$5,%lo(godzact_data+94)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$16,32
	addiu	$5,$0,128
$Lvcd_n05_800C5388_1:
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lvcd_n05_800C5388_2:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C5388_3
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C4DB8)
	addiu	$2,$2,%lo(vcd_n05_800C4DB8)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C5388_3:
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
	.globl	vcd_n05_800C5440
vcd_n05_800C5440:
	addiu	$29,$29,-40
	sw	$18,32($29)
	addu	$18,$4,$0
	sw	$31,36($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$2,2940($18)
	addu	$16,$5,$0
	ori	$2,$2,0x40
	bne	$16,$0,$Lvcd_n05_800C5440_0
	sw	$2,2940($18)
	addiu	$4,$18,156
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data)
	sh	$0,2272($18)
	lh	$5,%lo(godzact_data)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$Lvcd_n05_800C5440_0:
	addiu	$2,$0,30
	bne	$16,$2,$Lvcd_n05_800C5440_3
	addiu	$2,$0,35
	lb	$3,2949($18)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800C5440_1
	addiu	$4,$18,156
	addu	$6,$0,$0
	addiu	$2,$0,13
	sh	$2,2272($18)
	lui	$2,%hi(godzact_data+26)
	lh	$5,%lo(godzact_data+26)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$18,32
	j	$Lvcd_n05_800C5440_2
	addiu	$5,$0,135
$Lvcd_n05_800C5440_1:
	addu	$6,$0,$0
	addiu	$2,$0,12
	sh	$2,2272($18)
	lui	$2,%hi(godzact_data+24)
	lh	$5,%lo(godzact_data+24)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$18,32
	addiu	$5,$0,128
$Lvcd_n05_800C5440_2:
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,35
$Lvcd_n05_800C5440_3:
	beq	$16,$2,$Lvcd_n05_800C5440_4
	addiu	$2,$0,40
	beq	$16,$2,$Lvcd_n05_800C5440_4
	addiu	$2,$0,45
	beq	$16,$2,$Lvcd_n05_800C5440_4
	addiu	$2,$0,50
	beq	$16,$2,$Lvcd_n05_800C5440_4
	addiu	$2,$0,55
	bne	$16,$2,$Lvcd_n05_800C5440_5
	addiu	$2,$0,60
$Lvcd_n05_800C5440_4:
	addiu	$4,$18,32
	addiu	$5,$0,202
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,60
$Lvcd_n05_800C5440_5:
	bne	$16,$2,$Lvcd_n05_800C5440_6
	addiu	$2,$0,90
	addiu	$4,$18,32
	addiu	$5,$0,136
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,90
$Lvcd_n05_800C5440_6:
	bne	$16,$2,$Lvcd_n05_800C5440_7
	addiu	$2,$0,120
	addiu	$4,$18,32
	addiu	$5,$0,129
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,120
$Lvcd_n05_800C5440_7:
	bne	$16,$2,$Lvcd_n05_800C5440_8
	addiu	$2,$0,150
	addiu	$4,$18,32
	addiu	$5,$0,137
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,150
$Lvcd_n05_800C5440_8:
	bne	$16,$2,$Lvcd_n05_800C5440_9
	addiu	$2,$0,180
	addiu	$4,$18,32
	addiu	$5,$0,130
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,180
$Lvcd_n05_800C5440_9:
	bne	$16,$2,$Lvcd_n05_800C5440_10
	addiu	$2,$0,210
	addiu	$4,$18,32
	addiu	$5,$0,136
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,210
$Lvcd_n05_800C5440_10:
	bne	$16,$2,$Lvcd_n05_800C5440_11
	addiu	$2,$0,240
	addiu	$4,$18,32
	addiu	$5,$0,129
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,240
$Lvcd_n05_800C5440_11:
	bne	$16,$2,$Lvcd_n05_800C5440_12
	addiu	$2,$0,270
	addiu	$4,$18,32
	addiu	$5,$0,137
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,270
$Lvcd_n05_800C5440_12:
	bne	$16,$2,$Lvcd_n05_800C5440_13
	addiu	$2,$0,300
	addiu	$4,$18,32
	addiu	$5,$0,130
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,300
$Lvcd_n05_800C5440_13:
	bne	$16,$2,$Lvcd_n05_800C5440_14
	addiu	$2,$0,310
	addiu	$4,$18,32
	addiu	$5,$0,136
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,310
$Lvcd_n05_800C5440_14:
	bne	$16,$2,$Lvcd_n05_800C5440_15
	addiu	$2,$0,104
	addiu	$4,$18,32
	addiu	$5,$0,129
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,104
$Lvcd_n05_800C5440_15:
	bne	$16,$2,$Lvcd_n05_800C5440_16
	addiu	$2,$0,155
	addiu	$4,$18,32
	addiu	$5,$0,203
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,155
$Lvcd_n05_800C5440_16:
	beq	$16,$2,$Lvcd_n05_800C5440_17
	addiu	$2,$0,204
	beq	$16,$2,$Lvcd_n05_800C5440_17
	addiu	$2,$0,265
	beq	$16,$2,$Lvcd_n05_800C5440_17
	addiu	$2,$0,295
	bne	$16,$2,$Lvcd_n05_800C5440_18
	slti	$2,$16,61
$Lvcd_n05_800C5440_17:
	addiu	$4,$18,32
	addiu	$5,$0,204
	jal	GM_SeSetMode
	addiu	$6,$0,1
	slti	$2,$16,61
$Lvcd_n05_800C5440_18:
	bne	$2,$0,$Lvcd_n05_800C5440_19
	nop
	lh	$2,182($18)
	nop
	beq	$2,$0,$Lvcd_n05_800C5440_19
	addiu	$4,$18,32
	addiu	$5,$0,200
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$4,$0,2048
	addiu	$5,$29,16
	addiu	$6,$0,1
	addiu	$2,$0,-2500
	addiu	$17,$0,-2000
	addiu	$16,$0,-27500
	sh	$2,16($29)
	sh	$17,18($29)
	jal	vcd_n05_800CD920
	sh	$16,20($29)
	addiu	$4,$0,1024
	addiu	$5,$29,16
	jal	vcd_n05_800CD920
	addiu	$6,$0,1
	addiu	$4,$0,2048
	addiu	$5,$29,16
	addiu	$6,$0,1
	addiu	$2,$0,2500
	sh	$2,16($29)
	sh	$17,18($29)
	jal	vcd_n05_800CD920
	sh	$16,20($29)
	addiu	$4,$0,1024
	addiu	$5,$29,16
	jal	vcd_n05_800CD920
	addiu	$6,$0,1
	addiu	$4,$18,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C5768)
	addiu	$2,$2,%lo(vcd_n05_800C5768)
	sw	$2,2284($18)
	sw	$0,2292($18)
	sh	$0,112($18)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($18)
$Lvcd_n05_800C5440_19:
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C5768
vcd_n05_800C5768:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	addu	$17,$5,$0
	bne	$17,$0,$Lvcd_n05_800C5768_0
	sw	$31,24($29)
	addiu	$4,$16,156
	lui	$2,%hi(godzact_data)
	addu	$6,$0,$0
	sw	$0,2548($16)
	sh	$0,2272($16)
	lh	$5,%lo(godzact_data)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$Lvcd_n05_800C5768_0:
	addiu	$2,$0,90
	bne	$17,$2,$Lvcd_n05_800C5768_1
	addiu	$2,$0,60
	lw	$4,3148($16)
	nop
	bltz	$4,$Lvcd_n05_800C5768_1
	nop
	jal	GCL_ExecProc
	addu	$5,$0,$0
	addiu	$2,$0,60
$Lvcd_n05_800C5768_1:
	bne	$17,$2,$Lvcd_n05_800C5768_2
	nop
	lw	$2,76($16)
	nop
	lw	$4,0($2)
	jal	vcd_n05_800CE9A4
	nop
$Lvcd_n05_800C5768_2:
	lw	$31,24($29)
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
	.globl	vcd_n05_800C57FC
vcd_n05_800C57FC:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$7,$0,159
	addu	$6,$0,$0
	addiu	$4,$16,2304
	sw	$31,24($29)
	sw	$17,20($29)
$Lvcd_n05_800C57FC_0:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$6,$6,1
	or	$3,$3,$7
	sh	$3,0($2)
	slti	$2,$6,5
	bne	$2,$0,$Lvcd_n05_800C57FC_0
	addiu	$4,$4,4
	lui	$2,%hi(GODZ_EYE_LENGTH)
	lhu	$2,%lo(GODZ_EYE_LENGTH)($2)
	addiu	$17,$16,32
	bne	$5,$0,$Lvcd_n05_800C57FC_1
	sh	$2,2972($16)
	addiu	$4,$16,156
	addiu	$2,$0,16
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+32)
	addu	$6,$0,$0
	lh	$5,%lo(godzact_data+32)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$Lvcd_n05_800C57FC_1:
	jal	GodzCheckDamage
	addu	$4,$16,$0
	bne	$2,$0,$Lvcd_n05_800C57FC_4
	nop
	lh	$2,182($16)
	nop
	bne	$2,$0,$Lvcd_n05_800C57FC_2
	nop
	lw	$2,2888($16)
	nop
	andi	$2,$2,0x20
	bne	$2,$0,$Lvcd_n05_800C57FC_3
	nop
$Lvcd_n05_800C57FC_2:
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C4DB8)
	addiu	$2,$2,%lo(vcd_n05_800C4DB8)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
	j	$Lvcd_n05_800C57FC_4
	nop
$Lvcd_n05_800C57FC_3:
	lhu	$2,2904($16)
	sh	$0,68($17)
	sh	$0,72($17)
	sh	$2,78($17)
	lhu	$2,42($16)
	nop
	sh	$2,2968($16)
$Lvcd_n05_800C57FC_4:
	lw	$31,24($29)
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
	.globl	vcd_n05_800C5904
vcd_n05_800C5904:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C590C
vcd_n05_800C590C:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$7,$0,159
	addu	$6,$0,$0
	addiu	$4,$16,2304
	sw	$31,24($29)
	sw	$17,20($29)
$Lvcd_n05_800C590C_0:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$6,$6,1
	or	$3,$3,$7
	sh	$3,0($2)
	slti	$2,$6,5
	bne	$2,$0,$Lvcd_n05_800C590C_0
	addiu	$4,$4,4
	lui	$2,%hi(GODZ_EYE_LENGTH)
	lhu	$2,%lo(GODZ_EYE_LENGTH)($2)
	lw	$17,2888($16)
	bne	$5,$0,$Lvcd_n05_800C590C_3
	sh	$2,2972($16)
	lui	$2,0x1
	and	$2,$17,$2
	beq	$2,$0,$Lvcd_n05_800C590C_1
	addiu	$2,$0,3
	addiu	$4,$16,156
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+6)
	lh	$5,%lo(godzact_data+6)($2)
	j	$Lvcd_n05_800C590C_2
	addu	$6,$0,$0
$Lvcd_n05_800C590C_1:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,5
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+10)
	lh	$5,%lo(godzact_data+10)($2)
$Lvcd_n05_800C590C_2:
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$16,156
	jal	GM_ConfigMotionAdjust
	addiu	$5,$16,1828
	addiu	$4,$16,32
	addu	$5,$0,$0
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$4,%hi(godz_str_turn)
	lh	$5,110($16)
	lh	$6,42($16)
	jal	printf
	addiu	$4,$4,%lo(godz_str_turn)
$Lvcd_n05_800C590C_3:
	jal	GodzReviseReadyGun
	addu	$4,$16,$0
	jal	GodzCheckDamage
	addu	$4,$16,$0
	bne	$2,$0,$Lvcd_n05_800C590C_12
	lui	$2,0x3
	and	$2,$17,$2
	bne	$2,$0,$Lvcd_n05_800C590C_4
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C4DB8)
	j	$Lvcd_n05_800C590C_6
	addiu	$2,$2,%lo(vcd_n05_800C4DB8)
$Lvcd_n05_800C590C_4:
	lui	$2,0x4
	and	$2,$17,$2
	beq	$2,$0,$Lvcd_n05_800C590C_5
	lui	$2,%hi(vcd_n05_800C5AD4)
	j	$Lvcd_n05_800C590C_9
	addiu	$2,$2,%lo(vcd_n05_800C5AD4)
$Lvcd_n05_800C590C_5:
	lui	$2,0x8
	and	$2,$17,$2
	beq	$2,$0,$Lvcd_n05_800C590C_7
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C5BA4)
	addiu	$2,$2,%lo(vcd_n05_800C5BA4)
$Lvcd_n05_800C590C_6:
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
	j	$Lvcd_n05_800C590C_12
	nop
$Lvcd_n05_800C590C_7:
	lui	$2,0x10
	and	$2,$17,$2
	beq	$2,$0,$Lvcd_n05_800C590C_8
	lui	$2,%hi(vcd_n05_800C5CF8)
	j	$Lvcd_n05_800C590C_9
	addiu	$2,$2,%lo(vcd_n05_800C5CF8)
$Lvcd_n05_800C590C_8:
	lui	$2,0x20
	and	$2,$17,$2
	beq	$2,$0,$Lvcd_n05_800C590C_10
	lui	$2,%hi(vcd_n05_800C5E70)
	addiu	$2,$2,%lo(vcd_n05_800C5E70)
$Lvcd_n05_800C590C_9:
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	j	$Lvcd_n05_800C590C_12
	sh	$0,108($16)
$Lvcd_n05_800C590C_10:
	lh	$2,2904($16)
	lhu	$3,2904($16)
	bltz	$2,$Lvcd_n05_800C590C_11
	nop
	sh	$3,110($16)
$Lvcd_n05_800C590C_11:
	lhu	$2,42($16)
	nop
	sh	$2,2968($16)
$Lvcd_n05_800C590C_12:
	lw	$31,24($29)
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
	.globl	vcd_n05_800C5AD4
vcd_n05_800C5AD4:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	addiu	$7,$0,159
	addu	$6,$0,$0
	addiu	$4,$17,2304
	sw	$31,24($29)
	sw	$16,16($29)
$Lvcd_n05_800C5AD4_0:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$6,$6,1
	or	$3,$3,$7
	sh	$3,0($2)
	slti	$2,$6,5
	bne	$2,$0,$Lvcd_n05_800C5AD4_0
	addiu	$4,$4,4
	lui	$2,%hi(GODZ_EYE_LENGTH)
	lhu	$2,%lo(GODZ_EYE_LENGTH)($2)
	bne	$5,$0,$Lvcd_n05_800C5AD4_1
	sh	$2,2972($17)
	addiu	$16,$17,156
	addu	$4,$16,$0
	addiu	$2,$0,4
	sh	$2,2272($17)
	lui	$2,%hi(godzact_data+8)
	addu	$6,$0,$0
	lh	$5,%lo(godzact_data+8)($2)
	jal	GM_ConfigObjectAction
	addu	$7,$6,$0
	addu	$4,$17,$0
	jal	vcd_n05_800C7EF4
	addiu	$5,$0,3
	addu	$4,$16,$0
	jal	GM_ConfigMotionAdjust
	addiu	$5,$17,1828
$Lvcd_n05_800C5AD4_1:
	jal	GodzReviseReadyGun
	addu	$4,$17,$0
	jal	GodzCheckDamage
	addu	$4,$17,$0
	bne	$2,$0,$Lvcd_n05_800C5AD4_2
	lui	$2,%hi(vcd_n05_800C590C)
	addiu	$2,$2,%lo(vcd_n05_800C590C)
	sw	$2,2284($17)
	sw	$0,2292($17)
	sh	$0,112($17)
	sh	$0,108($17)
$Lvcd_n05_800C5AD4_2:
	lw	$31,24($29)
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
	jal	vcd_n05_800C7EF4
	addiu	$5,$0,3
	slti	$2,$18,77
$Lvcd_n05_800C5BA4_6:
	bne	$2,$0,$Lvcd_n05_800C5BA4_7
	addiu	$4,$17,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C590C)
	addiu	$2,$2,%lo(vcd_n05_800C590C)
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C5CF8
vcd_n05_800C5CF8:
	addiu	$29,$29,-40
	sw	$17,28($29)
	addu	$17,$4,$0
	sw	$18,32($29)
	addu	$18,$5,$0
	addiu	$6,$0,159
	addu	$5,$0,$0
	addiu	$4,$17,2304
	sw	$31,36($29)
	sw	$16,24($29)
$Lvcd_n05_800C5CF8_0:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$5,$5,1
	or	$3,$3,$6
	sh	$3,0($2)
	slti	$2,$5,5
	bne	$2,$0,$Lvcd_n05_800C5CF8_0
	addiu	$4,$4,4
	lui	$2,%hi(GODZ_EYE_LENGTH)
	lhu	$2,%lo(GODZ_EYE_LENGTH)($2)
	bne	$18,$0,$Lvcd_n05_800C5CF8_1
	sh	$2,2972($17)
	addiu	$16,$17,156
	addu	$4,$16,$0
	addu	$6,$0,$0
	addiu	$2,$0,7
	sh	$2,2272($17)
	lui	$2,%hi(godzact_data+14)
	lh	$5,%lo(godzact_data+14)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$17,32
	addu	$5,$16,$0
	addiu	$6,$0,9
	addiu	$7,$17,2912
	lui	$2,%hi(GM_PlayerPosition)
	addiu	$2,$2,%lo(GM_PlayerPosition)
	sw	$2,16($29)
	addiu	$2,$0,2
	jal	NewGrenadeEnemy
	sw	$2,20($29)
	sw	$2,2916($17)
$Lvcd_n05_800C5CF8_1:
	slti	$2,$18,5
	bne	$2,$0,$Lvcd_n05_800C5CF8_2
	addiu	$2,$0,17
	lw	$2,2912($17)
	nop
	ori	$2,$2,0x1
	sw	$2,2912($17)
	addiu	$2,$0,17
$Lvcd_n05_800C5CF8_2:
	bne	$18,$2,$Lvcd_n05_800C5CF8_3
	addiu	$2,$0,45
	addiu	$4,$17,32
	jal	GM_SeSet
	addiu	$5,$0,44
	addiu	$2,$0,45
$Lvcd_n05_800C5CF8_3:
	bne	$18,$2,$Lvcd_n05_800C5CF8_4
	nop
	lw	$2,2912($17)
	nop
	ori	$2,$2,0x4
	sw	$2,2912($17)
$Lvcd_n05_800C5CF8_4:
	jal	GodzCheckDamage
	addu	$4,$17,$0
	beq	$2,$0,$Lvcd_n05_800C5CF8_5
	nop
	lw	$4,2916($17)
	jal	GV_DestroyActor
	nop
	j	$Lvcd_n05_800C5CF8_6
	nop
$Lvcd_n05_800C5CF8_5:
	lh	$2,182($17)
	nop
	beq	$2,$0,$Lvcd_n05_800C5CF8_6
	nop
	lw	$4,2916($17)
	jal	GV_DestroyActor
	nop
	addiu	$4,$17,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C590C)
	addiu	$2,$2,%lo(vcd_n05_800C590C)
	sw	$2,2284($17)
	sw	$0,2292($17)
	sh	$0,112($17)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($17)
$Lvcd_n05_800C5CF8_6:
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C5E70
vcd_n05_800C5E70:
	lui	$2,%hi(GODZ_EYE_LENGTH)
	lhu	$2,%lo(GODZ_EYE_LENGTH)($2)
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	addu	$17,$5,$0
	sw	$31,24($29)
	bne	$17,$0,$Lvcd_n05_800C5E70_0
	sh	$2,2972($16)
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,8
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+16)
	lh	$5,%lo(godzact_data+16)($2)
	jal	GM_ConfigObjectAction
	addu	$7,$6,$0
$Lvcd_n05_800C5E70_0:
	addiu	$2,$0,27
	bne	$17,$2,$Lvcd_n05_800C5E70_1
	nop
	jal	GodzAttackForce
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800C5E70_1
	addiu	$4,$16,32
	addiu	$5,$0,41
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lvcd_n05_800C5E70_1:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C5E70_2
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C590C)
	addiu	$2,$2,%lo(vcd_n05_800C590C)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
	j	$Lvcd_n05_800C5E70_3
	nop
$Lvcd_n05_800C5E70_2:
	lhu	$2,2904($16)
	nop
	sh	$2,110($16)
$Lvcd_n05_800C5E70_3:
	lw	$31,24($29)
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
	.globl	vcd_n05_800C5F38
vcd_n05_800C5F38:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	bne	$5,$0,$Lvcd_n05_800C5F38_0
	sh	$0,2972($16)
	addiu	$4,$16,156
	addiu	$2,$0,21
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+42)
	addu	$6,$0,$0
	lh	$5,%lo(godzact_data+42)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$Lvcd_n05_800C5F38_0:
	jal	GodzCheckDamage
	addu	$4,$16,$0
	bne	$2,$0,$Lvcd_n05_800C5F38_2
	addiu	$6,$0,159
	addu	$5,$0,$0
	addiu	$4,$16,2304
$Lvcd_n05_800C5F38_1:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$5,$5,1
	or	$3,$3,$6
	sh	$3,0($2)
	slti	$2,$5,5
	bne	$2,$0,$Lvcd_n05_800C5F38_1
	addiu	$4,$4,4
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C5F38_2
	addiu	$4,$16,156
	addu	$5,$0,$0
	addiu	$2,$0,1
	sw	$2,2300($16)
	lui	$2,%hi(vcd_n05_800C4DB8)
	addiu	$2,$2,%lo(vcd_n05_800C4DB8)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C5F38_2:
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
	.globl	vcd_n05_800C5FF4
vcd_n05_800C5FF4:
	addiu	$29,$29,-40
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$18,24($29)
	addu	$18,$5,$0
	sw	$31,32($29)
	sw	$19,28($29)
	sw	$17,20($29)
	lw	$2,2940($16)
	lw	$19,2304($16)
	addiu	$17,$16,32
	sh	$0,2278($16)
	ori	$2,$2,0x8
	bne	$18,$0,$Lvcd_n05_800C5FF4_0
	sw	$2,2940($16)
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,6
	sw	$2,2268($16)
	addiu	$2,$0,31
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+62)
	lh	$5,%lo(godzact_data+62)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$Lvcd_n05_800C5FF4_0:
	addiu	$2,$18,-8
	sltiu	$2,$2,12
	beq	$2,$0,$Lvcd_n05_800C5FF4_1
	nop
	jal	GodzAttackTouch
	addu	$4,$16,$0
$Lvcd_n05_800C5FF4_1:
	lh	$3,2272($16)
	addiu	$2,$0,31
	bne	$3,$2,$Lvcd_n05_800C5FF4_5
	addiu	$2,$0,22
	bne	$18,$2,$Lvcd_n05_800C5FF4_4
	nop
	lh	$2,2($17)
	lh	$3,120($17)
	nop
	subu	$3,$2,$3
	slti	$2,$3,2000
	beq	$2,$0,$Lvcd_n05_800C5FF4_3
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,147
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,51
	addu	$4,$16,$0
	addiu	$5,$0,6
	jal	vcd_n05_800C78C8
	addu	$6,$0,$0
	addiu	$4,$0,100
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C5FF4_4
	addiu	$5,$0,4
	bne	$3,$4,$Lvcd_n05_800C5FF4_2
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C5FF4_4
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C5FF4_2:
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
	j	$Lvcd_n05_800C5FF4_4
	nop
$Lvcd_n05_800C5FF4_3:
	slti	$2,$3,30001
	bne	$2,$0,$Lvcd_n05_800C5FF4_4
	addiu	$5,$0,142
	lw	$2,2304($16)
	jal	GM_SeSet
	sh	$0,38($2)
$Lvcd_n05_800C5FF4_4:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C5FF4_11
	slti	$2,$18,24
	lb	$2,87($17)
	nop
	bne	$2,$0,$Lvcd_n05_800C5FF4_8
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,40
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+80)
	lh	$5,%lo(godzact_data+80)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	j	$Lvcd_n05_800C5FF4_11
	slti	$2,$18,24
$Lvcd_n05_800C5FF4_5:
	lb	$2,87($17)
	nop
	beq	$2,$0,$Lvcd_n05_800C5FF4_10
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,147
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,51
	addiu	$4,$0,100
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C5FF4_7
	addiu	$5,$0,4
	bne	$3,$4,$Lvcd_n05_800C5FF4_6
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C5FF4_7
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C5FF4_6:
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
$Lvcd_n05_800C5FF4_7:
	addu	$4,$16,$0
	addiu	$5,$0,6
	jal	vcd_n05_800C78C8
	addiu	$6,$0,1
	lw	$2,2304($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lvcd_n05_800C5FF4_8
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C70F4)
	j	$Lvcd_n05_800C5FF4_9
	addiu	$2,$2,%lo(vcd_n05_800C70F4)
$Lvcd_n05_800C5FF4_8:
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C6440)
	addiu	$2,$2,%lo(vcd_n05_800C6440)
$Lvcd_n05_800C5FF4_9:
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C5FF4_10:
	slti	$2,$18,24
$Lvcd_n05_800C5FF4_11:
	beq	$2,$0,$Lvcd_n05_800C5FF4_12
	slti	$2,$18,22
	lw	$2,28($19)
	nop
	lwl	$8,3($2)
	lwr	$8,0($2)
	lwl	$9,7($2)
	lwr	$9,4($2)
	swl	$8,79($17)
	swr	$8,76($17)
	swl	$9,83($17)
	swr	$9,80($17)
	slti	$2,$18,22
$Lvcd_n05_800C5FF4_12:
	beq	$2,$0,$Lvcd_n05_800C5FF4_13
	addiu	$2,$0,-32767
	sh	$2,84($16)
$Lvcd_n05_800C5FF4_13:
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C62D8
vcd_n05_800C62D8:
	addiu	$29,$29,-40
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$18,24($29)
	addu	$18,$5,$0
	sw	$31,32($29)
	sw	$19,28($29)
	sw	$17,20($29)
	lw	$2,2940($16)
	addiu	$19,$16,32
	sh	$0,2278($16)
	sh	$0,2972($16)
	ori	$2,$2,0x8
	bne	$18,$0,$Lvcd_n05_800C62D8_0
	sw	$2,2940($16)
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,32
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+64)
	lh	$5,%lo(godzact_data+64)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	lw	$2,2304($16)
	nop
	sh	$0,42($2)
$Lvcd_n05_800C62D8_0:
	jal	GodzCheckDamage
	addu	$4,$16,$0
	bne	$2,$0,$Lvcd_n05_800C62D8_6
	addiu	$17,$0,10
	bne	$18,$17,$Lvcd_n05_800C62D8_1
	addiu	$6,$0,159
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,1
	sw	$2,2268($16)
	addiu	$2,$0,37
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+74)
	lh	$5,%lo(godzact_data+74)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	j	$Lvcd_n05_800C62D8_3
	addiu	$2,$17,24
$Lvcd_n05_800C62D8_1:
	addu	$5,$0,$0
	addiu	$4,$16,2304
$Lvcd_n05_800C62D8_2:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$5,$5,1
	or	$3,$3,$6
	sh	$3,0($2)
	slti	$2,$5,5
	bne	$2,$0,$Lvcd_n05_800C62D8_2
	addiu	$4,$4,4
	addiu	$2,$17,24
$Lvcd_n05_800C62D8_3:
	bne	$18,$2,$Lvcd_n05_800C62D8_4
	addiu	$2,$17,46
	addu	$4,$19,$0
	jal	GM_SeSet
	addiu	$5,$0,81
	addiu	$2,$17,46
$Lvcd_n05_800C62D8_4:
	bne	$18,$2,$Lvcd_n05_800C62D8_5
	addiu	$2,$17,50
	addu	$4,$19,$0
	jal	GM_SeSet
	addiu	$5,$0,51
	addiu	$2,$17,50
$Lvcd_n05_800C62D8_5:
	slt	$2,$18,$2
	bne	$2,$0,$Lvcd_n05_800C62D8_6
	nop
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C62D8_6
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C6440)
	addiu	$2,$2,%lo(vcd_n05_800C6440)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C62D8_6:
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C6440
vcd_n05_800C6440:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$31,32($29)
	sw	$17,28($29)
	lw	$2,2940($16)
	addu	$17,$5,$0
	ori	$2,$2,0x20
	bne	$17,$0,$Lvcd_n05_800C6440_4
	sw	$2,2940($16)
	lw	$3,2268($16)
	nop
	slti	$2,$3,3
	beq	$2,$0,$Lvcd_n05_800C6440_1
	addiu	$2,$0,1
	bne	$3,$2,$Lvcd_n05_800C6440_0
	addiu	$4,$16,156
	addiu	$2,$0,41
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+82)
	lh	$5,%lo(godzact_data+82)($2)
	j	$Lvcd_n05_800C6440_2
	addu	$6,$0,$0
$Lvcd_n05_800C6440_0:
	addiu	$2,$0,39
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+78)
	lh	$5,%lo(godzact_data+78)($2)
	j	$Lvcd_n05_800C6440_2
	addu	$6,$0,$0
$Lvcd_n05_800C6440_1:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,40
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+80)
	lh	$5,%lo(godzact_data+80)($2)
$Lvcd_n05_800C6440_2:
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	lui	$3,0x8888
	lhu	$2,32($16)
	ori	$3,$3,0x8889
	sll	$2,$2,16
	sra	$4,$2,16
	mult	$4,$3
	sra	$2,$2,31
	mfhi	$8
	addu	$3,$8,$4
	sra	$3,$3,4
	subu	$3,$3,$2
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,1
	subu	$4,$4,$2
	sll	$4,$4,16
	sra	$2,$4,16
	bgez	$2,$Lvcd_n05_800C6440_3
	nop
	subu	$2,$0,$2
$Lvcd_n05_800C6440_3:
	addiu	$2,$2,10
	sh	$2,2922($16)
$Lvcd_n05_800C6440_4:
	lh	$2,2922($16)
	nop
	slt	$2,$2,$17
	beq	$2,$0,$Lvcd_n05_800C6440_6
	nop
	lw	$3,2304($16)
	nop
	lh	$2,42($3)
	nop
	bgtz	$2,$Lvcd_n05_800C6440_5
	addiu	$4,$16,156
	lhu	$2,2960($16)
	nop
	sh	$2,42($3)
$Lvcd_n05_800C6440_5:
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C6598)
	addiu	$2,$2,%lo(vcd_n05_800C6598)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C6440_6:
	lw	$31,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C6598
vcd_n05_800C6598:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$31,24($29)
	sw	$16,16($29)
	lw	$2,2940($17)
	sh	$0,2278($17)
	ori	$2,$2,0x8
	bne	$5,$0,$Lvcd_n05_800C6598_4
	sw	$2,2940($17)
	lw	$2,2268($17)
	nop
	slti	$2,$2,3
	beq	$2,$0,$Lvcd_n05_800C6598_1
	nop
	lh	$2,2922($17)
	nop
	slti	$2,$2,150
	bne	$2,$0,$Lvcd_n05_800C6598_0
	addiu	$4,$17,156
	addiu	$2,$0,44
	sh	$2,2272($17)
	lui	$2,%hi(godzact_data+88)
	lh	$5,%lo(godzact_data+88)($2)
	j	$Lvcd_n05_800C6598_3
	addu	$6,$0,$0
$Lvcd_n05_800C6598_0:
	addiu	$2,$0,42
	sh	$2,2272($17)
	lui	$2,%hi(godzact_data+84)
	lh	$5,%lo(godzact_data+84)($2)
	j	$Lvcd_n05_800C6598_3
	addu	$6,$0,$0
$Lvcd_n05_800C6598_1:
	lh	$2,2922($17)
	nop
	slti	$2,$2,150
	bne	$2,$0,$Lvcd_n05_800C6598_2
	addiu	$4,$17,156
	addiu	$2,$0,45
	sh	$2,2272($17)
	lui	$2,%hi(godzact_data+90)
	lh	$5,%lo(godzact_data+90)($2)
	j	$Lvcd_n05_800C6598_3
	addu	$6,$0,$0
$Lvcd_n05_800C6598_2:
	addu	$6,$0,$0
	addiu	$2,$0,43
	sh	$2,2272($17)
	lui	$2,%hi(godzact_data+86)
	lh	$5,%lo(godzact_data+86)($2)
$Lvcd_n05_800C6598_3:
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$17,32
	addiu	$5,$0,201
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lvcd_n05_800C6598_4:
	lh	$2,182($17)
	nop
	beq	$2,$0,$Lvcd_n05_800C6598_5
	lui	$4,%hi(godz_str_okiagari)
	lh	$5,108($17)
	jal	printf
	addiu	$4,$4,%lo(godz_str_okiagari)
	addiu	$16,$17,156
	addu	$4,$16,$0
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data)
	sh	$0,2272($17)
	lh	$5,%lo(godzact_data)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$16,$0
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C4DB8)
	addiu	$2,$2,%lo(vcd_n05_800C4DB8)
	sw	$2,2284($17)
	sw	$0,2292($17)
	sh	$0,112($17)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($17)
$Lvcd_n05_800C6598_5:
	lw	$31,24($29)
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
	.globl	vcd_n05_800C66E4
vcd_n05_800C66E4:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	addu	$17,$5,$0
	addiu	$6,$0,159
	addu	$5,$0,$0
	addiu	$4,$16,2304
	sw	$31,28($29)
	sw	$18,24($29)
	sh	$0,2278($16)
$Lvcd_n05_800C66E4_0:
	lw	$2,0($4)
	nop
	lhu	$3,0($2)
	addiu	$5,$5,1
	or	$3,$3,$6
	sh	$3,0($2)
	slti	$2,$5,5
	bne	$2,$0,$Lvcd_n05_800C66E4_0
	addiu	$4,$4,4
	lui	$2,%hi(GODZ_EYE_LENGTH)
	lhu	$3,%lo(GODZ_EYE_LENGTH)($2)
	lw	$2,2940($16)
	addu	$4,$16,$0
	ori	$2,$2,0x8
	sh	$3,2972($16)
	jal	GodzCheckDamage
	sw	$2,2940($16)
	bne	$2,$0,$Lvcd_n05_800C66E4_3
	nop
	lw	$18,2304($16)
	bne	$17,$0,$Lvcd_n05_800C66E4_2
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,15
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+30)
	lh	$5,%lo(godzact_data+30)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$17,$16,32
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,139
	lh	$3,62($18)
	addiu	$2,$0,3
	bne	$3,$2,$Lvcd_n05_800C66E4_1
	addu	$4,$16,$0
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,52
	jal	vcd_n05_800C7938
	addu	$4,$16,$0
	j	$Lvcd_n05_800C66E4_2
	nop
$Lvcd_n05_800C66E4_1:
	addiu	$5,$0,5
	jal	vcd_n05_800C78C8
	addu	$6,$0,$0
$Lvcd_n05_800C66E4_2:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C66E4_3
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C4DB8)
	addiu	$2,$2,%lo(vcd_n05_800C4DB8)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C66E4_3:
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
	.globl	vcd_n05_800C6814
vcd_n05_800C6814:
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
	bne	$18,$0,$Lvcd_n05_800C6814_14
	addiu	$17,$16,32
	lw	$3,20($19)
	nop
	sltiu	$2,$3,6
	beq	$2,$0,$Lvcd_n05_800C6814_32
	lui	$2,%hi(vcd_n05_800C6814_jtbl_800DE720)
	addiu	$2,$2,%lo(vcd_n05_800C6814_jtbl_800DE720)
	sll	$3,$3,2
	addu	$3,$3,$2
	lw	$2,0($3)
	nop
	jr	$2
	nop
$Lvcd_n05_800C6814_0:
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,52
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,34
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+68)
	lh	$5,%lo(godzact_data+68)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,139
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	vcd_n05_800C78C8
	addu	$6,$0,$0
	j	$Lvcd_n05_800C6814_13
	addiu	$2,$0,17
$Lvcd_n05_800C6814_1:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,37
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+74)
	lh	$5,%lo(godzact_data+74)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	lw	$2,2304($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lvcd_n05_800C6814_3
	addu	$4,$16,$0
	lui	$2,%hi(linkvarbuf+28)
	lh	$3,%lo(linkvarbuf+28)($2)
	addiu	$2,$0,9
	bne	$3,$2,$Lvcd_n05_800C6814_2
	addiu	$5,$0,6
	addu	$4,$16,$0
	j	$Lvcd_n05_800C6814_4
	addiu	$6,$0,2
$Lvcd_n05_800C6814_2:
	j	$Lvcd_n05_800C6814_4
	addiu	$6,$0,1
$Lvcd_n05_800C6814_3:
	addiu	$5,$0,5
	addu	$6,$0,$0
$Lvcd_n05_800C6814_4:
	jal	vcd_n05_800C78C8
	nop
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800C6814_5
	addiu	$4,$16,32
	lui	$2,%hi(GodzCommand+12)
	lw	$3,%lo(GodzCommand+12)($2)
	addiu	$2,$0,1
	bne	$3,$2,$Lvcd_n05_800C6814_6
	addiu	$5,$0,139
$Lvcd_n05_800C6814_5:
	addiu	$5,$0,132
$Lvcd_n05_800C6814_6:
	jal	GM_SeSetMode
	addiu	$6,$0,1
	j	$Lvcd_n05_800C6814_13
	addiu	$2,$0,100
$Lvcd_n05_800C6814_7:
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800C6814_8
	addiu	$4,$16,32
	lui	$2,%hi(GodzCommand+12)
	lw	$3,%lo(GodzCommand+12)($2)
	addiu	$2,$0,1
	bne	$3,$2,$Lvcd_n05_800C6814_9
	addiu	$5,$0,139
$Lvcd_n05_800C6814_8:
	addiu	$5,$0,132
$Lvcd_n05_800C6814_9:
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,35
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+70)
	lh	$5,%lo(godzact_data+70)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	vcd_n05_800C78C8
	addu	$6,$0,$0
	j	$Lvcd_n05_800C6814_13
	addiu	$2,$0,36
$Lvcd_n05_800C6814_10:
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,142
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,36
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+72)
	lh	$5,%lo(godzact_data+72)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	vcd_n05_800C78C8
	addu	$6,$0,$0
	j	$Lvcd_n05_800C6814_13
	addiu	$2,$0,37
$Lvcd_n05_800C6814_11:
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,144
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,29
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+58)
	lh	$5,%lo(godzact_data+58)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	j	$Lvcd_n05_800C6814_13
	addiu	$2,$0,67
$Lvcd_n05_800C6814_12:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,30
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+60)
	lh	$5,%lo(godzact_data+60)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$2,$0,15
$Lvcd_n05_800C6814_13:
	sh	$2,2922($16)
$Lvcd_n05_800C6814_14:
	lw	$3,20($19)
	nop
	sltiu	$2,$3,6
	beq	$2,$0,$Lvcd_n05_800C6814_32
	lui	$2,%hi(vcd_n05_800C6814_jtbl_800DE720+24)
	addiu	$2,$2,%lo(vcd_n05_800C6814_jtbl_800DE720+24)
	sll	$3,$3,2
	addu	$3,$3,$2
	lw	$2,0($3)
	nop
	jr	$2
	nop
$Lvcd_n05_800C6814_15:
	slti	$2,$18,12
	beq	$2,$0,$Lvcd_n05_800C6814_16
	addiu	$2,$18,-7
	lhu	$2,78($17)
	nop
	addiu	$2,$2,170
	sh	$2,78($17)
	addiu	$2,$18,-7
$Lvcd_n05_800C6814_16:
	sltiu	$2,$2,23
	beq	$2,$0,$Lvcd_n05_800C6814_17
	slti	$2,$18,20
	jal	GodzAttackTouch
	addu	$4,$16,$0
	slti	$2,$18,20
$Lvcd_n05_800C6814_17:
	beq	$2,$0,$Lvcd_n05_800C6814_32
	addiu	$2,$0,-32767
	j	$Lvcd_n05_800C6814_32
	sh	$2,84($16)
$Lvcd_n05_800C6814_18:
	addiu	$2,$0,58
	bne	$18,$2,$Lvcd_n05_800C6814_21
	slti	$2,$18,15
	addiu	$4,$16,32
	addiu	$5,$0,199
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$4,%hi(godzact_data+108)
	addiu	$4,$4,%lo(godzact_data+108)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(godzact_data+128)
	addiu	$4,$4,%lo(godzact_data+128)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C6814_20
	addiu	$5,$0,8
	bne	$3,$4,$Lvcd_n05_800C6814_19
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C6814_21
	slti	$2,$18,15
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C6814_19:
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
$Lvcd_n05_800C6814_20:
	slti	$2,$18,15
$Lvcd_n05_800C6814_21:
	beq	$2,$0,$Lvcd_n05_800C6814_33
	slti	$2,$18,17
	lhu	$2,72($17)
	nop
	addiu	$2,$2,-30
	j	$Lvcd_n05_800C6814_32
	sh	$2,72($17)
$Lvcd_n05_800C6814_22:
	addiu	$2,$18,-7
	sltiu	$2,$2,23
	beq	$2,$0,$Lvcd_n05_800C6814_23
	slti	$2,$18,15
	jal	GodzAttackTouch
	addu	$4,$16,$0
	slti	$2,$18,15
$Lvcd_n05_800C6814_23:
	beq	$2,$0,$Lvcd_n05_800C6814_24
	addiu	$3,$0,-32767
	lhu	$2,72($17)
	sh	$3,52($17)
	addiu	$2,$2,-30
	sh	$2,72($17)
$Lvcd_n05_800C6814_24:
	addiu	$2,$0,84
	bne	$18,$2,$Lvcd_n05_800C6814_27
	addiu	$2,$0,89
	addiu	$4,$16,32
	addiu	$5,$0,199
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$4,%hi(godzact_data+108)
	addiu	$4,$4,%lo(godzact_data+108)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(godzact_data+128)
	addiu	$4,$4,%lo(godzact_data+128)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C6814_26
	addiu	$5,$0,8
	bne	$3,$4,$Lvcd_n05_800C6814_25
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C6814_27
	addiu	$2,$0,89
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C6814_25:
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
$Lvcd_n05_800C6814_26:
	addiu	$2,$0,89
$Lvcd_n05_800C6814_27:
	bne	$18,$2,$Lvcd_n05_800C6814_33
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
	bne	$2,$0,$Lvcd_n05_800C6814_32
	addiu	$5,$0,8
	bne	$3,$4,$Lvcd_n05_800C6814_28
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C6814_33
	slti	$2,$18,17
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C6814_28:
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
	j	$Lvcd_n05_800C6814_33
	slti	$2,$18,17
$Lvcd_n05_800C6814_29:
	addiu	$2,$18,-7
	sltiu	$2,$2,23
	beq	$2,$0,$Lvcd_n05_800C6814_30
	slti	$2,$18,20
	jal	GodzAttackTouch
	addu	$4,$16,$0
	slti	$2,$18,20
$Lvcd_n05_800C6814_30:
	beq	$2,$0,$Lvcd_n05_800C6814_32
	addiu	$2,$0,-32767
	j	$Lvcd_n05_800C6814_32
	sh	$2,52($17)
$Lvcd_n05_800C6814_31:
	lw	$2,2940($16)
	nop
	ori	$2,$2,0x4
	sw	$2,2940($16)
$Lvcd_n05_800C6814_32:
	slti	$2,$18,17
$Lvcd_n05_800C6814_33:
	bne	$2,$0,$Lvcd_n05_800C6814_34
	nop
	lb	$2,87($17)
	nop
	beq	$2,$0,$Lvcd_n05_800C6814_34
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
$Lvcd_n05_800C6814_34:
	lh	$2,2922($16)
	nop
	bne	$18,$2,$Lvcd_n05_800C6814_36
	addiu	$4,$16,32
	addiu	$5,$0,199
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$4,%hi(godzact_data+108)
	addiu	$4,$4,%lo(godzact_data+108)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(godzact_data+128)
	addiu	$4,$4,%lo(godzact_data+128)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C6814_36
	addiu	$5,$0,8
	bne	$3,$4,$Lvcd_n05_800C6814_35
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C6814_36
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C6814_35:
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
$Lvcd_n05_800C6814_36:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C6814_39
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
	bgtz	$2,$Lvcd_n05_800C6814_37
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C70F4)
	j	$Lvcd_n05_800C6814_38
	addiu	$2,$2,%lo(vcd_n05_800C70F4)
$Lvcd_n05_800C6814_37:
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C6440)
	addiu	$2,$2,%lo(vcd_n05_800C6440)
$Lvcd_n05_800C6814_38:
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C6814_39:
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C6F14
vcd_n05_800C6F14:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$18,24($29)
	addu	$18,$5,$0
	sw	$31,28($29)
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
	bne	$18,$0,$Lvcd_n05_800C6F14_0
	addiu	$17,$16,32
	lw	$3,2268($16)
	addiu	$2,$0,2
	beq	$3,$2,$Lvcd_n05_800C6F14_0
	addu	$4,$17,$0
	jal	GM_SeSet
	addiu	$5,$0,142
$Lvcd_n05_800C6F14_0:
	slti	$2,$18,17
	bne	$2,$0,$Lvcd_n05_800C6F14_1
	nop
	lb	$2,87($17)
	nop
	beq	$2,$0,$Lvcd_n05_800C6F14_1
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
$Lvcd_n05_800C6F14_1:
	lh	$2,2272($16)
	nop
	slti	$2,$2,39
	beq	$2,$0,$Lvcd_n05_800C6F14_5
	nop
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C6F14_6
	nop
	lw	$3,2268($16)
	nop
	slti	$2,$3,3
	beq	$2,$0,$Lvcd_n05_800C6F14_3
	addiu	$2,$0,1
	bne	$3,$2,$Lvcd_n05_800C6F14_2
	addiu	$4,$16,156
	addiu	$2,$0,41
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+82)
	lh	$5,%lo(godzact_data+82)($2)
	j	$Lvcd_n05_800C6F14_4
	addu	$6,$0,$0
$Lvcd_n05_800C6F14_2:
	addiu	$2,$0,39
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+78)
	lh	$5,%lo(godzact_data+78)($2)
	j	$Lvcd_n05_800C6F14_4
	addu	$6,$0,$0
$Lvcd_n05_800C6F14_3:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,40
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+80)
	lh	$5,%lo(godzact_data+80)($2)
$Lvcd_n05_800C6F14_4:
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	j	$Lvcd_n05_800C6F14_6
	nop
$Lvcd_n05_800C6F14_5:
	lb	$2,87($17)
	nop
	beq	$2,$0,$Lvcd_n05_800C6F14_6
	addu	$4,$17,$0
	lw	$3,2304($16)
	addiu	$2,$0,1
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
	jal	GM_SeSet
	addiu	$5,$0,51
	addu	$4,$16,$0
	addiu	$5,$0,6
	jal	vcd_n05_800C78C8
	addiu	$6,$0,1
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C70F4)
	addiu	$2,$2,%lo(vcd_n05_800C70F4)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C6F14_6:
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
	.globl	vcd_n05_800C70F4
vcd_n05_800C70F4:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lw	$2,2940($16)
	addu	$17,$5,$0
	ori	$2,$2,0x40
	bne	$17,$0,$Lvcd_n05_800C70F4_3
	sw	$2,2940($16)
	lw	$3,2268($16)
	nop
	slti	$2,$3,3
	beq	$2,$0,$Lvcd_n05_800C70F4_1
	addiu	$2,$0,1
	bne	$3,$2,$Lvcd_n05_800C70F4_0
	addiu	$4,$16,156
	addiu	$2,$0,51
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+102)
	lh	$5,%lo(godzact_data+102)($2)
	j	$Lvcd_n05_800C70F4_2
	addu	$6,$0,$0
$Lvcd_n05_800C70F4_0:
	addiu	$2,$0,49
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+98)
	lh	$5,%lo(godzact_data+98)($2)
	j	$Lvcd_n05_800C70F4_2
	addu	$6,$0,$0
$Lvcd_n05_800C70F4_1:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,50
	sh	$2,2272($16)
	lui	$2,%hi(godzact_data+100)
	lh	$5,%lo(godzact_data+100)($2)
$Lvcd_n05_800C70F4_2:
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$16,32
	jal	GM_ConfigControlAttribute
	addu	$5,$0,$0
	sw	$0,2980($16)
$Lvcd_n05_800C70F4_3:
	slti	$2,$17,31
	bne	$2,$0,$Lvcd_n05_800C70F4_4
	addiu	$4,$16,156
	addu	$5,$0,$0
	lui	$2,%hi(vcd_n05_800C71D8)
	addiu	$2,$2,%lo(vcd_n05_800C71D8)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$Lvcd_n05_800C70F4_4:
	lw	$31,24($29)
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
	.globl	vcd_n05_800C71D8
vcd_n05_800C71D8:
	addiu	$29,$29,-24
	sw	$31,16($29)
	lw	$2,2940($4)
	nop
	ori	$2,$2,0x40
	bne	$5,$0,$Lvcd_n05_800C71D8_0
	sw	$2,2940($4)
	lui	$2,%hi(GODZ_NO_POINT)
	lui	$3,%hi(GodzCommand)
	addiu	$9,$2,%lo(GODZ_NO_POINT)
	lwl	$6,3($9)
	lwr	$6,0($9)
	lwl	$7,7($9)
	lwr	$7,4($9)
	swl	$6,35($4)
	swr	$6,32($4)
	swl	$7,39($4)
	swr	$7,36($4)
	lb	$2,2948($4)
	addiu	$3,$3,%lo(GodzCommand)
	sll	$2,$2,4
	addu	$2,$2,$3
	addiu	$3,$0,1
	sw	$3,148($2)
	lw	$4,3148($4)
	nop
	bltz	$4,$Lvcd_n05_800C71D8_0
	nop
	jal	GCL_ExecProc
	addu	$5,$0,$0
$Lvcd_n05_800C71D8_0:
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
	.globl	vcd_n05_800C7260
vcd_n05_800C7260:
	addiu	$5,$4,32
	lw	$2,2940($4)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lvcd_n05_800C7260_11
	addu	$6,$5,$0
	lui	$2,%hi(GodzCommand+12)
	lw	$3,%lo(GodzCommand+12)($2)
	addiu	$2,$0,2
	bne	$3,$2,$Lvcd_n05_800C7260_3
	nop
	lh	$2,4($5)
	nop
	slti	$2,$2,-18500
	beq	$2,$0,$Lvcd_n05_800C7260_2
	nop
	lh	$3,32($4)
	nop
	slti	$2,$3,-12500
	bne	$2,$0,$Lvcd_n05_800C7260_0
	addiu	$2,$0,-12500
	slti	$2,$3,12501
	bne	$2,$0,$Lvcd_n05_800C7260_1
	addiu	$2,$0,12500
$Lvcd_n05_800C7260_0:
	sh	$2,32($4)
	sh	$0,68($5)
$Lvcd_n05_800C7260_1:
	lh	$2,4($6)
	nop
	slti	$2,$2,-27500
	beq	$2,$0,$Lvcd_n05_800C7260_11
	addiu	$2,$0,-27500
	j	$Lvcd_n05_800C7260_10
	sh	$2,4($6)
$Lvcd_n05_800C7260_2:
	lh	$3,32($4)
	nop
	slti	$2,$3,-3000
	bne	$2,$0,$Lvcd_n05_800C7260_7
	addiu	$2,$0,-3000
	slti	$2,$3,4501
	bne	$2,$0,$Lvcd_n05_800C7260_9
	addiu	$2,$0,4500
	j	$Lvcd_n05_800C7260_8
	sh	$2,32($4)
$Lvcd_n05_800C7260_3:
	lh	$2,4($5)
	nop
	slti	$2,$2,-18500
	beq	$2,$0,$Lvcd_n05_800C7260_6
	nop
	lh	$3,32($4)
	nop
	slti	$2,$3,-1000
	bne	$2,$0,$Lvcd_n05_800C7260_4
	addiu	$2,$0,-950
	slti	$2,$3,11501
	bne	$2,$0,$Lvcd_n05_800C7260_5
	addiu	$2,$0,11500
$Lvcd_n05_800C7260_4:
	sh	$2,32($4)
	sh	$0,68($5)
$Lvcd_n05_800C7260_5:
	lh	$2,4($6)
	nop
	slti	$2,$2,-23500
	beq	$2,$0,$Lvcd_n05_800C7260_11
	addiu	$2,$0,-23500
	j	$Lvcd_n05_800C7260_10
	sh	$2,4($6)
$Lvcd_n05_800C7260_6:
	lh	$3,32($4)
	nop
	slti	$2,$3,-1000
	bne	$2,$0,$Lvcd_n05_800C7260_7
	addiu	$2,$0,-950
	slti	$2,$3,1001
	bne	$2,$0,$Lvcd_n05_800C7260_9
	addiu	$2,$0,950
$Lvcd_n05_800C7260_7:
	sh	$2,32($4)
$Lvcd_n05_800C7260_8:
	sh	$0,68($5)
$Lvcd_n05_800C7260_9:
	lh	$2,4($6)
	nop
	slti	$2,$2,-3499
	bne	$2,$0,$Lvcd_n05_800C7260_11
	addiu	$2,$0,-3500
	sh	$2,4($6)
$Lvcd_n05_800C7260_10:
	sh	$0,72($5)
$Lvcd_n05_800C7260_11:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C73B0
vcd_n05_800C73B0:
	addiu	$29,$29,-40
	sw	$17,20($29)
	addu	$17,$4,$0
	addu	$3,$0,$0
	addiu	$5,$0,1
	sw	$31,36($29)
	sw	$20,32($29)
	sw	$19,28($29)
	sw	$18,24($29)
	sw	$16,16($29)
	sw	$0,2912($17)
	sh	$0,2972($17)
$Lvcd_n05_800C73B0_0:
	lw	$2,2304($4)
	addiu	$3,$3,1
	sh	$5,0($2)
	slti	$2,$3,5
	bne	$2,$0,$Lvcd_n05_800C73B0_0
	addiu	$4,$4,4
	addiu	$20,$17,156
	sw	$0,2300($17)
	sw	$0,2940($17)
	sw	$0,3140($17)
	lh	$3,24($20)
	lw	$2,2544($17)
	nop
	mult	$3,$2
	addiu	$19,$17,2248
	lw	$16,2284($17)
	mflo	$3
	bgez	$3,$Lvcd_n05_800C73B0_1
	addiu	$18,$17,32
	addiu	$3,$3,4095
$Lvcd_n05_800C73B0_1:
	lhu	$2,120($18)
	sra	$3,$3,12
	sh	$3,50($18)
	addiu	$2,$2,750
	sh	$2,52($18)
	lw	$5,2292($17)
	nop
	addiu	$2,$5,1
	bne	$16,$0,$Lvcd_n05_800C73B0_2
	sw	$2,2292($17)
	lui	$2,%hi(vcd_n05_800C4DB8)
	addiu	$16,$2,%lo(vcd_n05_800C4DB8)
	sw	$16,2284($17)
$Lvcd_n05_800C73B0_2:
	jalr	$31,$16
	addu	$4,$17,$0
	lw	$16,2288($17)
	nop
	beq	$16,$0,$Lvcd_n05_800C73B0_3
	addu	$4,$17,$0
	lw	$5,2296($17)
	nop
	addiu	$2,$5,1
	jalr	$31,$16
	sw	$2,2296($17)
$Lvcd_n05_800C73B0_3:
	lh	$2,30($19)
	nop
	bne	$2,$0,$Lvcd_n05_800C73B0_4
	addiu	$2,$0,-1
	lh	$4,54($18)
	lh	$5,28($19)
	jal	GV_NearExp2
	nop
	j	$Lvcd_n05_800C73B0_5
	sh	$2,54($18)
$Lvcd_n05_800C73B0_4:
	sh	$2,54($18)
$Lvcd_n05_800C73B0_5:
	lw	$2,2304($17)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x4
	beq	$2,$0,$Lvcd_n05_800C73B0_6
	addiu	$2,$0,1
	lw	$3,2540($17)
	j	$Lvcd_n05_800C73B0_7
	sw	$2,8($3)
$Lvcd_n05_800C73B0_6:
	lw	$2,2540($17)
	nop
	sw	$0,8($2)
$Lvcd_n05_800C73B0_7:
	lui	$2,%hi(GODZ_GameFlag)
	lw	$2,%lo(GODZ_GameFlag)($2)
	nop
	slti	$2,$2,7
	bne	$2,$0,$Lvcd_n05_800C73B0_9
	nop
	lh	$3,24($20)
	lw	$2,2544($17)
	nop
	mult	$3,$2
	mflo	$2
	bgez	$2,$Lvcd_n05_800C73B0_8
	nop
	addiu	$2,$2,4095
$Lvcd_n05_800C73B0_8:
	sra	$2,$2,12
	j	$Lvcd_n05_800C73B0_11
	sh	$2,2($18)
$Lvcd_n05_800C73B0_9:
	lh	$2,4($19)
	nop
	bgez	$2,$Lvcd_n05_800C73B0_10
	nop
	lb	$2,87($18)
	nop
	beq	$2,$0,$Lvcd_n05_800C73B0_10
	nop
	sh	$0,4($19)
$Lvcd_n05_800C73B0_10:
	lhu	$2,4($19)
	nop
	addiu	$2,$2,-16
	sh	$2,4($19)
	sh	$2,70($18)
$Lvcd_n05_800C73B0_11:
	lw	$2,2936($17)
	nop
	blez	$2,$Lvcd_n05_800C73B0_12
	addiu	$2,$2,-1
	sw	$2,2936($17)
$Lvcd_n05_800C73B0_12:
	lb	$3,2949($17)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800C73B0_14
	lui	$2,%hi(GODZ_GameFlag)
	lw	$2,%lo(GODZ_GameFlag)($2)
	nop
	slti	$2,$2,4
	bne	$2,$0,$Lvcd_n05_800C73B0_18
	addu	$3,$0,$0
	addiu	$5,$0,1
	addu	$4,$17,$0
$Lvcd_n05_800C73B0_13:
	lw	$2,2304($4)
	addiu	$3,$3,1
	sh	$5,0($2)
	slti	$2,$3,5
	bne	$2,$0,$Lvcd_n05_800C73B0_13
	addiu	$4,$4,4
	j	$Lvcd_n05_800C73B0_18
	nop
$Lvcd_n05_800C73B0_14:
	lw	$3,%lo(GODZ_GameFlag)($2)
	addiu	$2,$0,5
	bne	$3,$2,$Lvcd_n05_800C73B0_16
	slti	$2,$3,6
	addu	$3,$0,$0
	addiu	$5,$0,3
	addu	$4,$17,$0
$Lvcd_n05_800C73B0_15:
	lw	$2,2304($4)
	addiu	$3,$3,1
	sh	$5,0($2)
	slti	$2,$3,5
	bne	$2,$0,$Lvcd_n05_800C73B0_15
	addiu	$4,$4,4
	j	$Lvcd_n05_800C73B0_18
	nop
$Lvcd_n05_800C73B0_16:
	bne	$2,$0,$Lvcd_n05_800C73B0_18
	addu	$3,$0,$0
	addiu	$5,$0,1
	addu	$4,$17,$0
$Lvcd_n05_800C73B0_17:
	lw	$2,2304($4)
	addiu	$3,$3,1
	sh	$5,0($2)
	slti	$2,$3,5
	bne	$2,$0,$Lvcd_n05_800C73B0_17
	addiu	$4,$4,4
$Lvcd_n05_800C73B0_18:
	jal	vcd_n05_800C7260
	addu	$4,$17,$0
	lw	$31,36($29)
	lw	$20,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7658
vcd_n05_800C7658:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$17,28($29)
	addu	$17,$5,$0
	bne	$17,$0,$Lvcd_n05_800C7658_0
	sw	$31,32($29)
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$7,$0,4
	addiu	$2,$0,9
	sh	$2,2274($16)
	lui	$2,%hi(godzact_data+18)
	lh	$5,%lo(godzact_data+18)($2)
	addiu	$2,$0,1022
	jal	GM_ConfigObjectOverride
	sw	$2,16($29)
$Lvcd_n05_800C7658_0:
	lw	$2,2888($16)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$Lvcd_n05_800C7658_1
	slti	$2,$17,4
	addiu	$4,$16,156
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data)
	sh	$0,2274($16)
	lh	$5,%lo(godzact_data)($2)
	addiu	$7,$0,4
	jal	GM_ConfigObjectOverride
	sw	$0,16($29)
	sw	$0,2288($16)
	sw	$0,2296($16)
	sh	$0,2274($16)
	sh	$0,112($16)
	j	$Lvcd_n05_800C7658_4
	sh	$0,108($16)
$Lvcd_n05_800C7658_1:
	beq	$2,$0,$Lvcd_n05_800C7658_2
	sll	$3,$17,8
	lhu	$2,42($16)
	j	$Lvcd_n05_800C7658_3
	subu	$2,$2,$3
$Lvcd_n05_800C7658_2:
	lhu	$2,42($16)
	nop
	addiu	$2,$2,-1024
$Lvcd_n05_800C7658_3:
	andi	$2,$2,0xfff
	sh	$2,2968($16)
$Lvcd_n05_800C7658_4:
	lw	$31,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7724
vcd_n05_800C7724:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$17,28($29)
	addu	$17,$5,$0
	bne	$17,$0,$Lvcd_n05_800C7724_0
	sw	$31,32($29)
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$7,$0,4
	addiu	$2,$0,10
	sh	$2,2274($16)
	lui	$2,%hi(godzact_data+20)
	lh	$5,%lo(godzact_data+20)($2)
	addiu	$2,$0,1022
	jal	GM_ConfigObjectOverride
	sw	$2,16($29)
$Lvcd_n05_800C7724_0:
	lw	$2,2888($16)
	nop
	andi	$2,$2,0x2
	bne	$2,$0,$Lvcd_n05_800C7724_1
	slti	$2,$17,4
	addiu	$4,$16,156
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data)
	sh	$0,2274($16)
	lh	$5,%lo(godzact_data)($2)
	addiu	$7,$0,4
	jal	GM_ConfigObjectOverride
	sw	$0,16($29)
	sw	$0,2288($16)
	sw	$0,2296($16)
	sh	$0,2274($16)
	sh	$0,112($16)
	j	$Lvcd_n05_800C7724_4
	sh	$0,108($16)
$Lvcd_n05_800C7724_1:
	beq	$2,$0,$Lvcd_n05_800C7724_2
	sll	$3,$17,8
	lhu	$2,42($16)
	j	$Lvcd_n05_800C7724_3
	addu	$2,$2,$3
$Lvcd_n05_800C7724_2:
	lhu	$2,42($16)
	nop
	addiu	$2,$2,1024
$Lvcd_n05_800C7724_3:
	andi	$2,$2,0xfff
	sh	$2,2968($16)
$Lvcd_n05_800C7724_4:
	lw	$31,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C77F0
vcd_n05_800C77F0:
	addiu	$29,$29,-32
	sw	$16,24($29)
	addu	$16,$4,$0
	addiu	$2,$0,3000
	sw	$31,28($29)
	bne	$5,$0,$Lvcd_n05_800C77F0_0
	sh	$2,2972($16)
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$7,$0,4
	addiu	$2,$0,11
	sh	$2,2274($16)
	lui	$2,%hi(godzact_data+22)
	lh	$5,%lo(godzact_data+22)($2)
	addiu	$2,$0,1022
	jal	GM_ConfigObjectOverride
	sw	$2,16($29)
$Lvcd_n05_800C77F0_0:
	lw	$2,2888($16)
	nop
	andi	$2,$2,0x4
	bne	$2,$0,$Lvcd_n05_800C77F0_1
	addiu	$4,$16,156
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data)
	sh	$0,2274($16)
	lh	$5,%lo(godzact_data)($2)
	addiu	$7,$0,4
	jal	GM_ConfigObjectOverride
	sw	$0,16($29)
	sw	$0,2288($16)
	sw	$0,2296($16)
	sh	$0,2274($16)
	sh	$0,112($16)
	sh	$0,108($16)
$Lvcd_n05_800C77F0_1:
	lw	$31,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7888
vcd_n05_800C7888:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7890
vcd_n05_800C7890:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7898
vcd_n05_800C7898:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C78A0
vcd_n05_800C78A0:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C78A8
vcd_n05_800C78A8:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C78B0
vcd_n05_800C78B0:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C78B8
vcd_n05_800C78B8:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C78C0
vcd_n05_800C78C0:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C78C8
vcd_n05_800C78C8:
	addiu	$29,$29,-56
	sw	$16,48($29)
	addu	$16,$6,$0
	sll	$2,$5,1
	addu	$2,$2,$5
	sll	$2,$2,3
	subu	$2,$2,$5
	sll	$2,$2,2
	sw	$31,52($29)
	lw	$4,156($4)
	addiu	$2,$2,72
	jal	DG_SetPos
	addu	$4,$4,$2
	lui	$4,%hi(godzact_data+148)
	jal	DG_MovePos
	addiu	$4,$4,%lo(godzact_data+148)
	lui	$4,%hi(godzact_data+156)
	jal	DG_RotatePos
	addiu	$4,$4,%lo(godzact_data+156)
	jal	ReadRotMatrix
	addiu	$4,$29,16
	addiu	$4,$29,16
	jal	NewBlood
	addu	$5,$16,$0
	lw	$31,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7938
vcd_n05_800C7938:
	addiu	$29,$29,-64
	sw	$31,56($29)
	lw	$4,156($4)
	jal	DG_SetPos
	addiu	$4,$4,164
	lui	$4,%hi(godzact_data+164)
	jal	DG_MovePos
	addiu	$4,$4,%lo(godzact_data+164)
	lui	$4,%hi(godzact_data+172)
	jal	DG_RotatePos
	addiu	$4,$4,%lo(godzact_data+172)
	jal	ReadRotMatrix
	addiu	$4,$29,16
	lhu	$2,36($29)
	lhu	$3,40($29)
	lhu	$5,44($29)
	addiu	$4,$29,48
	sh	$2,48($29)
	sh	$3,50($29)
	jal	AN_Fog
	sh	$5,52($29)
	lw	$31,56($29)
	nop
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C799C
vcd_n05_800C799C:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	lui	$3,%hi(GM_PlayerMap)
	sw	$31,28($29)
	sw	$18,24($29)
	sw	$17,20($29)
	lw	$2,76($16)
	lw	$3,%lo(GM_PlayerMap)($3)
	lw	$2,0($2)
	nop
	and	$2,$2,$3
	beq	$2,$0,$Lvcd_n05_800C799C_3
	addu	$18,$5,$0
	lw	$2,156($16)
	bne	$18,$0,$Lvcd_n05_800C799C_0
	addiu	$17,$2,624
	addiu	$4,$16,32
	j	$Lvcd_n05_800C799C_1
	addiu	$5,$0,138
$Lvcd_n05_800C799C_0:
	addiu	$4,$16,32
	addiu	$5,$0,140
$Lvcd_n05_800C799C_1:
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lw	$2,2936($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C799C_2
	addu	$4,$17,$0
	lw	$4,2928($16)
	jal	GV_DestroyActor
	nop
	addu	$4,$17,$0
$Lvcd_n05_800C799C_2:
	jal	vcd_n05_800C89A0
	addu	$5,$18,$0
	sw	$2,2928($16)
	addiu	$2,$0,30
	sw	$2,2936($16)
$Lvcd_n05_800C799C_3:
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
	.globl	vcd_n05_800C7A48
vcd_n05_800C7A48:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	addiu	$2,$0,1
	sw	$31,24($29)
	sw	$16,16($29)
	lh	$3,2272($17)
	lh	$16,402($17)
	bne	$3,$2,$Lvcd_n05_800C7A48_3
	nop
	bne	$16,$3,$Lvcd_n05_800C7A48_1
	addiu	$4,$17,32
	addiu	$5,$0,198
	jal	GM_SeSetMode
	addu	$6,$2,$0
	lui	$4,%hi(godzact_data+196)
	addiu	$4,$4,%lo(godzact_data+196)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(godzact_data+204)
	addiu	$4,$4,%lo(godzact_data+204)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C7A48_8
	addiu	$5,$0,8
	bne	$3,$4,$Lvcd_n05_800C7A48_0
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C7A48_8
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C7A48_0:
	sw	$5,%lo(GM_NoiseLength)($2)
	lui	$2,%hi(GM_NoisePosition)
	j	$Lvcd_n05_800C7A48_7
	sw	$4,%lo(GM_NoisePower)($6)
$Lvcd_n05_800C7A48_1:
	addiu	$2,$0,71
	bne	$16,$2,$Lvcd_n05_800C7A48_8
	addiu	$5,$0,197
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$4,%hi(godzact_data+196)
	addiu	$4,$4,%lo(godzact_data+196)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(godzact_data+204)
	addiu	$4,$4,%lo(godzact_data+204)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C7A48_8
	addiu	$5,$0,8
	bne	$3,$4,$Lvcd_n05_800C7A48_2
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C7A48_8
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C7A48_2:
	sw	$5,%lo(GM_NoiseLength)($2)
	lui	$2,%hi(GM_NoisePosition)
	j	$Lvcd_n05_800C7A48_7
	sw	$4,%lo(GM_NoisePower)($6)
$Lvcd_n05_800C7A48_3:
	addiu	$2,$0,2
	bne	$3,$2,$Lvcd_n05_800C7A48_8
	addiu	$2,$0,16
	bne	$16,$2,$Lvcd_n05_800C7A48_5
	addiu	$2,$0,8
	addiu	$4,$17,32
	addiu	$5,$0,198
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$4,$0,255
	lui	$6,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($6)
	nop
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C7A48_8
	addiu	$5,$0,8
	bne	$3,$4,$Lvcd_n05_800C7A48_4
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$5,$2
	bne	$2,$0,$Lvcd_n05_800C7A48_8
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C7A48_4:
	sw	$5,%lo(GM_NoiseLength)($2)
	lui	$2,%hi(GM_NoisePosition)
	j	$Lvcd_n05_800C7A48_7
	sw	$4,%lo(GM_NoisePower)($6)
$Lvcd_n05_800C7A48_5:
	bne	$16,$2,$Lvcd_n05_800C7A48_8
	addiu	$4,$17,32
	addiu	$5,$0,197
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$5,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($5)
	addiu	$4,$0,255
	slt	$2,$4,$3
	bne	$2,$0,$Lvcd_n05_800C7A48_8
	nop
	bne	$3,$4,$Lvcd_n05_800C7A48_6
	lui	$2,%hi(GM_NoiseLength)
	lw	$2,%lo(GM_NoiseLength)($2)
	nop
	slt	$2,$16,$2
	bne	$2,$0,$Lvcd_n05_800C7A48_8
	lui	$2,%hi(GM_NoiseLength)
$Lvcd_n05_800C7A48_6:
	sw	$16,%lo(GM_NoiseLength)($2)
	lui	$2,%hi(GM_NoisePosition)
	sw	$4,%lo(GM_NoisePower)($5)
$Lvcd_n05_800C7A48_7:
	addiu	$10,$2,%lo(GM_NoisePosition)
	lwl	$7,35($17)
	lwr	$7,32($17)
	lwl	$8,39($17)
	lwr	$8,36($17)
	swl	$7,3($10)
	swr	$7,0($10)
	swl	$8,7($10)
	swr	$8,4($10)
$Lvcd_n05_800C7A48_8:
	lw	$31,24($29)
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
	.globl	vcd_n05_800C7C60
vcd_n05_800C7C60:
	addiu	$29,$29,-32
	lui	$2,%hi(GodzCommand+32)
	lw	$3,%lo(GodzCommand+32)($2)
	addiu	$2,$0,1
	beq	$3,$2,$Lvcd_n05_800C7C60_6
	sw	$31,24($29)
	lui	$3,%hi(GM_PlayerMap)
	lw	$2,76($4)
	lw	$3,%lo(GM_PlayerMap)($3)
	lw	$2,0($2)
	nop
	and	$2,$2,$3
	beq	$2,$0,$Lvcd_n05_800C7C60_6
	addiu	$2,$0,20
	lh	$3,2274($4)
	nop
	bne	$3,$2,$Lvcd_n05_800C7C60_0
	addiu	$2,$0,22
	lh	$3,426($4)
	j	$Lvcd_n05_800C7C60_4
	addiu	$2,$0,31
$Lvcd_n05_800C7C60_0:
	bne	$3,$2,$Lvcd_n05_800C7C60_1
	addiu	$2,$0,19
	lh	$3,426($4)
	addiu	$2,$0,15
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,35
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,50
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,60
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,70
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,74
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,78
	j	$Lvcd_n05_800C7C60_4
	nop
$Lvcd_n05_800C7C60_1:
	bne	$3,$2,$Lvcd_n05_800C7C60_2
	lui	$2,%hi(GV_Time)
	lh	$3,426($4)
	addiu	$2,$0,30
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,40
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,50
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,60
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,70
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,80
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,90
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,95
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,100
	beq	$3,$2,$Lvcd_n05_800C7C60_5
	addiu	$2,$0,105
	j	$Lvcd_n05_800C7C60_4
	nop
$Lvcd_n05_800C7C60_2:
	lw	$5,%lo(GV_Time)($2)
	nop
	bgez	$5,$Lvcd_n05_800C7C60_3
	addu	$3,$5,$0
	addiu	$3,$5,63
$Lvcd_n05_800C7C60_3:
	sra	$3,$3,6
	sll	$3,$3,6
	lb	$2,2948($4)
	subu	$3,$5,$3
	sll	$2,$2,4
$Lvcd_n05_800C7C60_4:
	bne	$3,$2,$Lvcd_n05_800C7C60_6
	nop
$Lvcd_n05_800C7C60_5:
	lw	$4,156($4)
	jal	AN_Breath
	addiu	$4,$4,624
$Lvcd_n05_800C7C60_6:
	lw	$31,24($29)
	nop
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7DA8
vcd_n05_800C7DA8:
	addiu	$29,$29,-24
	addu	$5,$4,$0
	sw	$31,16($29)
	lh	$3,2974($5)
	addiu	$2,$0,2
	bne	$3,$2,$Lvcd_n05_800C7DA8_0
	lui	$4,%hi(GM_PlayerPosition)
	addiu	$4,$4,%lo(GM_PlayerPosition)
	addiu	$5,$5,32
	jal	NewLSight
	addiu	$6,$0,143
$Lvcd_n05_800C7DA8_0:
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
	.globl	vcd_n05_800C7DE4
vcd_n05_800C7DE4:
	addiu	$29,$29,-80
	sw	$18,72($29)
	addu	$18,$4,$0
	lui	$2,%hi(DG_ZeroVector)
	sw	$31,76($29)
	sw	$17,68($29)
	sw	$16,64($29)
	addiu	$10,$2,%lo(DG_ZeroVector)
	lwl	$3,3($10)
	lwr	$3,0($10)
	lwl	$8,7($10)
	lwr	$8,4($10)
	swl	$3,27($29)
	swr	$3,24($29)
	swl	$8,31($29)
	swr	$8,28($29)
	jal	GV_RandS
	addiu	$4,$0,16
	addiu	$4,$0,128
	jal	GV_RandU
	sh	$2,24($29)
	sh	$2,28($29)
	lw	$2,156($18)
	nop
	addiu	$17,$2,440
	jal	DG_SetPos
	addu	$4,$17,$0
	lui	$4,%hi(godzact_data+212)
	jal	DG_MovePos
	addiu	$4,$4,%lo(godzact_data+212)
	jal	DG_RotatePos
	addiu	$4,$29,24
	addiu	$16,$29,32
	jal	ReadRotMatrix
	addu	$4,$16,$0
	lui	$2,%hi(GV_Time)
	lw	$2,%lo(GV_Time)($2)
	nop
	andi	$2,$2,0x3
	beq	$2,$0,$Lvcd_n05_800C7DE4_0
	addiu	$2,$0,1
	j	$Lvcd_n05_800C7DE4_1
	sw	$2,16($29)
$Lvcd_n05_800C7DE4_0:
	sw	$0,16($29)
$Lvcd_n05_800C7DE4_1:
	addu	$4,$16,$0
	addiu	$5,$0,2
	addiu	$6,$0,1
	jal	NewBulletEnemy
	addu	$7,$0,$0
	addiu	$4,$18,32
	addiu	$5,$0,45
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addu	$4,$17,$0
	jal	AN_BulletSmoke
	addu	$5,$0,$0
	jal	AN_FamasFlash
	addiu	$4,$29,32
	addu	$4,$18,$0
	lui	$5,%hi(vcd_n05_800C7DE4)
	jal	vcd_n05_800C7F3C
	addiu	$5,$5,%lo(vcd_n05_800C7DE4)
	lw	$31,76($29)
	lw	$18,72($29)
	lw	$17,68($29)
	lw	$16,64($29)
	jr	$31
	addiu	$29,$29,80
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7EF4
vcd_n05_800C7EF4:
	addu	$6,$0,$0
	lui	$2,%hi(godzact_data+180)
	addiu	$2,$2,%lo(godzact_data+180)
	sll	$5,$5,2
	addu	$3,$5,$2
$Lvcd_n05_800C7EF4_0:
	lw	$2,2832($4)
	nop
	bne	$2,$0,$Lvcd_n05_800C7EF4_1
	addiu	$6,$6,1
	lw	$3,0($3)
	addiu	$2,$0,1
	jr	$31
	sw	$3,2832($4)
$Lvcd_n05_800C7EF4_1:
	slti	$2,$6,8
	bne	$2,$0,$Lvcd_n05_800C7EF4_0
	addiu	$4,$4,4
	jr	$31
	addu	$2,$0,$0
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7F3C
vcd_n05_800C7F3C:
	addu	$3,$0,$0
$Lvcd_n05_800C7F3C_0:
	lw	$2,2832($4)
	nop
	bne	$2,$5,$Lvcd_n05_800C7F3C_1
	addiu	$3,$3,1
	sw	$0,2832($4)
	jr	$31
	addiu	$2,$0,1
$Lvcd_n05_800C7F3C_1:
	slti	$2,$3,8
	bne	$2,$0,$Lvcd_n05_800C7F3C_0
	addiu	$4,$4,4
	jr	$31
	addu	$2,$0,$0
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C7F70
vcd_n05_800C7F70:
	addiu	$29,$29,-32
	sw	$18,24($29)
	addu	$18,$4,$0
	sw	$17,20($29)
	addu	$17,$0,$0
	sw	$16,16($29)
	addu	$16,$18,$0
	sw	$31,28($29)
$Lvcd_n05_800C7F70_0:
	lw	$2,2832($16)
	nop
	beq	$2,$0,$Lvcd_n05_800C7F70_1
	nop
	jalr	$31,$2
	addu	$4,$18,$0
$Lvcd_n05_800C7F70_1:
	addiu	$17,$17,1
	slti	$2,$17,8
	bne	$2,$0,$Lvcd_n05_800C7F70_0
	addiu	$16,$16,4
	lw	$31,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
godz_str_okiagari:
	.ascii	"okiagari end!! %d !!!\n"
	.byte	0
	.align	2
godz_str_turn:
	.ascii	" turn = %d rot = %d \n"
	.byte	0
	.word	0			# (the original has a zero word in front of the table)
	.align	2
vcd_n05_800C6814_jtbl_800DE720:
	.word	$Lvcd_n05_800C6814_0
	.word	$Lvcd_n05_800C6814_1
	.word	$Lvcd_n05_800C6814_10
	.word	$Lvcd_n05_800C6814_7
	.word	$Lvcd_n05_800C6814_11
	.word	$Lvcd_n05_800C6814_12
	.word	$Lvcd_n05_800C6814_15
	.word	$Lvcd_n05_800C6814_18
	.word	$Lvcd_n05_800C6814_29
	.word	$Lvcd_n05_800C6814_22
	.word	$Lvcd_n05_800C6814_31
	.word	$Lvcd_n05_800C6814_31
	.align	2
	.data
	.align	2
godzact_data:
	.word	0x00140013
	.word	0x0016000A
	.word	0x00220009
	.word	0x00240023
	.word	0x000D002D
	.word	0x001A000C
	.word	0x000E000F
	.word	0x001B0010
	.word	0x002E0008
	.word	0x00150032
	.word	0x001F001E
	.word	0x00210020
	.word	0x00340025
	.word	0x00190035
	.word	0x00020005
	.word	0x0004002A
	.word	0x00280027
	.word	0x00070006
	.word	0x00030026
	.word	0x00110029
	.word	0x002B0012
	.word	0x00180017
	.word	0x001D001C
	.word	0x00010000
	.word	0x00110033
	.word	0x002B0012
	.word	0x00000016
	.word	0x037F0300
	.word	0x037F0300
	.word	0x037F0300
	.word	0x037F0300
	.word	0x00000000
	.word	0x04E60278
	.word	0x04FF04B4
	.word	0x048C06C8
	.word	0x0A3C0664
	.word	0x00000000
	.word	0x00000000
	.word	0x00000064
	.word	0x0000FC00
	.word	0x00000000
	.word	0x00000000
	.word	0x00000064
	.word	0x0000FC00
	.word	0x00000000
	.word	vcd_n05_800C7A48
	.word	vcd_n05_800C7C60
	.word	vcd_n05_800C7DA8
	.word	vcd_n05_800C7DE4
	.word	0x047F0200
	.word	0x00000000
	.word	0x067803B4
	.word	0x0000063C
	.word	0xFE0C0005
	.word	0x00000050
	.text
