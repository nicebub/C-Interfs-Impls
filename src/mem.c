// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// the code in this main file is mostly ,if not all mine and not from the book

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include <stdlib.h>
#include <stddef.h>
#include "include/assert.h"
#include "include/except.h"
#include "include/mem.h"
#include "include/defines.h"
const Except_T Mem_Failed = { "Allocation Failed" };

void* Mem_alloc(long nbytes, const char* file, int line) {
	void* ptr;
	
	assert(nbytes > 0);
	ptr = malloc(nbytes);
	if(ptr == NULL) {
		if(file == NULL)
			THROW(Mem_Failed);
		else
			Except_raise(&Mem_Failed,file,line);
	}
	return ptr;
}

void* Mem_calloc(long count, long nbytes, const char* file, int line) {
	void* ptr;
	assert(count > 0);
	assert(nbytes > 0);
	ptr = calloc(count,nbytes);
	if(ptr == NULL) {
		if(file == NULL)
			THROW(Mem_Failed);
		else
			Except_raise(&Mem_Failed,file,line);
	}
	return ptr;
}

void Mem_free(void* ptr, const char* file, int line) {
	if(ptr)
		free(ptr);
}
void* Mem_resize(void* ptr, long nbytes, const char* file, int line) {
	assert(!isBadPtr(ptr));
	ptr = realloc(ptr, nbytes);
	if(ptr == NULL) {
		if(file == NULL)
			THROW(Mem_Failed);
		else
			Except_raise(&Mem_Failed,file,line);
	}
	return ptr;
}