.section .text

# int add_function (int, int, int)
.globl add_function
.type add_function, @function
add_function:
        add     t0, a0, a1
        add     t0, t0, a2
        mv      a0, t0
        ret
        
