#pragma once

struct Stack {
    size_t capacity;
    size_t     size;
    size_t  el_size;
    void       *arr;
};

Stack* stack_ctr(size_t size, size_t el_size);
Stack* stack_dtr(Stack *stk);

int push (Stack *stk, void* buffer);
int top  (Stack *stk, void* buffer);
int pop  (Stack *stk);