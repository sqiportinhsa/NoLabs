#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

static Element *create_elem(Element* prev, void* data, int el_size);
static Element *create_head();

static void delete_end(Stack *stk);


Stack* stack_ctr(int el_size) {
    Stack *stk = (Stack*) calloc(1, sizeof(Stack));

    stk->el_size = el_size;
    stk->size    = 0;
    stk->end     = nullptr;

    return stk;
}

Stack* stack_dtr(Stack *stk) {
    assert(stk != nullptr);
    while (stk->size > 0){
        delete_end(stk);
    }

    free(stk->end);
    free(stk);

    return nullptr;
}

int push(Stack* stk, void* buffer) {
    assert(stk    != nullptr);
    assert(buffer != nullptr);

    stk->end = create_elem(stk->end, buffer, stk->el_size);
    stk->size++;

    return 1;
}

int top(Stack *stk, void* buffer) {
    assert(stk != nullptr);
    if (stk->size == 0) {
        printf("error in top\n");
        return 0;
    }

    memcpy(buffer, stk->end->data, stk->el_size);
    return 1;
}

int pop(Stack *stk) {
    assert(stk != nullptr);
    if (stk->size == 0) {
        //printf("error in pop\n");
        return 0;
    }

    delete_end(stk);

    return 1;
}

static Element *create_elem(Element *prev, void* data, int el_size) {
    Element *elem = (Element*) calloc(1, sizeof(Element));
    elem->data    =            calloc(1, el_size);

    memcpy(elem->data, data, el_size);
    elem->prev = prev;

    return elem;
}

static Element *create_head() {
    Element *elem = (Element*) calloc(1, sizeof(Element));

    elem->data = nullptr;
    elem->prev = nullptr;

    return elem;
}

static void delete_end(Stack *stk) {
    assert(stk != nullptr);

    Element *end = stk->end;
    stk->end = end->prev;

    free(end->data);
    free(end);

    stk->size--;
}