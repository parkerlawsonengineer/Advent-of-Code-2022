# Day 10 (part 1)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day10

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day10 input.txt

The program expects an input in the form of lines of text in the format: "INSTRUCTION VALUE". The program supports 2 instructions: NOOP, and ADDX. A NOOP instruction performs no operation, and takes 1 cycle. ADDX adds the number specified by "VALUE" to the X register, and takes 2 cycles to complete. Upon initialization, the CPU object takes a list of cycles to observe, and records the contents of the X register for each. At the end of execution, the program multiplies each of the observed values by the cycle on which it was recorded, calculating the 'signal strength' for that cycle. All of the signal strength values are then totaled.

The result will be printed at the end of this process, and represents the total of all of the signal scores.

