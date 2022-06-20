# Project 2.1: ALU and Regfile

For more details please refer to the [course page](https://robotics.shanghaitech.edu.cn/courses/ca/22s/projects/2.1/).

In this project, you will create an ALU that supports all the operations needed by the instructions in our ISA, and a RegFile which should be able to write to or read from these registers specified in a given RISC-V instruction. 

# Project 2.2: CPU

For more details please refer to the [course page](https://robotics.shanghaitech.edu.cn/courses/ca/22s/projects/2.2/).

In this project you will be using logisim-evolution to implement a 32-bit 2-stage pipelined processor based on RISC-V. The processor must follow the architecture of RISC-V datapath, including 5 stages named Instruction Fetch, Instruction Decode, Execution, Memory and Write Back. Additionally, some key modules like ImmGen, Branch_Comp and Control Logic (the most important module) have to be implemented by yourself with only basic built-in components in Logisim. The ALU and RegFile you’ve implemented in Project 2.1 can be directly utilized in this project.

The processor should be able to parse and execute the given list of RISC-V instructions one after another, and correctly handle the 2-stage pipelined scenario in case a conditional or unconditional jump is taken.

Once you've completed this project, you'll know essentially everything you need to build a computer from scratch with nothing but transistors.
