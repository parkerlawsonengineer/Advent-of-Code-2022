# Day 4 (part 1)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day4

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input values. if the .txt is in the same directory as the executable, no path is required

    ./day4 input.txt

The program expects an input in the form of lines of text, each containing a string in the format: "firstRangeStart-firstRangeEnd,secondRangeStart-secondRangeEnd". The program uses each line to initiate an object which parses the line into 2 ranges. It then compares the ranges to check if either range overlaps the other, and tallies the total number of range pairs where this is true.

The program finishes by printing the total number of pairs where one range overlaps the other.