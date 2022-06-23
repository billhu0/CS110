#########################################################
# Function    void print_select_mode()
# The original C-code is the following

# void print_select_mode(){
#     LCD_Clear(BLACK);

#     LCD_DrawRectangle(10, 5, 149, 75, WHITE);
    
#     show_str_dynamic(35, 15, "Select Mode", WHITE);
#     show_str_dynamic(20, 40, "Debug", GREEN);
#     show_str_dynamic(70, 40, "Mid", YELLOW);
#     show_str_dynamic(110, 40, "Hard", MAGENTA);
    
#     LCD_DrawLine(20, 56, 20+5*8, 56, WHITE);
#     LCD_DrawLine(70, 56, 70+3*8, 56, BLUE);
#     LCD_DrawLine(110, 56, 110+4*8, 56, BLUE);
# }

#########################################################

.section .text
.globl  print_select_mode
.type   print_select_mode,   @function

print_select_mode:

        addi    sp, sp, -4 # push to stack pointer
        sw      ra, 0(sp) # save ra

        # LCD_Clear(BLACK)
        li      a0, 0x0000  # BLACK is macro-defined to 0x0000
        jal     LCD_Clear   # clear the screen to be black

        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border

        # Show the line "select mode"
        lui     a0, %hi(str_select_mode)
        addi    a2, a0, %lo(str_select_mode)
        li      a0, 35  # add parameter to function
        li      a1, 15  # add parameter to function
        li      a3, 0xFFFF  # WHITE
        jal     show_str_dynamic    # call function show_str_dynamic

        # show the selection "debug"
        lui     a0, %hi(str_debug)
        addi    a2, a0, %lo(str_debug)
        li      a0, 20  # add parameter to function
        li      a1, 40  # add parameter to function
        li      a3, 0x07E0  # GREEN
        jal     show_str_dynamic    # call function show_str_dynamic

        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border


        # show the selection "yellow"
        lui     a0, %hi(str_mid)
        addi    a2, a0, %lo(str_mid)
        li      a0, 70  # add parameter to function
        li      a1, 40  # add parameter to function
        li      a3, 0xFFE0  # YELLOW
        jal     show_str_dynamic    # call function show_str_dynamic

        # show the selection "magenta"
        lui     a0, %hi(str_hard)
        addi    a2, a0, %lo(str_hard)
        li      a0, 110 # add parameter to function
        li      a1, 40  # add parameter to function
        li      a3, 0xF81F  # MAGENTA
        jal     show_str_dynamic    # call function show_str_dynamic


        # show the white line under the 1st option
        # LCD_DrawLine(20, 56, 20+5*8, 56, WHITE);
        li      a0, 20  # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 28  # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0xFFFF # WHITE
        call    LCD_DrawLine    # call function LCD_DrawLine

        # LCD_DrawLine(20, 56, 20+5*8, 56, WHITE);
        li      a0, 20  # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 36  # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0xFFFF # WHITE
        call    LCD_DrawLine    # call function LCD_DrawLine
        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border


        # LCD_DrawLine(20, 56, 20+5*8, 56, WHITE);
        li      a0, 20  # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 44  # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0xFFFF # WHITE
        call    LCD_DrawLine    # call function LCD_DrawLine

        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border


        # LCD_DrawLine(20, 56, 20+5*8, 56, WHITE);
        li      a0, 20  # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 52  # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0xFFFF # WHITE
        call    LCD_DrawLine    # call function LCD_DrawLine

        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border


        # LCD_DrawLine(20, 56, 20+5*8, 56, WHITE);
        li      a0, 20  # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 60  # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0xFFFF # WHITE
        call    LCD_DrawLine    # call function LCD_DrawLine

        # LCD_DrawLine(70, 56, 70+3*8, 56, BLUE);
        li      a0, 70  # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 78  # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0x001F  # BLUE
        call    LCD_DrawLine    # call function LCD_DrawLine
        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border
        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border


        # LCD_DrawLine(70, 56, 70+3*8, 56, BLUE);
        li      a0, 70  # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 86  # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0x001F  # BLUE
        call    LCD_DrawLine    # call function LCD_DrawLine

        # LCD_DrawLine(70, 56, 70+3*8, 56, BLUE);
        li      a0, 70  # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 94  # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0x001F  # BLUE
        call    LCD_DrawLine    # call function LCD_DrawLine

        # LCD_DrawLine(110, 56, 110+4*8, 56, BLUE);
        li      a0, 110 # add parameter to function
        li      a1, 56  # add parameter to function
        li      a2, 142 # add parameter to function
        li      a3, 56  # add parameter to function
        li      a4, 0x001F  # BLUE
        call    LCD_DrawLine    # call function LCD_DrawLine
        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border
        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border
        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border
        li      a0, 10      # add parameter to function
        li      a1, 5       # add parameter to function
        li      a2, 149     # add parameter to function
        li      a3, 75      # add parameter to function
        li      a4, 0xFFFF  # WHITE is macro-defined to 0xFFFF
        jal     LCD_DrawRectangle   # draw the border


        # return 
        lw      ra, 0(sp) # restore ra
        addi    sp, sp, 4 # restore sp
        ret # return function


    str_select_mode:    .string     "Select Mode"
    str_debug:          .string     "Debug"
    str_mid:            .string     "Mid"
    str_hard:           .string     "Hard"