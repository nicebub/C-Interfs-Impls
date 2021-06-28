// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include <stddef.h>
#include "include/assert.h"
#include "include/mem.h"
#include "include/stack.h"

#define T Stack_T
struct T {
	int count;
	struct elem {
		void* x;
		struct elem *link;
		} *head;
};

T Stack_new(void) {
	T stack;
	NEW(stack);
	stack->count = 0;
	stack->head = NULL;
	return stack;
}

int Stack_empty(const struct T* stack) {
	assert(stack);
	return stack->count == 0;
}

void Stack_push(T stack, void* x) {
	struct elem* t;

	assert(stack);
	NEW(t);
	t->x = x;
	t->link = stack->head;
	stack->head = t;
	stack->count++;
}
void* Stack_pop(T stack) {
	void* x;
	struct elem*  t;
	assert(stack);
	assert(stack->count > 0);
	t = stack->head;
	stack->head = t->link;
	stack->count--;
	x = t->x;
	FREE(t);
	return x;
}

void Stack_free(T* stack) {
	struct elem*t, *u;
	assert(stack && *stack);
	for( t = (*stack)->head; t; t = u ) {
		u = t->link;
		FREE(t);
	}
	FREE(*stack);
}
#undef T
