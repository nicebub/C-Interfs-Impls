// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x
// INCLUDES BEST VERSION OF ATOM_LENGTH
#ifndef INCLUDE_ATOM5_H_
#define INCLUDE_ATOM5_H_

#include <unistd.h>

extern void Atom_free(const char * str);
extern void Atom_reset(void);
extern void Atom_vload(const char *str, ...);
extern void Atom_aload(const char * strs[]);
extern const char* Atom_add(const char* str, int len);

extern void Atom5_init(const long hint);
extern void Atom5_fillRandom(void);
extern int Atom5_length(const char* sr);
extern const char* Atom5_new(const char* str, const int len);
extern const char* Atom5_string(const char* str);
extern const char* Atom5_int(const long n);
extern void Atom5_closure(void(*func1)(const long bucketNum, long* cl, long** cl2),
						void(*func2)(const char* cur, long* cl, long** cl2,
						int(*Atom_lng)(const char* str)),
						void(*func3)(const long bucketNum, long* cl, long** cl2),
					 long* cl, long** cl2);
#endif  // INCLUDE_ATOM5_H_
