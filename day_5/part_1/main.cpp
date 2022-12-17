#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//number of characters long 1 crate is in a crate diagram (e.g. "[A] ")
#define CRATE_LENGTH 4

class Ship {

    typedef struct INSTRUCTION {
        int source;
        int destination; 
        int numberToMove;
    } INSTRUCTION;

    private:
        vector< vector<char> > stacks;


        /*
        *   Input: vector of strings representing a ship's cargo. This string must be in the format
        *   of a diagram such as:
        * 
        *   [A]     
        *   [B]     [C]
        *   [D] [E] [F]
        *    1   2   3
        * 
        *   Returns: int representing the total number of 'stacks' in the diagram
        */
        int getNumberOfStacksFromDiagram( vector<string> cargoDiagram) {

            //get last line of diagram, the stack labels
            string numLabels = cargoDiagram.back();

            //remove trailing space
            numLabels.pop_back();

            //get position of space right before last number
            int pos = numLabels.find_last_of(" ");

            //read last number into new string variable
            string stackNum = numLabels.substr(pos, numLabels.length() - pos);

            //cast to int and return
            return stoi(stackNum);

        }

        /*
        *   Input: int specifying which stack to find a character from, string line from cargoDiagram
        *   Returns: char from the crate in the stack specified by stackNum. this will be a ' ' space character if there is 
        *   no crate in that stack.
        */
        char getCrateFromLine(int stackNum, string line) {

            //calculate offset of stack
            int stackOffset = (CRATE_LENGTH * (stackNum - 1)) + 1;

            return line[stackOffset];

        }

        /*
        *   Input: int specifying which stack to read,
        *   vector of strings representing a ship's cargo. This string must be in the format
        *   of a diagram such as:
        * 
        *   [A]     
        *   [B]     [C]
        *   [D] [E] [F]
        *    1   2   3
        * 
        *   Returns: vector of chars representing the specified 'stack' based on data from the diagram 
        */
        vector<char> getStackFromDiagram(int stackNum, vector<string> cargoDiagram ) {

            vector<char> newStack;

            //remove last line of diagram, the stack labels
            cargoDiagram.pop_back();

            //iterate through cargoDiagram vector, and add to new stack
            for (vector<string>::iterator ptr = cargoDiagram.begin(); ptr < cargoDiagram.end(); ptr++) {

                char newCrate = getCrateFromLine(stackNum, *ptr);
                if (newCrate != ' ') {
                    newStack.insert(newStack.begin(), getCrateFromLine(stackNum, *ptr));
                }

            }

            return newStack;

        }

        /*
        *   Input: vector of strings representing a ship's cargo. This string must be in the format
        *   of a diagram such as:
        * 
        *   [A]     
        *   [B]     [C]
        *   [D] [E] [F]
        *    1   2   3
        * 
        *   Returns: vector of 'stacks' based on data from diagram
        */
        vector< vector<char> > parseCargoDiagram( vector<string> cargoDiagram) {

            vector< vector<char> > newStacks;

            if (cargoDiagram.empty()) {
                throw invalid_argument("Cargo diagram is empty.");
            }
            
            int numberOfStacks = getNumberOfStacksFromDiagram(cargoDiagram);

            for (int i = 1; i <= numberOfStacks; i++) {
                vector<char> newStack = getStackFromDiagram(i, cargoDiagram);
                newStacks.push_back(newStack);
            }

            return newStacks;

        }

        /*
        *   Input: string to parse into instruction, in the format: "move numToMove from source to destination"
        *   returns: INSTRUCTION struct with relevant values parsed into integer form
        */
        INSTRUCTION parseLineToInstruction(string line) {
            
            INSTRUCTION newInstruction;
            int startPos, endPos;
            string numString;

            //get start and end positions of first number (numberToMove)
            startPos = line.find(' ');
            endPos = line.find(' ', startPos + 1);

            //read numberToMove 
            numString = line.substr(startPos, endPos - startPos);
            newInstruction.numberToMove = stoi(numString);

            //get start and end positions of second number (source)
            startPos = line.find(' ', endPos + 1);
            endPos = line.find(' ', startPos + 1);

            //read source
            numString = line.substr(startPos, endPos - startPos);
            newInstruction.source = stoi(numString);

            //get start position of third number (destination)
            startPos = line.find(' ', endPos + 1);

            //read source
            numString = line.substr(startPos, line.length() - startPos);
            newInstruction.destination = stoi(numString);

            return newInstruction;


        }

        /*
        *   Input: integers representing the source and destination of a crate to move
        *   Description: removes crate from the top of source stack and adds it to the top of destination stack
        */
        void moveCrate(int source, int destination) {
            
            //copy char from top of source stack (subtract 1 because input file is 1-indexed, while vector is 0-indexed)
            char movedCrate = this->stacks[source - 1].back();

            //remove char from top of source stack (subtract 1 because input file is 1-indexed, while vector is 0-indexed)
            this->stacks[source - 1].pop_back();
            
            //add char to top of destination crate (subtract 1 because input file is 1-indexed, while vector is 0-indexed)
            this->stacks[destination - 1].push_back(movedCrate);

        }

    public:

        /*
        *   Input: vector of strings representing the initial state of the ship's cargo. This string must be in the format
        *   of a diagram such as:
        * 
        *   [A]     
        *   [B]     [C]
        *   [D] [E] [F]
        *    1   2   3
        * 
        *   Description: initializes stacks to state provided as argument
        */
        Ship(vector<string> initialState) {

            this->stacks = parseCargoDiagram(initialState);

        }

        /*
        *   Input: string in the format: "move numToMove from source to destination"
        *   Description: performs the move instructions specified by a line of text from the input file
        */
        void doInstruction(string line) {

            INSTRUCTION newInstruction = parseLineToInstruction(line);

            for (int i = 0; i < newInstruction.numberToMove; i++) {

                this->moveCrate(newInstruction.source, newInstruction.destination);

            }

        }

        /*
        *   Returns: a string composed of the character found at the top of each stack.
        */
        string getTopCrates() {

            string output = "";

            for (vector< vector<char> >::iterator ptr = this->stacks.begin(); ptr < this->stacks.end(); ptr++) {

                char topOfStack = ptr->back();
                output.push_back(topOfStack);

            }

            return output;

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
    int total = 0;

    vector<string> cargoDiagram;
    bool initializationDone = false;

    //read until first empty line, this is our initial state
    while (!initializationDone) {

        getline(inputFile, readLine);

        if (readLine.length() != 0) {
            cargoDiagram.push_back(readLine);
        } else {
            initializationDone = true;
        }

    }

    //initialize new cargo ship with initial state
    Ship cargoShip(cargoDiagram);


    while (getline(inputFile, readLine)) {

        cargoShip.doInstruction(readLine);

    }

    cout << "The crates on top of all of the stacks are: " << cargoShip.getTopCrates() << "." << endl;



    return 0;


}