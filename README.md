# Nate's Bank

## Introduction
This project was to implement the deadlock avoidance banker's algorithm using a provided allocation, max, and available matrix.

The following include statements are used in the code (REQUIRED libraries):
```
#include <iostream>
#include <fstream>
```

Some challenges I faced were trying to figure out what I needed to add to the available matrix after a process was processed and figuring out how to implement my attempts and finished arrays.

## Running the Project
Fork this repository into a Linux/Unix-compatible interface (ex. VSCode) and run the following lines in sequence for optimal performance:
```
g++ banker.cpp -o banker
./banker
```
To properly run this program, init.txt has been set up to an inital state to be parsed in function `fileParsed()`.

To experiment with different setups, you must change the values in the varaibles `NUM_OF_PROCESSES`, `NUM_OF_RESOURCES`, and `FILE_NAME` if necessary and follow the following format in your text file:
```
[process 0 allocated row, no spaces and one-digit per resource]
[process 1 allocated row, no spaces and one-digit per resource]
...
[process n allocated row, no spaces and one-digit per resource];

[process 0 max row, no spaces and one-digit per resource]
[process 1 max row, no spaces and one-digit per resource]
...
[process n max row, no spaces and one-digit per resource];

[available row for n resources, no space and one-digit per resource];
```

DO NOT INCLUDE ANY `...` IN YOUR TEXT FILE (please see init.txt for an example of this format). Make sure to recompile (using the provided `g++` line above) if you changed variable values in the code.

## Example Outputs
This program will print out a statement indicating if the system is in a safe state or not.
If it is safe, it will print out the sequence denoted `PX` (`X` is the process number). Examples:

Safe System

<img width="300" alt="p2SafeExample" src="https://github.com/user-attachments/assets/3c0a8216-e7e9-4660-bf56-ae3c2d76e5ee">


Unsafe System

<img width="300" alt="p2UnsafeExample" src="https://github.com/user-attachments/assets/c7019f92-d6d2-455d-9aab-0285b81c8c44">


### Errors
Please be careful to make sure the file format and constant variable values (see above) are correct otherwise you may see errors like these:

<img width="200" alt="p2FileOpenError" src="https://github.com/user-attachments/assets/da270db4-787a-45db-9ee1-05ca00048dec">


The file did not open properly.


<img width="200" alt="p2FileParseError" src="https://github.com/user-attachments/assets/e37d52e9-178d-43aa-929b-246acf48e78f">

`fileParsed()` either saw an invalid character, the values of `NUM_OF_PROCESSES` and/or `NUM_OF_RESOURCES` were invalid, or the file was in the wrong format.

## Thank You
Thank you for checking out my project and thanks for reading! :D
