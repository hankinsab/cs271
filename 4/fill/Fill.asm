// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.


// Initialize constants and variables
@8192           // Set the constant value of 8192 (total number of pixels on the screen)
D=A            
@totalPixels   // Store the total pixel count 
M=D            

// check input
(START)
    @KBD               
    D=M               // Read the keyboard value into D, 0 if no key pressed
    @FILL_BLACK     // If any key is pressed, jump to black screen section
    D;JNE
    @FILL_WHITE     // If no key is presse, jump to white 
    D;JEQ

// Paint the entire screen black (when a key is pressed)
(FILL_BLACK)
    @counter     // Initialize pixel counter to 0
    M=0              
(BLACK_LOOP)   
    @counter     // Load the current pixel index into D
    D=M
    @SCREEN         
    A=D+A            // Add the pixel index to the base address to get the correct memory location
    M=-1              // Set the current pixel to black
    @totalPixels   
    D=D+1             // Increment the counter by 1
    @counter
    M=D               // Store the new pixel counter value
    @8192            
    D=D-A             // Subtract current pixel index from total pixel count
    @BLACK_LOOP         // If D != 0, loop
    D;JNE
    @START    // Once the screen is painted black, go back to the main loop to check keyboard input
    0;JMP

// Paint the entire screen white when no key is pressed
(FILL_WHITE)
    @pixelCounterWhite  // Initialize a separate counter for white 
    M=0                 // Start the counter from 0 
(WHITE_LOOP)    
    @pixelCounterWhite  // Load the current pixel index into D
    D=M
    @SCREEN 
