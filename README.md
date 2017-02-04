# simple-CPU-in-c-
simulate a very simple CPU in c++ language


Move instructions
MOV reg, reg
MOV reg, constant

For example MOV R1, R2 copies the value of register 1 to register 2
and MOV R1, 100 puts the value of 100 to register 1


Addition and Subtraction insructions
ADD reg, reg
ADD reg, constant
SUB reg, reg
SUB reg, constant
For example, ADD R1, R2 adds the value of register 2 to register 1
and ADD R1, 100 adds the value of 100 to register 1

Jump instruction
JMP reg, lineAdress
JMP lineAddress
For example, JMP R1, 32 jumps to line 32 of the program if the value of R1 is zero. JMP 23 jumps to
line 23 directly.


Print instructions
PRN reg
PRN constant
For example, PRN R3 will print the value of register 3 to the screen, after each print a new line
should be inserted.


Other instructions
HLT
halts the program and prints on the screen the contents of all registers
