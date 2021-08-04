// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// the code in this main file is mostly ,if not all mine and not from the book

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#ifndef _INCLUDE_MEM_H
#define _INCLUDE_MEM_H

#include "include/except.h"

extern const Except_T Mem_Failed;

extern void *Mem_alloc(long nbytes, const char *file, int line);
extern void *Mem_calloc(long count, long nbytes, const char* file, int line);
extern void Mem_free(void* ptr,const char* file, int line);
extern void *Mem_resize(void* ptr, long nbytes, const char* file, int line);

#ifdef NDEBUG
	extern void Mem_stats(int type,const char* file, int line);
	#define STATS Mem_stats(3,__FILE__,__LINE__);
#else
	#define STATS
#endif

#define FREE(ptr) ((void)(Mem_free((ptr),\
	__FILE__,__LINE__), (ptr) = 0))

#define RESIZE(ptr, nbytes) ((ptr) = Mem_resize((ptr),\
	(nbytes), __FILE__, __LINE__))

#define ALLOC(nbytes) \
	Mem_alloc((nbytes), __FILE__,__LINE__)

#define CALLOC(count,nbytes) \
	Mem_calloc((count),(nbytes), __FILE__,__LINE__)

#define NEW(x) ((x) = ALLOC((long)sizeof *(x)))
#define NEWO(x) ((x) = CALLOC(1,(long) sizeof *(x)))


#endif  // _INCLUDE_MEM_H
