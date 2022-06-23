.data

# Constant integer specifying the lines of RVC codes

# DO NOT MODIFY THIS VARIABLE
.globl lines_of_rvc_codes
lines_of_rvc_codes:
    .word 6


# RVC codes, 16-bits instructions mixed with 32-bits instructions
# A 16/32-bits binary number represents one line of rvc code.
# You can suppose all of the input codes are valid. 

# DO NOT MODIFY THIS VARIABLE
.globl rvc_codes
rvc_codes:
    .word 0b00000001010000110000001010010011
    .word 0b00000000000000001000001010110111
    .word 0b00000000101100110001001100010011
    .word 0b00000000101100110101001100010011
    .word 0b11111111000101000111010000010011
    .word 0b11111110000001000000011011100011






    # original testcase
    # .word 0b00000000000000000000001010110011
    # .half 0b0001010111111101
    # .half 0b1001001010101010
    # .half 0b0001010111111101
    # .word 0b11111110000001011101111011100011
    # .half 0b1000010100010110
    # .half 0b1000000010000010