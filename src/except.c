// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// the code in this main file is mostly ,if not all mine and not from the book

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "except.h"

#define T Except_T

Except_Frame* Except_stack = NULL;

void Except_raise(const T *e, const char *file,
	int line) {
		Except_Frame *p = Except_stack;
		
		assert(e);
		if(p == NULL) {
			fprintf(stderr, "Uncaugt exception");
			if(e->reason)
				fprintf(stderr, " %s", e->reason);
			else
				fprintf(stderr, " at 0x%p", e);
				if(file && line > 0)
				fprintf(stderr, " raised at %s:%d\n", file, line);
			fprintf(stderr, "aborting...\n");
			fflush(stderr);
			abort();
		}
		p->exception = e;
		p->file = file;
		p->line = line;
		Except_stack = Except_stack->prev;
		longjmp(p->env, Except_raised);
	}