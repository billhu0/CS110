#########################################################
# Function    int main()
# The original C-code is the following

# int main() {
#     IO_init();   // miscellaneous initialize
#
#     welcome_page();  // display the welcome page
#
#     while (!Get_BOOT0() && !Get_Button(0) && !Get_Button(1)) delay_1ms(10);  // wait until BOOT0 button pressed
#
#     while (1){
#         int mode = settings_page();  // a simple settings menu
#         game_page(mode);  // game page
#         while (!Get_BOOT0() && !Get_Button(0) && !Get_Button(1)) delay_1ms(10);  // wait until BOOT0 button pressed
#     }
#
#     return 0;
# }

#########################################################



.section .text
.globl  main
.type   main,   @function
main:
        addi    sp, sp, -4 # push to the stack
        sw      ra, 0(sp)  # save ra

        # call IO_init() function
        jal     IO_init

        # display the welcome page
        jal     welcome_page

        # wait until any button is pressed
    main_loop1:

        # check if BOOT0 button pressed. If so (!=0), go out
        jal     Get_BOOT0 # call function get_boot0
        bnez    a0, main_outside1

        li      a0, 0 # button condition
        jal     Get_Button # call function get_button0
        bnez    a0, main_outside1

        li      a0, 1 # button condition
        jal     Get_Button # call function get_button1
        bnez    a0, main_outside1

        # delay 10ms and try again
        li      a0, 10 # button condition
        jal     delay_1ms # call function delay_1ms
        j       main_loop1

    main_outside1:

        # go to the settings page (to select mode)
        jal     settings_page

        # show the game page
        jal     game_page

        # wait until any button is pressed
    main_loop2:

        # check if BOOT0 button pressed. If so (!=0), go out
        jal     Get_BOOT0 # call function get_boot0
        bnez    a0, main_outside1

        li      a0, 0 # button condition
        jal     Get_Button # call function get_button0
        bnez    a0, main_outside1

        li      a0, 1 # button condition
        jal     Get_Button # call function get_button1
        bnez    a0, main_outside1

        # delay 10ms and try again
        li      a0, 10 # button condition
        jal     delay_1ms # call function delay_1ms
        j       main_loop2

        # exit main function (in fact its unreachable)
        xor     a0, a0, a0  # a0 = 0
        lw      ra, 0(sp)   # restore ra
        addi    sp, sp, 4   # restore stack pointer
        ret     # return function

    main_loop3:

        # check if BOOT0 button pressed. If so (!=0), go out
        jal     Get_BOOT0 # call function get_boot0
        bnez    a0, main_outside1

        li      a0, 0 # button condition
        jal     Get_Button # call function get_button0
        bnez    a0, main_outside1

        li      a0, 1 # button condition
        jal     Get_Button # call function get_button1
        bnez    a0, main_outside1

        # delay 10ms and try again
        li      a0, 10 # button condition
        jal     delay_1ms # call function delay_1ms
        j       main_loop2

        # exit main function (in fact its unreachable)
        xor     a0, a0, a0  # a0 = 0
        lw      ra, 0(sp)   # restore ra
        addi    sp, sp, 4   # restore stack pointer
        ret     # return function