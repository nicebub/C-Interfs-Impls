// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#ifndef INCLUDE_ATOM2_H_
#define INCLUDE_ATOM2_H_

#include <unistd.h>

extern void Atom2_fillRandom(void);
extern int Atom2_length(const char* sr);
extern const char* Atom2_new(const char* str, const int len);
extern const char* Atom2_string(const char* str);
extern const char* Atom2_int(const long n);
extern void Atom2_closure(void(*func1)(const int bucketNum, int* cl, int* cl2),
						void(*func2)(const char* cur, int* cl, int* cl2,int(*Atom_lng)(const char* str)),
						void(*func3)(const int bucketNum,int* cl, int* cl2),int* cl, int* cl2);
#endif  // INCLUDE_ATOM2_H_
