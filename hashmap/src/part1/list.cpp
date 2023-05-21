
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static void list_resize(List *list);

void list_init(List *list) {
    list->max_size = 0;
    list->size     = 0;
    list->nodes = nullptr;
}

void list_dtor(List *list) {
    free(list->nodes);
}

void list_insert(List *list, key_type key) {
    if (list->size == list->max_size) {
        list_resize(list);
        assert(list->nodes);
    }

    list->nodes[list->size].key = key;
    ++(list->size);
}

static void list_resize(List *list) {
    if (!list->nodes) {
        list->nodes = (Node*) calloc(INITIAL_LIST_SIZE, sizeof(Node));
        list->max_size = INITIAL_LIST_SIZE;
        return;
    }

    list->nodes = (Node*) realloc(list->nodes, list->max_size * 2 * sizeof(Node));
    list->max_size *= 2;
}

#ifdef STRING_KEY

Node *list_find(List *list, key_type key) {
    const char *value = nullptr;
    for (size_t i = 0; i < list->size; ++i) {
        if (!strcmp(list->nodes[i].key, key)) {
            return list->nodes + i;
        }
    }
    return nullptr;
}

#else

Node *list_find(List *list, key_type key) {
    const char *value = nullptr;
    for (size_t i = 0; i < list->size; ++i) {
        if (list->nodes[i].key == key) {
            return list->nodes + i;
        }
    }
    return nullptr;
}


#endif
