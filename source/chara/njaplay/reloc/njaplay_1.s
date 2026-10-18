	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C29E4
njp_800C29E4:
	addiu	$29,$29,-24
	sw	$16,16($29)
	lui	$2,%hi(GM_Camera)
	addiu	$5,$2,%lo(GM_Camera)
	sw	$31,20($29)
	lh	$3,34($5)
	addiu	$2,$0,1
	bne	$3,$2,$Lnjp_800C29E4_0
	addu	$16,$4,$0
	addiu	$2,$0,6
	sh	$2,2428($16)
$Lnjp_800C29E4_0:
	addiu	$4,$0,9
	sh	$0,34($5)
	jal	njp_GM_ClearPlayerStatusFlag
	sh	$0,2482($16)
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	ori	$5,$0,0x8000
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,2
	bne	$2,$0,$Lnjp_800C29E4_1
	lui	$4,0x1ff
	ori	$4,$4,0xff21
	jal	sd_set_cli
	addu	$5,$0,$0
$Lnjp_800C29E4_1:
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
	.globl	njp_800C2A58
njp_800C2A58:
	addiu	$29,$29,-24
	sw	$31,16($29)
	lh	$2,2428($4)
	lhu	$3,2428($4)
	beq	$2,$0,$Lnjp_800C2A58_1
	nop
	blez	$2,$Lnjp_800C2A58_0
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	bne	$2,$0,$Lnjp_800C2A58_1
	addiu	$2,$3,-1
	sh	$2,2428($4)
	sll	$2,$2,16
	bne	$2,$0,$Lnjp_800C2A58_1
	addiu	$5,$0,-129
	lw	$2,156($4)
	addiu	$4,$0,4
	lw	$3,40($2)
	nop
	and	$3,$3,$5
	jal	njp_GM_CheckPlayerStatusFlag
	sw	$3,40($2)
	bne	$2,$0,$Lnjp_800C2A58_1
	nop
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$0,0x8000
	j	$Lnjp_800C2A58_1
	nop
$Lnjp_800C2A58_0:
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C2A58_1
	addiu	$2,$3,1
	sh	$2,2428($4)
	sll	$2,$2,16
	bne	$2,$0,$Lnjp_800C2A58_1
	nop
	lw	$3,156($4)
	nop
	lw	$2,40($3)
	nop
	ori	$2,$2,0x80
	sw	$2,40($3)
$Lnjp_800C2A58_1:
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
	.globl	njp_800C2B14
njp_800C2B14:
	addiu	$29,$29,-104
	sw	$31,96($29)
	sw	$17,92($29)
	sw	$16,88($29)
	lw	$17,156($4)
	addiu	$4,$29,16
	jal	ReadRotMatrix
	addiu	$17,$17,624
	addiu	$4,$29,16
	addiu	$16,$29,48
	jal	DG_TransposeMatrix
	addu	$5,$16,$0
	addu	$4,$16,$0
	addu	$5,$17,$0
	jal	MulMatrix0
	addu	$6,$16,$0
	addu	$4,$16,$0
	jal	DG_MatrixRotZYX
	addiu	$5,$29,80
	jal	SetRotMatrix
	addiu	$4,$29,16
	lh	$3,80($29)
	nop
	bgez	$3,$Lnjp_800C2B14_0
	nop
	addiu	$3,$3,15
$Lnjp_800C2B14_0:
	andi	$3,$3,0xfff0
	lw	$31,96($29)
	lw	$17,92($29)
	lw	$16,88($29)
	lui	$2,%hi(GM_SnakeCamera+40)
	sh	$3,%lo(GM_SnakeCamera+40)($2)
	jr	$31
	addiu	$29,$29,104
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C2B9C
njp_800C2B9C:
	addiu	$2,$0,1
	bne	$5,$2,$Lnjp_800C2B9C_0
	addiu	$6,$4,412
	addiu	$6,$4,388
$Lnjp_800C2B9C_0:
	bne	$5,$2,$Lnjp_800C2B9C_1
	nop
	lh	$2,170($4)
	j	$Lnjp_800C2B9C_2
	nop
$Lnjp_800C2B9C_1:
	lh	$2,172($4)
$Lnjp_800C2B9C_2:
	lh	$3,0($6)
	lh	$4,2($6)
	nop
	addu	$3,$3,$4
	addiu	$4,$0,1
	beq	$3,$4,$Lnjp_800C2B9C_3
	nop
	addiu	$2,$0,-1
$Lnjp_800C2B9C_3:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C2BEC
njp_800C2BEC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,396($16)
	nop
	beq	$5,$2,$Lnjp_800C2BEC_0
	nor	$2,$0,$5
	sw	$2,420($16)
	ori	$2,$0,0xffff
	bne	$5,$2,$Lnjp_800C2BEC_0
	sw	$5,396($16)
	jal	njp_800C2B9C
	addiu	$5,$0,2
	bltz	$2,$Lnjp_800C2BEC_0
	addiu	$2,$0,4
	sw	$2,448($16)
	addiu	$2,$0,2
	sh	$2,432($16)
$Lnjp_800C2BEC_0:
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
	.globl	njp_800C2C48
njp_800C2C48:
	addiu	$29,$29,-56
	sw	$31,52($29)
	sw	$16,48($29)
	lw	$4,156($4)
	addu	$16,$5,$0
	jal	DG_SetPos
	addiu	$4,$4,624
	lui	$4,%hi(njp_data+64)
	jal	DG_MovePos
	addiu	$4,$4,%lo(njp_data+64)
	lui	$4,%hi(njp_data+72)
	jal	DG_RotatePos
	addiu	$4,$4,%lo(njp_data+72)
	jal	ReadRotMatrix
	addiu	$4,$29,16
	addiu	$2,$0,2
	beq	$16,$2,$Lnjp_800C2C48_3
	addiu	$5,$0,-1
	slti	$2,$16,3
	beq	$2,$0,$Lnjp_800C2C48_0
	addiu	$2,$0,1
	beq	$16,$2,$Lnjp_800C2C48_2
	nop
	j	$Lnjp_800C2C48_4
	nop
$Lnjp_800C2C48_0:
	addiu	$2,$0,3
	beq	$16,$2,$Lnjp_800C2C48_1
	addiu	$2,$0,4
	beq	$16,$2,$Lnjp_800C2C48_2
	nop
	j	$Lnjp_800C2C48_4
	nop
$Lnjp_800C2C48_1:
	j	$Lnjp_800C2C48_4
	addu	$5,$0,$0
$Lnjp_800C2C48_2:
	j	$Lnjp_800C2C48_4
	addiu	$5,$0,1
$Lnjp_800C2C48_3:
	addiu	$5,$0,2
$Lnjp_800C2C48_4:
	bltz	$5,$Lnjp_800C2C48_5
	nop
	jal	NewBlood
	addiu	$4,$29,16
$Lnjp_800C2C48_5:
	lw	$31,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C2CFC
njp_800C2CFC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$4,2308($16)
	nop
	beq	$4,$0,$Lnjp_800C2CFC_0
	nop
	jal	GV_DestroyActorQuick
	nop
$Lnjp_800C2CFC_0:
	addu	$4,$16,$0
	addiu	$5,$0,-1
	lui	$2,%hi(GM_ItemTypes)
	sw	$0,2308($4)
	sw	$5,2312($4)
	lhu	$3,%lo(GM_ItemTypes)($2)
	lui	$2,%hi(linkvarbuf+30)
	sh	$5,%lo(linkvarbuf+30)($2)
	jal	njp_800C29E4
	sw	$3,2316($4)
	lui	$4,0x40
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x1000
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
	.globl	njp_800C2D68
njp_800C2D68:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	addu	$17,$5,$0
	sw	$31,24($29)
	jal	njp_GM_SetPlayerStatusFlag
	lui	$4,0x80
	lw	$3,2200($16)
	sb	$17,2432($16)
	lhu	$2,0($3)
	nop
	andi	$2,$2,0xff69
	sh	$2,0($3)
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
	.globl	njp_800C2DB4
njp_800C2DB4:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	jal	njp_GM_ClearPlayerStatusFlag
	lui	$4,0x80
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,1
	lw	$3,2200($16)
	nop
	lhu	$2,0($3)
	nop
	ori	$2,$2,0x9e
	sh	$2,0($3)
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
	.globl	njp_800C2E00
njp_800C2E00:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,2
	beq	$2,$0,$Lnjp_800C2E00_0
	nop
	sh	$0,2482($16)
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$0,0x8009
	j	$Lnjp_800C2E00_1
	nop
$Lnjp_800C2E00_0:
	jal	njp_800C29E4
	addu	$4,$16,$0
$Lnjp_800C2E00_1:
	jal	njp_800C2DB4
	addu	$4,$16,$0
	addu	$4,$16,$0
	addiu	$5,$0,2
	jal	njp_sna_sub_8004E41C
	sb	$0,2432($16)
	addiu	$4,$16,156
	jal	GM_ConfigMotionAdjust
	addu	$5,$0,$0
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	jal	GM_ExitBehindCamera
	nop
	lui	$6,0x1400
	ori	$6,$6,0x3066
	addu	$4,$16,$0
	lui	$5,%hi(GM_PlayerStatus)
	lw	$2,%lo(GM_PlayerStatus)($5)
	addiu	$3,$0,450
	sh	$3,2436($16)
	and	$2,$2,$6
	sw	$2,%lo(GM_PlayerStatus)($5)
	lui	$5,0x1808
	lw	$2,2196($16)
	lbu	$3,117($16)
	and	$2,$2,$5
	andi	$3,$3,0xf7
	sw	$2,2196($16)
	jal	njp_800C48F4
	sb	$3,117($16)
	lui	$5,0xfdff
	ori	$5,$5,0xffff
	lui	$4,%hi(GM_GameStatus)
	lw	$2,%lo(GM_GameStatus)($4)
	addiu	$3,$0,3
	sw	$3,2528($16)
	lw	$31,20($29)
	lw	$16,16($29)
	and	$2,$2,$5
	sw	$2,%lo(GM_GameStatus)($4)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C2EF0
njp_800C2EF0:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	lui	$4,0x2
	sw	$31,20($29)
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x810
	addiu	$4,$16,156
	jal	GM_ConfigMotionAdjust
	addu	$5,$0,$0
	addu	$4,$0,$0
	lui	$5,%hi(DG_ZeroVector)
	addu	$3,$16,$0
$Lnjp_800C2EF0_0:
	addiu	$11,$5,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,1819($3)
	swr	$8,1816($3)
	swl	$9,1823($3)
	swr	$9,1820($3)
	addiu	$4,$4,1
	slti	$2,$4,16
	bne	$2,$0,$Lnjp_800C2EF0_0
	addiu	$3,$3,8
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	addu	$4,$16,$0
	jal	njp_sna_sub_8004E41C
	addiu	$5,$0,2
	addu	$4,$16,$0
	lui	$5,0x2200
	jal	njp_sna_clear_flags1_8004E308
	ori	$5,$5,0x1006
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x1
	bne	$2,$0,$Lnjp_800C2EF0_1
	addiu	$2,$0,450
	jal	GM_ExitBehindCamera
	sh	$2,2436($16)
$Lnjp_800C2EF0_1:
	lbu	$2,117($16)
	addu	$4,$16,$0
	andi	$2,$2,0xf7
	jal	njp_800C48F4
	sb	$2,117($16)
	lui	$5,0xfdff
	ori	$5,$5,0xffff
	lui	$4,%hi(GM_GameStatus)
	lw	$2,%lo(GM_GameStatus)($4)
	addiu	$3,$0,3
	sw	$3,2528($16)
	lw	$31,20($29)
	lw	$16,16($29)
	and	$2,$2,$5
	sw	$2,%lo(GM_GameStatus)($4)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C2FE4
njp_800C2FE4:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x40
	bne	$2,$0,$Lnjp_800C2FE4_5
	addu	$4,$16,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x100
	beq	$2,$0,$Lnjp_800C2FE4_0
	lui	$2,%hi(linkvarbuf+22)
	lw	$3,2200($16)
	lh	$4,%lo(linkvarbuf+22)($2)
	lh	$2,38($3)
	nop
	beq	$4,$2,$Lnjp_800C2FE4_5
	nop
$Lnjp_800C2FE4_0:
	lw	$3,2312($16)
	addiu	$2,$0,8
	bne	$3,$2,$Lnjp_800C2FE4_1
	lui	$2,%hi(linkvarbuf)
	lw	$4,2200($16)
	nop
	lh	$3,62($4)
	addiu	$2,$0,1
	bne	$3,$2,$Lnjp_800C2FE4_1
	lui	$2,%hi(linkvarbuf)
	lhu	$2,40($4)
	nop
	sll	$2,$2,16
	sra	$3,$2,16
	srl	$2,$2,31
	addu	$3,$3,$2
	sra	$3,$3,1
	sh	$3,40($4)
	lw	$3,2200($16)
	nop
	lhu	$2,38($3)
	lhu	$4,40($3)
	nop
	addu	$2,$2,$4
	sh	$2,38($3)
	lw	$2,2200($16)
	nop
	sh	$0,40($2)
	lui	$2,%hi(linkvarbuf)
$Lnjp_800C2FE4_1:
	addiu	$8,$2,%lo(linkvarbuf)
	lw	$7,2200($16)
	lh	$2,22($8)
	lh	$3,38($7)
	nop
	addu	$3,$3,$2
	lh	$2,2430($16)
	lh	$4,24($8)
	subu	$6,$3,$2
	slt	$2,$4,$6
	beq	$2,$0,$Lnjp_800C2FE4_2
	nop
	addu	$6,$4,$0
$Lnjp_800C2FE4_2:
	bgez	$6,$Lnjp_800C2FE4_3
	nop
	addu	$6,$0,$0
$Lnjp_800C2FE4_3:
	lw	$3,68($7)
	addiu	$2,$0,10
	bne	$3,$2,$Lnjp_800C2FE4_4
	addu	$4,$16,$0
	addu	$6,$0,$0
$Lnjp_800C2FE4_4:
	lui	$5,0x100
	sh	$6,38($7)
	sh	$6,2430($4)
	jal	njp_sna_set_flags1_8004E2F4
	sh	$6,22($8)
$Lnjp_800C2FE4_5:
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
	.globl	njp_800C3118
njp_800C3118:
	addiu	$29,$29,-56
	sw	$18,48($29)
	lui	$18,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($18)
	sw	$16,40($29)
	addu	$16,$4,$0
	sw	$17,44($29)
	addu	$17,$5,$0
	addiu	$2,$2,1
	sltiu	$2,$2,2
	beq	$2,$0,$Lnjp_800C3118_1
	sw	$31,52($29)
	lui	$4,%hi(njp_str_47E8)
	jal	GV_StrCode
	addiu	$4,$4,%lo(njp_str_47E8)
	sh	$2,16($29)
	addiu	$2,$0,6
	sh	$2,34($29)
	ori	$2,$0,0xbe0a
	sh	$2,20($29)
	ori	$2,$0,0xffff
	sh	$2,24($29)
	sh	$2,26($29)
	addiu	$2,$0,2
	sh	$2,28($29)
	addiu	$2,$0,2042
	sh	$17,22($29)
	sh	$2,30($29)
	lw	$3,1952($16)
	nop
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,2
	addu	$2,$16,$2
	lwl	$7,19($29)
	lwr	$7,16($29)
	lwl	$8,23($29)
	lwr	$8,20($29)
	lwl	$9,27($29)
	lwr	$9,24($29)
	lwl	$10,31($29)
	lwr	$10,28($29)
	swl	$7,1959($2)
	swr	$7,1956($2)
	swl	$8,1963($2)
	swr	$8,1960($2)
	swl	$9,1967($2)
	swr	$9,1964($2)
	swl	$10,1971($2)
	swr	$10,1968($2)
	lwl	$7,35($29)
	lwr	$7,32($29)
	nop
	swl	$7,1975($2)
	swr	$7,1972($2)
	lw	$2,1952($16)
	sw	$0,%lo(GM_GameOverTimer)($18)
	addiu	$2,$2,1
	jal	GM_GameOver
	sw	$2,1952($16)
	addu	$4,$16,$0
	lui	$5,0x8
	lui	$6,%hi(GM_GameStatus)
	lw	$2,%lo(GM_GameStatus)($6)
	lui	$3,0x1000
	or	$2,$2,$3
	jal	njp_sna_set_flags1_8004E2F4
	sw	$2,%lo(GM_GameStatus)($6)
	lw	$4,2508($16)
	nop
	bltz	$4,$Lnjp_800C3118_0
	nop
	jal	GCL_ForceExecProc
	addu	$5,$0,$0
$Lnjp_800C3118_0:
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,4096
	beq	$2,$0,$Lnjp_800C3118_1
	nop
	jal	njp_800C2CFC
	addu	$4,$16,$0
$Lnjp_800C3118_1:
	lw	$31,52($29)
	lw	$18,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3270
njp_800C3270:
	lui	$3,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($3)
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$2,$2,1
	sltiu	$2,$2,2
	beq	$2,$0,$Lnjp_800C3270_0
	sw	$31,20($29)
	jal	GM_GameOver
	sw	$0,%lo(GM_GameOverTimer)($3)
	addu	$4,$16,$0
	lui	$5,0x8
	lui	$2,%hi(GM_GameStatus)
	lw	$3,%lo(GM_GameStatus)($2)
	lui	$6,0x1000
	or	$3,$3,$6
	jal	njp_sna_set_flags1_8004E2F4
	sw	$3,%lo(GM_GameStatus)($2)
	lw	$4,2508($16)
	nop
	bltz	$4,$Lnjp_800C3270_0
	nop
	jal	GCL_ForceExecProc
	addu	$5,$0,$0
$Lnjp_800C3270_0:
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
	.globl	njp_800C32E4
njp_800C32E4:
	lui	$2,%hi(linkvarbuf+22)
	lh	$2,%lo(linkvarbuf+22)($2)
	nop
	beq	$2,$0,$Lnjp_800C32E4_0
	lui	$2,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($2)
	nop
	beq	$2,$0,$Lnjp_800C32E4_1
	nop
$Lnjp_800C32E4_0:
	jr	$31
	addiu	$2,$0,1
$Lnjp_800C32E4_1:
	jr	$31
	addu	$2,$0,$0
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3318
njp_800C3318:
	addiu	$29,$29,-64
	sw	$16,56($29)
	addu	$16,$4,$0
	addiu	$4,$29,24
	lui	$2,%hi(DG_ZeroMatrix)
	sw	$31,60($29)
	addiu	$11,$2,%lo(DG_ZeroMatrix)
	lw	$8,0($11)
	lw	$9,4($11)
	lw	$10,8($11)
	sw	$8,24($29)
	sw	$9,28($29)
	sw	$10,32($29)
	lw	$8,12($11)
	lw	$9,16($11)
	lw	$10,20($11)
	sw	$8,36($29)
	sw	$9,40($29)
	sw	$10,44($29)
	lw	$8,24($11)
	lw	$9,28($11)
	sw	$8,48($29)
	sw	$9,52($29)
	addiu	$2,$0,20
	addiu	$5,$0,200
	lh	$3,32($16)
	addiu	$6,$0,100
	sw	$2,48($29)
	sw	$3,44($29)
	lh	$2,36($16)
	addiu	$7,$0,300
	sw	$2,52($29)
	addiu	$2,$0,10
	jal	NewWindcrcl_800CF784
	sw	$2,16($29)
	addiu	$4,$16,156
	addiu	$5,$16,2528
	addiu	$2,$0,2
	jal	s08b_p_sphere_800D9834
	sw	$2,2528($16)
	lw	$31,60($29)
	lw	$16,56($29)
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C33C8
njp_800C33C8:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$4,$0,1
	sw	$31,28($29)
	sw	$18,24($29)
	jal	njp_GM_CheckPlayerStatusFlag
	sw	$17,20($29)
	bne	$2,$0,$Lnjp_800C33C8_6
	nop
	lw	$2,2320($16)
	nop
	lhu	$2,2($2)
	nop
	andi	$2,$2,0x4
	beq	$2,$0,$Lnjp_800C33C8_0
	addiu	$2,$0,10
	sw	$2,2312($16)
$Lnjp_800C33C8_0:
	lw	$2,2308($16)
	nop
	beq	$2,$0,$Lnjp_800C33C8_3
	nop
	lw	$3,2200($16)
	nop
	lhu	$2,38($3)
	nop
	addiu	$2,$2,-1
	sh	$2,38($3)
	lw	$2,2200($16)
	nop
	lhu	$2,38($2)
	nop
	andi	$2,$2,0x3f
	bne	$2,$0,$Lnjp_800C33C8_1
	lui	$2,%hi(GM_GameStatus)
	lw	$3,%lo(GM_GameStatus)($2)
	lui	$4,0x200
	or	$3,$3,$4
	sw	$3,%lo(GM_GameStatus)($2)
$Lnjp_800C33C8_1:
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C33C8_2
	nop
	lui	$17,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($17)
	nop
	bne	$2,$0,$Lnjp_800C33C8_2
	nop
	jal	njp_800C2EF0
	addu	$4,$16,$0
	addu	$4,$16,$0
	jal	njp_800C2D68
	addu	$5,$0,$0
	addu	$4,$16,$0
	lui	$5,0x8
	addiu	$2,$0,-1
	jal	njp_sna_set_flags1_8004E2F4
	sw	$2,%lo(GM_GameOverTimer)($17)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4E38)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4E38)
	addiu	$2,$0,3
	sw	$2,2528($16)
	addiu	$2,$0,10
	sw	$2,2312($16)
$Lnjp_800C33C8_2:
	lw	$2,2308($16)
	nop
	beq	$2,$0,$Lnjp_800C33C8_3
	lui	$2,%hi(linkvarbuf+30)
	lh	$3,%lo(linkvarbuf+30)($2)
	addiu	$2,$0,-1
	bne	$3,$2,$Lnjp_800C33C8_3
	addiu	$2,$0,10
	sw	$2,2312($16)
$Lnjp_800C33C8_3:
	lw	$17,2312($16)
	addiu	$2,$0,10
	bne	$17,$2,$Lnjp_800C33C8_6
	nop
	lw	$4,2308($16)
	nop
	bne	$4,$0,$Lnjp_800C33C8_4
	addiu	$18,$16,32
	addu	$4,$18,$0
	addiu	$5,$16,156
	jal	NewKogaku2
	addiu	$6,$0,6
	beq	$2,$0,$Lnjp_800C33C8_6
	sw	$2,2308($16)
	addu	$4,$18,$0
	addiu	$5,$0,78
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$3,%hi(dword_800ABA1C)
	addiu	$2,$0,1
	sw	$2,%lo(dword_800ABA1C)($3)
	lui	$2,%hi(linkvarbuf+30)
	sh	$17,%lo(linkvarbuf+30)($2)
	lui	$2,%hi(snainit_item_800A9420)
	j	$Lnjp_800C33C8_5
	sw	$17,%lo(snainit_item_800A9420)($2)
$Lnjp_800C33C8_4:
	jal	GV_DestroyActorQuick
	nop
	addiu	$4,$16,32
	addiu	$5,$0,78
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lui	$2,%hi(dword_800ABA1C)
	lui	$3,%hi(linkvarbuf+30)
	sw	$0,%lo(dword_800ABA1C)($2)
	addiu	$2,$0,-1
	sw	$0,2308($16)
	sh	$2,%lo(linkvarbuf+30)($3)
	lui	$3,%hi(snainit_item_800A9420)
	addiu	$2,$0,-1
	sw	$2,%lo(snainit_item_800A9420)($3)
$Lnjp_800C33C8_5:
	sw	$0,2312($16)
$Lnjp_800C33C8_6:
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
	.globl	njp_800C35BC
njp_800C35BC:
	addiu	$29,$29,-72
	sw	$18,64($29)
	addu	$18,$4,$0
	addu	$2,$5,$0
	sw	$17,60($29)
	addu	$17,$6,$0
	sw	$31,68($29)
	bltz	$2,$Lnjp_800C35BC_0
	sw	$16,56($29)
	addiu	$16,$29,48
	addu	$4,$16,$0
	addiu	$5,$29,16
	sh	$0,52($29)
	sh	$0,48($29)
	jal	RotMatrixYXZ
	sh	$2,50($29)
	addiu	$4,$29,16
	addu	$5,$16,$0
	addu	$6,$16,$0
	sh	$0,50($29)
	sh	$0,48($29)
	jal	ApplyMatrixSV
	sh	$17,52($29)
	addiu	$4,$18,100
	addu	$5,$16,$0
	jal	GV_AddVec3
	addu	$6,$4,$0
$Lnjp_800C35BC_0:
	lw	$31,68($29)
	lw	$18,64($29)
	lw	$17,60($29)
	lw	$16,56($29)
	jr	$31
	addiu	$29,$29,72
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3640
njp_800C3640:
	addiu	$29,$29,-24
	sw	$31,16($29)
	addiu	$2,$0,13
	beq	$5,$2,$Lnjp_800C3640_3
	addu	$3,$0,$0
	slti	$2,$5,14
	beq	$2,$0,$Lnjp_800C3640_0
	addiu	$2,$0,5
	beq	$5,$2,$Lnjp_800C3640_1
	nop
	j	$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_0:
	addiu	$2,$0,14
	beq	$5,$2,$Lnjp_800C3640_4
	addiu	$2,$0,3
	j	$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_1:
	bne	$6,$0,$Lnjp_800C3640_2
	addiu	$2,$0,10
	j	$Lnjp_800C3640_6
	addiu	$3,$0,168
$Lnjp_800C3640_2:
	bne	$6,$2,$Lnjp_800C3640_6
	nop
	j	$Lnjp_800C3640_6
	addiu	$3,$0,169
$Lnjp_800C3640_3:
	addiu	$2,$0,3
	bne	$6,$2,$Lnjp_800C3640_6
	nop
	j	$Lnjp_800C3640_6
	addiu	$3,$0,205
$Lnjp_800C3640_4:
	beq	$6,$2,$Lnjp_800C3640_5
	nop
	bne	$6,$5,$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_5:
	addiu	$3,$0,205
$Lnjp_800C3640_6:
	beq	$3,$0,$Lnjp_800C3640_7
	addu	$5,$3,$0
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C3640_7:
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
	.globl	njp_800C36EC
njp_800C36EC:
	addiu	$29,$29,-24
	sw	$31,16($29)
	addiu	$2,$0,26
	bne	$5,$2,$Lnjp_800C36EC_1
	addu	$3,$0,$0
	addiu	$2,$0,3
	beq	$6,$2,$Lnjp_800C36EC_0
	addiu	$2,$0,14
	bne	$6,$2,$Lnjp_800C36EC_1
	nop
$Lnjp_800C36EC_0:
	addiu	$3,$0,205
$Lnjp_800C36EC_1:
	beq	$3,$0,$Lnjp_800C36EC_2
	addu	$5,$3,$0
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C36EC_2:
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
	.globl	njp_800C3738
njp_800C3738:
	addiu	$29,$29,-64
	sw	$17,52($29)
	addu	$17,$4,$0
	sw	$18,56($29)
	addu	$18,$5,$0
	sw	$16,48($29)
	addiu	$16,$17,2204
	addu	$4,$16,$0
	addiu	$5,$0,2
	addiu	$6,$0,1
	sw	$31,60($29)
	jal	GM_SetTarget
	addiu	$7,$18,8
	addu	$4,$16,$0
	addiu	$2,$17,2296
	sw	$2,16($29)
	lw	$5,24($18)
	lw	$6,28($18)
	jal	GM_SetCaptureTarget
	addiu	$7,$17,2288
	addu	$4,$18,$0
	addiu	$5,$29,24
	jal	DG_PutVector
	addiu	$6,$0,1
	addu	$4,$16,$0
	jal	GM_MoveTarget
	addiu	$5,$29,24
	addu	$4,$16,$0
	jal	GM_CaptureTarget
	sw	$0,2276($17)
	addu	$16,$2,$0
	beq	$16,$0,$Lnjp_800C3738_2
	addu	$2,$0,$0
	lhu	$2,0($16)
	nop
	andi	$2,$2,0x20
	beq	$2,$0,$Lnjp_800C3738_0
	addiu	$4,$29,32
	lhu	$2,6($16)
	lhu	$3,42($16)
	andi	$2,$2,0xfffd
	sh	$2,6($16)
	lhu	$4,28($18)
	addu	$2,$0,$0
	addu	$3,$3,$4
	j	$Lnjp_800C3738_2
	sh	$3,42($16)
$Lnjp_800C3738_0:
	lwl	$8,35($17)
	lwr	$8,32($17)
	lwl	$9,39($17)
	lwr	$9,36($17)
	swl	$8,35($29)
	swr	$8,32($29)
	swl	$9,39($29)
	swr	$9,36($29)
	lwl	$8,11($16)
	lwr	$8,8($16)
	lwl	$9,15($16)
	lwr	$9,12($16)
	swl	$8,43($29)
	swr	$8,40($29)
	swl	$9,47($29)
	swr	$9,44($29)
	lw	$2,76($17)
	addiu	$6,$0,15
	lw	$5,8($2)
	jal	njp_sna_line_check
	addiu	$7,$0,1
	bgez	$2,$Lnjp_800C3738_1
	addiu	$2,$0,1
	j	$Lnjp_800C3738_2
	sw	$16,2276($17)
$Lnjp_800C3738_1:
	lhu	$2,6($16)
	nop
	andi	$2,$2,0xfffd
	sh	$2,6($16)
	lhu	$2,42($16)
	lhu	$3,28($18)
	nop
	addu	$2,$2,$3
	sh	$2,42($16)
	addu	$2,$0,$0
$Lnjp_800C3738_2:
	lw	$31,60($29)
	lw	$18,56($29)
	lw	$17,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3898
njp_800C3898:
	addiu	$29,$29,-168
	sw	$18,160($29)
	addu	$18,$4,$0
	sw	$16,152($29)
	addu	$16,$5,$0
	sw	$17,156($29)
	addiu	$17,$29,120
	sw	$31,164($29)
	jal	ReadRotMatrix
	addu	$4,$17,$0
	lw	$4,156($18)
	jal	DG_SetPos
	addiu	$4,$4,440
	addu	$4,$16,$0
	addiu	$16,$29,96
	addu	$5,$16,$0
	jal	DG_PutVector
	addiu	$6,$0,2
	jal	SetRotMatrix
	addu	$4,$17,$0
	addu	$4,$16,$0
	addiu	$16,$29,104
	addu	$5,$16,$0
	lw	$3,76($18)
	addiu	$2,$0,1
	sw	$2,16($29)
	lw	$6,0($3)
	jal	GM_OnlineTargetCheck
	addu	$7,$16,$0
	beq	$2,$0,$Lnjp_800C3898_0
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,112
	addiu	$2,$0,100
	sh	$2,116($29)
	sh	$2,114($29)
	jal	GM_SetTarget
	sh	$2,112($29)
	addiu	$4,$29,24
	addiu	$5,$0,1
	addu	$6,$5,$0
	addiu	$7,$0,256
	lui	$2,%hi(DG_ZeroVector)
	addiu	$2,$2,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$2,20($29)
	addiu	$4,$29,24
	jal	GM_MoveTarget
	addu	$5,$16,$0
	jal	GM_PowerTarget
	addiu	$4,$29,24
	lh	$2,104($29)
	lh	$3,106($29)
	lh	$4,108($29)
	sw	$2,140($29)
	sw	$3,144($29)
	sw	$4,148($29)
$Lnjp_800C3898_0:
	lw	$31,164($29)
	lw	$18,160($29)
	lw	$17,156($29)
	lw	$16,152($29)
	jr	$31
	addiu	$29,$29,168
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C399C
njp_800C399C:
	addiu	$29,$29,-112
	sw	$16,104($29)
	addu	$16,$4,$0
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	sw	$31,108($29)
	lw	$2,2200($16)
	nop
	lwl	$3,19($2)
	lwr	$3,16($2)
	lwl	$8,23($2)
	lwr	$8,20($2)
	swl	$3,99($29)
	swr	$3,96($29)
	swl	$8,103($29)
	swr	$8,100($29)
	jal	GM_SetTarget
	addiu	$7,$29,96
	addiu	$4,$29,24
	addiu	$5,$0,1
	addu	$6,$5,$0
	addiu	$7,$0,256
	lui	$2,%hi(DG_ZeroVector)
	addiu	$2,$2,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$2,20($29)
	addiu	$4,$29,24
	jal	GM_MoveTarget
	addiu	$5,$16,32
	jal	GM_PowerTarget
	addiu	$4,$29,24
	lw	$31,108($29)
	lw	$16,104($29)
	jr	$31
	addiu	$29,$29,112
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3A30
njp_800C3A30:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2320($16)
	nop
	lhu	$5,0($2)
	lhu	$4,2($2)
	andi	$3,$5,0x20
	beq	$3,$0,$Lnjp_800C3A30_1
	andi	$2,$4,0x40
	lb	$2,119($16)
	nop
	beq	$2,$0,$Lnjp_800C3A30_1
	andi	$2,$4,0x40
	addu	$4,$16,$0
	lui	$5,0x2000
	jal	njp_sna_set_flags1_8004E2F4
	ori	$5,$5,0x4
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$2,$Lnjp_800C3A30_0
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4A90)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C4A90)
$Lnjp_800C3A30_0:
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4A38)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C4A38)
$Lnjp_800C3A30_1:
	beq	$2,$0,$Lnjp_800C3A30_2
	andi	$2,$4,0x80
	lb	$2,119($16)
	nop
	beq	$2,$0,$Lnjp_800C3A30_2
	andi	$2,$4,0x80
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C5150)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C5150)
$Lnjp_800C3A30_2:
	beq	$2,$0,$Lnjp_800C3A30_4
	andi	$2,$5,0xf000
	beq	$2,$0,$Lnjp_800C3A30_3
	nop
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,2048
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4B44)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C4B44)
$Lnjp_800C3A30_3:
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C6AC0)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C6AC0)
$Lnjp_800C3A30_4:
	andi	$2,$4,0x8
	bne	$2,$0,$Lnjp_800C3A30_5
	addu	$4,$16,$0
	j	$Lnjp_800C3A30_7
	addu	$2,$0,$0
$Lnjp_800C3A30_5:
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4BA4)
	addiu	$5,$5,%lo(njp_800C4BA4)
$Lnjp_800C3A30_6:
	jal	njp_sna_start_anim_8004E1F4
	nop
	addiu	$2,$0,1
$Lnjp_800C3A30_7:
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
	.globl	njp_800C3B98
njp_800C3B98:
	lui	$2,%hi(njp_bss_44)
	lw	$2,%lo(njp_bss_44)($2)
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$2,$0,$Lnjp_800C3B98_0
	sw	$31,20($29)
	lh	$2,2452($16)
	nop
	bne	$2,$0,$Lnjp_800C3B98_0
	addiu	$2,$0,450
	sh	$2,2436($16)
	lui	$4,0x3
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x10
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	jal	GM_ExitBehindCamera
	nop
	j	$Lnjp_800C3B98_1
	addiu	$2,$0,1
$Lnjp_800C3B98_0:
	addu	$2,$0,$0
$Lnjp_800C3B98_1:
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
	.globl	njp_800C3C1C
njp_800C3C1C:
	addiu	$29,$29,-48
	sw	$18,32($29)
	addu	$18,$4,$0
	lui	$5,0x8
	sw	$31,40($29)
	sw	$19,36($29)
	sw	$17,28($29)
	jal	njp_sna_check_flags1_8004E31C
	sw	$16,24($29)
	bne	$2,$0,$Lnjp_800C3C1C_3
	nop
	lhu	$4,80($18)
	jal	GV_ReceiveMessage
	addiu	$5,$29,16
	beq	$2,$0,$Lnjp_800C3C1C_3
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
	blez	$16,$Lnjp_800C3C1C_3
	sw	$3,16($29)
	addiu	$19,$0,8
$Lnjp_800C3C1C_0:
	lw	$2,1952($18)
	nop
	beq	$2,$19,$Lnjp_800C3C1C_3
	nop
	lw	$2,16($29)
	nop
	lhu	$3,4($2)
	ori	$2,$0,0x937a
	beq	$3,$2,$Lnjp_800C3C1C_1
	addiu	$2,$0,28923
	beq	$3,$2,$Lnjp_800C3C1C_1
	ori	$2,$0,0xbe0a
	bne	$3,$2,$Lnjp_800C3C1C_2
	nop
$Lnjp_800C3C1C_1:
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,4
	bne	$2,$0,$Lnjp_800C3C1C_2
	nop
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,4
$Lnjp_800C3C1C_2:
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
	bgtz	$16,$Lnjp_800C3C1C_0
	sw	$3,1952($18)
$Lnjp_800C3C1C_3:
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
	jal	njp_800C32E4
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
	lui	$5,%hi(njp_800C5838)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C5838)
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C41B4
njp_800C41B4:
	lhu	$2,6($4)
	sh	$0,40($4)
	sh	$0,42($4)
	andi	$2,$2,0xff7b
	sh	$2,6($4)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$7,$2,%lo(DG_ZeroVector)
	lwl	$3,3($7)
	lwr	$3,0($7)
	lwl	$5,7($7)
	lwr	$5,4($7)
	swl	$3,47($4)
	swr	$3,44($4)
	swl	$5,51($4)
	swr	$5,48($4)
	addiu	$2,$0,-1
	sw	$2,68($4)
	jr	$31
	sh	$0,62($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C4200
njp_800C4200:
	addiu	$29,$29,-24
	bne	$5,$0,$Lnjp_800C4200_0
	sw	$31,16($29)
	lui	$2,%hi(njp_800C44CC)
	addiu	$2,$2,%lo(njp_800C44CC)
	sw	$2,2340($4)
	lui	$2,%hi(njp_800C6900)
	addiu	$2,$2,%lo(njp_800C6900)
	addiu	$5,$0,2
	addiu	$6,$0,4
	sh	$0,2434($4)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($4)
$Lnjp_800C4200_0:
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
	.globl	njp_800C4244
njp_800C4244:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C4244_0
	sw	$31,20($29)
	addiu	$4,$0,16
	lui	$2,%hi(njp_800C45CC)
	addiu	$2,$2,%lo(njp_800C45CC)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6900)
	addiu	$2,$2,%lo(njp_800C6900)
	jal	njp_GM_SetPlayerStatusFlag
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
$Lnjp_800C4244_0:
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
	.globl	njp_800C4298
njp_800C4298:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	bne	$5,$0,$Lnjp_800C4298_2
	sw	$17,20($29)
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x1
	bne	$2,$0,$Lnjp_800C4298_1
	addu	$4,$16,$0
	addiu	$17,$0,7
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x100
	beq	$2,$0,$Lnjp_800C4298_0
	addiu	$4,$16,32
	addiu	$17,$0,183
$Lnjp_800C4298_0:
	jal	GM_SeSet
	addu	$5,$17,$0
	lui	$2,%hi(njp_bss_56)
	lhu	$2,%lo(njp_bss_56)($2)
	lui	$4,0x1
	addiu	$2,$2,-2048
	jal	njp_GM_SetPlayerStatusFlag
	sh	$2,110($16)
	addu	$4,$16,$0
$Lnjp_800C4298_1:
	addiu	$5,$0,21
	addiu	$2,$0,300
	sh	$2,2436($16)
	lui	$2,%hi(njp_800C4750)
	addiu	$2,$2,%lo(njp_800C4750)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6994)
	addiu	$2,$2,%lo(njp_800C6994)
	addiu	$6,$0,4
	sh	$0,2434($16)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($16)
$Lnjp_800C4298_2:
	lw	$2,76($16)
	nop
	lw	$4,8($2)
	jal	GM_CheckBehindCamera
	addiu	$5,$16,32
	lh	$2,2454($16)
	nop
	slti	$2,$2,8
	beq	$2,$0,$Lnjp_800C4298_5
	lui	$2,%hi(njp_bss_52)
	lw	$4,%lo(njp_bss_52)($2)
	nop
	beq	$4,$0,$Lnjp_800C4298_5
	nop
	lh	$3,0($4)
	nop
	bgez	$3,$Lnjp_800C4298_3
	nop
	addiu	$3,$3,7
$Lnjp_800C4298_3:
	lhu	$2,100($16)
	sra	$3,$3,3
	addu	$2,$2,$3
	sh	$2,100($16)
	lh	$2,4($4)
	nop
	bgez	$2,$Lnjp_800C4298_4
	nop
	addiu	$2,$2,7
$Lnjp_800C4298_4:
	sra	$2,$2,3
	lhu	$3,104($16)
	lhu	$4,2454($16)
	addu	$3,$3,$2
	addiu	$4,$4,1
	sh	$3,104($16)
	sh	$4,2454($16)
$Lnjp_800C4298_5:
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
	.globl	njp_800C43CC
njp_800C43CC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C43CC_1
	sw	$31,20($29)
	lui	$4,0x1
	jal	njp_GM_SetPlayerStatusFlag
	ori	$4,$4,0x10
	lui	$2,%hi(njp_800C47EC)
	addiu	$2,$2,%lo(njp_800C47EC)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6994)
	lh	$3,2480($16)
	addiu	$2,$2,%lo(njp_800C6994)
	sw	$2,2344($16)
	addiu	$2,$0,2
	bne	$3,$2,$Lnjp_800C43CC_0
	addiu	$5,$0,23
	addiu	$5,$0,22
$Lnjp_800C43CC_0:
	addu	$4,$16,$0
	addiu	$2,$0,300
	addiu	$6,$0,4
	sh	$2,2436($16)
	jal	njp_SetAction_8004E22C
	sh	$0,2480($16)
	lui	$2,%hi(njp_bss_56)
	lhu	$2,%lo(njp_bss_56)($2)
	nop
	addiu	$2,$2,-2048
	sh	$2,110($16)
$Lnjp_800C43CC_1:
	lh	$2,2454($16)
	nop
	slti	$2,$2,8
	beq	$2,$0,$Lnjp_800C43CC_4
	lui	$2,%hi(njp_bss_52)
	lw	$4,%lo(njp_bss_52)($2)
	nop
	beq	$4,$0,$Lnjp_800C43CC_4
	nop
	lh	$3,0($4)
	nop
	bgez	$3,$Lnjp_800C43CC_2
	nop
	addiu	$3,$3,7
$Lnjp_800C43CC_2:
	lhu	$2,100($16)
	sra	$3,$3,3
	addu	$2,$2,$3
	sh	$2,100($16)
	lh	$2,4($4)
	nop
	bgez	$2,$Lnjp_800C43CC_3
	nop
	addiu	$2,$2,7
$Lnjp_800C43CC_3:
	sra	$2,$2,3
	lhu	$3,104($16)
	lhu	$4,2454($16)
	addu	$3,$3,$2
	addiu	$4,$4,1
	sh	$3,104($16)
	sh	$4,2454($16)
$Lnjp_800C43CC_4:
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
	.globl	njp_800C44CC
njp_800C44CC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	sw	$31,20($29)
	jal	njp_800C3A30
	addu	$16,$4,$0
	bne	$2,$0,$Lnjp_800C44CC_7
	nop
	lh	$2,2452($16)
	lhu	$3,2452($16)
	blez	$2,$Lnjp_800C44CC_0
	addiu	$2,$3,-1
	sh	$2,2452($16)
$Lnjp_800C44CC_0:
	lh	$2,2452($16)
	nop
	bne	$2,$0,$Lnjp_800C44CC_7
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$2,$Lnjp_800C44CC_7
	lui	$2,%hi(njp_bss_44)
	lw	$3,%lo(njp_bss_44)($2)
	addiu	$2,$0,1
	beq	$3,$2,$Lnjp_800C44CC_1
	addu	$4,$16,$0
	beq	$3,$0,$Lnjp_800C44CC_2
	addiu	$2,$0,2
	lw	$3,1948($16)
	nop
	bne	$3,$2,$Lnjp_800C44CC_3
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	addu	$4,$16,$0
$Lnjp_800C44CC_1:
	lui	$5,%hi(njp_800C4298)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4298)
	j	$Lnjp_800C44CC_7
	nop
$Lnjp_800C44CC_2:
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
$Lnjp_800C44CC_3:
	lh	$4,110($16)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	jal	GV_DiffDirAbs
	nop
	addu	$3,$2,$0
	slti	$2,$3,257
	bne	$2,$0,$Lnjp_800C44CC_5
	addu	$4,$16,$0
	addu	$2,$3,$0
	bgez	$2,$Lnjp_800C44CC_4
	nop
	addiu	$2,$2,1023
$Lnjp_800C44CC_4:
	sra	$2,$2,10
	addiu	$2,$2,1
	j	$Lnjp_800C44CC_6
	sh	$2,2452($16)
$Lnjp_800C44CC_5:
	lui	$5,%hi(njp_800C4244)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4244)
$Lnjp_800C44CC_6:
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lhu	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	sh	$2,110($16)
$Lnjp_800C44CC_7:
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
	.globl	njp_800C45CC
njp_800C45CC:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$31,24($29)
	jal	njp_800C3A30
	sw	$16,16($29)
	bne	$2,$0,$Lnjp_800C45CC_9
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bgez	$2,$Lnjp_800C45CC_0
	lui	$2,%hi(njp_bss_44)
	lhu	$2,2454($17)
	nop
	addiu	$2,$2,1
	sh	$2,2454($17)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,5
	bne	$2,$0,$Lnjp_800C45CC_1
	lui	$2,%hi(njp_bss_44)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$17,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	j	$Lnjp_800C45CC_9
	nop
$Lnjp_800C45CC_0:
	sh	$0,2454($17)
$Lnjp_800C45CC_1:
	lw	$3,%lo(njp_bss_44)($2)
	addiu	$2,$0,1
	beq	$3,$2,$Lnjp_800C45CC_2
	nop
	beq	$3,$0,$Lnjp_800C45CC_3
	addiu	$2,$0,2
	lw	$3,1948($17)
	nop
	bne	$3,$2,$Lnjp_800C45CC_3
	nop
$Lnjp_800C45CC_2:
	lhu	$2,2452($17)
	nop
	addiu	$2,$2,1
	sh	$2,2452($17)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,3
	bne	$2,$0,$Lnjp_800C45CC_4
	nop
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$17,$0
	lui	$5,%hi(njp_800C4298)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4298)
	j	$Lnjp_800C45CC_9
	nop
$Lnjp_800C45CC_3:
	sh	$0,2452($17)
$Lnjp_800C45CC_4:
	lh	$2,2452($17)
	nop
	bne	$2,$0,$Lnjp_800C45CC_5
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$5,$Lnjp_800C45CC_6
	nop
	jal	njp_sub_8004E4C0
	addu	$4,$17,$0
	j	$Lnjp_800C45CC_7
	addu	$16,$2,$0
$Lnjp_800C45CC_5:
	lw	$16,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bgez	$16,$Lnjp_800C45CC_7
	nop
$Lnjp_800C45CC_6:
	lh	$16,110($17)
$Lnjp_800C45CC_7:
	lh	$4,110($17)
	jal	GV_DiffDirAbs
	addu	$5,$16,$0
	slti	$2,$2,1049
	bne	$2,$0,$Lnjp_800C45CC_8
	addu	$4,$17,$0
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$17,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	j	$Lnjp_800C45CC_9
	sh	$16,110($17)
$Lnjp_800C45CC_8:
	sh	$16,110($17)
	jal	njp_sub_8004EA50
	addu	$5,$16,$0
$Lnjp_800C45CC_9:
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
	.globl	njp_800C4750
njp_800C4750:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lh	$2,2452($16)
	lhu	$3,2452($16)
	beq	$2,$0,$Lnjp_800C4750_0
	addiu	$2,$3,-1
	sh	$2,2452($16)
$Lnjp_800C4750_0:
	jal	njp_800C3B98
	addu	$4,$16,$0
	bne	$2,$0,$Lnjp_800C4750_3
	lui	$4,%hi(njp_bss_44)
	lw	$3,%lo(njp_bss_44)($4)
	addiu	$2,$0,2
	beq	$3,$2,$Lnjp_800C4750_1
	addiu	$2,$0,4
	bne	$3,$2,$Lnjp_800C4750_2
	nop
$Lnjp_800C4750_1:
	lhu	$2,%lo(njp_bss_44)($4)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C43CC)
	addiu	$5,$5,%lo(njp_800C43CC)
	jal	njp_sna_start_anim_8004E1F4
	sh	$2,2480($16)
$Lnjp_800C4750_2:
	lui	$4,%hi(njp_bss_56)
	lw	$2,%lo(njp_bss_56)($4)
	lh	$3,42($16)
	addiu	$2,$2,-2048
	beq	$2,$3,$Lnjp_800C4750_3
	nop
	lhu	$2,%lo(njp_bss_56)($4)
	sh	$0,2454($16)
	addiu	$2,$2,-2048
	sh	$2,110($16)
$Lnjp_800C4750_3:
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
	.globl	njp_800C47EC
njp_800C47EC:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lh	$2,2452($16)
	lhu	$3,2452($16)
	beq	$2,$0,$Lnjp_800C47EC_0
	addiu	$2,$3,-1
	sh	$2,2452($16)
$Lnjp_800C47EC_0:
	jal	njp_800C3B98
	addu	$4,$16,$0
	bne	$2,$0,$Lnjp_800C47EC_5
	nop
	lw	$2,76($16)
	nop
	lw	$4,8($2)
	jal	GM_CheckBehindCamera
	addiu	$5,$16,32
	lui	$2,%hi(njp_bss_44)
	lw	$3,%lo(njp_bss_44)($2)
	addiu	$2,$0,1
	bne	$3,$2,$Lnjp_800C47EC_1
	lui	$5,%hi(njp_bss_56)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4298)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4298)
	j	$Lnjp_800C47EC_5
	nop
$Lnjp_800C47EC_1:
	lw	$2,%lo(njp_bss_56)($5)
	lh	$3,42($16)
	addiu	$2,$2,-2048
	bne	$2,$3,$Lnjp_800C47EC_2
	lui	$2,%hi(njp_bss_48)
	lui	$3,%hi(njp_bss_52)
	lw	$4,%lo(njp_bss_48)($2)
	lw	$2,%lo(njp_bss_52)($3)
	nop
	beq	$4,$2,$Lnjp_800C47EC_3
	lui	$2,%hi(njp_bss_44)
$Lnjp_800C47EC_2:
	lhu	$2,%lo(njp_bss_56)($5)
	sh	$0,2454($16)
	addiu	$2,$2,-2048
	sh	$2,110($16)
	lui	$2,%hi(njp_bss_44)
$Lnjp_800C47EC_3:
	lw	$3,%lo(njp_bss_44)($2)
	addiu	$2,$0,2
	bne	$3,$2,$Lnjp_800C47EC_4
	addiu	$17,$0,23
	addiu	$17,$0,22
$Lnjp_800C47EC_4:
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addu	$5,$17,$0
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
$Lnjp_800C47EC_5:
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
	.globl	njp_800C48EC
njp_800C48EC:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C48F4
njp_800C48F4:
	addiu	$29,$29,-32
	sw	$18,24($29)
	addu	$18,$4,$0
	sw	$31,28($29)
	sw	$17,20($29)
	sw	$16,16($29)
	lw	$2,2524($18)
	nop
	blez	$2,$Lnjp_800C48F4_1
	addu	$16,$0,$0
	addu	$17,$18,$0
$Lnjp_800C48F4_0:
	lw	$4,2512($17)
	jal	GM_FreeTarget
	addiu	$17,$17,4
	lw	$2,2524($18)
	addiu	$16,$16,1
	slt	$2,$16,$2
	bne	$2,$0,$Lnjp_800C48F4_0
	nop
$Lnjp_800C48F4_1:
	sw	$0,2524($18)
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
	.globl	njp_800C495C
njp_800C495C:
	addiu	$29,$29,-56
	sw	$19,44($29)
	addu	$19,$4,$0
	addiu	$2,$0,160
	sh	$2,28($29)
	sh	$2,24($29)
	addiu	$2,$0,650
	sw	$31,52($29)
	sw	$20,48($29)
	sw	$18,40($29)
	sw	$17,36($29)
	sw	$16,32($29)
	sh	$2,26($29)
	lw	$2,2524($19)
	nop
	beq	$2,$0,$Lnjp_800C495C_0
	addu	$18,$0,$0
	jal	njp_800C48F4
	nop
$Lnjp_800C495C_0:
	lui	$2,%hi(DG_ZeroVector)
	addiu	$20,$2,%lo(DG_ZeroVector)
	addu	$17,$19,$0
$Lnjp_800C495C_1:
	jal	GM_AllocTarget
	nop
	addu	$16,$2,$0
	beq	$16,$0,$Lnjp_800C495C_2
	sw	$16,2512($17)
	addu	$4,$16,$0
	addiu	$5,$0,21
	addiu	$6,$0,1
	addiu	$7,$29,24
	addiu	$17,$17,4
	lw	$2,2524($19)
	addu	$18,$18,$6
	addu	$2,$2,$6
	jal	GM_SetTarget
	sw	$2,2524($19)
	addu	$4,$16,$0
	addiu	$5,$0,1
	addiu	$6,$0,-1
	addiu	$7,$0,1024
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$20,20($29)
	slti	$2,$18,3
	bne	$2,$0,$Lnjp_800C495C_1
	nop
$Lnjp_800C495C_2:
	lw	$31,52($29)
	lw	$20,48($29)
	lw	$19,44($29)
	lw	$18,40($29)
	lw	$17,36($29)
	lw	$16,32($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C4A38
njp_800C4A38:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C4A38_0
	sw	$31,20($29)
	lui	$2,%hi(njp_800C5C18)
	addiu	$2,$2,%lo(njp_800C5C18)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	addiu	$5,$0,3
	addiu	$6,$0,4
	jal	njp_SetAction_8004E22C
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$2,$0,-1
	jal	njp_800C495C
	sh	$2,2452($4)
$Lnjp_800C4A38_0:
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
	.globl	njp_800C4A90
njp_800C4A90:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C4A90_0
	sw	$31,20($29)
	lui	$2,%hi(njp_800C5D4C)
	addiu	$2,$2,%lo(njp_800C5D4C)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	addiu	$5,$0,24
	addiu	$6,$0,4
	jal	njp_SetAction_8004E22C
	sw	$2,2344($16)
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addiu	$2,$0,-1
	jal	njp_800C495C
	sh	$2,2452($4)
$Lnjp_800C4A90_0:
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
	.globl	njp_800C4AF0
njp_800C4AF0:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C4AF0_0
	sw	$31,20($29)
	addiu	$5,$0,14
	lui	$2,%hi(njp_800C5E9C)
	addiu	$2,$2,%lo(njp_800C5E9C)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	addiu	$6,$0,4
	jal	njp_SetAction_8004E22C
	sw	$2,2344($16)
	addu	$4,$16,$0
	jal	njp_800C2D68
	addu	$5,$0,$0
$Lnjp_800C4AF0_0:
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
	.globl	njp_800C4B44
njp_800C4B44:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C4B44_0
	sw	$31,20($29)
	addiu	$5,$0,13
	lui	$2,%hi(njp_800C5F20)
	addiu	$2,$2,%lo(njp_800C5F20)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C48EC)
	lui	$3,%hi(njp_gSnaMoveDir_800ABBA4)
	addiu	$2,$2,%lo(njp_800C48EC)
	lhu	$3,%lo(njp_gSnaMoveDir_800ABBA4)($3)
	addiu	$6,$0,4
	sw	$2,2344($16)
	jal	njp_SetAction_8004E22C
	sh	$3,110($16)
	addu	$4,$16,$0
	jal	njp_800C2D68
	addu	$5,$0,$0
$Lnjp_800C4B44_0:
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
	.globl	njp_800C4BA4
njp_800C4BA4:
	addiu	$29,$29,-128
	sw	$18,112($29)
	addu	$18,$4,$0
	sw	$16,104($29)
	addu	$16,$5,$0
	sw	$31,120($29)
	sw	$19,116($29)
	bne	$16,$0,$Lnjp_800C4BA4_0
	sw	$17,108($29)
	addiu	$5,$0,12
	addiu	$6,$0,4
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$2,2340($18)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($18)
	addiu	$4,$18,32
	addiu	$5,$0,198
	jal	GM_SeSetMode
	addiu	$6,$0,1
	jal	njp_800C3318
	addu	$4,$18,$0
$Lnjp_800C4BA4_0:
	lui	$2,0x6666
	ori	$2,$2,0x6667
	mult	$16,$2
	sra	$2,$16,31
	mfhi	$8
	sra	$3,$8,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	bne	$16,$2,$Lnjp_800C4BA4_1
	nop
	addiu	$4,$18,32
	addiu	$5,$0,208
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C4BA4_1:
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,96
	addiu	$2,$0,750
	addiu	$17,$0,200
	sh	$2,100($29)
	sh	$2,96($29)
	jal	GM_SetTarget
	sh	$17,98($29)
	addiu	$4,$29,24
	addiu	$5,$0,1
	addiu	$6,$0,2
	addiu	$7,$0,256
	lui	$16,%hi(DG_ZeroVector)
	addiu	$16,$16,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$16,20($29)
	addiu	$4,$29,24
	addiu	$19,$18,32
	jal	GM_MoveTarget
	addu	$5,$19,$0
	jal	GM_PowerTarget
	addiu	$4,$29,24
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,96
	addiu	$2,$0,1500
	sh	$2,100($29)
	sh	$2,96($29)
	jal	GM_SetTarget
	sh	$17,98($29)
	addiu	$4,$29,24
	addiu	$5,$0,1
	addiu	$6,$0,2
	addu	$7,$5,$0
	addiu	$2,$0,5
	sw	$2,16($29)
	jal	GM_SetPowerTarget
	sw	$16,20($29)
	addiu	$4,$29,24
	jal	GM_MoveTarget
	addu	$5,$19,$0
	jal	GM_PowerTarget
	addiu	$4,$29,24
	lhu	$2,2452($18)
	addiu	$3,$0,24
	addiu	$2,$2,1
	sh	$2,2452($18)
	sll	$2,$2,16
	sra	$2,$2,16
	bne	$2,$3,$Lnjp_800C4BA4_2
	addiu	$2,$0,3
	sw	$2,2528($18)
$Lnjp_800C4BA4_2:
	lh	$3,2452($18)
	addiu	$2,$0,32
	bne	$3,$2,$Lnjp_800C4BA4_3
	addiu	$5,$0,198
	addu	$4,$19,$0
	jal	GM_SeSetMode
	addiu	$6,$0,1
	sh	$0,2452($18)
	jal	njp_800C3318
	addu	$4,$18,$0
$Lnjp_800C4BA4_3:
	lw	$3,2200($18)
	nop
	lhu	$2,38($3)
	nop
	addiu	$2,$2,-1
	sh	$2,38($3)
	lw	$2,2200($18)
	nop
	lhu	$2,38($2)
	nop
	andi	$2,$2,0x3f
	bne	$2,$0,$Lnjp_800C4BA4_4
	lui	$2,%hi(GM_GameStatus)
	lw	$3,%lo(GM_GameStatus)($2)
	lui	$4,0x200
	or	$3,$3,$4
	sw	$3,%lo(GM_GameStatus)($2)
$Lnjp_800C4BA4_4:
	lw	$2,2200($18)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C4BA4_5
	lui	$16,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($16)
	nop
	bne	$2,$0,$Lnjp_800C4BA4_5
	addu	$4,$18,$0
	jal	njp_800C2D68
	addu	$5,$0,$0
	addu	$4,$18,$0
	lui	$5,0x8
	addiu	$2,$0,-1
	jal	njp_sna_set_flags1_8004E2F4
	sw	$2,%lo(GM_GameOverTimer)($16)
	addu	$4,$18,$0
	lui	$5,%hi(njp_800C4E38)
	j	$Lnjp_800C4BA4_6
	addiu	$5,$5,%lo(njp_800C4E38)
$Lnjp_800C4BA4_5:
	lw	$2,2320($18)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x8
	bne	$2,$0,$Lnjp_800C4BA4_7
	addu	$4,$18,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
	addu	$4,$18,$0
	lui	$5,%hi(njp_800C4200)
	addiu	$5,$5,%lo(njp_800C4200)
$Lnjp_800C4BA4_6:
	jal	njp_sna_start_anim_8004E1F4
	nop
	addiu	$2,$0,3
	sw	$2,2528($18)
$Lnjp_800C4BA4_7:
	lw	$31,120($29)
	lw	$19,116($29)
	lw	$18,112($29)
	lw	$17,108($29)
	lw	$16,104($29)
	jr	$31
	addiu	$29,$29,128
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C4E38
njp_800C4E38:
	addiu	$29,$29,-128
	sw	$19,116($29)
	addu	$19,$4,$0
	sw	$31,120($29)
	sw	$18,112($29)
	sw	$17,108($29)
	bne	$5,$0,$Lnjp_800C4E38_0
	sw	$16,104($29)
	addiu	$5,$0,19
	addiu	$6,$0,4
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$2,2340($19)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($19)
$Lnjp_800C4E38_0:
	lh	$3,2452($19)
	nop
	beq	$3,$0,$Lnjp_800C4E38_1
	addiu	$2,$0,1
	beq	$3,$2,$Lnjp_800C4E38_2
	lui	$3,0x6666
	j	$Lnjp_800C4E38_5
	nop
$Lnjp_800C4E38_1:
	lh	$2,182($19)
	nop
	beq	$2,$0,$Lnjp_800C4E38_5
	addiu	$5,$0,12
	addu	$4,$19,$0
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$17,$19,32
	addu	$4,$17,$0
	addiu	$5,$0,199
	jal	GM_SeSetMode
	addiu	$6,$0,1
	jal	njp_800C3318
	addu	$4,$19,$0
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,96
	addiu	$2,$0,750
	addiu	$18,$0,200
	sh	$2,100($29)
	sh	$2,96($29)
	jal	GM_SetTarget
	sh	$18,98($29)
	addiu	$4,$29,24
	addiu	$5,$0,1
	addiu	$6,$0,2
	addiu	$7,$0,256
	lui	$16,%hi(DG_ZeroVector)
	addiu	$16,$16,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$16,20($29)
	addiu	$4,$29,24
	jal	GM_MoveTarget
	addu	$5,$17,$0
	jal	GM_PowerTarget
	addiu	$4,$29,24
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,96
	addiu	$2,$0,1500
	sh	$2,100($29)
	sh	$2,96($29)
	jal	GM_SetTarget
	sh	$18,98($29)
	addiu	$4,$29,24
	addiu	$5,$0,1
	addiu	$6,$0,2
	addu	$7,$5,$0
	addiu	$2,$0,5
	sw	$2,16($29)
	jal	GM_SetPowerTarget
	sw	$16,20($29)
	addiu	$4,$29,24
	jal	GM_MoveTarget
	addu	$5,$17,$0
	jal	GM_PowerTarget
	addiu	$4,$29,24
	lhu	$2,2452($19)
	nop
	addiu	$2,$2,1
	j	$Lnjp_800C4E38_5
	sh	$2,2452($19)
$Lnjp_800C4E38_2:
	lhu	$2,2454($19)
	ori	$3,$3,0x6667
	sll	$2,$2,16
	sra	$4,$2,16
	mult	$4,$3
	sra	$2,$2,31
	mfhi	$8
	sra	$3,$8,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$4,$4,$2
	sll	$4,$4,16
	bne	$4,$0,$Lnjp_800C4E38_3
	addiu	$4,$19,32
	addiu	$5,$0,208
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C4E38_3:
	lhu	$2,2454($19)
	addiu	$3,$0,24
	addiu	$2,$2,1
	sh	$2,2454($19)
	sll	$2,$2,16
	sra	$2,$2,16
	bne	$2,$3,$Lnjp_800C4E38_4
	nop
	jal	njp_800C3270
	addu	$4,$19,$0
	addiu	$2,$0,3
	sw	$2,2528($19)
$Lnjp_800C4E38_4:
	lh	$3,2454($19)
	addiu	$2,$0,32
	bne	$3,$2,$Lnjp_800C4E38_5
	nop
	jal	njp_800C3318
	addu	$4,$19,$0
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,96
	addiu	$2,$0,750
	addiu	$18,$0,200
	sh	$2,100($29)
	sh	$2,96($29)
	jal	GM_SetTarget
	sh	$18,98($29)
	addiu	$4,$29,24
	addiu	$5,$0,1
	addiu	$6,$0,2
	addiu	$7,$0,256
	lui	$16,%hi(DG_ZeroVector)
	addiu	$16,$16,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$16,20($29)
	addiu	$4,$29,24
	addiu	$17,$19,32
	jal	GM_MoveTarget
	addu	$5,$17,$0
	jal	GM_PowerTarget
	addiu	$4,$29,24
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,96
	addiu	$2,$0,1500
	sh	$2,100($29)
	sh	$2,96($29)
	jal	GM_SetTarget
	sh	$18,98($29)
	addiu	$4,$29,24
	addiu	$5,$0,1
	addiu	$6,$0,2
	addu	$7,$5,$0
	addiu	$2,$0,5
	sw	$2,16($29)
	jal	GM_SetPowerTarget
	sw	$16,20($29)
	addiu	$4,$29,24
	jal	GM_MoveTarget
	addu	$5,$17,$0
	jal	GM_PowerTarget
	addiu	$4,$29,24
$Lnjp_800C4E38_5:
	lw	$31,120($29)
	lw	$19,116($29)
	lw	$18,112($29)
	lw	$17,108($29)
	lw	$16,104($29)
	jr	$31
	addiu	$29,$29,128
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5104
njp_800C5104:
	addiu	$5,$4,72
	lui	$6,0x1
	ori	$6,$6,0x86a0
	lh	$7,46($4)
	nop
	blez	$7,$Lnjp_800C5104_2
	addu	$4,$0,$0
$Lnjp_800C5104_0:
	lw	$3,24($5)
	nop
	slt	$2,$3,$6
	beq	$2,$0,$Lnjp_800C5104_1
	nop
	addu	$6,$3,$0
$Lnjp_800C5104_1:
	addiu	$4,$4,1
	slt	$2,$4,$7
	bne	$2,$0,$Lnjp_800C5104_0
	addiu	$5,$5,92
$Lnjp_800C5104_2:
	jr	$31
	addu	$2,$6,$0
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5150
njp_800C5150:
	addiu	$29,$29,-168
	sw	$20,160($29)
	addu	$20,$4,$0
	sw	$17,148($29)
	addu	$17,$5,$0
	sw	$31,164($29)
	sw	$19,156($29)
	sw	$18,152($29)
	bne	$17,$0,$Lnjp_800C5150_0
	sw	$16,144($29)
	addiu	$5,$0,27
	addiu	$6,$0,4
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$2,2340($20)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($20)
	addu	$4,$20,$0
	jal	njp_800C2D68
	addu	$5,$0,$0
	addu	$4,$20,$0
	addiu	$5,$0,4096
	lbu	$2,117($20)
	lhu	$3,152($20)
	ori	$2,$2,0x8
	sh	$3,2452($20)
	jal	njp_sna_set_flags1_8004E2F4
	sb	$2,117($20)
	addiu	$4,$20,32
	addiu	$5,$0,209
	addiu	$6,$0,1
	jal	GM_SeSetMode
	sh	$0,2442($20)
$Lnjp_800C5150_0:
	slti	$2,$17,12
	beq	$2,$0,$Lnjp_800C5150_2
	sw	$0,1944($20)
	addu	$4,$20,$0
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	jal	njp_800C35BC
	addiu	$6,$0,96
	addiu	$16,$20,32
	addu	$4,$16,$0
	addiu	$5,$20,2120
	lh	$3,2452($20)
	lh	$6,152($20)
	lhu	$2,180($20)
	subu	$3,$6,$3
	subu	$2,$2,$3
	sh	$2,82($20)
	addu	$2,$2,$6
	sh	$2,34($20)
	sll	$2,$2,16
	lw	$3,156($20)
	sra	$2,$2,16
	jal	DG_GetLightMatrix2
	sw	$2,24($3)
	lw	$2,76($20)
	addu	$5,$16,$0
	lw	$4,8($2)
	jal	njp_sub_8004E588
	addiu	$6,$29,24
	lhu	$2,24($29)
	nop
	sh	$2,152($20)
	lhu	$2,28($29)
	nop
	sh	$2,154($20)
	addiu	$2,$0,11
	bne	$17,$2,$Lnjp_800C5150_5
	nop
	lw	$4,156($20)
	jal	njp_800C5104
	nop
	lh	$3,34($20)
	nop
	subu	$3,$3,$2
	slti	$2,$3,97
	beq	$2,$0,$Lnjp_800C5150_1
	nop
	addiu	$3,$0,97
$Lnjp_800C5150_1:
	lw	$2,2200($20)
	sh	$3,82($20)
	j	$Lnjp_800C5150_5
	sh	$3,18($2)
$Lnjp_800C5150_2:
	lw	$4,156($20)
	jal	njp_800C5104
	nop
	lh	$3,34($20)
	nop
	subu	$3,$3,$2
	slti	$2,$3,97
	beq	$2,$0,$Lnjp_800C5150_3
	addu	$4,$20,$0
	addiu	$3,$0,97
$Lnjp_800C5150_3:
	lw	$2,2200($20)
	addiu	$5,$0,4096
	sh	$3,82($20)
	jal	njp_sna_check_flags1_8004E31C
	sh	$3,18($2)
	beq	$2,$0,$Lnjp_800C5150_5
	nop
	lb	$2,119($20)
	nop
	beq	$2,$0,$Lnjp_800C5150_4
	addu	$4,$20,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4096
	addiu	$4,$29,32
	lui	$2,%hi(DG_ZeroMatrix)
	addiu	$11,$2,%lo(DG_ZeroMatrix)
	lw	$8,0($11)
	lw	$9,4($11)
	lw	$10,8($11)
	sw	$8,32($29)
	sw	$9,36($29)
	sw	$10,40($29)
	lw	$8,12($11)
	lw	$9,16($11)
	lw	$10,20($11)
	sw	$8,44($29)
	sw	$9,48($29)
	sw	$10,52($29)
	lw	$8,24($11)
	lw	$9,28($11)
	sw	$8,56($29)
	sw	$9,60($29)
	lh	$2,32($20)
	addiu	$5,$0,200
	sw	$2,52($29)
	lh	$2,152($20)
	addiu	$6,$0,100
	addiu	$2,$2,20
	sw	$2,56($29)
	lh	$2,36($20)
	addiu	$7,$0,300
	sw	$2,60($29)
	addiu	$2,$0,10
	jal	NewWindcrcl_800CF784
	sw	$2,16($29)
	addiu	$16,$29,64
	addu	$4,$16,$0
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,136
	addiu	$2,$0,350
	addiu	$19,$0,150
	sh	$2,76($16)
	sh	$2,72($16)
	jal	GM_SetTarget
	sh	$19,74($16)
	addu	$4,$16,$0
	addiu	$5,$0,1
	addiu	$6,$0,2
	addiu	$7,$0,256
	lui	$17,%hi(DG_ZeroVector)
	addiu	$17,$17,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$17,20($29)
	addu	$4,$16,$0
	addiu	$18,$20,32
	jal	GM_MoveTarget
	addu	$5,$18,$0
	jal	GM_PowerTarget
	addu	$4,$16,$0
	addu	$4,$16,$0
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,136
	addiu	$2,$0,500
	sh	$2,76($16)
	sh	$2,72($16)
	jal	GM_SetTarget
	sh	$19,74($16)
	addu	$4,$16,$0
	addiu	$5,$0,1
	addiu	$6,$0,2
	addu	$7,$5,$0
	addiu	$2,$0,5
	sw	$2,16($29)
	jal	GM_SetPowerTarget
	sw	$17,20($29)
	addu	$4,$16,$0
	addu	$5,$18,$0
	addiu	$2,$0,4
	jal	GM_MoveTarget
	sw	$2,68($16)
	jal	GM_PowerTarget
	addu	$4,$16,$0
	lui	$4,%hi(njp_data)
	addiu	$4,$4,%lo(njp_data)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_data+4)
	addiu	$4,$4,%lo(njp_data+4)
	jal	NewPadVibration
	addiu	$5,$0,2
	addu	$4,$18,$0
	addiu	$5,$0,210
	jal	GM_SeSetMode
	addiu	$6,$0,1
	j	$Lnjp_800C5150_5
	nop
$Lnjp_800C5150_4:
	lhu	$2,2442($20)
	nop
	addiu	$2,$2,-96
	sh	$2,2442($20)
$Lnjp_800C5150_5:
	lh	$2,182($20)
	nop
	beq	$2,$0,$Lnjp_800C5150_6
	lui	$5,%hi(njp_800C4200)
	addu	$4,$20,$0
	lbu	$2,117($20)
	addiu	$5,$5,%lo(njp_800C4200)
	andi	$2,$2,0xf7
	jal	njp_sna_start_anim_8004E1F4
	sb	$2,117($20)
	addu	$4,$20,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4100
	jal	njp_800C2DB4
	addu	$4,$20,$0
$Lnjp_800C5150_6:
	lw	$31,164($29)
	lw	$20,160($29)
	lw	$19,156($29)
	lw	$18,152($29)
	lw	$17,148($29)
	lw	$16,144($29)
	jr	$31
	addiu	$29,$29,168
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C54EC
njp_800C54EC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C54EC_0
	sw	$31,20($29)
	addiu	$5,$0,5
	addiu	$6,$0,4
	lui	$2,%hi(njp_800C60E4)
	addiu	$2,$2,%lo(njp_800C60E4)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,26
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addiu	$7,$0,1022
	addiu	$2,$0,1
	sh	$2,2452($16)
$Lnjp_800C54EC_0:
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
	.globl	njp_800C5550
njp_800C5550:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C5550_0
	sw	$31,20($29)
	jal	njp_800C29E4
	nop
	jal	njp_800C2EF0
	addu	$4,$16,$0
	addu	$4,$16,$0
	addu	$5,$0,$0
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$2,2340($16)
	jal	njp_800C2D68
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,28
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
$Lnjp_800C5550_0:
	lh	$2,2452($16)
	nop
	bne	$2,$0,$Lnjp_800C5550_1
	nop
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5550_1
	addiu	$2,$0,15
	sw	$2,448($16)
	addiu	$2,$0,1
	sh	$0,408($16)
	sh	$2,2452($16)
$Lnjp_800C5550_1:
	lbu	$2,119($16)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$Lnjp_800C5550_2
	nop
	jal	njp_800C2DB4
	addu	$4,$16,$0
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	addiu	$4,$16,32
	addiu	$5,$0,210
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C5550_2:
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
	.globl	njp_800C5634
njp_800C5634:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C5634_0
	sw	$31,20($29)
	addu	$5,$0,$0
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6A60)
	addiu	$2,$2,%lo(njp_800C6A60)
	jal	njp_800C2D68
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,9
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$4,$16,32
	addiu	$5,$0,197
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C5634_0
	lui	$3,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($3)
	nop
	bne	$2,$0,$Lnjp_800C5634_0
	addiu	$2,$0,-1
	sw	$2,%lo(GM_GameOverTimer)($3)
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x8
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4E38)
	j	$Lnjp_800C5634_2
	addiu	$5,$5,%lo(njp_800C4E38)
$Lnjp_800C5634_0:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5634_3
	nop
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C5634_1
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4E38)
	j	$Lnjp_800C5634_2
	addiu	$5,$5,%lo(njp_800C4E38)
$Lnjp_800C5634_1:
	jal	njp_800C2D68
	addiu	$5,$0,32
	lui	$4,0x40
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x100
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	addiu	$5,$5,%lo(njp_800C4200)
$Lnjp_800C5634_2:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C5634_3:
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
	.globl	njp_800C573C
njp_800C573C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C573C_0
	sw	$31,20($29)
	addu	$5,$0,$0
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6A60)
	addiu	$2,$2,%lo(njp_800C6A60)
	sh	$0,2434($16)
	jal	njp_800C2D68
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,10
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$4,$16,32
	addiu	$5,$0,197
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C573C_0
	lui	$3,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($3)
	nop
	bne	$2,$0,$Lnjp_800C573C_0
	addiu	$2,$0,-1
	sw	$2,%lo(GM_GameOverTimer)($3)
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x8
$Lnjp_800C573C_0:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C573C_3
	nop
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C573C_1
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4E38)
	j	$Lnjp_800C573C_2
	addiu	$5,$5,%lo(njp_800C4E38)
$Lnjp_800C573C_1:
	jal	njp_800C2D68
	addiu	$5,$0,32
	lui	$4,0x40
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x100
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	addiu	$5,$5,%lo(njp_800C4200)
$Lnjp_800C573C_2:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C573C_3:
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
	.globl	njp_800C5838
njp_800C5838:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$18,32($29)
	addiu	$18,$16,2368
	sw	$31,36($29)
	bne	$5,$0,$Lnjp_800C5838_3
	sw	$17,28($29)
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$2,2340($16)
	jal	njp_800C2E00
	sw	$2,2344($16)
	lui	$4,0x2000
	jal	njp_GM_SetPlayerStatusFlag
	ori	$4,$4,0x8000
	lhu	$3,8($18)
	nop
	andi	$2,$3,0x400
	bne	$2,$0,$Lnjp_800C5838_1
	addu	$4,$16,$0
	andi	$2,$3,0x4000
	bne	$2,$0,$Lnjp_800C5838_0
	addiu	$2,$0,-2
	addiu	$2,$0,-1
$Lnjp_800C5838_0:
	sh	$2,88($16)
	sh	$2,86($16)
	sh	$2,2436($16)
	addu	$4,$16,$0
$Lnjp_800C5838_1:
	jal	njp_800C2D68
	addu	$5,$0,$0
	addu	$4,$16,$0
	addiu	$17,$0,-1
	sh	$17,170($16)
	lhu	$5,0($18)
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	lh	$2,2($18)
	nop
	bltz	$2,$Lnjp_800C5838_2
	nop
	sh	$2,110($16)
	sh	$2,42($16)
$Lnjp_800C5838_2:
	sh	$17,2452($16)
	sh	$17,2454($16)
$Lnjp_800C5838_3:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,64
	sh	$0,108($16)
	lhu	$2,8($18)
	nop
	andi	$2,$2,0x2
	bne	$2,$0,$Lnjp_800C5838_4
	lui	$2,%hi(DG_ZeroVector)
	addiu	$10,$2,%lo(DG_ZeroVector)
	lwl	$7,3($10)
	lwr	$7,0($10)
	lwl	$8,7($10)
	lwr	$8,4($10)
	swl	$7,2443($16)
	swr	$7,2440($16)
	swl	$8,2447($16)
	swr	$8,2444($16)
$Lnjp_800C5838_4:
	lhu	$3,8($18)
	nop
	andi	$2,$3,0x4000
	bne	$2,$0,$Lnjp_800C5838_5
	addiu	$5,$16,32
	andi	$2,$3,0x2
	bne	$2,$0,$Lnjp_800C5838_6
	addiu	$4,$16,32
	addiu	$5,$16,2120
	lh	$3,10($18)
	lh	$6,152($16)
	lhu	$2,180($16)
	subu	$3,$6,$3
	subu	$2,$2,$3
	sh	$2,82($16)
	addu	$2,$2,$6
	sh	$2,34($16)
	sll	$2,$2,16
	lw	$3,156($16)
	sra	$2,$2,16
	jal	DG_GetLightMatrix2
	sw	$2,24($3)
	j	$Lnjp_800C5838_6
	nop
$Lnjp_800C5838_5:
	lw	$2,76($16)
	nop
	lw	$4,8($2)
	jal	njp_sub_8004E588
	addiu	$6,$29,16
	lhu	$2,16($29)
	nop
	sh	$2,152($16)
	lhu	$2,20($29)
	nop
	sh	$2,154($16)
$Lnjp_800C5838_6:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5838_9
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x20
	lhu	$2,8($18)
	nop
	andi	$2,$2,0x20
	bne	$2,$0,$Lnjp_800C5838_7
	nop
	lbu	$2,117($16)
	nop
	andi	$2,$2,0xfd
	sb	$2,117($16)
$Lnjp_800C5838_7:
	lhu	$2,8($18)
	nop
	andi	$2,$2,0x100
	beq	$2,$0,$Lnjp_800C5838_8
	addiu	$2,$0,15
	sw	$2,448($16)
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sh	$0,408($16)
	sw	$2,2324($16)
	sw	$0,2328($16)
	sh	$0,2454($16)
	j	$Lnjp_800C5838_9
	sh	$0,2452($16)
$Lnjp_800C5838_8:
	lui	$4,0x2000
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x8040
	jal	njp_800C2DB4
	addu	$4,$16,$0
	sh	$0,2434($16)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
$Lnjp_800C5838_9:
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5A70
njp_800C5A70:
	addiu	$29,$29,-96
	sw	$19,84($29)
	addu	$19,$4,$0
	addiu	$4,$29,40
	sw	$31,88($29)
	sw	$18,80($29)
	sw	$17,76($29)
	jal	ReadRotMatrix
	sw	$16,72($29)
	addiu	$4,$19,32
	jal	DG_SetPos2
	addiu	$5,$19,40
	lui	$4,%hi(njp_data+80)
	addiu	$4,$4,%lo(njp_data+80)
	addiu	$5,$29,16
	jal	DG_PutVector
	addiu	$6,$0,3
	lw	$2,2524($19)
	nop
	blez	$2,$Lnjp_800C5A70_1
	addu	$16,$0,$0
	addiu	$18,$29,16
	addu	$17,$19,$0
	addu	$5,$18,$0
$Lnjp_800C5A70_0:
	addiu	$18,$18,8
	lw	$4,2512($17)
	jal	GM_MoveTarget
	addiu	$17,$17,4
	lw	$2,2524($19)
	addiu	$16,$16,1
	slt	$2,$16,$2
	bne	$2,$0,$Lnjp_800C5A70_0
	addu	$5,$18,$0
$Lnjp_800C5A70_1:
	jal	SetRotMatrix
	addiu	$4,$29,40
	lw	$31,88($29)
	lw	$19,84($29)
	lw	$18,80($29)
	lw	$17,76($29)
	lw	$16,72($29)
	jr	$31
	addiu	$29,$29,96
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5B18
njp_800C5B18:
	addiu	$29,$29,-72
	sw	$20,64($29)
	addu	$20,$4,$0
	sw	$19,60($29)
	addu	$19,$0,$0
	lui	$4,0x80
	sw	$31,68($29)
	sw	$18,56($29)
	sw	$17,52($29)
	jal	njp_GM_CheckPlayerStatusFlag
	sw	$16,48($29)
	bne	$2,$0,$Lnjp_800C5B18_3
	addu	$2,$19,$0
	lw	$2,2524($20)
	nop
	slt	$2,$19,$2
	beq	$2,$0,$Lnjp_800C5B18_2
	addu	$18,$0,$0
	addu	$17,$20,$0
$Lnjp_800C5B18_0:
	lw	$16,2512($17)
	nop
	lhu	$5,6($16)
	nop
	andi	$2,$5,0x4
	beq	$2,$0,$Lnjp_800C5B18_1
	addiu	$2,$0,1
	lh	$3,62($16)
	nop
	bne	$3,$2,$Lnjp_800C5B18_1
	addiu	$4,$29,16
	andi	$2,$5,0xfffb
	sh	$2,6($16)
	addiu	$2,$0,1024
	sh	$0,62($16)
	jal	ReadRotMatrix
	sh	$2,38($16)
	addiu	$19,$19,1
	lh	$2,8($16)
	addiu	$4,$20,32
	sw	$2,36($29)
	lh	$2,10($16)
	addiu	$5,$0,211
	sw	$2,40($29)
	lh	$2,12($16)
	addiu	$6,$0,1
	jal	GM_SeSetMode
	sw	$2,44($29)
	addiu	$4,$29,16
	jal	NewSpark
	addiu	$5,$0,1
$Lnjp_800C5B18_1:
	lw	$2,2524($20)
	addiu	$18,$18,1
	slt	$2,$18,$2
	bne	$2,$0,$Lnjp_800C5B18_0
	addiu	$17,$17,4
$Lnjp_800C5B18_2:
	addu	$2,$19,$0
$Lnjp_800C5B18_3:
	lw	$31,68($29)
	lw	$20,64($29)
	lw	$19,60($29)
	lw	$18,56($29)
	lw	$17,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,72
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5C18
njp_800C5C18:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$2,$0,2
	sw	$31,20($29)
	jal	njp_800C5A70
	sw	$2,2532($16)
	jal	njp_800C5B18
	addu	$4,$16,$0
	beq	$2,$0,$Lnjp_800C5C18_1
	nop
	lhu	$2,2452($16)
	nop
	addiu	$2,$2,1
	sh	$2,2452($16)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,3
	bne	$2,$0,$Lnjp_800C5C18_0
	addu	$4,$16,$0
	sh	$0,2452($16)
$Lnjp_800C5C18_0:
	lh	$5,2452($16)
	addu	$6,$0,$0
	jal	njp_SetAction_8004E22C
	addiu	$5,$5,16
$Lnjp_800C5C18_1:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5C18_2
	addu	$4,$16,$0
	addiu	$5,$0,3
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$2,$0,-1
	sh	$2,2452($16)
$Lnjp_800C5C18_2:
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x20
	bne	$2,$0,$Lnjp_800C5C18_3
	lui	$3,%hi(njp_gSnaMoveDir_800ABBA4)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4AF0)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4AF0)
	addu	$4,$16,$0
	lui	$5,0x2000
	jal	njp_sna_clear_flags1_8004E308
	ori	$5,$5,0x4
	j	$Lnjp_800C5C18_4
	addiu	$4,$0,2048
$Lnjp_800C5C18_3:
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($3)
	nop
	bltz	$2,$Lnjp_800C5C18_5
	nop
	lhu	$2,%lo(njp_gSnaMoveDir_800ABBA4)($3)
	lhu	$3,2454($16)
	sh	$2,110($16)
	addiu	$2,$3,1
	sll	$3,$3,16
	sra	$3,$3,16
	slti	$3,$3,2
	bne	$3,$0,$Lnjp_800C5C18_5
	sh	$2,2454($16)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4A90)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4A90)
	addiu	$4,$0,16
$Lnjp_800C5C18_4:
	jal	njp_GM_SetPlayerStatusFlag
	nop
	jal	njp_800C48F4
	addu	$4,$16,$0
$Lnjp_800C5C18_5:
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
	.globl	njp_800C5D4C
njp_800C5D4C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	sw	$31,20($29)
	jal	njp_800C5A70
	addu	$16,$4,$0
	jal	njp_800C5B18
	addu	$4,$16,$0
	beq	$2,$0,$Lnjp_800C5D4C_1
	nop
	lhu	$2,2452($16)
	nop
	addiu	$2,$2,1
	sh	$2,2452($16)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,3
	bne	$2,$0,$Lnjp_800C5D4C_0
	addu	$4,$16,$0
	sh	$0,2452($16)
$Lnjp_800C5D4C_0:
	addu	$6,$0,$0
	lh	$5,2452($16)
	addiu	$7,$0,1022
	jal	njp_sna_8004E260
	addiu	$5,$5,16
	addu	$4,$16,$0
	jal	njp_800C2BEC
	addiu	$5,$0,1022
$Lnjp_800C5D4C_1:
	lh	$2,184($16)
	nop
	beq	$2,$0,$Lnjp_800C5D4C_2
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	addiu	$2,$0,-1
	sh	$2,2452($16)
$Lnjp_800C5D4C_2:
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x20
	bne	$2,$0,$Lnjp_800C5D4C_3
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C54EC)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C54EC)
	addu	$4,$16,$0
	lui	$5,0x2000
	jal	njp_sna_clear_flags1_8004E308
	ori	$5,$5,0x4
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,2048
	j	$Lnjp_800C5D4C_4
	nop
$Lnjp_800C5D4C_3:
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bgez	$5,$Lnjp_800C5D4C_5
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4A38)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4A38)
$Lnjp_800C5D4C_4:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	jal	njp_800C48F4
	addu	$4,$16,$0
	j	$Lnjp_800C5D4C_6
	nop
$Lnjp_800C5D4C_5:
	jal	njp_sub_8004E4C0
	addu	$4,$16,$0
	sh	$2,110($16)
	addu	$4,$16,$0
	jal	njp_sub_8004EA50
	addu	$5,$2,$0
$Lnjp_800C5D4C_6:
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
	.globl	njp_800C5E9C
njp_800C5E9C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$2,$0,2
	sw	$31,20($29)
	sw	$2,2532($16)
	slti	$2,$5,3
	bne	$2,$0,$Lnjp_800C5E9C_1
	addiu	$2,$0,16
	bne	$5,$2,$Lnjp_800C5E9C_0
	nop
	jal	njp_800C2DB4
	nop
$Lnjp_800C5E9C_0:
	addu	$4,$16,$0
	lui	$5,%hi(njp_data+104)
	jal	njp_800C3898
	addiu	$5,$5,%lo(njp_data+104)
	jal	njp_800C399C
	addu	$4,$16,$0
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5E9C_1
	nop
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,2048
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
$Lnjp_800C5E9C_1:
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
	.globl	njp_800C5F20
njp_800C5F20:
	addiu	$29,$29,-40
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	addu	$17,$5,$0
	addiu	$2,$17,-5
	sltiu	$2,$2,11
	sw	$31,32($29)
	sw	$19,28($29)
	beq	$2,$0,$Lnjp_800C5F20_0
	sw	$18,24($29)
	addiu	$2,$0,2
	sw	$2,2532($16)
$Lnjp_800C5F20_0:
	bne	$17,$0,$Lnjp_800C5F20_1
	slti	$19,$17,10
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4096
	sh	$0,2442($16)
	slti	$19,$17,10
$Lnjp_800C5F20_1:
	beq	$19,$0,$Lnjp_800C5F20_2
	addu	$4,$16,$0
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	jal	njp_800C35BC
	addiu	$6,$0,96
	lbu	$2,117($16)
	sw	$0,1944($16)
	ori	$2,$2,0x8
	sb	$2,117($16)
$Lnjp_800C5F20_2:
	addiu	$18,$0,10
	bne	$17,$18,$Lnjp_800C5F20_3
	slti	$2,$17,3
	addu	$4,$16,$0
	lbu	$2,117($16)
	addiu	$5,$0,4096
	andi	$2,$2,0xf7
	jal	njp_sna_clear_flags1_8004E308
	sb	$2,117($16)
	slti	$2,$17,3
$Lnjp_800C5F20_3:
	bne	$2,$0,$Lnjp_800C5F20_9
	nop
	bne	$17,$18,$Lnjp_800C5F20_4
	nop
	jal	njp_800C2DB4
	addu	$4,$16,$0
$Lnjp_800C5F20_4:
	bne	$19,$0,$Lnjp_800C5F20_5
	nop
	lh	$2,2454($16)
	nop
	bne	$2,$0,$Lnjp_800C5F20_5
	nop
	lbu	$2,119($16)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$Lnjp_800C5F20_5
	nop
	addiu	$4,$16,32
	addiu	$5,$0,210
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,1
	sh	$2,2454($16)
$Lnjp_800C5F20_5:
	addu	$4,$16,$0
	lui	$5,%hi(njp_data+120)
	jal	njp_800C3898
	addiu	$5,$5,%lo(njp_data+120)
	jal	njp_800C399C
	addu	$4,$16,$0
	lh	$2,182($16)
	nop
	bne	$2,$0,$Lnjp_800C5F20_6
	addiu	$2,$0,13
	lh	$3,170($16)
	nop
	bne	$3,$2,$Lnjp_800C5F20_9
	nop
	lh	$2,390($16)
	nop
	slti	$2,$2,16
	bne	$2,$0,$Lnjp_800C5F20_9
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$2,$Lnjp_800C5F20_9
	nop
$Lnjp_800C5F20_6:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,2048
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$2,$Lnjp_800C5F20_7
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4244)
	j	$Lnjp_800C5F20_8
	addiu	$5,$5,%lo(njp_800C4244)
$Lnjp_800C5F20_7:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	addiu	$5,$5,%lo(njp_800C4200)
$Lnjp_800C5F20_8:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C5F20_9:
	lw	$31,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C60E4
njp_800C60E4:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$18,32($29)
	addu	$18,$5,$0
	addiu	$2,$18,-5
	sltiu	$2,$2,15
	sw	$31,36($29)
	beq	$2,$0,$Lnjp_800C60E4_0
	sw	$17,28($29)
	addiu	$2,$0,2
	sw	$2,2532($16)
$Lnjp_800C60E4_0:
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$17,$2,0xf000
	lh	$2,2452($16)
	sltu	$17,$0,$17
	beq	$17,$2,$Lnjp_800C60E4_2
	nop
	beq	$17,$0,$Lnjp_800C60E4_1
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$2,$0,1022
	sw	$2,16($29)
	addiu	$4,$16,156
	addiu	$5,$0,26
	addu	$6,$18,$0
	jal	GM_ConfigObjectOverride
	addiu	$7,$0,4
	j	$Lnjp_800C60E4_2
	nop
$Lnjp_800C60E4_1:
	addiu	$4,$16,156
	addiu	$5,$0,14
	addu	$6,$18,$0
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
$Lnjp_800C60E4_2:
	beq	$17,$0,$Lnjp_800C60E4_3
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	jal	njp_sub_8004E4C0
	addu	$4,$16,$0
	sh	$2,110($16)
$Lnjp_800C60E4_3:
	addu	$4,$16,$0
	lui	$5,%hi(njp_data+136)
	jal	njp_800C3898
	addiu	$5,$5,%lo(njp_data+136)
	jal	njp_800C399C
	addu	$4,$16,$0
	addiu	$2,$0,23
	bne	$18,$2,$Lnjp_800C60E4_6
	sh	$17,2452($16)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,2048
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	beq	$17,$0,$Lnjp_800C60E4_4
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4244)
	j	$Lnjp_800C60E4_5
	addiu	$5,$5,%lo(njp_800C4244)
$Lnjp_800C60E4_4:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	addiu	$5,$5,%lo(njp_800C4200)
$Lnjp_800C60E4_5:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C60E4_6:
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C6244
njp_800C6244:
	addiu	$29,$29,-104
	sw	$19,92($29)
	addu	$19,$4,$0
	sw	$18,88($29)
	addu	$18,$5,$0
	sw	$20,96($29)
	addu	$20,$6,$0
	sw	$17,84($29)
	addu	$17,$7,$0
	addiu	$4,$29,16
	sw	$31,100($29)
	jal	ReadRotMatrix
	sw	$16,80($29)
	addu	$4,$18,$0
	jal	DG_SetPos2
	addiu	$5,$19,40
	addu	$4,$17,$0
	addu	$5,$17,$0
	jal	DG_PutVector
	addiu	$6,$0,1
	jal	SetRotMatrix
	addiu	$4,$29,16
	addiu	$4,$29,48
	addiu	$6,$0,15
	lwl	$8,3($18)
	lwr	$8,0($18)
	lwl	$9,7($18)
	lwr	$9,4($18)
	swl	$8,51($29)
	swr	$8,48($29)
	swl	$9,55($29)
	swr	$9,52($29)
	lwl	$8,3($17)
	lwr	$8,0($17)
	lwl	$9,7($17)
	lwr	$9,4($17)
	swl	$8,59($29)
	swr	$8,56($29)
	swl	$9,63($29)
	swr	$9,60($29)
	lw	$2,76($19)
	addiu	$7,$0,1
	lw	$5,8($2)
	jal	njp_sna_line_check
	addiu	$16,$29,56
	bgez	$2,$Lnjp_800C6244_0
	nop
	lwl	$8,3($17)
	lwr	$8,0($17)
	lwl	$9,7($17)
	lwr	$9,4($17)
	swl	$8,59($29)
	swr	$8,56($29)
	swl	$9,63($29)
	swr	$9,60($29)
$Lnjp_800C6244_0:
	addu	$4,$16,$0
	addu	$5,$18,$0
	addiu	$17,$29,64
	jal	GV_SubVec3
	addu	$6,$17,$0
	jal	GV_VecLen3
	addu	$4,$17,$0
	lh	$3,2436($19)
	nop
	subu	$7,$2,$3
	bgtz	$7,$Lnjp_800C6244_1
	addu	$4,$17,$0
	lwl	$8,3($18)
	lwr	$8,0($18)
	lwl	$9,7($18)
	lwr	$9,4($18)
	swl	$8,67($29)
	swr	$8,64($29)
	swl	$9,71($29)
	swr	$9,68($29)
	j	$Lnjp_800C6244_2
	nop
$Lnjp_800C6244_1:
	addiu	$16,$29,72
	addu	$5,$16,$0
	jal	GV_LenVec3
	addu	$6,$2,$0
	addu	$4,$18,$0
	addu	$5,$16,$0
	jal	GV_AddVec3
	addu	$6,$17,$0
$Lnjp_800C6244_2:
	lwl	$8,67($29)
	lwr	$8,64($29)
	lwl	$9,71($29)
	lwr	$9,68($29)
	swl	$8,3($20)
	swr	$8,0($20)
	swl	$9,7($20)
	swr	$9,4($20)
	lw	$31,100($29)
	lw	$20,96($29)
	lw	$19,92($29)
	lw	$18,88($29)
	lw	$17,84($29)
	lw	$16,80($29)
	jr	$31
	addiu	$29,$29,104
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C63D8
njp_800C63D8:
	addiu	$29,$29,-56
	sw	$17,44($29)
	addu	$17,$4,$0
	sw	$31,48($29)
	sw	$16,40($29)
	lw	$2,2320($17)
	nop
	lhu	$3,0($2)
	lhu	$4,2($2)
	lhu	$5,4($2)
	andi	$3,$3,0xc
	beq	$3,$0,$Lnjp_800C63D8_6
	andi	$2,$4,0x8
	beq	$2,$0,$Lnjp_800C63D8_0
	addiu	$2,$0,8
	sh	$2,2482($17)
$Lnjp_800C63D8_0:
	andi	$2,$4,0x4
	beq	$2,$0,$Lnjp_800C63D8_1
	addiu	$2,$0,4
	sh	$2,2482($17)
$Lnjp_800C63D8_1:
	andi	$2,$5,0x8
	beq	$2,$0,$Lnjp_800C63D8_2
	addiu	$2,$0,4
	sh	$2,2482($17)
$Lnjp_800C63D8_2:
	andi	$2,$5,0x4
	beq	$2,$0,$Lnjp_800C63D8_3
	addiu	$2,$0,8
	sh	$2,2482($17)
$Lnjp_800C63D8_3:
	addu	$4,$17,$0
	addiu	$16,$29,32
	addu	$5,$16,$0
	addiu	$6,$17,2456
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,19($29)
	swr	$8,16($29)
	swl	$9,23($29)
	swr	$9,20($29)
	addiu	$2,$0,1280
	lwl	$8,19($29)
	lwr	$8,16($29)
	lwl	$9,23($29)
	lwr	$9,20($29)
	swl	$8,27($29)
	swr	$8,24($29)
	swl	$9,31($29)
	swr	$9,28($29)
	sh	$2,24($29)
	addiu	$2,$0,-1280
	sh	$2,16($29)
	lwl	$8,2495($17)
	lwr	$8,2492($17)
	lwl	$9,2499($17)
	lwr	$9,2496($17)
	swl	$8,35($29)
	swr	$8,32($29)
	swl	$9,39($29)
	swr	$9,36($29)
	jal	njp_800C6244
	addiu	$7,$29,24
	addu	$4,$17,$0
	addu	$5,$16,$0
	addiu	$6,$17,2464
	jal	njp_800C6244
	addiu	$7,$29,16
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	ori	$5,$0,0x8000
	bne	$2,$0,$Lnjp_800C63D8_4
	addiu	$2,$0,8
	sh	$2,2484($17)
	addu	$4,$17,$0
	jal	njp_sna_set_flags1_8004E2F4
	ori	$5,$0,0x8000
	j	$Lnjp_800C63D8_8
	addiu	$2,$0,1
$Lnjp_800C63D8_4:
	lhu	$3,2482($17)
	nop
	andi	$2,$3,0x4
	beq	$2,$0,$Lnjp_800C63D8_5
	addiu	$2,$0,1
	lwl	$8,2459($17)
	lwr	$8,2456($17)
	lwl	$9,2463($17)
	lwr	$9,2460($17)
	swl	$8,2495($17)
	swr	$8,2492($17)
	swl	$9,2499($17)
	swr	$9,2496($17)
	j	$Lnjp_800C63D8_8
	nop
$Lnjp_800C63D8_5:
	andi	$2,$3,0x8
	beq	$2,$0,$Lnjp_800C63D8_8
	addiu	$2,$0,1
	lwl	$8,2467($17)
	lwr	$8,2464($17)
	lwl	$9,2471($17)
	lwr	$9,2468($17)
	swl	$8,2495($17)
	swr	$8,2492($17)
	swl	$9,2499($17)
	swr	$9,2496($17)
	j	$Lnjp_800C63D8_8
	nop
$Lnjp_800C63D8_6:
	lh	$2,2484($17)
	lhu	$3,2484($17)
	blez	$2,$Lnjp_800C63D8_7
	addiu	$2,$3,-1
	sh	$2,2484($17)
	sll	$2,$2,16
	bne	$2,$0,$Lnjp_800C63D8_8
	addiu	$2,$0,1
	addu	$4,$17,$0
	jal	njp_sna_clear_flags1_8004E308
	ori	$5,$0,0x8000
	j	$Lnjp_800C63D8_8
	addu	$2,$0,$0
$Lnjp_800C63D8_7:
	addu	$2,$0,$0
$Lnjp_800C63D8_8:
	lw	$31,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C65D4
njp_800C65D4:
	addiu	$29,$29,-48
	sw	$20,40($29)
	addu	$20,$4,$0
	sw	$31,44($29)
	sw	$19,36($29)
	sw	$18,32($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$2,2320($20)
	lw	$3,2320($20)
	lhu	$2,0($2)
	nop
	sh	$2,16($29)
	lbu	$2,15($3)
	addiu	$4,$29,16
	jal	GM_CheckShukanReverse
	sb	$2,18($29)
	jal	GM_CheckShukanReverseAnalog
	addiu	$4,$29,18
	addiu	$17,$20,2348
	lh	$19,8($17)
	lh	$2,6($17)
	lh	$3,2348($20)
	subu	$18,$0,$2
	beq	$3,$0,$Lnjp_800C65D4_0
	addu	$16,$0,$0
	lh	$16,108($20)
$Lnjp_800C65D4_0:
	lui	$2,%hi(njp_dword_800ABBDC)
	lh	$3,%lo(njp_dword_800ABBDC)($2)
	nop
	slt	$2,$18,$3
	beq	$2,$0,$Lnjp_800C65D4_1
	lui	$2,%hi(njp_dword_800ABBD4)
	addu	$18,$3,$0
$Lnjp_800C65D4_1:
	lh	$3,%lo(njp_dword_800ABBD4)($2)
	nop
	slt	$2,$3,$19
	beq	$2,$0,$Lnjp_800C65D4_2
	nop
	addu	$19,$3,$0
$Lnjp_800C65D4_2:
	addu	$4,$20,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,16384
	addiu	$6,$0,1
	lhu	$3,16($29)
	addu	$5,$2,$0
	andi	$2,$3,0x1000
	beq	$2,$0,$Lnjp_800C65D4_6
	addu	$4,$6,$0
	andi	$2,$5,0xff
	beq	$2,$0,$Lnjp_800C65D4_3
	addiu	$2,$0,64
	addiu	$6,$0,64
	lbu	$3,18($29)
	nop
	subu	$4,$2,$3
$Lnjp_800C65D4_3:
	lh	$3,10($17)
	andi	$2,$4,0xff
	mult	$3,$2
	mflo	$3
	nop
	nop
	div	$3,$6
	bne	$6,$0,$Lnjp_800C65D4_4
	nop
	.word	0x0007000D
$Lnjp_800C65D4_4:
	addiu	$1,$0,-1
	bne	$6,$1,$Lnjp_800C65D4_5
	lui	$1,0x8000
	bne	$3,$1,$Lnjp_800C65D4_5
	nop
	.word	0x0006000D
$Lnjp_800C65D4_5:
	mflo	$2
	j	$Lnjp_800C65D4_10
	subu	$16,$16,$2
$Lnjp_800C65D4_6:
	andi	$2,$3,0x4000
	beq	$2,$0,$Lnjp_800C65D4_10
	andi	$2,$5,0xff
	beq	$2,$0,$Lnjp_800C65D4_7
	nop
	lbu	$2,18($29)
	addiu	$6,$0,63
	addiu	$4,$2,64
$Lnjp_800C65D4_7:
	lh	$3,12($17)
	andi	$2,$4,0xff
	mult	$3,$2
	mflo	$3
	nop
	nop
	div	$3,$6
	bne	$6,$0,$Lnjp_800C65D4_8
	nop
	.word	0x0007000D
$Lnjp_800C65D4_8:
	addiu	$1,$0,-1
	bne	$6,$1,$Lnjp_800C65D4_9
	lui	$1,0x8000
	bne	$3,$1,$Lnjp_800C65D4_9
	nop
	.word	0x0006000D
$Lnjp_800C65D4_9:
	mflo	$2
	nop
	addu	$16,$16,$2
$Lnjp_800C65D4_10:
	slt	$2,$16,$18
	beq	$2,$0,$Lnjp_800C65D4_11
	slt	$2,$19,$16
	addu	$16,$18,$0
	slt	$2,$19,$16
$Lnjp_800C65D4_11:
	beq	$2,$0,$Lnjp_800C65D4_12
	nop
	addu	$16,$19,$0
$Lnjp_800C65D4_12:
	sh	$16,108($20)
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
	.globl	njp_800C67B0
njp_800C67B0:
	addiu	$29,$29,-40
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$31,32($29)
	sw	$19,28($29)
	sw	$18,24($29)
	sw	$16,16($29)
	lw	$2,2320($17)
	nop
	lhu	$18,0($2)
	nop
	andi	$2,$18,0xa000
	beq	$2,$0,$Lnjp_800C67B0_8
	addiu	$19,$17,2348
	lh	$16,110($17)
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,16384
	addiu	$5,$0,1
	addu	$3,$2,$0
	andi	$2,$18,0x8000
	beq	$2,$0,$Lnjp_800C67B0_3
	addu	$4,$5,$0
	andi	$2,$3,0xff
	beq	$2,$0,$Lnjp_800C67B0_0
	nop
	lw	$2,2320($17)
	addiu	$5,$0,64
	lbu	$3,14($2)
	addiu	$2,$0,64
	subu	$4,$2,$3
$Lnjp_800C67B0_0:
	lh	$3,16($19)
	andi	$2,$4,0xff
	mult	$3,$2
	mflo	$3
	nop
	nop
	div	$3,$5
	bne	$5,$0,$Lnjp_800C67B0_1
	nop
	.word	0x0007000D
$Lnjp_800C67B0_1:
	addiu	$1,$0,-1
	bne	$5,$1,$Lnjp_800C67B0_2
	lui	$1,0x8000
	bne	$3,$1,$Lnjp_800C67B0_2
	nop
	.word	0x0006000D
$Lnjp_800C67B0_2:
	mflo	$2
	j	$Lnjp_800C67B0_7
	addu	$16,$16,$2
$Lnjp_800C67B0_3:
	andi	$2,$3,0xff
	beq	$2,$0,$Lnjp_800C67B0_4
	nop
	lw	$2,2320($17)
	nop
	lbu	$2,14($2)
	addiu	$5,$0,63
	addiu	$4,$2,64
$Lnjp_800C67B0_4:
	lh	$3,14($19)
	andi	$2,$4,0xff
	mult	$3,$2
	mflo	$3
	nop
	nop
	div	$3,$5
	bne	$5,$0,$Lnjp_800C67B0_5
	nop
	.word	0x0007000D
$Lnjp_800C67B0_5:
	addiu	$1,$0,-1
	bne	$5,$1,$Lnjp_800C67B0_6
	lui	$1,0x8000
	bne	$3,$1,$Lnjp_800C67B0_6
	nop
	.word	0x0006000D
$Lnjp_800C67B0_6:
	mflo	$2
	nop
	subu	$16,$16,$2
$Lnjp_800C67B0_7:
	sh	$16,110($17)
$Lnjp_800C67B0_8:
	lw	$31,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C6900
njp_800C6900:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addiu	$5,$0,2
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x10
	bne	$2,$0,$Lnjp_800C6900_0
	nop
	jal	njp_800C29E4
	addu	$4,$16,$0
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	j	$Lnjp_800C6900_1
	nop
$Lnjp_800C6900_0:
	jal	njp_800C63D8
	addu	$4,$16,$0
	bne	$2,$0,$Lnjp_800C6900_1
	nop
	jal	njp_800C65D4
	addu	$4,$16,$0
	jal	njp_800C67B0
	addu	$4,$16,$0
$Lnjp_800C6900_1:
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
	.globl	njp_800C6994
njp_800C6994:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,28($29)
	sw	$18,24($29)
	sw	$17,20($29)
	lw	$2,2320($16)
	nop
	lhu	$17,0($2)
	lhu	$18,2($2)
	andi	$3,$17,0x10
	bne	$3,$0,$Lnjp_800C6994_0
	nop
	jal	njp_800C29E4
	nop
	addiu	$2,$0,2
	j	$Lnjp_800C6994_4
	sh	$2,2452($16)
$Lnjp_800C6994_0:
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,16
	beq	$2,$0,$Lnjp_800C6994_1
	andi	$2,$18,0xf000
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addiu	$5,$0,21
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	andi	$2,$18,0xf000
$Lnjp_800C6994_1:
	bne	$2,$0,$Lnjp_800C6994_2
	andi	$2,$17,0xf000
	bne	$2,$0,$Lnjp_800C6994_3
	nop
$Lnjp_800C6994_2:
	jal	njp_GM_ClearPlayerStatusFlag
	lui	$4,0x1
	addiu	$2,$0,450
	sh	$2,2436($16)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	jal	GM_ExitBehindCamera
	nop
$Lnjp_800C6994_3:
	jal	njp_800C63D8
	addu	$4,$16,$0
$Lnjp_800C6994_4:
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
	.globl	njp_800C6A60
njp_800C6A60:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x10
	bne	$2,$0,$Lnjp_800C6A60_0
	lui	$3,%hi(GM_SnakeCamera)
	jal	njp_800C29E4
	nop
	lui	$3,%hi(GM_SnakeCamera)
$Lnjp_800C6A60_0:
	addiu	$3,$3,%lo(GM_SnakeCamera)
	lhu	$2,2($3)
	addu	$4,$16,$0
	addiu	$2,$2,320
	jal	njp_800C2B14
	sh	$2,2($3)
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
	.globl	njp_800C6AC0
njp_800C6AC0:
	addiu	$29,$29,-40
	sw	$19,28($29)
	addu	$19,$4,$0
	sw	$20,32($29)
	addu	$20,$5,$0
	sw	$31,36($29)
	sw	$18,24($29)
	sw	$17,20($29)
	bne	$20,$0,$Lnjp_800C6AC0_6
	sw	$16,16($29)
	addiu	$4,$0,16
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$0,2304($19)
	sw	$2,2340($19)
	jal	njp_GM_ClearPlayerStatusFlag
	sw	$2,2344($19)
	addu	$16,$0,$0
	addu	$4,$19,$0
	lui	$5,%hi(njp_data+152)
	addiu	$5,$5,%lo(njp_data+152)
	jal	njp_800C3738
	sh	$0,2480($19)
	bne	$2,$0,$Lnjp_800C6AC0_0
	nop
	addiu	$16,$0,1
	sh	$16,2452($19)
$Lnjp_800C6AC0_0:
	bne	$16,$0,$Lnjp_800C6AC0_4
	addiu	$18,$19,2280
	addiu	$17,$19,40
	lw	$3,2276($19)
	addu	$5,$17,$0
	lhu	$2,42($3)
	addiu	$4,$3,8
	addiu	$2,$2,-1
	jal	DG_SetPos2
	sh	$2,42($3)
	lui	$4,%hi(njp_data+184)
	addiu	$4,$4,%lo(njp_data+184)
	addu	$5,$18,$0
	jal	DG_PutVector
	addiu	$6,$0,1
	addiu	$16,$19,32
	addu	$4,$16,$0
	jal	DG_SetPos2
	addu	$5,$17,$0
	addu	$4,$18,$0
	addu	$5,$16,$0
	jal	GV_SubVec3
	addu	$6,$18,$0
	lh	$2,2280($19)
	nop
	bgez	$2,$Lnjp_800C6AC0_1
	nop
	addiu	$2,$2,3
$Lnjp_800C6AC0_1:
	sra	$2,$2,2
	sh	$2,2280($19)
	lh	$2,2($18)
	nop
	bgez	$2,$Lnjp_800C6AC0_2
	nop
	addiu	$2,$2,3
$Lnjp_800C6AC0_2:
	lh	$3,4($18)
	sra	$2,$2,2
	bgez	$3,$Lnjp_800C6AC0_3
	sh	$2,2($18)
	addiu	$3,$3,3
$Lnjp_800C6AC0_3:
	sra	$2,$3,2
	sh	$2,4($18)
	j	$Lnjp_800C6AC0_5
	addiu	$5,$0,25
$Lnjp_800C6AC0_4:
	lui	$2,%hi(DG_ZeroVector)
	addiu	$10,$2,%lo(DG_ZeroVector)
	lwl	$7,3($10)
	lwr	$7,0($10)
	lwl	$8,7($10)
	lwr	$8,4($10)
	swl	$7,2283($19)
	swr	$7,2280($19)
	swl	$8,2287($19)
	swr	$8,2284($19)
	addiu	$5,$0,3
$Lnjp_800C6AC0_5:
	addu	$4,$19,$0
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
$Lnjp_800C6AC0_6:
	slti	$2,$20,4
	beq	$2,$0,$Lnjp_800C6AC0_7
	addiu	$4,$19,100
	addiu	$5,$19,2280
	lw	$2,2304($19)
	addu	$6,$4,$0
	addiu	$2,$2,1
	jal	GV_AddVec3
	sw	$2,2304($19)
	j	$Lnjp_800C6AC0_10
	nop
$Lnjp_800C6AC0_7:
	lh	$2,2452($19)
	nop
	beq	$2,$0,$Lnjp_800C6AC0_8
	addu	$4,$19,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
	addu	$4,$19,$0
	lui	$5,%hi(njp_800C4200)
	j	$Lnjp_800C6AC0_9
	addiu	$5,$5,%lo(njp_800C4200)
$Lnjp_800C6AC0_8:
	lui	$5,%hi(njp_800C6CA4)
	addiu	$5,$5,%lo(njp_800C6CA4)
	lw	$3,2200($4)
	addiu	$2,$0,150
	sh	$2,16($3)
$Lnjp_800C6AC0_9:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C6AC0_10:
	lw	$31,36($29)
	lw	$20,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C6CA4
njp_800C6CA4:
	addiu	$29,$29,-64
	sw	$17,52($29)
	addu	$17,$4,$0
	addiu	$2,$5,-19
	sltiu	$2,$2,3
	sw	$31,56($29)
	beq	$2,$0,$Lnjp_800C6CA4_0
	sw	$16,48($29)
	addiu	$2,$0,2
	sw	$2,2532($17)
$Lnjp_800C6CA4_0:
	lw	$16,2276($17)
	bne	$5,$0,$Lnjp_800C6CA4_1
	lui	$2,%hi(dword_800AB9D4)
	addu	$4,$17,$0
	addiu	$5,$0,25
	addiu	$6,$0,4
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	sw	$2,2340($17)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($17)
	addiu	$2,$0,25
	sh	$2,62($16)
	sh	$0,2480($17)
	lui	$2,%hi(dword_800AB9D4)
$Lnjp_800C6CA4_1:
	lw	$3,%lo(dword_800AB9D4)($2)
	addiu	$2,$0,22
	bne	$3,$2,$Lnjp_800C6CA4_2
	addiu	$4,$16,8
	addiu	$5,$17,40
	lhu	$2,42($16)
	addiu	$3,$0,5
	sh	$3,40($16)
	addiu	$2,$2,-1
	jal	DG_SetPos2
	sh	$2,42($16)
	jal	ReadRotMatrix
	addiu	$4,$29,16
	addiu	$4,$29,16
	jal	NewBlood
	addiu	$5,$0,2
	lui	$4,%hi(njp_data+28)
	addiu	$4,$4,%lo(njp_data+28)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_data+36)
	addiu	$4,$4,%lo(njp_data+36)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$17,32
	addiu	$5,$0,212
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C6CA4_2:
	lh	$2,182($17)
	nop
	beq	$2,$0,$Lnjp_800C6CA4_3
	addu	$4,$17,$0
	jal	njp_sna_sub_8004E41C
	addiu	$5,$0,2
	addu	$4,$17,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	addu	$4,$17,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
$Lnjp_800C6CA4_3:
	lw	$31,56($29)
	lw	$17,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C6DC0
njp_800C6DC0:
	addiu	$29,$29,-104
	sw	$18,72($29)
	addu	$18,$4,$0
	sw	$31,100($29)
	sw	$30,96($29)
	sw	$23,92($29)
	sw	$22,88($29)
	sw	$21,84($29)
	sw	$20,80($29)
	sw	$19,76($29)
	sw	$17,68($29)
	sw	$16,64($29)
	lh	$3,180($18)
	lh	$2,82($18)
	sw	$0,2532($18)
	sw	$2,1944($18)
	slti	$2,$3,500
	beq	$2,$0,$Lnjp_800C6DC0_0
	sh	$3,82($18)
	addiu	$3,$0,500
$Lnjp_800C6DC0_0:
	slti	$2,$3,701
	bne	$2,$0,$Lnjp_800C6DC0_1
	addu	$4,$18,$0
	addiu	$3,$0,700
$Lnjp_800C6DC0_1:
	lw	$2,2200($18)
	addiu	$5,$0,4096
	jal	njp_sna_check_flags1_8004E31C
	sh	$3,18($2)
	bne	$2,$0,$Lnjp_800C6DC0_3
	nop
	lh	$2,2442($18)
	nop
	bgez	$2,$Lnjp_800C6DC0_2
	nop
	lb	$2,119($18)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_2
	nop
	sh	$0,2442($18)
$Lnjp_800C6DC0_2:
	lhu	$2,2442($18)
	nop
	addiu	$2,$2,-32
	sh	$2,2442($18)
$Lnjp_800C6DC0_3:
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,128
	bne	$2,$0,$Lnjp_800C6DC0_73
	nop
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x2000
	beq	$2,$0,$Lnjp_800C6DC0_4
	lui	$2,%hi(njp_data+192)
	addiu	$2,$2,%lo(njp_data+192)
	sw	$2,2320($18)
$Lnjp_800C6DC0_4:
	addu	$4,$18,$0
	addiu	$5,$0,16384
	jal	njp_sna_clear_flags1_8004E308
	sh	$0,112($18)
	lw	$3,2320($18)
	nop
	lh	$2,10($3)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_7
	lui	$4,0x1
	lhu	$2,0($3)
	nop
	andi	$2,$2,0xf000
	beq	$2,$0,$Lnjp_800C6DC0_6
	addiu	$4,$3,14
	addu	$3,$0,$0
$Lnjp_800C6DC0_5:
	lbu	$2,0($4)
	nop
	addiu	$2,$2,-64
	andi	$2,$2,0xff
	sltiu	$2,$2,129
	beq	$2,$0,$Lnjp_800C6DC0_8
	addiu	$3,$3,1
	slti	$2,$3,2
	bne	$2,$0,$Lnjp_800C6DC0_5
	addiu	$4,$4,1
$Lnjp_800C6DC0_6:
	lui	$4,0x1
$Lnjp_800C6DC0_7:
	lui	$2,%hi(njp_bss_16)
	lui	$3,%hi(njp_dword_800ABBA8)
	sw	$0,%lo(njp_bss_16)($2)
	addiu	$2,$0,-1
	sw	$2,%lo(njp_dword_800ABBA8)($3)
	lui	$2,%hi(njp_bss_44)
	sw	$0,%lo(njp_bss_44)($2)
	lui	$2,%hi(njp_bss_60)
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$16,$2,%lo(njp_bss_60)
	beq	$2,$0,$Lnjp_800C6DC0_9
	lui	$2,%hi(njp_bss_20)
	lw	$2,%lo(njp_bss_20)($2)
	j	$Lnjp_800C6DC0_10
	lui	$22,%hi(njp_bss_52)
$Lnjp_800C6DC0_8:
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,16384
	j	$Lnjp_800C6DC0_7
	lui	$4,0x1
$Lnjp_800C6DC0_9:
	addu	$2,$0,$0
	lui	$22,%hi(njp_bss_52)
$Lnjp_800C6DC0_10:
	lui	$30,%hi(njp_bss_20)
	sw	$2,0($16)
	addiu	$2,$0,-1
	lw	$4,%lo(njp_bss_52)($22)
	lw	$3,2320($18)
	lui	$15,%hi(njp_bss_56)
	sw	$2,%lo(njp_bss_56)($15)
	lh	$3,8($3)
	lui	$2,%hi(njp_bss_48)
	sw	$0,%lo(njp_bss_20)($30)
	sw	$0,%lo(njp_bss_52)($22)
	sw	$4,%lo(njp_bss_48)($2)
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	sw	$3,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	lb	$16,120($18)
	sw	$0,1948($18)
	blez	$16,$Lnjp_800C6DC0_31
	sw	$3,56($29)
	addiu	$4,$18,128
	lui	$21,%hi(njp_bss_16)
	lui	$19,%hi(njp_dword_800ABBB4)
	addiu	$2,$18,122
	sw	$4,%lo(njp_bss_16)($21)
	jal	GV_VecDir2
	sw	$2,%lo(njp_dword_800ABBB4)($19)
	addu	$4,$2,$0
	lw	$2,%lo(njp_dword_800ABBB4)($19)
	lui	$20,%hi(njp_dword_800ABBA8)
	sw	$4,%lo(njp_dword_800ABBA8)($20)
	lbu	$2,0($2)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lnjp_800C6DC0_11
	nop
	lw	$2,%lo(njp_bss_16)($21)
	lw	$3,144($18)
	lui	$23,%hi(njp_bss_56)
	sw	$4,%lo(njp_bss_56)($23)
	sw	$2,%lo(njp_bss_52)($22)
	sw	$3,%lo(njp_bss_20)($30)
$Lnjp_800C6DC0_11:
	lw	$24,56($29)
	nop
	bltz	$24,$Lnjp_800C6DC0_31
	addiu	$2,$0,1
	beq	$16,$2,$Lnjp_800C6DC0_12
	addiu	$17,$18,136
	jal	GV_VecDir2
	addu	$4,$17,$0
	lw	$4,56($29)
	lw	$5,%lo(njp_dword_800ABBA8)($20)
	jal	GV_DiffDirAbs
	addu	$16,$2,$0
	addu	$5,$16,$0
	lw	$4,56($29)
	jal	GV_DiffDirAbs
	addu	$16,$2,$0
	slt	$2,$2,$16
	beq	$2,$0,$Lnjp_800C6DC0_12
	addu	$4,$17,$0
	addiu	$2,$18,123
	sw	$4,%lo(njp_bss_16)($21)
	jal	GV_VecDir2
	sw	$2,%lo(njp_dword_800ABBB4)($19)
	lw	$3,%lo(njp_dword_800ABBB4)($19)
	addu	$4,$2,$0
	sw	$4,%lo(njp_dword_800ABBA8)($20)
	lbu	$2,0($3)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lnjp_800C6DC0_13
	addiu	$10,$0,-1
	lw	$2,%lo(njp_bss_16)($21)
	lw	$3,148($18)
	lui	$25,%hi(njp_bss_56)
	sw	$4,%lo(njp_bss_56)($25)
	sw	$2,%lo(njp_bss_52)($22)
	sw	$3,%lo(njp_bss_20)($30)
$Lnjp_800C6DC0_12:
	addiu	$10,$0,-1
$Lnjp_800C6DC0_13:
	addiu	$17,$18,32
	lb	$3,88($17)
	addiu	$2,$0,1
	bne	$3,$2,$Lnjp_800C6DC0_17
	addu	$16,$17,$0
	lbu	$2,90($17)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lnjp_800C6DC0_26
	nop
	lw	$6,112($17)
	lhu	$3,32($18)
	lhu	$2,0($6)
	nop
	subu	$3,$3,$2
	sh	$3,48($29)
	lhu	$4,4($17)
	lhu	$2,2($6)
	sll	$3,$3,16
	subu	$4,$4,$2
	sh	$4,50($29)
	lhu	$5,8($6)
	lhu	$2,0($6)
	sra	$3,$3,16
	subu	$5,$5,$2
	sll	$2,$5,16
	sra	$7,$2,16
	mult	$7,$3
	sll	$4,$4,16
	sh	$5,40($29)
	lhu	$3,10($6)
	lhu	$2,2($6)
	sra	$4,$4,16
	subu	$3,$3,$2
	mflo	$8
	sll	$2,$3,16
	sra	$5,$2,16
	mult	$5,$4
	sh	$3,42($29)
	mflo	$9
	addu	$2,$8,$9
	bgez	$2,$Lnjp_800C6DC0_14
	addu	$3,$2,$0
	j	$Lnjp_800C6DC0_15
	addiu	$2,$0,1
$Lnjp_800C6DC0_14:
	mult	$7,$7
	mflo	$2
	nop
	nop
	mult	$5,$5
	mflo	$8
	addu	$2,$2,$8
	slt	$2,$2,$3
$Lnjp_800C6DC0_15:
	bne	$2,$0,$Lnjp_800C6DC0_27
	addu	$16,$10,$0
	addu	$10,$0,$0
	addiu	$2,$0,1
$Lnjp_800C6DC0_16:
	j	$Lnjp_800C6DC0_26
	sw	$2,1948($18)
$Lnjp_800C6DC0_17:
	addiu	$13,$18,122
	addu	$14,$0,$0
	addu	$9,$14,$0
	addiu	$12,$29,32
	addu	$11,$17,$0
$Lnjp_800C6DC0_18:
	lw	$6,112($11)
	nop
	sw	$6,0($12)
	lbu	$2,0($13)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lnjp_800C6DC0_21
	nop
	lhu	$3,0($16)
	lhu	$2,0($6)
	nop
	subu	$3,$3,$2
	sh	$3,48($29)
	lhu	$5,4($16)
	lhu	$2,2($6)
	sll	$3,$3,16
	subu	$5,$5,$2
	sh	$5,50($29)
	lhu	$4,8($6)
	lhu	$2,0($6)
	sra	$3,$3,16
	subu	$4,$4,$2
	sll	$2,$4,16
	sra	$7,$2,16
	mult	$7,$3
	sll	$5,$5,16
	sh	$4,40($29)
	lhu	$3,10($6)
	lhu	$2,2($6)
	sra	$5,$5,16
	subu	$3,$3,$2
	mflo	$8
	sll	$2,$3,16
	sra	$4,$2,16
	mult	$4,$5
	sh	$3,42($29)
	mflo	$19
	addu	$2,$8,$19
	bgez	$2,$Lnjp_800C6DC0_19
	addu	$3,$2,$0
	j	$Lnjp_800C6DC0_20
	addiu	$2,$0,1
$Lnjp_800C6DC0_19:
	mult	$7,$7
	mflo	$2
	nop
	nop
	mult	$4,$4
	mflo	$8
	addu	$2,$2,$8
	slt	$2,$2,$3
$Lnjp_800C6DC0_20:
	bne	$2,$0,$Lnjp_800C6DC0_21
	addiu	$2,$0,1
	addu	$10,$9,$0
	addiu	$14,$14,1
	sw	$2,1948($18)
$Lnjp_800C6DC0_21:
	addiu	$12,$12,4
	addiu	$11,$11,4
	addiu	$9,$9,1
	slti	$2,$9,2
	bne	$2,$0,$Lnjp_800C6DC0_18
	addiu	$13,$13,1
	slti	$2,$14,2
	bne	$2,$0,$Lnjp_800C6DC0_26
	addiu	$16,$17,96
	jal	GV_VecLen3
	addu	$4,$16,$0
	addiu	$17,$17,104
	addu	$4,$17,$0
	jal	GV_VecLen3
	addu	$20,$2,$0
	addu	$4,$16,$0
	jal	GV_VecDir2
	addu	$19,$2,$0
	addu	$4,$17,$0
	jal	GV_VecDir2
	addu	$16,$2,$0
	addu	$4,$16,$0
	jal	GV_DiffDirAbs
	addu	$5,$2,$0
	slti	$2,$2,512
	beq	$2,$0,$Lnjp_800C6DC0_22
	addiu	$2,$0,1
	sw	$2,1948($18)
	slt	$2,$20,$19
	j	$Lnjp_800C6DC0_27
	xori	$16,$2,0x1
$Lnjp_800C6DC0_22:
	lui	$2,%hi(njp_bss_60)
	lw	$3,%lo(njp_bss_60)($2)
	lw	$2,32($29)
	nop
	bne	$3,$2,$Lnjp_800C6DC0_23
	addiu	$10,$0,2
	j	$Lnjp_800C6DC0_24
	addu	$10,$0,$0
$Lnjp_800C6DC0_23:
	lw	$2,36($29)
	nop
	bne	$3,$2,$Lnjp_800C6DC0_25
	addiu	$2,$0,2
	addiu	$10,$0,1
$Lnjp_800C6DC0_24:
	addiu	$2,$0,2
$Lnjp_800C6DC0_25:
	bne	$10,$2,$Lnjp_800C6DC0_16
	addiu	$2,$0,1
	sw	$10,1948($18)
$Lnjp_800C6DC0_26:
	addu	$16,$10,$0
$Lnjp_800C6DC0_27:
	addiu	$2,$0,-1
	bne	$16,$2,$Lnjp_800C6DC0_28
	addiu	$17,$0,2
	lui	$2,%hi(njp_bss_52)
	sw	$0,%lo(njp_bss_52)($2)
	lui	$2,%hi(njp_bss_56)
	j	$Lnjp_800C6DC0_31
	sw	$16,%lo(njp_bss_56)($2)
$Lnjp_800C6DC0_28:
	beq	$16,$17,$Lnjp_800C6DC0_29
	sll	$4,$16,3
	addiu	$4,$4,128
	addu	$4,$18,$4
	lui	$2,%hi(njp_bss_52)
	jal	GV_VecDir2
	sw	$4,%lo(njp_bss_52)($2)
	lui	$3,%hi(njp_bss_56)
	sw	$2,%lo(njp_bss_56)($3)
	sllv	$2,$16,$17
	addu	$2,$18,$2
	lw	$3,144($2)
	lui	$2,%hi(njp_bss_20)
	sw	$3,%lo(njp_bss_20)($2)
$Lnjp_800C6DC0_29:
	lui	$2,%hi(njp_bss_56)
	lw	$5,%lo(njp_bss_56)($2)
	lw	$4,56($29)
	jal	GV_DiffDirS
	nop
	addu	$3,$2,$0
	addiu	$2,$3,896
	sltiu	$2,$2,1793
	beq	$2,$0,$Lnjp_800C6DC0_31
	lui	$4,%hi(njp_bss_44)
	addiu	$2,$0,1
	bltz	$3,$Lnjp_800C6DC0_30
	sw	$2,%lo(njp_bss_44)($4)
	slti	$2,$3,257
	bne	$2,$0,$Lnjp_800C6DC0_31
	addiu	$2,$0,4
	j	$Lnjp_800C6DC0_31
	sw	$2,%lo(njp_bss_44)($4)
$Lnjp_800C6DC0_30:
	slti	$2,$3,-256
	beq	$2,$0,$Lnjp_800C6DC0_31
	nop
	sw	$17,%lo(njp_bss_44)($4)
$Lnjp_800C6DC0_31:
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x20
	beq	$2,$0,$Lnjp_800C6DC0_42
	nop
	lh	$2,2380($18)
	lh	$17,2376($18)
	beq	$2,$0,$Lnjp_800C6DC0_38
	addiu	$2,$0,450
	sh	$2,88($18)
	sh	$2,86($18)
	sh	$2,2436($18)
	andi	$2,$17,0x4002
	bne	$2,$0,$Lnjp_800C6DC0_32
	andi	$2,$17,0x100
	addiu	$4,$18,32
	addiu	$5,$18,2120
	lh	$3,2378($18)
	lh	$6,152($18)
	lhu	$2,180($18)
	subu	$3,$6,$3
	subu	$2,$2,$3
	sh	$2,82($18)
	addu	$2,$2,$6
	sh	$2,34($18)
	sll	$2,$2,16
	lw	$3,156($18)
	sra	$2,$2,16
	jal	DG_GetLightMatrix2
	sw	$2,24($3)
	j	$Lnjp_800C6DC0_33
	nop
$Lnjp_800C6DC0_32:
	bne	$2,$0,$Lnjp_800C6DC0_33
	addiu	$2,$0,1100
	sh	$2,82($18)
$Lnjp_800C6DC0_33:
	lhu	$2,82($18)
	lh	$16,2372($18)
	nop
	bltz	$16,$Lnjp_800C6DC0_35
	sh	$2,180($18)
	lh	$5,42($18)
	jal	GV_DiffDirAbs
	addu	$4,$16,$0
	slti	$2,$2,1537
	bne	$2,$0,$Lnjp_800C6DC0_34
	nop
	sh	$16,42($18)
$Lnjp_800C6DC0_34:
	sh	$16,110($18)
$Lnjp_800C6DC0_35:
	andi	$2,$17,0x80
	bne	$2,$0,$Lnjp_800C6DC0_36
	andi	$2,$17,0x800
	addiu	$4,$18,156
	addiu	$5,$18,384
	addiu	$6,$0,5887
	addiu	$2,$18,1076
	sw	$2,16($29)
	addiu	$2,$18,32
	sw	$2,20($29)
	addiu	$2,$18,1688
	addiu	$7,$18,464
	jal	GM_ConfigMotionControl
	sw	$2,24($29)
	addiu	$2,$0,-1
	sh	$2,170($18)
	andi	$2,$17,0x800
$Lnjp_800C6DC0_36:
	beq	$2,$0,$Lnjp_800C6DC0_37
	nop
	lh	$5,2434($18)
	jal	njp_sub_8004E5E8
	addu	$4,$18,$0
	addu	$4,$18,$0
	addu	$5,$2,$0
	jal	njp_SetAction_8004E22C
	addu	$6,$0,$0
$Lnjp_800C6DC0_37:
	sh	$0,2380($18)
$Lnjp_800C6DC0_38:
	lw	$3,1952($18)
	nop
	blez	$3,$Lnjp_800C6DC0_40
	addiu	$4,$18,1956
	ori	$7,$0,0x937a
	addiu	$6,$0,28923
	ori	$5,$0,0xbe0a
$Lnjp_800C6DC0_39:
	lhu	$2,4($4)
	nop
	beq	$2,$7,$Lnjp_800C6DC0_41
	nop
	beq	$2,$6,$Lnjp_800C6DC0_41
	nop
	beq	$2,$5,$Lnjp_800C6DC0_41
	addiu	$3,$3,-1
	bgtz	$3,$Lnjp_800C6DC0_39
	addiu	$4,$4,20
$Lnjp_800C6DC0_40:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,4
$Lnjp_800C6DC0_41:
	addu	$4,$18,$0
	jal	njp_sna_clear_flags1_8004E308
	lui	$5,0x820
$Lnjp_800C6DC0_42:
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x80
	beq	$2,$0,$Lnjp_800C6DC0_51
	nop
	lbu	$16,2432($18)
	nop
	beq	$16,$0,$Lnjp_800C6DC0_48
	addiu	$16,$16,-1
	blez	$16,$Lnjp_800C6DC0_46
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,1
	bne	$2,$0,$Lnjp_800C6DC0_43
	addu	$2,$0,$0
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,1
	bne	$2,$0,$Lnjp_800C6DC0_43
	addu	$2,$0,$0
	addiu	$2,$0,1
$Lnjp_800C6DC0_43:
	beq	$2,$0,$Lnjp_800C6DC0_45
	andi	$2,$16,0x3
	beq	$2,$0,$Lnjp_800C6DC0_44
	addiu	$4,$0,-129
	lw	$2,156($18)
	nop
	lw	$3,40($2)
	nop
	and	$3,$3,$4
	j	$Lnjp_800C6DC0_45
	sw	$3,40($2)
$Lnjp_800C6DC0_44:
	lw	$3,156($18)
	nop
	lw	$2,40($3)
	nop
	ori	$2,$2,0x80
	sw	$2,40($3)
$Lnjp_800C6DC0_45:
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_47
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,2
	beq	$2,$0,$Lnjp_800C6DC0_47
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,1
	bne	$2,$0,$Lnjp_800C6DC0_47
	nop
	jal	GV_RandS
	addiu	$4,$0,16
	mult	$2,$16
	lui	$3,%hi(GM_SnakeCamera)
	addiu	$3,$3,%lo(GM_SnakeCamera)
	lhu	$2,2($3)
	mflo	$15
	addu	$2,$2,$15
	j	$Lnjp_800C6DC0_47
	sh	$2,2($3)
$Lnjp_800C6DC0_46:
	jal	njp_800C2DB4
	addu	$4,$18,$0
$Lnjp_800C6DC0_47:
	j	$Lnjp_800C6DC0_64
	sb	$16,2432($18)
$Lnjp_800C6DC0_48:
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x400
	beq	$2,$0,$Lnjp_800C6DC0_49
	addiu	$4,$0,-129
	lw	$2,156($18)
	nop
	lw	$3,40($2)
	nop
	and	$3,$3,$4
	sw	$3,40($2)
$Lnjp_800C6DC0_49:
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_50
	addiu	$4,$0,-129
	lw	$3,156($18)
	nop
	lw	$2,40($3)
	nop
	ori	$2,$2,0x80
	j	$Lnjp_800C6DC0_64
	sw	$2,40($3)
$Lnjp_800C6DC0_50:
	lw	$2,156($18)
	nop
	lw	$3,40($2)
	nop
	and	$3,$3,$4
	j	$Lnjp_800C6DC0_64
	sw	$3,40($2)
$Lnjp_800C6DC0_51:
	lw	$16,2200($18)
	nop
	lhu	$3,6($16)
	nop
	andi	$2,$3,0x6
	beq	$2,$0,$Lnjp_800C6DC0_63
	addiu	$2,$0,1
	lh	$17,62($16)
	nop
	beq	$17,$2,$Lnjp_800C6DC0_52
	addiu	$2,$0,3
	beq	$17,$2,$Lnjp_800C6DC0_52
	addiu	$2,$0,8
	bne	$17,$2,$Lnjp_800C6DC0_53
	addiu	$19,$0,1
$Lnjp_800C6DC0_52:
	addu	$19,$0,$0
$Lnjp_800C6DC0_53:
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,2
	bne	$2,$0,$Lnjp_800C6DC0_57
	lui	$4,0x21
	lbu	$2,117($18)
	ori	$4,$4,0x20
	andi	$2,$2,0xfd
	jal	njp_GM_ClearPlayerStatusFlag
	sb	$2,117($18)
	addu	$4,$18,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,48
	addu	$4,$18,$0
	addiu	$2,$0,450
	jal	njp_800C2EF0
	sh	$2,2436($18)
	lui	$4,0x40
	jal	njp_GM_SetPlayerStatusFlag
	ori	$4,$4,0x100
	bne	$19,$0,$Lnjp_800C6DC0_54
	addu	$4,$18,$0
	lui	$5,%hi(njp_800C5634)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C5634)
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,24
	lui	$4,%hi(njp_data)
	addiu	$4,$4,%lo(njp_data)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_data+4)
	addiu	$4,$4,%lo(njp_data+4)
	jal	NewPadVibration
	addiu	$5,$0,2
	j	$Lnjp_800C6DC0_56
	addu	$4,$18,$0
$Lnjp_800C6DC0_54:
	lwl	$23,47($16)
	lwr	$23,44($16)
	lwl	$24,51($16)
	lwr	$24,48($16)
	swl	$23,2443($18)
	swr	$23,2440($18)
	swl	$24,2447($18)
	swr	$24,2444($18)
	lhu	$3,2440($18)
	lh	$6,2442($18)
	sll	$3,$3,16
	sra	$2,$3,16
	srl	$3,$3,31
	addu	$2,$2,$3
	sra	$2,$2,1
	bgez	$6,$Lnjp_800C6DC0_55
	sh	$2,2440($18)
	addiu	$6,$6,3
$Lnjp_800C6DC0_55:
	addu	$4,$18,$0
	lui	$5,%hi(njp_800C573C)
	addiu	$5,$5,%lo(njp_800C573C)
	lhu	$3,2444($18)
	sra	$2,$6,2
	sh	$2,2442($18)
	sll	$3,$3,16
	sra	$2,$3,16
	srl	$3,$3,31
	addu	$2,$2,$3
	sra	$2,$2,1
	jal	njp_sna_start_anim_8004E1F4
	sh	$2,2444($18)
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,25
	lui	$4,%hi(njp_data+12)
	addiu	$4,$4,%lo(njp_data+12)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_data+16)
	addiu	$4,$4,%lo(njp_data+16)
	jal	NewPadVibration
	addiu	$5,$0,2
	jal	njp_800C29E4
	addu	$4,$18,$0
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	addu	$4,$18,$0
$Lnjp_800C6DC0_56:
	jal	njp_800C2C48
	addu	$5,$17,$0
	j	$Lnjp_800C6DC0_62
	nop
$Lnjp_800C6DC0_57:
	addu	$4,$18,$0
	jal	njp_800C2D68
	addiu	$5,$0,32
	lh	$2,40($16)
	nop
	blez	$2,$Lnjp_800C6DC0_58
	addiu	$2,$0,1
	lh	$5,62($16)
	jal	njp_800C2C48
	addu	$4,$18,$0
	addiu	$2,$0,1
$Lnjp_800C6DC0_58:
	beq	$17,$2,$Lnjp_800C6DC0_59
	addiu	$2,$0,3
	bne	$17,$2,$Lnjp_800C6DC0_60
	addiu	$5,$0,63
$Lnjp_800C6DC0_59:
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,24
	lui	$4,%hi(njp_data)
	addiu	$4,$4,%lo(njp_data)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_data+4)
	j	$Lnjp_800C6DC0_61
	addiu	$4,$4,%lo(njp_data+4)
$Lnjp_800C6DC0_60:
	addu	$4,$0,$0
	jal	GM_SeSet2
	addiu	$6,$0,25
	lui	$4,%hi(njp_data+12)
	addiu	$4,$4,%lo(njp_data+12)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_data+16)
	addiu	$4,$4,%lo(njp_data+16)
$Lnjp_800C6DC0_61:
	jal	NewPadVibration
	addiu	$5,$0,2
	lh	$2,38($16)
	nop
	bgtz	$2,$Lnjp_800C6DC0_62
	lui	$2,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($2)
	nop
	addiu	$2,$2,1
	sltiu	$2,$2,2
	beq	$2,$0,$Lnjp_800C6DC0_62
	addu	$4,$0,$0
	addiu	$5,$0,63
	addiu	$6,$0,26
	sh	$0,40($18)
	jal	GM_SeSet2
	sh	$0,108($18)
	addu	$4,$18,$0
	jal	njp_800C3118
	addiu	$5,$0,12
$Lnjp_800C6DC0_62:
	jal	njp_800C41B4
	addu	$4,$16,$0
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_64
	nop
	jal	GV_RandS
	addiu	$4,$0,512
	lhu	$3,110($18)
	nop
	addu	$3,$3,$2
	j	$Lnjp_800C6DC0_64
	sh	$3,110($18)
$Lnjp_800C6DC0_63:
	andi	$2,$3,0x80
	beq	$2,$0,$Lnjp_800C6DC0_64
	nop
	jal	njp_800C41B4
	addu	$4,$16,$0
$Lnjp_800C6DC0_64:
	jal	njp_800C3D84
	addu	$4,$18,$0
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x4000
	bne	$2,$0,$Lnjp_800C6DC0_66
	nop
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,8192
	beq	$2,$0,$Lnjp_800C6DC0_65
	nop
	lw	$2,1952($18)
	nop
	bne	$2,$0,$Lnjp_800C6DC0_66
	nop
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,4
	bne	$2,$0,$Lnjp_800C6DC0_66
	nop
	jal	GM_StreamStatus
	nop
	addiu	$3,$0,2
	beq	$2,$3,$Lnjp_800C6DC0_66
	nop
	jal	GM_StreamPlayStop
	nop
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x4000
	lui	$3,%hi(GM_GameOverTimer)
	addiu	$2,$0,1
	j	$Lnjp_800C6DC0_66
	sw	$2,%lo(GM_GameOverTimer)($3)
$Lnjp_800C6DC0_65:
	lui	$16,%hi(GM_GameOverTimer)
	lw	$5,%lo(GM_GameOverTimer)($16)
	nop
	blez	$5,$Lnjp_800C6DC0_66
	lui	$3,0x1000
	lui	$4,%hi(GM_GameStatus)
	lw	$2,%lo(GM_GameStatus)($4)
	nop
	or	$2,$2,$3
	sw	$2,%lo(GM_GameStatus)($4)
	addiu	$2,$0,2
	bne	$5,$2,$Lnjp_800C6DC0_66
	nop
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x8
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,8192
	addu	$4,$18,$0
	jal	njp_800C2D68
	addu	$5,$0,$0
	addiu	$2,$0,-1
	sw	$2,%lo(GM_GameOverTimer)($16)
$Lnjp_800C6DC0_66:
	jal	njp_800C2A58
	addu	$4,$18,$0
	addu	$4,$18,$0
	lw	$16,2328($18)
	lw	$3,2324($18)
	addu	$5,$16,$0
	addiu	$2,$16,1
	jalr	$31,$3
	sw	$2,2328($18)
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,1
	beq	$2,$0,$Lnjp_800C6DC0_67
	addu	$4,$18,$0
	lw	$2,2344($18)
	j	$Lnjp_800C6DC0_68
	nop
$Lnjp_800C6DC0_67:
	lw	$2,2340($18)
$Lnjp_800C6DC0_68:
	nop
	jalr	$31,$2
	addu	$5,$16,$0
	lh	$4,86($18)
	lh	$5,2436($18)
	jal	GV_NearExp4
	nop
	lhu	$3,2442($18)
	lw	$4,2320($18)
	sh	$2,86($18)
	sh	$3,102($18)
	lhu	$2,2($4)
	nop
	andi	$2,$2,0x10
	beq	$2,$0,$Lnjp_800C6DC0_70
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,4
	bne	$2,$0,$Lnjp_800C6DC0_69
	addu	$2,$0,$0
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,2049
	bne	$2,$0,$Lnjp_800C6DC0_69
	addu	$2,$0,$0
	lw	$3,2344($18)
	lui	$2,%hi(njp_800C48EC)
	addiu	$2,$2,%lo(njp_800C48EC)
	bne	$3,$2,$Lnjp_800C6DC0_69
	addiu	$2,$0,1
	addu	$2,$0,$0
$Lnjp_800C6DC0_69:
	beq	$2,$0,$Lnjp_800C6DC0_70
	nop
	jal	njp_sub_8004EB74
	addu	$4,$18,$0
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,8
$Lnjp_800C6DC0_70:
	jal	njp_800C33C8
	addu	$4,$18,$0
	lh	$2,170($18)
	lh	$4,390($18)
	lhu	$3,2434($18)
	lui	$5,%hi(GM_PlayerAction)
	sw	$2,%lo(GM_PlayerAction)($5)
	lui	$2,%hi(dword_800AB9D4)
	sw	$4,%lo(dword_800AB9D4)($2)
	lui	$2,%hi(linkvarbuf+32)
	sh	$3,%lo(linkvarbuf+32)($2)
	lh	$3,170($18)
	addiu	$2,$0,25
	bne	$3,$2,$Lnjp_800C6DC0_72
	addiu	$16,$18,32
	slti	$2,$4,16
	bne	$2,$0,$Lnjp_800C6DC0_71
	addiu	$2,$0,7
	addiu	$2,$0,39
$Lnjp_800C6DC0_71:
	sw	$2,%lo(GM_PlayerAction)($5)
	addiu	$16,$18,32
$Lnjp_800C6DC0_72:
	lh	$5,170($18)
	lh	$6,390($18)
	jal	njp_800C3640
	addu	$4,$16,$0
	lh	$5,172($18)
	lh	$6,414($18)
	jal	njp_800C36EC
	addu	$4,$16,$0
$Lnjp_800C6DC0_73:
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C7C04
njp_800C7C04:
	addiu	$29,$29,-64
	sw	$17,44($29)
	addu	$17,$4,$0
	lui	$5,0x4
	sw	$31,60($29)
	sw	$20,56($29)
	sw	$19,52($29)
	sw	$18,48($29)
	jal	njp_sna_check_flags1_8004E31C
	sw	$16,40($29)
	beq	$2,$0,$Lnjp_800C7C04_1
	addu	$2,$0,$0
	jal	njp_800C3C1C
	addu	$4,$17,$0
	jal	njp_800C3D84
	addu	$4,$17,$0
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x4
	beq	$2,$0,$Lnjp_800C7C04_0
	addiu	$4,$17,32
	addiu	$5,$17,40
	lui	$2,%hi(dword_800AB9D4)
	jal	DG_SetPos2
	sw	$0,%lo(dword_800AB9D4)($2)
	lw	$4,156($17)
	jal	DG_PutObjs
	nop
	j	$Lnjp_800C7C04_1
	addiu	$2,$0,1
$Lnjp_800C7C04_0:
	addu	$2,$0,$0
$Lnjp_800C7C04_1:
	bne	$2,$0,$Lnjp_800C7C04_17
	nop
	lw	$16,2200($17)
	nop
	lhu	$2,6($16)
	nop
	andi	$2,$2,0x8
	beq	$2,$0,$Lnjp_800C7C04_2
	addiu	$4,$16,52
	addiu	$5,$17,100
	jal	GV_AddVec3
	addu	$6,$5,$0
	lhu	$2,6($16)
	nop
	andi	$2,$2,0xfff7
	sh	$2,6($16)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,55($16)
	swr	$8,52($16)
	swl	$9,59($16)
	swr	$9,56($16)
$Lnjp_800C7C04_2:
	lh	$20,180($17)
	jal	GM_ActMotion
	addiu	$4,$17,156
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x80
	beq	$2,$0,$Lnjp_800C7C04_4
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x800
	bne	$2,$0,$Lnjp_800C7C04_4
	addiu	$4,$29,32
	lwl	$8,2503($17)
	lwr	$8,2500($17)
	lwl	$9,2507($17)
	lwr	$9,2504($17)
	swl	$8,35($29)
	swr	$8,32($29)
	swl	$9,39($29)
	swr	$9,36($29)
	lui	$5,%hi(DG_ZeroVector)
	addiu	$5,$5,%lo(DG_ZeroVector)
	jal	GV_NearExp8V
	addiu	$6,$0,3
	jal	GV_VecLen3
	addiu	$4,$29,32
	slti	$2,$2,9
	bne	$2,$0,$Lnjp_800C7C04_3
	nop
	lwl	$8,35($29)
	lwr	$8,32($29)
	lwl	$9,39($29)
	lwr	$9,36($29)
	swl	$8,2503($17)
	swr	$8,2500($17)
	swl	$9,2507($17)
	swr	$9,2504($17)
$Lnjp_800C7C04_3:
	lhu	$2,2500($17)
	lbu	$3,119($17)
	lhu	$4,2504($17)
	andi	$3,$3,0x1
	sh	$2,100($17)
	beq	$3,$0,$Lnjp_800C7C04_4
	sh	$4,104($17)
	addu	$4,$17,$0
	jal	njp_sna_clear_flags1_8004E308
	lui	$5,0x80
$Lnjp_800C7C04_4:
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x200
	beq	$2,$0,$Lnjp_800C7C04_5
	nop
	sh	$0,104($17)
	sh	$0,100($17)
$Lnjp_800C7C04_5:
	lh	$18,152($17)
	lbu	$2,117($17)
	addiu	$3,$18,750
	andi	$2,$2,0x8
	beq	$2,$0,$Lnjp_800C7C04_6
	sh	$3,84($17)
	lw	$2,1944($17)
	nop
	slti	$2,$2,750
	beq	$2,$0,$Lnjp_800C7C04_6
	nop
	lhu	$2,34($17)
	nop
	sh	$2,84($17)
$Lnjp_800C7C04_6:
	lh	$2,2434($17)
	nop
	beq	$2,$0,$Lnjp_800C7C04_7
	slti	$2,$20,500
	bne	$2,$0,$Lnjp_800C7C04_7
	addiu	$2,$0,496
	sh	$2,82($17)
$Lnjp_800C7C04_7:
	jal	njp_800C2FE4
	addu	$4,$17,$0
	jal	njp_CheckSnakeDead_8004E384
	addu	$4,$17,$0
	jal	njp_800C3C1C
	addu	$4,$17,$0
	jal	GM_ActControl
	addiu	$4,$17,32
	lui	$19,%hi(njp_bss_40)
	lui	$16,%hi(njp_bss_32)
	addiu	$4,$16,%lo(njp_bss_32)
	sw	$0,4($4)
	sw	$0,%lo(njp_bss_32)($16)
	lh	$3,86($17)
	addiu	$2,$0,-2
	beq	$3,$2,$Lnjp_800C7C04_8
	sw	$0,%lo(njp_bss_40)($19)
	jal	HZD_GetLevelHazard
	nop
	lw	$2,%lo(njp_bss_32)($16)
	nop
	beq	$2,$0,$Lnjp_800C7C04_8
	nop
	lh	$2,46($2)
	nop
	sw	$2,%lo(njp_bss_40)($19)
$Lnjp_800C7C04_8:
	lh	$2,152($17)
	nop
	subu	$2,$18,$2
	slti	$2,$2,250
	bne	$2,$0,$Lnjp_800C7C04_11
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x800
	bne	$2,$0,$Lnjp_800C7C04_11
	lui	$2,%hi(njp_bss_32)
	lw	$2,%lo(njp_bss_32)($2)
	nop
	beq	$2,$0,$Lnjp_800C7C04_9
	addu	$4,$17,$0
	lhu	$2,6($2)
	nop
	andi	$2,$2,0x2
	beq	$2,$0,$Lnjp_800C7C04_11
	nop
$Lnjp_800C7C04_9:
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,4096
	bne	$2,$0,$Lnjp_800C7C04_11
	addu	$4,$17,$0
	lui	$5,0x80
	lwl	$8,103($17)
	lwr	$8,100($17)
	lwl	$9,107($17)
	lwr	$9,104($17)
	swl	$8,2503($17)
	swr	$8,2500($17)
	swl	$9,2507($17)
	swr	$9,2504($17)
	jal	njp_sna_set_flags1_8004E2F4
	sh	$0,2502($17)
	lui	$2,%hi(njp_800C5550)
	lw	$3,2324($17)
	addiu	$16,$2,%lo(njp_800C5550)
	beq	$3,$16,$Lnjp_800C7C04_11
	nop
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x1
	beq	$2,$0,$Lnjp_800C7C04_10
	addiu	$2,$0,450
	sh	$2,2436($17)
	lui	$4,0x3
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x10
	addu	$4,$17,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	jal	GM_ExitBehindCamera
	nop
$Lnjp_800C7C04_10:
	addu	$4,$17,$0
	jal	njp_sna_start_anim_8004E1F4
	addu	$5,$16,$0
$Lnjp_800C7C04_11:
	lh	$3,86($17)
	addiu	$2,$0,-2
	bne	$3,$2,$Lnjp_800C7C04_12
	addiu	$4,$17,32
	addiu	$5,$17,40
	lhu	$2,180($17)
	lhu	$3,34($17)
	subu	$2,$2,$20
	addu	$3,$3,$2
	jal	DG_SetPos2
	sh	$3,34($17)
$Lnjp_800C7C04_12:
	jal	GM_ActObject
	addiu	$4,$17,156
	addu	$4,$17,$0
	jal	njp_sna_clear_flags1_8004E308
	lui	$5,0x100
	addiu	$16,$17,32
	addu	$4,$16,$0
	jal	DG_GetLightMatrix2
	addiu	$5,$17,2120
	lui	$2,%hi(dword_800ABA1C)
	lw	$2,%lo(dword_800ABA1C)($2)
	lw	$3,2188($17)
	sltiu	$2,$2,1
	sw	$2,0($3)
	lw	$4,2200($17)
	jal	GM_MoveTarget
	addu	$5,$16,$0
	addu	$4,$17,$0
	lwl	$8,35($17)
	lwr	$8,32($17)
	lwl	$9,39($17)
	lwr	$9,36($17)
	swl	$8,27($29)
	swr	$8,24($29)
	swl	$9,31($29)
	swr	$9,28($29)
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,2048
	bne	$2,$0,$Lnjp_800C7C04_13
	lui	$19,%hi(GM_SnakeCamera)
	lw	$2,156($17)
	nop
	lhu	$2,648($2)
	nop
	sh	$2,26($29)
$Lnjp_800C7C04_13:
	addiu	$16,$19,%lo(GM_SnakeCamera)
	addu	$4,$17,$0
	lwl	$8,27($29)
	lwr	$8,24($29)
	lwl	$9,31($29)
	lwr	$9,28($29)
	swl	$8,2495($17)
	swr	$8,2492($17)
	swl	$9,2499($17)
	swr	$9,2496($17)
	lwl	$8,43($17)
	lwr	$8,40($17)
	lwl	$9,47($17)
	lwr	$9,44($17)
	swl	$8,43($16)
	swr	$8,40($16)
	swl	$9,47($16)
	swr	$9,44($16)
	lhu	$2,42($16)
	addiu	$18,$17,2492
	andi	$2,$2,0xfff
	jal	njp_800C6DC0
	sh	$2,42($16)
	lw	$4,2200($17)
	lwl	$8,103($17)
	lwr	$8,100($17)
	lwl	$9,107($17)
	lwr	$9,104($17)
	swl	$8,47($4)
	swr	$8,44($4)
	swl	$9,51($4)
	swr	$9,48($4)
	jal	GM_PushTarget
	nop
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C7C04_14
	addu	$4,$16,$0
	addu	$5,$18,$0
	jal	GV_NearExp4V
	addiu	$6,$0,3
	j	$Lnjp_800C7C04_15
	addu	$4,$17,$0
$Lnjp_800C7C04_14:
	addiu	$11,$19,%lo(GM_SnakeCamera)
	lwl	$8,27($29)
	lwr	$8,24($29)
	lwl	$9,31($29)
	lwr	$9,28($29)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	addu	$4,$17,$0
$Lnjp_800C7C04_15:
	ori	$5,$0,0x8000
	lui	$16,%hi(GM_PlayerPosition)
	lwl	$8,35($17)
	lwr	$8,32($17)
	lwl	$9,39($17)
	lwr	$9,36($17)
	swl	$8,19($29)
	swr	$8,16($29)
	swl	$9,23($29)
	swr	$9,20($29)
	addiu	$11,$16,%lo(GM_PlayerPosition)
	lwl	$8,19($29)
	lwr	$8,16($29)
	lwl	$9,23($29)
	lwr	$9,20($29)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	jal	njp_sna_check_flags1_8004E31C
	addiu	$19,$29,16
	beq	$2,$0,$Lnjp_800C7C04_16
	nop
	addiu	$11,$16,%lo(GM_PlayerPosition)
	lwl	$8,2495($17)
	lwr	$8,2492($17)
	lwl	$9,2499($17)
	lwr	$9,2496($17)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	lw	$4,2200($17)
	jal	GM_MoveTarget
	addiu	$5,$17,2492
$Lnjp_800C7C04_16:
	lh	$18,152($17)
	nop
	sh	$18,18($29)
	lw	$2,76($17)
	lw	$6,2116($17)
	lw	$4,8($2)
	jal	HZD_GetAddress
	addu	$5,$19,$0
	addiu	$4,$0,16384
	lui	$3,%hi(GM_PlayerAddress)
	sw	$2,2116($17)
	jal	njp_GM_ClearPlayerStatusFlag
	sw	$2,%lo(GM_PlayerAddress)($3)
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,3
	beq	$2,$0,$Lnjp_800C7C04_17
	nop
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,16384
$Lnjp_800C7C04_17:
	lw	$31,60($29)
	lw	$20,56($29)
	lw	$19,52($29)
	lw	$18,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C81E8
njp_800C81E8:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	addiu	$17,$16,32
	addu	$4,$17,$0
	sw	$31,28($29)
	jal	GM_FreeControl
	sw	$18,24($29)
	addiu	$18,$16,156
	jal	GM_FreeObject
	addu	$4,$18,$0
	lw	$4,2200($16)
	jal	GM_FreeTarget
	nop
	jal	njp_800C48F4
	addu	$4,$16,$0
	lw	$4,2184($16)
	nop
	beq	$4,$0,$Lnjp_800C81E8_0
	nop
	jal	GV_DestroyOtherActor
	nop
$Lnjp_800C81E8_0:
	lw	$4,2308($16)
	nop
	beq	$4,$0,$Lnjp_800C81E8_1
	lui	$3,%hi(GM_PlayerControl)
	jal	GV_DestroyOtherActor
	nop
	lui	$3,%hi(GM_PlayerControl)
$Lnjp_800C81E8_1:
	lw	$2,%lo(GM_PlayerControl)($3)
	nop
	bne	$2,$17,$Lnjp_800C81E8_2
	nop
	sw	$0,%lo(GM_PlayerControl)($3)
$Lnjp_800C81E8_2:
	lui	$3,%hi(GM_PlayerBody)
	lw	$2,%lo(GM_PlayerBody)($3)
	nop
	bne	$2,$18,$Lnjp_800C81E8_3
	nop
	sw	$0,%lo(GM_PlayerBody)($3)
$Lnjp_800C81E8_3:
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
	.globl	njp_800C82A4
njp_800C82A4:
	addiu	$29,$29,-88
	sw	$16,56($29)
	addu	$16,$4,$0
	sw	$17,60($29)
	addu	$17,$5,$0
	addiu	$4,$0,5
	addiu	$5,$0,2536
	sw	$31,84($29)
	sw	$22,80($29)
	sw	$21,76($29)
	sw	$20,72($29)
	sw	$19,68($29)
	jal	GV_NewActor
	sw	$18,64($29)
	addu	$18,$2,$0
	beq	$18,$0,$Lnjp_800C82A4_8
	lui	$5,%hi(njp_800C7C04)
	addu	$4,$18,$0
	addiu	$5,$5,%lo(njp_800C7C04)
	lui	$6,%hi(njp_800C81E8)
	addiu	$6,$6,%lo(njp_800C81E8)
	lui	$7,%hi(njp_str_4898)
	jal	GV_SetNamedActor
	addiu	$7,$7,%lo(njp_str_4898)
	addiu	$19,$18,32
	addu	$4,$19,$0
	addu	$5,$16,$0
	jal	GM_InitControl
	addu	$6,$17,$0
	bltz	$2,$Lnjp_800C82A4_6
	addiu	$2,$0,-1
	jal	GCL_GetOption
	addiu	$4,$0,112
	addiu	$4,$0,100
	jal	GCL_GetOption
	addu	$16,$2,$0
	addu	$4,$19,$0
	addu	$5,$16,$0
	jal	GM_ConfigControlString
	addu	$6,$2,$0
	addu	$4,$19,$0
	addu	$5,$0,$0
	addiu	$6,$0,450
	jal	GM_ConfigControlHazard
	addu	$7,$6,$0
	addiu	$2,$0,1
	sb	$2,89($19)
	addu	$4,$19,$0
	jal	GM_ConfigControlAttribute
	addu	$5,$2,$0
	jal	GM_ConfigControlTrapCheck
	addu	$4,$19,$0
	ori	$16,$0,0x92f1
	addiu	$4,$0,109
	jal	GCL_GetOption
	addiu	$20,$18,156
	beq	$2,$0,$Lnjp_800C82A4_0
	nop
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	addu	$16,$2,$0
$Lnjp_800C82A4_0:
	addu	$4,$20,$0
	addu	$5,$16,$0
	addiu	$6,$0,813
	jal	GM_InitObject
	ori	$7,$0,0x92f1
	jal	GM_ConfigObjectJoint
	addu	$4,$20,$0
	addu	$4,$20,$0
	addiu	$5,$18,384
	addiu	$6,$0,5887
	addiu	$7,$18,464
	addiu	$2,$18,1076
	sw	$2,16($29)
	addiu	$2,$18,1688
	sw	$19,20($29)
	jal	GM_ConfigMotionControl
	sw	$2,24($29)
	addu	$4,$20,$0
	jal	GM_ConfigObjectLight
	addiu	$5,$18,2120
	addu	$4,$18,$0
	lui	$2,%hi(GM_PlayerControl)
	sw	$19,%lo(GM_PlayerControl)($2)
	lui	$2,%hi(GM_PlayerPosition)
	addiu	$11,$2,%lo(GM_PlayerPosition)
	lwl	$8,35($18)
	lwr	$8,32($18)
	lwl	$9,39($18)
	lwr	$9,36($18)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	lui	$2,%hi(GM_PlayerBody)
	jal	njp_800C2914
	sw	$20,%lo(GM_PlayerBody)($2)
	lui	$2,%hi(linkvarbuf)
	addiu	$22,$2,%lo(linkvarbuf)
	addiu	$21,$0,-1
	lhu	$3,32($22)
	addiu	$2,$0,450
	sh	$2,2436($18)
	lui	$2,%hi(GM_SnakeCamera)
	sw	$21,2116($18)
	sw	$21,2312($18)
	sh	$3,2434($18)
	lwl	$8,35($18)
	lwr	$8,32($18)
	lwl	$9,39($18)
	lwr	$9,36($18)
	swl	$8,2467($18)
	swr	$8,2464($18)
	swl	$9,2471($18)
	swr	$9,2468($18)
	lwl	$8,35($18)
	lwr	$8,32($18)
	lwl	$9,39($18)
	lwr	$9,36($18)
	swl	$8,2495($18)
	swr	$8,2492($18)
	swl	$9,2499($18)
	swr	$9,2496($18)
	addiu	$11,$2,%lo(GM_SnakeCamera)
	lwl	$8,2495($18)
	lwr	$8,2492($18)
	lwl	$9,2499($18)
	lwr	$9,2496($18)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	jal	GCL_GetOption
	addiu	$4,$0,111
	beq	$2,$0,$Lnjp_800C82A4_1
	addiu	$2,$0,6000
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sh	$2,2486($18)
	addiu	$2,$0,6000
$Lnjp_800C82A4_1:
	sh	$2,2192($18)
	jal	GCL_GetOption
	addiu	$4,$0,108
	beq	$2,$0,$Lnjp_800C82A4_2
	addiu	$2,$0,512
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sh	$2,2192($18)
	addiu	$2,$0,512
$Lnjp_800C82A4_2:
	sh	$2,2194($18)
	jal	GCL_GetOption
	addiu	$4,$0,114
	beq	$2,$0,$Lnjp_800C82A4_3
	addiu	$4,$0,116
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sh	$2,2194($18)
	addiu	$4,$0,116
$Lnjp_800C82A4_3:
	lui	$16,%hi(njp_dword_800ABBDC)
	addiu	$2,$0,-1023
	lui	$17,%hi(njp_dword_800ABBD4)
	sh	$2,%lo(njp_dword_800ABBDC)($16)
	addiu	$2,$0,1023
	jal	GCL_GetOption
	sh	$2,%lo(njp_dword_800ABBD4)($17)
	beq	$2,$0,$Lnjp_800C82A4_4
	nop
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	jal	GCL_NextStr
	sh	$2,%lo(njp_dword_800ABBDC)($16)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sh	$2,%lo(njp_dword_800ABBD4)($17)
$Lnjp_800C82A4_4:
	sw	$21,2508($18)
	jal	GCL_GetOption
	addiu	$4,$0,101
	beq	$2,$0,$Lnjp_800C82A4_5
	nop
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sw	$2,2508($18)
$Lnjp_800C82A4_5:
	addu	$4,$18,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	addu	$4,$20,$0
	addu	$5,$0,$0
	addu	$6,$5,$0
	jal	GM_ConfigObjectAction
	addu	$7,$5,$0
	jal	GM_ActMotion
	addu	$4,$20,$0
	lui	$2,%hi(GV_PadData)
	addiu	$2,$2,%lo(GV_PadData)
	lh	$3,180($18)
	addiu	$17,$29,40
	sw	$2,2320($18)
	addiu	$2,$0,650
	sw	$3,1944($18)
	sh	$3,82($18)
	addiu	$3,$0,300
	sh	$3,40($29)
	sh	$2,2($17)
	jal	GM_AllocTarget
	sh	$3,4($17)
	addu	$16,$2,$0
	addu	$4,$16,$0
	addiu	$5,$0,159
	addiu	$6,$0,1
	addu	$7,$17,$0
	jal	GM_SetTarget
	sw	$16,2200($18)
	addu	$4,$16,$0
	addiu	$5,$0,1
	addiu	$6,$0,-1
	lui	$2,%hi(DG_ZeroVector)
	sw	$0,16($29)
	lh	$7,22($22)
	addiu	$2,$2,%lo(DG_ZeroVector)
	jal	GM_SetPowerTarget
	sw	$2,20($29)
	addu	$4,$16,$0
	addu	$5,$0,$0
	addu	$6,$5,$0
	addiu	$7,$18,2288
	addiu	$2,$18,2296
	jal	GM_SetCaptureTarget
	sw	$2,16($29)
	addu	$4,$16,$0
	jal	GM_MoveTarget
	addu	$5,$19,$0
	addu	$4,$19,$0
	lhu	$2,22($22)
	addu	$5,$20,$0
	sh	$2,2430($18)
	addiu	$2,$0,6
	sh	$2,34($29)
	addiu	$2,$0,12
	sh	$2,36($29)
	addiu	$2,$0,15
	sh	$2,38($29)
	addiu	$2,$18,2188
	sh	$0,32($29)
	sw	$2,16($29)
	lhu	$6,34($29)
	lhu	$2,32($29)
	lhu	$7,38($29)
	sll	$6,$6,16
	or	$6,$2,$6
	lhu	$2,36($29)
	sll	$7,$7,16
	jal	NewShadow2
	or	$7,$2,$7
	addu	$5,$17,$0
	addiu	$6,$29,48
	addiu	$7,$18,2532
	sw	$2,2184($18)
	lui	$2,%hi(dword_800ABA1C)
	sw	$0,%lo(dword_800ABA1C)($2)
	lui	$2,%hi(njp_bss_52)
	addiu	$3,$0,-65
	sw	$0,%lo(njp_bss_52)($2)
	addiu	$2,$0,-883
	sh	$21,30($22)
	sh	$2,44($29)
	addiu	$2,$0,-45
	sh	$0,40($29)
	sh	$3,42($29)
	sh	$0,48($29)
	sh	$3,50($29)
	sh	$2,52($29)
	lw	$4,156($18)
	lui	$2,%hi(snainit_item_800A9420)
	sw	$21,%lo(snainit_item_800A9420)($2)
	jal	NewKatana
	addiu	$4,$4,440
	addu	$2,$0,$0
$Lnjp_800C82A4_6:
	bltz	$2,$Lnjp_800C82A4_7
	lui	$2,%hi(njp_snainit_actor)
	sw	$18,%lo(njp_snainit_actor)($2)
	j	$Lnjp_800C82A4_9
	addu	$2,$18,$0
$Lnjp_800C82A4_7:
	jal	GV_DestroyActor
	addu	$4,$18,$0
$Lnjp_800C82A4_8:
	addu	$2,$0,$0
$Lnjp_800C82A4_9:
	lw	$31,84($29)
	lw	$22,80($29)
	lw	$21,76($29)
	lw	$20,72($29)
	lw	$19,68($29)
	lw	$18,64($29)
	lw	$17,60($29)
	lw	$16,56($29)
	jr	$31
	addiu	$29,$29,88
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
njp_str_47E8:
	.ascii	"\245\271\245\315\241\274\245\257"
	.byte	0
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
	.align	2
njp_str_4898:
	.ascii	"njaplay.c"
	.byte	0
	.text
