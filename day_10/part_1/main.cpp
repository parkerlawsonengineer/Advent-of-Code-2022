#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

enum CPU_STATE {
    BUSY,
    READY
};

#define NOOP_CYCLES 1
#define ADDX_CYCLES 2

enum INSTRUCTION {
    NOOP,
    ADDX,
};

class CPU {

    private:
        CPU_STATE state;
        vector<int> cyclesToCheck;
        map<int, int> cycleResults;
        int registerX;
        int cycleNumber;
        INSTRUCTION currentInstruction;
        int instructionVal;
        int instructionCyclesLeft;

        /*
        *   Input: string line of input from input.txt, in the format of "INSTRUCTION VALUE", where VALUE is present only
        *   if the instruction is ADDX.
        *   Returns: INSTRUCTION (enum) value corresponding to the instruction defined by the string
        */
        INSTRUCTION getInstruction(string line) {
            if (line[0] == 'n') {
                return NOOP;
            } else {
                return ADDX;
            }
        }

        /*
        *   Input: string line of input from input.txt, in the format of "INSTRUCTION VALUE", where VALUE is present only
        *   if the instruction is ADDX.
        *   Returns: integer value defined as parameter for addx instruction.
        */
        int getIntValue(string line) {
            int pos = line.find(" ");
            string val = line.substr(pos, line.length() - pos);
            return stoi(val);
        }

    public:
        
        /*
        *   Input: vector indicating which cycles we are saving the contents of register X (1-indexed)
        *   Description: initializes CPU with default values
        */
        CPU(vector<int> _cyclesToCheck) {

            this->cyclesToCheck = _cyclesToCheck;
            this->cycleNumber = 1;
            this->state = READY;
            this->registerX = 1;

        }

        /*
        *   Returns: boolean value indicating whether the CPU has finished with it's previous instruction and is ready
        *   for a new one to be loaded.
        */
        bool isReady() {
            if (this->state == READY) {
                return true;
            } else {
                return false;
            }
        }

        /*
        *   Input: string line of input from input.txt, in the format of "INSTRUCTION VALUE", where VALUE is present only
        *   if the instruction is ADDX.
        *   Description: loads the instruction (and optionally the value of the addx parameter) into the CPU and prepares
        *   it to execute the instruction on the next runCycle().
        */
        void loadInstruction(string line) {

            INSTRUCTION instr = this->getInstruction(line);
            int instrVal = 0;

            if (instr == ADDX) {
                instrVal = this->getIntValue(line);
            }

            this->currentInstruction = instr;
            this->instructionVal = instrVal;

            this->state = BUSY;

            switch (this->currentInstruction) {
                case NOOP:
                    this->instructionCyclesLeft = NOOP_CYCLES;
                    break;
                case ADDX:
                    this->instructionCyclesLeft = ADDX_CYCLES;
            }

        }

        /*
        *   Description: runs a 'cycle' of the cpu, checking to see if the current cycle is one marked for observation.
        *   if we are observing this cycle, the cycle number and the value of register X are added to a map<int,int> that
        *   will allow us to calculate signal strength values later on.
        */
        void runCycle() {
            
            for (vector<int>::iterator ptr = this->cyclesToCheck.begin(); ptr < this->cyclesToCheck.end(); ptr++) {
                if (*ptr == this->cycleNumber) {
                    this->cycleResults.insert(pair<int, int>(this->cycleNumber, this->registerX));
                }
            }

            switch (this->currentInstruction) {
                case NOOP:
                    break;
                case ADDX:
                    if (this->instructionCyclesLeft == 1) {
                        this->registerX += this->instructionVal;
                    }
                    break;
            }

            this->cycleNumber++;
            this->instructionCyclesLeft--;
            
            if (this->instructionCyclesLeft == 0) {
                this->state = READY;
            }

        }

        /*
        *   Returns: total signal strength value.
        *   Description: iterates through the register X values for each cycle that was marked for observation when the 
        *   CPU was initialized. A signal strength is calculated for each by multiplying the cycle number by the register
        *   value. These scores are totaled and returned as the total signal strength of the program.
        */
        int getTotalSignalStrength() {

            int total = 0;

            for (map<int, int>::iterator ptr = this->cycleResults.begin(); ptr != this->cycleResults.end(); ptr++) {
                int score = ptr->first * ptr->second;
                total += score;
            }

            return total;

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
    int cyclesToCheckArr[] = { 20,60,100,140,180,220 };
    vector<int> cyclesToCheck(cyclesToCheckArr, cyclesToCheckArr + sizeof(cyclesToCheckArr) / sizeof(cyclesToCheckArr[0]));
    CPU cpu(cyclesToCheck);

    while (getline(inputFile, readLine)) {

        if (cpu.isReady()) {
            cpu.loadInstruction(readLine);
        }
        while (!cpu.isReady()) {
            cpu.runCycle();
        }
        
    }

    int total = cpu.getTotalSignalStrength();

    //print result
    cout << "The total signal strength calculated is: " << total << "." << endl;

    return 0;


}