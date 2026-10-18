	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C9E84
vcd_n05_800C9E84:
	lw	$2,3060($4)
	nop
	sw	$2,3072($4)
	lwl	$3,3047($4)
	lwr	$3,3044($4)
	lwl	$5,3051($4)
	lwr	$5,3048($4)
	swl	$3,3055($4)
	swr	$3,3052($4)
	swl	$5,3059($4)
	swr	$5,3056($4)
	lw	$2,3064($4)
	jr	$31
	sw	$2,3076($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C9EBC
vcd_n05_800C9EBC:
	lui	$2,%hi(GODZCOM_PlayerAddress)
	lw	$2,%lo(GODZCOM_PlayerAddress)($2)
	nop
	sw	$2,3072($4)
	lui	$2,%hi(GODZCOM_PlayerMap)
	lw	$3,%lo(GODZCOM_PlayerMap)($2)
	lui	$2,%hi(GODZCOM_PlayerPosition)
	addiu	$8,$2,%lo(GODZCOM_PlayerPosition)
	lwl	$5,3($8)
	lwr	$5,0($8)
	lwl	$6,7($8)
	lwr	$6,4($8)
	swl	$5,3055($4)
	swr	$5,3052($4)
	swl	$6,3059($4)
	swr	$6,3056($4)
	jr	$31
	sw	$3,3076($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C9F04
vcd_n05_800C9F04:
	lui	$2,%hi(GM_WhereList)
	lw	$2,%lo(GM_WhereList)($2)
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	lui	$17,%hi(GM_NoisePosition)
	sw	$31,24($29)
	lw	$2,44($2)
	addiu	$5,$17,%lo(GM_NoisePosition)
	lw	$4,8($2)
	jal	HZD_GetAddress
	addiu	$6,$0,-1
	lui	$3,%hi(GODZCOM_PlayerMap)
	lw	$3,%lo(GODZCOM_PlayerMap)($3)
	sw	$2,3072($16)
	addiu	$10,$17,%lo(GM_NoisePosition)
	lwl	$7,3($10)
	lwr	$7,0($10)
	lwl	$8,7($10)
	lwr	$8,4($10)
	swl	$7,3055($16)
	swr	$7,3052($16)
	swl	$8,3059($16)
	swr	$8,3056($16)
	sw	$3,3076($16)
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
	.globl	vcd_n05_800C9F80
vcd_n05_800C9F80:
	lui	$2,%hi(GodzCommand)
	addiu	$2,$2,%lo(GodzCommand)
	lw	$3,40($2)
	nop
	sw	$3,3072($4)
	lwl	$5,51($2)
	lwr	$5,48($2)
	lwl	$6,55($2)
	lwr	$6,52($2)
	swl	$5,3055($4)
	swr	$5,3052($4)
	swl	$6,3059($4)
	swr	$6,3056($4)
	lw	$2,44($2)
	jr	$31
	sw	$2,3076($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800C9FC0
vcd_n05_800C9FC0:
	lbu	$2,2952($4)
	lw	$5,76($4)
	sll	$3,$2,1
	addu	$3,$3,$2
	lw	$5,8($5)
	sll	$6,$2,8
	lw	$5,0($5)
	or	$2,$2,$6
	lw	$5,20($5)
	sll	$3,$3,3
	sw	$2,3072($4)
	addu	$5,$5,$3
	lhu	$2,0($5)
	nop
	sh	$2,3052($4)
	lhu	$2,4($5)
	nop
	sh	$2,3054($4)
	lw	$2,3064($4)
	lhu	$3,2($5)
	sw	$2,3076($4)
	jr	$31
	sh	$3,3056($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA01C
vcd_n05_800CA01C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$3,2884($16)
	lw	$2,2552($16)
	addiu	$3,$3,1
	slt	$2,$3,$2
	bne	$2,$0,$Lvcd_n05_800CA01C_0
	sll	$2,$3,3
	addu	$3,$0,$0
	sll	$2,$3,3
$Lvcd_n05_800CA01C_0:
	addu	$2,$16,$2
	sw	$3,2884($16)
	lwl	$7,2559($2)
	lwr	$7,2556($2)
	lwl	$8,2563($2)
	lwr	$8,2560($2)
	swl	$7,3055($16)
	swr	$7,3052($16)
	swl	$8,3059($16)
	swr	$8,3056($16)
	lw	$2,76($16)
	addiu	$5,$16,3052
	lw	$4,8($2)
	jal	HZD_GetAddress
	addiu	$6,$0,-1
	lw	$3,3064($16)
	sw	$2,3072($16)
	sw	$3,3076($16)
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA0A4
vcd_n05_800CA0A4:
	sh	$0,2864($4)
	sh	$0,2866($4)
	sh	$0,2868($4)
	sw	$0,2872($4)
	jr	$31
	sh	$0,2908($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA0BC
vcd_n05_800CA0BC:
	lb	$3,2949($4)
	addiu	$2,$0,7
	sh	$2,2866($4)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800CA0BC_0
	addiu	$2,$0,12
	addiu	$2,$0,11
$Lvcd_n05_800CA0BC_0:
	sh	$2,2868($4)
	jr	$31
	sw	$0,2872($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA0E4
vcd_n05_800CA0E4:
	addiu	$2,$0,1
	sh	$2,2864($4)
	addiu	$2,$0,10
	sh	$2,2866($4)
	addiu	$2,$0,23
	sh	$2,2868($4)
	jr	$31
	sw	$0,2872($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA104
vcd_n05_800CA104:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lbu	$3,2952($16)
	addiu	$2,$0,255
	bne	$3,$2,$Lvcd_n05_800CA104_0
	nop
	jal	vcd_n05_800C9F80
	nop
	j	$Lvcd_n05_800CA104_1
	addiu	$2,$0,1
$Lvcd_n05_800CA104_0:
	jal	vcd_n05_800C9FC0
	addu	$4,$16,$0
	addiu	$2,$0,1
$Lvcd_n05_800CA104_1:
	sh	$2,2864($16)
	addiu	$2,$0,10
	sh	$2,2866($16)
	addiu	$2,$0,23
	sh	$2,2868($16)
	addiu	$2,$0,1
	sw	$0,2872($16)
	sw	$2,2892($16)
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA170
vcd_n05_800CA170:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800CA170_0
	addiu	$2,$0,5
	addiu	$2,$0,4
$Lvcd_n05_800CA170_0:
	sb	$2,2954($16)
	sb	$2,2953($16)
	jal	vcd_n05_800CB0D4
	addu	$4,$16,$0
	jal	vcd_n05_800C9E84
	addu	$4,$16,$0
	lw	$3,2552($16)
	addiu	$2,$0,2
	sh	$2,2864($16)
	addiu	$2,$0,11
	sh	$2,2866($16)
	addiu	$2,$0,8
	sh	$2,2868($16)
	sw	$0,2872($16)
	sw	$0,2892($16)
	addiu	$3,$3,-1
	sw	$3,2884($16)
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA1E8
vcd_n05_800CA1E8:
	addiu	$2,$0,4
	sh	$2,2866($4)
	sh	$2,2868($4)
	sw	$0,2872($4)
	jr	$31
	sb	$0,2986($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA200
vcd_n05_800CA200:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	lui	$2,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($2)
	addiu	$2,$0,100
	beq	$3,$2,$Lvcd_n05_800CA200_3
	sw	$31,20($29)
	slti	$2,$3,101
	beq	$2,$0,$Lvcd_n05_800CA200_0
	addiu	$2,$0,5
	beq	$3,$2,$Lvcd_n05_800CA200_1
	addiu	$2,$0,1
	j	$Lvcd_n05_800CA200_3
	nop
$Lvcd_n05_800CA200_0:
	addiu	$2,$0,200
	beq	$3,$2,$Lvcd_n05_800CA200_2
	addiu	$2,$0,255
	beq	$3,$2,$Lvcd_n05_800CA200_2
	nop
	j	$Lvcd_n05_800CA200_3
	nop
$Lvcd_n05_800CA200_1:
	sh	$2,2866($16)
	addiu	$2,$0,7
	j	$Lvcd_n05_800CA200_4
	sh	$2,2868($16)
$Lvcd_n05_800CA200_2:
	jal	vcd_n05_800C9F04
	addu	$4,$16,$0
	jal	GODZ_SetGoPointNoise
	nop
	addiu	$2,$0,7
	sh	$2,2866($16)
	addiu	$2,$0,12
	j	$Lvcd_n05_800CA200_4
	sh	$2,2868($16)
$Lvcd_n05_800CA200_3:
	jal	vcd_n05_800C9F04
	addu	$4,$16,$0
	addiu	$2,$0,1
	sh	$2,2866($16)
	addiu	$2,$0,5
	sh	$2,2868($16)
	sb	$0,2984($16)
$Lvcd_n05_800CA200_4:
	sw	$0,2872($16)
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA2BC
vcd_n05_800CA2BC:
	addiu	$2,$0,2
	sh	$2,2866($4)
	addiu	$2,$0,5
	sh	$2,2868($4)
	jr	$31
	sw	$0,2872($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA2D4
vcd_n05_800CA2D4:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$2,$0,5
	sw	$31,20($29)
	sh	$2,2866($16)
	jal	NearAsiato
	sh	$2,2868($16)
	sb	$2,2988($16)
	sw	$0,2872($16)
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA30C
vcd_n05_800CA30C:
	addiu	$29,$29,-32
	lui	$2,%hi(GODZCOM_PlayerPosition)
	addiu	$5,$4,32
	addiu	$4,$2,%lo(GODZCOM_PlayerPosition)
	sw	$31,24($29)
	jal	GV_SubVec3
	addiu	$6,$29,16
	jal	GV_VecDir2
	addiu	$4,$29,16
	lw	$31,24($29)
	nop
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA340
vcd_n05_800CA340:
	addu	$5,$4,$0
	lui	$2,0x8888
	lw	$6,2872($5)
	ori	$2,$2,0x8889
	mult	$6,$2
	lb	$4,2948($5)
	sra	$3,$6,31
	mfhi	$7
	addu	$2,$7,$6
	sra	$2,$2,4
	subu	$3,$2,$3
	addu	$3,$3,$4
	addiu	$2,$0,1
	beq	$3,$2,$Lvcd_n05_800CA340_0
	nop
	addiu	$2,$0,4
	bne	$3,$2,$Lvcd_n05_800CA340_1
	nop
$Lvcd_n05_800CA340_0:
	lw	$2,2888($5)
	j	$Lvcd_n05_800CA340_3
	ori	$2,$2,0x2
$Lvcd_n05_800CA340_1:
	addiu	$2,$0,2
	beq	$3,$2,$Lvcd_n05_800CA340_2
	addiu	$2,$0,5
	bne	$3,$2,$Lvcd_n05_800CA340_4
	slti	$2,$6,31
$Lvcd_n05_800CA340_2:
	lw	$2,2888($5)
	nop
	ori	$2,$2,0x1
$Lvcd_n05_800CA340_3:
	sw	$2,2888($5)
	slti	$2,$6,31
$Lvcd_n05_800CA340_4:
	beq	$2,$0,$Lvcd_n05_800CA340_5
	addu	$2,$0,$0
	lw	$3,2872($5)
	nop
	addiu	$3,$3,1
	jr	$31
	sw	$3,2872($5)
$Lvcd_n05_800CA340_5:
	jr	$31
	addiu	$2,$0,1
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA3E0
vcd_n05_800CA3E0:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2872($16)
	nop
	bne	$2,$0,$Lvcd_n05_800CA3E0_0
	addiu	$2,$0,71
	lb	$3,2949($16)
	nop
	beq	$3,$2,$Lvcd_n05_800CA3E0_1
	lui	$2,%hi(GODZ_GameFlag)
	addiu	$3,$0,7
	sw	$3,%lo(GODZ_GameFlag)($2)
	addiu	$2,$0,1024
	sh	$2,2904($16)
$Lvcd_n05_800CA3E0_0:
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800CA3E0_2
	lui	$2,%hi(GODZ_GameFlag)
$Lvcd_n05_800CA3E0_1:
	jal	vcd_n05_800CA30C
	addu	$4,$16,$0
	sh	$2,2904($16)
	lui	$2,%hi(GODZ_GameFlag)
$Lvcd_n05_800CA3E0_2:
	lw	$3,%lo(GODZ_GameFlag)($2)
	addiu	$2,$0,7
	bne	$3,$2,$Lvcd_n05_800CA3E0_3
	addiu	$2,$0,71
	j	$Lvcd_n05_800CA3E0_5
	addiu	$2,$0,1
$Lvcd_n05_800CA3E0_3:
	lb	$3,2949($16)
	nop
	bne	$3,$2,$Lvcd_n05_800CA3E0_4
	lui	$3,0x1000
	lw	$2,2888($16)
	nop
	or	$2,$2,$3
	sw	$2,2888($16)
$Lvcd_n05_800CA3E0_4:
	lw	$3,2872($16)
	addu	$2,$0,$0
	addiu	$3,$3,1
	sw	$3,2872($16)
$Lvcd_n05_800CA3E0_5:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA498
vcd_n05_800CA498:
	lw	$2,2872($4)
	nop
	bne	$2,$0,$Lvcd_n05_800CA498_0
	lui	$3,0x800
	lw	$2,2888($4)
	nop
	or	$2,$2,$3
	sw	$2,2888($4)
$Lvcd_n05_800CA498_0:
	lh	$2,182($4)
	nop
	bne	$2,$0,$Lvcd_n05_800CA498_1
	addu	$2,$0,$0
	lw	$3,2872($4)
	nop
	addiu	$3,$3,1
	jr	$31
	sw	$3,2872($4)
$Lvcd_n05_800CA498_1:
	jr	$31
	addiu	$2,$0,1
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA4E4
vcd_n05_800CA4E4:
	lui	$5,0x800
	lw	$2,2888($4)
	lw	$3,2872($4)
	or	$2,$2,$5
	addiu	$3,$3,1
	sw	$2,2888($4)
	addu	$2,$0,$0
	jr	$31
	sw	$3,2872($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA508
vcd_n05_800CA508:
	lw	$2,2872($4)
	nop
	beq	$2,$0,$Lvcd_n05_800CA508_0
	slti	$2,$2,33
	bne	$2,$0,$Lvcd_n05_800CA508_1
	addiu	$2,$0,1
	jr	$31
	nop
$Lvcd_n05_800CA508_0:
	addiu	$2,$0,245
	sh	$2,2906($4)
$Lvcd_n05_800CA508_1:
	lw	$3,2872($4)
	addu	$2,$0,$0
	addiu	$3,$3,1
	jr	$31
	sw	$3,2872($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA544
vcd_n05_800CA544:
	addiu	$29,$29,-48
	sw	$16,24($29)
	addu	$16,$4,$0
	lui	$4,%hi(godz_str_target_map)
	sw	$31,44($29)
	sw	$20,40($29)
	sw	$19,36($29)
	sw	$18,32($29)
	sw	$17,28($29)
	lw	$2,76($16)
	lw	$5,3076($16)
	lw	$6,0($2)
	lw	$19,8($2)
	jal	printf
	addiu	$4,$4,%lo(godz_str_target_map)
	addu	$4,$19,$0
	addiu	$20,$16,32
	lw	$6,3096($16)
	lw	$18,3072($16)
	jal	HZD_GetAddress
	addu	$5,$20,$0
	addu	$4,$19,$0
	addu	$17,$2,$0
	lw	$6,3100($16)
	addu	$5,$17,$0
	jal	HZD_ReachTo
	sw	$17,3096($16)
	lw	$3,3068($16)
	nop
	bne	$18,$3,$Lvcd_n05_800CA544_0
	nop
	bgtz	$2,$Lvcd_n05_800CA544_4
	addiu	$4,$16,3112
$Lvcd_n05_800CA544_0:
	sw	$18,3068($16)
	addu	$4,$19,$0
	addu	$5,$17,$0
	jal	HZD_ReachTo
	addu	$6,$18,$0
	slti	$2,$2,2
	beq	$2,$0,$Lvcd_n05_800CA544_1
	addiu	$4,$16,3112
	addu	$5,$20,$0
	addiu	$6,$29,16
	lwl	$8,3055($16)
	lwr	$8,3052($16)
	lwl	$9,3059($16)
	lwr	$9,3056($16)
	swl	$8,3115($16)
	swr	$8,3112($16)
	swl	$9,3119($16)
	swr	$9,3116($16)
	jal	GV_SubVec3
	sw	$18,3100($16)
	jal	GV_VecDir2
	addiu	$4,$29,16
	sh	$2,2904($16)
	j	$Lvcd_n05_800CA544_5
	addiu	$2,$0,-1
$Lvcd_n05_800CA544_1:
	addu	$4,$19,$0
	addu	$5,$17,$0
	addu	$6,$18,$0
	jal	HZD_Navigate
	addu	$7,$20,$0
	addu	$5,$2,$0
	sll	$2,$5,1
	lw	$3,0($19)
	addu	$2,$2,$5
	lw	$3,20($3)
	sll	$2,$2,3
	addu	$4,$3,$2
	lw	$3,3080($16)
	addiu	$2,$0,4000
	bne	$3,$2,$Lvcd_n05_800CA544_2
	nop
	lhu	$2,0($4)
	nop
	addiu	$2,$2,250
	sh	$2,3112($16)
	lhu	$2,4($4)
	nop
	sh	$2,3114($16)
	lhu	$2,2($4)
	j	$Lvcd_n05_800CA544_3
	addiu	$2,$2,250
$Lvcd_n05_800CA544_2:
	lhu	$2,0($4)
	nop
	sh	$2,3112($16)
	lhu	$2,4($4)
	nop
	sh	$2,3114($16)
	lhu	$2,2($4)
$Lvcd_n05_800CA544_3:
	nop
	sh	$2,3116($16)
	lhu	$2,0($4)
	nop
	sh	$2,3112($16)
	lhu	$2,4($4)
	nop
	sh	$2,3114($16)
	andi	$2,$5,0xff
	sll	$3,$2,8
	lhu	$4,2($4)
	or	$2,$2,$3
	sw	$2,3100($16)
	sh	$4,3116($16)
	addiu	$4,$16,3112
$Lvcd_n05_800CA544_4:
	addiu	$5,$16,32
	jal	GV_SubVec3
	addiu	$6,$29,16
	jal	GV_VecDir2
	addiu	$4,$29,16
$Lvcd_n05_800CA544_5:
	lw	$31,44($29)
	lw	$20,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA720
vcd_n05_800CA720:
	addiu	$29,$29,-24
	addu	$5,$4,$0
	sw	$31,16($29)
	lw	$2,2900($5)
	nop
	beq	$2,$0,$Lvcd_n05_800CA720_0
	addu	$4,$5,$0
	lw	$2,2888($5)
	lw	$4,2896($5)
	lw	$3,2900($5)
	or	$2,$2,$4
	addiu	$3,$3,-1
	sw	$2,2888($5)
	sw	$3,2900($5)
	addu	$4,$5,$0
$Lvcd_n05_800CA720_0:
	jal	vcd_n05_800CAC60
	addiu	$5,$0,350
	lw	$31,16($29)
	sltu	$2,$0,$2
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA774
vcd_n05_800CA774:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$31,28($29)
	sw	$18,24($29)
	sw	$16,16($29)
	lh	$18,3058($17)
	addiu	$4,$0,100
	andi	$2,$18,0x1c00
	jal	GV_RandU
	sra	$16,$2,10
	andi	$4,$16,0x3
	lui	$3,%hi(godzthk_data)
	addiu	$3,$3,%lo(godzthk_data)
	sll	$4,$4,1
	addu	$4,$4,$3
	lhu	$3,0($4)
	nop
	slt	$2,$2,$3
	beq	$2,$0,$Lvcd_n05_800CA774_0
	andi	$16,$16,0x4
	lh	$2,2908($17)
	addiu	$3,$0,1
	bne	$2,$3,$Lvcd_n05_800CA774_1
	nop
$Lvcd_n05_800CA774_0:
	addu	$2,$0,$0
	sw	$0,2900($17)
	sw	$0,2896($17)
	j	$Lvcd_n05_800CA774_7
	sh	$0,2908($17)
$Lvcd_n05_800CA774_1:
	beq	$16,$0,$Lvcd_n05_800CA774_2
	andi	$2,$18,0xe0
	sh	$3,2908($17)
$Lvcd_n05_800CA774_2:
	sra	$5,$2,5
	lui	$3,%hi(godzthk_data+8)
	addiu	$3,$3,%lo(godzthk_data+8)
	sll	$2,$5,1
	addu	$2,$2,$3
	lhu	$2,0($2)
	andi	$4,$18,0x1f
	bne	$4,$0,$Lvcd_n05_800CA774_3
	sw	$2,2900($17)
	bne	$5,$0,$Lvcd_n05_800CA774_4
	lui	$3,%hi(godzthk_data+24)
	sw	$0,2900($17)
$Lvcd_n05_800CA774_3:
	lui	$3,%hi(godzthk_data+24)
$Lvcd_n05_800CA774_4:
	addiu	$3,$3,%lo(godzthk_data+24)
	sll	$2,$4,2
	addu	$2,$2,$3
	lw	$2,0($2)
	nop
	sw	$2,2896($17)
	andi	$2,$4,0x10
	bne	$2,$0,$Lvcd_n05_800CA774_7
	addu	$2,$0,$0
	bne	$4,$0,$Lvcd_n05_800CA774_5
	andi	$2,$18,0x300
	bne	$5,$0,$Lvcd_n05_800CA774_6
	sll	$2,$2,2
	lhu	$3,42($17)
	addu	$2,$0,$0
	sw	$0,2900($17)
	j	$Lvcd_n05_800CA774_7
	sh	$3,2904($17)
$Lvcd_n05_800CA774_5:
	sll	$2,$2,2
$Lvcd_n05_800CA774_6:
	sh	$2,2904($17)
	addiu	$2,$0,1
$Lvcd_n05_800CA774_7:
	lw	$31,28($29)
	lw	$18,24($29)
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
	.globl	vcd_n05_800CA898
vcd_n05_800CA898:
	addiu	$2,$4,32
	lb	$3,86($2)
	lw	$5,92($2)
	blez	$3,$Lvcd_n05_800CA898_2
	nop
	lh	$4,2908($4)
$Lvcd_n05_800CA898_0:
	lhu	$2,4($5)
	nop
	bne	$2,$4,$Lvcd_n05_800CA898_1
	addiu	$3,$3,-1
	jr	$31
	addiu	$2,$0,1
$Lvcd_n05_800CA898_1:
	bgtz	$3,$Lvcd_n05_800CA898_0
	addiu	$5,$5,20
$Lvcd_n05_800CA898_2:
	jr	$31
	addu	$2,$0,$0
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA8D8
vcd_n05_800CA8D8:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2872($16)
	lw	$3,2900($16)
	addiu	$2,$2,1
	sw	$2,2872($16)
	addiu	$2,$0,32001
	bne	$3,$2,$Lvcd_n05_800CA8D8_1
	nop
	jal	vcd_n05_800CA898
	nop
	beq	$2,$0,$Lvcd_n05_800CA8D8_0
	addiu	$2,$0,1
	sh	$0,2908($16)
	j	$Lvcd_n05_800CA8D8_2
	sw	$0,2900($16)
$Lvcd_n05_800CA8D8_0:
	lw	$3,2888($16)
	lw	$4,2896($16)
	addu	$2,$0,$0
	or	$3,$3,$4
	j	$Lvcd_n05_800CA8D8_2
	sw	$3,2888($16)
$Lvcd_n05_800CA8D8_1:
	beq	$3,$0,$Lvcd_n05_800CA8D8_2
	addiu	$2,$0,1
	lw	$2,2888($16)
	lw	$4,2896($16)
	lw	$3,2900($16)
	or	$2,$2,$4
	addiu	$3,$3,-1
	sw	$2,2888($16)
	sw	$3,2900($16)
$Lvcd_n05_800CA8D8_2:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA96C
vcd_n05_800CA96C:
	lw	$2,2940($4)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$Lvcd_n05_800CA96C_0
	nop
	lbu	$2,2986($4)
	nop
	addiu	$2,$2,1
	sb	$2,2986($4)
	sll	$2,$2,24
	sra	$2,$2,24
	slti	$2,$2,31
	bne	$2,$0,$Lvcd_n05_800CA96C_1
	addiu	$2,$0,1
	jr	$31
	nop
$Lvcd_n05_800CA96C_0:
	sb	$0,2986($4)
$Lvcd_n05_800CA96C_1:
	lw	$3,2872($4)
	addu	$2,$0,$0
	addiu	$3,$3,1
	jr	$31
	sw	$3,2872($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CA9C4
vcd_n05_800CA9C4:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2872($16)
	nop
	bne	$2,$0,$Lvcd_n05_800CA9C4_0
	addiu	$2,$0,136
	sh	$2,2906($16)
	jal	GODZ_PutMark
	addiu	$5,$0,5
$Lvcd_n05_800CA9C4_0:
	lw	$3,2872($16)
	addiu	$2,$0,20
	bne	$3,$2,$Lvcd_n05_800CA9C4_1
	nop
	lhu	$2,3132($16)
	nop
	sh	$2,2904($16)
$Lvcd_n05_800CA9C4_1:
	jal	vcd_n05_800CA340
	addu	$4,$16,$0
	lw	$31,20($29)
	lw	$16,16($29)
	sltu	$2,$0,$2
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAA28
vcd_n05_800CAA28:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2872($16)
	nop
	bne	$2,$0,$Lvcd_n05_800CAA28_0
	nop
	jal	GODZ_PutMark
	addu	$5,$0,$0
	lhu	$2,3132($16)
	nop
	sh	$2,2904($16)
$Lvcd_n05_800CAA28_0:
	lw	$3,2872($16)
	addiu	$2,$0,60
	beq	$3,$2,$Lvcd_n05_800CAA28_1
	addiu	$2,$3,1
	sw	$2,2872($16)
	j	$Lvcd_n05_800CAA28_2
	addu	$2,$0,$0
$Lvcd_n05_800CAA28_1:
	addiu	$2,$0,1
$Lvcd_n05_800CAA28_2:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAA8C
vcd_n05_800CAA8C:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$31,24($29)
	sw	$16,16($29)
	lw	$2,2872($17)
	nop
	bne	$2,$0,$Lvcd_n05_800CAA8C_0
	sltiu	$2,$2,20
	jal	GODZ_PutMark
	addu	$5,$0,$0
	addiu	$16,$17,32
	addu	$4,$16,$0
	jal	GM_SeSet
	addiu	$5,$0,83
	lw	$4,156($17)
	addu	$5,$16,$0
	lui	$6,%hi(godz_str_kirari01)
	addiu	$6,$6,%lo(godz_str_kirari01)
	addu	$7,$0,$0
	jal	NewEyeflash
	addiu	$4,$4,624
	lw	$2,2872($17)
	nop
	sltiu	$2,$2,20
$Lvcd_n05_800CAA8C_0:
	bne	$2,$0,$Lvcd_n05_800CAA8C_1
	addu	$4,$17,$0
	j	$Lvcd_n05_800CAA8C_2
	addiu	$2,$0,1
$Lvcd_n05_800CAA8C_1:
	lw	$2,2888($17)
	nop
	ori	$2,$2,0x20
	jal	vcd_n05_800CA30C
	sw	$2,2888($17)
	lw	$3,2872($17)
	sh	$2,2904($17)
	addu	$2,$0,$0
	addiu	$3,$3,1
	sw	$3,2872($17)
$Lvcd_n05_800CAA8C_2:
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
	.globl	vcd_n05_800CAB3C
vcd_n05_800CAB3C:
	lw	$2,2872($4)
	nop
	beq	$2,$0,$Lvcd_n05_800CAB3C_0
	lui	$3,0x400
	lh	$2,182($4)
	nop
	beq	$2,$0,$Lvcd_n05_800CAB3C_1
	addiu	$2,$0,1
	jr	$31
	nop
$Lvcd_n05_800CAB3C_0:
	lw	$2,2888($4)
	nop
	or	$2,$2,$3
	sw	$2,2888($4)
$Lvcd_n05_800CAB3C_1:
	lw	$3,2872($4)
	addu	$2,$0,$0
	addiu	$3,$3,1
	jr	$31
	sw	$3,2872($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAB88
vcd_n05_800CAB88:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2872($16)
	nop
	bne	$2,$0,$Lvcd_n05_800CAB88_0
	addiu	$4,$16,32
	jal	GM_SeSet
	addiu	$5,$0,83
	addu	$4,$16,$0
	jal	GODZ_PutMark
	addu	$5,$0,$0
$Lvcd_n05_800CAB88_0:
	lw	$3,2872($16)
	nop
	sltiu	$2,$3,21
	beq	$2,$0,$Lvcd_n05_800CAB88_1
	addiu	$2,$3,1
	sw	$2,2872($16)
	j	$Lvcd_n05_800CAB88_2
	addu	$2,$0,$0
$Lvcd_n05_800CAB88_1:
	addiu	$2,$0,1
$Lvcd_n05_800CAB88_2:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CABF0
vcd_n05_800CABF0:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2872($16)
	nop
	andi	$2,$2,0x1f
	bne	$2,$0,$Lvcd_n05_800CABF0_0
	addiu	$2,$0,-1
	sw	$2,3096($16)
	jal	vcd_n05_800CA544
	sw	$2,3068($16)
$Lvcd_n05_800CABF0_0:
	jal	vcd_n05_800CA544
	addu	$4,$16,$0
	sh	$2,2904($16)
	sll	$2,$2,16
	bltz	$2,$Lvcd_n05_800CABF0_1
	addu	$2,$0,$0
	lw	$3,2872($16)
	nop
	addiu	$3,$3,1
	j	$Lvcd_n05_800CABF0_2
	sw	$3,2872($16)
$Lvcd_n05_800CABF0_1:
	addiu	$2,$0,1
$Lvcd_n05_800CABF0_2:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAC60
vcd_n05_800CAC60:
	addiu	$29,$29,-32
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$31,28($29)
	lh	$3,3052($16)
	lh	$2,32($16)
	nop
	subu	$4,$3,$2
	sh	$4,16($29)
	lh	$3,3056($16)
	lh	$2,36($16)
	subu	$6,$0,$5
	subu	$3,$3,$2
	slt	$2,$6,$4
	beq	$2,$0,$Lvcd_n05_800CAC60_0
	sh	$3,20($29)
	slt	$2,$4,$5
	beq	$2,$0,$Lvcd_n05_800CAC60_0
	slt	$2,$6,$3
	beq	$2,$0,$Lvcd_n05_800CAC60_0
	slt	$2,$3,$5
	bne	$2,$0,$Lvcd_n05_800CAC60_1
	addiu	$2,$0,1
$Lvcd_n05_800CAC60_0:
	jal	GV_VecDir2
	addiu	$4,$29,16
	lw	$3,2872($16)
	sh	$2,2904($16)
	addu	$2,$0,$0
	addiu	$3,$3,1
	sw	$3,2872($16)
$Lvcd_n05_800CAC60_1:
	lw	$31,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CACE8
vcd_n05_800CACE8:
	addu	$7,$6,$0
	lh	$6,0($4)
	lh	$3,0($5)
	lh	$4,4($4)
	lh	$2,4($5)
	subu	$6,$6,$3
	subu	$4,$4,$2
	subu	$3,$0,$7
	slt	$2,$3,$6
	bne	$2,$0,$Lvcd_n05_800CACE8_0
	slt	$2,$6,$7
	bne	$2,$0,$Lvcd_n05_800CACE8_0
	slt	$2,$3,$4
	bne	$2,$0,$Lvcd_n05_800CACE8_0
	slt	$2,$4,$7
	beq	$2,$0,$Lvcd_n05_800CACE8_1
	nop
$Lvcd_n05_800CACE8_0:
	jr	$31
	addu	$2,$0,$0
$Lvcd_n05_800CACE8_1:
	jr	$31
	addiu	$2,$0,1
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAD3C
vcd_n05_800CAD3C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	sw	$31,20($29)
	jal	vcd_n05_800C9EBC
	addu	$16,$4,$0
	lw	$4,76($16)
	lw	$2,3076($16)
	lw	$3,0($4)
	nop
	bne	$3,$2,$Lvcd_n05_800CAD3C_2
	addiu	$2,$0,-1
	lw	$2,2872($16)
	nop
	andi	$2,$2,0x10
	beq	$2,$0,$Lvcd_n05_800CAD3C_0
	addiu	$5,$16,32
	lw	$4,8($4)
	jal	HZD_GetAddress
	addiu	$6,$0,-1
	lw	$6,3072($16)
	lw	$3,76($16)
	sw	$2,3096($16)
	lw	$4,8($3)
	jal	HZD_ReachTo
	addu	$5,$2,$0
	slti	$2,$2,2
	bne	$2,$0,$Lvcd_n05_800CAD3C_1
	addu	$4,$16,$0
	j	$Lvcd_n05_800CAD3C_2
	addiu	$2,$0,-1
$Lvcd_n05_800CAD3C_0:
	addu	$4,$16,$0
$Lvcd_n05_800CAD3C_1:
	jal	vcd_n05_800CAC60
	addiu	$5,$0,1500
$Lvcd_n05_800CAD3C_2:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CADD0
vcd_n05_800CADD0:
	addu	$5,$4,$0
	lui	$3,0x1
	lw	$2,2888($5)
	lw	$4,2872($5)
	or	$3,$2,$3
	beq	$4,$0,$Lvcd_n05_800CADD0_0
	sw	$3,2888($5)
	addiu	$2,$0,4
	bne	$4,$2,$Lvcd_n05_800CADD0_1
	addu	$2,$0,$0
	jr	$31
	addiu	$2,$0,1
$Lvcd_n05_800CADD0_0:
	lui	$2,0x4
	or	$2,$3,$2
	sw	$2,2888($5)
	addu	$2,$0,$0
$Lvcd_n05_800CADD0_1:
	lw	$3,2872($5)
	lhu	$4,3132($5)
	addiu	$3,$3,1
	sh	$4,2904($5)
	jr	$31
	sw	$3,2872($5)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAE28
vcd_n05_800CAE28:
	addu	$5,$4,$0
	lui	$3,0x2
	lw	$2,2888($5)
	lw	$4,2872($5)
	or	$3,$2,$3
	beq	$4,$0,$Lvcd_n05_800CAE28_0
	sw	$3,2888($5)
	addiu	$2,$0,8
	bne	$4,$2,$Lvcd_n05_800CAE28_1
	addu	$2,$0,$0
	jr	$31
	addiu	$2,$0,1
$Lvcd_n05_800CAE28_0:
	lui	$2,0x8
	or	$2,$3,$2
	sw	$2,2888($5)
	addu	$2,$0,$0
$Lvcd_n05_800CAE28_1:
	lw	$3,2872($5)
	lhu	$4,3132($5)
	addiu	$3,$3,1
	sh	$4,2904($5)
	jr	$31
	sw	$3,2872($5)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAE80
vcd_n05_800CAE80:
	addu	$5,$4,$0
	lw	$3,2888($5)
	lui	$2,0x1
	or	$4,$3,$2
	lw	$3,2872($5)
	addiu	$2,$0,30
	beq	$3,$2,$Lvcd_n05_800CAE80_0
	sw	$4,2888($5)
	lh	$2,182($5)
	nop
	beq	$2,$0,$Lvcd_n05_800CAE80_1
	addu	$2,$0,$0
	jr	$31
	addiu	$2,$0,1
$Lvcd_n05_800CAE80_0:
	lui	$2,0x10
	or	$2,$4,$2
	sw	$2,2888($5)
	addu	$2,$0,$0
$Lvcd_n05_800CAE80_1:
	lw	$3,2872($5)
	lhu	$4,3132($5)
	addiu	$3,$3,1
	sh	$4,2904($5)
	jr	$31
	sw	$3,2872($5)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAEE0
vcd_n05_800CAEE0:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2872($16)
	nop
	beq	$2,$0,$Lvcd_n05_800CAEE0_0
	lui	$3,0x20
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lvcd_n05_800CAEE0_1
	addiu	$2,$0,1
	j	$Lvcd_n05_800CAEE0_2
	nop
$Lvcd_n05_800CAEE0_0:
	lw	$2,2888($16)
	nop
	or	$2,$2,$3
	sw	$2,2888($16)
$Lvcd_n05_800CAEE0_1:
	lui	$3,0x1
	lw	$2,2888($16)
	addu	$4,$16,$0
	or	$2,$2,$3
	jal	vcd_n05_800CA30C
	sw	$2,2888($16)
	lw	$3,2872($16)
	sh	$2,2904($16)
	addu	$2,$0,$0
	addiu	$3,$3,1
	sw	$3,2872($16)
$Lvcd_n05_800CAEE0_2:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAF64
vcd_n05_800CAF64:
	addu	$5,$4,$0
	lw	$2,2872($5)
	nop
	sltiu	$2,$2,91
	beq	$2,$0,$Lvcd_n05_800CAF64_0
	addu	$2,$0,$0
	lw	$3,2888($5)
	lw	$4,2872($5)
	ori	$3,$3,0x4
	addiu	$4,$4,1
	sw	$3,2888($5)
	jr	$31
	sw	$4,2872($5)
$Lvcd_n05_800CAF64_0:
	jr	$31
	addiu	$2,$0,1
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CAFA0
vcd_n05_800CAFA0:
	addu	$5,$4,$0
	lui	$3,0x1
	lw	$2,2888($5)
	lw	$4,2872($5)
	or	$3,$2,$3
	slti	$2,$4,10
	bne	$2,$0,$Lvcd_n05_800CAFA0_0
	sw	$3,2888($5)
	slti	$2,$4,20
	bne	$2,$0,$Lvcd_n05_800CAFA0_1
	addu	$2,$0,$0
	jr	$31
	addiu	$2,$0,1
$Lvcd_n05_800CAFA0_0:
	andi	$2,$4,0x1
	bne	$2,$0,$Lvcd_n05_800CAFA0_1
	addu	$2,$0,$0
	lui	$2,0x4
	or	$2,$3,$2
	sw	$2,2888($5)
	addu	$2,$0,$0
$Lvcd_n05_800CAFA0_1:
	lw	$3,2872($5)
	lhu	$4,3132($5)
	addiu	$3,$3,1
	sh	$4,2904($5)
	jr	$31
	sw	$3,2872($5)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CB008
vcd_n05_800CB008:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	lui	$3,0x1
	sw	$31,20($29)
	lw	$2,2888($16)
	nop
	or	$2,$2,$3
	jal	vcd_n05_800CA30C
	sw	$2,2888($16)
	lw	$3,2872($16)
	sh	$2,2904($16)
	addiu	$3,$3,1
	sw	$3,2872($16)
	lw	$31,20($29)
	lw	$16,16($29)
	addiu	$2,$0,20
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CB054
vcd_n05_800CB054:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lh	$3,2868($16)
	addiu	$2,$0,3
	bne	$3,$2,$Lvcd_n05_800CB054_0
	nop
	jal	vcd_n05_800CA508
	nop
	beq	$2,$0,$Lvcd_n05_800CB054_0
	nop
	jal	vcd_n05_800C9E84
	addu	$4,$16,$0
	lw	$2,2552($16)
	addu	$4,$16,$0
	addiu	$2,$2,-1
	jal	vcd_n05_800CA0A4
	sw	$2,2884($16)
	addiu	$2,$0,1
	sw	$2,2892($16)
$Lvcd_n05_800CB054_0:
	lw	$2,2980($16)
	nop
	slti	$2,$2,2
	bne	$2,$0,$Lvcd_n05_800CB054_1
	nop
	jal	vcd_n05_800CA0BC
	addu	$4,$16,$0
$Lvcd_n05_800CB054_1:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CB0D4
vcd_n05_800CB0D4:
	addiu	$29,$29,-56
	sw	$20,40($29)
	addu	$20,$4,$0
	sw	$31,52($29)
	sw	$22,48($29)
	sw	$21,44($29)
	sw	$19,36($29)
	sw	$18,32($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$4,3064($20)
	jal	GM_GetMap
	nop
	addiu	$4,$0,1
	lui	$5,%hi(godz_str_c_root)
	addu	$22,$2,$0
	addiu	$3,$20,2948
	lw	$2,8($22)
	lb	$7,5($3)
	lw	$2,0($2)
	lbu	$6,6($3)
	lw	$16,24($2)
	sll	$2,$7,3
	addu	$16,$16,$2
	sw	$16,16($29)
	lh	$2,0($16)
	addiu	$5,$5,%lo(godz_str_c_root)
	jal	fprintf
	sw	$2,20($29)
	lh	$2,0($16)
	nop
	bgtz	$2,$Lvcd_n05_800CB0D4_0
	sw	$2,2552($20)
	j	$Lvcd_n05_800CB0D4_3
	addiu	$2,$0,-1
$Lvcd_n05_800CB0D4_0:
	lw	$19,4($16)
	blez	$2,$Lvcd_n05_800CB0D4_2
	addu	$18,$0,$0
	lui	$21,%hi(godz_str_action)
	addu	$16,$20,$0
	addiu	$17,$19,6
$Lvcd_n05_800CB0D4_1:
	lhu	$2,0($19)
	addiu	$19,$19,8
	addiu	$4,$0,1
	sh	$2,2556($16)
	lhu	$2,-2($17)
	addiu	$5,$21,%lo(godz_str_action)
	sh	$2,2558($16)
	lhu	$2,-4($17)
	addu	$18,$18,$4
	sh	$2,2560($16)
	lhu	$2,0($17)
	addiu	$17,$17,8
	sll	$6,$2,16
	sra	$6,$6,16
	jal	fprintf
	sh	$2,2562($16)
	lw	$2,2552($20)
	nop
	slt	$2,$18,$2
	bne	$2,$0,$Lvcd_n05_800CB0D4_1
	addiu	$16,$16,8
$Lvcd_n05_800CB0D4_2:
	addiu	$5,$20,3044
	lwl	$8,2559($20)
	lwr	$8,2556($20)
	lwl	$9,2563($20)
	lwr	$9,2560($20)
	swl	$8,3047($20)
	swr	$8,3044($20)
	swl	$9,3051($20)
	swr	$9,3048($20)
	lw	$4,8($22)
	jal	HZD_GetAddress
	addiu	$6,$0,-1
	sw	$2,3060($20)
	addu	$2,$0,$0
$Lvcd_n05_800CB0D4_3:
	lw	$31,52($29)
	lw	$22,48($29)
	lw	$21,44($29)
	lw	$20,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CB22C
vcd_n05_800CB22C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lbu	$3,2954($16)
	lb	$2,2953($16)
	nop
	bne	$3,$2,$Lvcd_n05_800CB22C_0
	addiu	$4,$0,1
	j	$Lvcd_n05_800CB22C_1
	addu	$2,$0,$0
$Lvcd_n05_800CB22C_0:
	lui	$5,%hi(godz_str_root_change)
	jal	printf
	addiu	$5,$5,%lo(godz_str_root_change)
	lbu	$2,2954($16)
	addu	$4,$16,$0
	jal	vcd_n05_800CB0D4
	sb	$2,2953($4)
	addiu	$2,$0,1
$Lvcd_n05_800CB22C_1:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CB288
vcd_n05_800CB288:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,28($29)
	sw	$18,24($29)
	sw	$17,20($29)
	lh	$17,2868($16)
	addiu	$18,$0,1
	beq	$17,$18,$Lvcd_n05_800CB288_2
	slti	$2,$17,2
	beq	$2,$0,$Lvcd_n05_800CB288_0
	addiu	$2,$0,2
	beq	$17,$0,$Lvcd_n05_800CB288_1
	nop
	j	$Lvcd_n05_800CB288_14
	nop
$Lvcd_n05_800CB288_0:
	beq	$17,$2,$Lvcd_n05_800CB288_8
	nop
	j	$Lvcd_n05_800CB288_14
	nop
$Lvcd_n05_800CB288_1:
	jal	vcd_n05_800CABF0
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB288_14
	addu	$4,$16,$0
	sw	$0,2892($16)
	sh	$0,2866($16)
	j	$Lvcd_n05_800CB288_7
	sh	$18,2868($16)
$Lvcd_n05_800CB288_2:
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800CB288_3
	lui	$2,%hi(GODZ_GameFlag)
	lw	$3,%lo(GODZ_GameFlag)($2)
	addiu	$2,$0,2
	bne	$3,$2,$Lvcd_n05_800CB288_3
	addiu	$3,$0,6
	lb	$2,2953($16)
	nop
	beq	$2,$3,$Lvcd_n05_800CB288_3
	nop
	sb	$3,2954($16)
$Lvcd_n05_800CB288_3:
	jal	vcd_n05_800CA720
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB288_14
	nop
	jal	vcd_n05_800CB22C
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB288_4
	nop
	jal	vcd_n05_800C9E84
	addu	$4,$16,$0
	lw	$2,2552($16)
	addu	$4,$16,$0
	addiu	$2,$2,-1
	jal	vcd_n05_800CA0A4
	sw	$2,2884($16)
	addiu	$2,$0,1
	j	$Lvcd_n05_800CB288_18
	sw	$2,2892($16)
$Lvcd_n05_800CB288_4:
	jal	vcd_n05_800CA774
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB288_6
	addiu	$2,$0,71
	lb	$3,2949($16)
	nop
	bne	$3,$2,$Lvcd_n05_800CB288_5
	addiu	$2,$0,2
	lb	$4,2953($16)
	addiu	$2,$0,1
	bne	$4,$2,$Lvcd_n05_800CB288_5
	addiu	$2,$0,2
	lui	$5,%hi(GODZ_GameFlag)
	lw	$3,%lo(GODZ_GameFlag)($5)
	addiu	$2,$0,2
	beq	$3,$2,$Lvcd_n05_800CB288_5
	addiu	$2,$0,2
	sw	$4,%lo(GODZ_GameFlag)($5)
$Lvcd_n05_800CB288_5:
	j	$Lvcd_n05_800CB288_14
	sh	$2,2868($16)
$Lvcd_n05_800CB288_6:
	addu	$4,$16,$0
$Lvcd_n05_800CB288_7:
	jal	vcd_n05_800CA01C
	nop
	j	$Lvcd_n05_800CB288_14
	sw	$0,2872($16)
$Lvcd_n05_800CB288_8:
	jal	vcd_n05_800CA8D8
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB288_9
	nop
	jal	vcd_n05_800CA01C
	addu	$4,$16,$0
	sh	$18,2868($16)
	sw	$0,2872($16)
$Lvcd_n05_800CB288_9:
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800CB288_10
	addiu	$2,$0,66
	lui	$4,%hi(GODZ_GameFlag)
	lw	$2,%lo(GODZ_GameFlag)($4)
	nop
	blez	$2,$Lvcd_n05_800CB288_13
	addiu	$2,$0,900
	lw	$3,2872($16)
	nop
	bne	$3,$2,$Lvcd_n05_800CB288_13
	addiu	$3,$0,6
	lb	$2,2953($16)
	j	$Lvcd_n05_800CB288_12
	nop
$Lvcd_n05_800CB288_10:
	bne	$3,$2,$Lvcd_n05_800CB288_11
	lui	$4,%hi(GODZ_GameFlag)
	lb	$4,2953($16)
	nop
	beq	$4,$0,$Lvcd_n05_800CB288_13
	addiu	$2,$0,150
	lw	$3,2872($16)
	nop
	bne	$3,$2,$Lvcd_n05_800CB288_13
	addiu	$2,$0,7
	beq	$4,$2,$Lvcd_n05_800CB288_13
	nop
	sb	$2,2954($16)
	lui	$2,%hi(GODZ_GameFlag)
	j	$Lvcd_n05_800CB288_13
	sw	$17,%lo(GODZ_GameFlag)($2)
$Lvcd_n05_800CB288_11:
	lw	$2,%lo(GODZ_GameFlag)($4)
	nop
	blez	$2,$Lvcd_n05_800CB288_13
	addiu	$2,$0,1500
	lw	$3,2872($16)
	nop
	bne	$3,$2,$Lvcd_n05_800CB288_13
	addiu	$3,$0,7
	lb	$2,2953($16)
$Lvcd_n05_800CB288_12:
	nop
	beq	$2,$3,$Lvcd_n05_800CB288_13
	nop
	sb	$3,2954($16)
	sw	$17,%lo(GODZ_GameFlag)($4)
$Lvcd_n05_800CB288_13:
	jal	vcd_n05_800CB22C
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB288_14
	nop
	jal	vcd_n05_800C9E84
	addu	$4,$16,$0
	lw	$2,2552($16)
	addu	$4,$16,$0
	jal	vcd_n05_800CA0A4
	sw	$2,2884($16)
$Lvcd_n05_800CB288_14:
	lb	$3,2949($16)
	addiu	$2,$0,71
	bne	$3,$2,$Lvcd_n05_800CB288_15
	addiu	$2,$0,7
	lb	$3,2953($16)
	addiu	$2,$0,6
	beq	$3,$2,$Lvcd_n05_800CB288_18
	lui	$17,%hi(GODZ_GameFlag)
	lw	$2,%lo(GODZ_GameFlag)($17)
	nop
	slti	$2,$2,2
	beq	$2,$0,$Lvcd_n05_800CB288_18
	nop
	lbu	$2,2990($16)
	nop
	andi	$2,$2,0x4
	beq	$2,$0,$Lvcd_n05_800CB288_18
	nop
	jal	vcd_n05_800CA1E8
	addu	$4,$16,$0
	lw	$3,%lo(GODZ_GameFlag)($17)
	addiu	$2,$0,1
	bne	$3,$2,$Lvcd_n05_800CB288_18
	addiu	$2,$0,4
	j	$Lvcd_n05_800CB288_18
	sw	$2,%lo(GODZ_GameFlag)($17)
$Lvcd_n05_800CB288_15:
	lb	$3,2953($16)
	nop
	beq	$3,$2,$Lvcd_n05_800CB288_18
	nop
	lbu	$3,2990($16)
	nop
	andi	$2,$3,0x4
	beq	$2,$0,$Lvcd_n05_800CB288_18
	andi	$2,$3,0x8
	beq	$2,$0,$Lvcd_n05_800CB288_16
	lui	$4,%hi(GODZ_GameFlag)
	lw	$3,%lo(GODZ_GameFlag)($4)
	addiu	$2,$0,2
	beq	$3,$2,$Lvcd_n05_800CB288_17
	addiu	$2,$0,6
	j	$Lvcd_n05_800CB288_17
	sw	$2,%lo(GODZ_GameFlag)($4)
$Lvcd_n05_800CB288_16:
	lui	$3,%hi(GODZ_GameFlag)
	addiu	$2,$0,2
	sw	$2,%lo(GODZ_GameFlag)($3)
$Lvcd_n05_800CB288_17:
	jal	vcd_n05_800CA1E8
	addu	$4,$16,$0
$Lvcd_n05_800CB288_18:
	lw	$31,28($29)
	lw	$18,24($29)
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
	.globl	vcd_n05_800CB5B0
vcd_n05_800CB5B0:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CB5B8
vcd_n05_800CB5B8:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$31,28($29)
	sw	$18,24($29)
	sw	$16,16($29)
	lh	$16,2868($17)
	addiu	$18,$0,5
	beq	$16,$18,$Lvcd_n05_800CB5B8_4
	slti	$2,$16,6
	beq	$2,$0,$Lvcd_n05_800CB5B8_0
	addiu	$2,$0,4
	beq	$16,$2,$Lvcd_n05_800CB5B8_1
	nop
	j	$Lvcd_n05_800CB5B8_9
	nop
$Lvcd_n05_800CB5B8_0:
	addiu	$2,$0,6
	beq	$16,$2,$Lvcd_n05_800CB5B8_7
	nop
	j	$Lvcd_n05_800CB5B8_9
	nop
$Lvcd_n05_800CB5B8_1:
	jal	vcd_n05_800CA96C
	addu	$4,$17,$0
	beq	$2,$0,$Lvcd_n05_800CB5B8_9
	addiu	$2,$0,71
	lb	$3,2949($17)
	nop
	bne	$3,$2,$Lvcd_n05_800CB5B8_3
	lui	$2,%hi(GODZ_GameFlag)
	lui	$3,%hi(GODZ_GameFlag)
	lw	$2,%lo(GODZ_GameFlag)($3)
	nop
	bne	$2,$16,$Lvcd_n05_800CB5B8_2
	addiu	$2,$0,2
	sh	$18,2868($17)
	j	$Lvcd_n05_800CB5B8_9
	sw	$0,2872($17)
$Lvcd_n05_800CB5B8_2:
	sw	$2,%lo(GODZ_GameFlag)($3)
	addiu	$2,$0,6
	sh	$2,2868($17)
	j	$Lvcd_n05_800CB5B8_9
	sw	$0,2872($17)
$Lvcd_n05_800CB5B8_3:
	lw	$3,%lo(GODZ_GameFlag)($2)
	addiu	$2,$0,6
	beq	$3,$2,$Lvcd_n05_800CB5B8_5
	addu	$4,$17,$0
	addiu	$2,$0,7
	sb	$2,2954($17)
	j	$Lvcd_n05_800CB5B8_8
	sb	$2,2953($17)
$Lvcd_n05_800CB5B8_4:
	jal	vcd_n05_800CA9C4
	addu	$4,$17,$0
	beq	$2,$0,$Lvcd_n05_800CB5B8_9
	lui	$16,%hi(GODZ_GameFlag)
	lw	$3,%lo(GODZ_GameFlag)($16)
	addiu	$2,$0,4
	bne	$3,$2,$Lvcd_n05_800CB5B8_6
	addu	$4,$17,$0
$Lvcd_n05_800CB5B8_5:
	jal	vcd_n05_800CA0BC
	addu	$4,$17,$0
	j	$Lvcd_n05_800CB5B8_9
	nop
$Lvcd_n05_800CB5B8_6:
	addiu	$2,$0,6
	sb	$2,2954($17)
	jal	vcd_n05_800CB0D4
	sb	$2,2953($17)
	jal	vcd_n05_800C9E84
	addu	$4,$17,$0
	lw	$2,2552($17)
	addu	$4,$17,$0
	addiu	$2,$2,-1
	jal	vcd_n05_800CA0A4
	sw	$2,2884($4)
	addiu	$2,$0,2
	j	$Lvcd_n05_800CB5B8_9
	sw	$2,%lo(GODZ_GameFlag)($16)
$Lvcd_n05_800CB5B8_7:
	jal	vcd_n05_800CAA28
	addu	$4,$17,$0
	beq	$2,$0,$Lvcd_n05_800CB5B8_9
	addiu	$2,$0,71
	lb	$3,2949($17)
	nop
	bne	$3,$2,$Lvcd_n05_800CB5B8_9
	addu	$4,$17,$0
	sb	$16,2954($17)
	sb	$16,2953($17)
$Lvcd_n05_800CB5B8_8:
	jal	vcd_n05_800CB0D4
	nop
	jal	vcd_n05_800C9E84
	addu	$4,$17,$0
	lw	$2,2552($17)
	addu	$4,$17,$0
	addiu	$2,$2,-1
	jal	vcd_n05_800CA0A4
	sw	$2,2884($4)
$Lvcd_n05_800CB5B8_9:
	lw	$31,28($29)
	lw	$18,24($29)
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
	.globl	vcd_n05_800CB74C
vcd_n05_800CB74C:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lh	$3,2868($16)
	addiu	$17,$0,12
	beq	$3,$17,$Lvcd_n05_800CB74C_2
	slti	$2,$3,13
	beq	$2,$0,$Lvcd_n05_800CB74C_0
	addiu	$2,$0,11
	beq	$3,$2,$Lvcd_n05_800CB74C_1
	nop
	j	$Lvcd_n05_800CB74C_6
	nop
$Lvcd_n05_800CB74C_0:
	addiu	$2,$0,13
	beq	$3,$2,$Lvcd_n05_800CB74C_5
	nop
	j	$Lvcd_n05_800CB74C_6
	nop
$Lvcd_n05_800CB74C_1:
	jal	vcd_n05_800CAA8C
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB74C_6
	nop
	sh	$17,2868($16)
	j	$Lvcd_n05_800CB74C_6
	sw	$0,2872($16)
$Lvcd_n05_800CB74C_2:
	jal	vcd_n05_800CAB3C
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB74C_6
	addiu	$2,$0,71
	lb	$3,2949($16)
	nop
	bne	$3,$2,$Lvcd_n05_800CB74C_4
	lui	$4,%hi(GODZ_GameFlag)
	lw	$3,%lo(GODZ_GameFlag)($4)
	addiu	$2,$0,2
	beq	$3,$2,$Lvcd_n05_800CB74C_3
	addiu	$2,$0,3
	sw	$2,%lo(GODZ_GameFlag)($4)
$Lvcd_n05_800CB74C_3:
	jal	vcd_n05_800CA0E4
	addu	$4,$16,$0
	j	$Lvcd_n05_800CB74C_6
	nop
$Lvcd_n05_800CB74C_4:
	jal	vcd_n05_800CA170
	addu	$4,$16,$0
	j	$Lvcd_n05_800CB74C_6
	nop
$Lvcd_n05_800CB74C_5:
	jal	vcd_n05_800CAB88
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB74C_6
	nop
	jal	vcd_n05_800CA0E4
	addu	$4,$16,$0
	addiu	$2,$0,240
	sh	$2,2906($16)
	addiu	$2,$0,255
	sw	$2,2980($16)
$Lvcd_n05_800CB74C_6:
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
	.globl	vcd_n05_800CB848
vcd_n05_800CB848:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lhu	$2,2868($16)
	nop
	addiu	$2,$2,-4
	sll	$2,$2,16
	sra	$3,$2,16
	sltiu	$2,$3,19
	beq	$2,$0,$Lvcd_n05_800CB848_7
	lui	$2,%hi(vcd_n05_800CB848_jtbl_800DE970)
	addiu	$2,$2,%lo(vcd_n05_800CB848_jtbl_800DE970)
	sll	$3,$3,2
	addu	$3,$3,$2
	lw	$2,0($3)
	nop
	jr	$2
	nop
$Lvcd_n05_800CB848_0:
	jal	vcd_n05_800CADD0
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB848_7
	addiu	$2,$0,22
	j	$Lvcd_n05_800CB848_6
	sh	$2,2868($16)
$Lvcd_n05_800CB848_1:
	jal	vcd_n05_800CAE80
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB848_7
	addiu	$2,$0,22
	j	$Lvcd_n05_800CB848_6
	sh	$2,2868($16)
$Lvcd_n05_800CB848_2:
	jal	vcd_n05_800CAEE0
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB848_7
	addiu	$2,$0,4
	j	$Lvcd_n05_800CB848_6
	sh	$2,2868($16)
$Lvcd_n05_800CB848_3:
	jal	vcd_n05_800CAF64
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB848_7
	lui	$2,%hi(GODZ_GameFlag)
	lw	$3,%lo(GODZ_GameFlag)($2)
	addiu	$2,$0,2
	bne	$3,$2,$Lvcd_n05_800CB848_4
	addiu	$2,$0,4
	sh	$0,2864($16)
	sh	$2,2866($16)
	sh	$2,2868($16)
	j	$Lvcd_n05_800CB848_6
	sw	$0,2872($16)
$Lvcd_n05_800CB848_4:
	jal	vcd_n05_800CA170
	addu	$4,$16,$0
	j	$Lvcd_n05_800CB848_7
	sw	$0,2872($16)
$Lvcd_n05_800CB848_5:
	jal	vcd_n05_800CB008
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB848_7
	nop
	sh	$2,2868($16)
$Lvcd_n05_800CB848_6:
	sw	$0,2872($16)
$Lvcd_n05_800CB848_7:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CB948
vcd_n05_800CB948:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lh	$3,2868($16)
	addiu	$17,$0,14
	beq	$3,$17,$Lvcd_n05_800CB948_0
	addiu	$2,$0,15
	beq	$3,$2,$Lvcd_n05_800CB948_1
	nop
	j	$Lvcd_n05_800CB948_4
	nop
$Lvcd_n05_800CB948_0:
	jal	vcd_n05_800C9EBC
	addu	$4,$16,$0
	jal	vcd_n05_800CABF0
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CB948_4
	addiu	$2,$0,15
	j	$Lvcd_n05_800CB948_3
	sh	$2,2868($16)
$Lvcd_n05_800CB948_1:
	jal	vcd_n05_800CAD3C
	addu	$4,$16,$0
	bgez	$2,$Lvcd_n05_800CB948_2
	nop
	j	$Lvcd_n05_800CB948_3
	sh	$17,2868($16)
$Lvcd_n05_800CB948_2:
	blez	$2,$Lvcd_n05_800CB948_4
	addiu	$2,$0,9
	sh	$2,2866($16)
	addiu	$2,$0,22
	sh	$2,2868($16)
$Lvcd_n05_800CB948_3:
	sw	$0,2872($16)
$Lvcd_n05_800CB948_4:
	lw	$2,3128($16)
	lw	$3,3080($16)
	nop
	slt	$2,$2,$3
	beq	$2,$0,$Lvcd_n05_800CB948_6
	slti	$2,$3,7000
	beq	$2,$0,$Lvcd_n05_800CB948_5
	addiu	$2,$0,2
	lh	$3,2974($16)
	nop
	bne	$3,$2,$Lvcd_n05_800CB948_7
	nop
$Lvcd_n05_800CB948_5:
	addiu	$2,$0,9
	sh	$2,2866($16)
	addiu	$2,$0,22
	sh	$2,2868($16)
	sw	$0,2872($16)
$Lvcd_n05_800CB948_6:
	lh	$3,2974($16)
	addiu	$2,$0,2
	bne	$3,$2,$Lvcd_n05_800CB948_7
	addiu	$2,$0,255
	sw	$2,2980($16)
$Lvcd_n05_800CB948_7:
	jal	GODZ_SetGoPointLast
	nop
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
	.globl	vcd_n05_800CBA40
vcd_n05_800CBA40:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lh	$17,2868($16)
	addiu	$3,$0,9
	beq	$17,$3,$Lvcd_n05_800CBA40_0
	addiu	$2,$0,23
	bne	$17,$2,$Lvcd_n05_800CBA40_2
	lui	$2,%hi(GODZ_GameFlag)
	sh	$3,2868($16)
	j	$Lvcd_n05_800CBA40_2
	sw	$0,2872($16)
$Lvcd_n05_800CBA40_0:
	jal	vcd_n05_800C9EBC
	addu	$4,$16,$0
	addu	$4,$16,$0
	jal	vcd_n05_800CAC60
	addiu	$5,$0,3000
	beq	$2,$0,$Lvcd_n05_800CBA40_1
	lui	$4,%hi(GODZ_GameFlag)
	lw	$3,%lo(GODZ_GameFlag)($4)
	addiu	$2,$0,22
	sh	$2,2868($16)
	addiu	$2,$0,2
	sh	$17,2866($16)
	beq	$3,$2,$Lvcd_n05_800CBA40_3
	sw	$0,2872($16)
	addiu	$2,$0,5
	sw	$2,%lo(GODZ_GameFlag)($4)
$Lvcd_n05_800CBA40_1:
	lui	$2,%hi(GODZ_GameFlag)
$Lvcd_n05_800CBA40_2:
	lw	$3,%lo(GODZ_GameFlag)($2)
	addiu	$2,$0,2
	bne	$3,$2,$Lvcd_n05_800CBA40_4
	nop
$Lvcd_n05_800CBA40_3:
	addiu	$2,$0,4
	sh	$0,2864($16)
	sh	$2,2866($16)
	sh	$2,2868($16)
	sw	$0,2872($16)
$Lvcd_n05_800CBA40_4:
	lbu	$2,2990($16)
	nop
	andi	$2,$2,0x4
	beq	$2,$0,$Lvcd_n05_800CBA40_5
	nop
	sh	$0,2864($16)
	jal	vcd_n05_800CA1E8
	addu	$4,$16,$0
$Lvcd_n05_800CBA40_5:
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
	.globl	vcd_n05_800CBB14
vcd_n05_800CBB14:
	addiu	$29,$29,-32
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$31,28($29)
	lh	$3,2868($16)
	addiu	$2,$0,8
	beq	$3,$2,$Lvcd_n05_800CBB14_0
	addiu	$2,$0,9
	beq	$3,$2,$Lvcd_n05_800CBB14_1
	addu	$4,$16,$0
	j	$Lvcd_n05_800CBB14_3
	nop
$Lvcd_n05_800CBB14_0:
	jal	vcd_n05_800CABF0
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CBB14_3
	addiu	$2,$0,9
	j	$Lvcd_n05_800CBB14_2
	sh	$2,2868($16)
$Lvcd_n05_800CBB14_1:
	jal	vcd_n05_800CAC60
	addiu	$5,$0,1500
	beq	$2,$0,$Lvcd_n05_800CBB14_3
	lui	$4,%hi(godz_str_tuita)
	lb	$5,2948($16)
	lh	$6,32($16)
	lh	$7,34($16)
	addiu	$2,$0,13
	sh	$2,2866($16)
	addiu	$2,$0,25
	sh	$2,2868($16)
	lh	$2,36($16)
	addiu	$4,$4,%lo(godz_str_tuita)
	jal	printf
	sw	$2,16($29)
	sw	$0,2892($16)
$Lvcd_n05_800CBB14_2:
	sw	$0,2872($16)
$Lvcd_n05_800CBB14_3:
	lw	$31,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CBBB0
vcd_n05_800CBBB0:
	addiu	$29,$29,-24
	sw	$16,16($29)
	sw	$31,20($29)
	jal	vcd_n05_800C9EBC
	addu	$16,$4,$0
	jal	vcd_n05_800CABF0
	addu	$4,$16,$0
	bne	$2,$0,$Lvcd_n05_800CBBB0_0
	addiu	$2,$0,13
	lw	$2,3128($16)
	lw	$3,3080($16)
	nop
	slt	$2,$2,$3
	bne	$2,$0,$Lvcd_n05_800CBBB0_0
	addiu	$2,$0,13
	lui	$2,%hi(GM_AlertLevel)
	lw	$3,%lo(GM_AlertLevel)($2)
	addiu	$2,$0,100
	bne	$3,$2,$Lvcd_n05_800CBBB0_1
	addiu	$2,$0,13
$Lvcd_n05_800CBBB0_0:
	sh	$2,2866($16)
	addiu	$2,$0,24
	sh	$2,2868($16)
	addiu	$2,$0,2
	sh	$2,2870($16)
	sw	$0,2892($16)
	sw	$0,2872($16)
$Lvcd_n05_800CBBB0_1:
	lw	$2,2980($16)
	nop
	slti	$2,$2,2
	beq	$2,$0,$Lvcd_n05_800CBBB0_2
	nop
	lbu	$2,2990($16)
	nop
	andi	$2,$2,0x2
	beq	$2,$0,$Lvcd_n05_800CBBB0_3
	nop
$Lvcd_n05_800CBBB0_2:
	jal	vcd_n05_800CA0BC
	addu	$4,$16,$0
$Lvcd_n05_800CBBB0_3:
	lbu	$2,2990($16)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$Lvcd_n05_800CBBB0_4
	lui	$2,%hi(GM_NoisePower)
	lw	$3,%lo(GM_NoisePower)($2)
	addiu	$2,$0,5
	beq	$3,$2,$Lvcd_n05_800CBBB0_4
	nop
	jal	vcd_n05_800C9F04
	addu	$4,$16,$0
	jal	GODZ_SetGoPointNoise
	nop
	addiu	$2,$0,7
	sh	$2,2866($16)
	addiu	$2,$0,12
	sh	$2,2868($16)
	sw	$0,2872($16)
$Lvcd_n05_800CBBB0_4:
	lbu	$3,2990($16)
	nop
	andi	$2,$3,0x10
	beq	$2,$0,$Lvcd_n05_800CBBB0_5
	andi	$2,$3,0x4
	jal	vcd_n05_800CA2D4
	addu	$4,$16,$0
	j	$Lvcd_n05_800CBBB0_6
	sw	$0,2892($16)
$Lvcd_n05_800CBBB0_5:
	beq	$2,$0,$Lvcd_n05_800CBBB0_6
	nop
	jal	vcd_n05_800CA1E8
	addu	$4,$16,$0
	sw	$0,2892($16)
$Lvcd_n05_800CBBB0_6:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	vcd_n05_800CBCDC
vcd_n05_800CBCDC:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lh	$3,2868($16)
	addiu	$17,$0,21
	beq	$3,$17,$Lvcd_n05_800CBCDC_2
	slti	$2,$3,22
	beq	$2,$0,$Lvcd_n05_800CBCDC_0
	addiu	$2,$0,11
	beq	$3,$2,$Lvcd_n05_800CBCDC_1
	nop
	j	$Lvcd_n05_800CBCDC_3
	nop
$Lvcd_n05_800CBCDC_0:
	addiu	$2,$0,25
	bne	$3,$2,$Lvcd_n05_800CBCDC_3
	nop
	jal	vcd_n05_800CA3E0
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CBCDC_3
	addiu	$2,$0,11
	sh	$2,2868($16)
	j	$Lvcd_n05_800CBCDC_3
	sw	$0,2872($16)
$Lvcd_n05_800CBCDC_1:
	jal	vcd_n05_800CA498
	addu	$4,$16,$0
	beq	$2,$0,$Lvcd_n05_800CBCDC_3
	nop
	sh	$17,2868($16)
	j	$Lvcd_n05_800CBCDC_3
	sw	$0,2872($16)
$Lvcd_n05_800CBCDC_2:
	jal	vcd_n05_800CA4E4
	addu	$4,$16,$0
$Lvcd_n05_800CBCDC_3:
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
	.globl	vcd_n05_800CBD78
vcd_n05_800CBD78:
	addiu	$29,$29,-24
	sw	$31,16($29)
	lh	$3,2866($4)
	addiu	$2,$0,4
	beq	$3,$2,$Lvcd_n05_800CBD78_3
	slti	$2,$3,5
	beq	$2,$0,$Lvcd_n05_800CBD78_0
	nop
	beq	$3,$0,$Lvcd_n05_800CBD78_2
	nop
	j	$Lvcd_n05_800CBD78_5
	nop
$Lvcd_n05_800CBD78_0:
	addiu	$2,$0,6
	beq	$3,$2,$Lvcd_n05_800CBD78_1
	addiu	$2,$0,7
	beq	$3,$2,$Lvcd_n05_800CBD78_4
	nop
	j	$Lvcd_n05_800CBD78_5
	nop
$Lvcd_n05_800CBD78_1:
	jal	vcd_n05_800CB054
	nop
	j	$Lvcd_n05_800CBD78_5
	nop
$Lvcd_n05_800CBD78_2:
	jal	vcd_n05_800CB288
	nop
	j	$Lvcd_n05_800CBD78_5
	nop
$Lvcd_n05_800CBD78_3:
	lhu	$2,90($4)
	nop
	ori	$2,$2,0x1000
	jal	vcd_n05_800CB5B8
	sh	$2,90($4)
	j	$Lvcd_n05_800CBD78_5
	nop
$Lvcd_n05_800CBD78_4:
	lhu	$2,90($4)
	nop
	ori	$2,$2,0x1000
	jal	vcd_n05_800CB74C
	sh	$2,90($4)
$Lvcd_n05_800CBD78_5:
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
	.globl	vcd_n05_800CBE24
vcd_n05_800CBE24:
	addiu	$29,$29,-24
	sw	$31,16($29)
	lh	$3,2866($4)
	addiu	$2,$0,8
	beq	$3,$2,$Lvcd_n05_800CBE24_1
	slti	$2,$3,9
	beq	$2,$0,$Lvcd_n05_800CBE24_0
	addiu	$2,$0,7
	beq	$3,$2,$Lvcd_n05_800CBE24_4
	nop
	j	$Lvcd_n05_800CBE24_5
	nop
$Lvcd_n05_800CBE24_0:
	addiu	$2,$0,9
	beq	$3,$2,$Lvcd_n05_800CBE24_2
	addiu	$2,$0,10
	beq	$3,$2,$Lvcd_n05_800CBE24_3
	nop
	j	$Lvcd_n05_800CBE24_5
	nop
$Lvcd_n05_800CBE24_1:
	jal	vcd_n05_800CB948
	nop
	j	$Lvcd_n05_800CBE24_5
	nop
$Lvcd_n05_800CBE24_2:
	jal	vcd_n05_800CB848
	nop
	j	$Lvcd_n05_800CBE24_5
	nop
$Lvcd_n05_800CBE24_3:
	jal	vcd_n05_800CBA40
	nop
	j	$Lvcd_n05_800CBE24_5
	nop
$Lvcd_n05_800CBE24_4:
	jal	vcd_n05_800CB74C
	nop
$Lvcd_n05_800CBE24_5:
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
	.globl	vcd_n05_800CBEB8
vcd_n05_800CBEB8:
	addiu	$29,$29,-24
	sw	$31,16($29)
	lh	$3,2866($4)
	addiu	$2,$0,7
	beq	$3,$2,$Lvcd_n05_800CBEB8_4
	slti	$2,$3,8
	beq	$2,$0,$Lvcd_n05_800CBEB8_0
	addiu	$2,$0,4
	beq	$3,$2,$Lvcd_n05_800CBEB8_3
	nop
	j	$Lvcd_n05_800CBEB8_5
	nop
$Lvcd_n05_800CBEB8_0:
	addiu	$2,$0,11
	beq	$3,$2,$Lvcd_n05_800CBEB8_1
	addiu	$2,$0,13
	beq	$3,$2,$Lvcd_n05_800CBEB8_2
	nop
	j	$Lvcd_n05_800CBEB8_5
	nop
$Lvcd_n05_800CBEB8_1:
	jal	vcd_n05_800CBB14
	nop
	j	$Lvcd_n05_800CBEB8_5
	nop
$Lvcd_n05_800CBEB8_2:
	jal	vcd_n05_800CBCDC
	nop
	j	$Lvcd_n05_800CBEB8_5
	nop
$Lvcd_n05_800CBEB8_3:
	jal	vcd_n05_800CB5B8
	nop
	j	$Lvcd_n05_800CBEB8_5
	nop
$Lvcd_n05_800CBEB8_4:
	jal	vcd_n05_800CB74C
	nop
$Lvcd_n05_800CBEB8_5:
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
	.globl	vcd_n05_800CBF4C
vcd_n05_800CBF4C:
	addiu	$29,$29,-24
	addiu	$2,$0,-1
	sw	$31,16($29)
	lh	$3,2864($4)
	addiu	$5,$0,1
	sh	$2,2904($4)
	beq	$3,$5,$Lvcd_n05_800CBF4C_2
	sw	$0,2888($4)
	slti	$2,$3,2
	beq	$2,$0,$Lvcd_n05_800CBF4C_0
	nop
	beq	$3,$0,$Lvcd_n05_800CBF4C_1
	nop
	j	$Lvcd_n05_800CBF4C_4
	nop
$Lvcd_n05_800CBF4C_0:
	addiu	$2,$0,2
	beq	$3,$2,$Lvcd_n05_800CBF4C_3
	nop
	j	$Lvcd_n05_800CBF4C_4
	nop
$Lvcd_n05_800CBF4C_1:
	jal	vcd_n05_800CBD78
	sh	$5,2278($4)
	j	$Lvcd_n05_800CBF4C_4
	nop
$Lvcd_n05_800CBF4C_2:
	jal	vcd_n05_800CBE24
	sh	$3,2278($4)
	j	$Lvcd_n05_800CBF4C_4
	nop
$Lvcd_n05_800CBF4C_3:
	jal	vcd_n05_800CBEB8
	sh	$0,2278($4)
$Lvcd_n05_800CBF4C_4:
	lw	$31,16($29)
	nop
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
godz_str_target_map:
	.ascii	"work->target_map %d to %d \n"
	.byte	0
	.align	2
godz_str_kirari01:
	.ascii	"kirari01"
	.byte	0
	.align	2
godz_str_c_root:
	.ascii	"c_root= %d root %d pat %d n_points = %d \n"
	.byte	0
	.align	2
godz_str_action:
	.ascii	"action = 0x%x \n"
	.byte	0
	.align	2
godz_str_root_change:
	.ascii	" Root Change !!\n"
	.byte	0
	.align	3
vcd_n05_800CB848_jtbl_800DE970:
	.word	$Lvcd_n05_800CB848_3
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_0
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_1
	.word	$Lvcd_n05_800CB848_2
	.word	$Lvcd_n05_800CB848_7
	.word	$Lvcd_n05_800CB848_5
	.align	2
godz_str_tuita:
	.ascii	"ID[%d] tuita!! %d %d %d\n"
	.byte	0
	.data
	.align	2
godzthk_data:
	.word	0x00320064
	.word	0x000A0019
	.word	0x000F012C
	.word	0x003C001E
	.word	0x0000005A
	.word	0x75307D01
	.word	0x00000000
	.word	0x00000001
	.word	0x00000002
	.word	0x00000004
	.word	0x00000004
	.word	0x00000040
	.word	0x00000080
	.word	0x00000200
	.word	0x00000400
	.word	0x00000800
	.word	0x00000100
	.word	0x00010000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000001
	.word	0x00000002
	.word	0x00000004
	.word	0x00000004
	.word	0x00000040
	.word	0x00000080
	.word	0x00000200
	.word	0x00000400
	.word	0x00000800
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.text
