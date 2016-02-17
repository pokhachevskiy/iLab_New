#ifndef CSTACK_H_INCLUDED
#define CSTACK_H_INCLUDED
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
const int STACK_MAX_SIZE = 100;
typedef char T;
using namespace std;
const unsigned int MAX_LENGTH = 2147483648, MULTIPLIER = 2, START_LEN = 2;


class CStack
{
	private:
		T* data;
		int pos;
		int len;
		void stack_resize(const int a);
		int Stack_OK()const;
	public:
		CStack();
		~CStack();
		void push(const T in);
		void pop (T& out);
		int is_empty()const;
		void Stack_Dump()const;
        void Assert_OK ()const;
};




#endif // CSTACK_H_INCLUDED
