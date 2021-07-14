// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// the code in this main file is mostly ,if not all mine and not from the book

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x
#ifndef _INCLUDE_EXCEPT_H
#define _INCLUDE_EXCEPT_H
#include <setjmp.h>

#define T Except_T
typedef struct T {
	const char *reason;
 } T;

 typedef struct Except_Frame Except_Frame;
 struct Except_Frame {
	 Except_Frame *prev;
	 jmp_buf env;
	 const char * file;
	 int line;
	 int finally;
	 const T * exception;
 };
enum { Except_entered =0, Except_raised,
	Except_handled, Except_finalized }; 

extern Except_Frame* Except_stack;
extern const Except_T Assert_Failed;

void Except_raise(const T *e, const char *file, int line);

#define THROW(e) Except_raise(&(e), __FILE__, __LINE__)

#define RETHROW Except_raise(Except_frame.exception,\
	Except_frame.file, Except_frame.line)

#define RETURN switch (Except_stack = Except_stack->prev, 0) default : return

#define TRY do {\
	volatile int Except_flag;\
	Except_Frame Except_frame;\
	Except_frame.prev = Except_stack;\
	Except_stack = &Except_frame;\
	Except_frame.finally = 0;\
	Except_flag = setjmp(Except_frame.env);\
	if(Except_flag == Except_entered) {

#define CATCH(e) \
if(Except_flag == Except_entered)\
	Except_stack = Except_stack->prev;\
} else if (Except_frame.exception == &(e)) {\
	Except_flag = Except_handled;

#define ELSE \
if(Except_flag == Except_entered)\
	Except_stack = Except_stack->prev;\
	} else { \
		Except_flag = Except_handled;

#define FINALLY \
if(Except_flag == Except_entered)\
	Except_stack = Except_stack->prev;\
	} { \
		if(Except_flag == Except_entered) {\
			Except_flag = Except_finalized;\
			Except_stack.finally = 1;\
		}

#define END_TRY \
if(Except_flag == Except_entered)\
	Except_stack = Except_stack->prev;\
} if (Except_flag == Except_raised) RETHROW;\
	} while(0);


#undef T
#endif  // _INCLUDE_EXCEPT_H
