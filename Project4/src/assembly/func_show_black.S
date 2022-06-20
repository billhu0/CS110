
#########################################################
# Function    my_lcd_show_black(int, int, int, int)
# The original C-code is the following

# void my_lcd_show_black(u16 x1, u16 y1, u16 x2, u16 y2) {
#     int size = (x2 - x1 + 1) * (y2 - y1 + 1) * 2;
#     LCD_Address_Set(x1, y1, x2, y2);
#     for (int i = 0; i < size; i++) {
#         LCD_WR_DATA8(0);
#     }
# }

#########################################################


.section .text
.globl  my_lcd_show_black
.type   my_lcd_show_black,   @function

my_lcd_show_black:
        addi    sp, sp, -16 # push to stack pointer
        sw      ra, 12(sp)  # save ra
        sw      s0, 8(sp)   # save s0
        sub     a4, a2, a0  # x2 - x1
        addi    a4, a4, 1   # x2 - x1 + 1
        sub     a5, a3, a1  # y2 - y1
        addi    a5, a5, 1   # y2 - y1 + 1
        mul     a4, a4, a5
        slli    s0, a4, 1   # (x2 - x1 + 1) * (y2 - y1 + 1) * 2
        call    LCD_Address_Set # call function LCD_Address_set
        blez    s0, exit    # if size = 0 immediately exit
loop: # enter loop
        li      a0, 0 # for loop initial condition
        call    LCD_WR_DATA8 # call function LCD_WR_DATA8 
        addi    s0, s0, -1   # while s0 != 0 loop
        bnez    s0, loop
exit: # exit function
        lw      ra, 12(sp) # restore ra
        lw      s0, 8(sp) # restore s0
        addi    sp, sp, 16 # restore stack pointer
        ret # ret function