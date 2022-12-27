#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define SIZE_LIMIT 100000

struct ELF_FILE {
    string name;
    int size;
};

struct ELF_FOLDER {
    vector<ELF_FILE> files;
    vector<ELF_FOLDER> folders;
    string name;
    int size;
};

class ElfFilesystem {

    private:
        ELF_FOLDER root;
        string currentPath;

        /*
        *   Input: string containing the name of the folder to search for in the current path
        *   Returns: boolean value indicating whether a folder exists in the current path with the specified name
        *   Description: iterates through the current folder's vector of folders to see if there is one with the
        *   name specified in the 'folder' parameter
        */
        bool folderExistsInCurrentPath(string folder) {
            ELF_FOLDER *currentFolder = getFolderFromPath(currentPath, &(this->root));

            for (vector<ELF_FOLDER>::iterator ptr = currentFolder->folders.begin(); ptr < currentFolder->folders.end(); ptr++) {
                if (folder == ptr->name) {
                    return true;
                }
            }
            return false;
        }

        /*
        *   Input: string filename to check for
        *   Returns: boolean indicating whether the specified file exists in the folder specified by the currentPath variable
        */
        bool fileExistsInCurrentPath(string fileName) {
            ELF_FOLDER *currentFolder = getFolderFromPath(currentPath, &(this->root));

            for (vector<ELF_FILE>::iterator ptr = currentFolder->files.begin(); ptr < currentFolder->files.end(); ptr++) {
                if (fileName == ptr->name) {
                    return true;
                }
            }

            return false;
        }

        /*
        *   Input: ELF_FOLDER *current - pointer to "current" folder (usually this will be root when called from another function)
        *           string pathFromFolder - the path from the "current" folder to the folder we're searching for
        *   Returns: ELF_FOLDER pointer to the folder described by the pathFromFolder string
        *   Description: This function is called recursively, and moves down a tree of folders to return a pointer to the
        *   specified folder.
        */
        ELF_FOLDER* getFolderFromPath(string pathFromFolder, ELF_FOLDER *current) {

            if (pathFromFolder == "") {
                return current;
            } else {
                int pos = pathFromFolder.find("/", 1); //skip first character, as it will always be a "/"
                string folderName, newPath;

                if (pos == string::npos) { //no path left after this folder
                    newPath = "";
                    folderName = pathFromFolder.substr(1, pathFromFolder.length() - 1);
                } else {
                    newPath = pathFromFolder.substr(pos, pathFromFolder.length() - pos);
                    folderName = pathFromFolder.substr(1, pos - 1);
                }  

                for (vector<ELF_FOLDER>::iterator ptr = current->folders.begin(); ptr < current->folders.end(); ptr++) {
                    if (folderName == ptr->name) {
                        return getFolderFromPath(newPath, &(*ptr));
                    }
                }

                //if we got this far, something went wrong
                throw invalid_argument("Folder must exist before it can be moved to.");


            }

        }

        /*
        *   Description: called when command is "$ cd ..", moves the current path variable up one folder
        */
        void moveUpFolder() {

            int pos = this->currentPath.find_last_of('/');
            string newPath = this->currentPath.substr(0, pos);
            this->currentPath = newPath;

        }

        /*
        *   Input: string folder - name of folder to create
        *   Description: creates a new folder in the directory described by the currentPath variable, using the 
        *   input parameter as a name
        */
        void createFolderInCurrentPath(string folder) {

            ELF_FOLDER *currentFolder = getFolderFromPath(currentPath, &(this->root));

            ELF_FOLDER newFolder;
            newFolder.name = folder;

            currentFolder->folders.push_back(newFolder);

        }

        /*
        *   Input: string filename and int filesize describing the file to create
        *   Description: creates a new file in the directory described by the currentPath variable using the input parameters
        */
        void createFileInCurrentPath(string fileName, int fileSize) {

            ELF_FOLDER *currentFolder = getFolderFromPath(currentPath, &(this->root));

            ELF_FILE newFile;
            newFile.name = fileName;
            newFile.size = fileSize;

            currentFolder->files.push_back(newFile);

        }

        /*
        *   Input: string containing the name of the folder to move into
        *   Description: Checks whether the specified folder exists, creates it if it doesn't, then moves the 
        *   current path to that folder
        */
        void moveIntoChildFolder(string dest) {
            
            if (!folderExistsInCurrentPath(dest)) {
                createFolderInCurrentPath(dest);
            }
            this->currentPath += "/" + dest;

        }

        /*
        *   Input: string line from input file, must be a cd command (e.g. "$ cd folder")
        *   Description: determines whether the cd command is moving to a specific folder, moving up a folder, or moving 
        *   back to the root.
        */
        void doCDCommand(string line) {

            //separate 'destination' from command (e.g. "$ cd folder", we just want "folder")
            int pos = line.find_last_of(' ');
            string dest = line.substr(pos + 1, line.length() - pos);

            if (dest == "/") {
                this->currentPath = ""; //go back to root
            } else if (dest == "..") {
                moveUpFolder();
            } else {
                moveIntoChildFolder(dest);
            }


        }

        /*
        *   Input: string line from input file
        *   Description: determines which terminal command is being executed and passes to the correct function for handling
        */
        void parseCommand(string line) {
            

            if (line[2] == 'c') { //command is 'cd' ('$ cd')
                doCDCommand(line);
            } else { //command is 'ls' ('$ ls')
                return; //we don't need to do anything here to handle 'ls' commands, it's handled by parseOutput
            }

        }

        /*
        *   Input: string line from input file, must be ouput of 'ls' command (e.g. "dir asdfdasf" or "195973 file.txt")
        *   Description: determines whether output line is describing a directory or a file, then creates the file or directory
        *   if it doesn't exist yet.
        */
        void parseOutput(string line) {
            
            if (line[0] == 'd') { //this denotes a directory (e.g. "dir asdfasdf")
                
                int pos = line.find(" ");
                string folderName = line.substr(pos + 1, line.length());

                if(!folderExistsInCurrentPath(folderName)) {
                    createFolderInCurrentPath(folderName);
                }

            } else { //otherwise, it's a file
                
                int pos = line.find(" ");
                string fileSizeString = line.substr(0, pos);
                int fileSize = stoi(fileSizeString);
                string fileName = line.substr(pos + 1, line.length());
                
                if (!fileExistsInCurrentPath(fileName)) {
                    createFileInCurrentPath(fileName, fileSize);
                }

            }

        }

        /*
        *   Input: ELF_FOLDER pointer to folder to recursively calculate size of
        *   Description: Recursively loops through folders to update size variable of folders
        */
        void populateFolderSize(ELF_FOLDER *folder) {

            int total = 0;

            //loop through files in folder, adding to total
            for (vector<ELF_FILE>::iterator ptr = folder->files.begin(); ptr < folder->files.end(); ptr++) {
                total += ptr->size;
            }

            for (int i = 0; i < folder->folders.size() ; i++) {
                populateFolderSize(&(folder->folders[i]));
                total += folder->folders[i].size;
            }

            folder->size = total;

        }

        /*
        *   Input: ELF_FOLDER folder to calculate sizes for
        *   Returns: total sizes of all folders with a size under the SIZE_LIMIT
        */
        int getTotalSizeOfFoldersUnderLimitRecursive(ELF_FOLDER folder) {

            int total = 0;

            for (vector<ELF_FOLDER>::iterator ptr = folder.folders.begin(); ptr < folder.folders.end(); ptr++) {

                total += getTotalSizeOfFoldersUnderLimitRecursive(*ptr);

            }

            if (folder.size <= SIZE_LIMIT) {
                total += folder.size;
            }

            return total;

        }

    public:

        /*
        *   Description: initializes empty filesystem
        */
        ElfFilesystem() {
            this->root.name = "";
        }
        
        /*
        *   Input: string line from input file
        *   Description: determines whether line from input file is a new command or output from the previous command, 
        *   then sends it to the correct function for handling.
        */
        void parseLine(string line) {

            if (line[0] == '$') { //this is a new function
                this->parseCommand(line);
            } else { //continuing from a previous function
                this->parseOutput(line);
            }

        }

        /*
        *   Description: public wrapper of private populateFolderSize function
        */
        void calculateSizes() {
            this->populateFolderSize(&(this->root));
        }

        /*
        *   Returns: total size of all folders under SIZE_LIMIT
        *   Description: public wrapper of getTotalSizeOfFoldersUnderLimitRecursive function
        */
        int calculateTotalSizeOfFoldersUnderLimit() {
            int total = getTotalSizeOfFoldersUnderLimitRecursive(this->root);
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
    ElfFilesystem files;

    while (getline(inputFile, readLine)) {
        files.parseLine(readLine);
    }

    files.calculateSizes();
    int total = files.calculateTotalSizeOfFoldersUnderLimit();

    //print result
    cout << "Total size of files under " << SIZE_LIMIT << " bytes: " << total << "." << endl;

    return 0;


}