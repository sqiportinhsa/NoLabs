#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#include "hash.h"

const size_t INITIAL_LIST_SIZE = 1;

struct Node {
    key_type key = 0;
};

struct List {
    size_t max_size = 0;
    size_t     size = 0;

    Node *nodes = nullptr;
};

void  list_init  (List *list);
void  list_dtor  (List *list);
void  list_insert(List *list, key_type key);
Node *list_find  (List *list, key_type key);

#endif 