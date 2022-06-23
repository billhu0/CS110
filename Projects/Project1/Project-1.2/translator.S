#   Project 1.2 RVC instructions to RISC-V instructions in RISC-V
#   You can suppose you will get the number of machine codes you should translate from 
#   "lines_of_rvc_codes" and get the 16 or 32 bits-machine codes from "rvc_codes". 
#   Both of them are stored in file "input.S"
#   When we test your project, we will change the input files content.
# DO NOT REMOVE THIS LINE WHEN SUBMITTING
.import input.S

.data
    ins:    .word   0   # ptr to ins[100]
    len:    .word   0   # ptr to len[100]
    res:    .word   0   # ptr to res[100]
    
.text
main:
        jal     readin          # read in the instructions
        # jal     test_print_ins  # DEBUG only: print the instructions out
        jal     analyze         # main expanding function
        jal     final_print     # print the final result out
        j       exit_0          # exit the program

readin:
        li      a0  0x3cc   # calloc a space for ins[100]
        li      a1  100
        li      a2  4
        li      a6  2
        ecall               # now a0 is &ins[0]
        la      t0  ins     # store to global var 'ins'
        sw      a0  0(t0)   # store address

        li      a0  0x3cc   # calloc a space for len[100]
        li      a1  100
        li      a2  4
        li      a6  2
        ecall
        la      t0  len     # store to global var 'len'
        sw      a0  0(t0) 

        li      a0  0x3cc   # calloc a space for res[100]
        li      a1  100
        li      a2  4
        li      a6  2
        ecall 
        la      t0  res
        sw      a0  0(t0)

        la      s0  lines_of_rvc_codes
        lw      s0  0(s0)       # get lines of code to s0
        la      s1  rvc_codes   # get &rvc_codes to s1

        li      s2  0       # s2 = i
        mv      s5  s1      # s5 = &rvc_codes[pos]
        j       readin_for_check
    readin_for_body:
        lhu     s4  0(s5)   # second = rvc_codes[pos]
        andi    t0  s4  3   
        li      t1  3       # if (second&3==3) read 32
        beq     t0  t1  readin_load_32
        bne     t0  t1  readin_load_16

    readin_load_32:
        lhu     s3  2(s5)   # first = rvc_codes[pos+1]
        slli    s3  s3  16
        add     s3  s3  s4  # s3 is the 32bit inst
        la      t1  ins
        lw      t1  0(t1)   # t1 = &ins[0]
        slli    t2  s2  2   
        add     t1  t1  t2  # t1 = &ins[i]
        sw      s3  0(t1)   # ins[i] = 32-bit ins
        la      t1  len
        lw      t1  0(t1)   # t1 = &len[0]
        add     t1  t1  t2  # t2 = &len[i]
        li      t6  4
        sw      t6  0(t1)   # len[i] = 4
        addi    s5  s5  4   # pos += 2
        addi    s2  s2  1   # i++
        j       readin_for_check
        
    readin_load_16:
        la      t1  ins
        lw      t1  0(t1)   # t1 = &ins[0]
        slli    t2  s2  2
        add     t1  t1  t2  # t1 = &ins[i]
        sw      s4  0(t1)   # ins[i] = second
        la      t1  len
        lw      t1  0(t1)   # t1 = &len[0]
        add     t1  t1  t2  # t1 = &len[i]
        li      t6  2
        sw      t6  0(t1)   # len[i] = 2
        addi    s5  s5  2   # pos += 1
        addi    s2  s2  1   # i++
        j       readin_for_check

    readin_for_check:
        blt     s2  s0  readin_for_body
        jr      ra

test_print_ins:
        la      s0  lines_of_rvc_codes
        lw      s0  0(s0)   # s0 = lines of code
        li      s1  0       # s1 = i
        la      s2  ins
        lw      s2  0(s2)   # s2 = &ins[0]
        la      s3  len
        lw      s3  0(s3)   # s3 = &len[0]
        j       test_print_ins_for_check
    test_print_ins_for_body:
        lw      a0  0(s2)   # print ins[i] in binary string
        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     print_unsigned_32
        lw      ra  0(sp)
        addi    sp  sp  4

        lw      a1  0(s3)   # print len[i]
        li      a0  1
        ecall 
        li      a1  '\n'    # print '\n'
        li      a0  11
        ecall
        addi    s1  s1  1   # i++
        addi    s2  s2  4
        addi    s3  s3  4

    test_print_ins_for_check:
        blt     s1  s0  test_print_ins_for_body
        jr      ra


analyze:
        la      s0  lines_of_rvc_codes
        lw      s0  0(s0)   # s0 = lines of code
        li      s1  0       # s1 = i
        la      s2  ins
        lw      s2  0(s2)   # s2 = &ins[0]
        la      s3  len
        lw      s3  0(s3)   # s3 = &len[0]
        la      s4  res
        lw      s4  0(s4)   # s4 = &res[0]
        j       analyze_for_check
    analyze_for_body:
        # at any time, s2 = &ins[i], s3 = &len[i], s4 = &res[i]
        lw      a1  0(s2)   # a1 = ins[i]
        lw      a1  0(s3)   # a1 = len[i]
        li      a2  2       # a2 = 2 for number reference
        li      a4  4       # a2 = 4 for number reference

        beq     a1  a2  analyze_expand_16   # if len[i] is 2, expand 16
        beq     a1  a4  analyze_expand_32   # else, expand 32  
    
    analyze_expand_16:
        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     c_add_jalr      # expand c.add and c.jalr 
        jal     c_mv_jr         # expand c.mv and c.jr
        jal     c_and_or_xor_sub# expand c.and, c.or, c.xor and c.sub
        jal     c_srli_srai     # expand c.srli and c.srai
        jal     c_slli          # expand c.slli
        jal     c_li            # expand c.li
        jal     c_lui           # expand c.lui
        jal     c_addi          # expand c.addi
        jal     c_andi          # expand c.andi
        jal     c_lw            # expand c.lw
        jal     c_sw            # expand c.sw
        jal     c_beqz_bnez     # expand c.beqz and c.bnez
        jal     c_j_jal         # expand c.j and c.jal
        lw      ra  0(sp)
        addi    sp  sp  4
        j       analyze_for_iterate # continue for-loop iteration
    analyze_expand_32:  # for the first iteration, we do nothing here
        addi    sp  sp  -4      
        sw      ra  0(sp)       
        jal     modify_32   # modify 32-bit instructions (offset for B and J)
        lw      ra  0(sp)
        addi    sp  sp  4 
        j       analyze_for_iterate # continuw for-loop iteration

    analyze_for_iterate:
        addi    s1  s1  1   # i++
        addi    s2  s2  4   # pointer of ins ++
        addi    s3  s3  4   # pointer of len ++
        addi    s4  s4  4   # pointer of res ++

    analyze_for_check:
        blt     s1  s0  analyze_for_body    # if (i < LOC) continue
        jr      ra

modify_32:  # for non-B,J type 32-bit instruction, directly out, otherwise modify the offset
        lw      a0  0(s2)           # a0 = ins[i], a 32-bit instruction
        andi    t0  a0  0b1111111   # get opcode
        li      t1  0b1100011       # B-type opcode template
        beq     t0  t1  modify32_B 
        li      t1  0b1101111       # JAL opcode template
        beq     t0  t1  modify32_JAL

        sw      a0  0(s4)   # otherwise, output the original 32-bit instruction
        jr      ra          # return function

    modify32_B:
        # get the original offset to t1
        li      t1  0

        srli    t2  a0  8   
        andi    t2  t2  0b1111  # get imm[4:1]
        slli    t2  t2  1       
        or      t1  t1  t2      # fill in imm[4:1]

        srli    t2  a0  25
        andi    t2  t2  0b111111    # get imm[10:5]
        slli    t2  t2  5       
        or      t1  t1  t2      # fill in imm[10:5]

        srli    t2  a0  7
        andi    t2  t2  0b1     # get imm[11]
        slli    t2  t2  11
        or      t1  t1  t2      # fill in imm[11]

        srli    t2  a0  31
        andi    t2  t2  0b1     # get imm[12]
        slli    t2  t2  12
        or      t1  t1  t2      # fill in imm[12]

        slli    t1  t1  19
        srai    t1  t1  19  # do sign-extension for this 13-bit number

        # now t1 is the original offset. Then we need to adjust it.
        beqz    t1  new_offset_zero   # zero offset
        bgez    t1  new_offset_down   # positive offset
        bltz    t1  new_offset_up     # negative offset

    new_offset_zero:
        sw      a0  0(s4)   # don't need to modify offset, directly output and exit func
        jr      ra
    new_offset_down:    # positive offset, search downwards, write, and exit
        # Note: at any time, s2 = &ins[i], s3 = &len[i], s4 = &res[i]
        addi    sp  sp  -4  # save the original s3
        sw      s3  0(sp)

        li      t3  0   # t3 will store the new offset
        new_offset_down_forloop:
        lw      t6  0(s3)   
        sub     t1  t1  t6  # sub the length (2 or 4)
        addi    t3  t3  4   # update new offset
        addi    s3  s3  4   # prepare for getting the next length
        bnez    t1  new_offset_down_forloop

        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     store_B     # write new offset to inst
        lw      ra  0(sp)
        addi    sp  sp  4

        lw      s3  0(sp)   # restore the original s3
        addi    sp  sp  4
        jr      ra          # exit function

    new_offset_up:  # negative offset
        # Note: at any time, s2 = &ins[i], s3 = &len[i], s4 = &res[i]
        addi    sp  sp  -4  # save the original s3
        sw      s3  0(sp)

        li      t3  0   # t3 will store the new offset
        addi    s3  s3  -4
        new_offset_up_forloop:
        lw      t6  0(s3)
        add     t1  t1  t6
        addi    t3  t3  -4
        addi    s3  s3  -4
        bnez    t1  new_offset_up_forloop
        
        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     store_B
        lw      ra  0(sp)
        addi    sp  sp  4

        lw      s3  0(sp)   # restore the original s3
        addi    sp  sp  4
        jr      ra          # exit function

    store_B:    # the new offset is in t3, put it back to B-type inst, and exit function
        # t0 will store the 32-bit new instruction
        li      t0  0b00000001111111111111000001111111
        and     t0  t0  a0  # clear the original offset to make it zero

        srli    t1  t3  1
        andi    t1  t1  0b1111  # get imm[4:1]
        slli    t1  t1  8
        or      t0  t0  t1      # fill imm[4:1]

        srli    t1  t3  5
        andi    t1  t1  0b111111    # get imm[10:5]
        slli    t1  t1  25
        or      t0  t0  t1      # fill imm[10:5]

        srli    t1  t3  11
        andi    t1  t1  0b1     # get imm[11]
        slli    t1  t1  7 
        or      t0  t0  t1      # fill imm[11]

        srli    t1  t3  12
        andi    t1  t1  0b1     # get imm[12]
        slli    t1  t1  31
        or      t0  t0  t1      # fill imm[12]

        sw      t0  0(s4)   # store the output instruction
        jr      ra

        


    modify32_JAL:
        # get the original offset to t1
        li      t1  0
        
        srli    t2  a0  21
        andi    t2  t2  0b1111111111    # get imm[10:1]
        slli    t2  t2  1
        or      t1  t1  t2  # fill in imm[10:1]

        srli    t2  a0  20
        andi    t2  t2  0b1 # get imm[11]
        slli    t2  t2  11
        or      t1  t1  t2  # fill in imm[11]

        srli    t2  a0  12
        andi    t2  t2  0b11111111  # get imm[19:12]
        slli    t2  t2  12
        or      t1  t1  t2  # fill in imm[19:12]

        srli    t2  a0  31
        andi    t2  t2  0b1     # get imm[20]
        slli    t2  t2  20
        or      t1  t1  t2  # fill in imm[20]

        slli    t1  t1  11
        srai    t1  t1  11  # sign extension

        # now t1 is the original offset. Then we need to adjust it.
        beqz    t1  new_offset_zero_J   # zero offset
        bgez    t1  new_offset_down_J   # positive offset
        bltz    t1  new_offset_up_J    # negative offset

    new_offset_zero_J:
        sw      a0  0(s4)   # don't need to modify offset, directly output and exit func
        jr      ra
    new_offset_down_J:    # positive offset, search downwards
        # Note: at any time, s2 = &ins[i], s3 = &len[i], s4 = &res[i]
        addi    sp  sp  -4  # save the original s3
        sw      s3  0(sp)

        li      t3  0   # t3 will store the new offset
        new_offset_down_J_forloop:
        lw      t6  0(s3)   
        sub     t1  t1  t6  # sub the length (2 or 4)
        addi    t3  t3  4   # update new offset
        addi    s3  s3  4   # prepare for getting the next length
        bnez    t1  new_offset_down_J_forloop
        j       store_J

    new_offset_up_J:  # negative offset
        # Note: at any time, s2 = &ins[i], s3 = &len[i], s4 = &res[i]
        addi    sp  sp  -4  # save the original s3
        sw      s3  0(sp)

        li      t3  0   # t3 will store the new offset
        addi    s3  s3  -4
        new_offset_up_J_forloop:
        lw      t6  0(s3)
        add     t1  t1  t6
        addi    t3  t3  -4
        addi    s3  s3  -4
        bnez    t1  new_offset_up_J_forloop
        j       store_J


    
    store_J:   # the new offset is in t3, put it back to J-type inst, and exit function
        li      t0  0b111111111111
        and     t0  t0  a0  # clear the original offset to make it zero

        srli    t1  t3  1
        andi    t1  t1  0b1111111111    # get imm[10:1]
        slli    t1  t1  21
        or      t0  t0  t1  # fill imm[10:1]

        srli    t1  t3  11
        andi    t1  t1  0b1 # get imm[11]
        slli    t1  t1  20
        or      t0  t0  t1  # fill imm[11]

        srli    t1  t3  12
        andi    t1  t1  0b11111111  # get imm[19:12]
        slli    t1  t1  12
        or      t0  t0  t1  # fill imm[19:12]

        srli    t1  t3  20
        andi    t1  t1  0b1 # get imm[20]
        slli    t1  t1  31
        or      t0  t0  t1  # fill imm[20]

        sw      t0  0(s4)   # store the output instruction

        lw      s3  0(sp)   # restore the original s3
        addi    sp  sp  4
        jr      ra      # exit function


c_j_jal:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  11
        andi    t0  t0  0b11100 # get funct3
        andi    t1  a0  0b11    # get opcode
        or      t0  t0  t1      # get funct3 and op
        li      t2  0b10101     # c.j expected: funct3=101, op=01
        beq     t0  t2  expand_c_j
        li      t2  0b00101     # c.jal expected: funct3=001, op=01
        beq     t0  t2  expand_c_jal
        j       c_j_jal_exit    # otherwise, exit function

    expand_c_j:
        li      t0  0   # t0 will store the 32-bit inst result
        j       c_j_jal_common

    expand_c_jal:
        li      t0  0   # t0 will store the 32-bit inst result
        li      t1  0b00001
        slli    t1  t1  7   
        or      t0  t0  t1  # fill in rd (which is x1)
        j       c_j_jal_common

    c_j_jal_common:
        ori     t0  t0  0b1101111   # fill opcode=1101111

        # get the original offset to t1
        srli    t1  a0  3
        andi    t1  t1  0b111   # get offset[3:1]
        slli    t1  t1  1       # move to correct position
        
        srli    t2  a0  11
        andi    t2  t2  0b1     # get offset[4]
        slli    t2  t2  4   
        or      t1  t1  t2      # fill offset[4]

        srli    t2  a0  2
        andi    t2  t2  0b1     # get offset[5]
        slli    t2  t2  5
        or      t1  t1  t2      # fill offset[5]

        srli    t2  a0  7
        andi    t2  t2  0b1     # get offset[6]
        slli    t2  t2  6
        or      t1  t1  t2      # fill offset[6]

        srli    t2  a0  6
        andi    t2  t2  0b1     # get offset[7]
        slli    t2  t2  7
        or      t1  t1  t2      # fill offset[7]

        srli    t2  a0  9
        andi    t2  t2  0b11    # get offset[9:8]
        slli    t2  t2  8
        or      t1  t1  t2      # fill offset[9:8]

        srli    t2  a0  8
        andi    t2  t2  0b1     # get offset[10]
        slli    t2  t2  10
        or      t1  t1  t2      # fill offset[10]

        srli    t2  a0  12
        andi    t2  t2  0b1     # get offset[11]
        slli    t2  t2  11
        or      t1  t1  t2      # fill offset[11]

        slli    t1  t1  20
        srai    t1  t1  20  # do sign extension for this 12-bit number

        # now t1 is the original offset. We need to adjust it.
        beqz    t1  c_j_jal_zero    # zero offset
        bgez    t1  c_j_jal_down    # positive offset
        bltz    t1  c_j_jal_up      # negative offset

    c_j_jal_zero:   # zero offset, fill in nothing, directly output
        sw      t0  0(s4)
        jr      ra  

    c_j_jal_down:   # positive offset
        addi    sp  sp  -4
        sw      s3  0(sp)
        li      t3  0   # t3 will store the new offset
        c_j_jal_down_forloop:
        lw      t6  0(s3)
        sub     t1  t1  t6
        addi    t3  t3  4
        addi    s3  s3  4
        bnez    t1  c_j_jal_down_forloop

        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     c_j_jal_store
        lw      ra  0(sp)
        addi    sp  sp  4

        lw      s3  0(sp)
        addi    sp  sp  4
        jr      ra

    c_j_jal_up:     # negative offset
        addi    sp  sp  -4
        sw      s3  0(sp)
        li      t3  0
        addi    s3  s3  -4
        c_j_jal_up_forloop:
        lw      t6  0(s3)
        add     t1  t1  t6
        addi    t3  t3  -4
        addi    s3  s3  -4
        bnez    t1  c_j_jal_up_forloop

        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     c_j_jal_store
        lw      ra  0(sp)
        addi    sp  sp  4

        lw      s3  0(sp)
        addi    sp  sp  4
        jr      ra

    c_j_jal_exit:
        jr      ra  # exit the function

    c_j_jal_store:  # the new offset is in t3, put it into J instruction, and exit function
        srli    t1  t3  1
        andi    t1  t1  0b1111111111    # get imm[10:1]
        slli    t1  t1  21
        or      t0  t0  t1  # fill imm[10:1]

        srli    t1  t3  11
        andi    t1  t1  0b1 # get imm[11]
        slli    t1  t1  20
        or      t0  t0  t1  # fill imm[11]

        srli    t1  t3  12
        andi    t1  t1  0b11111111  # get imm[19:12]
        slli    t1  t1  12
        or      t0  t0  t1  # fill imm[19:12]

        srli    t1  t3  20
        andi    t1  t1  0b1 # get imm[20]
        slli    t1  t1  31
        or      t0  t0  t1  # fill imm[20]

        sw      t0  0(s4)   # store the output instruction

        jr      ra  # 1

c_beqz_bnez:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  11
        andi    t0  t0  0b11100 # get funct3
        andi    t1  a0  0b11
        or      t0  t0  t1  # get funct3 and opcode
        li      t2  0b11001 # c.beqz expected: funct3=110, op=01
        beq     t0  t2  expand_c_beqz
        li      t2  0b11101 # c.bnez expected: funct3=111, op=01
        beq     t0  t2  expand_c_bnez
        j       c_beqz_bnez_exit    # otherwise, exit function

    expand_c_beqz:
        li      t0  0   # t0 will store the 32-bit inst result
        j       expand_beqz_bnez_common

    expand_c_bnez:
        li      t0  0   # t0 will store the 32-bit inst result
        li      t1  0b001
        slli    t1  t1  12
        or      t0  t0  t1  # fill funct3=001
        j       expand_beqz_bnez_common

    expand_beqz_bnez_common:
        ori     t0  t0  0b1100011   # fill opcode

        srli    t1  a0  7
        andi    t1  t1  0b111   # get rs1'
        ori     t1  t1  0b01000 # restore the original reg name
        slli    t1  t1  15
        or      t0  t0  t1  # fill rs1

        # get the original offset to t1
        srli    t1  a0  3
        andi    t1  t1  0b11
        slli    t1  t1  1   # fill offset[2:1]
        srli    t2  a0  10
        andi    t2  t2  0b11
        slli    t2  t2  3   # get offset[4:3]
        or      t1  t1  t2  # fill offset[4:1]
        srli    t2  a0  2
        andi    t2  t2  0b1
        slli    t2  t2  5   # get offset[5]
        or      t1  t1  t2  # fill offset[5:1]
        srli    t2  a0  5
        andi    t2  t2  0b11
        slli    t2  t2  6   # get offset[7:6]
        or      t1  t1  t2  # fill offset[7:1]
        srli    t2  a0  12
        andi    t2  t2  0b1
        slli    t2  t2  8   # get offset[8]
        or      t1  t1  t2  # fill offset[8:1]

        slli    t1  t1  23
        srai    t1  t1  23  # sign extension for this 9-bit number

        # now t1 is the original offset. We need to adjust it.
        beqz    t1  c_beqz_bnez_zero    # zero offset
        bgez    t1  c_beqz_bnez_down    # positive offset
        bltz    t1  c_beqz_bnez_up      # negative offset

    c_beqz_bnez_zero:   # zero offset, fill in nothing, directly output
        sw      t0  0(s4)
        jr      ra 
    
    c_beqz_bnez_down:   # positive offset
        addi    sp  sp  -4
        sw      s3  0(sp)
        li      t3  0   # t3 will store the new offset
        c_beqz_bnez_down_forloop:
        lw      t6  0(s3)
        sub     t1  t1  t6
        addi    t3  t3  4
        addi    s3  s3  4
        bnez    t1  c_beqz_bnez_down_forloop

        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     c_beqz_bnez_store
        lw      ra  0(sp)
        addi    sp  sp  4

        lw      s3  0(sp)
        addi    sp  sp  4
        jr      ra

    c_beqz_bnez_up:     # negative offset
        addi    sp  sp  -4
        sw      s3  0(sp)
        addi    s3  s3  -4
        li      t3  0
        c_beqz_bnez_up_forloop:
        lw      t6  0(s3)
        add     t1  t1  t6
        addi    t3  t3  -4
        addi    s3  s3  -4
        bnez    t1  c_beqz_bnez_up_forloop

        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     c_beqz_bnez_store
        lw      ra  0(sp)
        addi    sp  sp  4

        lw      s3  0(sp)
        addi    sp  sp  4
        jr      ra


    c_beqz_bnez_exit:
        jr      ra  

    c_beqz_bnez_store:    # the new offset is in t3, put it to B-type inst, and exit function
        # t0 will store the 32-bit new instruction
        srli    t1  t3  1
        andi    t1  t1  0b1111  # get imm[4:1]
        slli    t1  t1  8
        or      t0  t0  t1      # fill imm[4:1]

        srli    t1  t3  5
        andi    t1  t1  0b111111    # get imm[10:5]
        slli    t1  t1  25
        or      t0  t0  t1      # fill imm[10:5]

        srli    t1  t3  11
        andi    t1  t1  0b1     # get imm[11]
        slli    t1  t1  7 
        or      t0  t0  t1      # fill imm[11]

        srli    t1  t3  12
        andi    t1  t1  0b1     # get imm[12]
        slli    t1  t1  31
        or      t0  t0  t1      # fill imm[12]

        sw      t0  0(s4)   # store the output instruction
        jr      ra


c_add_jalr:  # Note: at any time, s2 = &ins[i], s3 = &len[i], s4 = &res[i]
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  10  
        andi    t0  t0  0b111100    # get the funct4
        andi    t1  a0  0b11    # get opcode
        add     t0  t0  t1      # get funct4 and opcode
        li      t2  0b100110    # expected funct4=1001 and opcode=10

        beq     t0  t2  c_add_jalr_matches  # c.add or c.jalr
        jr      ra      # if failed to match, exit the function
        
    c_add_jalr_matches:     # distinguish c.add or c.jalr
        andi    t1  a0  0b1111100   # get rs2
        bnez    t1  expand_c_add    # rs2 is not x0, c.add inst
        beqz    t1  expand_c_jalr   # rs2 is x0, c.jalr inst

    expand_c_add:
        li      t0  0   # t0 will store the 32-bit inst result
        ori     t0  t0  0b0110011   # fill opcode=0110011

        srli    t1  a0  7 
        andi    t1  t1  0b11111 # get rd (which is also rs1)
        slli    t1  t1  7   # move to the positon of rd
        or      t0  t0  t1  # fill rd 
        slli    t1  t1  8   # continue move to the position of rs1
        or      t0  t0  t1  # fill rs1

        srli    t1  a0  2   
        andi    t1  t1  0b11111 # get rs2
        slli    t1  t1  20  # move to the position of rs2
        or      t0  t0  t1  # fill rs2

        sw      t0  0(s4)   # store to result
        jr      ra          # exit c_add_jalr function

    expand_c_jalr:
        li      t0  0   # t0 is going to store the result
        addi    t0  t0  0b11100111  # fill rd=00001 and opcode=1100111

        srli    t1  a0  7   # get rs1
        andi    t1  t1  0b11111
        slli    t1  t1  15 
        or      t0  t0  t1  # fill rs1

        sw      t0  0(s4)   # store the result
        jr      ra          # return the c_add_jalr function

c_mv_jr:  # Note: at any time, s2 = &ins[i], s3 = &len[i], s4 = &res[i]
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  10  # t0 = a0 >> 10
        andi    t0  t0  0b111100
        andi    t1  a0  0b11    # get opcode
        add     t0  t0  t1  
        li      t2  0b100010    # expected funct4 and opcode

        beq     t0  t2  c_mv_jr_matches  # c.mv or c.jr matches
        jr      ra      # if failed to match, exit the function

    c_mv_jr_matches:    # distinguish c.mv or c.jr
        andi    t1  a0  0b1111100
        bnez    t1  expand_c_mv
        beqz    t1  expand_c_jr

    expand_c_mv:
        li      t0  0   # t0 will store the 32-bit inst result
        addi    t0  t0  0b0110011   # opcode

        srli    t1  a0  7
        andi    t1  t1  0b11111     # get rd
        slli    t1  t1  7
        or      t0  t0  t1  # fill rd

        srli    t1  a0  2   # get rs2
        andi    t1  t1  0b11111
        slli    t1  t1  20
        or      t0  t0  t1  # fill rs2

        sw      t0  0(s4)   # store result
        jr      ra          # exit  c_mv_jr function

    expand_c_jr:
        li      t0  0   # t0 will store the 32-bit inst result
        addi    t0  t0  0b1100111   # opcode

        srli    t1  a0  7   # get rs1
        andi    t1  t1  0b11111
        slli    t1  t1  15 
        or      t0  t0  t1  # fill rs1

        sw      t0  0(s4)   # store the result
        jr      ra          # exit c_mv_jr function

c_and_or_xor_sub:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  8   
        andi    t0  t0  0b11111100  # get funct6
        andi    t1  a0  0b11        # get opcode
        add     t0  t0  t1          # get funct6 and opcode
        li      t2  0b10001101  # expected funct6=100011 and opcode=01

        beq     t0  t2  c_and_or_xor_sub_matches
        jr      ra      # failed to match, exit the function

    c_and_or_xor_sub_matches:
        srli    t1  a0  5 
        andi    t1  t1  0b11    # get funct2 

        li      t2  0b11    # c.and funct2 is 11
        beq     t1  t2  expand_c_and
        li      t2  0b10    # c.or  funct2 is 10
        beq     t1  t2  expand_c_or
        li      t2  0b01    # c.xor funct2 is 01
        beq     t1  t2  expand_c_xor
        li      t2  0b00    # c.sub funct2 is 00
        beq     t1  t2  expand_c_sub

    expand_c_and:
        li      t0  0   # t0 will store the 32-bit inst result
        li      t1  0b111   # the funct3 of AND is 111
        slli    t1  t1  12  # move to the position of funct3
        or      t0  t0  t1  # fill funct3 (which is 111)
        j       expand_c_and_or_xor_sub_common
    expand_c_or:
        li      t0  0   # t0 will store the 32-bit inst result
        li      t1  0b110   # the funct3 of OR is 110
        slli    t1  t1  12  # move to the position of funct3
        or      t0  t0  t1  # fill funct3 (which is 110)
        j       expand_c_and_or_xor_sub_common
    expand_c_xor:
        li      t0  0   # t0 will store the 32-bit inst result
        li      t1  0b100   # the funct3 of xor is 100
        slli    t1  t1  12  # move to the position of funct3
        or      t0  t0  t1  # fill funct3 (which is 100)
        j       expand_c_and_or_xor_sub_common
    expand_c_sub:
        li      t0  0   # t0 will store the 32-bit inst result
        li      t1  0b0100000   # no funct3 for this, but funct7 is needed
        slli    t1  t1  25  # move to the position of funct7
        or      t0  t0  t1  # fill funct7 (which is 0100000)
        j       expand_c_and_or_xor_sub_common
    
    expand_c_and_or_xor_sub_common:     # the below process is exactly same for the 4 types
        ori     t0  t0  0b0110011   # fill opcode=0110011

        srli    t1  a0  7  
        andi    t1  t1  0b111       # get rd' (which is also rs1') 
        ori     t1  t1  0b01000     # restore common reg name to normal reg name
        slli    t1  t1  7   # move to the position of rd
        or      t0  t0  t1  # fill in rd
        slli    t1  t1  8   # continue move to the position of rs1
        or      t0  t0  t1  # fill in rs1

        srli    t1  a0  2   
        andi    t1  t1  0b111       # get rs2'
        ori     t1  t1  0b01000     # restore common reg name to normal reg name
        slli    t1  t1  20  # move to the position of rs2
        or      t0  t0  t1  # fill rs2

        sw      t0  0(s4)   # store the result
        jr      ra  # exit c_and_or_xor_sub function

c_andi:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  8
        andi    t0  t0  0b1100  # get funct2
        andi    t1  a0  0b11    # get opcode
        or      t0  t0  t1      # get funct2 and opcode
        li      t2  0b1001      # expected funct2=10, opcode=01
        bne     t0  t2  c_andi_exit     # funct2 or opcode not match, exit function

        srli    t0  a0  13
        andi    t0  t0  0b111   # get funct3
        li      t2  0b100       # expected funct3=100
        bne     t0  t2  c_andi_exit     # funct3 not match, exit function

    expand_c_andi:  
        li      t0  0   # t0 will store the 32-bit inst result
        ori     t0  t0  0b0010011   # fill opcode=0010011
        li      t1  0b111
        slli    t1  t1  12
        or      t0  t0  t1          # fill funct3=111

        srli    t1  a0  7
        andi    t1  t1  0b111   # get rd'
        ori     t1  t1  0b01000 # get rd (store the original reg name)
        slli    t1  t1  7       # move to the position of rd
        or      t0  t0  t1      # fill rd
        slli    t1  t1  8       # move to the position of rs1
        or      t0  t0  t1      # fill rs1

        srli    t1  a0  2
        andi    t1  t1  0b11111     # get imm[4:0]
        srli    t2  a0  12
        slli    t2  t2  5
        andi    t2  t2  0b100000    # get imm[5]
        or      t1  t1  t2          # get imm[5:0]

        slli    t1  t1  26
        srai    t1  t1  26  # shift-left and shift-back for sign extension
        slli    t1  t1  20  # move to the position of imm
        or      t0  t0  t1  # fill imm

        sw      t0  0(s4)   # store the result

    c_andi_exit:
        jr      ra  # exit c.andi function

c_srli_srai:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  9
        andi    t0  t0  0b1111100   # get funct3, shamt[5] and 1st bit of funct2
        andi    t1  a0  0b11
        add     t0  t0  t1  # get opcode along with funct3, shamt[5] and funct2 1st bit
        li      t2  0b1000001    # expected opcode and funct3=100 and other=00, op=01

        beq     t0  t2  c_srli_srai_matches
        jr      ra      # failed to match, exit the function

    c_srli_srai_matches:
        srli    t1  a0  10  # prepare for reading funct2
        andi    t1  t1  0b11

        li      t2  0b00 
        beq     t1  t2  expand_c_srli
        li      t2  0b01
        beq     t1  t2  expand_c_srai

    expand_c_srli:
        li      t0  0   # t0 will store the 32-bit inst result 
        j       expand_c_srli_srai_common

    expand_c_srai:
        li      t0  0   # t0 will store the 32-bit inst result
        li      t1  0b0100000
        slli    t1  t1  25
        or      t0  t0  t1  # fill the funct7 (only for srai) 
        j       expand_c_srli_srai_common

    expand_c_srli_srai_common: # they share the operation of rd, rs1, funct3 
        ori     t0  t0  0b0010011   # fill opcode
        li      t1  0b101   # the funct3 for both srli and srai is 101
        slli    t1  t1  12
        or      t0  t0  t1  # fill funct3

        srli    t1  a0  7   # prepare to get rd'
        andi    t1  t1  0b111   # get rd'
        ori     t1  t1  0b01000     # restore the original reg name
        slli    t1  t1  7 
        or      t0  t0  t1  # fill rd

        slli    t1  t1  8   # continue left-shift t1 to fill rs1
        or      t0  t0  t1  # fill rs1

        srli    t1  a0  2   # prepare to get shamt
        andi    t1  t1  0b11111     # get shamt
        slli    t1  t1  20  # move to the imm(shamt) area
        or      t0  t0  t1  # fill shamt

        sw      t0  0(s4)   # store the result
        jr      ra  

c_slli:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  10  
        andi    t0  t0  0b111100    # get funct3 and shamt[5](0)
        andi    t1  a0  0b11
        or      t0  t0  t1  # get funct3, shamt[5] and opcode
        li      t2  0b000010    # expected opcode, funct3 and shamt[5]

        bne     t0  t2  c_slli_exit     # not match, not c.slli

        srli    t0  a0  7
        andi    t0  t0  0b11111     # get rd/rs1
        beqz    t0  c_slli_exit     # rs/rs1 = zero means it's not c.slli

    expand_c_slli:
        li      t0  0   # t0 will store the 32-bit inst result
        ori     t0  t0  0b0010011   # fill opcode
        li      t1  0b001
        slli    t1  t1  12
        or      t0  t0  t1  # fill funct3 (which is 001)

        srli    t1  a0  7
        andi    t1  t1  0b11111     # get rd/rs1
        slli    t1  t1  7
        or      t0  t0  t1  # fill rd
        slli    t1  t1  8
        or      t0  t0  t1  # fill rs1

        srli    t1  a0  2
        andi    t1  t1  0b11111     # get shamt
        slli    t1  t1  20
        or      t0  t0  t1  # fill shamt

        sw      t0  0(s4)   # store the result
    c_slli_exit:
        jr      ra 

c_li:   
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  11 
        andi    t0  t0  0b11100 # get funct3
        andi    t1  a0  0b11
        or      t0  t0  t1  # get funct3 and opcode together
        li      t2  0b01001 # expected funct3=010 and opcode=01

        bne     t0  t2  c_li_exit   # if not match, exit

        srli    t0  a0  7
        andi    t0  t0  0b11111 # get rd/rs1
        beqz    t0  c_li_exit   # if rd/rs1 is zero, it's not c.li

    expand_c_li:
        li      t0  0   # t0 will store the 32-bit inst result
        ori     t0  t0  0b0010011   # fill the opcode

        srli    t1  a0  7
        andi    t1  t1  0b11111     # get the rd
        slli    t1  t1  7
        or      t0  t0  t1      # fill the rd (rs1 no need since it's zero)

        srli    t1  a0  2
        andi    t1  t1  0b11111     # get imm[4:0]
        srli    t2  a0  12
        andi    t2  t2  0b1         # get imm[5]
        slli    t2  t2  5
        or      t1  t1  t2          # get imm[5:0]

        slli    t1  t1  26
        srai    t1  t1  26  # shift-left and shift-back for sign extension
        slli    t1  t1  20  # shift-left to the position of imm
        or      t0  t0  t1  # fill the imm

        sw      t0  0(s4)   # store the result

    c_li_exit:
        jr      ra      # exit the function


c_lui:
        lw      a0  0 (s2)  # a0 = ins[i]
        srli    t0  a0  11  
        andi    t0  t0  0b11100 # get funct3 (should be 011)
        andi    t1  a0  0b11
        or      t0  t0  t1  # get funct3 and opcode together
        li      t2  0b01101 # expected funct3=011 and opcode=01

        bne     t0  t2  c_lui_exit

        srli    t0  a0  7 
        andi    t0  t0  0b11111     # get rd
        beqz    t0  c_lui_exit  # if rd=x0, not c.lui instruction
        li      t2  0b00010 
        beq     t0  t2  c_lui_exit  # if rd=x2, not c.lui instruction

    expand_c_lui:
        li      t0  0   # t0 will store the 32-bit result
        ori     t0  t0  0b0110111   # fill opcode

        srli    t1  a0  7
        andi    t1  t1  0b11111     # get the rd
        slli    t1  t1  7
        or      t0  t0  t1  # fill the rd

        srli    t1  a0  2
        andi    t1  t1  0b11111     # get nzimm[16:12]
        srli    t2  a0  12
        andi    t2  t2  1           # get nzimm[17]
        slli    t2  t2  5
        or      t1  t1  t2  # get nzimm[17:12] (6-bits)

        slli    t1  t1  26
        srai    t1  t1  26  # shift-left and shift-back for sign-extension
        slli    t1  t1  12  # move to the position of imm
        or      t0  t0  t1  # fill the imm

        sw      t0  0(s4)   # store the result

    c_lui_exit:
        jr      ra  # exit the c_lui function

c_addi:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  11
        andi    t0  t0  0b11100     # get funct3(should be 000)
        andi    t1  a0  0b11
        or      t0  t0  t1  # get funct3 and opcode together
        li      t2  0b00001 # expected funct3=000 and opcode=01

        bne     t0  t2  c_addi_exit

        srli    t0  a0  7
        andi    t0  t0  0b11111     # get rd
        beqz    t0  c_addi_exit     # if rd=x0, this is not c.addi 

    expand_c_addi:
        li      t0  0 # t0 will store the 32-bit result
        ori     t0  t0  0b0010011   # fill opcode
        
        srli    t1  a0  7
        andi    t1  t1  0b11111     # get rd (also rs1)
        slli    t1  t1  7
        or      t0  t0  t1  # fill rd
        slli    t1  t1  8
        or      t0  t0  t1  # fill rs1

        srli    t1  a0  2 
        andi    t1  t1  0b11111     # get nzimm[4:0]
        srli    t2  a0  12
        andi    t2  t2  0b1         # get nzimm[5]
        slli    t2  t2  5 
        or      t1  t1  t2  # get nzimm[5:0] (6-bits)

        slli    t1  t1  26
        srai    t1  t1  26  # shift-left and shift-back for sign extension
        slli    t1  t1  20
        or      t0  t0  t1  # fill imm

        sw      t0  0(s4)   # store the result

    c_addi_exit:
        jr      ra  # exit the c.addi function

c_lw:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  11
        andi    t0  t0  0b11100 # get funct3
        andi    t1  a0  0b11    # get opcode
        or      t0  t0  t1      # get funct3 and opcode
        li      t2  0b01000     # expected funct3=010, opcode=00
        bne     t0  t2  c_lw_exit   # fail to match funct3 and opcode, exit

    expand_c_lw:
        li      t0  0   # t0 will store the 32-bit inst result
        ori     t0  t0  0b0000011   # fill opcode=0000011
        li      t1  0b010
        slli    t1  t1  12  # funct3 should be 010
        or      t0  t0  t1  # fill funct3=010

        srli    t1  a0  2
        andi    t1  t1  0b111   # get rd'
        ori     t1  t1  0b01000 # restore original reg name
        slli    t1  t1  7       # move to the position of rd
        or      t0  t0  t1      # fill rd

        srli    t1  a0  7
        andi    t1  t1  0b111   # get rs1'
        ori     t1  t1  0b01000 # restore original reg name
        slli    t1  t1  15      # move to the position of rs1
        or      t0  t0  t1      # fill rs1

        li      t1  0   # let t1 store the offset, init to zero
        srli    t1  a0  6   # offset[2]
        andi    t1  t1  0b1
        slli    t1  t1  2   # move offset[2] to its position
        
        srli    t2  a0  10
        andi    t2  t2  0b111   # get imm[5:3]
        slli    t2  t2  3   # move offset[5:3] to its position
        or      t1  t1  t2  # get offset[5:2]

        srli    t2  a0  5
        andi    t2  t2  0b1     # imm[6]
        slli    t2  t2  6
        or      t1  t1  t2  # get offset[6:2]

        slli    t1  t1  20  # move to the position of imm
        or      t0  t0  t1  # fill imm

        sw      t0  0(s4)   # store the result

    c_lw_exit:
        jr      ra  # exit c.lw function

c_sw:
        lw      a0  0(s2)   # a0 = ins[i]
        srli    t0  a0  11
        andi    t0  t0  0b11100 # get funct3
        andi    t1  a0  0b11
        or      t0  t0  t1      # get funct3 and opcode
        li      t2  0b11000     # expected funct3=110, opcode=00
        bne     t0  t2  c_sw_exit   # fail to match funct3 and opcode, exit

    expand_c_sw:
        li      t0  0   # t0 will store the 32-bit inst result
        ori     t0  t0  0b0100011   # fill opcode=0100011
        li      t1  0b010
        slli    t1  t1  12  # funct3 should be 010
        or      t0  t0  t1  # fill funct3=010

        srli    t1  a0  2
        andi    t1  t1  0b111   # get rs2'
        ori     t1  t1  0b01000 # restore original reg name
        slli    t1  t1  20      # move to the position of rs2
        or      t0  t0  t1      # fill rs2

        srli    t1  a0  7
        andi    t1  t1  0b111   # get rs1'
        ori     t1  t1  0b01000 # restore the original reg name
        slli    t1  t1  15      # move to the position of rs1
        or      t0  t0  t1      # fill rs1

        li      t1  0   # let t1 store the offset, init to zero
        srli    t1  a0  6   
        andi    t1  t1  0b1 # get offset[2]
        slli    t1  t1  2   # move offset[2] to its position

        srli    t2  a0  10
        andi    t2  t2  0b011   # get offset[4:3]
        slli    t2  t2  3   # move offset[4:3] to its position
        or      t1  t1  t2  # get offset[4:2]

        slli    t1  t1  7   # move to the position of imm[4:0]
        or      t0  t0  t1  # fill in imm[4:0]

        li      t1  0
        srli    t1  a0  11
        andi    t1  t1  0b1 # get offset[5]
        srli    t2  a0  5
        andi    t2  t2  0b1 # get offset[6]
        slli    t2  t2  1   # get offset[6] next to offset[5]
        or      t1  t1  t2  # now t1 contains offset[6:5]
        slli    t1  t1  25  # move to the position of imm[11:5]
        or      t0  t0  t1  # fill in imm[11:5]

        sw      t0  0(s4)   # store the result

    c_sw_exit:
        jr      ra  # exit c.sw function



# Exit with error code 0
exit_0:
        li      a1  0 
        li      a0  17
        ecall


final_print:
        la      s0  lines_of_rvc_codes
        lw      s0  0(s0)   # s0 = lines of code
        li      s1  0       # s1 = i
        la      s4  res
        lw      s4  0(s4)   # s4 = &res[0]
        j       final_print_for_check
    final_print_for_body:
        lw      a0  0(s4)   # print res[i] in binary string
        addi    sp  sp  -4
        sw      ra  0(sp)
        jal     print_unsigned_32
        lw      ra  0(sp)
        addi    sp  sp  4

        addi    s1  s1  1   # i++
        addi    s4  s4  4   

    final_print_for_check:
        blt     s1  s0  final_print_for_body
        jr      ra
   

int_to_binary_32:
        li      a2  31   # a2 = i, the initial value is 31
        li      a3  -1   # a3 = -1
        mv      a4  a1   # a4 = &str[0]
    int_to_binary_32_for_body: 
        srl     a5  a0  a2     # a5 = num >> i
        andi    a5  a5  1      # a5 = (num >> i) & 1
        ori     a5  a5  48     # a5 = (num >> i) & 1 + 48
        sb      a5  0(a4)      # str[xx] = a5
        addi    a2  a2  -1     # i--
        addi    a4  a4  1      # adjust a4 to let a4 = &str[15-i]
        bne     a2  a3  int_to_binary_32_for_body   # if (i >= 0) goto forloop_body
        sb      x0  32(a1)     # str[32] = 0
        ret                    # return function

print_unsigned_32:  # takes a 32-bit number from a0 and print it in binary
        addi    sp  sp  -44   # create a space for tmp_str[40] and ra
        sw      ra  40(sp)    # save the original ra
        mv      a1  sp        # a0 keeps the same, while a1 = 0(sp) = &tmp_str[0]
        jal     int_to_binary_32   # call the function to convert it to binary string
        mv      a1  sp    # print out the string
        li      a0  4
        ecall
        li      a1  '\n'  # print the '\n'
        li      a0  11    
        ecall
        lw      ra  40(sp)   # restore the original ra
        addi    sp  sp  44   # restore the stack pointer
        ret                  # return function
