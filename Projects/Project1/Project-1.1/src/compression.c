#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compression.h"
#include "utils.h"

/* This function compresses acceptable C.ADD instructions to 16-bit */
void compress_c_add(Instruction_t *ins){
    ins->size = two_byte;  /* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "1001", 4);  /* set funct4 to 1001 */
    memcpy(&ins->compressed_ins[4], &ins->rd[0], 5);  /* set rd/rs1 to the corresponding value */
    memcpy(&ins->compressed_ins[9], &ins->rs2[0], 5);  /* set rs2 to the corresponding value */
    memcpy(&ins->compressed_ins[14], "10", 2);  /* set opcode to '10' */
    ins->compressed_ins[16] = '\0';  /* add '\0' at the end of string */
}

/* This function compresses acceptable C.MV instructions to 16-bit. */
void compress_c_mv(Instruction_t *ins){
    ins->size = two_byte;   /* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "1000", 4);   /* set funct4 to 1000 */
    memcpy(&ins->compressed_ins[4], &ins->rd[0], 5);  /* set rd/rs1 to the corresponding value */
    memcpy(&ins->compressed_ins[9], &ins->rs2[0], 5);  /* set rs2 to the corresponding value */
    memcpy(&ins->compressed_ins[14], "10", 2);  /* set opcode to '10' */
    ins->compressed_ins[16] = '\0';  /* add '\0' at the end of string */
}

/* Compress C.AND instructions to 16-bit */
void compress_c_and(Instruction_t *ins){
    /* Note that the common registers' abbreviation are
     * the same as the last 3 characters of the original name,
     * thus directly take out the last 3 characters can complete the map */
    ins->size = two_byte;  /* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "100011", 6);  /* set funct6 to 100011 */
    memcpy(&ins->compressed_ins[6], &ins->rd[2], 3);  /* set rd'/rs1' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[9], "11", 2);  /* set funct 2 to 11 */
    memcpy(&ins->compressed_ins[11], &ins->rs2[2], 3);  /* set rs2' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[14], "01", 2);  /* set opcode to '01' */
    ins->compressed_ins[16] = '\0';  /* add '\0' at the end of string */
}

/* Compress C.OR instructions to 16-bit */
void compress_c_or(Instruction_t *ins){
    /* Note that the common registers' abbreviation are
     * the same as the last 3 characters of the original name
     * thus directly take out the last 3 characters can complete the map */
    ins->size = two_byte;  /* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "100011", 6);  /* set funct6 to 100011 */
    memcpy(&ins->compressed_ins[6], &ins->rd[2], 3);  /* set rd'/rs1' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[9], "10", 2);  /* set funct 2 to 10 */
    memcpy(&ins->compressed_ins[11], &ins->rs2[2], 3);  /* set rs2' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[14], "01", 2);  /* set opcode to '01' */
    ins->compressed_ins[16] = '\0';  /* add '\0' at the end of string */
}

/* Compress C.XOR instructions to 16-bit */
void compress_c_xor(Instruction_t *ins){
    /* Note that the common registers' abbreviation are
     * the same as the last 3 characters of the original name
     * thus directly take out the last 3 characters can complete the map */
    ins->size = two_byte;  /* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "100011", 6);  /* set funct6 to 100011 */
    memcpy(&ins->compressed_ins[6], &ins->rd[2], 3);  /* set rd'/rs1' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[9], "01", 2);  /* set funct 2 to 01 */
    memcpy(&ins->compressed_ins[11], &ins->rs2[2], 3);  /* set rs2' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[14], "01", 2);  /* set opcode to '01' */
    ins->compressed_ins[16] = '\0';  /* add '\0' at the end of string */
}

/* Compress C.SUB instructions to 16-bit */
void compress_c_sub(Instruction_t *ins){
    /* Note that the common registers' abbreviation are
     * the same as the last 3 characters of the original name
     * thus directly take out the last 3 characters can complete the map */
    ins->size = two_byte;  /* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "100011", 6);  /* set funct6 to 100011 */
    memcpy(&ins->compressed_ins[6], &ins->rd[2], 3);  /* set rd'/rs1' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[9], "00", 2);  /* set funct 2 to 00 */
    memcpy(&ins->compressed_ins[11], &ins->rs2[2], 3);  /* set rs2' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[14], "01", 2);  /* set opcode to '01' */
    ins->compressed_ins[16] = '\0';  /* add '\0' at the end of string */
}

/* Compress C.LI instructions to 16-bit */
void compress_c_li(Instruction_t *ins){
    char new_imm[7];
    ins->size = two_byte; /* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "010", 3); /* set funct3 to 010 */
    signed_int_to_bin_6(signed_bin_str_to_int(ins->imm), new_imm);  /* calculated the new immediate (in string) */
    memcpy(&ins->compressed_ins[3], &new_imm[0], 1); /* merge immediate */
    memcpy(&ins->compressed_ins[4], ins->rd, 5); /* set rd to the corresponding value */
    memcpy(&ins->compressed_ins[9], &new_imm[1], 5);
    memcpy(&ins->compressed_ins[14], "01", 2); /* set opcode */
    ins->compressed_ins[16] = '\0'; /* add '\0' at the end of string */
}

/* Compress C.ADDI instructions to 16-bit */
void compress_c_addi(Instruction_t *ins){
    char new_imm[7];
    ins->size = two_byte;/* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "000", 3); /* set funct3 to 010 */
    signed_int_to_bin_6(signed_bin_str_to_int(ins->imm), new_imm);  /* calculated the new immediate (in string) */
    memcpy(&ins->compressed_ins[3], &new_imm[0], 1);/* merge immediate */
    memcpy(&ins->compressed_ins[4], ins->rd, 5);/* set rd to the corresponding value*/
    memcpy(&ins->compressed_ins[9], &new_imm[1], 5);
    memcpy(&ins->compressed_ins[14], "01", 2);/* set opcode */
    ins->compressed_ins[16] = '\0'; /* add '\0' at the end of string */
}

/* Compress C.SLLI instructions to 16-bit */
void compress_c_slli(Instruction_t *ins){
    ins->size = two_byte;/* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "000", 3);/* set funct3 to 010 */
    memcpy(&ins->compressed_ins[3], "0", 1);/* shamt */
    memcpy(&ins->compressed_ins[4], ins->rd, 5);/* set rd to the corresponding value*/
    memcpy(&ins->compressed_ins[9], ins->imm, 5);/* merge immediate */
    memcpy(&ins->compressed_ins[14], "10", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* Compress C.LW instructions to 16-bit */
void compress_c_lw(Instruction_t *ins){
    char new_imm[8];
    ins->size = two_byte;/* mark this instruction as compressible */
    signed_int_to_bin_7(signed_bin_str_to_int(ins->imm), new_imm);
    memcpy(&ins->compressed_ins[0], "010", 3);/* set funct3 to 010 */
    memcpy(&ins->compressed_ins[3], &new_imm[1], 3);/* merge immediate */
    memcpy(&ins->compressed_ins[6], &ins->rs1[2], 3);/* set rs1' (abbreviation) to the corresponding value */
    memcpy(&ins->compressed_ins[9], &new_imm[4], 1);/* merge immediate */
    memcpy(&ins->compressed_ins[10], &new_imm[0], 1);/* merge immediate */
    memcpy(&ins->compressed_ins[11], &ins->rd[2], 3);/* set rd to the corresponding value*/
    memcpy(&ins->compressed_ins[14], "00", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* Compress C.SRLI instructions to 16-bit */
void compress_c_srli(Instruction_t *ins){
    ins->size = two_byte;/* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "100", 3);/* set funct3 to 010 */
    memcpy(&ins->compressed_ins[3], "0", 1);/* shamt */
    memcpy(&ins->compressed_ins[4], "00", 2);
    memcpy(&ins->compressed_ins[6], &ins->rd[2], 3);/* set rd to the corresponding value*/
    memcpy(&ins->compressed_ins[9], ins->imm, 5);/* merge immediate */
    memcpy(&ins->compressed_ins[14], "01", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* Compress C.SRAI instructions to 16-bit */
void compress_c_srai(Instruction_t *ins){
    ins->size = two_byte;/* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "100", 3);/* set funct3 to 010 */
    memcpy(&ins->compressed_ins[3], "0", 1);/* shamt */
    memcpy(&ins->compressed_ins[4], "01", 2);
    memcpy(&ins->compressed_ins[6], &ins->rd[2], 3);/* set rd to the corresponding value*/
    memcpy(&ins->compressed_ins[9], ins->imm, 5);/* merge immediate */
    memcpy(&ins->compressed_ins[14], "01", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* Compress C.ANDI instructions to 16-bit */
void compress_c_andi(Instruction_t *ins){
    char new_imm[7];
    ins->size = two_byte;/* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "100", 3);/* set funct3 to 010 */
    signed_int_to_bin_6(signed_bin_str_to_int(ins->imm), new_imm);
    memcpy(&ins->compressed_ins[3], &new_imm[0], 1);/* merge immediate */
    memcpy(&ins->compressed_ins[4], "10", 2);
    memcpy(&ins->compressed_ins[6], &ins->rd[2], 3);/* set rd to the corresponding value*/
    memcpy(&ins->compressed_ins[9], &new_imm[1], 5);/* merge immediate */
    memcpy(&ins->compressed_ins[14], "01", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* Compress C.SW instructions to 16-bit */
void compress_c_sw(Instruction_t *ins){
    char new_imm[8];
    ins->size = two_byte;/* mark this instruction as compressible */
    signed_int_to_bin_7(signed_bin_str_to_int(ins->imm), new_imm);
    memcpy(&ins->compressed_ins[0], "110", 3);/* set funct3 to 010 */
    memcpy(&ins->compressed_ins[3], &new_imm[1], 3);/* merge immediate */
    memcpy(&ins->compressed_ins[6], &ins->rs1[2], 3);/* set rs1 to the corresponding value*/
    memcpy(&ins->compressed_ins[9], &new_imm[4], 1);/* merge immediate */
    memcpy(&ins->compressed_ins[10], &new_imm[0], 1);/* merge immediate */
    memcpy(&ins->compressed_ins[11], &ins->rs2[2], 3);/* set rs2 to the corresponding value*/
    memcpy(&ins->compressed_ins[14], "00", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* Compress C.LUI instructions to 16-bit */
void compress_c_lui(Instruction_t *ins){
    char new_imm[7];
    ins->size = two_byte;/* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "011", 3);/* set funct3 to 010 */
    signed_int_to_bin_6(signed_bin_str_to_int(ins->imm), new_imm);
    memcpy(&ins->compressed_ins[3], &new_imm[0], 1);/* merge immediate */
    memcpy(&ins->compressed_ins[4], ins->rd, 5);/* set rd to the corresponding value*/
    memcpy(&ins->compressed_ins[9], &new_imm[1], 5);/* merge immediate */
    memcpy(&ins->compressed_ins[14], "01", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* Compress C.JR instructions to 16-bit */
void compress_c_jr(Instruction_t *ins){
    ins->size = two_byte;/* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "1000", 4);
    memcpy(&ins->compressed_ins[4], ins->rs1, 5);/* set rs1 to the corresponding value*/
    memcpy(&ins->compressed_ins[9], "00000", 5);
    memcpy(&ins->compressed_ins[14], "10", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* Compress C.JALR instructions to 16-bit */
void compress_c_jalr(Instruction_t *ins){
    ins->size = two_byte;/* mark this instruction as compressible */
    memcpy(&ins->compressed_ins[0], "1001", 4);
    memcpy(&ins->compressed_ins[4], ins->rs1, 5);/* set rs1 to the corresponding value*/
    memcpy(&ins->compressed_ins[9], "00000", 5);
    memcpy(&ins->compressed_ins[14], "10", 2);/* set opcode */
    ins->compressed_ins[16] = '\0';/* add '\0' at the end of string */
}

/* upper-level function which handles all R-type instructions, 
 * checking whether it can be compressed, 
 * and call the corresponding compressing function if compressible */
void compress_Rtype(Instruction_t *ins){
    /* check which type of R_format the instruction is */
    switch (ins->R) {
        case add:
            if (is_same_rd_rs1(ins)){ /* check if rd and rs1 are the same */
                if (strcmp(ins->rd, "00000") && strcmp(ins->rs2, "00000"))  /* check if rd and rs2 are not x0 */
                    compress_c_add(ins);  /* rd=rs1, rd!=x0 and rs2!=x0 ==> RVC C.ADD format */
            } else if (!strcmp(ins->rs1, "00000")){  /* Check if rs1 is x0 */
                if (strcmp(ins->rd, "00000") && strcmp(ins->rs2, "00000"))  /* Check if rd and rs2 are not x0 */
                    compress_c_mv(ins);   /* rs1=x0, rd and rs2 are not x0 ==> RVC C.MV format. */
            }
            break;
        case and:
            /* Check if registers 'rd', 'rs1' and 'rs2' are in common registers list */
            if (is_common_reg(ins->rd) && is_common_reg(ins->rs1) && is_common_reg(ins->rs2) && is_same_rd_rs1(ins))
                compress_c_and(ins);   /* all registers are common reg, can be compressed */
            break;
        case or:
            /* Check if registers 'rd', 'rs1' and 'rs2' are in common registers list */
            if (is_common_reg(ins->rd) && is_common_reg(ins->rs1) && is_common_reg(ins->rs2) && is_same_rd_rs1(ins))
                compress_c_or(ins);   /* all registers are common reg, can be compressed */
            break;
        case xor:
            /* Check if registers 'rd', 'rs1' and 'rs2' are in common registers list */
            if (is_common_reg(ins->rd) && is_common_reg(ins->rs1) && is_common_reg(ins->rs2) && is_same_rd_rs1(ins))
                compress_c_xor(ins);   /* all registers are common reg, can be compressed */
            break;
        case sub:
            /* Check if registers 'rd', 'rs1' and 'rs2' are in common registers list */
            if (is_common_reg(ins->rd) && is_common_reg(ins->rs1) && is_common_reg(ins->rs2) && is_same_rd_rs1(ins))
                compress_c_sub(ins);
            break;
        default:
            /* This instruction can not be compressed */
            break;
    }
}

/* upper-level function which handles all I-type instructions, 
 * checking whether it can be compressed, 
 * and call the corresponding compressing function if compressible */
void compress_Itype(Instruction_t *ins){
    /* check which type of I_format the instruction is */
    switch (ins->I){
        case addi:
            /* rd!=x0, rs1=x0, -32<=imm<=31          ==> C.LI
             * rd!-x0, rd=rs1, -32<=imm<=31, imm!=0  ==> C.ADDI  */
            if (strcmp(ins->rd, "00000") && !strcmp(ins->rs1, "00000") && signed_bin_str_to_int(ins->imm) >= -32 && signed_bin_str_to_int(ins->imm) <= 31){
                /* check if the immediate is small (can be represented within 5 bits) */
                compress_c_li(ins);
            }  /* check the immediate range and rd*/

            else if (is_same_rd_rs1(ins) && signed_bin_str_to_int(ins->imm) >= -32 && signed_bin_str_to_int(ins->imm) <= 31 && signed_bin_str_to_int(ins->imm) != 0 && strcmp(ins->rd, "00000")){
                compress_c_addi(ins);
            } 
            break;
        case slli:
            /* check the immediate range and rd/rs1 */
            if (is_same_rd_rs1(ins) && strcmp(ins->rd, "00000"))
                compress_c_slli(ins);
            break;
        case lw:
            /* check the immediate range and rd/rs1 */
            if (is_common_reg(ins->rd) && is_common_reg(ins->rs1) && signed_bin_str_to_int(ins->imm) >= 0 && signed_bin_str_to_int(ins->imm) <= 127 && ins->imm[10] == '0' && ins->imm[11] == '0' /* signed_bin_str_to_int(ins->imm)%4 == 0 */)
                compress_c_lw(ins);
            break;
        case srli:
            /* check rd/rs1 and common register */
            if (is_same_rd_rs1(ins) && is_common_reg(ins->rs1))
                compress_c_srli(ins);
            break;
        case srai:
            /* check rd/rs1 and common register */
            if (is_same_rd_rs1(ins) && is_common_reg(ins->rs1))
                compress_c_srai(ins);
            break;
        case andi:
            /* check rd/rs1 and common register and immediate in range */
            if (is_same_rd_rs1(ins) && is_common_reg(ins->rs1) && signed_bin_str_to_int(ins->imm) >= -32 && signed_bin_str_to_int(ins->imm) <= 31)
                compress_c_andi(ins);
            break;
        case jalr:
            /* check rd/rs1 and common register and immediate*/
            if (!strcmp(ins->rd, "00000") && strcmp(ins->rs1, "00000") && signed_bin_str_to_int(ins->imm) == 0)
                compress_c_jr(ins);
                /* check rd/rs1 and common register and immediate */
            else if (!strcmp(ins->rd, "00001") && strcmp(ins->rs1, "00000") && signed_bin_str_to_int(ins->imm) == 0)
                compress_c_jalr(ins);
            /* Finish */
        default:
            break;
    }
}

/* upper-level function which handles all S-type instructions, 
 * checking whether it can be compressed, 
 * and call the corresponding compressing function if compressible */
void compress_Stype(Instruction_t *ins){
    switch (ins->S){
        /* In stype, only sw can be compressed */
        case sw:
            /* check rs1/rs2 common register and immediate in range */
            if (is_common_reg(ins->rs1) && is_common_reg(ins->rs2) && signed_bin_str_to_int(ins->imm) >= 0  && signed_bin_str_to_int(ins->imm) <= 127 && signed_bin_str_to_int(ins->imm)%4 == 0)
                compress_c_sw(ins);
        default:
            break;
            /* Finish */
    }
}

/* upper-level function which handles all U-type instructions, 
 * checking whether it can be compressed, 
 * and call the corresponding compressing function if compressible */
void compress_Utype(Instruction_t *ins){
    switch (ins->U){
        case lui:
            /* includes checking whether the immediate is small enough */
            /* The original imm has 20 bits (signed), 
             * while the compressed imm has only 6 bits (signed, -32~31) */
            if (strcmp(ins->rd, "00000") && strcmp(ins->rd, "00010") && signed_bin_str_to_int(ins->imm) != 0 && signed_bin_str_to_int(ins->imm) >= -32 && signed_bin_str_to_int(ins->imm) <= 31)
                compress_c_lui(ins);
            break;
        default:
        /* Finish */
            break;
    }
}


/* compress B-type instructions at the first loop */
/* Only checks if registers follow the compressable conditions 
 * and mark it as compressable, but will not calculate the offset 
 * The offset are calculated at the second loop */
void compress_Btype_first(Instruction_t *ins){
    switch (ins->B){
        case beq:  /* if rs1 is common register and rs2 = x0, can be compressed */
            if (is_common_reg(ins->rs1) && !strcmp(ins->rs2, "00000"))  ins->size = two_byte;
            break;
        case bne:  /* if rs1 is common register and rs2 = x0, can be compressed */
            if (is_common_reg(ins->rs1) && !strcmp(ins->rs2, "00000"))  ins->size = two_byte;
            break;
            /* Finish */
        default:
            break;
    }
}

/* compress J-type instructions at the first loop */
/* Only checks if registers follow the compressable conditions 
 * and mark it as compressable, but will not calculate the offset 
 * The offset are calculated at the second loop */
void compress_Jtype_first(Instruction_t *ins){
    switch (ins->J){
        case jal:  /* JAL can be compressed if the register is x0 or x1 */
            /* mark the instruction as compressible if rd is x0 or x1 */
            if (!strcmp(ins->rd, "00000"))       ins->size = two_byte;
            else if (!strcmp(ins->rd, "00001"))  ins->size = two_byte; 
            break;
            /* Finish */
        default:
            break;
    }
}

/* compress B-type instructions at the second loop */
/* If this instruction itself is compressible, it calculates the new offset and compress it.
 * If itself is not compressible, it still calculates the new offset,
 * and directly modify the original 32-bit instruction's immediate to adjust the offset */
void compress_Btype_after(Instruction_t instruction[], int index){
    /* We need to check whether it can be compressed by looking at whether the size is 2 or 4 */
    /* If it cannot be compressed, we still need to modify its offset */
    if (instruction[index].size == four_byte){  
        /* variables declaration first */
        int ori_imm, ori_line_of_code, new_imm;
        char new_offset[15];
        new_imm = 0;
        /* get the original immediate (in bytes) */
        ori_imm = signed_bin_str_to_int(instruction[index].imm);
        /* Divide it by 4 gives the lines of code (original) it needs to jump */
        ori_line_of_code = ori_imm / 4;
        /* Scan the code segments and calculate what's the new offset */
        if (ori_line_of_code == 0){
            /* since the offset is zero, we don't need to calculate */
            new_imm = 0;
        } else if (ori_line_of_code > 0){
            /* search downwards */
            /* we need to add itself's length when jumping downwards */
            int k;
            new_imm = 0;
            for (k = index; k < index + ori_line_of_code; k++){
                /* Judge size */
                if      (instruction[k].size == two_byte ) new_imm += 2;
                else if (instruction[k].size == four_byte) new_imm += 4;
            }
        } else if (ori_line_of_code < 0){
            /* search upwards */
            /* no need to add itself's length */
            int k;
            new_imm = 0;
            for (k = index - 1; k >= index + ori_line_of_code; k--){
                /* Judge size */
                if      (instruction[k].size == two_byte ) new_imm -= 2;
                else if (instruction[k].size == four_byte) new_imm -= 4;
            }
        }
        /* set the new offset to original instruction */
        signed_int_to_bin_13(new_imm, new_offset);
        memcpy(&instruction[index].original_ins[0], &new_offset[0], 1);
        memcpy(&instruction[index].original_ins[1], &new_offset[2], 6);
        /* We do this even when it cant be compressed */
        memcpy(&instruction[index].original_ins[20], &new_offset[8], 4);
        memcpy(&instruction[index].original_ins[24], &new_offset[1], 1);
    }
    else {   /* otherwise, the instruction itself is compressible. Compress it */
        /* variables declaration first */
        int ori_imm, ori_line_of_code, new_imm;
        char new_offset[10];
        new_imm = 0;
        /* get the original immediate (in bytes) */
        ori_imm = signed_bin_str_to_int(instruction[index].imm);
        /* Divide it by 4 gives the lines of code (original) it needs to jump */
        ori_line_of_code = ori_imm / 4;
        /* Scan the code segments and calculate what's the new offset */
        if (ori_line_of_code == 0){
            /* since the offset is zero, we don't need to calculate */
            new_imm = 0;
        } else if (ori_line_of_code > 0){
            /* search downwards */
            /* we need to add itself's length when jumping downwards */
            int k;
            new_imm = 0;
            for (k = index; k < index + ori_line_of_code; k++){
                /* Judge size */
                if      (instruction[k].size == two_byte ) new_imm += 2;
                else if (instruction[k].size == four_byte) new_imm += 4;
            }
        } else if (ori_line_of_code < 0){
            /* search upwards */
            /* no need to add itself's length */
            int k;
            new_imm = 0;
            for (k = index - 1; k >= index + ori_line_of_code; k--){
                /* Judge size */
                if      (instruction[k].size == two_byte ) new_imm -= 2;
                else if (instruction[k].size == four_byte) new_imm -= 4;
            }
        }
        /* after getting the new offset, compress it */
        switch (instruction[index].B){
            case beq:
                signed_int_to_bin_9(new_imm, new_offset);
                memcpy(&instruction[index].compressed_ins[0],  "110", 3);/* set funct3 to 010 */
                memcpy(&instruction[index].compressed_ins[3],  &new_offset[0], 1);/* merge offset */
                memcpy(&instruction[index].compressed_ins[4],  &new_offset[4], 2);/* merge offset */
                memcpy(&instruction[index].compressed_ins[6],  &instruction[index].rs1[2], 3);/* set rs1 to the corresponding value*/
                memcpy(&instruction[index].compressed_ins[9],  &new_offset[1], 2);/* merge offset */
                memcpy(&instruction[index].compressed_ins[11], &new_offset[6], 2);/* merge offset */
                memcpy(&instruction[index].compressed_ins[13], &new_offset[3], 1);/* merge offset */
                memcpy(&instruction[index].compressed_ins[14], "01", 2);/* set opcode */
                instruction[index].compressed_ins[16] = '\0';/* add '\0' at the end of string */
                break;
            case bne:
                signed_int_to_bin_9(new_imm, new_offset);
                memcpy(&instruction[index].compressed_ins[0],  "111", 3);/* set funct3 to 010 */
                memcpy(&instruction[index].compressed_ins[3],  &new_offset[0], 1);/* merge offset */
                memcpy(&instruction[index].compressed_ins[4],  &new_offset[4], 2);/* merge offset */
                memcpy(&instruction[index].compressed_ins[6],  &instruction[index].rs1[2], 3);/* set rs1 to the corresponding value*/
                memcpy(&instruction[index].compressed_ins[9],  &new_offset[1], 2);/* merge offset */
                memcpy(&instruction[index].compressed_ins[11], &new_offset[6], 2);/* merge offset */
                memcpy(&instruction[index].compressed_ins[13], &new_offset[3], 1);/* merge offset */
                memcpy(&instruction[index].compressed_ins[14], "01", 2);/* set opcode */
                instruction[index].compressed_ins[16] = '\0';/* add '\0' at the end of string */
                break;
            default:
                break;
        }
    }
}

/* compress J-type instructions at the second loop */
/* If this instruction itself is compressible, it calculates the new offset and compress it.
 * If itself is not compressible, it still calculates the new offset,
 * and directly modify the original 32-bit instruction's immediate to adjust the offset */
void compress_Jtype_after(Instruction_t instruction[], int index){
    /* If it cannot be compressed, we still need to modify its offset */
    if (instruction[index].size == four_byte){
        /* variables declaration first */
        int ori_imm, ori_line_of_code, new_imm;
        char new_offset[25];
        new_imm = 0;
        /* get the original immediate (in bytes) */
        ori_imm = signed_bin_str_to_int(instruction[index].imm);
        /* Divide it by 4 gives the lines of code (original) it needs to jump */
        ori_line_of_code = ori_imm / 4;
        /* Scan the code segments and calculate what's the new offset */
        if (ori_line_of_code == 0){
            /* since the offset is zero, we don't need to calculate */
            new_imm = 0;
        } else if (ori_line_of_code > 0){
            /* search downwards */
            /* we need to add itself's length when jumping downwards */
            int k;
            new_imm = 0;
            for (k = index; k < index + ori_line_of_code; k++){
                /* judge size */
                if      (instruction[k].size == two_byte ) new_imm += 2;
                else if (instruction[k].size == four_byte) new_imm += 4;
            }
        } else if (ori_line_of_code < 0){
            /* search upwards */
            /* no need to add itself's length */
            int k;
            new_imm = 0;
            for (k = index - 1; k >= index + ori_line_of_code; k--){
                /* judge size */
                if      (instruction[k].size == two_byte ) new_imm -= 2;
                else if (instruction[k].size == four_byte) new_imm -= 4;
            }
        }
        /* set the new offset to original instruction */
        signed_int_to_bin_21(new_imm, new_offset);
        memcpy(&instruction[index].original_ins[0],  &new_offset[0], 1);/* merge offset */
        memcpy(&instruction[index].original_ins[1],  &new_offset[10], 10);/* merge offset */
        memcpy(&instruction[index].original_ins[11], &new_offset[9], 1);/* merge offset */
        memcpy(&instruction[index].original_ins[12], &new_offset[1], 8);/* merge offset */

    } else {   /* otherwise, compress it */
        /* variables declaration first */
        int ori_imm, ori_line_of_code, new_imm;
        char new_offset[15];
        new_imm = 0;
        /* get the original immediate (in bytes) */
        ori_imm = signed_bin_str_to_int(instruction[index].imm);
        /* Divide it by 4 gives the lines of code (original) it needs to jump */
        ori_line_of_code = ori_imm / 4;
        /* Scan the code segments and calculate what's the new offset */
        if (ori_line_of_code == 0){
            /* since the offset is zero, we don't need to calculate */
            new_imm = 0;
        } else if (ori_line_of_code > 0){
            /* search downwards */
            /* we need to add itself's length when jumping downwards */
            int k;
            new_imm = 0;
            for (k = index; k < index + ori_line_of_code; k++){
                /* judge size */
                if      (instruction[k].size == two_byte ) new_imm += 2;
                else if (instruction[k].size == four_byte) new_imm += 4;
            }
        } else if (ori_line_of_code < 0){
            /* search upwards */
            /* no need to add itself's length */
            int k;
            new_imm = 0;
            for (k = index - 1; k >= index + ori_line_of_code; k--){
                /* judge size */
                if      (instruction[k].size == two_byte ) new_imm -= 2;
                else if (instruction[k].size == four_byte) new_imm -= 4;
            }
        }
        /* after getting the new offset, compress it */
        if (!strcmp(instruction[index].rd, "00000")){
            /* rd is x0, C.J type instruction */
            signed_int_to_bin_12(new_imm, new_offset);
            memcpy(&instruction[index].compressed_ins[0],  "101", 3);
            memcpy(&instruction[index].compressed_ins[3],  &new_offset[0], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[4],  &new_offset[7], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[5],  &new_offset[2], 2);/* merge offset */
            memcpy(&instruction[index].compressed_ins[7],  &new_offset[1], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[8],  &new_offset[5], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[9],  &new_offset[4], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[10], &new_offset[8], 3);/* merge offset */
            memcpy(&instruction[index].compressed_ins[13], &new_offset[6], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[14], "01", 2);/* set opcode */
            instruction[index].compressed_ins[16] = '\0';/* add '\0' at the end of string */
        } else if (!strcmp(instruction[index].rd, "00001")){
            /* rd is x1, C.JAL type instruction */
            signed_int_to_bin_12(new_imm, new_offset);
            memcpy(&instruction[index].compressed_ins[0],  "001", 3);
            memcpy(&instruction[index].compressed_ins[3],  &new_offset[0], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[4],  &new_offset[7], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[5],  &new_offset[2], 2);/* merge offset */
            memcpy(&instruction[index].compressed_ins[7],  &new_offset[1], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[8],  &new_offset[5], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[9],  &new_offset[4], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[10], &new_offset[8], 3);/* merge offset */
            memcpy(&instruction[index].compressed_ins[13], &new_offset[6], 1);/* merge offset */
            memcpy(&instruction[index].compressed_ins[14], "01", 2);/* set opcode */
            instruction[index].compressed_ins[16] = '\0';/* add '\0' at the end of string */
        }
    }
}

/* This function reads in all instructions, and compress them one by one.
 * It contains two for-loops. 
 * In the first for-loop, R I S U type instructions are fully compressed (if possible),
 * but B and J instructions, though partially compressed, their offsets are not calculated.
 * In the second for-loop, we calculate the new and correct offset of B and J instructions. */
void compress(Instruction_t instruction[], int count){
    int i;
    for (i = 0; i < count; i++){
        if      (instruction[i].format == R_fmt) compress_Rtype(&instruction[i]);/*rtype*/
        else if (instruction[i].format == I_fmt) compress_Itype(&instruction[i]);/*itype*/
        else if (instruction[i].format == S_fmt) compress_Stype(&instruction[i]);/*stype*/
        else if (instruction[i].format == U_fmt) compress_Utype(&instruction[i]);/*utype*/
        else if (instruction[i].format == B_fmt) compress_Btype_first(&instruction[i]);/*bftype*/
        else if (instruction[i].format == J_fmt) compress_Jtype_first(&instruction[i]);/*jftype*/
    }
    /* Compress B and J type instructions at last */
    for (i = 0; i < count; i++){
        /* Compress B format here, which includes calculating the new offset */
        if      (instruction[i].format == B_fmt) compress_Btype_after(instruction, i);/*batype*/
        else if (instruction[i].format == J_fmt) compress_Jtype_after(instruction, i);/*jatype*/
    }
}

/* top-level output function */
/* It is called after the compression process */
/* It checks whether an instruction is compressed or not, and then print it to the file */
void write_file(Instruction_t instruction[], int count, FILE *output){
    int i;
    for (i = 0; i < count; i++){
        /* If the instruction is not compressed, print the original instruction */
        if (instruction[i].size == four_byte)
            fprintf(output, "%s\n", instruction[i].original_ins);
        /* Otherwise, print the compressed instruction */
        else 
            fprintf(output, "%s\n", instruction[i].compressed_ins);
    }
}

