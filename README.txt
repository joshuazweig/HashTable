Joshua Zweig
joshua.zweig@columbia.edu
Columbia University

The primary source implementation is in HashMap.c. 
hashmap.h defines the methods to be implemented in HashMap.c as well as the neseccary structures. 

The test driver program is hashmap-test.c and tests the basic functionality and edge cases 
for the implementation of the hashmap.

The Makefile contains the build definition for the code

To run the test program, simply type "make" into the command line
This will produce a runnable file called "hashmap-test"
To tun the file, enter "./hashmap-test" into the command line

Requirments:
gcc compiler (if you prefer a different compiler, simply replace gcc with the name of that compiler in the command line).
Sufficent memory for the malloc of the test structure. The program will exit immediatley if there is not enough storage. 
