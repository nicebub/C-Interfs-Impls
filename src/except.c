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

void Except_raise(const T *e, const char *file, const char* func,
	int line) {
		Except_Frame *p = Except_stack;
		
		assert(e);
    if(Except_stack == NULL){
	    fprintf(stderr, "Uncaught exception");
	    if(e->reason)
		    fprintf(stderr, " %s", e->reason);
	    else
		    fprintf(stderr, " at 0x%p", e);
	   if(file && line > 0){
		   if(func)
		    fprintf(stderr, " raised in %s at %s:%d\n", func, file, line);
		   else
			  fprintf(stderr, " raised at %s:%d\n", file, line);
	   }
	    fprintf(stderr, "aborting...\n");
	    fflush(stderr);
	    abort();
    }
		else{
			p->exception = e;
			p->file = file;
			p->line = line;
		    p->func = func;
//		    Except_Frame *q;
/*		    for(q = p ;q != NULL &&
			    q->exception != p->exception
			    && !q->finally;q = Except_stack->prev) {
					fprintf(stderr, "called from %s at %s:%d\n",q->file,
					q->file,q->line);
			}
		    Except_stack = q;*/
		}
		Except_stack = Except_stack->prev;
		longjmp(p->env, Except_raised);
	}
