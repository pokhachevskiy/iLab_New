#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

const int STACK_MAX_SIZE = 100;
typedef char T;
typedef struct Stack_tag
{
    T* data;
    int pos;
    int len;
} Stack_t;

typedef enum
{
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	STACK_NOT_WORK,
	NO_ERROR
} code_error;

typedef struct
{
	char* message;// = NULL;
	code_error code;// = NO_ERROR;
} Error;

int init(Stack_t*);

Error* my_error_ctor ();

void my_error_dtor (Error*);

Error stack_resize (Stack_t *stack, const char a);


Error push(Stack_t *stack, T in);
Error pop(Stack_t *stack, T *out);


int is_ok(Stack_t*);		   // Checks, if stack is in work state.

int is_empty(Stack_t*);

Stack_t* my_stack_ctor(Stack_t*); // constructor

Error my_stack_dtor(Stack_t*);
Error dump(Stack_t*);

#endif // STACK_H_INCLUDED
