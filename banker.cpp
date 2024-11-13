#include <iostream>
#include <fstream>

const int NUM_OF_PROCESSES = 5;
const int NUM_OF_RESOURCES = 3;
const char FILE_NAME[] = "init.txt";

bool fileInput(std::ifstream&,  
               int[NUM_OF_PROCESSES][NUM_OF_RESOURCES], 
               int[NUM_OF_PROCESSES][NUM_OF_RESOURCES], 
               int[NUM_OF_RESOURCES]);

bool isSafe(int[NUM_OF_PROCESSES][NUM_OF_RESOURCES],
            int[NUM_OF_PROCESSES][NUM_OF_RESOURCES],
            int[NUM_OF_RESOURCES],
            int[NUM_OF_PROCESSES]);

int main(){
    std::ifstream in(FILE_NAME);
    if(!in){
        std::cerr << "File opening error.\n";
        return 1;
    } else {
        int alloc[NUM_OF_PROCESSES][NUM_OF_RESOURCES];
        int max[NUM_OF_PROCESSES][NUM_OF_RESOURCES];
        int available[NUM_OF_RESOURCES];
        
        bool success = fileInput(in, alloc, max, available);

        if(success){
            int sequence[NUM_OF_PROCESSES];
            for(int i = 0; i < NUM_OF_PROCESSES; ++i){
                sequence[i] = -1;
            }

            bool safe = isSafe(alloc, max, available, sequence);
            if(safe){
                std::cout << "System is in a safe state." << std::endl;
                std::cout << "Safe sequence: ";

            } else {
                std::cout << "System is NOT in a safe state." << std::endl;
                return 0;
            }
        } else {
            std::cerr << "File parsing error.\n";
            return 1;
        }
    }
}

bool isSafe(int alloc[NUM_OF_PROCESSES][NUM_OF_RESOURCES],
            int max[NUM_OF_PROCESSES][NUM_OF_RESOURCES],
            int available[NUM_OF_RESOURCES],
            int sequence[NUM_OF_PROCESSES]){
    int need[NUM_OF_PROCESSES][NUM_OF_RESOURCES];
    for(int i = 0; i < NUM_OF_PROCESSES; ++i){
        for(int j = 0; j < NUM_OF_RESOURCES; ++j){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int successCounter = 0;

    int delayed[NUM_OF_PROCESSES];
    int delayedCounter = 0;

    for(int i = 0; i < NUM_OF_PROCESSES; ++i){
        int successes = 0;
        for(int j = 0; j < NUM_OF_RESOURCES; ++j){
            if(need[i][j] <= available[j]){
                ++successes;
            } else {
                break;
            }
        }
        if(successes == NUM_OF_RESOURCES){
            sequence[successCounter] = i;
            ++successCounter;
        } else {
            delayed[delayedCounter] = i;
            ++delayedCounter;
        }
    }

    if(counter == 0) return false;
    if(counter == 5) return true;

    //NEED TO CHECK DELAYED ARRAY AND RUN SIMULATIONS
}

bool fileInput(std::ifstream& in, 
               int alloc[NUM_OF_PROCESSES][NUM_OF_RESOURCES], 
               int max[NUM_OF_PROCESSES][NUM_OF_RESOURCES], 
               int available[NUM_OF_RESOURCES]){
    int semis = 0; //holds number of ';' found

    while(semis < 2){
        for(int i = 0; i < NUM_OF_PROCESSES; ++i){
            for(int j = 0; j < NUM_OF_RESOURCES; ++j){
                if(semis == 0) alloc[i][j] = int(in.get() - '0');
                if(semis == 1) max[i][j] = int(in.get() - '0');
            }

            if(in.peek() == ';'){
                ++semis;
                if(semis == 1) i = -1; //resets 'i' for input of max
                in.get(); //skips ';'
                in.get(); //skips '\n'
                in.get(); //skips blank line
            } else if (in.peek() == '\n'){
                in.get(); //skips '\n'
            } else { //error
                semis = 3;
                break; 
            }
        }

        if(semis == 3) return false;
    }

    for(int i = 0; i < NUM_OF_RESOURCES; ++i){
        available[i] = int(in.get() - '0');
    }

    return true;
}