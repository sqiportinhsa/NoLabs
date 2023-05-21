#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

//------------------------------------------------------------------------------------------------//

struct OpenNode {
    uint64_t key;
    bool is_empty;
    bool is_erased;
};

//------------------------------------------------------------------------------------------------//

static void      hashmap_init   (OpenNode *hashmap);
static void      hashmap_insert (OpenNode *hashmap, uint64_t key);
static OpenNode *hashmap_find   (OpenNode *hashmap, uint64_t key);
static void      hashmap_erase  (OpenNode *hashmap, uint64_t key);
static void      hashmap_dtor   (OpenNode *hashmap);

static OpenNode *hashmap_find_skip_graves(OpenNode *hashmap, hash_t hash, uint64_t key);
static OpenNode *hashmap_find_for_insert (OpenNode *hashmap, hash_t hash, uint64_t key);

//------------------------------------------------------------------------------------------------//

long run_cmds_open(Command *cmds, size_t cmds_amount) {
    OpenNode *hashmap = (OpenNode*) calloc(HASHMAP_SIZE, sizeof(OpenNode));
    hashmap_init(hashmap);

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

//-------------------------------------- HASHMAP -------------------------------------------------//

static void hashmap_init(OpenNode *hashmap) {
    for (size_t i = 0; i < HASHMAP_SIZE; ++i) {
        hashmap[i].is_empty = true;
    }
}

static void hashmap_dtor(OpenNode *hashmap) {
    free(hashmap);
}

static void hashmap_erase(OpenNode *hashmap, uint64_t key) {
    hash_t hash = hashfunc(key) % HASHMAP_SIZE;

    OpenNode *found = hashmap_find_skip_graves(hashmap, hash, key);
    if (!found) return;

    if (found->is_empty || found->is_erased) {
        return;
    }

    found->is_erased = true;
}

static void hashmap_insert(OpenNode *hashmap, uint64_t key) {
    hash_t hash = hashfunc(key) % HASHMAP_SIZE;

    OpenNode *found = hashmap_find_for_insert(hashmap, hash, key);
    if (!found) return;

    if (found->is_empty || found->is_erased) {
        found->key = key;
        found->is_empty = false;
    }
}

static OpenNode *hashmap_find(OpenNode *hashmap, uint64_t key) {
    hash_t hash = hashfunc(key) % HASHMAP_SIZE;
    return hashmap_find_skip_graves(hashmap, hash, key);
}

static OpenNode *hashmap_find_for_insert(OpenNode *hashmap, hash_t hash, uint64_t key) {
    size_t current = hash;

    if (hashmap[current].is_empty || hashmap[current].is_erased) {
        return &(hashmap[current]);
    } else if (hashmap[current].key == key) {
        return &(hashmap[current]);
    }

    current = (current + 1) % HASHMAP_SIZE;
    for (; current != hash; current = (current + 1) % HASHMAP_SIZE) {
        if (hashmap[current].is_empty || hashmap[current].is_erased) {
            return &(hashmap[current]);
        } else if (hashmap[current].key == key) {
            return &(hashmap[current]);
        }
    }

    return nullptr;
}

static OpenNode *hashmap_find_skip_graves(OpenNode *hashmap, hash_t hash, uint64_t key) {
    size_t current = hash;
    if (hashmap[current].is_empty) {
        return &(hashmap[current]);
    } 

    if (!(hashmap[current].is_erased) && hashmap[current].key == key) {
        return &(hashmap[current]);
    }

    current = (current + 1) % HASHMAP_SIZE;
    for (; current != hash; current = (current + 1) % HASHMAP_SIZE) {
        if (hashmap[current].is_erased) {
            continue;
        }

        if (hashmap[current].is_empty) {
            return &(hashmap[current]);
        } 
        
        if (hashmap[current].key == key) {
            return &(hashmap[current]);
        }
    }

    return nullptr;
}