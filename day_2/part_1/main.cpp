#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#define YOUR_ROCK           "X"
#define YOUR_PAPER          "Y"
#define YOUR_SCISSORS       "Z"

#define ROCK_SCORE          1
#define PAPER_SCORE         2
#define SCISSORS_SCORE      3

#define OPPONENT_ROCK       "A"
#define OPPONENT_PAPER      "B"
#define OPPONENT_SCISSORS   "C"

#define OUTCOME_SCORE_LOSE  0
#define OUTCOME_SCORE_DRAW  3
#define OUTCOME_SCORE_WIN   6


class RockPaperScissors {

    private:

        int totalScore;
        map<string, int> scoreMap;

    public:

        RockPaperScissors() {

            this->totalScore = 0;

            //initialize scoreMap
            this->scoreMap[YOUR_ROCK] = ROCK_SCORE;
            this->scoreMap[YOUR_PAPER] = PAPER_SCORE;
            this->scoreMap[YOUR_SCISSORS] = SCISSORS_SCORE;


        }

        int getTotalScore() {return this->totalScore;};
        void increaseTotalScore(int scoreToAdd) {this->totalScore+=scoreToAdd;};

        /*
        *   Input: string in the format: "opponentMove yourMove" e.g. "X A"
        *   Return: First part of string, preceding the space
        */
        string getOpponentMoveFromLine(string line) {
            
            //split line by space
            int pos = line.find(" ");

            //get contents of string before space
            return line.substr(0, pos);

        }

        /*
        *   Input: string in the format: "opponentMove yourMove" e.g. "X A"
        *   Return: Last part of string, following the space
        */
        string getYourMoveFromLine(string line) {
            
            //split line by space
            int pos = line.find(" ");

            //get contents of string after space
            return line.substr(pos + 1, line.length() - pos);

        }


        /*
        *   Input: strings defining you and your oponnent's rules
        *   Return: the number of points rewarded for the round, depending on the result: tie, draw, win
        */
        int findOutcomeScore(string yourMove, string opponentMove) {
            
            if (yourMove == YOUR_ROCK) {

                if (opponentMove == OPPONENT_ROCK) {
                    return OUTCOME_SCORE_DRAW;
                } else if (opponentMove == OPPONENT_PAPER) {
                    return OUTCOME_SCORE_LOSE;
                } else if (opponentMove == OPPONENT_SCISSORS) {
                    return OUTCOME_SCORE_WIN;
                } else {
                    return 0;
                }

            } else if (yourMove == YOUR_PAPER) {

                if (opponentMove == OPPONENT_ROCK) {
                    return OUTCOME_SCORE_WIN;
                } else if (opponentMove == OPPONENT_PAPER) {
                    return OUTCOME_SCORE_DRAW;
                } else if (opponentMove == OPPONENT_SCISSORS) {
                    return OUTCOME_SCORE_LOSE;
                } else {
                    return 0;
                }

            } else if (yourMove == YOUR_SCISSORS) {
                
                if (opponentMove == OPPONENT_ROCK) {
                    return OUTCOME_SCORE_LOSE;
                } else if (opponentMove == OPPONENT_PAPER) {
                    return OUTCOME_SCORE_WIN;
                } else if (opponentMove == OPPONENT_SCISSORS) {
                    return OUTCOME_SCORE_DRAW;
                } else {
                    return 0;
                }

            } else {
                return 0;
            }

        }


        /*
        *   Input: string in the format: "yourMove opponentMove" e.g. "X A"
        *   Returns: total score of round
        *   Description: Parses a line of input and calculates total score of the round using the following rules:
        *       You play:
        *           Rock: +1 point
        *           Paper: +2 points
        *           Scissors: +3 points
        * 
        *       Result of round is:
        *           Loss: +0 points
        *           Draw: +3 points
        *           Win: +6 points
        *           
        */
        int parseLine(string line) {

            string yourMove = getYourMoveFromLine(line);
            string opponentMove = getOpponentMoveFromLine(line);

            int optionScore = this->scoreMap[yourMove];

            int outcomeScore = findOutcomeScore(yourMove, opponentMove);

            int roundScore = optionScore + outcomeScore;

            return roundScore;

        }


};

int main(int argc, char** argv) {

    //check for arguments
    if (argc != 2) {
        cout << "Incorrect number of arguments. Please specify the name of 1 .txt file to read input from." << endl;
        return -1;
    }

    ifstream inputFile(argv[1]);

    //if the file doesn't open correctly, exit.
    if (!inputFile) {
        cout << "There was a problem opening the file." << endl;
        return -1;
    }

    //initialize variables
    string readLine;
    int currentTotal = 0, currentHighest = 0;

    RockPaperScissors game;

    while (getline(inputFile, readLine)) {

        int roundScore = game.parseLine(readLine);
        game.increaseTotalScore(roundScore);

    }

    cout << "Total Score: " << game.getTotalScore() << endl;


    return 0;


}