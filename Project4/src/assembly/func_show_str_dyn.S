#########################################################
# Function    void show_str_dynamic(u16 x, u16 y, char str[], u16 color)
# The original C-code is the following

# void show_str_dynamic(u16 x, u16 y, char str[], u16 color) {
#     char c = '\0';
#     int length = strlen(str);
#     for (int i = 0; i < length; i++) {
#         delay_1ms(50);
#         c = str[i];
#         LCD_ShowChar(x + i * 8, y, (u8) c, 1, color);
#     }
# }

#########################################################

.section .text
.globl  show_str_dynamic
.type   show_str_dynamic,   @function
show_str_dynamic:
        addi    sp, sp, -32     # push to the stack
        sw      ra, 28(sp)      # save ra
        sw      s0, 24(sp)      # save s0
        sw      s1, 20(sp)      # save s1
        sw      s2, 16(sp)      # save s2
        sw      s3, 12(sp)      # save s3
        sw      s4, 8(sp)       # save s4
        sw      s5, 4(sp)       # save s5

        mv      s2, a3          # s2 = a3
        mv      s5, a2          # s5 = a2
        mv      s3, a1          # s3 = a1
        mv      s4, a0          # s4 = a0

        mv      a0, a2          # a0 = a2
        call    strlen          # call function strlen
        blez    a0, exit        # if a0 < 0 jump to label exit
        mv      s0, a0          # s0 = a0
        li      s1, 0

loop:  # enter loop
        li      a0, 50          # initial condition
        call    delay_1ms       # call function delay_1ms
        add     a0, s5, s1      
        lbu     a2, 0(a0)
        slli    a0, s1, 3
        add     a0, a0, s4      # a0 += s4
        slli    a0, a0, 16
        srli    a0, a0, 16
        li      a3, 1
        mv      a1, s3          # a1 = s3
        mv      a4, s2          # a4 = s2
        call    LCD_ShowChar    # call function LCD_ShowChar
        addi    s1, s1, 1       # s1++ and follow condition in loop
        bne     s0, s1, loop    # judge loop
        
exit: # enter label exit
        lw      ra, 28(sp)      # restore ra
        lw      s0, 24(sp)      # restore s0
        lw      s1, 20(sp)      # restore s1
        lw      s2, 16(sp)      # restore s2
        lw      s3, 12(sp)      # restore s3
        lw      s4, 8(sp)       # restore s4
        lw      s5, 4(sp)       # restore s5
        addi    sp, sp, 32      # restore stack pointer
        ret # return function