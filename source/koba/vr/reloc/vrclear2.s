	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DE6F8
Vrclear2_800DE6F8:
	addiu	$29,$29,-48
	sw	$20,40($29)
	addu	$20,$4,$0
	sw	$17,28($29)
	addu	$17,$5,$0
	lui	$2,%hi(vrclear2_rect)
	sw	$19,36($29)
	addiu	$19,$29,16
	addu	$4,$19,$0
	sw	$31,44($29)
	sw	$18,32($29)
	sw	$16,24($29)
	addiu	$11,$2,%lo(vrclear2_rect)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,19($29)
	swr	$8,16($29)
	swl	$9,23($29)
	swr	$9,20($29)
	lui	$2,%hi(vrclear2_flags)
	addiu	$18,$2,%lo(vrclear2_flags)
	jal	StoreImage
	addu	$5,$18,$0
	jal	DrawSync
	addu	$4,$0,$0
	blez	$17,$LVrclear2_800DE6F8_0
	addu	$5,$17,$0
	lui	$4,%hi(vrclear2_str_stage)
	addiu	$4,$4,%lo(vrclear2_str_stage)
	jal	printf
	sra	$16,$17,5
	lui	$4,%hi(vrclear2_str_area)
	addiu	$4,$4,%lo(vrclear2_str_area)
	jal	printf
	addu	$5,$16,$0
	lui	$4,%hi(vrclear2_str_flags)
	addiu	$4,$4,%lo(vrclear2_str_flags)
	addiu	$5,$20,-1
	sll	$6,$16,2
	sll	$2,$5,1
	addu	$2,$2,$5
	sll	$2,$2,3
	addu	$6,$6,$2
	addu	$6,$6,$18
	sll	$2,$16,5
	subu	$2,$17,$2
	addiu	$7,$0,1
	lw	$3,0($6)
	sllv	$7,$7,$2
	or	$3,$3,$7
	sw	$3,0($6)
	jal	printf
	addu	$6,$16,$0
$LVrclear2_800DE6F8_0:
	addu	$4,$19,$0
	jal	LoadImage
	addu	$5,$18,$0
	jal	DrawSync
	addu	$4,$0,$0
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DE808
Vrclear2_800DE808:
	ori	$2,$0,0xedaf
	beq	$4,$2,$LVrclear2_800DE808_0
	addiu	$4,$0,1
	jr	$31
	addu	$2,$0,$0
$LVrclear2_800DE808_0:
	addiu	$3,$0,4
	lui	$2,%hi(vrclear2_data)
	addiu	$2,$2,%lo(vrclear2_data)
	addiu	$2,$2,480
$LVrclear2_800DE808_1:
	sb	$4,34($2)
	addiu	$3,$3,-1
	bgez	$3,$LVrclear2_800DE808_1
	addiu	$2,$2,-120
	jr	$31
	addiu	$2,$0,1
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DE844
Vrclear2_800DE844:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$5,$0
	bne	$16,$0,$LVrclear2_800DE844_0
	sw	$31,20($29)
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,102
$LVrclear2_800DE844_0:
	addiu	$2,$0,1
	bne	$16,$2,$LVrclear2_800DE844_1
	addiu	$2,$0,2
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,102
	addiu	$2,$0,2
$LVrclear2_800DE844_1:
	bne	$16,$2,$LVrclear2_800DE844_2
	addiu	$2,$0,3
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,33
	addiu	$2,$0,3
$LVrclear2_800DE844_2:
	bne	$16,$2,$LVrclear2_800DE844_3
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,33
$LVrclear2_800DE844_3:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DE8C8
Vrclear2_800DE8C8:
	addiu	$29,$29,-24
	addiu	$4,$0,200
	addu	$5,$4,$0
	addu	$6,$4,$0
	sw	$31,20($29)
	jal	MENU_Color
	sw	$16,16($29)
	addiu	$4,$0,8
	addu	$5,$4,$0
	jal	MENU_Locate
	addiu	$6,$0,16
	lui	$16,%hi(vrclear2_str_demo)
	addiu	$16,$16,%lo(vrclear2_str_demo)
	jal	MENU_Printf
	addu	$4,$16,$0
	addiu	$4,$0,10
	addu	$5,$4,$0
	jal	MENU_Color
	addu	$6,$4,$0
	addiu	$4,$0,9
	addu	$5,$4,$0
	jal	MENU_Locate
	addiu	$6,$0,16
	jal	MENU_Printf
	addu	$4,$16,$0
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DE93C
Vrclear2_800DE93C:
	addiu	$29,$29,-24
	addiu	$4,$0,200
	addu	$5,$4,$0
	addu	$6,$4,$0
	sw	$31,20($29)
	jal	MENU_Color
	sw	$16,16($29)
	addiu	$4,$0,8
	addu	$5,$4,$0
	jal	MENU_Locate
	addiu	$6,$0,16
	lui	$16,%hi(vrclear2_str_replay_up)
	addiu	$16,$16,%lo(vrclear2_str_replay_up)
	jal	MENU_Printf
	addu	$4,$16,$0
	addiu	$4,$0,10
	addu	$5,$4,$0
	jal	MENU_Color
	addu	$6,$4,$0
	addiu	$4,$0,9
	addu	$5,$4,$0
	jal	MENU_Locate
	addiu	$6,$0,16
	jal	MENU_Printf
	addu	$4,$16,$0
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DE9B0
Vrclear2_800DE9B0:
	addiu	$29,$29,-24
	sw	$31,16($29)
	lw	$2,1012($4)
	addiu	$3,$0,-497
	and	$3,$2,$3
	srl	$2,$2,4
	andi	$2,$2,0x1f
	addiu	$2,$2,1
	andi	$2,$2,0x1f
	sll	$2,$2,4
	or	$3,$3,$2
	srl	$2,$3,4
	andi	$2,$2,0x1f
	slti	$2,$2,16
	bne	$2,$0,$LVrclear2_800DE9B0_1
	sw	$3,1012($4)
	andi	$2,$3,0x1
	beq	$2,$0,$LVrclear2_800DE9B0_1
	lui	$2,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($2)
	nop
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2_800DE9B0_0
	nop
	jal	Vrclear2_800DE93C
	nop
	j	$LVrclear2_800DE9B0_1
	nop
$LVrclear2_800DE9B0_0:
	jal	Vrclear2_800DE8C8
	nop
$LVrclear2_800DE9B0_1:
	lw	$31,16($29)
	nop
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DEA38
Vrclear2_800DEA38:
	addiu	$29,$29,-8
	sw	$16,0($29)
	addu	$13,$4,$0
	addu	$12,$5,$0
	bgez	$12,$LVrclear2_800DEA38_0
	addu	$2,$12,$0
	addu	$2,$0,$0
$LVrclear2_800DEA38_0:
	beq	$6,$0,$LVrclear2_800DEA38_1
	addu	$12,$2,$0
	lui	$2,%hi(VR_Records+12)
	lw	$3,%lo(VR_Records+12)($2)
	j	$LVrclear2_800DEA38_2
	lui	$7,0x8888
$LVrclear2_800DEA38_1:
	addu	$3,$12,$0
	lui	$7,0x8888
$LVrclear2_800DEA38_2:
	ori	$7,$7,0x8889
	mult	$3,$7
	mfhi	$2
	nop
	nop
	mult	$12,$7
	addu	$9,$2,$3
	sra	$9,$9,4
	sra	$2,$3,31
	subu	$9,$9,$2
	sll	$6,$9,4
	subu	$6,$6,$9
	sll	$6,$6,1
	subu	$6,$3,$6
	sll	$3,$6,1
	addu	$3,$3,$6
	sll	$3,$3,3
	mfhi	$8
	addu	$3,$3,$6
	sll	$3,$3,2
	mult	$3,$7
	sra	$2,$12,31
	addu	$5,$8,$12
	sra	$5,$5,4
	subu	$5,$5,$2
	sll	$4,$5,4
	subu	$4,$4,$5
	sll	$4,$4,1
	subu	$4,$12,$4
	sll	$2,$4,1
	addu	$2,$2,$4
	sll	$2,$2,3
	mfhi	$8
	addu	$2,$2,$4
	sll	$2,$2,2
	mult	$2,$7
	lui	$10,0x6666
	ori	$10,$10,0x6667
	addu	$8,$8,$3
	sra	$8,$8,4
	mfhi	$7
	sra	$3,$3,31
	subu	$8,$8,$3
	mult	$8,$10
	addu	$7,$7,$2
	sra	$7,$7,4
	mfhi	$15
	sra	$2,$2,31
	subu	$7,$7,$2
	mult	$7,$10
	mfhi	$24
	addu	$12,$5,$0
	nop
	mult	$12,$10
	mfhi	$2
	lui	$11,0x5555
	ori	$11,$11,0x5556
	mult	$4,$11
	lui	$5,0x2aaa
	ori	$5,$5,0xaaab
	sra	$3,$2,2
	sra	$2,$12,31
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	mfhi	$14
	subu	$2,$12,$2
	addu	$12,$3,$0
	mult	$12,$5
	sb	$0,8($13)
	addiu	$3,$0,58
	sra	$4,$4,31
	addiu	$2,$2,48
	mfhi	$16
	sb	$2,4($13)
	sra	$2,$12,31
	mult	$6,$11
	sb	$3,5($13)
	sb	$3,2($13)
	sra	$3,$15,2
	subu	$4,$14,$4
	addiu	$4,$4,48
	sb	$4,6($13)
	subu	$2,$16,$2
	sll	$5,$2,1
	addu	$5,$5,$2
	sll	$5,$5,1
	subu	$5,$12,$5
	mfhi	$4
	addu	$12,$2,$0
	sra	$2,$8,31
	mult	$12,$10
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$8,$8,$2
	sra	$6,$6,31
	andi	$8,$8,0xff
	sll	$2,$8,3
	subu	$2,$2,$8
	sll	$2,$2,2
	addu	$2,$2,$8
	mfhi	$11
	addu	$9,$9,$2
	subu	$6,$4,$6
	mult	$9,$6
	sra	$2,$12,31
	addiu	$5,$5,48
	sb	$5,3($13)
	sra	$3,$11,2
	subu	$3,$3,$2
	sll	$4,$3,2
	addu	$4,$4,$3
	sll	$4,$4,1
	subu	$4,$12,$4
	addu	$12,$3,$0
	sra	$3,$24,2
	mflo	$9
	sra	$2,$7,31
	subu	$3,$3,$2
	mult	$12,$10
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$7,$7,$2
	addiu	$7,$7,48
	addiu	$4,$4,48
	sb	$7,7($13)
	sb	$4,1($13)
	andi	$2,$9,0xff
	srl	$9,$2,1
	sra	$2,$12,31
	mfhi	$10
	sra	$3,$10,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$2,$12,$2
	addiu	$2,$2,48
	sb	$2,0($13)
	addiu	$2,$0,6
	bne	$8,$2,$LVrclear2_800DEA38_3
	andi	$4,$9,0xff
	j	$LVrclear2_800DEA38_4
	andi	$9,$9,0x3
$LVrclear2_800DEA38_3:
	lui	$2,0xaaaa
	ori	$2,$2,0xaaab
	multu	$4,$2
	mfhi	$25
	srl	$3,$25,1
	sll	$2,$3,1
	addu	$2,$2,$3
	subu	$9,$4,$2
$LVrclear2_800DEA38_4:
	lbu	$2,7($13)
	nop
	addu	$3,$2,$9
	andi	$2,$3,0xff
	sltiu	$2,$2,58
	bne	$2,$0,$LVrclear2_800DEA38_5
	sb	$3,7($13)
	lbu	$2,6($13)
	addiu	$3,$3,-10
	sb	$3,7($13)
	addiu	$2,$2,1
	sb	$2,6($13)
$LVrclear2_800DEA38_5:
	lw	$16,0($29)
	jr	$31
	addiu	$29,$29,8
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DED20
Vrclear2_800DED20:
	addiu	$29,$29,-80
	sw	$21,68($29)
	addu	$21,$4,$0
	sw	$19,60($29)
	sw	$16,48($29)
	lui	$16,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($16)
	lui	$3,%hi(vrclear2_ranks)
	sw	$31,76($29)
	sw	$22,72($29)
	sw	$20,64($29)
	sw	$18,56($29)
	sw	$17,52($29)
	addiu	$10,$3,%lo(vrclear2_ranks)
	lw	$7,0($10)
	lw	$8,4($10)
	lw	$9,8($10)
	sw	$7,32($29)
	sw	$8,36($29)
	sw	$9,40($29)
	lw	$7,12($10)
	nop
	sw	$7,44($29)
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2_800DED20_11
	addu	$19,$5,$0
	addiu	$4,$0,208
	addiu	$5,$0,107
	jal	MENU_Color
	addiu	$6,$0,57
	slti	$2,$21,9
	beq	$2,$0,$LVrclear2_800DED20_0
	addiu	$17,$0,8
	addu	$17,$21,$0
$LVrclear2_800DED20_0:
	lw	$2,%lo(VR_Flags)($16)
	nop
	andi	$2,$2,0x6
	srl	$20,$2,1
	slti	$2,$20,3
	bne	$2,$0,$LVrclear2_800DED20_1
	nop
	addiu	$20,$0,-1
$LVrclear2_800DED20_1:
	bltz	$20,$LVrclear2_800DED20_2
	addiu	$18,$0,60
	lui	$2,0x8888
	ori	$2,$2,0x8889
	addiu	$4,$21,15
	mult	$4,$2
	sra	$2,$4,31
	mfhi	$7
	addu	$3,$7,$4
	sra	$3,$3,4
	subu	$3,$3,$2
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,1
	bne	$4,$2,$LVrclear2_800DED20_2
	nop
	lw	$2,1012($19)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$LVrclear2_800DED20_2
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,192
$LVrclear2_800DED20_2:
	lw	$2,1012($19)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2_800DED20_3
	addu	$16,$0,$0
	addiu	$16,$0,3
$LVrclear2_800DED20_3:
	slti	$2,$16,4
	beq	$2,$0,$LVrclear2_800DED20_11
	lui	$2,0x8888
	ori	$2,$2,0x8889
	mult	$21,$2
	addiu	$3,$29,16
	addu	$22,$3,$17
	sll	$2,$16,2
	addu	$19,$2,$3
	addu	$17,$2,$0
	sra	$3,$21,31
	mfhi	$7
	addu	$2,$7,$21
	sra	$2,$2,3
	subu	$2,$2,$3
	andi	$21,$2,0x1
$LVrclear2_800DED20_4:
	bne	$16,$20,$LVrclear2_800DED20_5
	addiu	$2,$0,3
	beq	$21,$0,$LVrclear2_800DED20_10
	nop
$LVrclear2_800DED20_5:
	bne	$16,$2,$LVrclear2_800DED20_6
	sb	$0,0($22)
	addiu	$18,$18,12
$LVrclear2_800DED20_6:
	lui	$2,%hi(VR_Records)
	addiu	$2,$2,%lo(VR_Records)
	addu	$2,$17,$2
	lw	$2,0($2)
	nop
	blez	$2,$LVrclear2_800DED20_7
	addiu	$5,$0,107
	addiu	$4,$0,208
	j	$LVrclear2_800DED20_8
	addiu	$6,$0,57
$LVrclear2_800DED20_7:
	addiu	$4,$0,104
	addiu	$5,$0,53
	addiu	$6,$0,28
$LVrclear2_800DED20_8:
	jal	MENU_Color
	nop
	addiu	$4,$0,221
	addu	$5,$18,$0
	jal	MENU_Locate
	addiu	$6,$0,17
	lui	$4,%hi(vrclear2_str_d)
	lui	$2,%hi(VR_Records)
	addiu	$2,$2,%lo(VR_Records)
	addu	$2,$17,$2
	lw	$5,0($2)
	nop
	bgez	$5,$LVrclear2_800DED20_9
	nop
	subu	$5,$0,$5
$LVrclear2_800DED20_9:
	jal	MENU_Printf
	addiu	$4,$4,%lo(vrclear2_str_d)
	addiu	$4,$0,208
	addiu	$5,$0,107
	jal	MENU_Color
	addiu	$6,$0,57
	addiu	$4,$0,99
	addu	$5,$18,$0
	jal	MENU_Locate
	addiu	$6,$0,16
	lui	$4,%hi(vrclear2_str_s)
	lw	$5,16($19)
	jal	MENU_Printf
	addiu	$4,$4,%lo(vrclear2_str_s)
$LVrclear2_800DED20_10:
	addiu	$18,$18,12
	addiu	$19,$19,4
	addiu	$16,$16,1
	slti	$2,$16,4
	bne	$2,$0,$LVrclear2_800DED20_4
	addiu	$17,$17,4
$LVrclear2_800DED20_11:
	lw	$31,76($29)
	lw	$22,72($29)
	lw	$21,68($29)
	lw	$20,64($29)
	lw	$19,60($29)
	lw	$18,56($29)
	lw	$17,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,80
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DEF84
Vrclear2_800DEF84:
	addu	$6,$4,$0
	lw	$2,988($6)
	nop
	slti	$2,$2,5
	beq	$2,$0,$LVrclear2_800DEF84_4
	lui	$5,0x6666
	lw	$5,984($6)
	nop
	slti	$2,$5,20
	beq	$2,$0,$LVrclear2_800DEF84_2
	addiu	$4,$0,3
	lw	$2,988($6)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$LVrclear2_800DEF84_0
	sw	$5,1000($6)
	addiu	$4,$0,4
$LVrclear2_800DEF84_0:
	lw	$2,988($6)
	addiu	$3,$0,1
	slti	$2,$2,3
	beq	$2,$0,$LVrclear2_800DEF84_1
	sw	$4,992($6)
	addiu	$3,$0,2
$LVrclear2_800DEF84_1:
	j	$LVrclear2_800DEF84_6
	sw	$3,996($6)
$LVrclear2_800DEF84_2:
	lui	$2,0x6666
	ori	$2,$2,0x6667
	mult	$5,$2
	mfhi	$3
	lw	$4,984($6)
	nop
	mult	$4,$2
	sra	$3,$3,2
	sra	$2,$5,31
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$2,$5,$2
	lw	$3,988($6)
	sra	$4,$4,31
	sw	$2,1000($6)
	mfhi	$7
	sra	$2,$7,2
	subu	$2,$2,$4
	sw	$2,996($6)
	slti	$2,$3,3
	beq	$2,$0,$LVrclear2_800DEF84_3
	addiu	$2,$3,2
	j	$LVrclear2_800DEF84_6
	sw	$3,992($6)
$LVrclear2_800DEF84_3:
	j	$LVrclear2_800DEF84_6
	sw	$2,992($6)
$LVrclear2_800DEF84_4:
	lw	$4,984($6)
	ori	$5,$5,0x6667
	mult	$4,$5
	lw	$2,988($6)
	sw	$0,996($6)
	addiu	$2,$2,2
	sw	$2,992($6)
	sra	$2,$4,31
	mfhi	$8
	sra	$3,$8,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	lw	$3,988($6)
	subu	$4,$4,$2
	slti	$3,$3,7
	beq	$3,$0,$LVrclear2_800DEF84_5
	sw	$4,1000($6)
	lw	$4,984($6)
	nop
	mult	$4,$5
	sw	$0,1000($6)
	sra	$2,$4,31
	mfhi	$8
	sra	$3,$8,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$4,$4,$2
	sw	$4,996($6)
$LVrclear2_800DEF84_5:
	lw	$2,1000($6)
	nop
	bne	$2,$0,$LVrclear2_800DEF84_6
	addiu	$2,$0,12
	lw	$3,992($6)
	nop
	bne	$3,$2,$LVrclear2_800DEF84_6
	addiu	$2,$0,10
	sw	$2,1000($6)
$LVrclear2_800DEF84_6:
	lw	$2,996($6)
	nop
	slti	$2,$2,10
	bne	$2,$0,$LVrclear2_800DEF84_7
	addiu	$2,$0,9
	sw	$2,996($6)
$LVrclear2_800DEF84_7:
	lw	$2,992($6)
	nop
	slti	$2,$2,17
	bne	$2,$0,$LVrclear2_800DEF84_8
	addiu	$2,$0,16
	sw	$2,992($6)
$LVrclear2_800DEF84_8:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DF134
Vrclear2_800DF134:
	addiu	$29,$29,-64
	sw	$16,24($29)
	addu	$16,$4,$0
	lui	$5,0x6666
	sw	$31,60($29)
	sw	$30,56($29)
	sw	$23,52($29)
	sw	$22,48($29)
	sw	$21,44($29)
	sw	$20,40($29)
	sw	$19,36($29)
	sw	$18,32($29)
	sw	$17,28($29)
	sb	$0,18($29)
	lw	$4,1000($16)
	ori	$5,$5,0x6667
	mult	$4,$5
	sra	$2,$4,31
	mfhi	$7
	sra	$3,$7,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$4,$4,$2
	addiu	$4,$4,48
	sb	$4,17($29)
	lw	$2,1000($16)
	nop
	mult	$2,$5
	addu	$18,$0,$0
	sra	$2,$2,31
	mfhi	$7
	sra	$3,$7,2
	subu	$3,$3,$2
	lui	$2,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($2)
	addiu	$3,$3,48
	andi	$2,$2,0x8
	bne	$2,$0,$LVrclear2_800DF134_0
	sb	$3,16($29)
	addiu	$18,$0,15
$LVrclear2_800DF134_0:
	lh	$3,38($16)
	addiu	$2,$0,6
	beq	$3,$2,$LVrclear2_800DF134_11
	nop
	lw	$3,972($16)
	nop
	slti	$2,$3,161
	bne	$2,$0,$LVrclear2_800DF134_2
	addu	$17,$0,$0
	addiu	$2,$0,320
	bne	$3,$2,$LVrclear2_800DF134_1
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,195
$LVrclear2_800DF134_1:
	lw	$2,972($16)
	nop
	addiu	$2,$2,-20
	sw	$2,972($16)
	addu	$17,$0,$0
$LVrclear2_800DF134_2:
	lui	$7,%hi(vrclear2_str_s)
	addiu	$23,$7,%lo(vrclear2_str_s)
	lui	$2,%hi(vrclear2_data+600)
	addiu	$21,$2,%lo(vrclear2_data+600)
	lui	$30,%hi(vrclear2_data+668)
	addiu	$22,$30,%lo(vrclear2_data+668)
	addiu	$20,$18,40
	addiu	$19,$0,320
	addiu	$18,$18,25
$LVrclear2_800DF134_3:
	beq	$17,$0,$LVrclear2_800DF134_4
	addiu	$4,$0,50
	addu	$5,$4,$0
	j	$LVrclear2_800DF134_5
	addu	$6,$4,$0
$LVrclear2_800DF134_4:
	addiu	$4,$0,200
	lui	$2,%hi(GV_Clock)
	lw	$2,%lo(GV_Clock)($2)
	addu	$5,$4,$0
	sll	$6,$2,1
	addu	$6,$6,$2
	sll	$6,$6,3
	addu	$6,$6,$2
	sll	$6,$6,3
$LVrclear2_800DF134_5:
	jal	MENU_Color
	nop
	lw	$2,1012($16)
	nop
	srl	$2,$2,3
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2_800DF134_6
	addu	$5,$18,$0
	lw	$4,972($16)
	addiu	$6,$0,18
	jal	MENU_Locate
	addu	$4,$4,$17
	lw	$5,956($16)
	jal	MENU_Printf
	addu	$4,$23,$0
	addu	$5,$20,$0
	lw	$4,972($16)
	addiu	$6,$0,18
	jal	MENU_Locate
	subu	$4,$19,$4
	lw	$5,960($16)
	j	$LVrclear2_800DF134_10
	addu	$4,$23,$0
$LVrclear2_800DF134_6:
	lw	$2,1000($16)
	nop
	beq	$2,$0,$LVrclear2_800DF134_9
	addiu	$6,$0,18
	lw	$4,972($16)
	jal	MENU_Locate
	addu	$4,$4,$17
	lw	$2,996($16)
	nop
	beq	$2,$0,$LVrclear2_800DF134_7
	sll	$2,$2,2
	addu	$2,$2,$22
	lui	$4,%hi(vrclear2_str_fmt_dash)
	lw	$3,992($16)
	lw	$6,0($2)
	sll	$3,$3,2
	addu	$3,$3,$21
	lw	$5,0($3)
	j	$LVrclear2_800DF134_8
	addiu	$4,$4,%lo(vrclear2_str_fmt_dash)
$LVrclear2_800DF134_7:
	lui	$4,%hi(vrclear2_str_fmt_ss)
	lw	$2,992($16)
	lw	$6,%lo(vrclear2_data+668)($30)
	sll	$2,$2,2
	addu	$2,$2,$21
	lw	$5,0($2)
	addiu	$4,$4,%lo(vrclear2_str_fmt_ss)
$LVrclear2_800DF134_8:
	jal	MENU_Printf
	nop
	addu	$5,$20,$0
	lw	$4,972($16)
	addiu	$6,$0,18
	jal	MENU_Locate
	subu	$4,$19,$4
	lui	$4,%hi(vrclear2_str_level_cleared)
	addiu	$4,$4,%lo(vrclear2_str_level_cleared)
	j	$LVrclear2_800DF134_10
	addiu	$5,$29,16
$LVrclear2_800DF134_9:
	addu	$5,$18,$0
	lw	$4,972($16)
	jal	MENU_Locate
	addu	$4,$4,$17
	lw	$2,992($16)
	lui	$7,%hi(vrclear2_str_s)
	sll	$2,$2,2
	addu	$2,$2,$21
	lw	$5,0($2)
	jal	MENU_Printf
	addiu	$4,$7,%lo(vrclear2_str_s)
	addu	$5,$20,$0
	lw	$4,972($16)
	addiu	$6,$0,18
	jal	MENU_Locate
	subu	$4,$19,$4
	lw	$2,996($16)
	lui	$4,%hi(vrclear2_str_cleared)
	sll	$2,$2,2
	addu	$2,$2,$22
	lw	$5,0($2)
	addiu	$4,$4,%lo(vrclear2_str_cleared)
$LVrclear2_800DF134_10:
	jal	MENU_Printf
	addiu	$20,$20,1
	addiu	$19,$19,1
	addiu	$17,$17,1
	slti	$2,$17,2
	bne	$2,$0,$LVrclear2_800DF134_3
	addiu	$18,$18,1
$LVrclear2_800DF134_11:
	lw	$31,60($29)
	lw	$30,56($29)
	lw	$23,52($29)
	lw	$22,48($29)
	lw	$21,44($29)
	lw	$20,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DF420
Vrclear2_800DF420:
	addu	$7,$4,$0
	lui	$2,%hi(GV_PadData+32)
	lhu	$4,%lo(GV_PadData+32)($2)
	addiu	$29,$29,-24
	sw	$31,16($29)
	lw	$3,264($7)
	nop
	bne	$4,$3,$LVrclear2_800DF420_0
	addiu	$9,$2,%lo(GV_PadData+32)
	lhu	$2,950($7)
	nop
	addiu	$3,$2,-1
	sll	$2,$2,16
	bgtz	$2,$LVrclear2_800DF420_8
	sh	$3,950($7)
	j	$LVrclear2_800DF420_1
	addiu	$2,$0,1
$LVrclear2_800DF420_0:
	addiu	$2,$0,10
	sw	$4,264($7)
$LVrclear2_800DF420_1:
	sh	$2,950($7)
	andi	$2,$4,0xf000
	beq	$2,$0,$LVrclear2_800DF420_5
	andi	$2,$4,0x8000
	bne	$2,$0,$LVrclear2_800DF420_2
	addiu	$5,$0,1
	andi	$2,$4,0x4000
	bne	$2,$0,$LVrclear2_800DF420_2
	addiu	$5,$0,2
	andi	$2,$4,0x2000
	beq	$2,$0,$LVrclear2_800DF420_2
	addu	$5,$0,$0
	addiu	$5,$0,3
$LVrclear2_800DF420_2:
	lui	$2,%hi(vrclear2_data)
	addiu	$6,$2,%lo(vrclear2_data)
	lh	$3,34($7)
	sll	$8,$5,1
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,3
	addu	$2,$8,$2
	addu	$2,$2,$6
	lhu	$3,8($2)
	lh	$4,8($2)
	addiu	$2,$0,-1
	beq	$4,$2,$LVrclear2_800DF420_5
	sll	$2,$4,4
	subu	$2,$2,$4
	sll	$2,$2,3
	addu	$2,$2,$6
	lw	$2,16($2)
	nop
	bgtz	$2,$LVrclear2_800DF420_4
	addu	$4,$0,$0
	addu	$5,$6,$0
	addu	$6,$8,$0
	addiu	$8,$0,-1
$LVrclear2_800DF420_3:
	sll	$3,$3,16
	sra	$3,$3,16
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,3
	addu	$2,$6,$2
	addu	$2,$2,$5
	lh	$4,8($2)
	lhu	$3,8($2)
	beq	$4,$8,$LVrclear2_800DF420_8
	sll	$2,$4,4
	subu	$2,$2,$4
	sll	$2,$2,3
	addu	$2,$2,$5
	lw	$2,16($2)
	nop
	blez	$2,$LVrclear2_800DF420_3
	addu	$4,$0,$0
$LVrclear2_800DF420_4:
	addiu	$5,$0,63
	addiu	$6,$0,31
	sh	$3,36($7)
	jal	GM_SeSet2
	sh	$0,38($7)
	j	$LVrclear2_800DF420_9
	addu	$2,$0,$0
$LVrclear2_800DF420_5:
	lhu	$4,2($9)
	nop
	andi	$2,$4,0x20
	beq	$2,$0,$LVrclear2_800DF420_8
	lui	$2,%hi(vrclear2_data)
	lh	$3,34($7)
	addiu	$4,$2,%lo(vrclear2_data)
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,3
	addu	$2,$2,$4
	lw	$2,20($2)
	nop
	bltz	$2,$LVrclear2_800DF420_8
	addiu	$2,$0,3
	lbu	$3,954($7)
	sh	$2,38($7)
	beq	$3,$0,$LVrclear2_800DF420_7
	addu	$2,$4,$0
	addiu	$4,$0,3
	addiu	$2,$2,32
$LVrclear2_800DF420_6:
	addiu	$3,$3,-1
	sb	$4,2($2)
	sh	$0,0($2)
	bne	$3,$0,$LVrclear2_800DF420_6
	addiu	$2,$2,120
$LVrclear2_800DF420_7:
	lui	$2,%hi(vrclear2_data)
	lh	$4,34($7)
	addiu	$2,$2,%lo(vrclear2_data)
	sll	$3,$4,4
	subu	$3,$3,$4
	sll	$3,$3,3
	addu	$3,$3,$2
	sb	$0,34($3)
	lh	$5,34($7)
	jal	Vrclear2_800DE844
	addu	$4,$0,$0
$LVrclear2_800DF420_8:
	addu	$2,$0,$0
$LVrclear2_800DF420_9:
	lw	$31,16($29)
	nop
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DF60C
Vrclear2_800DF60C:
	lui	$2,%hi(GV_PadData+32)
	lhu	$5,%lo(GV_PadData+32)($2)
	lw	$2,264($4)
	nop
	beq	$5,$2,$LVrclear2_800DF60C_0
	addiu	$2,$0,1
	addiu	$3,$0,10
	sh	$3,950($4)
	andi	$3,$5,0xf0f0
	bne	$3,$0,$LVrclear2_800DF60C_1
	sw	$5,264($4)
$LVrclear2_800DF60C_0:
	addu	$2,$0,$0
$LVrclear2_800DF60C_1:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DF644
Vrclear2_800DF644:
	addiu	$29,$29,-56
	sw	$18,32($29)
	addu	$18,$4,$0
	sw	$31,48($29)
	sw	$21,44($29)
	sw	$20,40($29)
	sw	$19,36($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$4,40($18)
	jal	GV_ReceiveMessage
	addiu	$5,$29,16
	addu	$17,$2,$0
	blez	$17,$LVrclear2_800DF644_2
	ori	$21,$0,0xedaf
	lui	$20,%hi(vrclear2_str_clear)
	addiu	$19,$0,1
$LVrclear2_800DF644_0:
	lw	$3,16($29)
	nop
	lhu	$2,4($3)
	nop
	beq	$2,$21,$LVrclear2_800DF644_3
	ori	$2,$0,0xedaf
	lhu	$16,4($3)
	jal	GV_StrCode
	addiu	$4,$20,%lo(vrclear2_str_clear)
	bne	$16,$2,$LVrclear2_800DF644_1
	nop
	sw	$19,1004($18)
$LVrclear2_800DF644_1:
	lw	$2,16($29)
	addiu	$17,$17,-1
	addiu	$2,$2,20
	bgtz	$17,$LVrclear2_800DF644_0
	sw	$2,16($29)
$LVrclear2_800DF644_2:
	addu	$2,$0,$0
$LVrclear2_800DF644_3:
	lw	$31,48($29)
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DF6F4
Vrclear2_800DF6F4:
	addiu	$29,$29,-40
	sw	$18,32($29)
	addu	$18,$4,$0
	sw	$31,36($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$3,976($18)
	nop
	slti	$2,$3,111
	bne	$2,$0,$LVrclear2_800DF6F4_0
	addiu	$2,$3,12
	addiu	$2,$0,111
$LVrclear2_800DF6F4_0:
	sw	$2,976($18)
	lw	$3,980($18)
	nop
	slti	$2,$3,160
	bne	$2,$0,$LVrclear2_800DF6F4_1
	addiu	$2,$3,12
	addiu	$2,$0,160
$LVrclear2_800DF6F4_1:
	sw	$2,980($18)
	lhu	$2,980($18)
	addiu	$4,$18,112
	sh	$2,16($29)
	lhu	$2,976($18)
	addiu	$17,$0,320
	sh	$2,18($29)
	lw	$2,980($18)
	addiu	$5,$29,16
	sll	$2,$2,1
	subu	$2,$17,$2
	sh	$2,20($29)
	lw	$2,976($18)
	addiu	$16,$0,224
	sll	$2,$2,1
	subu	$2,$16,$2
	jal	SetDrawArea
	sh	$2,22($29)
	lhu	$2,980($18)
	nop
	addu	$2,$2,$17
	sh	$2,16($29)
	lhu	$2,976($18)
	nop
	sh	$2,18($29)
	lw	$2,980($18)
	addiu	$4,$18,124
	sll	$2,$2,1
	subu	$17,$17,$2
	sh	$17,20($29)
	lw	$2,976($18)
	addiu	$5,$29,16
	sll	$2,$2,1
	subu	$16,$16,$2
	jal	SetDrawArea
	sh	$16,22($29)
	lw	$2,60($18)
	nop
	sll	$2,$2,6
	slti	$2,$2,321
	bne	$2,$0,$LVrclear2_800DF6F4_3
	lui	$2,%hi(GV_Clock)
	lw	$3,%lo(GV_Clock)($2)
	nop
	sll	$3,$3,6
	addu	$2,$3,$18
	addiu	$4,$2,136
	lui	$2,%hi(DG_Chanls+492)
	addiu	$2,$2,%lo(DG_Chanls+492)
	addu	$3,$3,$2
	addiu	$2,$3,108
	addiu	$3,$3,172
$LVrclear2_800DF6F4_2:
	lw	$10,0($2)
	lw	$11,4($2)
	lw	$12,8($2)
	lw	$13,12($2)
	sw	$10,0($4)
	sw	$11,4($4)
	sw	$12,8($4)
	sw	$13,12($4)
	addiu	$2,$2,16
	bne	$2,$3,$LVrclear2_800DF6F4_2
	addiu	$4,$4,16
	lui	$9,0xff
	ori	$9,$9,0xffff
	lui	$3,%hi(DG_Chanls+492)
	lui	$2,%hi(GV_Clock)
	addiu	$3,$3,%lo(DG_Chanls+492)
	lw	$5,%lo(GV_Clock)($2)
	lui	$8,0xff00
	sll	$6,$5,2
	addu	$6,$6,$3
	sll	$4,$5,1
	addu	$4,$4,$5
	sll	$4,$4,2
	addu	$7,$4,$18
	addiu	$4,$4,112
	addu	$4,$18,$4
	lw	$2,0($6)
	lw	$3,112($7)
	lw	$2,784($2)
	and	$3,$3,$8
	and	$2,$2,$9
	or	$3,$3,$2
	sw	$3,112($7)
	lw	$3,0($6)
	and	$4,$4,$9
	lw	$2,784($3)
	sll	$5,$5,6
	and	$2,$2,$8
	or	$2,$2,$4
	addu	$4,$5,$18
	addiu	$5,$5,136
	sw	$2,784($3)
	lw	$2,0($6)
	lw	$3,136($4)
	lw	$2,0($2)
	and	$3,$3,$8
	and	$2,$2,$9
	or	$3,$3,$2
	sw	$3,136($4)
	lw	$3,0($6)
	addu	$5,$18,$5
	lw	$2,0($3)
	and	$5,$5,$9
	and	$2,$2,$8
	or	$2,$2,$5
	sw	$2,0($3)
$LVrclear2_800DF6F4_3:
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DF908
Vrclear2_800DF908:
	addiu	$29,$29,-48
	sw	$18,24($29)
	addu	$18,$4,$0
	sw	$31,40($29)
	sw	$21,36($29)
	sw	$20,32($29)
	sw	$19,28($29)
	sw	$17,20($29)
	jal	Vrclear2_800DF134
	sw	$16,16($29)
	lh	$3,38($18)
	nop
	sltiu	$2,$3,7
	beq	$2,$0,$LVrclear2_800DF908_19
	lui	$2,%hi(Vrclear2_800DF908_jtbl_800E183C)
	addiu	$2,$2,%lo(Vrclear2_800DF908_jtbl_800E183C)
	sll	$3,$3,2
	addu	$3,$3,$2
	lw	$2,0($3)
	nop
	jr	$2
	nop
$LVrclear2_800DF908_0:
	lui	$2,%hi(vrclear2_data)
	lbu	$17,954($18)
	lhu	$3,36($18)
	addiu	$16,$2,%lo(vrclear2_data)
	beq	$17,$0,$LVrclear2_800DF908_2
	sh	$3,34($18)
$LVrclear2_800DF908_1:
	jal	VrMenu_DrawItem
	addu	$4,$16,$0
	addiu	$17,$17,-1
	bne	$17,$0,$LVrclear2_800DF908_1
	addiu	$16,$16,120
$LVrclear2_800DF908_2:
	lw	$2,60($18)
	addu	$5,$18,$0
	addu	$4,$2,$0
	addiu	$2,$2,1
	jal	Vrclear2_800DED20
	sw	$2,60($18)
	jal	Vrclear2_800DF6F4
	addu	$4,$18,$0
	lui	$2,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($2)
	nop
	andi	$2,$2,0x10
	bne	$2,$0,$LVrclear2_800DF908_3
	nop
	jal	Vrclear2_800DF420
	addu	$4,$18,$0
	j	$LVrclear2_800DF908_16
	addiu	$4,$18,268
$LVrclear2_800DF908_3:
	jal	Vrclear2_800DF60C
	addu	$4,$18,$0
	beq	$2,$0,$LVrclear2_800DF908_19
	lui	$3,%hi(linkvarbuf)
	lbu	$2,952($18)
	addiu	$3,$3,%lo(linkvarbuf)
	addiu	$2,$2,16
	sll	$2,$2,1
	addu	$2,$2,$3
	lh	$2,0($2)
	lw	$4,60($18)
	sll	$2,$2,1
	addiu	$3,$2,30
	slt	$2,$3,$4
	beq	$2,$0,$LVrclear2_800DF908_4
	nop
	addu	$3,$4,$0
$LVrclear2_800DF908_4:
	j	$LVrclear2_800DF908_19
	sw	$3,60($18)
$LVrclear2_800DF908_5:
	lhu	$2,32($18)
	addu	$4,$18,$0
	addiu	$2,$2,1
	jal	Vrclear2_800DF644
	sh	$2,32($18)
	jal	Vrclear2_800DE808
	addu	$4,$2,$0
	beq	$2,$0,$LVrclear2_800DF908_19
	nop
	lw	$2,44($18)
	sh	$0,38($18)
	sh	$0,32($18)
	beq	$2,$0,$LVrclear2_800DF908_6
	sw	$0,60($18)
	lw	$2,1012($18)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$LVrclear2_800DF908_7
	lui	$2,%hi(GV_PadData+32)
	jal	GM_StreamPlayStart
	nop
$LVrclear2_800DF908_6:
	lui	$2,%hi(GV_PadData+32)
$LVrclear2_800DF908_7:
	lhu	$2,%lo(GV_PadData+32)($2)
	j	$LVrclear2_800DF908_19
	sw	$2,264($18)
$LVrclear2_800DF908_8:
	jal	Vrclear2_800DF6F4
	addu	$4,$18,$0
	lw	$2,60($18)
	nop
	addiu	$2,$2,1
	j	$LVrclear2_800DF908_19
	sw	$2,60($18)
$LVrclear2_800DF908_9:
	addu	$19,$0,$0
	lbu	$17,954($18)
	lui	$2,%hi(vrclear2_data)
	beq	$17,$0,$LVrclear2_800DF908_13
	addiu	$16,$2,%lo(vrclear2_data)
	addu	$21,$16,$0
	addiu	$20,$0,5
$LVrclear2_800DF908_10:
	jal	VrMenu_DrawItem
	addu	$4,$16,$0
	lh	$3,34($18)
	nop
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,3
	addu	$2,$2,$21
	beq	$16,$2,$LVrclear2_800DF908_12
	nop
	lbu	$3,34($16)
	nop
	beq	$3,$20,$LVrclear2_800DF908_11
	addu	$2,$0,$0
	sltu	$2,$2,$3
$LVrclear2_800DF908_11:
	or	$19,$19,$2
$LVrclear2_800DF908_12:
	addiu	$17,$17,-1
	bne	$17,$0,$LVrclear2_800DF908_10
	addiu	$16,$16,120
$LVrclear2_800DF908_13:
	lw	$2,60($18)
	addu	$5,$18,$0
	addu	$4,$2,$0
	addiu	$2,$2,1
	jal	Vrclear2_800DED20
	sw	$2,60($18)
	jal	Vrclear2_800DF6F4
	addu	$4,$18,$0
	bne	$19,$0,$LVrclear2_800DF908_15
	addiu	$2,$0,3
	lh	$3,38($18)
	nop
	bne	$3,$2,$LVrclear2_800DF908_15
	addiu	$2,$0,2
	lh	$3,34($18)
	nop
	bne	$3,$2,$LVrclear2_800DF908_14
	lui	$16,%hi(vrclear2_data)
	lw	$2,1012($18)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2_800DF908_14
	nop
	lw	$4,964($18)
	jal	GCL_SetVar
	addiu	$5,$0,-1
	lui	$16,%hi(vrclear2_data)
$LVrclear2_800DF908_14:
	lh	$2,34($18)
	addiu	$16,$16,%lo(vrclear2_data)
	sll	$4,$2,4
	subu	$4,$4,$2
	sll	$4,$4,3
	jal	VrMenu_ExecItem
	addu	$4,$4,$16
	lh	$2,34($18)
	addiu	$17,$0,5
	sh	$17,38($18)
	sll	$4,$2,4
	subu	$4,$4,$2
	sll	$4,$4,3
	jal	VrMenu_ExecItem
	addu	$4,$4,$16
	sh	$17,38($18)
$LVrclear2_800DF908_15:
	addiu	$4,$18,268
$LVrclear2_800DF908_16:
	lui	$5,%hi(vrclear2_data+24)
	lh	$2,36($18)
	addiu	$5,$5,%lo(vrclear2_data+24)
	sll	$3,$2,4
	subu	$3,$3,$2
	sll	$3,$3,3
	lui	$2,%hi(GV_Clock)
	lw	$7,%lo(GV_Clock)($2)
	addu	$5,$3,$5
	sll	$6,$7,2
	addu	$6,$6,$7
	sll	$6,$6,6
	addiu	$6,$6,276
	addu	$6,$18,$6
	sll	$7,$7,4
	addiu	$7,$7,916
	jal	VrMenu_UpdateFrame
	addu	$7,$18,$7
	j	$LVrclear2_800DF908_19
	nop
$LVrclear2_800DF908_17:
	jal	Vrclear2_800DF6F4
	addu	$4,$18,$0
	lbu	$17,954($18)
	lui	$2,%hi(vrclear2_data)
	beq	$17,$0,$LVrclear2_800DF908_19
	addiu	$16,$2,%lo(vrclear2_data)
$LVrclear2_800DF908_18:
	jal	VrMenu_DrawItem
	addu	$4,$16,$0
	addiu	$17,$17,-1
	bne	$17,$0,$LVrclear2_800DF908_18
	addiu	$16,$16,120
$LVrclear2_800DF908_19:
	lw	$31,40($29)
	lw	$21,36($29)
	lw	$20,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DFC58
Vrclear2_800DFC58:
	addiu	$29,$29,-56
	sw	$18,48($29)
	addu	$18,$4,$0
	lui	$2,%hi(linkvarbuf)
	addiu	$5,$2,%lo(linkvarbuf)
	sw	$31,52($29)
	sw	$17,44($29)
	sw	$16,40($29)
	lh	$3,34($5)
	lui	$2,%hi(vrclear2_weights)
	addiu	$11,$2,%lo(vrclear2_weights)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	lb	$10,8($11)
	swl	$8,19($29)
	swr	$8,16($29)
	swl	$9,23($29)
	swr	$9,20($29)
	sb	$10,24($29)
	lb	$8,9($11)
	nop
	sb	$8,25($29)
	bgez	$3,$LVrclear2_800DFC58_1
	addu	$4,$0,$0
	addiu	$3,$0,34
$LVrclear2_800DFC58_0:
	slti	$2,$4,11
	beq	$2,$0,$LVrclear2_800DFC58_2
	addiu	$2,$0,10
	addiu	$3,$3,2
	addu	$2,$3,$5
	lh	$2,0($2)
	nop
	bltz	$2,$LVrclear2_800DFC58_0
	addiu	$4,$4,1
$LVrclear2_800DFC58_1:
	addiu	$2,$0,10
$LVrclear2_800DFC58_2:
	bne	$4,$2,$LVrclear2_800DFC58_3
	addiu	$2,$4,1
	addiu	$2,$0,1
	sb	$2,952($18)
	lui	$2,%hi(linkvarbuf+34)
	sb	$0,953($18)
	j	$LVrclear2_800DFC58_4
	sh	$0,%lo(linkvarbuf+34)($2)
$LVrclear2_800DFC58_3:
	sb	$2,952($18)
	andi	$2,$4,0xff
	sltiu	$2,$2,10
	beq	$2,$0,$LVrclear2_800DFC58_4
	nop
	lbu	$2,952($18)
	nop
	addu	$2,$2,$29
	lbu	$2,15($2)
	nop
	sb	$2,953($18)
$LVrclear2_800DFC58_4:
	lw	$2,1008($18)
	nop
	bne	$2,$0,$LVrclear2_800DFC58_5
	lui	$2,%hi(VR_Flags)
	lw	$3,%lo(VR_Flags)($2)
	addiu	$4,$0,-17
	and	$3,$3,$4
	sw	$3,%lo(VR_Flags)($2)
$LVrclear2_800DFC58_5:
	lw	$3,1008($18)
	addiu	$2,$0,16
	bne	$3,$2,$LVrclear2_800DFC58_6
	lui	$2,%hi(VR_Flags)
	sw	$0,%lo(VR_Flags)($2)
$LVrclear2_800DFC58_6:
	lw	$4,988($18)
	nop
	beq	$4,$0,$LVrclear2_800DFC58_7
	lui	$2,%hi(VR_Flags)
	lw	$2,1012($18)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$LVrclear2_800DFC58_7
	lui	$2,%hi(VR_Flags)
	lw	$5,984($18)
	jal	Vrclear2_800DE6F8
	nop
	lui	$2,%hi(VR_Flags)
$LVrclear2_800DFC58_7:
	lw	$3,%lo(VR_Flags)($2)
	lw	$4,1012($18)
	andi	$2,$3,0x6
	srl	$5,$2,1
	addiu	$2,$0,-5
	and	$4,$4,$2
	sw	$4,1012($18)
	addiu	$2,$0,3
	lui	$3,%hi(vrclear2_data+128)
	sb	$2,954($18)
	addiu	$2,$0,-1
	sh	$2,%lo(vrclear2_data+128)($3)
	slti	$2,$5,3
	bne	$2,$0,$LVrclear2_800DFC58_8
	lui	$2,%hi(VR_Flags)
	addiu	$5,$0,-1
$LVrclear2_800DFC58_8:
	lw	$2,%lo(VR_Flags)($2)
	nop
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2_800DFC58_9
	addiu	$2,$0,-1
	beq	$5,$2,$LVrclear2_800DFC58_9
	sll	$2,$5,2
	addu	$2,$18,$2
	lw	$4,44($2)
	j	$LVrclear2_800DFC58_10
	nop
$LVrclear2_800DFC58_9:
	lw	$4,56($18)
$LVrclear2_800DFC58_10:
	jal	GM_VoxStream
	lui	$5,0x4000
	addiu	$4,$18,112
	addiu	$16,$29,32
	addu	$5,$16,$0
	sh	$0,32($29)
	sh	$0,34($29)
	sh	$0,36($29)
	jal	SetDrawArea
	sh	$0,38($29)
	addiu	$4,$18,124
	jal	SetDrawArea
	addu	$5,$16,$0
	lui	$2,%hi(vrclear2_data)
	addiu	$5,$2,%lo(vrclear2_data)
	lw	$3,140($5)
	lw	$2,260($5)
	nop
	bne	$3,$2,$LVrclear2_800DFC58_13
	addiu	$2,$0,1
	lui	$2,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($2)
	addiu	$3,$0,2
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2_800DFC58_11
	sh	$3,36($18)
	lw	$2,1012($18)
	nop
	srl	$2,$2,2
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2_800DFC58_11
	addiu	$3,$0,3
	lhu	$2,122($5)
	lhu	$4,146($5)
	sh	$3,8($5)
	sh	$0,372($5)
	sh	$2,362($5)
	j	$LVrclear2_800DFC58_12
	sh	$4,386($5)
$LVrclear2_800DFC58_11:
	lui	$2,%hi(vrclear2_data)
	addiu	$2,$2,%lo(vrclear2_data)
	addiu	$3,$0,-1
	sh	$3,8($2)
	addiu	$3,$0,1
	sh	$3,372($2)
$LVrclear2_800DFC58_12:
	lui	$2,%hi(vrclear2_data)
	addiu	$2,$2,%lo(vrclear2_data)
	sh	$0,124($2)
	sh	$0,126($2)
	j	$LVrclear2_800DFC58_14
	sh	$0,120($2)
$LVrclear2_800DFC58_13:
	sh	$2,36($18)
$LVrclear2_800DFC58_14:
	lui	$3,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($3)
	nop
	andi	$2,$2,0x20
	beq	$2,$0,$LVrclear2_800DFC58_15
	nop
	sh	$0,36($18)
$LVrclear2_800DFC58_15:
	lw	$2,%lo(VR_Flags)($3)
	nop
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2_800DFC58_16
	nop
	lw	$2,1012($18)
	nop
	srl	$2,$2,2
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2_800DFC58_16
	addiu	$2,$0,3
	sh	$2,36($18)
$LVrclear2_800DFC58_16:
	lw	$2,1012($18)
	nop
	andi	$3,$2,0x1
	addiu	$2,$0,1
	bne	$3,$2,$LVrclear2_800DFC58_17
	addiu	$4,$0,4
	lui	$4,%hi(vrclear2_str_replay)
	addiu	$4,$4,%lo(vrclear2_str_replay)
	addiu	$2,$0,2
	lui	$17,%hi(vrclear2_data)
	addiu	$16,$17,%lo(vrclear2_data)
	sh	$2,36($18)
	addiu	$2,$0,-1
	sh	$2,8($16)
	addiu	$2,$0,3
	sh	$3,372($16)
	sh	$0,124($16)
	sh	$0,126($16)
	sh	$0,120($16)
	jal	GV_StrCode
	sb	$2,954($18)
	addu	$4,$2,$0
	jal	DG_GetTexture
	sw	$4,16($16)
	addiu	$3,$16,40
	sw	$2,36($16)
	lbu	$6,8($2)
	lbu	$5,10($2)
	lbu	$4,9($2)
	lbu	$7,11($2)
	addu	$5,$6,$5
	sb	$4,13($3)
	sb	$4,21($3)
	addu	$4,$4,$7
	sb	$6,12($3)
	sb	$5,20($3)
	sb	$6,28($3)
	sb	$4,29($3)
	sb	$5,36($3)
	sb	$4,37($3)
	lhu	$4,4($2)
	nop
	sh	$4,22($3)
	lhu	$4,6($2)
	nop
	sh	$4,14($3)
	addiu	$3,$16,80
	lbu	$6,8($2)
	lbu	$5,10($2)
	lbu	$4,9($2)
	lbu	$7,11($2)
	addu	$5,$6,$5
	sb	$4,13($3)
	sb	$4,21($3)
	addu	$4,$4,$7
	sb	$6,12($3)
	sb	$5,20($3)
	sb	$6,28($3)
	sb	$4,29($3)
	sb	$5,36($3)
	sb	$4,37($3)
	lhu	$4,4($2)
	nop
	sh	$4,22($3)
	lhu	$2,6($2)
	nop
	sh	$2,14($3)
	addiu	$2,$0,56
	sh	$2,4($16)
	addiu	$2,$0,8
	sh	$2,6($16)
	addiu	$2,$0,132
	sh	$2,%lo(vrclear2_data)($17)
	addiu	$2,$0,76
	sh	$2,28($16)
	addiu	$2,$0,14
	sh	$2,30($16)
	addiu	$2,$0,121
	sh	$2,24($16)
	addiu	$4,$0,4
$LVrclear2_800DFC58_17:
	lui	$2,%hi(VR_Flags)
	lw	$3,%lo(VR_Flags)($2)
	addiu	$2,$0,2
	sh	$2,38($18)
	addiu	$2,$0,32
	sh	$4,34($18)
	sh	$0,32($18)
	sw	$0,976($18)
	andi	$3,$3,0x28
	bne	$3,$2,$LVrclear2_800DFC58_18
	sw	$0,980($18)
	sh	$4,38($18)
$LVrclear2_800DFC58_18:
	jal	VrMenu_LoadFrameTexture
	nop
	addiu	$4,$18,276
	addiu	$5,$18,916
	jal	VrMenu_InitFrame
	addu	$6,$2,$0
	addiu	$2,$0,160
	sh	$2,268($18)
	addiu	$2,$0,112
	sh	$2,270($18)
	sh	$0,272($18)
	sh	$0,274($18)
	lw	$31,52($29)
	lw	$18,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800E00E4
Vrclear2_800E00E4:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$3,1004($16)
	addiu	$2,$0,1
	beq	$3,$2,$LVrclear2_800E00E4_4
	slti	$2,$3,2
	beq	$2,$0,$LVrclear2_800E00E4_0
	nop
	beq	$3,$0,$LVrclear2_800E00E4_1
	lui	$2,%hi(VR_Flags)
	j	$LVrclear2_800E00E4_6
	nop
$LVrclear2_800E00E4_0:
	addiu	$2,$0,2
	beq	$3,$2,$LVrclear2_800E00E4_5
	nop
	j	$LVrclear2_800E00E4_6
	nop
$LVrclear2_800E00E4_1:
	lw	$2,%lo(VR_Flags)($2)
	nop
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2_800E00E4_2
	addiu	$3,$0,-2
	lw	$2,1012($16)
	j	$LVrclear2_800E00E4_3
	and	$2,$2,$3
$LVrclear2_800E00E4_2:
	lw	$2,1012($16)
	nop
	ori	$2,$2,0x1
$LVrclear2_800E00E4_3:
	sw	$2,1012($16)
	jal	Vrclear2_800DF644
	addu	$4,$16,$0
	jal	Vrclear2_800DE9B0
	addu	$4,$16,$0
	j	$LVrclear2_800E00E4_6
	nop
$LVrclear2_800E00E4_4:
	jal	Vrclear2_800DFC58
	addu	$4,$16,$0
	lw	$2,1004($16)
	nop
	addiu	$2,$2,1
	j	$LVrclear2_800E00E4_6
	sw	$2,1004($16)
$LVrclear2_800E00E4_5:
	jal	Vrclear2_800DF908
	addu	$4,$16,$0
$LVrclear2_800E00E4_6:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800E01AC
Vrclear2_800E01AC:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800E01B4
Vrclear2_800E01B4:
	addiu	$29,$29,-64
	sw	$19,52($29)
	addu	$19,$4,$0
	addiu	$4,$0,99
	lui	$2,%hi(GM_CurrentMap)
	sw	$5,%lo(GM_CurrentMap)($2)
	addiu	$2,$0,320
	sw	$31,56($29)
	sw	$18,48($29)
	sw	$17,44($29)
	sw	$16,40($29)
	jal	GCL_GetOption
	sw	$2,972($19)
	beq	$2,$0,$LVrclear2_800E01B4_0
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LVrclear2_800E01B4_1
	sw	$2,1008($19)
$LVrclear2_800E01B4_0:
	addiu	$2,$0,1
	sw	$2,1008($19)
$LVrclear2_800E01B4_1:
	jal	GCL_GetOption
	addiu	$4,$0,112
	beq	$2,$0,$LVrclear2_800E01B4_5
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	addu	$16,$2,$0
	addiu	$2,$0,4
	bne	$16,$2,$LVrclear2_800E01B4_2
	addiu	$2,$0,1
	sh	$2,948($19)
	j	$LVrclear2_800E01B4_3
	addiu	$16,$0,3
$LVrclear2_800E01B4_2:
	sh	$0,948($19)
$LVrclear2_800E01B4_3:
	beq	$16,$0,$LVrclear2_800E01B4_5
	addiu	$17,$29,16
$LVrclear2_800E01B4_4:
	jal	GCL_NextStr
	addiu	$16,$16,-1
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sw	$2,0($17)
	bne	$16,$0,$LVrclear2_800E01B4_4
	addiu	$17,$17,4
$LVrclear2_800E01B4_5:
	jal	GCL_GetOption
	addiu	$4,$0,115
	beq	$2,$0,$LVrclear2_800E01B4_6
	sw	$2,964($19)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	jal	GCL_NextStr
	sw	$2,984($19)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LVrclear2_800E01B4_7
	sw	$2,988($19)
$LVrclear2_800E01B4_6:
	sw	$0,984($19)
	sw	$0,988($19)
$LVrclear2_800E01B4_7:
	jal	Vrclear2_800DEF84
	addu	$4,$19,$0
	addiu	$4,$0,122
	lui	$2,%hi(vrclear2_pad186c)
	addiu	$2,$2,%lo(vrclear2_pad186c)
	sw	$2,960($19)
	sw	$2,956($19)
	lw	$2,1012($19)
	addiu	$3,$0,-9
	and	$2,$2,$3
	jal	GCL_GetOption
	sw	$2,1012($19)
	beq	$2,$0,$LVrclear2_800E01B4_9
	addu	$16,$0,$0
	lw	$2,1012($19)
	addu	$17,$19,$0
	ori	$2,$2,0x8
	sw	$2,1012($19)
$LVrclear2_800E01B4_8:
	jal	GCL_NextStr
	nop
	jal	GCL_GetString
	addu	$4,$2,$0
	beq	$2,$0,$LVrclear2_800E01B4_9
	sw	$2,956($17)
	addiu	$16,$16,1
	slti	$2,$16,2
	bne	$2,$0,$LVrclear2_800E01B4_8
	addiu	$17,$17,4
$LVrclear2_800E01B4_9:
	jal	GCL_GetOption
	addiu	$4,$0,116
	beq	$2,$0,$LVrclear2_800E01B4_11
	addu	$16,$0,$0
	addu	$17,$19,$0
$LVrclear2_800E01B4_10:
	jal	GCL_NextStr
	addiu	$16,$16,1
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sw	$2,44($17)
	slti	$2,$16,4
	bne	$2,$0,$LVrclear2_800E01B4_10
	addiu	$17,$17,4
	j	$LVrclear2_800E01B4_13
	addu	$16,$0,$0
$LVrclear2_800E01B4_11:
	addiu	$16,$0,3
	addiu	$2,$19,12
$LVrclear2_800E01B4_12:
	sw	$0,44($2)
	addiu	$16,$16,-1
	bgez	$16,$LVrclear2_800E01B4_12
	addiu	$2,$2,-4
	addu	$16,$0,$0
$LVrclear2_800E01B4_13:
	lui	$2,%hi(vrclear2_data)
	addiu	$18,$2,%lo(vrclear2_data)
	addiu	$17,$29,16
$LVrclear2_800E01B4_14:
	addu	$4,$18,$0
	lw	$5,0($17)
	jal	VrMenu_InitItem
	addiu	$6,$0,1
	beq	$2,$0,$LVrclear2_800E01B4_15
	nop
	addiu	$17,$17,4
$LVrclear2_800E01B4_15:
	addiu	$16,$16,1
	slti	$2,$16,5
	bne	$2,$0,$LVrclear2_800E01B4_14
	addiu	$18,$18,120
	lui	$4,%hi(vrclear2_str_go_vrsave)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrclear2_str_go_vrsave)
	lui	$3,%hi(vrclear2_data+380)
	sw	$2,%lo(vrclear2_data+380)($3)
	lw	$3,1012($19)
	addiu	$4,$0,-497
	and	$3,$3,$4
	sw	$3,1012($19)
	lw	$31,56($29)
	lw	$19,52($29)
	lw	$18,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	addu	$2,$0,$0
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NewVrClear2
NewVrClear2:
	addiu	$29,$29,-32
	sw	$18,24($29)
	addu	$18,$4,$0
	sw	$17,20($29)
	addu	$17,$5,$0
	addiu	$4,$0,7
	addiu	$5,$0,1016
	sw	$31,28($29)
	jal	GV_NewActor
	sw	$16,16($29)
	addu	$16,$2,$0
	beq	$16,$0,$LNewVrClear2_1
	addu	$4,$16,$0
	lui	$5,%hi(Vrclear2_800E00E4)
	addiu	$5,$5,%lo(Vrclear2_800E00E4)
	lui	$6,%hi(Vrclear2_800E01AC)
	lui	$7,%hi(vrclear2_str_file)
	addiu	$6,$6,%lo(Vrclear2_800E01AC)
	jal	GV_SetNamedActor
	addiu	$7,$7,%lo(vrclear2_str_file)
	sw	$0,1004($16)
	addu	$4,$16,$0
	jal	Vrclear2_800E01B4
	addu	$5,$17,$0
	bgez	$2,$LNewVrClear2_0
	nop
	jal	GV_DestroyActor
	addu	$4,$16,$0
	j	$LNewVrClear2_2
	addu	$2,$0,$0
$LNewVrClear2_0:
	sw	$18,40($16)
$LNewVrClear2_1:
	addu	$2,$16,$0
$LNewVrClear2_2:
	lw	$31,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.rdata
	.align	2
vrclear2_rect:
	.word	0x00E000A0
	.word	0x0010000C
	.align	2
vrclear2_str_stage:
	.ascii	"stage = %d\n"
	.byte	0
	.align	2
vrclear2_str_area:
	.ascii	"area = %d\n"
	.byte	0
	.align	2
vrclear2_str_flags:
	.ascii	"clearflags[%d][%d] = %d\n"
	.byte	0
	.align	2
vrclear2_str_demo:
	.ascii	"DEMO"
	.byte	0
	.align	2
vrclear2_str_replay_up:
	.ascii	"REPLAY"
	.byte	0
	.align	2
vrclear2_str_1st:
	.ascii	"1st"
	.byte	0
	.align	2
vrclear2_str_2nd:
	.ascii	"2nd"
	.byte	0
	.align	2
vrclear2_str_3rd:
	.ascii	"3rd"
	.byte	0
	.align	2
vrclear2_str_record:
	.ascii	"record"
	.byte	0
	.align	2
vrclear2_ranks:
	.word	vrclear2_str_1st
	.word	vrclear2_str_2nd
	.word	vrclear2_str_3rd
	.word	vrclear2_str_record
	.align	2
vrclear2_str_d:
	.ascii	"%d"
	.byte	0
	.align	2
vrclear2_str_s:
	.ascii	"%s"
	.byte	0
	.align	2
vrclear2_str_variety:
	.ascii	"VARIETY"
	.byte	0
	.align	2
vrclear2_str_vr_mission:
	.ascii	"VR MISSION"
	.byte	0
	.align	2
vrclear2_str_vs12:
	.ascii	"VS. 12 BATTLE"
	.byte	0
	.align	2
vrclear2_str_mystery:
	.ascii	"MYSTERY"
	.byte	0
	.align	2
vrclear2_str_puzzle:
	.ascii	"PUZZLE"
	.byte	0
	.align	2
vrclear2_str_ninja:
	.ascii	"NINJA"
	.byte	0
	.align	2
vrclear2_str_min_target:
	.ascii	"1 MIN. BATTLE - VS. TARGET"
	.byte	0
	.align	2
vrclear2_str_min_enemy:
	.ascii	"1 MIN. BATTLE - VS. ENEMY"
	.byte	0
	.align	2
vrclear2_str_advanced:
	.ascii	"ADVANCED MODE"
	.byte	0
	.align	2
vrclear2_str_sneaking:
	.ascii	"SNEAKING MODE"
	.byte	0
	.align	2
vrclear2_str_weapon:
	.ascii	"WEAPON MODE"
	.byte	0
	.align	2
vrclear2_pad17b4:
	.word	0x00000000
	.align	2
vrclear2_str_stinger:
	.ascii	"STINGER"
	.byte	0
	.align	2
vrclear2_str_psg1:
	.ascii	"PSG1"
	.byte	0
	.align	2
vrclear2_str_nikita:
	.ascii	"NIKITA"
	.byte	0
	.align	2
vrclear2_str_claymore:
	.ascii	"CLAYMORE"
	.byte	0
	.align	2
vrclear2_str_grenade:
	.ascii	"GRENADE"
	.byte	0
	.align	2
vrclear2_str_famas:
	.ascii	"FAMAS"
	.byte	0
	.align	2
vrclear2_str_c4:
	.ascii	"C4"
	.byte	0
	.align	2
vrclear2_str_socom:
	.ascii	"SOCOM"
	.byte	0
	.align	2
vrclear2_str_noweapon:
	.ascii	"NO WEAPON"
	.byte	0
	.align	2
vrclear2_str_fmt_dash:
	.ascii	"%s - %s"
	.byte	0
	.align	2
vrclear2_str_fmt_ss:
	.ascii	"%s %s"
	.byte	0
	.align	2
vrclear2_str_level_cleared:
	.ascii	"LEVEL %s  CLEARED"
	.byte	0
	.align	2
vrclear2_str_cleared:
	.ascii	"%s  CLEARED"
	.byte	0
	.align	2
vrclear2_str_clear:
	.ascii	"clear"
	.byte	0
	.align	2
Vrclear2_800DF908_jtbl_800E183C:
	.word	$LVrclear2_800DF908_0
	.word	$LVrclear2_800DF908_19
	.word	$LVrclear2_800DF908_5
	.word	$LVrclear2_800DF908_9
	.word	$LVrclear2_800DF908_8
	.word	$LVrclear2_800DF908_9
	.word	$LVrclear2_800DF908_17
	.align	2
vrclear2_weights:
	.word	0x0A0A010A
	.word	0x0A0A1E0A
	.word	0x00000A0A
	.align	2
vrclear2_str_replay:
	.ascii	"replay"
	.byte	0
	.align	2
vrclear2_pad186c:
	.word	0x00000000
	.align	2
vrclear2_str_go_vrsave:
	.ascii	"GO_VRSAVE"
	.byte	0
	.align	2
vrclear2_str_file:
	.ascii	"vrclear2.c"
	.byte	0
	.data
	.align	2
vrclear2_data:
	.word	0x00A9007A
	.word	0x0008004C
	.word	0xFFFF0001
	.word	0xFFFF0002
	.word	0x00008D82
	.word	0x00000001
	.word	0x00A6006F
	.word	0x000E0060
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00990073
	.word	0x0008005C
	.word	0xFFFFFFFF
	.word	0xFFFF0000
	.word	0x00007F9C
	.word	0x00000001
	.word	0x00960067
	.word	0x000E0072
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00B80084
	.word	0x000E0038
	.word	0xFFFF0000
	.word	0xFFFFFFFF
	.word	0x00006DC8
	.word	0x00000001
	.word	0x00B80084
	.word	0x000E0039
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x008A006E
	.word	0x00080064
	.word	0xFFFFFFFF
	.word	0xFFFF0001
	.word	0x0000023C
	.word	0xFFFFFFFF
	.word	0x00870062
	.word	0x000E0078
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00AB00A0
	.word	0x00080000
	.word	0xFFFFFFFF
	.word	0xFFFFFFFF
	.word	0x00006DC8
	.word	0x00000000
	.word	0x00AB00A0
	.word	0x00080000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	vrclear2_pad17b4
	.word	vrclear2_str_weapon
	.word	vrclear2_str_weapon
	.word	vrclear2_str_sneaking
	.word	vrclear2_str_sneaking
	.word	vrclear2_str_advanced
	.word	vrclear2_str_advanced
	.word	vrclear2_str_min_enemy
	.word	vrclear2_str_min_target
	.word	vrclear2_str_ninja
	.word	vrclear2_pad17b4
	.word	vrclear2_str_puzzle
	.word	vrclear2_str_mystery
	.word	vrclear2_str_vs12
	.word	vrclear2_pad17b4
	.word	vrclear2_str_vr_mission
	.word	vrclear2_str_variety
	.word	vrclear2_pad17b4
	.word	vrclear2_str_noweapon
	.word	vrclear2_str_socom
	.word	vrclear2_str_c4
	.word	vrclear2_str_famas
	.word	vrclear2_str_grenade
	.word	vrclear2_str_claymore
	.word	vrclear2_str_nikita
	.word	vrclear2_str_psg1
	.word	vrclear2_str_stinger
	.text
