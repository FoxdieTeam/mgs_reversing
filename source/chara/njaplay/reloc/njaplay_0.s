	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C2914
njp_800C2914:
	lui	$2,%hi(njp_word_8009EFC0)
	addiu	$7,$2,%lo(njp_word_8009EFC0)
	lwl	$3,3($7)
	lwr	$3,0($7)
	lwl	$5,7($7)
	lwr	$5,4($7)
	lwl	$6,11($7)
	lwr	$6,8($7)
	swl	$3,2351($4)
	swr	$3,2348($4)
	swl	$5,2355($4)
	swr	$5,2352($4)
	swl	$6,2359($4)
	swr	$6,2356($4)
	lwl	$3,15($7)
	lwr	$3,12($7)
	lwl	$5,19($7)
	lwr	$5,16($7)
	swl	$3,2363($4)
	swr	$3,2360($4)
	swl	$5,2367($4)
	swr	$5,2364($4)
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.text
