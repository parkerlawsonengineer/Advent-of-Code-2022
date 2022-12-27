# Day 10 (part 2)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day10

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day10 input.txt

The program expects an input in the form of lines of text in the format: "INSTRUCTION VALUE". The program supports 2 instructions: NOOP, and ADDX. A NOOP instruction performs no operation, and takes 1 cycle. ADDX adds the number specified by "VALUE" to the X register, and takes 2 cycles to complete. The contents of the X register represent the position of the center pixel of a 3-pixel wide sprite. At the beginning of each cycle, a pixel is drawn into a 'display buffer' of 240 pixels (6 rows of 40 pixels). If the current pixel being drawn overlaps with the sprite, a 'lit' pixel (#) is written to the buffer. if the sprite does not overlap, an 'unlit' (.) pixel is drawn. 

At the end of the program, the display buffer is printed to the console, and contains 6 uppercase letters, the solution to the challenge.
