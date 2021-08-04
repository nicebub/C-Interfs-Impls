// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#ifndef INCLUDE_DEFINES_H_
#define INCLUDE_DEFINES_H_

#define isBadPtr(p) (((p) == NULL) ? 1 : 0 || !"NULL POINTER")
//#define NEW(x) ((x)) = malloc(sizeof(*(x)));
//#define ALLOC(x) malloc((x))
//#define FREE(x) free(*(x)); *(x) = NULL
//#define REALLOC(x, y) reallocf((x), (y))
//#define REALLOC(x, y) realloc((x), (y))

#endif  // INCLUDE_DEFINES_H_
