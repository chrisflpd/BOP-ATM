# BOP-ATM
## Overview
BOP-ATM is a simulation program for basic functions of an automated teller machine (ATM), written in the C language. The user can use their account or create a new one to carry out financial transactions (deposits, withdrawals, and transfers). Additionally, the user has the ability to check their account balance, account details, and transaction history. The user inputs the required data and makes selections by typing characters, while the corresponding data output is printed in a console window. Each account’s details, as well as all transactions that have taken place, are stored in relevant files.
## Compilation, Installation and Execution 
The program "BOP_ATM.cbp" (and the corresponding executable file) operates only on Windows software. To run it, you need to have the "BOP_ATM" folder downloaded on your computer and a compiler for the C programming language. Below are instructions related to the GNU Compiler Collection (GCC) compiler.
### Command line
To produce the .exe file yourself, firstly clone the project in your pc and open your command line.
To change directory to the cloned file, type
```
cd <path>
```
where path is the path of the "Source code" folder. To compile, type
```
gcc -c ATM.c user_interface.c file_access.c
```
To link and create the executable file BOP_ATM.exe, type
```
gcc ATM.o user_interface.o file_access.o -o BOP_ATM.exe
```
Finally, to run the programm, type
```
BOP_ATM.exe
```
### Codeblocks
An alternative approach is to use the integrated development environment CodeBlocks. Open the "BOP_ATM.cbp" file through the CodeBlocks application and, after selecting the main file ATM.c, use the "Build and run" function to compile and run the program.

For more details, check the documentation file: [BOP-ATM Documentation.pdf](https://github.com/chrisflpd/BOP-ATM/blob/main/BOP-ATM%20Documentation.pdf)
