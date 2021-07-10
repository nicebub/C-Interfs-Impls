// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#ifndef INCLUDE_ATOM_H_
#define INCLUDE_ATOM_H_

#include <unistd.h>

extern void Atom_fillRandom();
extern int Atom_length(const char* sr);
extern const char* Atom_new(const char* str, const int len);
extern const char* Atom_string(const char* str);
extern const char* Atom_int(const long n);
extern void Atom_closure(void(*func1)(const int bucketNum, int* cl, int* cl2),
						void(*func2)(void* cur, int* cl, int* cl2),
						void(*func3)(const int bucketNum,int* cl, int* cl2),int* cl, int* cl2);
#endif  // INCLUDE_ATOM_H_
