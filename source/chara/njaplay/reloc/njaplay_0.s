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
	.text
