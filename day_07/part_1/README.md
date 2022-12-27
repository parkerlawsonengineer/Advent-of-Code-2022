# Day 7 (part 1)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day7

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day7 input.txt


The program expects input in the form of lines of text representing console commands and output. The program supports the commands 'cd' and 'ls', as well as the output of the 'ls' command. The program reads the input and recreates the filesystem described by the series of commands. It then calculates the size of each folder present in the filesystem.

For part 1, the program searches through the filesystem recursively and totals the filesizes of every folder with a size of less than 100000 bytes.

At the end of this process, the program prints the total size of every folder that met the requirements to the console.

