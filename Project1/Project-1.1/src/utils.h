#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* There are at most 50 input instructions */
#define MAX_INSTRUCTS 64

/* Your code here... */

/* TODO: remember to remove debug flag before submitting to autolab */
/* This enables more informative outputs for debug use */


/* Enumerate all the instruction formats and operations */
typedef enum {
    Invalid = 0, R_fmt, I_fmt, S_fmt, B_fmt, J_fmt, U_fmt
} Instruction_format;

/* Enumerate all Register type instructions */
typedef enum {
    Invalid_r = 0, add, sub, sll, slt, sltu, xor, srl, sra, or, and
} R_type;

/* Enumerate all immediate type instructions */
typedef enum {
    Invalid_i = 0, addi, slti, sltiu, xori, ori, andi, slli, srli, srai,  /* arithmetic instructions */
    lb, lh, lw, lbu, lhu,  /* load instructions */
    jalr /* jalr instruction is also I-type */
} I_type;

/* Enumerate all Store type instructions */
typedef enum {
    Invalid_s = 0, sb, sh, sw
} S_type;

/* Enumerate all conditional branch type instructions */
typedef enum {
    Invalid_b = 0, beq, bne, blt, bge, bltu, bgeu
} B_type;

/* Enumerate all upper-immediate type instructions */
typedef enum {
    Invalid_u = 0, lui, auipc
} U_type;

/* Enumerate all jump type instructions */
typedef enum {
    Invalid_j = 0, jal
} J_type;

/* typedef a flag for marking 16bit or 32bit instructions */
/* TODO: this might be removed */
typedef enum {
    two_byte = 1, four_byte = 0
} Compressed_size;

/* define a struct type to store instructions in an analyzed type */
typedef struct {
    /* analyzed instruction formats */
    Instruction_format format;  /* Store the type (R/I/S/B/U/J) */
    R_type R;  /* for R-type instructions use only */
    I_type I;  /* for I-type instructions use only */
    S_type S;  /* for S-type instructions use only */
    B_type B;  /* for B-type instructions use only */
    U_type U;  /* for U-type instructions use only */
    J_type J;  /* for J-type instructions use only */
    char rd [7];   /* store 'rd'  in string */
    char rs1[7];   /* store 'rs1' in string */
    char rs2[7];   /* store 'rs2' in string */
    char imm[25];  /* store 'imm' in string */
    /* machine code of original instruction and compressed instruction */
    Compressed_size size;    /* Store the compressed size, either 2-bytes or 4-bytes */
    char original_ins  [64]; /* Store the original instruction in string */
    char compressed_ins[18]; /* Store the compressed instruction in string if compressible */
} Instruction_t;

/* 
 * This function gets the instruction type (R I S B U J)
 * from the last 7 characters of the machine code.
 * It then sets the item "format" in the struct to the corresponding format.
 */
void get_instruction_format(Instruction_t *ins);

/*
 * This function gets 'rd' from instruction string and store it.
 * It works because as long as an instruction has rd,
 * it is always placed in the same position.
 */
void get_rd(Instruction_t *ins);

/* Like the 'get_rd()' func, this function gets the rs1 from instruction */

void get_rs1(Instruction_t *ins);
/* Like the 'get_rd()' func, this function gets the rs2 from instruction */
void get_rs2(Instruction_t *ins);


/* 
 * This function can handle R-type instructions,
 * judging what type it is and 'extract' the rd, rs1 and rs2
 */
void parse_Rtype(Instruction_t *ins);

/* 
 * This function can handle I-type instructions,
 * judging what type it is and 'extract' the rd, rs1 and imm
 */
void parse_Itype(Instruction_t *ins);

/* 
 * This function can handle S-type instructions,
 * judging what type it is and 'extract' the rs1, rs2 and imm
 */
void parse_Stype(Instruction_t *ins);

void parse_Btype(Instruction_t *ins);

void parse_Utype(Instruction_t *ins);

void parse_Jtype(Instruction_t *ins);

int parse_instruction(Instruction_t *ins);

/* This functions checks whether the register (in string format) is x8-x15 or not
 * If so, it returns true, otherwise return false */
bool is_common_reg(char reg[]);

/* This function checks whether rd and rs1 of an instruction are the same */
bool is_same_rd_rs1(Instruction_t *ins);

int power(int radix, int exponent);
int unsigned_bin_str_to_int(char bin_str[]);
int signed_bin_str_to_int(char bin_str[]);

/* converts signed integer to binary number, and print it into a string */
/* 6-bits are able to hold -32 ~ 31 */
void signed_int_to_bin_6(int number, char imm[7]);
void signed_int_to_bin_7(int number, char imm[8]);
/* converts signed integer to binary number, and print it into a string */
/* 9-bits are able to hold -256 ~ 255 */
void signed_int_to_bin_9(int number, char imm[10]);
void signed_int_to_bin_12(int number, char imm[13]);
void signed_int_to_bin_13(int number, char imm[14]);
void signed_int_to_bin_21(int number, char imm[22]);
#endif
