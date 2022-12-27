#include <iostream>
#include <fstream>
using namespace std;

#define PAIR_DELIMITER ','
#define RANGE_DELIMITER '-'

class rangePair {

    private:
        int firstRangeStart;
        int firstRangeEnd;
        int secondRangeStart;
        int secondRangeEnd;

        /*
        *   Input: string in the format: "firstRangeStart-firstRangeEnd,secondRangeStart-secondRangeEnd"
        *   Returns: substring from beginning of string to before the delimiter
        */
        string getFirstRange(string line) {
            int pos = line.find(PAIR_DELIMITER);
            return line.substr(0, pos);
        }

        /*
        *   Input: string in the format: "firstRangeStart-firstRangeEnd,secondRangeStart-secondRangeEnd"
        *   Returns: substring from after delimiter to end of input string
        */
        string getSecondRange(string line) {
            int pos = line.find(PAIR_DELIMITER);
            return line.substr(pos + 1, line.length() - pos);
        }

        /*
        *   Input: string in the format "rangeStart-rangeEnd"
        *   Returns: rangeStart, casted to int
        */
        int getFirstValueFromRange(string range) {
            int pos = range.find(RANGE_DELIMITER);
            string value = range.substr(0, pos);
            return stoi(value);
        }

        /*
        *   Input: string in the format "rangeStart-rangeEnd"
        *   Returns: rangeEnd, casted to int
        */
        int getSecondValueFromRange(string range) {
            int pos = range.find(RANGE_DELIMITER);
            string value = range.substr(pos + 1, range.length() - pos);
            return stoi(value);
        }

    public:

        /*
        *   Input: string in the format: "firstRangeStart-firstRangeEnd,secondRangeStart-secondRangeEnd"
        *   Description: populates object values from string
        */
        rangePair(string line) {

            string firstRange = this->getFirstRange(line);
            string secondRange = this->getSecondRange(line);

            this->firstRangeStart = this->getFirstValueFromRange(firstRange);
            this->firstRangeEnd = this->getSecondValueFromRange(firstRange);

            this->secondRangeStart = this->getFirstValueFromRange(secondRange);
            this->secondRangeEnd = this->getSecondValueFromRange(secondRange);

        }
        
        /*
        *   Returns: boolean representing whether the first range in the object fully encompasses the second
        */
        bool doesFirstRangeContainSecond() {

            if (this->firstRangeStart <= this->secondRangeStart && this->secondRangeEnd <= this->firstRangeEnd) {
                return true;
            } else {
                return false;
            }

        }

        /*
        *   Returns: boolean representing whether the second range in the object fully encompasses the first
        */
        bool doesSecondRangeContainFirst() {

            if (this->firstRangeStart >= this->secondRangeStart && this->secondRangeEnd >= this->firstRangeEnd) {
                return true;
            } else {
                return false;
            }

        }

        /*
        *   Returns: boolean representing whether the ranges overlap each other
        */
        bool doRangesOverlap() {

            if ((this->firstRangeStart >= this->secondRangeStart && this->firstRangeStart <= this->secondRangeEnd) ||
                (this->secondRangeStart >= this->firstRangeStart && this->secondRangeStart <= this->firstRangeEnd) ||
                (this->firstRangeEnd >= this->secondRangeStart && this->firstRangeEnd <= this->secondRangeEnd) ||
                (this->secondRangeEnd >= this->firstRangeStart && this->secondRangeEnd <= this->firstRangeEnd)) {
                return true;
            } else {
                return false;
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

    //initialize variables
    string readLine;
    int total = 0;

    while (getline(inputFile, readLine)) {

        rangePair newRange(readLine);
        if (newRange.doRangesOverlap()) {
                total++;
            }

    }

    cout << "The total number of pairs where ranges overlap is: " << total << "." << endl;



    return 0;


}