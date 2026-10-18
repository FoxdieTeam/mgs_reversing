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
	.text
