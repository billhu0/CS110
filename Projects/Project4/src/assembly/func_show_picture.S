#########################################################
# Function    void my_lcd_show_picture(u16 x1, u16 y1, u16 x2, u16 y2, unsigned char img[])
# The original C-code is the following

# void my_lcd_show_picture(u16 x1, u16 y1, u16 x2, u16 y2, unsigned char img[]) {
#     int size = (x2 - x1 + 1) * (y2 - y1 + 1) * 2;
#     LCD_Address_Set(x1, y1, x2, y2);
#     for (int i = 0; i < size; i++) {
#         LCD_WR_DATA8(img[i]);
#     }
# }

#########################################################



.section .text
.globl  my_lcd_show_picture
.type   my_lcd_show_picture,   @function

my_lcd_show_picture:
        addi    sp, sp, -16     # push to stack pointer
        sw      ra, 12(sp)      # save ra
        sw      s0, 8(sp)       # save s0
        sw      s1, 4(sp)       # save s1

        mv      s0, a4          # s0 = a4
        sub     a4, a2, a0      # x2 - x1
        addi    a4, a4, 1       # x2 - x1 + 1
        sub     a5, a3, a1      # y2 - y1
        addi    a5, a5, 1       # y2 - y1 + 1
        mul     a4, a4, a5
        slli    s1, a4, 1       # s1 = size
        call    LCD_Address_Set # call function LCD_Address_Set
        blez    s1, exit        # if size < 0, then directly exit

loop:   # enter loop                              
        lbu     a0, 0(s0)
        call    LCD_WR_DATA8 # call function LCD_WR_DATA8
        addi    s1, s1, -1
        addi    s0, s0, 1 # s0++
        bnez    s1, loop # if s1 jump to loop

exit:
        lw      ra, 12(sp) # restore ra
        lw      s0, 8(sp)  # restore s0
        lw      s1, 4(sp)  # restore s1  
        addi    sp, sp, 16 # restore sp
        ret # return function
