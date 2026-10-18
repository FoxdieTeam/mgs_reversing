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
	.globl	Vrclear2DrawResult
Vrclear2DrawResult:
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
	beq	$2,$0,$LVrclear2DrawResult_11
	addu	$19,$5,$0
	addiu	$4,$0,208
	addiu	$5,$0,107
	jal	MENU_Color
	addiu	$6,$0,57
	slti	$2,$21,9
	beq	$2,$0,$LVrclear2DrawResult_0
	addiu	$17,$0,8
	addu	$17,$21,$0
$LVrclear2DrawResult_0:
	lw	$2,%lo(VR_Flags)($16)
	nop
	andi	$2,$2,0x6
	srl	$20,$2,1
	slti	$2,$20,3
	bne	$2,$0,$LVrclear2DrawResult_1
	nop
	addiu	$20,$0,-1
$LVrclear2DrawResult_1:
	bltz	$20,$LVrclear2DrawResult_2
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
	bne	$4,$2,$LVrclear2DrawResult_2
	nop
	lw	$2,1012($19)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$LVrclear2DrawResult_2
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,192
$LVrclear2DrawResult_2:
	lw	$2,1012($19)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2DrawResult_3
	addu	$16,$0,$0
	addiu	$16,$0,3
$LVrclear2DrawResult_3:
	slti	$2,$16,4
	beq	$2,$0,$LVrclear2DrawResult_11
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
$LVrclear2DrawResult_4:
	bne	$16,$20,$LVrclear2DrawResult_5
	addiu	$2,$0,3
	beq	$21,$0,$LVrclear2DrawResult_10
	nop
$LVrclear2DrawResult_5:
	bne	$16,$2,$LVrclear2DrawResult_6
	sb	$0,0($22)
	addiu	$18,$18,12
$LVrclear2DrawResult_6:
	lui	$2,%hi(VR_Records)
	addiu	$2,$2,%lo(VR_Records)
	addu	$2,$17,$2
	lw	$2,0($2)
	nop
	blez	$2,$LVrclear2DrawResult_7
	addiu	$5,$0,107
	addiu	$4,$0,208
	j	$LVrclear2DrawResult_8
	addiu	$6,$0,57
$LVrclear2DrawResult_7:
	addiu	$4,$0,104
	addiu	$5,$0,53
	addiu	$6,$0,28
$LVrclear2DrawResult_8:
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
	bgez	$5,$LVrclear2DrawResult_9
	nop
	subu	$5,$0,$5
$LVrclear2DrawResult_9:
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
$LVrclear2DrawResult_10:
	addiu	$18,$18,12
	addiu	$19,$19,4
	addiu	$16,$16,1
	slti	$2,$16,4
	bne	$2,$0,$LVrclear2DrawResult_4
	addiu	$17,$17,4
$LVrclear2DrawResult_11:
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
	.rdata
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
	.globl	vrclear2_str_s
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
	.data
	.align	2
	.globl	vrclear2_buttons
vrclear2_buttons:
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
	.align	2
	.globl	vrclear2_mode_names
vrclear2_mode_names:
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
	.align	2
	.globl	vrclear2_weapon_names
vrclear2_weapon_names:
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
