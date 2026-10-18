	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_CheckMessage0_80050878
njp_CheckMessage0_80050878:
	addiu	$29,$29,-48
	sw	$18,32($29)
	addu	$18,$4,$0
	lui	$5,0x8
	sw	$31,40($29)
	sw	$19,36($29)
	sw	$17,28($29)
	jal	njp_sna_check_flags1_8004E31C
	sw	$16,24($29)
	bne	$2,$0,$Lnjp_CheckMessage0_80050878_3
	nop
	lhu	$4,80($18)
	jal	GV_ReceiveMessage
	addiu	$5,$29,16
	beq	$2,$0,$Lnjp_CheckMessage0_80050878_3
	addu	$16,$2,$0
	lw	$3,1952($18)
	nop
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,2
	addiu	$2,$2,1956
	addu	$17,$18,$2
	sll	$2,$16,2
	addu	$2,$2,$16
	lw	$3,16($29)
	sll	$2,$2,2
	addu	$3,$3,$2
	addiu	$3,$3,-20
	blez	$16,$Lnjp_CheckMessage0_80050878_3
	sw	$3,16($29)
	addiu	$19,$0,8
$Lnjp_CheckMessage0_80050878_0:
	lw	$2,1952($18)
	nop
	beq	$2,$19,$Lnjp_CheckMessage0_80050878_3
	nop
	lw	$2,16($29)
	nop
	lhu	$3,4($2)
	ori	$2,$0,0x937a
	beq	$3,$2,$Lnjp_CheckMessage0_80050878_1
	addiu	$2,$0,28923
	beq	$3,$2,$Lnjp_CheckMessage0_80050878_1
	ori	$2,$0,0xbe0a
	bne	$3,$2,$Lnjp_CheckMessage0_80050878_2
	nop
$Lnjp_CheckMessage0_80050878_1:
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,4
	bne	$2,$0,$Lnjp_CheckMessage0_80050878_2
	nop
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,4
$Lnjp_CheckMessage0_80050878_2:
	lw	$2,16($29)
	addiu	$16,$16,-1
	lwl	$6,3($2)
	lwr	$6,0($2)
	lwl	$7,7($2)
	lwr	$7,4($2)
	lwl	$8,11($2)
	lwr	$8,8($2)
	lwl	$9,15($2)
	lwr	$9,12($2)
	swl	$6,3($17)
	swr	$6,0($17)
	swl	$7,7($17)
	swr	$7,4($17)
	swl	$8,11($17)
	swr	$8,8($17)
	swl	$9,15($17)
	swr	$9,12($17)
	lwl	$6,19($2)
	lwr	$6,16($2)
	nop
	swl	$6,19($17)
	swr	$6,16($17)
	addiu	$17,$17,20
	lw	$2,16($29)
	lw	$3,1952($18)
	addiu	$2,$2,-20
	addiu	$3,$3,1
	sw	$2,16($29)
	bgtz	$16,$Lnjp_CheckMessage0_80050878_0
	sw	$3,1952($18)
$Lnjp_CheckMessage0_80050878_3:
	lw	$31,40($29)
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
	.globl	njp_800C3D84
njp_800C3D84:
	addiu	$29,$29,-88
	sw	$18,56($29)
	addu	$18,$4,$0
	sw	$31,84($29)
	sw	$30,80($29)
	sw	$23,76($29)
	sw	$22,72($29)
	sw	$21,68($29)
	sw	$20,64($29)
	sw	$19,60($29)
	sw	$17,52($29)
	sw	$16,48($29)
	lw	$2,1952($18)
	nop
	beq	$2,$0,$Lnjp_800C3D84_24
	nop
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x2
	bne	$2,$0,$Lnjp_800C3D84_24
	addiu	$23,$18,1956
	sw	$0,40($29)
	lw	$22,1952($18)
	nop
	blez	$22,$Lnjp_800C3D84_23
	addu	$30,$23,$0
	addiu	$17,$18,1974
$Lnjp_800C3D84_0:
	lhu	$3,-14($17)
	addiu	$2,$0,25270
	beq	$3,$2,$Lnjp_800C3D84_20
	slti	$2,$3,25271
	beq	$2,$0,$Lnjp_800C3D84_2
	addiu	$2,$0,12835
	beq	$3,$2,$Lnjp_800C3D84_17
	slti	$2,$3,12836
	beq	$2,$0,$Lnjp_800C3D84_1
	addiu	$2,$0,9600
	beq	$3,$2,$Lnjp_800C3D84_18
	nop
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_1:
	addiu	$2,$0,24203
	beq	$3,$2,$Lnjp_800C3D84_15
	addu	$4,$18,$0
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_2:
	ori	$2,$0,0x9a1f
	beq	$3,$2,$Lnjp_800C3D84_16
	slt	$2,$2,$3
	bne	$2,$0,$Lnjp_800C3D84_3
	ori	$2,$0,0xaf6a
	ori	$2,$0,0x937a
	beq	$3,$2,$Lnjp_800C3D84_4
	addu	$20,$0,$0
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_3:
	beq	$3,$2,$Lnjp_800C3D84_19
	ori	$2,$0,0xbe0a
	beq	$3,$2,$Lnjp_800C3D84_4
	addiu	$20,$0,1
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_4:
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x800
	bne	$2,$0,$Lnjp_800C3D84_21
	addu	$21,$0,$0
	lhu	$19,0($17)
	lhu	$2,-12($17)
	addiu	$16,$18,2368
	sh	$0,0($17)
	sh	$2,2368($18)
	addiu	$2,$0,-1
	sh	$2,2($16)
	sh	$2,4($16)
	sh	$2,6($16)
	slti	$2,$19,3
	bne	$2,$0,$Lnjp_800C3D84_5
	sh	$0,8($16)
	lhu	$2,-10($17)
	nop
	sh	$2,2($16)
$Lnjp_800C3D84_5:
	slti	$2,$19,4
	bne	$2,$0,$Lnjp_800C3D84_6
	slti	$2,$19,5
	lhu	$2,-8($17)
	nop
	sh	$2,4($16)
	slti	$2,$19,5
$Lnjp_800C3D84_6:
	bne	$2,$0,$Lnjp_800C3D84_7
	slti	$2,$19,6
	lhu	$2,-6($17)
	nop
	sh	$2,6($16)
	slti	$2,$19,6
$Lnjp_800C3D84_7:
	bne	$2,$0,$Lnjp_800C3D84_8
	nop
	lhu	$3,-4($17)
	nop
	sll	$2,$3,16
	sra	$21,$2,16
	sh	$3,8($16)
$Lnjp_800C3D84_8:
	jal	njp_sna_act_unk_helper4_8004FA3C
	nop
	beq	$2,$0,$Lnjp_800C3D84_9
	nop
	bne	$20,$0,$Lnjp_800C3D84_9
	nop
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,4
	sh	$0,0($17)
	lui	$4,%hi(njp_str_47F4)
	jal	printf
	addiu	$4,$4,%lo(njp_str_47F4)
	j	$Lnjp_800C3D84_21
	nop
$Lnjp_800C3D84_9:
	beq	$20,$0,$Lnjp_800C3D84_10
	sh	$0,14($16)
	addiu	$2,$0,1
	sh	$2,14($16)
$Lnjp_800C3D84_10:
	andi	$2,$21,0x80
	bne	$2,$0,$Lnjp_800C3D84_11
	andi	$2,$21,0x4
	lhu	$2,2486($18)
	nop
	beq	$2,$0,$Lnjp_800C3D84_21
	addiu	$4,$18,156
	addiu	$5,$18,384
	addu	$6,$2,$0
	addiu	$2,$18,1076
	sw	$2,16($29)
	addiu	$2,$18,32
	sw	$2,20($29)
	addiu	$2,$18,1688
	addiu	$7,$18,464
	jal	GM_ConfigMotionControl
	sw	$2,24($29)
	andi	$2,$21,0x4
$Lnjp_800C3D84_11:
	beq	$2,$0,$Lnjp_800C3D84_12
	slti	$2,$19,7
	bne	$2,$0,$Lnjp_800C3D84_21
	nop
	lhu	$2,34($18)
	lhu	$3,-2($17)
	j	$Lnjp_800C3D84_13
	subu	$2,$2,$3
$Lnjp_800C3D84_12:
	lhu	$2,152($18)
$Lnjp_800C3D84_13:
	nop
	sh	$2,10($16)
	andi	$2,$21,0x10
	beq	$2,$0,$Lnjp_800C3D84_14
	addiu	$2,$0,1
	lbu	$2,117($18)
	nop
	ori	$2,$2,0x2
	sb	$2,117($18)
	addiu	$2,$0,1
$Lnjp_800C3D84_14:
	sh	$2,12($16)
	addu	$4,$18,$0
	lui	$5,%hi(njp_sna_anim_dying_80055524)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_dying_80055524)
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,4
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x800
	j	$Lnjp_800C3D84_21
	nop
$Lnjp_800C3D84_15:
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x4
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_16:
	addu	$4,$18,$0
	jal	njp_sna_clear_flags1_8004E308
	lui	$5,0x4
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_17:
	jal	GV_DestroyActor
	addu	$4,$18,$0
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_18:
	jal	njp_GM_ClearPlayerStatusFlag
	lui	$4,0x2000
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_19:
	jal	njp_GM_SetPlayerStatusFlag
	lui	$4,0x2000
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_20:
	lhu	$2,-12($17)
	nop
	sh	$2,32($18)
	lhu	$2,-10($17)
	nop
	sh	$2,34($18)
	lhu	$2,-8($17)
	nop
	sh	$2,36($18)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,103($18)
	swr	$8,100($18)
	swl	$9,107($18)
	swr	$9,104($18)
	lw	$2,76($18)
	addiu	$5,$18,32
	lw	$4,8($2)
	jal	njp_sub_8004E588
	addiu	$6,$29,32
	lhu	$2,32($29)
	nop
	sh	$2,152($18)
	lhu	$2,36($29)
	nop
	sh	$2,154($18)
	sh	$0,0($17)
$Lnjp_800C3D84_21:
	lhu	$2,0($17)
	nop
	beq	$2,$0,$Lnjp_800C3D84_22
	nop
	lwl	$8,3($23)
	lwr	$8,0($23)
	lwl	$9,7($23)
	lwr	$9,4($23)
	lwl	$10,11($23)
	lwr	$10,8($23)
	lwl	$11,15($23)
	lwr	$11,12($23)
	swl	$8,3($30)
	swr	$8,0($30)
	swl	$9,7($30)
	swr	$9,4($30)
	swl	$10,11($30)
	swr	$10,8($30)
	swl	$11,15($30)
	swr	$11,12($30)
	lwl	$8,19($23)
	lwr	$8,16($23)
	nop
	swl	$8,19($30)
	swr	$8,16($30)
	lw	$8,40($29)
	addiu	$30,$30,20
	addiu	$8,$8,1
	sw	$8,40($29)
$Lnjp_800C3D84_22:
	addiu	$22,$22,-1
	addiu	$17,$17,20
	bgtz	$22,$Lnjp_800C3D84_0
	addiu	$23,$23,20
$Lnjp_800C3D84_23:
	lw	$9,40($29)
	nop
	sw	$9,1952($18)
$Lnjp_800C3D84_24:
	lw	$31,84($29)
	lw	$30,80($29)
	lw	$23,76($29)
	lw	$22,72($29)
	lw	$21,68($29)
	lw	$20,64($29)
	lw	$19,60($29)
	lw	$18,56($29)
	lw	$17,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,88
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
njp_str_47F4:
	.ascii	"force act cancel\n"
	.byte	0
	.align	2
njp_str_4808:
	.ascii	"pos %d %d %d\n"
	.byte	0
	.align	2
njp_str_4818:
	.ascii	"turn %d %d %d\n"
	.byte	0
	.align	2
njp_str_4828:
	.ascii	"ceil floor %d %d\n"
	.byte	0
	.align	2
njp_str_483C:
	.ascii	"status %4x\n"
	.byte	0
	.align	2
njp_str_4848:
	.ascii	"item %d\n"
	.byte	0
	.align	2
njp_str_4854:
	.ascii	"flag %4x\n"
	.byte	0
	.align	2
njp_str_4860:
	.ascii	"stance %d\n"
	.byte	0
	.align	2
njp_str_486C:
	.ascii	"pad %x\n"
	.byte	0
	.align	2
njp_str_4874:
	.ascii	"padto %d\n"
	.byte	0
	.align	2
njp_str_4880:
	.ascii	"trap check %d\n"
	.byte	0
	.align	2
njp_str_4890:
	.ascii	"kaze \n"
	.byte	0
	.text
