'''
This file scans for comments begin with '//' and convert it into '/*  */' format
since the ANSI C (C89) standard accepts only '/* */' comments.
'''

import os

input_file = "ringbuffer.c"

if __name__ == '__main__':
    input = open(input_file, 'r')
    output = open(input_file+"1", 'w+')
    
    lines = input.read().split('\n')
    i = 0
    lines_len = len(lines)
    
    while i < lines_len:
        line = lines[i]
        if line.find("//") != -1:
            tmp = line.find("//")
            # print("// comment detected")
            line = line.replace("//", '/*')
            line += ' */'
            # print("linestart:{}:lineend".format(line))
        lines[i] = line
        output.write(line + '\n')
        i+=1
        
    input.close()
    output.close()
    
    os.system("rm {}".format(input_file))
    os.system("mv {} {}".format(input_file+"1", input_file))

