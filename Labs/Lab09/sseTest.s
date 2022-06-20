	.file	"sseTest.c"
	.text
.Ltext0:
	.file 0 "/home/ubuntu/DocumentServer/Study_docs/CS110-2022/Lab09" "sseTest.c"
	.section	.rodata
.LC5:
	.string	"|%g %g| * |%g %g| = |%g %g|\n"
.LC6:
	.string	"|%g %g|   |%g %g|   |%g %g|\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4203:
	.file 1 "sseTest.c"
	.loc 1 10 35
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$448, %rsp
	movl	%edi, -436(%rbp)
	movq	%rsi, -448(%rbp)
	.loc 1 10 35
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 13 12
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, -112(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -104(%rbp)
	movsd	.LC2(%rip), %xmm0
	movsd	%xmm0, -96(%rbp)
	movsd	.LC3(%rip), %xmm0
	movsd	%xmm0, -88(%rbp)
	.loc 1 13 30
	movsd	.LC2(%rip), %xmm0
	movsd	%xmm0, -80(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -72(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -64(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -56(%rbp)
	.loc 1 13 48
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -48(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -40(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -32(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -24(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, -416(%rbp)
.LBB32:
.LBB33:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/11/include/emmintrin.h"
	.loc 2 131 10
	movq	-416(%rbp), %rax
	movupd	(%rax), %xmm0
.LBE33:
.LBE32:
	.loc 1 22 18
	movaps	%xmm0, -352(%rbp)
	.loc 1 23 18
	leaq	-48(%rbp), %rax
	addq	$16, %rax
	movq	%rax, -424(%rbp)
.LBB34:
.LBB35:
	.loc 2 131 10
	movq	-424(%rbp), %rax
	movupd	(%rax), %xmm0
.LBE35:
.LBE34:
	.loc 1 23 18
	movaps	%xmm0, -336(%rbp)
.LBB36:
	.loc 1 25 14
	movl	$0, -428(%rbp)
	.loc 1 25 5
	jmp	.L4
.L14:
.LBB37:
	.loc 1 26 39 discriminator 3
	movl	-428(%rbp), %eax
	addl	%eax, %eax
	cltq
	.loc 1 26 37 discriminator 3
	leaq	0(,%rax,8), %rdx
	.loc 1 26 22 discriminator 3
	leaq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -376(%rbp)
.LBB38:
.LBB39:
	.loc 2 131 10 discriminator 3
	movq	-376(%rbp), %rax
	movupd	(%rax), %xmm0
.LBE39:
.LBE38:
	.loc 1 26 22 discriminator 3
	movaps	%xmm0, -320(%rbp)
	.loc 1 27 39 discriminator 3
	movl	-428(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	.loc 1 27 22 discriminator 3
	leaq	-80(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -392(%rbp)
.LBB40:
.LBB41:
	.loc 2 138 10 discriminator 3
	movq	-392(%rbp), %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -384(%rbp)
.LBB42:
.LBB43:
	.loc 2 75 10 discriminator 3
	movsd	-384(%rbp), %xmm0
	unpcklpd	%xmm0, %xmm0
.LBE43:
.LBE42:
	.loc 2 138 10 discriminator 3
	nop
.LBE41:
.LBE40:
	.loc 1 27 22 discriminator 3
	movaps	%xmm0, -304(%rbp)
	.loc 1 28 39 discriminator 3
	movl	-428(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,8), %rdx
	.loc 1 28 22 discriminator 3
	leaq	-80(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -408(%rbp)
.LBB44:
.LBB45:
	.loc 2 138 10 discriminator 3
	movq	-408(%rbp), %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -400(%rbp)
.LBB46:
.LBB47:
	.loc 2 75 10 discriminator 3
	movsd	-400(%rbp), %xmm0
	unpcklpd	%xmm0, %xmm0
.LBE47:
.LBE46:
	.loc 2 138 10 discriminator 3
	nop
.LBE45:
.LBE44:
	.loc 1 28 22 discriminator 3
	movaps	%xmm0, -288(%rbp)
	movapd	-320(%rbp), %xmm0
	movaps	%xmm0, -176(%rbp)
	movapd	-304(%rbp), %xmm0
	movaps	%xmm0, -160(%rbp)
.LBB48:
.LBB49:
	.loc 2 272 10 discriminator 3
	movapd	-176(%rbp), %xmm0
	mulpd	-160(%rbp), %xmm0
	movapd	-352(%rbp), %xmm1
	movaps	%xmm1, -208(%rbp)
	movaps	%xmm0, -192(%rbp)
.LBE49:
.LBE48:
.LBB50:
.LBB51:
	.loc 2 248 10 discriminator 3
	movapd	-208(%rbp), %xmm0
	addpd	-192(%rbp), %xmm0
.LBE51:
.LBE50:
	.loc 1 30 14 discriminator 3
	movaps	%xmm0, -352(%rbp)
	movapd	-320(%rbp), %xmm0
	movaps	%xmm0, -240(%rbp)
	movapd	-288(%rbp), %xmm0
	movaps	%xmm0, -224(%rbp)
.LBB52:
.LBB53:
	.loc 2 272 10 discriminator 3
	movapd	-240(%rbp), %xmm0
	mulpd	-224(%rbp), %xmm0
	movapd	-336(%rbp), %xmm1
	movaps	%xmm1, -272(%rbp)
	movaps	%xmm0, -256(%rbp)
.LBE53:
.LBE52:
.LBB54:
.LBB55:
	.loc 2 248 10 discriminator 3
	movapd	-272(%rbp), %xmm0
	addpd	-256(%rbp), %xmm0
.LBE55:
.LBE54:
	.loc 1 31 14 discriminator 3
	movaps	%xmm0, -336(%rbp)
.LBE37:
	.loc 1 25 29 discriminator 3
	addl	$1, -428(%rbp)
.L4:
	.loc 1 25 23 discriminator 1
	cmpl	$1, -428(%rbp)
	jle	.L14
	leaq	-48(%rbp), %rax
	movq	%rax, -360(%rbp)
	movapd	-352(%rbp), %xmm0
	movaps	%xmm0, -128(%rbp)
.LBE36:
.LBB56:
.LBB57:
	.loc 2 173 21
	movapd	-128(%rbp), %xmm0
	movq	-360(%rbp), %rax
	movups	%xmm0, (%rax)
	.loc 2 174 1
	nop
.LBE57:
.LBE56:
	.loc 1 36 5
	leaq	-48(%rbp), %rax
	addq	$16, %rax
	movq	%rax, -368(%rbp)
	movapd	-336(%rbp), %xmm0
	movaps	%xmm0, -144(%rbp)
.LBB58:
.LBB59:
	.loc 2 173 21
	movapd	-144(%rbp), %xmm0
	movq	-368(%rbp), %rax
	movups	%xmm0, (%rax)
	.loc 2 174 1
	nop
.LBE59:
.LBE58:
	.loc 1 39 5
	movsd	-32(%rbp), %xmm4
	movsd	-48(%rbp), %xmm3
	movsd	-64(%rbp), %xmm2
	movsd	-80(%rbp), %xmm1
	movsd	-96(%rbp), %xmm0
	movq	-112(%rbp), %rax
	movapd	%xmm4, %xmm5
	movapd	%xmm3, %xmm4
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$6, %eax
	call	printf@PLT
	.loc 1 40 5
	movsd	-24(%rbp), %xmm4
	movsd	-40(%rbp), %xmm3
	movsd	-56(%rbp), %xmm2
	movsd	-72(%rbp), %xmm1
	movsd	-88(%rbp), %xmm0
	movq	-104(%rbp), %rax
	movapd	%xmm4, %xmm5
	movapd	%xmm3, %xmm4
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$6, %eax
	call	printf@PLT
	.loc 1 42 12
	movl	$0, %eax
	.loc 1 43 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L16
	call	__stack_chk_fail@PLT
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4203:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 8
.LC1:
	.long	0
	.long	1073741824
	.align 8
.LC2:
	.long	0
	.long	1074266112
	.align 8
.LC3:
	.long	0
	.long	1074790400
	.text
.Letext0:
	.file 3 "/usr/include/stdio.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x4b6
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0xf
	.long	.LASF26
	.byte	0x1d
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x10
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF8
	.uleb128 0x6
	.long	0x6b
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x9
	.long	0x6b
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF10
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.long	.LASF11
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF12
	.uleb128 0xa
	.long	.LASF14
	.byte	0x28
	.long	0x96
	.uleb128 0xb
	.long	0xa1
	.long	0xa1
	.uleb128 0xc
	.byte	0
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.long	.LASF13
	.uleb128 0x9
	.long	0xa1
	.uleb128 0xa
	.long	.LASF15
	.byte	0x36
	.long	0xb7
	.uleb128 0xb
	.long	0xa1
	.long	0xc2
	.uleb128 0xc
	.byte	0
	.uleb128 0x11
	.long	.LASF27
	.byte	0x2
	.byte	0x3a
	.byte	0x10
	.long	0xb7
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.byte	0x4
	.long	.LASF16
	.uleb128 0x12
	.long	.LASF21
	.byte	0x3
	.value	0x164
	.byte	0xc
	.long	0x58
	.long	0xee
	.uleb128 0x13
	.long	0xee
	.uleb128 0x14
	.byte	0
	.uleb128 0x6
	.long	0x72
	.uleb128 0x15
	.long	.LASF28
	.byte	0x1
	.byte	0xa
	.byte	0x5
	.long	0x58
	.quad	.LFB4203
	.quad	.LFE4203-.LFB4203
	.uleb128 0x1
	.byte	0x9c
	.long	0x3dd
	.uleb128 0xd
	.long	.LASF17
	.byte	0xf
	.long	0x58
	.uleb128 0x3
	.byte	0x91
	.sleb128 -452
	.uleb128 0xd
	.long	.LASF18
	.byte	0x1c
	.long	0x3dd
	.uleb128 0x3
	.byte	0x91
	.sleb128 -464
	.uleb128 0x3
	.string	"A"
	.byte	0xd
	.byte	0xc
	.long	0x3e2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x3
	.string	"B"
	.byte	0xd
	.byte	0x1e
	.long	0x3e2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x3
	.string	"C"
	.byte	0xd
	.byte	0x30
	.long	0x3e2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x3
	.string	"c1"
	.byte	0x16
	.byte	0xd
	.long	0xad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -368
	.uleb128 0x3
	.string	"c2"
	.byte	0x17
	.byte	0xd
	.long	0xad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -352
	.uleb128 0x16
	.quad	.LBB36
	.quad	.LBE36-.LBB36
	.long	0x339
	.uleb128 0x3
	.string	"i"
	.byte	0x19
	.byte	0xe
	.long	0x58
	.uleb128 0x3
	.byte	0x91
	.sleb128 -444
	.uleb128 0x17
	.quad	.LBB37
	.quad	.LBE37-.LBB37
	.uleb128 0x3
	.string	"a"
	.byte	0x1a
	.byte	0x11
	.long	0xad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -336
	.uleb128 0x3
	.string	"b1"
	.byte	0x1b
	.byte	0x11
	.long	0xad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -320
	.uleb128 0x3
	.string	"b2"
	.byte	0x1c
	.byte	0x11
	.long	0xad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -304
	.uleb128 0x4
	.long	0x486
	.quad	.LBB38
	.quad	.LBE38-.LBB38
	.byte	0x1a
	.byte	0x16
	.long	0x1f4
	.uleb128 0x1
	.long	0x494
	.uleb128 0x3
	.byte	0x91
	.sleb128 -392
	.byte	0
	.uleb128 0x4
	.long	0x467
	.quad	.LBB40
	.quad	.LBE40-.LBB40
	.byte	0x1b
	.byte	0x16
	.long	0x23b
	.uleb128 0x1
	.long	0x475
	.uleb128 0x3
	.byte	0x91
	.sleb128 -408
	.uleb128 0x7
	.long	0x4a0
	.quad	.LBB42
	.quad	.LBE42-.LBB42
	.byte	0x2
	.byte	0x8a
	.byte	0xa
	.uleb128 0x1
	.long	0x4ad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -400
	.byte	0
	.byte	0
	.uleb128 0x4
	.long	0x467
	.quad	.LBB44
	.quad	.LBE44-.LBB44
	.byte	0x1c
	.byte	0x16
	.long	0x282
	.uleb128 0x1
	.long	0x475
	.uleb128 0x3
	.byte	0x91
	.sleb128 -424
	.uleb128 0x7
	.long	0x4a0
	.quad	.LBB46
	.quad	.LBE46-.LBB46
	.byte	0x2
	.byte	0x8a
	.byte	0xa
	.uleb128 0x1
	.long	0x4ad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -416
	.byte	0
	.byte	0
	.uleb128 0x4
	.long	0x3f2
	.quad	.LBB48
	.quad	.LBE48-.LBB48
	.byte	0x1e
	.byte	0xe
	.long	0x2b0
	.uleb128 0x1
	.long	0x40e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -176
	.uleb128 0x1
	.long	0x404
	.uleb128 0x3
	.byte	0x91
	.sleb128 -192
	.byte	0
	.uleb128 0x4
	.long	0x419
	.quad	.LBB50
	.quad	.LBE50-.LBB50
	.byte	0x1e
	.byte	0xe
	.long	0x2de
	.uleb128 0x1
	.long	0x432
	.uleb128 0x3
	.byte	0x91
	.sleb128 -208
	.uleb128 0x1
	.long	0x427
	.uleb128 0x3
	.byte	0x91
	.sleb128 -224
	.byte	0
	.uleb128 0x4
	.long	0x3f2
	.quad	.LBB52
	.quad	.LBE52-.LBB52
	.byte	0x1f
	.byte	0xe
	.long	0x30c
	.uleb128 0x1
	.long	0x40e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -240
	.uleb128 0x1
	.long	0x404
	.uleb128 0x3
	.byte	0x91
	.sleb128 -256
	.byte	0
	.uleb128 0x7
	.long	0x419
	.quad	.LBB54
	.quad	.LBE54-.LBB54
	.byte	0x1
	.byte	0x1f
	.byte	0xe
	.uleb128 0x1
	.long	0x432
	.uleb128 0x3
	.byte	0x91
	.sleb128 -272
	.uleb128 0x1
	.long	0x427
	.uleb128 0x3
	.byte	0x91
	.sleb128 -288
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4
	.long	0x486
	.quad	.LBB32
	.quad	.LBE32-.LBB32
	.byte	0x16
	.byte	0x12
	.long	0x35e
	.uleb128 0x1
	.long	0x494
	.uleb128 0x3
	.byte	0x91
	.sleb128 -432
	.byte	0
	.uleb128 0x4
	.long	0x486
	.quad	.LBB34
	.quad	.LBE34-.LBB34
	.byte	0x17
	.byte	0x12
	.long	0x383
	.uleb128 0x1
	.long	0x494
	.uleb128 0x3
	.byte	0x91
	.sleb128 -440
	.byte	0
	.uleb128 0x4
	.long	0x43e
	.quad	.LBB56
	.quad	.LBE56-.LBB56
	.byte	0x23
	.byte	0x5
	.long	0x3b1
	.uleb128 0x1
	.long	0x456
	.uleb128 0x3
	.byte	0x91
	.sleb128 -144
	.uleb128 0x1
	.long	0x44b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -376
	.byte	0
	.uleb128 0x7
	.long	0x43e
	.quad	.LBB58
	.quad	.LBE58-.LBB58
	.byte	0x1
	.byte	0x24
	.byte	0x5
	.uleb128 0x1
	.long	0x456
	.uleb128 0x3
	.byte	0x91
	.sleb128 -160
	.uleb128 0x1
	.long	0x44b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -384
	.byte	0
	.byte	0
	.uleb128 0x6
	.long	0x66
	.uleb128 0x18
	.long	0xa1
	.long	0x3f2
	.uleb128 0x19
	.long	0x2e
	.byte	0x3
	.byte	0
	.uleb128 0x1a
	.long	.LASF19
	.byte	0x2
	.value	0x10e
	.byte	0x1
	.long	0xad
	.byte	0x3
	.long	0x419
	.uleb128 0xe
	.string	"__A"
	.byte	0x15
	.long	0xad
	.uleb128 0xe
	.string	"__B"
	.byte	0x22
	.long	0xad
	.byte	0
	.uleb128 0x8
	.long	.LASF20
	.byte	0xf6
	.long	0xad
	.long	0x43e
	.uleb128 0x5
	.string	"__A"
	.byte	0xf6
	.byte	0x15
	.long	0xad
	.uleb128 0x5
	.string	"__B"
	.byte	0xf6
	.byte	0x22
	.long	0xad
	.byte	0
	.uleb128 0x1b
	.long	.LASF22
	.byte	0x2
	.byte	0xab
	.byte	0x1
	.byte	0x3
	.long	0x462
	.uleb128 0x5
	.string	"__P"
	.byte	0xab
	.byte	0x18
	.long	0x462
	.uleb128 0x5
	.string	"__A"
	.byte	0xab
	.byte	0x25
	.long	0xad
	.byte	0
	.uleb128 0x6
	.long	0xa1
	.uleb128 0x8
	.long	.LASF23
	.byte	0x88
	.long	0xad
	.long	0x481
	.uleb128 0x5
	.string	"__P"
	.byte	0x88
	.byte	0x1d
	.long	0x481
	.byte	0
	.uleb128 0x6
	.long	0xa8
	.uleb128 0x8
	.long	.LASF24
	.byte	0x81
	.long	0xad
	.long	0x4a0
	.uleb128 0x5
	.string	"__P"
	.byte	0x81
	.byte	0x1d
	.long	0x481
	.byte	0
	.uleb128 0x1c
	.long	.LASF25
	.byte	0x2
	.byte	0x49
	.byte	0x1
	.long	0xad
	.byte	0x3
	.uleb128 0x5
	.string	"__F"
	.byte	0x49
	.byte	0x15
	.long	0xa1
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x58
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 16
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x2107
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x2f
	.uleb128 0x21
	.sleb128 1
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 10
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 270
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x88
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF26:
	.string	"GNU C17 11.2.0 -mtune=generic -march=x86-64 -g -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection"
.LASF19:
	.string	"_mm_mul_pd"
.LASF23:
	.string	"_mm_load1_pd"
.LASF22:
	.string	"_mm_storeu_pd"
.LASF13:
	.string	"double"
.LASF15:
	.string	"__m128d"
.LASF11:
	.string	"float"
.LASF14:
	.string	"__v2df"
.LASF4:
	.string	"unsigned char"
.LASF5:
	.string	"short unsigned int"
.LASF20:
	.string	"_mm_add_pd"
.LASF2:
	.string	"long unsigned int"
.LASF28:
	.string	"main"
.LASF24:
	.string	"_mm_loadu_pd"
.LASF27:
	.string	"__m128d_u"
.LASF3:
	.string	"unsigned int"
.LASF12:
	.string	"long long unsigned int"
.LASF17:
	.string	"argc"
.LASF25:
	.string	"_mm_set1_pd"
.LASF10:
	.string	"long long int"
.LASF9:
	.string	"char"
.LASF21:
	.string	"printf"
.LASF7:
	.string	"short int"
.LASF18:
	.string	"argv"
.LASF8:
	.string	"long int"
.LASF16:
	.string	"long double"
.LASF6:
	.string	"signed char"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/ubuntu/DocumentServer/Study_docs/CS110-2022/Lab09"
.LASF0:
	.string	"sseTest.c"
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
