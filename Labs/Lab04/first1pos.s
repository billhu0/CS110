.data
shouldben1:	.asciiz "Should be -1, and firstposshift and firstposmask returned: "
shouldbe0:	.asciiz "Should be 0 , and firstposshift and firstposmask returned: "
shouldbe16:	.asciiz "Should be 16, and firstposshift and firstposmask returned: "
shouldbe31:	.asciiz "Should be 31, and firstposshift and firstposmask returned: "

.text
main:
	la	a1, shouldbe31
	jal	print_str
	lui	a1, 0x80000	# should be 31
	jal	first1posshift
	mv	a1, a0
	jal	print_int
	jal	print_space

	lui	a1, 0x80000
	jal	first1posmask
	mv	a1, a0
	jal	print_int
	jal	print_newline

	la	a1, shouldbe16
	jal	print_str
	lui	a1, 0x0010	# should be 16
	jal	first1posshift
	mv	a1, a0
	jal	print_int
	jal	print_space

	lui	a1, 0x0010
	jal	first1posmask
	mv	a1, a0
	jal	print_int
	jal	print_newline

	la	a1, shouldbe0
	jal	print_str
	li	a1, 1		# should be 0
	jal	first1posshift
	mv	a1, a0
	jal	print_int
	jal	print_space

	li	a1, 1
	jal	first1posmask
	mv	a1, a0
	jal	print_int
	jal	print_newline

	la	a1, shouldben1
	jal	print_str
	mv	a1, zero		# should be -1
	jal	first1posshift
	mv	a1, a0
	jal	print_int
	jal	print_space

	mv	a1, zero
	jal	first1posmask
	mv	a1, a0
	jal	print_int
	jal	print_newline

	li	a0, 10
	ecall

first1posshift:
	### YOUR CODE HERE ###
	mv s9 zero
	Loop:
		beq a1 x0 zfinish
		#\when all zero return -1
		blt a1 x0 finish
		addi s9 s9 1

		slli a1 a1 1
		beq x0 x0 Loop
	finish:
		addi t3 x0 31
		sub a0 t3 s9
		jr ra
	zfinish:
		addi a0 x0 -1
		jr ra
		
	

first1posmask:
	### YOUR CODE HERE ###
	mv s9 zero
	lui	s10 0x80000
	Lop:
		beq a1 x0 zfinsh
		#\when all zero return -1
		and s11 s10 a1
		bne x0 s11 finsh
		addi s9 s9 1
		srli s10 s10 1
		beq x0 x0 Lop
	finsh:
		addi t3 x0 31
		sub a0 t3 s9
		jr ra
	zfinsh:
		addi a0 x0 -1
		jr ra
		

print_int:
	mv	a1, a0
	li	a0, 1
	ecall
	jr	ra

print_str:
	li	a0, 4
	ecall
	jr	ra

print_space:
	li	a1, ' '
	li	a0, 11
	ecall
	jr	ra

print_newline:
	li	a1, '\n'
	li	a0, 11
	ecall
	jr	ra
