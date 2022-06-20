### Exercise 2 (cgdb)

1. How do you pass command line arguments to a program when using gdb?

Ans: using 'run arg1 arg2....'

2. How do you set a breakpoint which only occurs when a set of conditions is true (e.g. when certain variables are a certain value)?

Ans: using "break [line_number] if [expr]"

3. How do you execute the next line of C code in the program after stopping at a breakpoint?

Ans:use "n" to continue for next line, stepping over function calls

4. If the next line of code is a function call, you'll execute the whole function call at once if you use your answer to #3. (If not, consider a different command for #3!) How do you tell GDB that you want to debug the code inside the function instead? (If you changed your answer to #3, then that answer is most likely now applicable here.)

Ans: use "s" is the same as "n" except that it steps into function calls

5. How do you resume the program after stopping at a breakpoint?

Ans: "c" or "continue"

6. How can you see the value of a variable (or even an expression like 1+2) in gdb?

Ans: use "p [var]" (for instance, "p count" to display the value of variable "count", "p 1+2" to see the value of expression '1+2')


7. How do you configure gdb so it prints the value of a variable after every step?

Ans: "display [param]" 

WRONG ANSWER: we can "watch" this variable. For instance, use "watch *p" to get the value of *p every time it changes after executing one code.

8. How do you print a list of all variables and their values in the current function?

Ans: "info stack full" shows the current stack along with all vars on stack "info locals"

9. How do you exit out of gdb?

Ans: Use 'quit' or 'q'
