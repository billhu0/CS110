.data
test_input: .word 3 6 7 8

.text
main:
	add t0, x0, x0        # t0 = 0
	addi t1, x0, 4        # t1 = 4
	la t2, test_input     # t2 is pointing to array[3,6,7,8]
main_loop:
	beq t0, t1, main_exit   # if (t0==4) exit(0);
	slli t3, t0, 2        # t3 = t0 * 4
	add t4, t2, t3        # t4 = t2 + t3
	lw a0, 0(t4)          # a0 = *(t4)

	addi sp, sp, -20      # push the stack by 20 Bytes
	sw t0, 0(sp)          # save a copy of registers t0,t1,t2,t3,t4
	sw t1, 4(sp)
	sw t2, 8(sp)
	sw t3, 12(sp)
	sw t4, 16(sp)

	jal ra, factorial

	lw t0, 0(sp)         # restore the original value of t0,t1,t2,t3,t4
	lw t1, 4(sp)
	lw t2, 8(sp)
	lw t3, 12(sp)
	lw t4, 16(sp)
	addi sp, sp, 20      # pop the stack by 20 Bytes

	addi a1, a0, 0
	addi a0, x0, 1
	ecall # Print Result
	addi a1, x0, ' '
	addi a0, x0, 11
	ecall
	
	addi t0, t0, 1
	jal x0, main_loop
main_exit:  
	addi a0, x0, 10
	ecall # Exit

factorial:
	# YOUR CODE HERE
	addi t0, x0, 1         # result = 1
	addi t1, x0, 1
factorial_loop:
	beq a0, t1, factorial_return   # if (a==1) goto return;
	mul t0, t0, a0      # t0 = t0 * a0  # result *= a
	addi a0, a0, -1     # a--
	j factorial_loop
factorial_return:
	add a0, t0, x0    # return the value of result (t0)
	# return 
	jr ra