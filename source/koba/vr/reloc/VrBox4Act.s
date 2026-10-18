	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBox4Act
VrBox4Act:
	addiu	$29,$29,-120
	sw	$17,100($29)
	addu	$17,$4,$0
	lui	$2,%hi(VR_Status)
	lw	$3,%lo(VR_Status)($2)
	addiu	$2,$0,2
	sw	$31,112($29)
	sw	$19,108($29)
	sw	$18,104($29)
	bne	$3,$2,$LVrBox4Act_0
	sw	$16,96($29)
	jal	GV_DestroyActor
	nop
$LVrBox4Act_0:
	addiu	$5,$17,128
	addiu	$19,$17,36
	lhu	$4,48($19)
	lw	$3,32($17)
	lw	$18,1024($17)
	lui	$2,%hi(GM_CurrentMap)
	jal	GV_ReceiveMessage
	sw	$3,%lo(GM_CurrentMap)($2)
	sb	$2,86($19)
	sll	$2,$2,24
	beq	$2,$0,$LVrBox4Act_7
	nop
	lw	$2,92($19)
	nop
	lhu	$3,4($2)
	addiu	$2,$0,26847
	beq	$3,$2,$LVrBox4Act_6
	slti	$2,$3,26848
	beq	$2,$0,$LVrBox4Act_1
	addiu	$2,$0,12835
	beq	$3,$2,$LVrBox4Act_2
	addiu	$2,$0,17405
	beq	$3,$2,$LVrBox4Act_4
	nop
	j	$LVrBox4Act_7
	nop
$LVrBox4Act_1:
	ori	$2,$0,0x905f
	beq	$3,$2,$LVrBox4Act_5
	ori	$2,$0,0xc39b
	beq	$3,$2,$LVrBox4Act_3
	nop
	j	$LVrBox4Act_7
	nop
$LVrBox4Act_2:
	jal	GV_DestroyActor
	addu	$4,$17,$0
	j	$LVrBox4Act_7
	nop
$LVrBox4Act_3:
	lbu	$2,1079($17)
	sh	$0,1082($17)
	j	$LVrBox4Act_7
	sw	$2,1064($17)
$LVrBox4Act_4:
	lbu	$2,1079($17)
	j	$LVrBox4Act_7
	sw	$2,1064($17)
$LVrBox4Act_5:
	addiu	$5,$17,1172
	lui	$2,%hi(GM_PlayerBody)
	lw	$4,%lo(GM_PlayerBody)($2)
	addiu	$2,$0,1
	jal	s08b_p_sphere_800D9834
	sw	$2,1172($17)
	j	$LVrBox4Act_7
	nop
$LVrBox4Act_6:
	lw	$2,1068($17)
	lui	$3,0x2
	or	$2,$2,$3
	sw	$2,1068($17)
$LVrBox4Act_7:
	lw	$4,1068($17)
	nop
	srl	$2,$4,1
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox4Act_9
	srl	$2,$4,8
	lb	$2,86($19)
	nop
	beq	$2,$0,$LVrBox4Act_8
	addu	$3,$0,$0
	lw	$2,92($19)
	nop
	lhu	$2,4($2)
	nop
	xori	$2,$2,0x9a1f
	sltiu	$3,$2,1
$LVrBox4Act_8:
	addiu	$2,$0,-3
	and	$2,$4,$2
	sll	$3,$3,1
	or	$2,$2,$3
	sw	$2,1068($17)
	jal	GM_ActControl
	addu	$4,$19,$0
	jal	GM_ActObject2
	addiu	$4,$17,160
	addu	$4,$18,$0
	jal	GM_MoveTarget
	addu	$5,$19,$0
	jal	GM_PushTarget
	addu	$4,$18,$0
	jal	UpdateShadow
	addu	$4,$17,$0
	j	$LVrBox4Act_48
	nop
$LVrBox4Act_9:
	andi	$2,$2,0x7
	addiu	$3,$0,7
	bne	$2,$3,$LVrBox4Act_10
	nop
	lhu	$2,78($19)
	nop
	addiu	$2,$2,128
	sh	$2,78($19)
	lw	$2,1064($17)
	nop
	beq	$2,$0,$LVrBox4Act_11
	nop
	lhu	$2,76($19)
	nop
	addiu	$2,$2,8
	j	$LVrBox4Act_11
	sh	$2,76($19)
$LVrBox4Act_10:
	lhu	$2,78($19)
	nop
	addiu	$2,$2,64
	sh	$2,78($19)
$LVrBox4Act_11:
	lhu	$2,78($19)
	nop
	andi	$2,$2,0xfff
	sh	$2,78($19)
	lhu	$2,1076($17)
	nop
	bne	$2,$0,$LVrBox4Act_13
	addiu	$2,$2,-1
	lw	$5,1072($17)
	addu	$4,$17,$0
	jal	MoveToNode
	addiu	$5,$5,25
	beq	$2,$0,$LVrBox4Act_14
	nop
	jal	ReadNodeFlags
	addu	$4,$17,$0
	jal	NextNode
	addu	$4,$17,$0
	lhu	$2,1076($17)
	nop
	bne	$2,$0,$LVrBox4Act_12
	addiu	$2,$2,-1
	addiu	$4,$17,1008
	addiu	$5,$17,36
	addiu	$16,$29,80
	jal	GV_SubVec3
	addu	$6,$16,$0
	jal	GV_VecLen3
	addu	$4,$16,$0
	addu	$4,$16,$0
	addiu	$5,$17,104
	lw	$7,1072($17)
	jal	GV_LenVec3
	addu	$6,$2,$0
	j	$LVrBox4Act_14
	nop
$LVrBox4Act_12:
	sh	$2,1076($17)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,107($17)
	swr	$8,104($17)
	swl	$9,111($17)
	swr	$9,108($17)
	j	$LVrBox4Act_14
	nop
$LVrBox4Act_13:
	sh	$2,1076($17)
$LVrBox4Act_14:
	lh	$2,1082($17)
	nop
	beq	$2,$0,$LVrBox4Act_16
	nop
	lh	$4,1080($17)
	lhu	$3,1080($17)
	slti	$2,$4,2
	bne	$2,$0,$LVrBox4Act_15
	addiu	$2,$0,1
	addiu	$2,$3,-1
	j	$LVrBox4Act_16
	sh	$2,1080($17)
$LVrBox4Act_15:
	bne	$4,$2,$LVrBox4Act_16
	nop
	jal	Appear
	addu	$4,$17,$0
	sh	$0,1080($17)
$LVrBox4Act_16:
	lw	$2,1068($17)
	addiu	$3,$0,7
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBox4Act_24
	nop
	lw	$3,452($17)
	lw	$2,160($17)
	nop
	lw	$8,0($2)
	lw	$9,4($2)
	lw	$10,8($2)
	lw	$11,12($2)
	sw	$8,0($3)
	sw	$9,4($3)
	sw	$10,8($3)
	sw	$11,12($3)
	lw	$8,16($2)
	lw	$9,20($2)
	lw	$10,24($2)
	lw	$11,28($2)
	sw	$8,16($3)
	sw	$9,20($3)
	sw	$10,24($3)
	sw	$11,28($3)
	lw	$3,1068($17)
	nop
	srl	$2,$3,17
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox4Act_17
	lui	$5,0xfc03
	ori	$5,$5,0xffff
	and	$4,$3,$5
	srl	$2,$3,18
	addiu	$2,$2,2
	andi	$2,$2,0xff
	sll	$2,$2,18
	or	$4,$4,$2
	srl	$2,$4,18
	andi	$2,$2,0xff
	slti	$2,$2,129
	bne	$2,$0,$LVrBox4Act_17
	sw	$4,1068($17)
	and	$2,$4,$5
	lui	$3,0x200
	or	$2,$2,$3
	sw	$2,1068($17)
$LVrBox4Act_17:
	lw	$2,452($17)
	addu	$4,$17,$0
	lw	$5,52($2)
	lw	$2,1068($17)
	addiu	$3,$5,32
	srl	$2,$2,18
	andi	$2,$2,0xff
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
	sw	$2,28($5)
	sw	$2,24($5)
	jal	DrawLife
	sw	$2,20($5)
	lw	$2,1064($17)
	nop
	beq	$2,$0,$LVrBox4Act_24
	addiu	$2,$0,-1
	lwl	$8,39($17)
	lwr	$8,36($17)
	lwl	$9,43($17)
	lwr	$9,40($17)
	swl	$8,91($29)
	swr	$8,88($29)
	swl	$9,95($29)
	swr	$9,92($29)
	lw	$3,1172($17)
	nop
	beq	$3,$2,$LVrBox4Act_18
	addiu	$2,$0,3
	sw	$2,1172($17)
$LVrBox4Act_18:
	lw	$3,1064($17)
	nop
	subu	$3,$0,$3
	sll	$2,$3,2
	addu	$2,$2,$3
	lw	$3,1064($17)
	sh	$0,108($17)
	sh	$0,104($17)
	sh	$2,106($17)
	addiu	$2,$0,2
	bne	$3,$2,$LVrBox4Act_19
	nop
	lw	$4,1168($17)
	nop
	blez	$4,$LVrBox4Act_19
	nop
	jal	GCL_ExecProc
	addu	$5,$0,$0
	sw	$0,1168($17)
$LVrBox4Act_19:
	lh	$2,1102($17)
	lh	$3,38($17)
	addiu	$2,$2,2500
	slt	$3,$3,$2
	beq	$3,$0,$LVrBox4Act_20
	lui	$4,%hi(vib_boss_hit2)
	addiu	$4,$4,%lo(vib_boss_hit2)
	lbu	$2,1079($17)
	addiu	$5,$0,1
	sh	$0,106($17)
	jal	NewPadVibration
	sw	$2,1064($17)
	lui	$4,%hi(vib_boss_hit)
	addiu	$4,$4,%lo(vib_boss_hit)
	jal	NewPadVibration
	addu	$5,$0,$0
	addiu	$4,$29,88
	addiu	$5,$0,214
	jal	GM_SeSetMode
	addiu	$6,$0,1
$LVrBox4Act_20:
	lw	$3,1024($17)
	addiu	$2,$0,513
	sh	$2,0($3)
	lw	$2,1064($17)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox4Act_21
	addiu	$4,$29,88
	lhu	$2,90($29)
	nop
	addiu	$2,$2,5000
	jal	AN_Blast_Single
	sh	$2,90($29)
$LVrBox4Act_21:
	lw	$4,1068($17)
	nop
	srl	$2,$4,11
	andi	$2,$2,0xf
	bne	$2,$0,$LVrBox4Act_23
	addiu	$3,$0,-30721
	lui	$5,%hi(GM_PlayerPosition)
	addiu	$4,$0,4
	lhu	$3,36($17)
	lhu	$6,%lo(GM_PlayerPosition)($5)
	addiu	$5,$5,%lo(GM_PlayerPosition)
	subu	$3,$3,$6
	sh	$3,88($29)
	sll	$3,$3,16
	sra	$3,$3,18
	lhu	$2,40($17)
	lhu	$5,4($5)
	addu	$6,$6,$3
	sh	$6,88($29)
	subu	$2,$2,$5
	sh	$2,92($29)
	sll	$2,$2,16
	sra	$2,$2,18
	lhu	$3,38($17)
	addu	$5,$5,$2
	sh	$5,92($29)
	jal	GV_RandU
	sh	$3,90($29)
	addu	$4,$2,$0
	sll	$2,$4,16
	lw	$6,1068($17)
	sra	$2,$2,16
	srl	$3,$6,15
	andi	$3,$3,0x3
	bne	$3,$2,$LVrBox4Act_22
	addu	$5,$4,$0
	addiu	$5,$4,1
$LVrBox4Act_22:
	lui	$3,0xfffe
	ori	$3,$3,0x7fff
	and	$3,$6,$3
	andi	$2,$5,0x3
	sll	$2,$2,15
	or	$3,$3,$2
	addiu	$16,$29,88
	addu	$4,$16,$0
	lui	$2,%hi(blast_se_table)
	addiu	$2,$2,%lo(blast_se_table)
	sw	$3,1068($17)
	srl	$3,$3,15
	andi	$3,$3,0x3
	addu	$3,$3,$2
	lbu	$5,0($3)
	jal	GM_SeSetMode
	addiu	$6,$0,1
	jal	GV_RandS
	addiu	$4,$0,8192
	lhu	$3,36($17)
	addiu	$4,$0,2048
	addu	$3,$3,$2
	jal	GV_RandS
	sh	$3,88($29)
	lhu	$3,38($17)
	addiu	$4,$0,8192
	addu	$3,$3,$2
	jal	GV_RandS
	sh	$3,90($29)
	lhu	$3,40($17)
	addu	$4,$16,$0
	addu	$3,$3,$2
	jal	AN_Blast_Single
	sh	$3,92($29)
	lui	$4,%hi(vib_blast)
	addiu	$4,$4,%lo(vib_blast)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(vib_boss_down)
	addiu	$4,$4,%lo(vib_boss_down)
	jal	NewPadVibration
	addu	$5,$0,$0
	jal	GV_RandU
	addiu	$4,$0,8
	addiu	$4,$0,4
	jal	GV_RandU
	addu	$16,$2,$0
	addiu	$3,$0,-30721
	addu	$16,$16,$2
	addiu	$16,$16,4
	andi	$16,$16,0xf
	lw	$4,1068($17)
	sll	$16,$16,11
	and	$4,$4,$3
	or	$4,$4,$16
	j	$LVrBox4Act_24
	sw	$4,1068($17)
$LVrBox4Act_23:
	and	$3,$4,$3
	addiu	$2,$2,-1
	andi	$2,$2,0xf
	sll	$2,$2,11
	or	$3,$3,$2
	sw	$3,1068($17)
$LVrBox4Act_24:
	jal	GM_ActControl
	addu	$4,$19,$0
	lhu	$2,2($19)
	lhu	$3,70($19)
	addu	$4,$17,$0
	addu	$2,$2,$3
	jal	UpdateShadow
	sh	$2,2($19)
	addu	$4,$18,$0
	jal	GM_MoveTarget
	addu	$5,$19,$0
	jal	GM_PushTarget
	addu	$4,$18,$0
	jal	GM_ActObject2
	addiu	$4,$17,160
	lw	$2,160($17)
	nop
	lw	$8,0($2)
	lw	$9,4($2)
	lw	$10,8($2)
	lw	$11,12($2)
	sw	$8,1028($17)
	sw	$9,1032($17)
	sw	$10,1036($17)
	sw	$11,1040($17)
	lw	$8,16($2)
	lw	$9,20($2)
	lw	$10,24($2)
	lw	$11,28($2)
	sw	$8,1044($17)
	sw	$9,1048($17)
	sw	$10,1052($17)
	sw	$11,1056($17)
	lw	$2,1052($17)
	lh	$3,1080($17)
	addiu	$2,$2,200
	bne	$3,$0,$LVrBox4Act_30
	sw	$2,1052($17)
	lw	$2,1064($17)
	nop
	bne	$2,$0,$LVrBox4Act_30
	nop
	lw	$2,1068($17)
	nop
	srl	$2,$2,3
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox4Act_26
	nop
	lw	$3,1136($17)
	nop
	slti	$2,$3,8
	beq	$2,$0,$LVrBox4Act_25
	addiu	$2,$3,1
	sw	$2,1136($17)
	sll	$2,$2,9
	sw	$2,32($29)
	sw	$2,28($29)
	sw	$2,24($29)
	lw	$4,160($17)
	jal	ScaleMatrix
	addiu	$5,$29,24
$LVrBox4Act_25:
	lw	$3,1024($17)
	addiu	$2,$0,28
	sh	$2,0($3)
	lw	$2,1068($17)
	nop
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox4Act_28
	addiu	$2,$0,1
	lw	$3,1060($17)
	j	$LVrBox4Act_28
	sw	$2,12($3)
$LVrBox4Act_26:
	lw	$3,1136($17)
	nop
	blez	$3,$LVrBox4Act_28
	nop
	lw	$2,1132($17)
	nop
	bne	$2,$0,$LVrBox4Act_27
	addiu	$2,$3,-1
	sw	$2,1136($17)
	sll	$2,$2,9
	sw	$2,32($29)
	sw	$2,28($29)
	sw	$2,24($29)
	lw	$4,160($17)
	jal	ScaleMatrix
	addiu	$5,$29,24
$LVrBox4Act_27:
	lw	$2,1136($17)
	nop
	bne	$2,$0,$LVrBox4Act_29
	addiu	$2,$0,513
	lw	$3,1024($17)
	nop
	sh	$2,0($3)
	lw	$2,1068($17)
	nop
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox4Act_28
	nop
	lw	$2,1060($17)
	nop
	sw	$0,12($2)
$LVrBox4Act_28:
	lw	$2,1136($17)
	nop
	bne	$2,$0,$LVrBox4Act_29
	nop
	lw	$3,160($17)
	nop
	lw	$2,40($3)
	nop
	ori	$2,$2,0x80
	j	$LVrBox4Act_30
	sw	$2,40($3)
$LVrBox4Act_29:
	lw	$2,160($17)
	nop
	lw	$3,40($2)
	addiu	$4,$0,-129
	and	$3,$3,$4
	sw	$3,40($2)
$LVrBox4Act_30:
	lw	$2,1132($17)
	nop
	beq	$2,$0,$LVrBox4Act_31
	lui	$2,%hi(GV_Clock)
	lw	$4,%lo(GV_Clock)($2)
	lw	$3,160($17)
	sll	$2,$4,8
	lw	$3,52($3)
	subu	$2,$2,$4
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
	lw	$2,1132($17)
	nop
	addiu	$2,$2,1
	andi	$2,$2,0xf
	bne	$2,$0,$LVrBox4Act_31
	sw	$2,1132($17)
	lw	$2,160($17)
	nop
	lw	$3,52($2)
	addiu	$2,$0,127
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
$LVrBox4Act_31:
	lhu	$3,6($18)
	nop
	andi	$2,$3,0x4
	beq	$2,$0,$LVrBox4Act_39
	andi	$2,$3,0xfffb
	lhu	$4,62($18)
	sh	$2,6($18)
	addiu	$2,$4,-3
	sltiu	$2,$2,2
	beq	$2,$0,$LVrBox4Act_32
	addiu	$3,$0,6
	lw	$2,1068($17)
	nop
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBox4Act_36
	nop
	lhu	$2,38($18)
	nop
	addiu	$2,$2,-2
	sh	$2,38($18)
	sll	$2,$2,16
	bltz	$2,$LVrBox4Act_34
	addu	$4,$19,$0
	j	$LVrBox4Act_33
	addiu	$5,$0,52
$LVrBox4Act_32:
	sll	$2,$4,16
	sra	$2,$2,16
	addiu	$3,$0,2
	beq	$2,$3,$LVrBox4Act_35
	addiu	$2,$0,1
	lh	$2,38($18)
	nop
	bltz	$2,$LVrBox4Act_34
	addu	$4,$19,$0
	addiu	$5,$0,215
$LVrBox4Act_33:
	jal	GM_SeSetMode
	addiu	$6,$0,1
$LVrBox4Act_34:
	addiu	$2,$0,1
$LVrBox4Act_35:
	sw	$2,1132($17)
$LVrBox4Act_36:
	lw	$2,1064($17)
	nop
	bne	$2,$0,$LVrBox4Act_40
	nop
	lh	$2,38($18)
	nop
	bltz	$2,$LVrBox4Act_37
	addiu	$2,$0,2
	lh	$3,62($18)
	nop
	bne	$3,$2,$LVrBox4Act_39
	nop
	lw	$2,1068($17)
	nop
	srl	$2,$2,6
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox4Act_39
	nop
$LVrBox4Act_37:
	lh	$2,1080($17)
	nop
	bne	$2,$0,$LVrBox4Act_39
	nop
	lw	$2,1068($17)
	nop
	srl	$2,$2,4
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox4Act_38
	addiu	$2,$0,1
	lbu	$2,1079($17)
$LVrBox4Act_38:
	nop
	sw	$2,1064($17)
	addiu	$2,$0,255
	sh	$2,38($18)
	addiu	$2,$0,513
	sh	$2,0($18)
$LVrBox4Act_39:
	lw	$2,1064($17)
	nop
	beq	$2,$0,$LVrBox4Act_48
	nop
$LVrBox4Act_40:
	lbu	$2,1079($17)
	lw	$3,1064($17)
	nop
	beq	$3,$2,$LVrBox4Act_41
	addiu	$2,$3,1
	j	$LVrBox4Act_48
	sw	$2,1064($17)
$LVrBox4Act_41:
	lw	$2,1068($17)
	nop
	srl	$2,$2,4
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox4Act_42
	lui	$5,%hi(blast_data_8009F4B8)
	lw	$4,160($17)
	addiu	$5,$5,%lo(blast_data_8009F4B8)
	jal	NewBlast
	addiu	$18,$0,32
	j	$LVrBox4Act_43
	nop
$LVrBox4Act_42:
	addiu	$18,$0,64
$LVrBox4Act_43:
	lw	$2,1068($17)
	addiu	$3,$0,7
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBox4Act_44
	nop
	addiu	$18,$0,128
$LVrBox4Act_44:
	addu	$4,$19,$0
	addiu	$5,$29,72
	lui	$6,%hi(VR_TargetCount)
	lw	$2,%lo(VR_TargetCount)($6)
	lui	$3,%hi(DG_ZeroVector)
	addiu	$11,$3,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,75($29)
	swr	$8,72($29)
	swl	$9,79($29)
	swr	$9,76($29)
	addiu	$2,$2,1
	jal	DG_SetPos2
	sw	$2,%lo(VR_TargetCount)($6)
	addiu	$16,$29,40
	jal	ReadRotMatrix
	addu	$4,$16,$0
	addu	$4,$16,$0
	addiu	$5,$17,1016
	lhu	$2,1140($17)
	addu	$6,$18,$0
	sw	$2,16($29)
	lw	$2,1144($17)
	addu	$7,$0,$0
	jal	NewSplashVr
	sw	$2,20($29)
	lw	$2,1068($17)
	addiu	$3,$0,4
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBox4Act_45
	addu	$4,$19,$0
	addiu	$5,$0,201
	jal	GM_SeSetMode
	addiu	$6,$0,1
$LVrBox4Act_45:
	lh	$2,1082($17)
	nop
	bne	$2,$0,$LVrBox4Act_46
	nop
	jal	GV_DestroyActor
	addu	$4,$17,$0
	j	$LVrBox4Act_47
	nop
$LVrBox4Act_46:
	jal	Disappear
	addu	$4,$17,$0
$LVrBox4Act_47:
	lw	$4,1092($17)
	nop
	blez	$4,$LVrBox4Act_48
	nop
	jal	GCL_ExecProc
	addu	$5,$0,$0
$LVrBox4Act_48:
	lw	$31,112($29)
	lw	$19,108($29)
	lw	$18,104($29)
	lw	$17,100($29)
	lw	$16,96($29)
	jr	$31
	addiu	$29,$29,120
	.set	macro
	.set	reorder
	.set	at
