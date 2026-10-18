	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C2CFC
njp_800C2CFC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$4,2308($16)
	nop
	beq	$4,$0,$Lnjp_800C2CFC_0
	nop
	jal	GV_DestroyActorQuick
	nop
$Lnjp_800C2CFC_0:
	addu	$4,$16,$0
	addiu	$5,$0,-1
	lui	$2,%hi(GM_ItemTypes)
	sw	$0,2308($4)
	sw	$5,2312($4)
	lhu	$3,%lo(GM_ItemTypes)($2)
	lui	$2,%hi(linkvarbuf+30)
	sh	$5,%lo(linkvarbuf+30)($2)
	jal	njp_sna_8004EC00
	sw	$3,2316($4)
	lui	$4,0x40
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x1000
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.text
