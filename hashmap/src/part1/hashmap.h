#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"
#include "hash.h"

struct ChainsHashMap {
    hashfunc_t hashfunc = nullptr;
    List *array = nullptr;
    size_t array_size = 0;
};

ChainsHashMap    *hashmap_create  (hashfunc_t hashfunc, size_t array_size);
void        hashmap_insert(ChainsHashMap *hashmap, key_type key);
Node       *hashmap_find  (ChainsHashMap *hashmap, key_type key);
void        hashmap_dtor  (ChainsHashMap *hashmap);

#endif