	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	GodzReset
GodzReset:
	addiu	$29,$29,-32
	sw	$18,24($29)
	addu	$18,$4,$0
	sw	$16,16($29)
	addiu	$16,$18,32
	addu	$4,$16,$0
	addiu	$5,$0,13
	sw	$17,20($29)
	addiu	$17,$0,1
	sw	$31,28($29)
	jal	GM_ConfigControlAttribute
	sw	$17,2548($18)
	jal	GodzResetTarget
	addu	$4,$18,$0
	lui	$2,%hi(GODZCOM_PlayerAddress)
	lui	$3,%hi(GodzCommand)
	addiu	$3,$3,%lo(GodzCommand)
	lbu	$5,%lo(GODZCOM_PlayerAddress)($2)
	lh	$2,58($3)
	lw	$4,104($3)
	sllv	$2,$2,$17
	addu	$2,$2,$3
	lw	$4,8($4)
	lh	$6,60($2)
	jal	HZD_BoundOutZone
	addiu	$7,$0,200
	lw	$3,44($16)
	nop
	lw	$4,8($3)
	sllv	$3,$2,$17
	lw	$4,0($4)
	addu	$3,$3,$2
	lw	$4,20($4)
	sll	$3,$3,3
	addu	$4,$4,$3
	lhu	$2,0($4)
	nop
	sh	$2,32($18)
	lhu	$2,4($4)
	nop
	addiu	$2,$2,1000
	sh	$2,2($16)
	lhu	$2,2($4)
	nop
	sh	$2,4($16)
	lw	$4,3064($18)
	jal	GM_GetMap
	nop
	sw	$2,44($16)
	lw	$2,2552($18)
	lw	$3,3060($18)
	sb	$17,2956($18)
	sh	$0,2864($18)
	sh	$0,2866($18)
	sh	$0,2868($18)
	sh	$0,2870($18)
	sw	$0,2872($18)
	addiu	$2,$2,-1
	sw	$2,2884($18)
	lui	$2,%hi(GODZ_EYE_LENGTH)
	sw	$3,3072($18)
	lwl	$8,3047($18)
	lwr	$8,3044($18)
	lwl	$9,3051($18)
	lwr	$9,3048($18)
	swl	$8,3055($18)
	swr	$8,3052($18)
	swl	$9,3059($18)
	swr	$9,3056($18)
	lw	$4,3064($18)
	lhu	$3,%lo(GODZ_EYE_LENGTH)($2)
	addiu	$2,$0,512
	sw	$0,2980($18)
	sh	$0,2968($18)
	sh	$2,2970($18)
	sh	$0,2906($18)
	sw	$17,2892($18)
	sh	$3,2972($18)
	sw	$4,3076($18)
	lwl	$8,3047($18)
	lwr	$8,3044($18)
	lwl	$9,3051($18)
	lwr	$9,3048($18)
	swl	$8,3115($18)
	swr	$8,3112($18)
	swl	$9,3119($18)
	swr	$9,3116($18)
	lbu	$4,2957($18)
	lw	$2,3060($18)
	andi	$3,$4,0xff
	sw	$2,3100($18)
	sw	$2,3068($18)
	addiu	$2,$0,255
	beq	$3,$2,$LGodzReset_1
	nop
	bne	$3,$0,$LGodzReset_0
	addiu	$2,$4,-1
	lui	$4,%hi(godz_str_reset_err)
	jal	printf
	addiu	$4,$4,%lo(godz_str_reset_err)
	j	$LGodzReset_1
	nop
$LGodzReset_0:
	sb	$2,2957($18)
$LGodzReset_1:
	lw	$31,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
	.align	2
godz_str_reset_err:
	.ascii	" Err Err Enemy Reset Num Err CALL KOREKADOOOOOOOOOO!!\n"
	.byte	0
	.text
