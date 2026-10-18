	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	s00a_command_800C9930
s00a_command_800C9930:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lbu	$2,2979($16)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$Ls00a_command_800C9930_5
	nop
	lw	$2,2928($16)
	nop
	andi	$2,$2,0x68
	bne	$2,$0,$Ls00a_command_800C9930_5
	lui	$2,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($2)
	nop
	beq	$3,$0,$Ls00a_command_800C9930_5
	addiu	$5,$16,32
	lui	$3,%hi(GM_PlayerMap)
	lw	$2,44($5)
	lw	$3,%lo(GM_PlayerMap)($3)
	lw	$2,0($2)
	nop
	and	$2,$2,$3
	beq	$2,$0,$Ls00a_command_800C9930_5
	lui	$4,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($4)
	addiu	$2,$0,100
	beq	$3,$2,$Ls00a_command_800C9930_3
	slti	$2,$3,101
	beq	$2,$0,$Ls00a_command_800C9930_0
	addiu	$2,$0,5
	beq	$3,$2,$Ls00a_command_800C9930_1
	lui	$4,%hi(GM_NoisePosition)
	j	$Ls00a_command_800C9930_5
	nop
$Ls00a_command_800C9930_0:
	addiu	$2,$0,200
	beq	$3,$2,$Ls00a_command_800C9930_2
	addiu	$2,$0,255
	beq	$3,$2,$Ls00a_command_800C9930_4
	nop
	j	$Ls00a_command_800C9930_5
	nop
$Ls00a_command_800C9930_1:
	jal	GV_DiffVec3
	addiu	$4,$4,%lo(GM_NoisePosition)
	slti	$2,$2,1500
	beq	$2,$0,$Ls00a_command_800C9930_5
	nop
	j	$Ls00a_command_800C9930_4
	nop
$Ls00a_command_800C9930_2:
	lui	$4,%hi(GM_NoisePosition)
	jal	GV_DiffVec3
	addiu	$4,$4,%lo(GM_NoisePosition)
	lui	$3,%hi(COM_NOISEMODE_DIS)
	lw	$3,%lo(COM_NOISEMODE_DIS)($3)
	nop
	slt	$2,$2,$3
	beq	$2,$0,$Ls00a_command_800C9930_5
	nop
	j	$Ls00a_command_800C9930_4
	nop
$Ls00a_command_800C9930_3:
	lui	$2,%hi(COM_NoiseMinDisID)
	lb	$3,2936($16)
	lw	$2,%lo(COM_NoiseMinDisID)($2)
	nop
	bne	$3,$2,$Ls00a_command_800C9930_5
	nop
	lbu	$2,2977($16)
	nop
	ori	$2,$2,0x1
	sb	$2,2977($16)
	lui	$2,%hi(GM_NoiseLength)
	sw	$0,%lo(GM_NoiseLength)($2)
	j	$Ls00a_command_800C9930_5
	sw	$0,%lo(GM_NoisePower)($4)
$Ls00a_command_800C9930_4:
	lbu	$2,2977($16)
	nop
	ori	$2,$2,0x1
	sb	$2,2977($16)
$Ls00a_command_800C9930_5:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
