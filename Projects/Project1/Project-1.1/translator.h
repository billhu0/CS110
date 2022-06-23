#ifndef TRANSLATOR_H
#define TRANSLATOR_H

/* check if file can be correctly opened */
static int open_files(FILE** input, FILE** output, const char* input_name, const char* output_name);
/* close the files */
static int close_files(FILE** input, FILE** output);
/* print the usage of program and exit with code 0 */
static void print_usage_and_exit();
/* Run the translator */
int translate(const char*in, const char*out);


#endif
