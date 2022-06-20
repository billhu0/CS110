.data
.word 2, 4, 6, 8
n: .word 9

.text
main:   add     t0, x0, x0  # t0 = 0
        addi    t1, x0, 1   # t1 = 1
        la      t3, n       # t3 = &n 
        lw      t3, 0(t3)   # t3 = *n
fib:    beq     t3, x0, finish # if (t3 = 0) goto finish;
        add     t2, t1, t0  # t2 = t1 + t0
        mv      t0, t1      # t0 = t1
        mv      t1, t2      # t1 = t2
        addi    t3, t3, -1  # t3 -= 1
        j       fib         # goto fib
finish: addi    a0, x0, 1   # a0 = 1
        addi    a1, t0, 0   # a1 = t0
        ecall # print integer ecall   # print t0
        addi    a0, x0, 10
        ecall # terminate ecall       # exit(0)

# venus ecalls (environmental calls)
# Place id in a0, args in a1~a7
# 1  ==> print_int  (print the integer in a1)
# 4  ==> print_string  (a1 is the address)
# 10 ==> exit the program 
# 17 ==> exit the program with return code in a1
