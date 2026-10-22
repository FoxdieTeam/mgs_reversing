	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrClearDrawResult
VrClearDrawResult:
	addiu	$29,$29,-96
	sw	$19,68($29)
	addu	$19,$4,$0
	sw	$30,88($29)
	sw	$16,56($29)
	lui	$16,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($16)
	lui	$3,%hi(vrclear_ranks)
	sw	$31,92($29)
	sw	$23,84($29)
	sw	$22,80($29)
	sw	$21,76($29)
	sw	$20,72($29)
	sw	$18,64($29)
	sw	$17,60($29)
	addiu	$11,$3,%lo(vrclear_ranks)
	lw	$8,0($11)
	lw	$9,4($11)
	lw	$10,8($11)
	sw	$8,32($29)
	sw	$9,36($29)
	sw	$10,40($29)
	lw	$8,12($11)
	nop
	sw	$8,44($29)
	andi	$2,$2,0x8
	beq	$2,$0,$LVrClearDrawResult_22
	addu	$30,$5,$0
	addiu	$4,$0,208
	addiu	$5,$0,107
	jal	MENU_Color
	addiu	$6,$0,57
	lw	$3,%lo(VR_Flags)($16)
	nop
	andi	$2,$3,0x10
	beq	$2,$0,$LVrClearDrawResult_10
	addiu	$4,$19,-30
	lui	$3,%hi(linkvarbuf)
	addiu	$3,$3,%lo(linkvarbuf)
	lbu	$2,902($30)
	lbu	$16,903($30)
	addiu	$2,$2,16
	sll	$2,$2,1
	addu	$2,$2,$3
	lh	$17,0($2)
	bgez	$4,$LVrClearDrawResult_0
	addu	$19,$4,$0
	addu	$4,$0,$0
	addu	$19,$4,$0
$LVrClearDrawResult_0:
	srl	$2,$19,31
	addu	$2,$19,$2
	sra	$2,$2,1
	subu	$20,$17,$2
	bgez	$20,$LVrClearDrawResult_1
	lui	$2,%hi(vrclear_last_count)
	addu	$20,$0,$0
$LVrClearDrawResult_1:
	lw	$2,%lo(vrclear_last_count)($2)
	nop
	beq	$20,$2,$LVrClearDrawResult_2
	lui	$2,%hi(vrclear_last_count)
	beq	$19,$0,$LVrClearDrawResult_2
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,187
	lui	$2,%hi(vrclear_last_count)
$LVrClearDrawResult_2:
	bne	$19,$0,$LVrClearDrawResult_4
	sw	$20,%lo(vrclear_last_count)($2)
	lui	$2,%hi(VR_Records+12)
	lw	$5,%lo(VR_Records+12)($2)
	nop
	bgez	$5,$LVrClearDrawResult_3
	nop
	addu	$5,$0,$0
$LVrClearDrawResult_3:
	addiu	$4,$29,16
	j	$LVrClearDrawResult_6
	addiu	$6,$0,3
$LVrClearDrawResult_4:
	mult	$16,$20
	lui	$2,%hi(VR_Records+12)
	lw	$2,%lo(VR_Records+12)($2)
	mflo	$8
	addu	$5,$2,$8
	bgez	$5,$LVrClearDrawResult_5
	nop
	addu	$5,$0,$0
$LVrClearDrawResult_5:
	addiu	$4,$29,16
	addiu	$6,$0,1
$LVrClearDrawResult_6:
	jal	VrClearFormatTime
	addu	$7,$30,$0
	addiu	$4,$0,159
	addiu	$5,$0,108
	jal	MENU_Locate
	addiu	$6,$0,16
	lui	$16,%hi(vrclear_fmt_s)
	addiu	$16,$16,%lo(vrclear_fmt_s)
	addu	$4,$16,$0
	jal	MENU_Printf
	addiu	$5,$29,16
	addiu	$4,$0,99
	addiu	$5,$0,108
	jal	MENU_Locate
	addiu	$6,$0,16
	lw	$5,44($29)
	jal	MENU_Printf
	addu	$4,$16,$0
	addiu	$4,$0,219
	addiu	$5,$0,72
	jal	MENU_Locate
	addiu	$6,$0,17
	lui	$4,%hi(vrclear_fmt_d)
	addiu	$4,$4,%lo(vrclear_fmt_d)
	jal	MENU_Printf
	addu	$5,$20,$0
	addiu	$4,$0,99
	addiu	$5,$0,72
	jal	MENU_Locate
	addiu	$6,$0,16
	lui	$4,%hi(vrclear_str_bullet)
	jal	MENU_Printf
	addiu	$4,$4,%lo(vrclear_str_bullet)
	addiu	$2,$19,1
	srl	$3,$2,31
	addu	$2,$2,$3
	sra	$2,$2,1
	subu	$2,$17,$2
	slti	$2,$2,-15
	beq	$2,$0,$LVrClearDrawResult_7
	lui	$2,%hi(VR_Flags)
	lw	$3,%lo(VR_Flags)($2)
	addiu	$4,$0,-17
	and	$3,$3,$4
	sw	$3,%lo(VR_Flags)($2)
$LVrClearDrawResult_7:
	lw	$3,932($30)
	addiu	$2,$0,6
	bne	$3,$2,$LVrClearDrawResult_22
	addiu	$5,$0,84
	addiu	$4,$0,160
	jal	MENU_Locate
	addiu	$6,$0,18
	lui	$2,%hi(VR_FoundCount)
	lw	$3,%lo(VR_FoundCount)($2)
	nop
	beq	$3,$0,$LVrClearDrawResult_8
	addiu	$2,$0,1
	beq	$3,$2,$LVrClearDrawResult_9
	lui	$4,%hi(vrclear_str_bonus1)
	j	$LVrClearDrawResult_22
	nop
$LVrClearDrawResult_8:
	lui	$4,%hi(vrclear_str_bonus3)
	jal	MENU_Printf
	addiu	$4,$4,%lo(vrclear_str_bonus3)
	j	$LVrClearDrawResult_22
	nop
$LVrClearDrawResult_9:
	jal	MENU_Printf
	addiu	$4,$4,%lo(vrclear_str_bonus1)
	j	$LVrClearDrawResult_22
	nop
$LVrClearDrawResult_10:
	slti	$2,$19,9
	beq	$2,$0,$LVrClearDrawResult_11
	addiu	$20,$0,8
	addu	$20,$19,$0
$LVrClearDrawResult_11:
	andi	$2,$3,0x6
	srl	$22,$2,1
	slti	$2,$22,3
	bne	$2,$0,$LVrClearDrawResult_12
	nop
	addiu	$22,$0,-1
$LVrClearDrawResult_12:
	bltz	$22,$LVrClearDrawResult_13
	addiu	$18,$0,60
	lui	$2,0x8888
	ori	$2,$2,0x8889
	addiu	$4,$19,15
	mult	$4,$2
	sra	$2,$4,31
	mfhi	$8
	addu	$3,$8,$4
	sra	$3,$3,4
	subu	$3,$3,$2
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,1
	bne	$4,$2,$LVrClearDrawResult_13
	nop
	lw	$2,944($30)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$LVrClearDrawResult_13
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,192
$LVrClearDrawResult_13:
	lw	$2,944($30)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$LVrClearDrawResult_14
	addu	$17,$0,$0
	addiu	$17,$0,3
$LVrClearDrawResult_14:
	slti	$2,$17,4
	beq	$2,$0,$LVrClearDrawResult_22
	lui	$2,0x8888
	ori	$2,$2,0x8889
	mult	$19,$2
	addiu	$3,$29,16
	addu	$20,$3,$20
	sw	$20,48($29)
	lui	$2,%hi(vrclear_fmt_s)
	addiu	$23,$2,%lo(vrclear_fmt_s)
	sll	$2,$17,2
	addu	$21,$2,$3
	addu	$20,$2,$0
	sra	$3,$19,31
	mfhi	$8
	addu	$2,$8,$19
	sra	$2,$2,3
	subu	$2,$2,$3
	andi	$19,$2,0x1
$LVrClearDrawResult_15:
	bne	$17,$22,$LVrClearDrawResult_16
	addiu	$4,$29,16
	beq	$19,$0,$LVrClearDrawResult_21
	nop
$LVrClearDrawResult_16:
	addu	$6,$0,$0
	lui	$2,%hi(VR_Records)
	addiu	$2,$2,%lo(VR_Records)
	addu	$16,$20,$2
	lw	$5,0($16)
	nop
	bgez	$5,$LVrClearDrawResult_17
	nop
	subu	$5,$0,$5
$LVrClearDrawResult_17:
	jal	VrClearFormatTime
	addu	$7,$30,$0
	lw	$9,48($29)
	addiu	$2,$0,3
	bne	$17,$2,$LVrClearDrawResult_18
	sb	$0,0($9)
	addiu	$18,$18,12
$LVrClearDrawResult_18:
	lw	$2,0($16)
	nop
	blez	$2,$LVrClearDrawResult_19
	nop
	addiu	$4,$0,208
	addiu	$5,$0,107
	j	$LVrClearDrawResult_20
	addiu	$6,$0,57
$LVrClearDrawResult_19:
	addiu	$4,$0,104
	addiu	$5,$0,53
	addiu	$6,$0,28
$LVrClearDrawResult_20:
	jal	MENU_Color
	nop
	addiu	$4,$0,159
	addu	$5,$18,$0
	jal	MENU_Locate
	addiu	$6,$0,16
	addu	$4,$23,$0
	jal	MENU_Printf
	addiu	$5,$29,16
	addiu	$4,$0,208
	addiu	$5,$0,107
	jal	MENU_Color
	addiu	$6,$0,57
	addiu	$4,$0,99
	addu	$5,$18,$0
	jal	MENU_Locate
	addiu	$6,$0,16
	lw	$5,16($21)
	jal	MENU_Printf
	addu	$4,$23,$0
$LVrClearDrawResult_21:
	addiu	$18,$18,12
	addiu	$21,$21,4
	addiu	$17,$17,1
	slti	$2,$17,4
	bne	$2,$0,$LVrClearDrawResult_15
	addiu	$20,$20,4
$LVrClearDrawResult_22:
	lw	$31,92($29)
	lw	$30,88($29)
	lw	$23,84($29)
	lw	$22,80($29)
	lw	$21,76($29)
	lw	$20,72($29)
	lw	$19,68($29)
	lw	$18,64($29)
	lw	$17,60($29)
	lw	$16,56($29)
	jr	$31
	addiu	$29,$29,96
	.set	macro
	.set	reorder
	.rdata
	.align	2
	.align	2
vrclear_str_1st:
	.ascii	"1st"
	.byte	0
	.align	2
vrclear_str_2nd:
	.ascii	"2nd"
	.byte	0
	.align	2
vrclear_str_3rd:
	.ascii	"3rd"
	.byte	0
	.align	2
vrclear_str_record:
	.ascii	"record"
	.byte	0
	.align	2
vrclear_ranks:
	.word	vrclear_str_1st
	.word	vrclear_str_2nd
	.word	vrclear_str_3rd
	.word	vrclear_str_record
	.align	2
	.globl	vrclear_fmt_s
vrclear_fmt_s:
	.ascii	"%s"
	.byte	0
	.align	2
vrclear_fmt_d:
	.ascii	"%d"
	.byte	0
	.align	2
vrclear_str_bullet:
	.ascii	"bullet   X"
	.byte	0
	.align	2
vrclear_str_bonus3:
	.ascii	"SNEAKING BONUS  -3 SEC"
	.byte	0
	.align	2
vrclear_str_bonus1:
	.ascii	"SNEAKING BONUS  -1 SEC"
	.byte	0
	.text
