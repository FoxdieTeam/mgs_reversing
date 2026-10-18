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
	.text
