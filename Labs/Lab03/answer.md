Lab 3 

## Exercise 1

#### 1.What do the `.data`, `.word`, `.text` directives mean (i.e. what do you use them for)? **Hint**: think about the 4 sections of memory.

`.data` refers to the following part that stores the static segment data

`.word` refers to continously storing words (4 byte aligned) in the memory

`.text` refers to the following part that stores the code



#### 2.Run the program to completion. What number did the program output? What does this number represent?

34, the 9th Fibonacci number

#### 3. At what address is `n` stored in memory? **Hint**: Look at the contents of the registers.

0x10000010


#### 4.Without using the “Edit” tab, have the program calculate the 13th fib number (0-indexed) by *manually* modifying the value of a register. You may find it helpful to first step through the code. If you prefer to look at decimal values, change the “Display Settings” option at the bottom.

Set number n to 13（Will be displayed）

## Exercise 2

#### Find/explain the following components of the assembly file and put your answers in a text file.

1. ##### The register representing the variable `k`.

	register `t0` (`x5`)

2. ##### The registers acting as pointers to the `source` and `dest` arrays.

	Source: `t1` is acting as `&source[0]`, `t4` is representing `&source[k]`

	Dest:  `t2` is acting as `&source[0]`, `t6` is representing `&source[k]`

3. ##### The assembly code for the loop found in the C code.

```assembly
loop:
	slli t3, t0, 2
	add t4, t1, t3
	lw t5, 0(t4)
	beq t5, x0, exit
	add t6, t2, t3
	sw t5, 0(t6)
	addi t0, t0, 1
	jal x0, loop
exit:
```

4. ##### How the pointers are manipulated in the assembly code.

	By using `addi` instruction to add 1 on register `t0` (representing `k`)

	[and then multiply it by `4` to get the offset in Bytes, finally add `t1` or `t2` (representing `&source[0]` or `&dest[0]`) to get the actual pointer]

## Exercise 3

Check `factorial.s` for this problem. 

The original c-code is in `factorial.c`

