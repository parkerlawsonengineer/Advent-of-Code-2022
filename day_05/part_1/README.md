# Day 5 (part 1)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day5

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day5 input.txt

The program expects an input file with 2 sections, seperated by an empty line as a delimiter. 

The first section of the input file should be a diagram of the initial state of the cargo ship, in the form of a diagram with the following formatting:

    [A]     
    [B]     [C]
    [D] [E] [F]
     1   2   3

The second section should be a list of move instructions, in the format of:

    move {numberToMove} from {sourceStack} to {destinationStack}

The program begins by reading the first section from the file, and initializing a vector of 'stacks'. Each stack is a vector of characters, representing the 'crates' found in that stack.

Once the Ship object is initialized, the program begins reading in instructions from the file, and executing them. For part 1, each crate is moved 1 at a time, so when multiple crates are being moved in 1 instruction, their order is effectively reversed once added to the new stack.

At the end of the process, the program prints out a string representing the character found at the top of each of the stacks.
