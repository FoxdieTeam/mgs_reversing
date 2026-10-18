	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	GodzAct_800C6440
GodzAct_800C6440:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$31,32($29)
	sw	$17,28($29)
	lw	$2,2940($16)
	addu	$17,$5,$0
	ori	$2,$2,0x20
	bne	$17,$0,$LGodzAct_800C6440_4
	sw	$2,2940($16)
	lw	$3,2268($16)
	nop
	slti	$2,$3,3
	beq	$2,$0,$LGodzAct_800C6440_1
	addiu	$2,$0,1
	bne	$3,$2,$LGodzAct_800C6440_0
	addiu	$4,$16,156
	addiu	$2,$0,41
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+82)
	lh	$5,%lo(GodzActTable+82)($2)
	j	$LGodzAct_800C6440_2
	addu	$6,$0,$0
$LGodzAct_800C6440_0:
	addiu	$2,$0,39
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+78)
	lh	$5,%lo(GodzActTable+78)($2)
	j	$LGodzAct_800C6440_2
	addu	$6,$0,$0
$LGodzAct_800C6440_1:
	addiu	$4,$16,156
	addu	$6,$0,$0
	addiu	$2,$0,40
	sh	$2,2272($16)
	lui	$2,%hi(GodzActTable+80)
	lh	$5,%lo(GodzActTable+80)($2)
$LGodzAct_800C6440_2:
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
	bgez	$2,$LGodzAct_800C6440_3
	nop
	subu	$2,$0,$2
$LGodzAct_800C6440_3:
	addiu	$2,$2,10
	sh	$2,2922($16)
$LGodzAct_800C6440_4:
	lh	$2,2922($16)
	nop
	slt	$2,$2,$17
	beq	$2,$0,$LGodzAct_800C6440_6
	nop
	lw	$3,2304($16)
	nop
	lh	$2,42($3)
	nop
	bgtz	$2,$LGodzAct_800C6440_5
	addiu	$4,$16,156
	lhu	$2,2960($16)
	nop
	sh	$2,42($3)
$LGodzAct_800C6440_5:
	addu	$5,$0,$0
	lui	$2,%hi(GodzAct_800C6598)
	addiu	$2,$2,%lo(GodzAct_800C6598)
	sw	$2,2284($16)
	sw	$0,2292($16)
	sh	$0,112($16)
	jal	GM_ConfigMotionAdjust
	sh	$0,108($16)
$LGodzAct_800C6440_6:
	lw	$31,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.text
