# Day 3 (part 2)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day3

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input values. if the .txt is in the same directory as the executable, no path is required

    ./day2 input.txt

The program expects an input in the form of lines of text, each containing an even number of characters, representing the contents of a Rucksack. The program reads one line at a time from the file, creating a Rucksack object each time. Once the program has read 3 lines, it finds the only character found in all 3 of the previous Rucksacks, and adds the 'priority' value of that character to a running total.

The program finishes by printing the total of all of the 'priority' values to the console.