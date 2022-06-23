#########################################################
# Function    void show_welcome_text()
# The original C-code is the following

# void show_welcome_text(){
#     LCD_Clear(BLACK);
#     show_str_dynamic(35, 15, "Chrome dino", BRED);
#     show_str_dynamic(30, 35, "Press any key", GBLUE);
#     show_str_dynamic(45, 55, "to play!", GBLUE);
# }

#########################################################

.section .text
.globl  show_welcome_text
.type   show_welcome_text,   @function

show_welcome_text:

        addi    sp, sp, -4  # push to the stack pointer
        sw      ra, 0(sp)   # save ra

        # LCD_Clear(BLACK)
        li      a0, 0x0000  # BLACK is macro-defined to 0x0000
        jal     LCD_Clear   # clear the screen to be black

        li      a0, 35      # add parameter to function
        li      a1, 15      # add parameter to function
        lui     t0, %hi(str_chrome_dino)
        addi    a2, t0, %lo(str_chrome_dino)
        li      a3, 0xF81F  # BRED
        jal     show_str_dynamic    # call function show_str_dynamic

        li      a0, 30      # add parameter to function
        li      a1, 35      # add parameter to function
        lui     t0, %hi(str_press_any_key)
        addi    a2, t0, %lo(str_press_any_key)
        li      a3, 0x07FF  # BRED
        jal     show_str_dynamic  # call function show_str_dynamic

        li      a0, 45      # add parameter to function
        li      a1, 55      # add parameter to function
        lui     t0, %hi(str_to_play)
        addi    a2, t0, %lo(str_to_play)
        li      a3, 0x07FF  # BRED
        jal     show_str_dynamic  # call function show_str_dynamic

        # return 
        lw      ra, 0(sp) # restore ra
        addi    sp, sp, 4 # restore stack pointer
        ret # return function


    str_chrome_dino:    .string     "Chrome dino"
    str_press_any_key:  .string     "Press any key"
    str_to_play:        .string     "to play!"