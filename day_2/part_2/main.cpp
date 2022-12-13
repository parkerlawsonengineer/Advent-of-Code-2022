#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#define ROUND_LOSE          "X"
#define ROUND_DRAW          "Y"
#define ROUND_WIN           "Z"

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
        map<string, int> outcomeMap;

    public:

        RockPaperScissors() {

            this->totalScore = 0;

            //initialize scoreMap
            this->scoreMap["rock"] = ROCK_SCORE;
            this->scoreMap["paper"] = PAPER_SCORE;
            this->scoreMap["scissors"] = SCISSORS_SCORE;

            this->outcomeMap[ROUND_LOSE] = OUTCOME_SCORE_LOSE;
            this->outcomeMap[ROUND_DRAW] = OUTCOME_SCORE_DRAW;
            this->outcomeMap[ROUND_WIN] = OUTCOME_SCORE_WIN;


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
        string getOutcomeFromLine(string line) {
            
            //split line by space
            int pos = line.find(" ");

            //get contents of string after space
            return line.substr(pos + 1, line.length() - pos);

        }

        /*
        *   Input: string representing opponent's move, string representing the round outcome 
        *   Return: score associated with player's move
        *   Description: Using the opponent's move and the outcome of the round, finds the player's move and
        *   returns the associated score.
        */
        int findOptionScore(string opponentMove, string outcome) {

            if (opponentMove == OPPONENT_ROCK) {
                if (outcome == ROUND_LOSE) {
                    return SCISSORS_SCORE;
                } else if (outcome == ROUND_DRAW) {
                    return ROCK_SCORE;
                } else if (outcome == ROUND_WIN) {
                    return PAPER_SCORE;
                } else {
                    return 0;
                }
            } else if (opponentMove == OPPONENT_PAPER) {
                if (outcome == ROUND_LOSE) {
                    return ROCK_SCORE;
                } else if (outcome == ROUND_DRAW) {
                    return PAPER_SCORE;
                } else if (outcome == ROUND_WIN) {
                    return SCISSORS_SCORE;
                } else {
                    return 0;
                }
            } else if (opponentMove == OPPONENT_SCISSORS) {
                if (outcome == ROUND_LOSE) {
                    return PAPER_SCORE;
                } else if (outcome == ROUND_DRAW) {
                    return SCISSORS_SCORE;
                } else if (outcome == ROUND_WIN) {
                    return ROCK_SCORE;
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

            string outcome = getOutcomeFromLine(line);
            string opponentMove = getOpponentMoveFromLine(line);

            int optionScore = findOptionScore(opponentMove, outcome);

            int outcomeScore = this->outcomeMap[outcome];

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