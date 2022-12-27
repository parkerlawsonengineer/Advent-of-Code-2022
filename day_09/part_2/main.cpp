#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#define TAIL_LENGTH 9

struct ROPE_PART {
    int pos_x;
    int pos_y;
};

class Rope {

    private:
        ROPE_PART head;
        ROPE_PART tail[TAIL_LENGTH];

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
        *   Input: ROPE_PART head and tail, representing 2 sequential parts of the rope
        *   Returns: distance on the x-axis between the head and the tail
        */
        int getDistanceX(ROPE_PART _head, ROPE_PART _tail) {
            return abs(_head.pos_x - _tail.pos_x);
        }

        /*
        *   Input: ROPE_PART head and tail, representing 2 sequential parts of the rope
        *   Returns: distance on the y-axis between the head and the tail
        */
        int getDistanceY(ROPE_PART _head, ROPE_PART _tail) {
            return abs(_head.pos_y - _tail.pos_y);
        }

        /*
        *   Input: ROPE_PART head and tail, representing 2 sequential parts of the rope
        *   Returns: boolean value, true if head is within 1 space of tail, otherwise false
        */
        bool tailIsTouchingHead(ROPE_PART _head, ROPE_PART _tail) {

            int distanceX, distanceY;

            distanceX = getDistanceX(_head, _tail);
            distanceY = getDistanceY(_head, _tail);

            if (distanceX <= 1 && distanceY <= 1) {
                return true;
            } else {
                return false;
            }

        }

        /*
        *   Input: ROPE_PART head and tail, representing 2 sequential parts of the rope
        *   Description: Moves the tail of the rope towards the head when it is farther than 1 space away.
        *   if the tail is farther than 1 space away and is diagonal to the head, it moves diagonally to keep up. e.g.:
        *   . . . .      . . . .
        *   . . H .  ->  . . H .
        *   . . . .      . . T .
        *   . T . .      . . . .
        */
        void moveTailTowardsHead(ROPE_PART *_head, ROPE_PART *_tail) {

            if (this->getDistanceX(*_head, *_tail) > 1) { //need to move on x-axis primarily

                if (_head->pos_x > _tail->pos_x) {
                    _tail->pos_x++;
                } else {
                    _tail->pos_x--;
                }

                //handle diagonal movement if necessary
                if (this->getDistanceY(*_head, *_tail) > 0) {
                    if (_head->pos_y > _tail->pos_y) {
                        _tail->pos_y++;
                    } else {
                        _tail->pos_y--;
                    }
                }
                
            } else { //need to move on y-axis primarily

                if (_head->pos_y > _tail->pos_y) {
                    _tail->pos_y++;
                } else {
                    _tail->pos_y--;
                }

                //handle diagonal movement if necessary
                if (this->getDistanceX(*_head, *_tail) > 0) {
                    if (_head->pos_x > _tail->pos_x) {
                        _tail->pos_x++;
                    } else {
                        _tail->pos_x--;
                    }
                }

            } 
            
        }

        /*
        *   Description: adds current location of tail to map of visited locations, to be tallied later
        */
        void markCurrentTailLocation(ROPE_PART _tail) {

            string location = "";
            location += to_string(_tail.pos_x);
            location += ",";
            location += to_string(_tail.pos_y);

            this->locationsVisited[location]++;

        }


    public:
        /*
        *   Description: constructor, intitializes position of head and tail to (0,0)
        */
        Rope() {
            this->head.pos_x = 0;
            this->head.pos_y = 0;
            for (int i = 0; i < TAIL_LENGTH; i++) {
                this->tail[i].pos_x = 0;
                this->tail[i].pos_y = 0;
            }
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

                for (int j = 0; j < TAIL_LENGTH; j++) {

                    ROPE_PART *_head;
                    ROPE_PART *_tail = &(this->tail[j]);

                    if (j == 0) {
                        _head = &(this->head);
                    } else {
                        _head = &(this->tail[j - 1]);
                    }

                    if (!this->tailIsTouchingHead(*_head, *_tail)) {

                        this->moveTailTowardsHead(_head, _tail);

                    }


                }

                this->markCurrentTailLocation(this->tail[TAIL_LENGTH - 1]);

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