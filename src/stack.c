// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include <stddef.h>
#include <stdlib.h>
//#include <assert.h>
  #include "include/assert.h"
//  #include "include/mem.h" for later
#include "include/stack.h"
#include "include/defines.h"
#define MAGIC_ID 999
//#define NEW(x) x = malloc(sizeof(*(x)))

extern const Except_T Mem_Failed;// = { "Cannot Allocate Memory" };

#define T Stack_T
struct T {
	int id;
	int count;
	struct elem {
		void* x;
		struct elem *link;
		} *head;
};

T Stack_new(void) {
	T stack;
	NEW(stack);
	if(stack == NULL) THROW(Mem_Failed);
	stack->count = 0;
	stack->head = NULL;
	stack->id = MAGIC_ID;
	return stack;
}

T Stack_newWithSize(int s) {
	T stack;

	assert(s >= 0);

	stack = Stack_new();
	for(int i = 0; i < s; i++)
		Stack_push(stack, NULL);
	return stack;
}

int Stack_empty(const struct T* stack) {
	assert(!isBadPtr(stack) && (stack->id == MAGIC_ID));
	return stack->count == 0;
}

void Stack_push(T stack, void* x) {
	struct elem* t;

	assert(!isBadPtr(stack) && (stack->id == MAGIC_ID));
	NEW(t);
	if(isBadPtr(t)) THROW(Mem_Failed);
	t->x = x;
	t->link = stack->head;
	stack->head = t;
	stack->count++;
}
void* Stack_peek(T stack) {
	assert(!isBadPtr(stack) && (stack->id == MAGIC_ID));
	assert(stack->count > 0);
	return stack->head->x;
}
//#define FREE(x) free((x))
void* Stack_pop(T stack) {
	void* x;
	struct elem*  t;
	assert(!isBadPtr(stack) && (stack->id == MAGIC_ID));
	assert(stack->count > 0);
	t = stack->head;
	stack->head = t->link;
	stack->count--;
	x = t->x;
	FREE(&t);
	return x;
}

void Stack_free(T* stack) {
	struct elem*t, *u;
	assert(!isBadPtr(stack) && !isBadPtr(*stack) && ((*stack)->id == MAGIC_ID));
	for( t = (*stack)->head; t; t = u ) {
		u = t->link;
		FREE(&t);
	}
	FREE(&stack);
}
#undef T
#undef MAGIC_ID
#undef isBadPtr
