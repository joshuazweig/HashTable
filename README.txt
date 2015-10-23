Joshua Zweig
joshua.zweig@columbia.edu
Columbia University

The primary source implementation is in HashMap.c. 
Noted in this file are some reasosn that I had to slightly stray from the spec as a consequence of my using c to implement 
this HashMap. I'm a big fan of C and some of the KPCB companies I'm interested in certainly work in C, so I thought why not emphasize my low level chops! 
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


Why I chose to enact open addressing and linear probing
I originally considered implementing chaining as a strategy for collison resolution. However, the spec states the the load factor should never be greater than 1. With chaining, it is possible to achienve such a load factor so I decided for open addressing to accomedate this aspect of the spec. 
I chose linear probing over something like quadratic probing because quadratic probing does not always garuntee a space for an element to be set, even when there remain empty spaces in the table. Since open addressing can reduce the capacity of the table through lazy deletion, I opted for linear probing in an effort to mitigate this effect. 


