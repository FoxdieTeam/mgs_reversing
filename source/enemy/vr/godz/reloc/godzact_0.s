	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	GodzAct_800C5440
GodzAct_800C5440:
	addiu	$29,$29,-40
	sw	$18,32($29)
	addu	$18,$4,$0
	sw	$31,36($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$2,2940($18)
	addu	$16,$5,$0
	ori	$2,$2,0x40
	bne	$16,$0,$LGodzAct_800C5440_0
	sw	$2,2940($18)
	addiu	$4,$18,156
	addu	$6,$0,$0
	lui	$2,%hi(GodzActTable)
	sh	$0,2272($18)
	lh	$5,%lo(GodzActTable)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
$LGodzAct_800C5440_0:
	addiu	$2,$0,30
	bne	$16,$2,$LGodzAct_800C5440_3
	addiu	$2,$0,35
	lb	$3,2949($18)
	addiu	$2,$0,71
	bne	$3,$2,$LGodzAct_800C5440_1
	addiu	$4,$18,156
	addu	$6,$0,$0
	addiu	$2,$0,13
	sh	$2,2272($18)
	lui	$2,%hi(GodzActTable+26)
	lh	$5,%lo(GodzActTable+26)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$18,32
	j	$LGodzAct_800C5440_2
	addiu	$5,$0,135
$LGodzAct_800C5440_1:
	addu	$6,$0,$0
	addiu	$2,$0,12
	sh	$2,2272($18)
	lui	$2,%hi(GodzActTable+24)
	lh	$5,%lo(GodzActTable+24)($2)
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addiu	$4,$18,32
	addiu	$5,$0,128
$LGodzAct_800C5440_2:
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,35
$LGodzAct_800C5440_3:
	beq	$16,$2,$LGodzAct_800C5440_4
	addiu	$2,$0,40
	beq	$16,$2,$LGodzAct_800C5440_4
	addiu	$2,$0,45
	beq	$16,$2,$LGodzAct_800C5440_4
	addiu	$2,$0,50
	beq	$16,$2,$LGodzAct_800C5440_4
	addiu	$2,$0,55
	bne	$16,$2,$LGodzAct_800C5440_5
	addiu	$2,$0,60
$LGodzAct_800C5440_4:
	addiu	$4,$18,32
	addiu	$5,$0,202
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,60
$LGodzAct_800C5440_5:
	bne	$16,$2,$LGodzAct_800C5440_6
	addiu	$2,$0,90
	addiu	$4,$18,32
	addiu	$5,$0,136
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,90
$LGodzAct_800C5440_6:
	bne	$16,$2,$LGodzAct_800C5440_7
	addiu	$2,$0,120
	addiu	$4,$18,32
	addiu	$5,$0,129
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,120
$LGodzAct_800C5440_7:
	bne	$16,$2,$LGodzAct_800C5440_8
	addiu	$2,$0,150
	addiu	$4,$18,32
	addiu	$5,$0,137
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,150
$LGodzAct_800C5440_8:
	bne	$16,$2,$LGodzAct_800C5440_9
	addiu	$2,$0,180
	addiu	$4,$18,32
	addiu	$5,$0,130
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,180
$LGodzAct_800C5440_9:
	bne	$16,$2,$LGodzAct_800C5440_10
	addiu	$2,$0,210
	addiu	$4,$18,32
	addiu	$5,$0,136
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,210
$LGodzAct_800C5440_10:
	bne	$16,$2,$LGodzAct_800C5440_11
	addiu	$2,$0,240
	addiu	$4,$18,32
	addiu	$5,$0,129
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,240
$LGodzAct_800C5440_11:
	bne	$16,$2,$LGodzAct_800C5440_12
	addiu	$2,$0,270
	addiu	$4,$18,32
	addiu	$5,$0,137
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,270
$LGodzAct_800C5440_12:
	bne	$16,$2,$LGodzAct_800C5440_13
	addiu	$2,$0,300
	addiu	$4,$18,32
	addiu	$5,$0,130
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,300
$LGodzAct_800C5440_13:
	bne	$16,$2,$LGodzAct_800C5440_14
	addiu	$2,$0,310
	addiu	$4,$18,32
	addiu	$5,$0,136
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,310
$LGodzAct_800C5440_14:
	bne	$16,$2,$LGodzAct_800C5440_15
	addiu	$2,$0,104
	addiu	$4,$18,32
	addiu	$5,$0,129
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,104
$LGodzAct_800C5440_15:
	bne	$16,$2,$LGodzAct_800C5440_16
	addiu	$2,$0,155
	addiu	$4,$18,32
	addiu	$5,$0,203
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,155
$LGodzAct_800C5440_16:
	beq	$16,$2,$LGodzAct_800C5440_17
	addiu	$2,$0,204
	beq	$16,$2,$LGodzAct_800C5440_17
	addiu	$2,$0,265
	beq	$16,$2,$LGodzAct_800C5440_17
	addiu	$2,$0,295
	bne	$16,$2,$LGodzAct_800C5440_18
	slti	$2,$16,61
$LGodzAct_800C5440_17:
	addiu	$4,$18,32
	addiu	$5,$0,204
	jal	GM_SeSetMode
	addiu	$6,$0,1
	slti	$2,$16,61
$LGodzAct_800C5440_18:
	bne	$2,$0,$LGodzAct_800C5440_19
	nop
	lh	$2,182($18)
	nop
	beq	$2,$0,$LGodzAct_800C5440_19
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
	jal	NewSplash2Big
	sh	$16,20($29)
	addiu	$4,$0,1024
	addiu	$5,$29,16
	jal	NewSplash2Big
	addiu	$6,$0,1
	addiu	$4,$0,2048
	addiu	$5,$29,16
	addiu	$6,$0,1
	addiu	$2,$0,2500
	sh	$2,16($29)
	sh	$17,18($29)
	jal	NewSplash2Big
	sh	$16,20($29)
	addiu	$4,$0,1024
	addiu	$5,$29,16
	jal	NewSplash2Big
	addiu	$6,$0,1
	addiu	$4,$18,156
	addu	$5,$0,$0
	lui	$2,%hi(GodzAct_800C5768)
	addiu	$2,$2,%lo(GodzAct_800C5768)
	sw	$2,2284($18)
	sw	$0,2292($18)
	sh	$0,112($18)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($18)
$LGodzAct_800C5440_19:
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.text
