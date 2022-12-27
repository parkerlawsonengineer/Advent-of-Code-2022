# Day 2 (part 2)

## Compilation:

Compile with any c++ compiler, I use g++:

    g++ main.cpp -o day2

## Usage:

from the command line, run the executable followed by the path to a .txt file that contains the input values. if the .txt is in the same directory as the executable, no path is required

    ./day2 input.txt

The program expects an input in the form of lines of text, in the format of: "opponentMove roundOutcome" (e.g. "A X"). The program reads one line at a time from the file, and calculates the points earned for that 'round' of the game, according to the rules defined by the challenge:

    +0 points for a loss
    +3 points for a draw
    +6 points for a win

    +1 point for playing rock
    +2 points for playing paper
    +3 points for playing scissors

While most of the code is left unchanged from part 1, this version of the program must also determine what move the 'player' is making based on the opponent's move and the round outcome in order to calculate the correct point total.

the program ends by printing the total points earned cumulatively from all the 'rounds' defined in the input file.