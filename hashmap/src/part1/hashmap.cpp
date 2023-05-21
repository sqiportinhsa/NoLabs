#include <stdlib.h>

#include "hashmap.h"

static void init_lists(List *array, size_t size);
static void free_lists(List *array, size_t size);

ChainsHashMap *hashmap_create(hashfunc_t hashfunc, size_t array_size) {
    ChainsHashMap *map = (ChainsHashMap*) calloc(1, sizeof(ChainsHashMap));
    if (!map) return nullptr;

    map->hashfunc   = hashfunc;
    map->array_size = array_size;

    map->array = (List*) calloc(array_size, sizeof(List));
    if (!map->array) {
        free(map);
        return nullptr;
    }

    init_lists(map->array, array_size);

    return map;
}

void hashmap_insert(ChainsHashMap *hashmap, key_type key) {
    if (hashmap_find(hashmap, key)) return;

    hash_t hash = hashmap->hashfunc(key) % hashmap->array_size;
    list_insert(hashmap->array + hash, key);
}

Node *hashmap_find(ChainsHashMap *hashmap, key_type key) {
    hash_t hash = hashmap->hashfunc(key) % hashmap->array_size;
    return list_find(hashmap->array + hash, key);
}

void hashmap_dtor(ChainsHashMap *hashmap) {
    free_lists(hashmap->array, hashmap->array_size);
    free(hashmap->array);
    free(hashmap);
}

static void init_lists(List *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        list_init(array + i);
    }
}

static void free_lists(List *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        list_dtor(array + i);
    }
}