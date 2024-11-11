// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.


//R0 is where you subtract, R1 first, R2 is where you store the result 

//set r2 at zero 
@R2
M=0

//if R0 > 0, go to loop
@R0
D=M
@LOOP 
D;JGT


//if it didnt jump then go to end 
@END 
0;JMP

(LOOP)
// get R2
    @R2
    D=M

    //add r1 to it 
    @R1
    D=D+M

    //send the result back to R2
    @R2
    M=D

    //subract 1 from r0
    @R0
    D=M-1 
    M=D

//if r0 > 0 loop
@LOOP
D;JGT

(END) 
    @END
    0;JMP