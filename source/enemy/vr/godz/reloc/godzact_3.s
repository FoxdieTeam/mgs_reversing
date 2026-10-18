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
	lui	$2,%hi(GodzAct_800C4DB8)
	addiu	$16,$2,%lo(GodzAct_800C4DB8)
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
	.text
