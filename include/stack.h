// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#define T Stack_T
typedef struct T* T;

extern T Stack_new(void);
extern T Stack_newWithSize(int s);
extern int Stack_empty(const struct T* stack);
extern void Stack_push(T stack, void* x);
extern void* Stack_pop(T stack);
extern void* Stack_peek(T stack);
extern void Stack_free(T* stack);

#undef T
#endif  // INCLUDE_STACK_H_
