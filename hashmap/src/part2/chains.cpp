#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

#define CHECK_NULLPTR(ptr) if (!ptr) return nullptr

//------------------------------------------------------------------------------------------------//

struct ChainsNode {
    int key;
    struct ChainsNode *next;
    struct ChainsNode *prev;
};

struct ChainsList {
    struct ChainsNode *first;
    size_t size;
};

struct ChainsHashMap {
    struct ChainsList *array;
};

//------------------------------------------------------------------------------------------------//

static ChainsHashMap *hashmap_create();
static void           hashmap_insert(ChainsHashMap *hashmap, int key);
static ChainsNode    *hashmap_find  (ChainsHashMap *hashmap, int key);
static void           hashmap_erase (ChainsHashMap *hashmap, int key);
static void           hashmap_dtor  (ChainsHashMap *hashmap);

static ChainsNode  *create_node   (int key, ChainsNode *next);

static ChainsNode  *list_find   (ChainsList *list, int key);
static void         list_init   (ChainsList *list);
static void         list_dtor   (ChainsList *list);
static void         list_insert (ChainsList *list, int key);
static void         list_erase  (ChainsList *list, int key);

static void init_lists(ChainsList *array);
static void free_lists(ChainsList *array);

//------------------------------------ INPUT + OUTPUT --------------------------------------------//

long run_cmds_chains(Command *cmds, size_t cmds_amount) {
    ChainsHashMap *hashmap = hashmap_create();

    clock_t start = clock();
    for (size_t i = 0; i < cmds_amount; ++i) {
        switch (cmds[i].type) {
            case INSERT:
                hashmap_insert(hashmap, cmds[i].key);
                break;
            case FIND:
                hashmap_find(hashmap, cmds[i].key);
                break;
            case ERASE:
                hashmap_erase(hashmap, cmds[i].key);
                break;
            default:
                assert(0 && "unknow command");
                break;
        }
    }
    clock_t end = clock();
    long time = (end - start) * 1000 / CLOCKS_PER_SEC;

    hashmap_dtor(hashmap);
    return time;
}

//---------------------------------------- HASHMAP -----------------------------------------------//

static ChainsHashMap *hashmap_create() {
    ChainsHashMap *map = (ChainsHashMap*) calloc(1, sizeof(ChainsHashMap));
    if (!map) return nullptr;

    map->array = (ChainsList*) calloc(HASHMAP_SIZE, sizeof(ChainsList));
    if (!map->array) {
        free(map);
        return nullptr;
    }

    init_lists(map->array);

    return map;
}

static void hashmap_insert(ChainsHashMap *hashmap, int key) {
    if (hashmap_find(hashmap, key)) return;

    hash_t hash = hashfunc(key) % HASHMAP_SIZE;
    list_insert(hashmap->array + hash, key);
}

static ChainsNode *hashmap_find(ChainsHashMap *hashmap, int key) {
    hash_t hash = hashfunc(key) % HASHMAP_SIZE;
    return list_find(hashmap->array + hash, key);
}

static void hashmap_erase(ChainsHashMap *hashmap, int key) {
    hash_t hash = hashfunc(key) % HASHMAP_SIZE;
    list_erase(hashmap->array + hash, key);
}

static void hashmap_dtor(ChainsHashMap *hashmap) {
    free_lists(hashmap->array);
    free(hashmap->array);
    free(hashmap);
}

static void init_lists(ChainsList *array) {
    for (size_t i = 0; i < HASHMAP_SIZE; ++i) {
        list_init(array + i);
    }
}

static void free_lists(ChainsList *array) {
    for (size_t i = 0; i < HASHMAP_SIZE; ++i) {
        list_dtor(array + i);
    }
}

//----------------------------------------- LIST -------------------------------------------------//

static void list_init(ChainsList *list) {
    list->size     = 0;
    list->first = nullptr;
}

static void list_dtor(ChainsList *list) {
    while (list->first) {
        ChainsNode *to_free = list->first;
        list->first = list->first->next;
        free(to_free);
    }
}

static void list_insert(ChainsList *list, int key) {
    list->first = create_node(key, list->first);
    if (list->first->next) {
        list->first->next->prev = list->first;
    }

    ++(list->size);
}

static void list_erase(ChainsList *list, int key) {
    ChainsNode *to_erase = list_find(list, key);
    if (!to_erase) return;

    if (to_erase->prev) to_erase->prev->next = to_erase->next;
    if (to_erase->next) to_erase->next->prev = to_erase->prev;

    if (list->first == to_erase) {
        list->first =  to_erase->next;
    }

    free(to_erase);
    --(list->size);
}

static ChainsNode *list_find(ChainsList *list, int key) {
    ChainsNode *current = list->first;
    while (current) {
        if (current->key == key) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

static ChainsNode *create_node(int key, ChainsNode *next) {
    ChainsNode *node = (ChainsNode*) calloc(1, sizeof(ChainsNode));
    CHECK_NULLPTR(node);

    node->next = next;
    node->key  = key;
    node->prev = nullptr;

    return node;
}