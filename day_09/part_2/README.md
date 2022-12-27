# Day 9 (part 2)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day9

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day9 input.txt

The program expects input in the form of lines of text of the format: "direction numberOfMoves", where 'direction' is one of: 'U', 'D', 'L', 'R' and 'numberOfMoves' is an integer value. The program begins by initializing a 'rope' object with a head and a tail made up of 9 segments, both at x,y coordinates 0,0. The program then reads the input line by line and updates the position of the head of the rope. After each move if the next segment of thee rope isn't touching the head, it is moved towards the previous one. 

At the end, the total number of spaces visited by the final segment of the rope is tallied and printed to the console.
