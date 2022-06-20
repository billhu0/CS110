# DO NOT REMOVE THIS LINE WHEN SUBMITTING
.import input.S

.data

# This is a global variable, 'int final_result', 
# which stores the length of the currently found max sub-series,
# which is initialized to zero.
.globl final_result
final_result: 
    .word 0 


.text                   # code starts here

.globl main
main:
    la      s0  str1    # let s0 = &str1[0]
    la      s1  str2    # let s1 = &str2[0]
    lw      s2  len1    # let s2 be len1
    lw      s3  len2    # let s3 be len2
    # s0 s1 s2 s3 will never be changed from now on.
    # All functions will promise not to change these 4 registers.
    
    # call the judging function. This includes reading data, judging and printing.
    jal     judge_func  

    # exit the program by ecall command.
    li      a0  10
    ecall   

judge_func:
    # This function is the core judging function.

    # The C code uses variables like 'i', 'j', 'len', whose meaning 
    # is clearly represented by looking at the c-code.

    # Since the risc-v assembly are 'translated' from this piece of C-code,
    # should you get confused with the variable names or label names (in the comments of the risc-v commands),
    # READ THIS C-CODE FIRST.


#  ██████╗     ██████╗ ██████╗ ██████╗ ███████╗
# ██╔════╝    ██╔════╝██╔═══██╗██╔══██╗██╔════╝
# ██║         ██║     ██║   ██║██║  ██║█████╗  
# ██║         ██║     ██║   ██║██║  ██║██╔══╝  
# ╚██████╗    ╚██████╗╚██████╔╝██████╔╝███████╗
#  ╚═════╝     ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝

# int str1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
# int str2[] = {3,4,5,10,11,12,13};
# int len1 = 13, len2 = 7;
# 
# int main(){
#     int result = 0;
#     // label: inloop1
#     for (int i = 0; i < len1; i++){
#         // label: inloop2
#         for (int j = 0; j < len2; j++){
#             int len = 0;
#             // label: inloop3
#             while (i+len < len1 && j+len < len2 && str1[i+len] == str2[j+len]){
#                 len++;
#             }
#             // label: outloop3
#             if (len >= result) result = len;
#             // a hidden 'j++' is placed here
#         }
#         // label: outloop2
#         // a hidden 'i++' is placed here
#     }
#     // label: outloop 1
#     printf("%d\n", result);
#     return 0;
# }

# ██████╗ ██╗███████╗ ██████╗     ██████╗ ██████╗ ██████╗ ███████╗
# ██╔══██╗██║██╔════╝██╔════╝    ██╔════╝██╔═══██╗██╔══██╗██╔════╝
# ██████╔╝██║███████╗██║         ██║     ██║   ██║██║  ██║█████╗  
# ██╔══██╗██║╚════██║██║         ██║     ██║   ██║██║  ██║██╔══╝  
# ██║  ██║██║███████║╚██████╗    ╚██████╗╚██████╔╝██████╔╝███████╗
# ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝     ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝

    # use s4 and s5 as the two iterators, 'i' and 'j'
    li      s4  0       # int i = 0;
    li      s5  0       # int j = 0;

judge_func_inloop1:                     # the out-most for-loop judging condition
    bge     s4  s2  judge_func_outloop1 # if (i>=len1) break the for-loop and print the result.
    li      s5  0                       # otherwise, step into the for-loop. Let 'j = 0'.

judge_func_inloop2:                     # the 2nd out-most for-loop judging condition
    bge     s5  s3  judge_func_outloop2 # if (j>=len2) break the 2nd for-loop (i++ and continue)
    li      s6  0                       # otherwise, step into the for-loop. Let 'len = 0'

judge_func_inloop3:
    # check the three conditions in the while loop
    # the 1st condition is 'i+len<len1', whose opposite is 'i+len>=len1' (checked by 'bge' in risc)
    addi    t0  s4  0                   # now t0 = i
    add     t0  t0  s6                  # now t0 = i + k
    bge     t0  s2  judge_func_outloop3 # if (i+k >= len1) go out of the while loop;

    # the 2nd condition is 'j+len<len2', whose opposite is 'j+len>=len2' (checked by 'bge' in risc)
    addi    t1  s5  0                   # now t0 = j
    add     t1  t1  s6                  # now t1 = j + k
    bge     t1  s3  judge_func_outloop3 # if (j+k >= len2) goto xx;
    
    # the 3rd condition is 'str1[i+len]==str2[j+len]'
    # which is a bit more complicated.
    # we have to get the offset (in words), then offset in Bytes, after that the address,
    # and finally, the value.
    addi    t2  t0  0                   # now t2 = i + len
    slli    t2  t2  2                   # now t2 = (i+k) * 4  (done by shift-left instruction)
    add     t2  t2  s0                  # now t2 = &str1[i+k] (done by adding the addr of 'str1' and the offset in Bytes together)
    lw      t4  0(t2)                   # now t4 = str1[i+k]  (done by loading the word from memory)
                                        # Same for str2[j+k] below. Some comments ommited.
    addi    t3  t1  0                   # now t3 = j + len
    slli    t3  t3  2                   # now t3 = (j+k) * 4
    add     t3  t3  s1                  # now t3 = &str2[j+k]
    lw      t5  0(t3)                   # now t5 = str2[j+k]

    bne     t4  t5  judge_func_outloop3 # if str1[i+k] != str2[i+k] go out of the inner while-loop.
    addi    s6  s6  1                   # otherwise, step into the inner while-loop, and iterate len ('len++;')

    j       judge_func_inloop3          # go back to the front of the inner while-loop

judge_func_outloop3:    # Here, we need to check and update the global variable 'final_result'.
    # iflen>result result = len
    # len is stored in s7
    # load final_result

    la      t6  final_result            # load the address of 'final_result'
    lw      a1  0(t6)                   # store the value of 'final_result' in a1
judge_func_check_if_greater_found:      # check if a greater length is found
    bge     s6  a1  judge_func_update_result  # if (len>=result), update it
    j       judge_func_dont_update_result     # else, don't update it 

judge_func_update_result:
    sw      s6  0(t6)                   # save the value of 'len' to the 'final_result'
judge_func_dont_update_result:          # no code here, since we should do nothing if newly-found length 
                                        # is no-greater than the currently-known length

    addi    s5  s5  1                   # j++, and 
    j       judge_func_inloop2          # continue to the 2nd out-most for-loop

judge_func_outloop2:
    addi    s4  s4  1                   # i++, and
    j       judge_func_inloop1          # continue to the out-most for-loop

judge_func_outloop1:    # Now the core-algorithm is done. Print the number and exit.

    addi    sp  sp  -4                  # adjust stack ptr to save the original 'ra' value
    sw      ra  0(sp)
    jal     print_number                # call the function to print the global var 'final_result'
    lw      ra  0(sp)
    addi    sp  sp  4                   # restore the original 'ra' value and exit function
    jr      ra                          # exit judge function

print_number:
    # This function prints the number stored in 
    # global variable 'final_result'.
    # It takes no argument and returns nothing. (void print_number(void))

    la      t0  final_result
    lw      a1  0(t0)                   # load the final_result from memory
    li      a0  1                       # let a0 = 1 to use ecall instruction 'print_int'
    ecall                               # print the number
    # li a1 '\n'
    # li a0 11
    # ecall                             # print '\n'  # It seems unnecessary to print '\n'
    jr      ra                          # return 
