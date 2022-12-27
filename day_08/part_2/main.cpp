#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct TREE {
    int height;
    bool visible;
};


class TreeGrid {

    private:
        vector< vector<TREE> > trees;

        /*
        *   Description: iterates through each column in the grid and calls the checkColumnFromTop and checkColumnFromBottom
        *   functions in order to determine which trees are visible.
        */
        void checkColumns() {

            int length = (this->trees.begin())->size();

            for (int i = 0; i < length; i++){
                checkColumnFromTop(i);
                checkColumnFromBottom(i);
            }

        }

        /*
        *   Description: iterates through each row in the grid and calls the checkRowFromTop and checkRowFromBottom
        *   functions in order to determine which trees are visible.
        */
        void checkRows() {

            for (int i = 0; i < this->trees.size(); i++) {
                checkRowFromLeft(i);
                checkRowFromRight(i);
            }

        }

        /*
        *   Input: int highest describing the height to check against, and TREE *tree a pointer to the tree to check
        *   Returns: the higher value between the height of *tree and 'highest'
        *   Description: Compares the height of the tree against the highest tree in the row or column thus far.
        *   if the tree is higher than the passed height, it is marked visible, and it's height is returned as the new 
        *   highest
        */
        int checkHighest(int highest, TREE *tree) {

            if (tree->height > highest) {
                tree->visible = true;
                return tree->height;
            } else {
                return highest;
            }

        }

        /*
        *   Input: int row defining which row to check
        *   Description: iterates through the trees in the specified row from left to right and marks them as visible 
        *   if they can be seen from the perimeter of the grid
        */
        void checkRowFromLeft(int row) {

            int highest = 0;

            for (int i = 0; i < this->trees[row].size(); i++) {

                if (i == 0 || i == this->trees[row].size() - 1) { //automatically visible if it's on the perimiter
                    this->trees[row][i].visible = true;
                }

                highest = checkHighest(highest, &(this->trees[row][i]));
            }

        }

        /*
        *   Input: int row defining which row to check
        *   Description: iterates through the trees in the specified row from right to left and marks them as visible 
        *   if they can be seen from the perimeter of the grid
        */
        void checkRowFromRight(int row) {

            int highest = 0;

            for (int i = this->trees[row].size() - 1; i >= 0; i--) {

                if (i == 0 || i == this->trees[row].size() - 1) { //automatically visible if it's on the perimiter
                    this->trees[row][i].visible = true;
                }

                highest = checkHighest(highest, &(this->trees[row][i]));
            }

        }

        /*
        *   Input: int row defining which row to check
        *   Description: iterates through the trees in the specified column from top to bottom and marks them as visible 
        *   if they can be seen from the perimeter of the grid
        */
        void checkColumnFromTop(int column) {

            int highest = 0;

            for (int i = 0; i < this->trees.size(); i++) {

                if (i == 0 || i == this->trees.size() - 1) { //automatically visible if it's on the perimiter
                    this->trees[i][column].visible = true;
                }

                highest = checkHighest(highest, &(this->trees[i][column]));
            }

        }

        /*
        *   Input: int row defining which row to check
        *   Description: iterates through the trees in the specified column from bottom to top and marks them as visible 
        *   if they can be seen from the perimeter of the grid
        */
        void checkColumnFromBottom(int column) {

            int highest = 0;

            for (int i = this->trees.size() - 1; i >= 0; i--) {

                if (i == 0 || i == this->trees.size() - 1) { //automatically visible if it's on the perimiter
                    this->trees[i][column].visible = true;
                }

                highest = checkHighest(highest, &(this->trees[i][column]));
            }

        }

        /*
        *   Description: iterates through the trees vector and tallies the total number of trees marked as visible
        */
        int getVisibleCount() {

            int total = 0;

            for (int i = 0; i < this->trees.size(); i++){
                for (int j = 0; j < this->trees[i].size(); j++) {
                    if (this->trees[i][j].visible) {
                        total++;
                    }
                }
            }

            return total;

        }

        /*
        *   Input: int row and column describing the coordinates of the tree in the grid to check
        *   Returns: the number of trees visible when looking up from the current tree.
        *   Description: iterates through the grid to see how many trees are above the current tree that are
        *   not obstructed by a taller tree.
        */
        int checkUp(int row, int column) {
            if (row == 0) {
                return 0;
            }

            int score = 0;
            for (int i = row - 1; i >= 0; i--) {
                score++;
                if (this->trees[i][column].height >= this->trees[row][column].height) {
                    return score;
                }
            }
            return score;
        }

        /*
        *   Input: int row and column describing the coordinates of the tree in the grid to check
        *   Returns: the number of trees visible when looking down from the current tree.
        *   Description: iterates through the grid to see how many trees are under the current tree that are
        *   not obstructed by a taller tree.
        */
        int checkDown(int row, int column) {
            if (row == this->trees.size() - 1) {
                return 0;
            }

            int score = 0;
            for (int i = row + 1; i < this->trees.size(); i++) {
                score++;
                if (this->trees[i][column].height >= this->trees[row][column].height) {
                    return score;
                }
            }
            return score;
        }

        /*
        *   Input: int row and column describing the coordinates of the tree in the grid to check
        *   Returns: the number of trees visible when looking to the left of the current tree.
        *   Description: iterates through the grid to see how many trees are to the left of the current tree that are
        *   not obstructed by a taller tree.
        */
        int checkLeft(int row, int column) {
            if (column == 0) {
                return 0;
            }

            int score = 0;
            for (int i = column - 1; i >= 0; i--) {
                score++;
                if (this->trees[row][i].height >= this->trees[row][column].height) {
                    return score;
                }
            }
            return score;
        }

        /*
        *   Input: int row and column describing the coordinates of the tree in the grid to check
        *   Returns: the number of trees visible when looking to the right of the current tree.
        *   Description: iterates through the grid to see how many trees are to the right of the current tree that are
        *   not obstructed by a taller tree.
        */
        int checkRight(int row, int column) {
            if (column == this->trees[row].size() - 1) {
                return 0;
            }

            int score = 0;
            for (int i = column + 1; i < this->trees[row].size(); i++) {
                score++;
                if (this->trees[row][i].height >= this->trees[row][column].height) {
                    return score;
                }
            }
            return score;
        }

        /*
        *   Input: int row and column describing the coordinates of the tree in the grid to check
        *   Returns: 'scenic score' of the tree, based on the number of trees visible from this point int the grid.
        *   Description: checks the scores of each individual direction, and then calculates the final 'scenic score' 
        *   by multiplying them together
        */
        int getScenicScore(int row, int column) {

            int upScore = checkUp(row, column);
            int downScore = checkDown(row, column);
            int leftScore = checkLeft(row, column);
            int rightScore = checkRight(row, column);

            int score = upScore * downScore * leftScore * rightScore;

            return score;

        }

    public:

        /*
        *   Input: string line of text from input file, where every character is an integer value.
        *   Description: parses the string into a vector of TREE objects, then adds the entire line to the 'trees' vector,
        *   in order to initialize the grid of trees to perform operations on later.
        */
        void parseLine(string line) {

            vector<TREE> newLine;

            for (int i = 0; i < line.length(); i++) {

                TREE newTree;
                newTree.height = stoi(line.substr(i, 1));
                newTree.visible = false;

                newLine.push_back(newTree);
            }

            this->trees.push_back(newLine);

        }

        /*
        *   Returns: total number of visible trees
        *   Description: performs checks on all rows and columns of the grid to determine which trees are visible,
        *   then tallies the number of visible trees and returns it.
        */
        int getTotalVisibleTrees() {

            this->checkColumns();
            this->checkRows();

            return this->getVisibleCount();

        }

        /*
        *   Returns: highest 'scenic score' out of all the trees in the grid
        *   Description: iterates through all trees in the grid, calculating the 'scenic score' for each
        *   once every score has been calculated, the highest score is returned
        */
        int getHighestScenicScore() {

            int highest = 0;

            for (int i = 0; i < this->trees.size(); i++) {
                for (int j = 0; j < this->trees[i].size(); j++) {
                    int score = getScenicScore(i,j);
                    if (score > highest) {
                        highest = score;
                    }
                }
            }

            return highest;

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
    TreeGrid grid;

    while (getline(inputFile, readLine)) {
        grid.parseLine(readLine);
    }

    int highest = grid.getHighestScenicScore();
    //print result
    cout << "The highest scenic score for a tree in the grid is: " << highest << "." << endl;
    

    return 0;


}