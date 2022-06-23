/*  Project 1.1: RISC-V instructions to RISC-V compressed instructions in C89.
    The following is the starter code provided for you. To finish the task, you 
    should define and implement your own functions in translator.c, compression.c, 
    utils.c and their header files.
    Please read the problem description before you start.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "src/compression.h"
#include "src/utils.h"

#include "translator.h"

/* check if file can be correctly opened */
static int open_files(FILE** input, FILE** output, const char* input_name, const char* output_name){ 
    *input = fopen(input_name, "r");
    if (!*input){  /* open input file failed */
        printf("Error: unable to open input file: %s\n", input_name);
        return -1;
    }
    *output = fopen(output_name, "w");
    if (!*output){  /* open output file failed */
        printf("Error: unable to open output file: %s\n", output_name);
        fclose(*input);
        return -1;
    }
    return 0; /* no problem opening files */
}

/* close the files */
static int close_files(FILE** input, FILE** output){
    fclose(*input);  /* close input file at the end */
    fclose(*output); /* close output file at the end */
    return 0;
}

/* print the usage of program and exit with code 0 */
static void print_usage_and_exit() {
    printf("Usage:\n");
    printf("Run program with translator <input file> <output file>\n"); /* print the correct usage of the program */
    exit(0);
}

/* Run the translator */
int translate(const char *in, const char *out){
    FILE *input, *output;   /* file streams */
    int err;   /* error flag */
    
    /* Calloc a space to store all instructions .
     * Since the memory are initialized to 0, and the invalid type in the enums are defined as 0, 
     * the default state of instructions are 'invalid', making it easier to find errors     */
    Instruction_t *instructs = (Instruction_t*) calloc(sizeof(Instruction_t), MAX_INSTRUCTS);
    /* initialized to 0. During translation, nonzero indicates failure */
    err = 0;

    if (in){    /* correct input file name */
        int count = 0;  /* count how many instructions we have read */
        if(open_files(&input, &output, in, out) != 0)
            exit(1);  /* If input or output failed, exit with error code 1 */
        
        /* read, parse, analyze and translate here */

        /* read in the machine code until reaching an EOF (EndOfFile) */
        while (fscanf(input, "%s", instructs[count].original_ins) != EOF){
            #ifdef debug /* For debug use only: print the machine code inputted */
            /* printf("%s\n", instructs[count].original_ins); */
            #endif
            /* parse */
            parse_instruction(&instructs[count]);
            count++;
        }

        /* After parsing and storing all the instructions, */
        /* It's time to compress them */
        compress(instructs, count);

        /* 
         * To correctly calculate offsets for J, B type instructions,
         * we compress other type of instructions first, 
         * and then J, B instructions.
         */
        /* After all the compression process,
         * we need to write the compressed instructions to the output file */
        /* output the files here */
        write_file(instructs, count, output);

        /* translation process completed, close files */
        close_files(&input, &output);
    }

    /* free the dynamically allocated space here */
    free(instructs);

    return err;
}

/* main func */
int main(int argc, char *argv[]){
    char* input_fname, *output_fname;
    int err;

    if (argc != 3) /* need correct arguments */
        print_usage_and_exit();

    input_fname  = argv[1];
    output_fname = argv[2];
    /* main translation process */
    err = translate(input_fname, output_fname); 
    if (err)
        printf("One or more errors encountered during translation operation.\n"); /* something wrong */
    else
        printf("Translation process completed successfully.\n"); /* correctly output */
    return 0;
}

/*
Git Operations:
git add .                 # add files to temperory area
git commit -m {message}   # message refers to modified contents
git push origin {Branch_name}
git fetch --all
git push origin {Branch_name}
git pull origin {Branch_name}
git checkout {Branch_name} # switch the branch, if(-b) create and switch to the branch
*/

