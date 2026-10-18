	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	s08b_p_sphere_800D8F50
s08b_p_sphere_800D8F50:
	addiu	$29,$29,-104
	sw	$23,92($29)
	addu	$23,$4,$0
	addiu	$7,$23,32
	sw	$22,88($29)
	addiu	$8,$23,640
	addiu	$9,$23,656
	lui	$2,%hi(GM_PlayerMap)
	lw	$3,%lo(GM_PlayerMap)($2)
	addiu	$10,$23,664
	sw	$31,100($29)
	sw	$30,96($29)
	sw	$21,84($29)
	sw	$20,80($29)
	sw	$19,76($29)
	sw	$18,72($29)
	sw	$17,68($29)
	sw	$16,64($29)
	sw	$7,24($29)
	sw	$8,28($29)
	sw	$9,32($29)
	sw	$10,36($29)
	lw	$4,704($23)
	lui	$2,%hi(GM_CurrentMap)
	sw	$3,%lo(GM_CurrentMap)($2)
	lw	$3,0($4)
	addiu	$5,$0,-1
	beq	$3,$5,$Ls08b_p_sphere_800D8F50_4
	addiu	$22,$23,624
	addiu	$2,$0,1
	beq	$3,$2,$Ls08b_p_sphere_800D8F50_0
	slti	$2,$3,2
	bne	$2,$0,$Ls08b_p_sphere_800D8F50_5
	addu	$21,$23,$0
	addiu	$2,$0,2
	beq	$3,$2,$Ls08b_p_sphere_800D8F50_1
	addiu	$2,$0,3
	beq	$3,$2,$Ls08b_p_sphere_800D8F50_3
	nop
	j	$Ls08b_p_sphere_800D8F50_5
	nop
$Ls08b_p_sphere_800D8F50_0:
	addiu	$3,$0,2048
	addiu	$2,$0,4096
	sw	$0,0($4)
	sw	$3,656($23)
	sw	$2,664($23)
	sw	$3,660($23)
	j	$Ls08b_p_sphere_800D8F50_4
	sw	$3,668($23)
$Ls08b_p_sphere_800D8F50_1:
	addiu	$2,$0,4096
	sw	$0,0($4)
	sw	$2,656($23)
	addiu	$2,$0,2048
	sw	$2,664($23)
	sw	$2,660($23)
	j	$Ls08b_p_sphere_800D8F50_4
	sw	$2,668($23)
$Ls08b_p_sphere_800D8F50_2:
	jal	GV_DestroyActor
	addu	$4,$23,$0
	j	$Ls08b_p_sphere_800D8F50_21
	nop
$Ls08b_p_sphere_800D8F50_3:
	sw	$5,0($4)
	sw	$0,664($23)
	sw	$0,668($23)
$Ls08b_p_sphere_800D8F50_4:
	addu	$21,$23,$0
$Ls08b_p_sphere_800D8F50_5:
	lw	$7,28($29)
	addu	$20,$21,$0
	sw	$0,40($29)
	addiu	$7,$7,4
	sw	$7,56($29)
$Ls08b_p_sphere_800D8F50_6:
	lw	$2,672($21)
	nop
	addiu	$2,$2,1
	sw	$2,672($21)
	lw	$2,680($21)
	lw	$3,616($21)
	addiu	$2,$2,1
	sw	$2,680($21)
	lhu	$2,20($3)
	nop
	sh	$2,0($22)
	lw	$2,616($21)
	nop
	lhu	$2,24($2)
	nop
	sh	$2,2($22)
	lw	$2,616($21)
	nop
	lhu	$2,28($2)
	nop
	sh	$2,4($22)
	lw	$8,28($29)
	nop
	lhu	$2,0($8)
	nop
	addiu	$2,$2,32
	sh	$2,0($8)
	lw	$9,56($29)
	nop
	lhu	$2,-2($9)
	lhu	$3,0($9)
	addiu	$2,$2,123
	addiu	$3,$3,295
	sh	$2,-2($9)
	sh	$3,0($9)
	lw	$10,32($29)
	lw	$7,36($29)
	lw	$3,0($10)
	lw	$4,0($7)
	nop
	slt	$2,$4,$3
	beq	$2,$0,$Ls08b_p_sphere_800D8F50_8
	sll	$2,$3,5
	subu	$2,$2,$3
	bgez	$2,$Ls08b_p_sphere_800D8F50_7
	nop
	addiu	$2,$2,31
$Ls08b_p_sphere_800D8F50_7:
	lw	$8,32($29)
	sra	$2,$2,5
	j	$Ls08b_p_sphere_800D8F50_9
	sw	$2,0($8)
$Ls08b_p_sphere_800D8F50_8:
	lw	$9,32($29)
	nop
	sw	$4,0($9)
$Ls08b_p_sphere_800D8F50_9:
	lw	$2,704($23)
	lw	$10,32($29)
	lw	$3,0($2)
	addiu	$2,$0,-1
	lw	$19,0($10)
	bne	$3,$2,$Ls08b_p_sphere_800D8F50_10
	lui	$7,%hi(DG_Chanls+492)
	slti	$2,$19,500
	bne	$2,$0,$Ls08b_p_sphere_800D8F50_2
	nop
$Ls08b_p_sphere_800D8F50_10:
	addiu	$7,$7,%lo(DG_Chanls+492)
	lui	$8,%hi(DG_Chanls+492)
	addiu	$8,$8,%lo(DG_Chanls+492)
	lh	$7,52($7)
	lw	$10,40($29)
	lui	$9,%hi(DG_Chanls+492)
	sw	$7,44($29)
	lh	$8,58($8)
	addiu	$9,$9,%lo(DG_Chanls+492)
	sw	$8,48($29)
	lh	$9,64($9)
	bne	$10,$0,$Ls08b_p_sphere_800D8F50_14
	sw	$9,52($29)
	addu	$18,$0,$0
	sll	$2,$19,5
	subu	$2,$2,$19
	sll	$2,$2,2
	addu	$30,$2,$19
	addu	$16,$23,$0
$Ls08b_p_sphere_800D8F50_11:
	lui	$2,%hi(GV_Time)
	lw	$3,%lo(GV_Time)($2)
	nop
	addu	$3,$3,$18
	srl	$2,$3,31
	addu	$2,$3,$2
	sra	$2,$2,1
	sll	$2,$2,1
	subu	$3,$3,$2
	bne	$3,$18,$Ls08b_p_sphere_800D8F50_13
	nop
	jal	GV_RandU
	addiu	$4,$0,128
	addiu	$4,$0,128
	lhu	$3,708($16)
	addu	$2,$2,$4
	addu	$3,$3,$2
	jal	GV_RandU
	sh	$3,708($16)
	addiu	$4,$0,128
	lhu	$3,710($16)
	addu	$2,$2,$4
	addu	$3,$3,$2
	jal	GV_RandU
	sh	$3,710($16)
	sll	$6,$30,3
	addiu	$2,$2,128
	lhu	$3,712($16)
	sll	$17,$18,3
	addu	$3,$3,$2
	sh	$3,712($16)
	sh	$0,16($29)
	bgez	$6,$Ls08b_p_sphere_800D8F50_12
	sh	$0,18($29)
	addiu	$6,$6,4095
$Ls08b_p_sphere_800D8F50_12:
	addu	$4,$22,$0
	addiu	$5,$17,708
	addu	$5,$23,$5
	sra	$2,$6,12
	jal	DG_SetPos2
	sh	$2,20($29)
	addiu	$4,$29,16
	addu	$5,$4,$0
	jal	DG_PutVector
	addiu	$6,$0,1
	addiu	$4,$17,724
	addu	$4,$23,$4
	addiu	$5,$29,16
	jal	NewPlasmaL
	addiu	$6,$0,2
	lwl	$7,19($29)
	lwr	$7,16($29)
	lwl	$8,23($29)
	lwr	$8,20($29)
	swl	$7,727($16)
	swr	$7,724($16)
	swl	$8,731($16)
	swr	$8,728($16)
$Ls08b_p_sphere_800D8F50_13:
	addiu	$18,$18,1
	slti	$2,$18,2
	bne	$2,$0,$Ls08b_p_sphere_800D8F50_11
	addiu	$16,$16,8
$Ls08b_p_sphere_800D8F50_14:
	lw	$5,28($29)
	jal	DG_SetPos2
	addu	$4,$22,$0
	lw	$4,24($29)
	jal	GM_ActObject2
	nop
	addu	$4,$23,$0
	lw	$5,24($29)
	jal	s08b_p_sphere_800D8F20
	addu	$6,$19,$0
	slti	$2,$19,4097
	bne	$2,$0,$Ls08b_p_sphere_800D8F50_15
	nop
	addiu	$19,$0,4096
$Ls08b_p_sphere_800D8F50_15:
	bgez	$19,$Ls08b_p_sphere_800D8F50_16
	addu	$2,$19,$0
	addiu	$2,$19,7
$Ls08b_p_sphere_800D8F50_16:
	addu	$6,$19,$0
	bgez	$6,$Ls08b_p_sphere_800D8F50_17
	sra	$16,$2,3
	addiu	$6,$6,3
$Ls08b_p_sphere_800D8F50_17:
	lw	$4,672($21)
	sra	$17,$6,2
	jal	rsin
	sll	$4,$4,6
	bgez	$2,$Ls08b_p_sphere_800D8F50_18
	nop
	addiu	$2,$2,7
$Ls08b_p_sphere_800D8F50_18:
	lw	$7,44($29)
	sra	$2,$2,3
	addu	$2,$7,$2
	sh	$2,488($20)
	lw	$3,672($21)
	nop
	sll	$4,$3,3
	addu	$4,$4,$3
	sll	$2,$4,4
	addu	$4,$4,$2
	jal	rsin
	addu	$4,$4,$3
	bgez	$2,$Ls08b_p_sphere_800D8F50_19
	nop
	addiu	$2,$2,7
$Ls08b_p_sphere_800D8F50_19:
	lw	$8,48($29)
	sra	$2,$2,3
	addu	$2,$8,$2
	sh	$2,490($20)
	lw	$2,672($21)
	nop
	sll	$4,$2,2
	addu	$4,$4,$2
	sll	$4,$4,2
	addu	$4,$4,$2
	sll	$4,$4,3
	subu	$4,$4,$2
	jal	rsin
	sll	$4,$4,1
	bgez	$2,$Ls08b_p_sphere_800D8F50_20
	nop
	addiu	$2,$2,7
$Ls08b_p_sphere_800D8F50_20:
	sra	$2,$2,3
	lw	$9,40($29)
	lw	$10,24($29)
	lw	$7,52($29)
	addiu	$9,$9,1
	addiu	$10,$10,228
	addu	$2,$7,$2
	sw	$9,40($29)
	sw	$10,24($29)
	sh	$2,492($20)
	sh	$16,520($20)
	sh	$16,526($20)
	sh	$17,532($20)
	lw	$2,672($21)
	nop
	sll	$4,$2,2
	addu	$4,$4,$2
	sll	$4,$4,3
	addu	$4,$4,$2
	jal	rsin
	sll	$4,$4,2
	srl	$3,$2,31
	addu	$3,$3,$2
	lw	$8,44($29)
	sra	$3,$3,1
	addu	$3,$8,$3
	sh	$3,494($20)
	lw	$9,56($29)
	lw	$2,672($21)
	addiu	$9,$9,8
	sll	$4,$2,7
	subu	$4,$4,$2
	sll	$4,$4,1
	jal	rsin
	sw	$9,56($29)
	srl	$3,$2,31
	addu	$3,$3,$2
	lw	$10,48($29)
	sra	$3,$3,1
	addu	$3,$10,$3
	sh	$3,496($20)
	lw	$7,28($29)
	lw	$2,672($21)
	addiu	$7,$7,8
	sll	$4,$2,1
	addu	$4,$4,$2
	sll	$4,$4,7
	jal	rsin
	sw	$7,28($29)
	srl	$3,$2,31
	addu	$3,$3,$2
	lw	$8,52($29)
	sra	$3,$3,1
	sh	$16,522($20)
	sh	$16,528($20)
	sh	$17,534($20)
	addu	$3,$8,$3
	sh	$3,498($20)
	lw	$9,32($29)
	lw	$2,672($21)
	addiu	$9,$9,4
	sll	$4,$2,5
	addu	$4,$4,$2
	sll	$4,$4,3
	jal	rsin
	sw	$9,32($29)
	lw	$10,44($29)
	nop
	addu	$2,$10,$2
	sh	$2,500($20)
	lw	$7,36($29)
	lw	$2,672($21)
	addiu	$7,$7,4
	sll	$4,$2,1
	addu	$4,$4,$2
	sll	$4,$4,2
	subu	$4,$4,$2
	sll	$4,$4,4
	addu	$4,$4,$2
	sll	$4,$4,1
	jal	rsin
	sw	$7,36($29)
	lw	$8,48($29)
	nop
	addu	$2,$8,$2
	sh	$2,502($20)
	lw	$3,672($21)
	addiu	$22,$22,8
	sll	$2,$3,3
	subu	$2,$2,$3
	sll	$4,$2,5
	subu	$4,$4,$2
	jal	rsin
	sll	$4,$4,1
	lw	$9,52($29)
	addiu	$21,$21,4
	addu	$2,$9,$2
	sh	$2,504($20)
	sh	$16,524($20)
	sh	$16,530($20)
	sh	$17,536($20)
	lw	$10,40($29)
	nop
	slti	$2,$10,2
	bne	$2,$0,$Ls08b_p_sphere_800D8F50_6
	addiu	$20,$20,64
$Ls08b_p_sphere_800D8F50_21:
	lw	$31,100($29)
	lw	$30,96($29)
	lw	$23,92($29)
	lw	$22,88($29)
	lw	$21,84($29)
	lw	$20,80($29)
	lw	$19,76($29)
	lw	$18,72($29)
	lw	$17,68($29)
	lw	$16,64($29)
	jr	$31
	addiu	$29,$29,104
	.set	macro
	.set	reorder
	.set	at
