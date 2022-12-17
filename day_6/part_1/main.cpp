#include <iostream>
#include <fstream>
using namespace std;

#define PACKET_LENGTH 4

/*
*   Input: a string representing 1 'packet' of length PACKET_LENGTH
*   Returns: boolean representing whether there are any repeating characters in the packet
*/
bool tryPacket(string packet) {

    for (int i = 0; i < packet.length(); i++ ) {

        for (int j = i + 1; j < packet.length(); j++) {
            if (packet[i] == packet[j]) {
                return false;
            }
        }

    }

    return true;

}

/*
*   Input: string representing a datastream buffer
*   Returns: number of characters that must be checked before a valid packet was found
*/
int getPacketPosition(string line) {

    int pos = 0;

    while ((pos + PACKET_LENGTH) <= line.length()) {

        string packet = line.substr(pos, PACKET_LENGTH);
        if (tryPacket(packet)) {
            return pos + PACKET_LENGTH;

        } else {
            pos++;
        }


    }

    throw invalid_argument("no valid packet found.");

}

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
    int charsTried = 0;

    while (getline(inputFile, readLine)) {
       charsTried = getPacketPosition(readLine);
    }

    cout << "The number of characters tried is: " << charsTried << "." << endl;

    return 0;


}