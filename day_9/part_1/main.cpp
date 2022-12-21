#include <iostream>
#include <fstream>
#include <map>
using namespace std;

struct ROPE_PART {
    int pos_x;
    int pos_y;
};

class Rope {

    private:
        ROPE_PART head;
        ROPE_PART tail;

        map<string, int> locationsVisited;

        /*
        *   Input: string line from input file, in the format: "direction numberOfMoves"
        *   Returns: char indicating which direction to move in
        */
        char getDirectionFromLine(string line) {
            return line[0];
        }

        /*
        *   Input: string line from input file, in the format: "direction numberOfMoves"
        *   Returns: int indicating number of moves to make
        */
        int getNumberOfMovesFromLine(string line) {
            int pos = line.find(" ");
            string number = line.substr(pos, line.length() - pos);
            return stoi(number);
        }

        /*
        *   Input: char representing which direction to move the 'head' of the rope (must be one of: 'U','D','L','R')
        *   Description: updates x,y coordinates of the 'head' of the rope based on a 1-space movement in the specified
        *   direction.
        */
        void moveHead(char direction) {

            switch (direction) {
                case 'U':
                    this->head.pos_y++;
                    break;
                case 'D':
                    this->head.pos_y--;
                    break;
                case 'R':
                    this->head.pos_x++;
                    break;
                case 'L':
                    this->head.pos_x--;
                    break;
            }

        }

        /*
        *   Returns: distance on the x-axis between the head and the tail
        */
        int getDistanceX() {
            return abs(this->head.pos_x - this->tail.pos_x);
        }

        /*
        *   Returns: distance on the y-axis between the head and the tail
        */
        int getDistanceY() {
            return abs(this->head.pos_y - this->tail.pos_y);
        }

        /*
        *   Returns: boolean value, true if head is within 1 space of tail, otherwise false
        */
        bool tailIsTouchingHead() {

            int distanceX, distanceY;

            distanceX = getDistanceX();
            distanceY = getDistanceY();

            if (distanceX <= 1 && distanceY <= 1) {
                return true;
            } else {
                return false;
            }

        }

        /*
        *   Description: Moves the tail of the rope towards the head when it is farther than 1 space away.
        *   if the tail is farther than 1 space away and is diagonal to the head, it moves diagonally to keep up. e.g.:
        *   . . . .      . . . .
        *   . . H .  ->  . . H .
        *   . . . .      . . T .
        *   . T . .      . . . .
        */
        void moveTailTowardsHead() {

            if (this->getDistanceX() > 1) { //need to move on x-axis primarily

                if (this->head.pos_x > this->tail.pos_x) {
                    this->tail.pos_x++;
                } else {
                    this->tail.pos_x--;
                }

                //handle diagonal movement if necessary
                if (this->getDistanceY() > 0) {
                    if (this->head.pos_y > this->tail.pos_y) {
                        this->tail.pos_y++;
                    } else {
                        this->tail.pos_y--;
                    }
                }
                
            } else { //need to move on y-axis primarily

                if (this->head.pos_y > this->tail.pos_y) {
                    this->tail.pos_y++;
                } else {
                    this->tail.pos_y--;
                }

                //handle diagonal movement if necessary
                if (this->getDistanceX() > 0) {
                    if (this->head.pos_x > this->tail.pos_x) {
                        this->tail.pos_x++;
                    } else {
                        this->tail.pos_x--;
                    }
                }

            } 
            
        }

        /*
        *   Description: adds current location of tail to map of visited locations, to be tallied later
        */
        void markCurrentTailLocation() {

            string location = "";
            location += to_string(this->tail.pos_x);
            location += ",";
            location += to_string(this->tail.pos_y);

            this->locationsVisited[location]++;

        }


    public:
        /*
        *   Description: constructor, intitializes position of head and tail to (0,0)
        */
        Rope() {
            this->head.pos_x = 0;
            this->head.pos_y = 0;
            this->tail.pos_x = 0;
            this->tail.pos_y = 0;
        }

        /*
        *   Input: string line from input file, in the format: "direction numberOfMoves"
        *   Description: moves the head of the rope using data from the input file, then moves the tail accordingly,
        *   tracking the spaces the tail occupies along the way
        */
        void parseLine(string line) {

            int numberOfMoves = this->getNumberOfMovesFromLine(line);
            char direction = this->getDirectionFromLine(line);

            for (int i = 0; i < numberOfMoves; i++) {

                this->moveHead(direction);

                if (!this->tailIsTouchingHead()) {

                    this->moveTailTowardsHead();
                    this->markCurrentTailLocation();

                }

            }

        }

        /*
        *   Returns: total number of spaces the tail has occupied
        */
        int getTotalSpacesVisited() {
            return this->locationsVisited.size();
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
    Rope rope;

    while (getline(inputFile, readLine)) {
        
        rope.parseLine(readLine);
        
    }

    int total = rope.getTotalSpacesVisited();
    //print result
    cout << "The total number of spaces visited is: " << total << "." << endl;

    return 0;


}