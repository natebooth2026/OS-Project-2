#include <iostream>
#include <fstream>

//constants for file parsing
const int NUM_OF_PROCESSES = 5;
const int NUM_OF_RESOURCES = 3;
const char FILE_NAME[] = "init.txt";

//file parsing function
bool fileParsed(std::ifstream&,  
               int[NUM_OF_PROCESSES][NUM_OF_RESOURCES], 
               int[NUM_OF_PROCESSES][NUM_OF_RESOURCES], 
               int[NUM_OF_RESOURCES]);

//banker's algorithm function
bool isSafe(int[NUM_OF_PROCESSES][NUM_OF_RESOURCES],
            int[NUM_OF_PROCESSES][NUM_OF_RESOURCES],
            int[NUM_OF_RESOURCES],
            int[NUM_OF_PROCESSES]);

int main(){
    //test for file opening test
    std::ifstream in(FILE_NAME);
    if(!in){ //file failed to open
        std::cerr << "File opening error.\n";
        return 1;
    } else { //file opened
        int alloc[NUM_OF_PROCESSES][NUM_OF_RESOURCES]; //holds per-process data on what has been allocated
        int max[NUM_OF_PROCESSES][NUM_OF_RESOURCES]; //holds per-process data on what each needs
        int available[NUM_OF_RESOURCES]; //holds available resources
        
        bool success = fileParsed(in, alloc, max, available); //holds result of file parsing

        if(success){ //file successfully was processed
            int sequence[NUM_OF_PROCESSES]; //holds order of processes in safe state case

            //initializes sequence items to invalid -1
            for(int i = 0; i < NUM_OF_PROCESSES; ++i){
                sequence[i] = -1;
            }

            bool safe = isSafe(alloc, max, available, sequence); //holds result of banker's alg
            if(safe){ //safe sequence found
                std::cout << "System is in a safe state." << std::endl;
                std::cout << "Safe sequence: ";

                //prints sequence
                for(int i = 0; i < NUM_OF_PROCESSES; ++i){ 
                    std::cout << "P" << sequence[i] << " ";
                }
                std::cout << std::endl;
            } else { //not in safe state
                std::cout << "System is NOT in a safe state." << std::endl;
                return 0;
            }
        } else { //file failed to process
            std::cerr << "File parsing error.\n";
            return 1;
        }
    }
}

//Banker's alg function, returns true if safe state and false if not
//Requires the allocation, max, and available data arrays and sequence array for safe state sequence result (if it exists)
bool isSafe(int alloc[NUM_OF_PROCESSES][NUM_OF_RESOURCES],
            int max[NUM_OF_PROCESSES][NUM_OF_RESOURCES],
            int available[NUM_OF_RESOURCES],
            int sequence[NUM_OF_PROCESSES]){
    //generates need data
    int need[NUM_OF_PROCESSES][NUM_OF_RESOURCES]; //holds per-process resource needs

    //calculates need
    for(int i = 0; i < NUM_OF_PROCESSES; ++i){
        for(int j = 0; j < NUM_OF_RESOURCES; ++j){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int successCounter = 0; //holds how many processes are in sequence[]

    int attempts[NUM_OF_PROCESSES]; //holds times that a process failed to be placed in sequence[]
    for(int i = 0; i < NUM_OF_PROCESSES; ++i) attempts[i] = 0; //initalizes attempts[]
    bool finished[NUM_OF_PROCESSES]; //holds if a process has been processed and placed in sequence[]
    for(int i = 0; i < NUM_OF_PROCESSES; ++i) finished[i] = false; //initalizes finished[]

    int tracker = 0; //holds iteration number

    //finds safety and safe sequence (if it exists)
    while(successCounter < NUM_OF_PROCESSES && attempts[tracker % NUM_OF_PROCESSES] < 3){
        //skips already finished processes
        if(finished[tracker % NUM_OF_PROCESSES]){
            ++tracker;
            continue;
        }

        int successes = 0; //holds num of resources that had successful request

        //checks for need[][] compared to available[]
        for(int j = 0; j < NUM_OF_RESOURCES; ++j){
            if(need[tracker % NUM_OF_PROCESSES][j] <= available[j]){
                ++successes;
            } else {
                break;
            }
        }

        //checks if allocation can be done to the process
        if(successes == NUM_OF_RESOURCES){ //need <= available
            sequence[successCounter] = tracker % NUM_OF_PROCESSES; //adds process to sequence

            //retrieves resources already allocated to process
             for(int j = 0; j < NUM_OF_RESOURCES; ++j) {
                available[j] += alloc[tracker % NUM_OF_PROCESSES][j];
            }

            finished[tracker % NUM_OF_PROCESSES] = true; //flags completion
            attempts[tracker % NUM_OF_PROCESSES] = 0; //wipes out attempt data
            ++successCounter; //moves to next elem in sequence[]
            ++tracker; //moves to next process
        } else { //need > available
            ++attempts[tracker % NUM_OF_PROCESSES]; //adds attempt
            ++tracker; //moves to next process
        }

        //absolute failure case (no successes)
        if(tracker >= NUM_OF_PROCESSES && successCounter == 0) return false;

        //solution case (no failures/corrected failures)
        if(successCounter == NUM_OF_PROCESSES) return true;
    }

    return false; //assumes error by failure to allocation in given attempts
}


//File input parsing and storing
//Requires the ifstream and arrays to store allocation, max, and available data
bool fileParsed(std::ifstream& in, 
               int alloc[NUM_OF_PROCESSES][NUM_OF_RESOURCES], 
               int max[NUM_OF_PROCESSES][NUM_OF_RESOURCES], 
               int available[NUM_OF_RESOURCES]){
    int semis = 0; //holds number of ';' found

    //parsing and storing in alloc[][] and max[][]
    for(int i = 0; i < NUM_OF_PROCESSES; ++i){
        bool successfulChar = true; //holds if the char read is valid

        //parsing and storing in alloc[][] and max[][]
        for(int j = 0; j < NUM_OF_RESOURCES; ++j){
            //checks for invalid character
            if(int(in.peek() - '0') >= 10 || int(in.peek() - '0') < 0){ 
                successfulChar = false; 
                break;
            }

            //stores input
            if(semis == 0) alloc[i][j] = int(in.get() - '0');
            if(semis == 1) max[i][j] = int(in.get() - '0');
        }

        //flags error condition if invalid char found
        if(!successfulChar) return false;

        //checks for semi-colon
        if(in.peek() == ';'){ //next char is ;
            ++semis;
            if(semis == 1) i = -1; //resets 'i' for input of max
            in.get(); //skips ';'
            in.get(); //skips '\n'
            in.get(); //skips blank line
        } else if (in.peek() == '\n'){ //next char is new-line (continue reading condition)
            in.get(); //skips '\n'
        } else { //error (invalid char)
            semis = 3;
            break; 
        }

        //flags error condition if invalid char found
        if(semis == 3) return false;
    }

    bool successfulChar = true; //holds if the char read is valid in available[] storing

    //parsing and storing in available
    for(int i = 0; i < NUM_OF_RESOURCES; ++i){
        if(int(in.peek() - '0') >= 10 || int(in.peek() - '0') < 0){
            successfulChar = false;
            break;
        }
        available[i] = int(in.get() - '0');
    }

    //flags error condition if invalid char found
    if(!successfulChar) return false;

    return true; //succeeded
}