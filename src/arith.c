// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include "include/arith.h"

int Arith_max(const int x, const int y) {
	return x > y ? x : y;
}
int Arith_min(const int x, const int y) {
	return x > y ? y : x;
}
int Arith_div(const int x, const int y) {
	volatile const int truncTop = -13;
	volatile const int truncBottom = 5;
	volatile const int truncDiv = -2;
	if((truncTop / truncBottom == truncDiv) && ((x < 0) != (y < 0)) && (x%y != 0))
		return x/y - 1;
	else
		return x/y;
}
int Arith_mod(const int x, const int y) {
	volatile const int truncTop = -13;
	volatile const int truncBottom = 5;
	volatile const int truncDiv = -2;
	if((truncTop / truncBottom == truncDiv) && ((x < 0) != (y < 0)) && (x%y != 0))
		return x%y + y;
	else
		return x%y;
}
int Arith_ceiling(const int x, const int y) {
	return Arith_div(x, y) + (x%y != 0);
}
int Arith_floor(const int x, const int y) {
	return Arith_div(x, y);
}
