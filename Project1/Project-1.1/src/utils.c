#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h" 

/* 
 * This function gets the instruction type (R I S B U J)
 * from the last 7 characters of the machine code.
 * It then sets the item "format" in the struct to the corresponding format.
 */
void get_instruction_format(Instruction_t *ins){
    char opcode[8];   /* Create a temporary buffer */
    /* Get the last 7 chars and added \0 at the end */
    memcpy(opcode, &ins->original_ins[25], 7);  
    opcode[7] = '\0';  /* add '\0' at the end of string */
    /* Judge the instruction type from the opcode */
    if      (!strcmp(opcode, "0110011")) ins->format = R_fmt;
    else if (!strcmp(opcode, "0010011")) ins->format = I_fmt; /* arithmetic I */
    else if (!strcmp(opcode, "0000011")) ins->format = I_fmt; /* load I */
    else if (!strcmp(opcode, "0100011")) ins->format = S_fmt; /* S format */
    else if (!strcmp(opcode, "1100011")) ins->format = B_fmt; /* B format */
    else if (!strcmp(opcode, "0110111")) ins->format = U_fmt; /* LUI */
    else if (!strcmp(opcode, "0010111")) ins->format = U_fmt; /* AUIPC */
    else if (!strcmp(opcode, "1101111")) ins->format = J_fmt; /* JAL */
    else if (!strcmp(opcode, "1100111")) ins->format = I_fmt; /* JALR */
    /* If none of the above fits (not recognized type). This instruction is invalid */
}

/*
 * This function gets 'rd' from instruction string and store it.
 * It works because as long as an instruction has rd,
 * it is always placed in the same position.
 */
void get_rd(Instruction_t *ins){
    memcpy(ins->rd, &ins->original_ins[20], 5);  /* copy the 'rd' string from instruction */
    ins->rd[5] = '\0';  /* added a '\0' at the end of string */
}

/* Like the 'get_rd()' func, this function gets the rs1 from instruction */
void get_rs1(Instruction_t *ins){
    memcpy(ins->rs1, &ins->original_ins[12], 5);  /* copy the 'rs1' string from instruction */
    ins->rs1[5] = '\0';  /* added a '\0' at the end of string */
}

/* Like the 'get_rd()' func, this function gets the rs2 from instruction */
void get_rs2(Instruction_t *ins){
    memcpy(ins->rs2, &ins->original_ins[7], 5);  /* copy the 'rs2' string from instruction */
    ins->rs2[5] = '\0';  /* added a '\0' at the end of string */
}


/* This function handles R-type instructions,
 * juding what type it is, 'extract' the rd, rs1 and rs2, and store it. */
void parse_Rtype(Instruction_t *ins){
    /* get funct3 from the instruction */
    char tmp[10];
    memcpy(tmp, &ins->original_ins[17], 3);
    tmp[3] = '\0';

    /* judge what instruction it is */
    if (!strcmp(tmp, "000")){  /* add or sub type, look at funct7 for further observation */
        if      (ins->original_ins[1] == '0') { ins->R = add; } 
        else if (ins->original_ins[1] == '1') { ins->R = sub; }
    }/* execpt from add and sub, others can be configued by 17-19 */
    else if (!strcmp(tmp, "001")) { ins->R = sll; } /*sll*/
    else if (!strcmp(tmp, "010")) { ins->R = slt; } /*slt*/
    else if (!strcmp(tmp, "011")) { ins->R = sltu;} /*sltu*/
    else if (!strcmp(tmp, "100")) { ins->R = xor; } /*xor*/
    else if (!strcmp(tmp, "101")){   /* srl or sra type, look at funct7 for further observation */
        if      (ins->original_ins[1] == '0'){ ins->R = srl; } /*srl*/
        else if (ins->original_ins[1] == '1'){ ins->R = sra; } /*sra*/
    } /*or and and share the same 0-6 but can be different in 17-19*/
    else if (!strcmp(tmp, "110")) { ins->R = or;  } 
    else if (!strcmp(tmp, "111")) { ins->R = and; }

    /* Then, find the rd, rs1 and rs2 by calling the above functions */
    get_rd (ins);
    get_rs1(ins);
    get_rs2(ins);

    /* And we are done */
}

/* This function handles I-type instructions,
 * juding what type it is and 'extract' the rd, rs1 and imm */
void parse_Itype(Instruction_t *ins){
    /* first, check the last seven characters again to judge 
       whether it is 'load' instructions or not */
    char tmp[10];
    memcpy(tmp, &ins->original_ins[25], 7);
    tmp[7] = '\0';
     /* jalr instruction */
    if (!strcmp(tmp, "1100111")){ 
        ins->I = jalr;
        /* get rd rs1 */
        get_rd(ins);
        get_rs1(ins);
        /* get immediate */
        memcpy(&ins->imm[0], &ins->original_ins[0], 12);
        ins->imm[12] = '\0';
        /* We use memcpy instead of strcpy due to the fact that strcpy has an annoying ending of '\0'*/
    }
    else if (!strcmp(tmp, "0010011")){
        /* arithmetic instruction */
        /* check funct3 to judge its type */
        memcpy(tmp, &ins->original_ins[17], 3);   /* get funct3 from the instruction */
        tmp[3] = '\0';
        /* The following are configued by 17-19 */
        if      (!strcmp(tmp, "000")) { ins->I = addi; } /*addi*/
        else if (!strcmp(tmp, "010")) { ins->I = slti; } /*alti*/
        else if (!strcmp(tmp, "011")) { ins->I = sltiu;} /*sltiu*/
        else if (!strcmp(tmp, "100")) { ins->I = xori; } /*xori*/
        else if (!strcmp(tmp, "110")) { ins->I = ori;  } /*ori*/
        else if (!strcmp(tmp, "111")) { ins->I = andi; } /*andi*/
        else if (!strcmp(tmp, "001")) { ins->I = slli; } /*alli*/
        else if (!strcmp(tmp, "101")){  /* the instruction is 'srli' or 'srai'*/
            /* judge between 'srli' and 'srai' by checking the 2nd character */
            if (ins->original_ins[1] == '0') { ins->I = srli; } 
            else                             { ins->I = srai; }
        }
    } else {  /* the instruction is 'load' */
        /* check funct3 for information on the size and 'signedness' of load data */
        memcpy(tmp, &ins->original_ins[17], 3);   /* get funct3 from the instruction */
        tmp[3] = '\0';
        if      (!strcmp(tmp, "000")) { ins->I = lb; } /*lb*/
        else if (!strcmp(tmp, "001")) { ins->I = lh; } /*lh*/
        else if (!strcmp(tmp, "010")) { ins->I = lw; } /*lw*/
        else if (!strcmp(tmp, "100")) { ins->I = lbu;} /*lbu*/
        else if (!strcmp(tmp, "101")) { ins->I = lhu;} /*lhu*/
    }
    /* Get the 'rd' and 'rs1' from the instruction */
    get_rd (ins);
    get_rs1(ins);
    /* get the immediate from the instruction by memcpy */
    /* if the instruction is slli, srli or srai, immediate has only five bits */
    if (ins->I == slli || ins->I == srli || ins->I == srai) {
        memcpy(ins->imm, &ins->original_ins[7], 5);  /* shamt (shift amount) */
        ins->imm[5] = '\0';  
    } else {
        memcpy(ins->imm, &ins->original_ins[0], 12); /* whole immediate */
        ins->imm[12] = '\0';
    }
}

/* This function handles S-type instructions,
 * juding what type it is and 'extract' the rs1, rs2 and imm */
void parse_Stype(Instruction_t *ins){
    /* S-type is rather simple, since we only need to check funct3 */
    char tmp[5];
    memcpy(tmp, &ins->original_ins[17], 3); 
    /* get funct3 from the instruction */
    tmp[3] = '\0';
    if      (!strcmp(tmp, "000")) { ins->S = sb; } 
    else if (!strcmp(tmp, "001")) { ins->S = sh; } 
    else if (!strcmp(tmp, "010")) { ins->S = sw; } 
    /* get rs1 and rs2 */
    get_rs1(ins);
    get_rs2(ins);
    /* get immediate */
    /* Since the Imm[11:5] and Imm[4:0] are not stored continously */
    /* we need to get them one after another */
    memcpy(&ins->imm[0], &ins->original_ins[0], 7);
    memcpy(&ins->imm[7], &ins->original_ins[20], 5);
    ins->imm[12] = '\0';
    /* end with a extra \0 */
}

void parse_Btype(Instruction_t *ins){
    /* Get funct3 */
    char tmp[10];
    memcpy(tmp, &ins->original_ins[17], 3);
    tmp[3] = '\0';
    /* this type can be completely configured by func3(17-19) */
    if      (!strcmp(tmp, "000")) { ins->B = beq; } /*beq*/
    else if (!strcmp(tmp, "001")) { ins->B = bne; } /*bne*/
    else if (!strcmp(tmp, "100")) { ins->B = blt; } /*blt*/
    else if (!strcmp(tmp, "101")) { ins->B = bge; } /*bge*/
    else if (!strcmp(tmp, "110")) { ins->B = bltu;} /*bltu*/
    else if (!strcmp(tmp, "111")) { ins->B = bgeu;} /*bgeu*/
    /* get rs1 and rs2 */
    get_rs1(ins);
    get_rs2(ins);
    /* get immediate */
    ins->imm[0] = ins->original_ins[0];
    ins->imm[1] = ins->original_ins[24];
    memcpy(&ins->imm[2], &ins->original_ins[1], 6);
    memcpy(&ins->imm[8], &ins->original_ins[20], 4);
    /* The B-type instruction stores IMM with unit 2-bytes,
     * indicating an omitted 0 in the end */
    memcpy(&ins->imm[12], "0", 1);
    ins->imm[13] = '\0';
}

void parse_Utype(Instruction_t *ins){
    /* shouheng please do this */
    char tmp[10];
    memcpy(tmp, &ins->original_ins[25],7);
    tmp[7] = '\0';
    /* Utype is configured by its opcode(25-31) */
    if      (!strcmp(tmp, "0110111")) { ins->U = lui;  }
    else if (!strcmp(tmp, "0010111")) { ins->U = auipc;}
    get_rd(ins);   /* get rd */
    memcpy(&ins->imm[0], &ins->original_ins[0], 20);  /* get immediate */
    ins->imm[20] = '\0';
}

void parse_Jtype(Instruction_t *ins){
    /* TODO: shouheng please do this */
    /* char tmp[10]; */
    /* memcpy(tmp, &ins->original_ins[25],7); */
    /* tmp[7] = '\0'; */
    /* if      (!strcmp(tmp, "1101111")) { ins->J = jal; } */
    /* else if (!strcmp(tmp, "1100111")) { ins->J = jalr; } */
    /* if (ins->J == jal){ */

    /* Only 'JAL' belongs to J-type */
    ins->J = jal;
    
    get_rd(ins);  /* get rd */
    /* get immediate */
    ins->imm[0] = ins->original_ins[0];
    /* respectively merge the immediate in offset */
    memcpy(&ins->imm[0], &ins->original_ins[0], 1);
    memcpy(&ins->imm[1], &ins->original_ins[12], 8);
    memcpy(&ins->imm[9], &ins->original_ins[11], 1);
    memcpy(&ins->imm[10], &ins->original_ins[1], 10);
    /* JAL instruction stores the imm with 2-byte unit, 
     * indicating a hidden '0' at the end */
    memcpy(&ins->imm[20], "0", 1);
    ins->imm[21] = '\0';
    
    
    /* else if (ins->J == jalr){ */
        /* get rd rs1 */
        /* get_rd(ins); */
        /* get_rs1(ins); */
        /* get immediate */
        /* memcpy(&ins->imm[0], &ins->original_ins[0], 11); */
        /* ins->imm[12] = '\0'; */
    /* } */
    
}


int parse_instruction(Instruction_t *ins){
    /* first, get the last 7 bits of the instruction and judge its format */
    get_instruction_format(ins);
    switch (ins->format) {
        case R_fmt:  parse_Rtype(ins); break;  /* parse R-type instructions */
        case I_fmt:  parse_Itype(ins); break;  /* parse I-type instructions */
        case S_fmt:  parse_Stype(ins); break;  /* parse S-type instructions */
        case B_fmt:  parse_Btype(ins); break;  /* parse B-type instructions */
        case U_fmt:  parse_Utype(ins); break;  /* parse U-type instructions */
        case J_fmt:  parse_Jtype(ins); break;  /* parse J-type instructions */
        default:
            /* #ifdef debug */
            /* printf("Invalid instruction !"); */
            /* #endif */
            break;
    }
    if (ins->format == Invalid) return -1;  /* not recognized operator. Abort. */
    return 0;
}

/* This function checks whether the register (in string format) is x8-x15 or not
 * If so, it returns true, otherwise return false */
bool is_common_reg(char reg[]){
    int i;
      /* x8 -x15 */
    char *common_registers[] = {
        "01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111"
    };
    /* judge common registers */
    for (i = 0; i < 8; i++)
        if (!strcmp(reg, common_registers[i])) return true;
    return false;
}

/* This function checks whether rd and rs1 of an instruction are the same */
bool is_same_rd_rs1(Instruction_t *ins){
    return (!strcmp(ins->rd, ins->rs1));
}

/* calculates the 'radix' to the 'exponent'-th power */
/* Warning: this function only works for non-negative exponent */
int power(int radix, int exponent){
    int i, result = 1;
    for (i = 0; i < exponent; i++) result *= radix;
    return result;
}

/* converts binary number (in string) to int, treating the number as unsigned */
int unsigned_bin_str_to_int(char bin_str[]){
    /* declare variables first */
    size_t i, len;
    int result;
    len = strlen(bin_str); 
    /* get the length of string */
    result = 0;
    for (i = 0; i < len; i++) 
    /* repeatedly add the corresponding bit of value to result */
        result += power(2, len-i-1) * (bin_str[i] - '0');
    return result;
}

/* converts binary number (in string) to int, treating the number as signed */
int signed_bin_str_to_int(char bin_str[]){
    /* declare variables first */
    size_t i, len;
    int result;
    len = strlen(bin_str); 
    /* get the length of string */
    result = 0;
    /* repeatedly add the corresponding bit of value to result */
    for (i = 1; i < len; i++)   /* ignore the sign bit temporarily */
        result += power(2, len-i-1) * (bin_str[i] - '0');
    /* consider the affect of the sign bit */
    result -= (bin_str[0] - '0') * power(2, len-1);
    return result;
}


/* converts signed integer to binary number, and print it into a string */
/* 6-bits are able to hold -32 ~ 31 */
void signed_int_to_bin_6(int number, char imm[7]){
    int i;
    memset(imm, 0, sizeof(char) * 7);
    /* initialize */
    if (number >= 0){
        for (i = 0; i < 6; i++){
            /* use and operation */
            imm[5-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
    } else if (number < 0){
        /* inverse */
        number = -number - 1;
        /* loop */
        for (i = 0; i <= 5; i++){
            imm[5-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
        /* conveniently use ternary operator */
        for (i = 0; i <= 5; i++) imm[i] = (imm[i] == '1')? '0':'1';
    }
    imm[6] = '\0';
    /* end with an extra \0 */
}


/* converts signed integer to binary number, and print it into a string */
/* 7-bits are able to hold -64 ~ 63 */
void signed_int_to_bin_7(int number, char imm[8]){
    int i;
    memset(imm, 0, sizeof(char) * 8);
    /* initialize */
    if (number >= 0){
        for (i = 0; i < 7; i++){
            /* use and operation */
            imm[6-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
    } else if (number < 0){
        /* inverse */
        number = -number - 1;
        /* loop */
        for (i = 0; i <= 6; i++){
            imm[6-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
        /* conveniently use ternary operator */
        for (i = 0; i <= 6; i++)
            imm[i] = (imm[i] == '1')? '0':'1';
    }
    imm[7] = '\0';
    /* end with an extra \0 */
}

/* converts signed integer to binary number, and print it into a string */
/* 9-bits are able to hold -256 ~ 255 */
void signed_int_to_bin_9(int number, char imm[10]){
    int i;
    memset(imm, 0, sizeof(char) * 10);
    /* initialize */
    if (number >= 0){
        for (i = 0; i < 9; i++){
            /* use and operation */
            imm[8-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
    } else if (number < 0){
        /* inverse */
        number = -number - 1;
        /* loop */
        for (i = 0; i <= 8; i++){
            imm[8-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
        /* conveniently use ternary operator */
        for (i = 0; i <= 8; i++)
            imm[i] = (imm[i] == '1')? '0':'1';
    
    }
    imm[9] = '\0';
    /* end with an extra \0 */
}

void signed_int_to_bin_12(int number, char imm[13]){
    int i;
    memset(imm, 0, sizeof(char) * 13);
    /* initialize */
    if (number >= 0){
        for (i = 0; i < 12; i++){
            /* use and operation */
            imm[11-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
    } else if (number < 0){
        /* inverse */
        number = -number - 1;
        /* loop */
        for (i = 0; i <= 12; i++){
            imm[11-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
        /* conveniently use ternary operator */
        for (i = 0; i <= 12; i++)
            imm[i] = (imm[i] == '1')? '0':'1';
        
    }
    imm[12] = '\0';
    /* end with an extra \0 */
}

void signed_int_to_bin_13(int number, char imm[14]){
    int i;
    memset(imm, 0, sizeof(char) * 14);
    /* initialize */
    if (number >= 0){
        for (i = 0; i < 13; i++){
            /* use and operation */
            imm[12-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
    } else if (number < 0){
        /* inverse */
        number = -number - 1;
        /* loop */
        for (i = 0; i <= 12; i++){
            imm[12-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
        /* conveniently use ternary operator */
        for (i = 0; i <= 12; i++)
            imm[i] = (imm[i] == '1')? '0':'1';
        
    }
    imm[13] = '\0';
    /* end with an extra \0 */
}

void signed_int_to_bin_21(int number, char imm[22]){
    int i;
    memset(imm, 0, sizeof(char) * 22);
    /* initialize */
    if (number >= 0){
        for (i = 0; i < 21; i++){
            /* use and operation */
            imm[20-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
    } else if (number < 0){
        /* inverse */
        number = -number - 1;
        /* loop */
        for (i = 0; i <= 20; i++){
            imm[20-i] = ((number & 1) == 1)? '1':'0';
            number >>= 1;
        }
        /* conveniently use ternary operator */
        for (i = 0; i <= 20; i++)
            imm[i] = (imm[i] == '1')? '0':'1';
        
    }
    imm[21] = '\0';
    /* end with an extra \0 */
}