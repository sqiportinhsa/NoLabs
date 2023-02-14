#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

static void arr_realloc(Stack *stk);


Stack* stack_ctr(size_t size, size_t el_size) {
    Stack *stk = (Stack*) calloc(1, sizeof(Stack));

    stk->el_size  = el_size;
    stk->capacity = size;
    stk->size     = 0;

    stk->arr = calloc(size, el_size);

    return stk;
}

Stack* stack_dtr(Stack *stk) {
    assert(stk != nullptr);
    
    free(stk->arr);
    free(stk);

    return nullptr;
}

int push(Stack* stk, void* buffer) {
    assert(stk    != nullptr);
    assert(buffer != nullptr);

    if (stk->size == stk->capacity) {
        arr_realloc(stk);
    }

    memcpy(stk->arr + (stk->el_size)*(stk->size), buffer, stk->el_size);
    stk->size++;

    return 1;
}

int top(Stack *stk, void* buffer) {
    assert(stk != nullptr);
    if (stk->size == 0) {
        printf("error in top\n");
        return 0;
    }

    memcpy(buffer, stk->arr + (stk->el_size)*(stk->size), stk->el_size);
    return 1;
}

int pop(Stack *stk) {
    assert(stk != nullptr);
    if (stk->size == 0) {
        printf("error in pop\n");
        return 0;
    }

    stk->size--;
    return 1;
}

static void arr_realloc(Stack *stk) {
    //printf("old capacity %d\n", stk->capacity);
    //printf("ptr before realloc: %p\n", stk->arr);
    stk->arr = realloc(stk->arr, stk->capacity * 2 * stk->el_size);
    //printf("realloc returns     %p\n", stk->arr);
    stk->capacity *= 2;
}