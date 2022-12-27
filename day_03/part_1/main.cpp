#include <iostream>
#include <fstream>
using namespace std;

//ASCII A is 65, so to get it to the correct value (27), we subtract 65 and add 27
#define UPPERCASE_ASCII_OFFSET 38

//ASCII a is 97, so to get it to the correct value (1), we subtract 97 and add 1
#define LOWERCASE_ASCII_OFFSET 96

class Rucksack {

    private:
        string firstCompartment;
        string secondCompartment;

    public:
        /*
        *   Input: string line, a string of even-numbered length which represents both compartments in the rucksack
        *   Description: initializes rucksack object, populates firstCompartment and secondCompartment with the first and
        *   second halves of the input line, respectively.
        */
        Rucksack(string line) {

            int len = line.length();
            this->firstCompartment = line.substr(0, len / 2);
            this->secondCompartment = line.substr((len / 2), (len/2));

        }

        /*
        *   Returns: char value that is found in both firstCompartment and secondCompartment strings
        */
        char findCommonChar() {

            //iterate through both halves, comparing to see if any characters are present in both. if so, return that char
            for (int i = 0; i < firstCompartment.length(); i++) {

                for (int j = 0; j < secondCompartment.length(); j++) {

                    if (firstCompartment[i] == secondCompartment[j]) {
                        return firstCompartment[i];
                    }

                }

            }

            //if no common character is found, throw an exception
            throw invalid_argument("No characters found in common, strings must contain at least one character in common.");
            
            
        }

        /*
        *   Input: char representing an 'item'
        *   Returns: int value of the 'priority' value of the input char
        */
        int getPriorityValue(char item) {

            if (!isalpha((int) item)) {
                throw invalid_argument("Character is not a letter of the alphabet");
                exit(1);
            }

            if (isupper((int) item)) {
                return ((int) item) - UPPERCASE_ASCII_OFFSET;
            } else {
                return ((int) item) - LOWERCASE_ASCII_OFFSET;
            }


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

    string readLine;
    int total = 0;
    
    while (getline(inputFile, readLine)) {

        Rucksack newSack(readLine);
        char commonChar = newSack.findCommonChar();
        total += newSack.getPriorityValue(commonChar);

    }
    
    cout << "Total of all priority values: " << total << "." << endl;


    return 0;
}