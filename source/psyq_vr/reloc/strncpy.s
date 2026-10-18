	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	strncpy
strncpy:
	beq	$4,$0,$Lstrncpy_5
	addu	$2,$0,$0
	beq	$5,$0,$Lstrncpy_5
	addu	$3,$0,$0
	blez	$6,$Lstrncpy_4
	addu	$7,$4,$0
$Lstrncpy_0:
	lbu	$2,0($5)
	addiu	$5,$5,1
	sb	$2,0($4)
	bne	$2,$0,$Lstrncpy_3
	addiu	$4,$4,1
	j	$Lstrncpy_2
	addiu	$3,$3,1
$Lstrncpy_1:
	sb	$0,0($4)
	addiu	$4,$4,1
	addiu	$3,$3,1
$Lstrncpy_2:
	slt	$2,$3,$6
	bne	$2,$0,$Lstrncpy_1
	addu	$2,$7,$0
	j	$Lstrncpy_5
	nop
$Lstrncpy_3:
	addiu	$3,$3,1
	slt	$2,$3,$6
	bne	$2,$0,$Lstrncpy_0
	nop
$Lstrncpy_4:
	addu	$2,$7,$0
$Lstrncpy_5:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
