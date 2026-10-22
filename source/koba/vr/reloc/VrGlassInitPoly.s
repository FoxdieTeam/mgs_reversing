	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrGlassInitPoly
VrGlassInitPoly:
	addiu	$12,$0,9
	addiu	$11,$0,46
	addiu	$8,$0,128
	sb	$12,3($4)
	sb	$11,7($4)
	sb	$8,4($4)
	sb	$8,5($4)
	sb	$8,6($4)
	lbu	$7,10($5)
	nop
	addiu	$7,$7,1
	mult	$7,$6
	mflo	$2
	addiu	$10,$6,1
	nop
	mult	$7,$10
	mflo	$7
	lui	$9,0x5555
	ori	$9,$9,0x5556
	mult	$2,$9
	mfhi	$15
	nop
	nop
	mult	$7,$9
	lbu	$3,8($5)
	sra	$2,$2,31
	subu	$2,$15,$2
	addu	$2,$3,$2
	sra	$7,$7,31
	sb	$2,28($4)
	sb	$2,12($4)
	mfhi	$13
	subu	$7,$13,$7
	addu	$3,$3,$7
	addiu	$3,$3,-1
	sb	$3,36($4)
	sb	$3,20($4)
	lbu	$3,11($5)
	lbu	$2,9($5)
	addiu	$3,$3,1
	sra	$3,$3,1
	sb	$2,21($4)
	sb	$2,13($4)
	addu	$2,$2,$3
	addiu	$2,$2,-1
	sb	$2,37($4)
	sb	$2,29($4)
	lhu	$2,4($5)
	nop
	sh	$2,22($4)
	lhu	$2,6($5)
	nop
	sh	$2,14($4)
	addiu	$4,$4,40
	sb	$12,3($4)
	sb	$11,7($4)
	sb	$8,4($4)
	sb	$8,5($4)
	sb	$8,6($4)
	lbu	$2,10($5)
	nop
	addiu	$2,$2,1
	mult	$2,$6
	mflo	$6
	nop
	nop
	mult	$2,$10
	mflo	$2
	nop
	nop
	mult	$6,$9
	mfhi	$8
	nop
	nop
	mult	$2,$9
	lbu	$3,8($5)
	sra	$6,$6,31
	subu	$6,$8,$6
	addu	$6,$3,$6
	sra	$2,$2,31
	sb	$6,28($4)
	sb	$6,12($4)
	mfhi	$7
	subu	$2,$7,$2
	addu	$3,$3,$2
	addiu	$3,$3,-1
	sb	$3,36($4)
	sb	$3,20($4)
	lbu	$6,11($5)
	lbu	$3,9($5)
	addiu	$6,$6,1
	srl	$2,$6,1
	addu	$2,$3,$2
	addu	$3,$3,$6
	addiu	$3,$3,-1
	sb	$2,21($4)
	sb	$2,13($4)
	sb	$3,37($4)
	sb	$3,29($4)
	lhu	$2,4($5)
	nop
	sh	$2,22($4)
	lhu	$2,6($5)
	jr	$31
	sh	$2,14($4)
	.set	macro
	.set	reorder
	.set	at
