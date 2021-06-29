// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#ifndef INCLUDE_ATOM_H_
#define INCLUDE_ATOM_H_

#include <unistd.h>

extern int Atom_length(const char* sr);
extern const char* Atom_new(const char* str, const int len);
extern const char* Atom_string(const char* str);
extern const char* Atom_int(const long n);
#endif  // INCLUDE_ATOM_H_
