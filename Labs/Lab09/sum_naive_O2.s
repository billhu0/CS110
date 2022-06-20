sum_naive:
.LFB5514:
	.cfi_startproc
	endbr64
	test	edi, edi
	jle	.L4
	lea	eax, -1[rdi]
	lea	rdx, 4[rsi+rax*4]
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L3:
	add	eax, DWORD PTR [rsi]
	add	rsi, 4
	cmp	rsi, rdx
	jne	.L3
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	xor	eax, eax
	ret
	.cfi_endproc
.LFE5514:
	.size	sum_naive, .-sum_naive
