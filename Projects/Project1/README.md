# Project1.1: Translator from RV32I to RVC

For more details please refer to the [course page](https://robotics.shanghaitech.edu.cn/courses/ca/22s/projects/1.1/).

In this part of the project, you will be writing an translator that translates RISC-V instructions to RISC-V compressed instructions. The RISC-V standard compressed instruction set extension (called RVC for shorthand) offers 16-bit versions of common 32-bit RISC-V instructions, thus reducing the binary code size. Note that not all RISC-V instructions can be compressed. RVC scheme offers compression to a 32-bit RISC-V instruction when:

- The immediate or address offset is small, or
- one of the registers is the zero register (x0), or
- the destination register and the first source register are identical, or
- the registers used are the 8 most popular ones.

In this project this process is a part of the assembler's job - even though in practical systems a good compression ratio can only be achieved if the compiler is aware of the compression. To simplify the task, assume each RISC-V instruction from compiler is already translated into 32-bit RISC-V binary instruction. So your job is to take an input file consisting of 32-bit RISC-V binary instructions, and output the compressed machine code. Since not all RISC-V instructions can be compressed, your output will be a mix of 32-bit and 16-bit instructions. This is also the reason why the offsets in the jumps we saw in class are scaled by two rather than four.

In general, the compression process has the following steps:

1. Parse the input 32-bit RISC-V instructions line by line.
2. Check if it can be compressed. If not, you should write the 32-bit without compression to the output file. If it can be compressed, compress it to the corresponding 16-bit RVC instruction and write it to the output file.
3. However, since some lines are compressed into 16-bits, original jump offsets need to be updated. You can use another pass to deal with it.

# Project1.2: Translator from RVC to RV32I

For more details please refer to the [course page](https://robotics.shanghaitech.edu.cn/courses/ca/22s/projects/1.2/).

In project 1.2, you will implement a translator that converts 16-bit RISC-V Compressed (RVC) instructions to equivalent 32-bit RISC-V instructions. Instructions are provided and output in binary form. This project is easy if you gain sufficient understanding of RISC-V from the courses, Lab 3, Lab 4 and its compressed instruction set extension from Project1.1.

To simplify the implementation, all RVC instructions map to a single existing RISC-V instruction. In this project, you only need to translate part of RVC instructions that are mentioned in Project 1.1.