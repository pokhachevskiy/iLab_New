#ifndef CSTACK_H_INCLUDED
#define CSTACK_H_INCLUDED
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
const int STACK_MAX_SIZE = 100;
typedef int T;
using namespace std;
const int MULTIPLIER = 2, START_LEN = 32;


class CStack
{
	private:
		T* data;
		int pos;
		int len;
		void stack_resize(const int a);
		bool Stack_OK()const;
		static int number; // number of active Stacks
	public:
		CStack();
		~CStack();
		void push(const T in);
		void pop (T& out);
		bool is_empty()const;
		void Stack_Dump()const;
        void Assert_OK ()const;
        T& top();
        const T& top()const;
        const int size()const;
        T& operator[](const int temp_pos);
};





#endif // CSTACK_H_INCLUDED
