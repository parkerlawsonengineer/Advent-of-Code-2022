# Day 1

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day1

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day1 input.txt

The program expects an input in the format of numerical values, each separated by a newline. Between each block of numbers there must be an empty line acting as a delimiter. Numbers will be added until the program reaches the delimiter, at which point the current total will be compared with the highest total recorded. If the new total is higher, the old value will be replaced with the new one. If not, the new value will be discarded. The program then clears the current total and continues. This process repeats until it reaches the end of the file.

The result will be printed at the end of this process, and represents the highest value of a 'block' of data within the file.

