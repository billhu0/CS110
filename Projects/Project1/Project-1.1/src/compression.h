#ifndef COMPRESSION_H
#define COMPRESSION_H

/* Your code here... */

#include "utils.h"

/* NOTE: THE DETAILED DESCRIPTION OF THESE FUNCTIONS 
 * ARE PRESENT IN THE .c FILE */

/* R type compressions */
void compress_c_add (Instruction_t *ins);
void compress_c_mv  (Instruction_t *ins);
void compress_c_and (Instruction_t *ins);
void compress_c_or  (Instruction_t *ins);
void compress_c_xor (Instruction_t *ins);
void compress_c_sub (Instruction_t *ins);

/* I type compressions */
void compress_c_li  (Instruction_t *ins);
void compress_c_addi(Instruction_t *ins);
void compress_c_slli(Instruction_t *ins);
void compress_c_lw  (Instruction_t *ins);
void compress_c_srli(Instruction_t *ins);
void compress_c_srai(Instruction_t *ins);
void compress_c_andi(Instruction_t *ins);
void compress_c_jr  (Instruction_t *ins);
void compress_c_jalr(Instruction_t *ins);

/* S type compressions */
void compress_c_sw  (Instruction_t *ins);

/* U type compressions */
void compress_c_lui (Instruction_t *ins);


/* ALL */
void compress_Rtype (Instruction_t *ins);
void compress_Itype (Instruction_t *ins);
void compress_Stype (Instruction_t *ins);
void compress_Utype (Instruction_t *ins);
/* B and Jtype compressions */
void compress_Btype_first(Instruction_t *ins);
void compress_Jtype_first(Instruction_t *ins);
void compress_Btype_after(Instruction_t instruction[], int index);
void compress_Jtype_after(Instruction_t instruction[], int index);

/* top-level compress function */
void compress  (Instruction_t instruction[], int count);

/* top-level file output function */
void write_file(Instruction_t instruction[], int count, FILE *output);

#endif
