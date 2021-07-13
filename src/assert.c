// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// the code in this main file is mostly ,if not all mine and not from the book

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include "assert.h"
const Except_T Assert_Failed = { "Assertion failed" };

void (assert)(int e) {
	assert(e);
}