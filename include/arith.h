// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#ifndef INCLUDE_ARITH_H_
#define INCLUDE_ARITH_H_

extern int Arith_max(const int x, const int y);
extern int Arith_min(const int x, const int y);
extern int Arith_div(const int x, const int y);
extern int Arith_mod(const int x, const int y);
extern int Arith_ceiling(const int x, const int y);
extern int Arith_floor(const int x, const int y);

#endif  // INCLUDE_ARITH_H_
