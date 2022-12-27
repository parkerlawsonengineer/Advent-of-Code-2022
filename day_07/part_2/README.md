# Day 7 (part 2)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day7

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day7 input.txt


The program expects input in the form of lines of text representing console commands and output. The program supports the commands 'cd' and 'ls', as well as the output of the 'ls' command. The program reads the input and recreates the filesystem described by the series of commands. It then calculates the size of each folder present in the filesystem.

For part 2, the program searches recursively through the filesystem to find folders that can be deleted in order to leave 30000000 bytes free on the disk (which has a total size of 70000000)

At the end of this process, the program prints the size of the smallest folder that fit the requirements.

