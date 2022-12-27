# Day 8 (part 1)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day8

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input number values. if the .txt is in the same directory as the executable, no path is required

    ./day8 input.txt

The program expects input in the form of lines of integer values, with each line of the file being of equal length. The program begins by reading each integer value into a 2D Vector of Tree structs, which each contain the integer representing it's height, as well as a boolean representing whether the tree is visible from the perimeter of the grid. During construction, the visibility of all trees defaults to false. Once the grid is initialized, the program iterates through the grid, 'looking' from the top, bottom, left, and right, and marks each tree that is visible.

The number of trees visible from the perimeter will be printed to the command line as the result.
