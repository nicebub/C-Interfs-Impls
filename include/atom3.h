// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x
// INCLUDES MORE BYTES IN EACH ATOM TO STORE THE HASH, and lookup use
// in Atom_new, negligible changes from this in time except sometimes
// on my cpu it seems to take twice as long

#ifndef INCLUDE_ATOM3_H_
#define INCLUDE_ATOM3_H_

#include <unistd.h>

extern void Atom3_fillRandom(void);
extern int Atom3_length(const char* sr);
extern const char* Atom3_new(const char* str, const int len);
extern const char* Atom3_string(const char* str);
extern const char* Atom3_int(const long n);
extern void Atom3_closure(void(*func1)(const int bucketNum, int* cl, int* cl2),
						void(*func2)(const char* cur, int* cl, int* cl2,
						int(*Atom_lng)(const char* str)),
						void(*func3)(const int bucketNum, int* cl, int* cl2),
						int* cl, int* cl2);
#endif  // INCLUDE_ATOM3_H_
