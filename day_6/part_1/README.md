# Day 6 (part 1)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day6

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day6 input.txt

The program expects an input in the form of 1 line of characters, representing a datastream buffer. The program moves through the string 4 characters at a time, looking for the start-of-packet marker: a sequence of 4 unique characters.

The result will be printed at the end of this process, and represents the number of characters that were processed to find the packet.

