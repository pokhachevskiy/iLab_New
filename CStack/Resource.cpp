
//#include <stdio.h>
//#include <stdlib.h>
#include <conio.h>
#include <сstring>
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
//_____________________________________________________2147483
const unsigned int MAX_LENGTH = 2147483648, MULTIPLIER = 2, START_LEN = 32;
typedef char T;
Class CStack
{
	private:
		T* data;
		int pos;
		int len;
	public:
		CStack();
		~CStack();
		
}
CStack::CStack() : data(new T*(START_LEN)), pos (0), len(START_LEN)
{}
CStack::~CStack(): 
{
	delete(data);
	len = 0;
	pos = 0;
}
//____________________________________________________
typedef enum
{
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	STACK_NOT_WORK,
	NO_ERROR
} code_error;
//_____________________________________________________
typedef struct
{
	char* message;// = NULL;
	code_error code;// = NO_ERROR;
} Error;
//________________________________________________________
int is_ok(Stack_t* stack)
{
    return ((stack == NULL) || (stack->data == NULL) || (stack->len > MAX_LENGTH)) ? 1 : 0;
}
//________________________________________________________
int is_empty(Stack_t* stack)
{
    return (stack->pos == 0) ? 0 : 1;
}
//________________________________________________________
Error* my_error_ctor ()
{
    Error* This = (Error*)malloc(sizeof(Error));
    This->code = NO_ERROR;
    This->message = (T*)realloc(This->message, 30*sizeof(char));
    This->message = NULL;
    return This;
}
//_________________________________________________________

void my_error_dtor (Error *This)
{
   This->code = NO_ERROR;
   free(This->message);
   This->message = NULL;
}
//__________________________________________________________
Error dump(Stack_t* stack)
{
    Error *err_temp = NULL;
    err_temp = my_error_ctor(err_temp);
    if (is_ok(stack) == 1)
    {
        err_temp->code = STACK_NOT_WORK;
        err_temp->message = "STACK NOT WORK\n";
        return *err_temp;
    }
    else
        if (is_empty(stack) == 0)
        {
            err_temp->code = NO_ERROR;
            err_temp->message = "Stack is empty\n";

            return *err_temp;
        }
        else
        {
            for (size_t i = 0; i < stack->pos; i++)
                printf("%c data[%d]\n", stack->data[i], i);
            printf("number of elements %d \n", stack->pos);

            my_error_dtor(err_temp);
            return *err_temp;
        }
}
//_____________________________________________________________
Error stack_resize (Stack_t *stack, const char a)
{
    Error *err_temp;
    err_temp = NULL;
    err_temp = my_error_ctor(err_temp);

    if (is_ok(stack) == 1)
    {
        err_temp->code = STACK_NOT_WORK;
        err_temp->message = "STACK NOT WORK\n";
        return *err_temp;
    }

    if ((a == 0) && (stack->pos > 3*(stack->len)/8))
        stack->data = (T*)realloc (stack->data, (stack->len*sizeof(T))/2);
    if (a == 1)
    {
        stack->len *= MULTIPLIER;
        stack->data = (T*)realloc (stack->data, stack->len*sizeof(T));
    }
    if (stack->data != NULL)
    {
        my_error_dtor(err_temp);
    }
    else
    {
        err_temp->code = STACK_OVERFLOW;
        err_temp->message = "Stack is overflow\n";
    }

    return *err_temp;
}
//_______________________________________________________________
Error push(Stack_t *stack, T in)
{
    Error *err_temp = NULL;
    err_temp = my_error_ctor(err_temp);
    if (is_ok(stack) == 1)
    {
        err_temp->code = STACK_NOT_WORK;
        err_temp->message = "STACK NOT WORK\n";
        return *err_temp;
    }


    if (stack->pos == stack->len)
    {
        Error r_resize = stack_resize(stack, 1);
        if (r_resize.code != NO_ERROR)
            return r_resize;
    }
     if (is_ok(stack) == 1)
    {
        err_temp->code = STACK_NOT_WORK;
        err_temp->message = "STACK NOT WORK\n";
        return *err_temp;
    }


    stack->data[stack->pos++] = in;
  //  (void)dump(stack);
//why do you need dump after each push?

    my_error_dtor(err_temp);

    return *err_temp;
}
//_____________________________________________________
Error pop(Stack_t *stack, T* out)
{
    Error *err_temp = NULL;
    err_temp = my_error_ctor(err_temp);
    if (is_ok(stack) == 1)
    {
        err_temp->code = STACK_NOT_WORK;
        err_temp->message = "STACK NOT WORK\n";
        return *err_temp;
    }
    if (stack->pos == 0)
    {
        err_temp->code = STACK_UNDERFLOW;
        err_temp->message = "STACK IS UNDERFLOW\n";
        return *err_temp;
    }
    my_error_dtor(err_temp);
    *out = stack->data[--stack->pos];


    Error r_resize = stack_resize(stack, 0);
    if (r_resize.code != NO_ERROR)
        return r_resize;

    return *err_temp;
}
//_____________________________________________________

Stack_t* my_stack_ctor()
{
    Stack_t *temp_stack;
    temp_stack = (Stack_t*)malloc(sizeof(Stack_t));
    (*temp_stack).data = (T*)calloc(START_LEN, sizeof(T));
    (*temp_stack).pos = 0;
    (*temp_stack).len = START_LEN;
    return temp_stack;
}
//_______________________________________________________
Error my_stack_dtor(Stack_t* stack)
{
    Error *err_temp = NULL;
    err_temp = my_error_ctor(err_temp);
    if (is_ok(stack) == 1)
    {
        err_temp->code = STACK_NOT_WORK;
        err_temp->message = "STACK NOT WORK\n";
        return *err_temp;
    }
    else
    {
        free(stack->data);
        stack->data = NULL;
        stack->len = 0;
        stack->pos = 0;
        my_error_dtor(err_temp);
        return *err_temp;
    }
}
//_____________________________________________
int init(Stack_t* stack)
{


    if (stack == NULL)
        return 1;
    else
    {
        stack->pos = 0;
        stack->len = START_LEN;
        stack->data = (T*)memset((void*)stack->data, 0, START_LEN*sizeof(T));
        return (stack->data == NULL) ? 1 : 0;
    }
}
//________________________________________________
#endif
