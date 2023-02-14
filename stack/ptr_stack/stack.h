#pragma once

struct Element {
    void*    data;
    Element *prev;
};

struct Stack {
    int  el_size;
    int     size;
    Element *end;
};

Stack* stack_ctr(int el_size);
Stack* stack_dtr(Stack *stk);

int push (Stack *stk, void* buffer);
int top  (Stack *stk, void* buffer);
int pop  (Stack *stk);