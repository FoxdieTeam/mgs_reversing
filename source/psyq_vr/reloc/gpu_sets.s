	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	SetSprt
	.globl	SetTile
	.globl	SetPriority
SetSprt:
	addiu	$2,$0,4
	sb	$2,3($4)
	addiu	$2,$0,100
	jr	$31
	sb	$2,7($4)
	nop
	nop
	nop
SetTile:
	addiu	$2,$0,3
	sb	$2,3($4)
	addiu	$2,$0,96
	jr	$31
	sb	$2,7($4)
	nop
	nop
	nop
SetPriority:
	addiu	$2,$0,2
	sb	$2,3($4)
	beq	$5,$0,$LSetSprt_0
	lui	$3,0xe600
	ori	$3,$3,0x2
$LSetSprt_0:
	sltu	$2,$0,$6
	or	$2,$3,$2
	sw	$2,4($4)
	jr	$31
	sw	$0,8($4)
	.set	macro
	.set	reorder
	.set	at
