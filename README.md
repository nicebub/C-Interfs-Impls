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

# - Chapter 3 -

Atom implentation and interface added.

`atom5.c` and `atom5.h` hold most current version with all exercise functions added

Inside the build directory, the executable created is `bin`

bin takes 2 arguments, the last argument is optional

1st argument is the filename to open, if no filename is given then the executable quits.

2nd argument is a hint of words that may be read and used to determine how many buckets use.  

# - chapter 4 -

C Exceptions and Assertions
Implemented the C Exception Interface of:

TRY
CATCH(e)
CATCH(e)
.
.
.

CATCH(e)
ELSE(e)
FINALLY(e)
END_TRY

assert inerface with an assert exception thrown

I'm still working on this. I would like to add Stack Traces, Open to debugger
and I need to

test whether the 1 longjmp version works.
