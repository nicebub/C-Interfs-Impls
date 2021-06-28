# C Interfaces and Implementations - my modern approach

I will try to implement the code and potentially example program fixes, upgrades, etc

I will try to use the most modern style of C code I can, although it may not be quite the best the first time around

# 	- Chapter 1 -

Program double completed and implemented with changes from exercises at end of chapter.

Programs of code , dotProduct and the 2 distinct strcpy methods were implemented as well


#	- Chapter 2 -

Program arith.c has 4 arithmetic functions that have been extended per the exercises
-13/5 == -2 is volatile so it is computed at runtime and not compile time, even with 
optimization flags -O0, O1, -O2, -O3, -Os

Program stack.c implements stack.h with extensions including peek() and newWithSize(int)

isBadPtr(p) macro defined but simply checks for NULL for now

