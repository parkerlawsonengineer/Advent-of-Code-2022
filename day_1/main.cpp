#include <iostream>
#include <fstream>
using namespace std;

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

    while (getline(inputFile, readLine)) {
        
        if (readLine.size() == 0) {
            //string is a newline, compare current total with highest so far, then clear it and start again
            if (currentTotal > currentHighest) {
                currentHighest = currentTotal;
            }
            currentTotal = 0;
        } else {
            //add number we just read in to running total
            currentTotal += stoi(readLine);

        }
    }

    //print result
    cout << "The highest total is: " << currentHighest << "." << endl;

    return 0;


}