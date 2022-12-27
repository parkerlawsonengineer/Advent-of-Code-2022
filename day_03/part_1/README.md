# Day 3 (part 1)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day3

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input values. if the .txt is in the same directory as the executable, no path is required

    ./day3 input.txt

The program expects an input in the form of lines of text, each containing an even number of characters, representing the contents of a Rucksack. The program reads one line at a time from the file, and splits it into 2 strings of equal length, each representing half of the input string. The program then finds the only character present in each of these 2 strings, and adds the associated 'priority' value to a running total.

The program finishes by printing the total of all of the 'priority' values to the console.