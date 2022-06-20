sum_naive:
.LFB5514:
	.cfi_startproc
	endbr64
	mov	edx, edi
	test	edi, edi
	jle	.L7
	lea	eax, -1[rdi]
	cmp	eax, 2
	jbe	.L8
	mov	ecx, edi
	mov	rax, rsi
	pxor	xmm0, xmm0
	shr	ecx, 2
	sub	ecx, 1
	sal	rcx, 4
	lea	rcx, 16[rsi+rcx]
	.p2align 4,,10
	.p2align 3
.L4:
	movdqu	xmm2, XMMWORD PTR [rax]
	add	rax, 16
	paddd	xmm0, xmm2
	cmp	rax, rcx
	jne	.L4
	movdqa	xmm1, xmm0
	mov	ecx, edx
	psrldq	xmm1, 8
	and	ecx, -4
	paddd	xmm0, xmm1
	movdqa	xmm1, xmm0
	psrldq	xmm1, 4
	paddd	xmm0, xmm1
	movd	eax, xmm0
	test	dl, 3
	je	.L11
.L3:
	movsx	rdi, ecx
	lea	r8, 0[0+rdi*4]
	add	eax, DWORD PTR [rsi+rdi*4]
	lea	edi, 1[rcx]
	cmp	edx, edi
	jle	.L1
	add	ecx, 2
	add	eax, DWORD PTR 4[rsi+r8]
	cmp	edx, ecx
	jle	.L1
	add	eax, DWORD PTR 8[rsi+r8]
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	xor	eax, eax
.L1:
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	ret
.L8:
	xor	ecx, ecx
	xor	eax, eax
	jmp	.L3
	.cfi_endproc
.LFE5514:
	.size	sum_naive, .-sum_naive