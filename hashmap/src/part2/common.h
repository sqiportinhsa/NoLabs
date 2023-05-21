#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>

enum Commands {
    INSERT,
    ERASE,
    FIND  
};

struct Command {
    enum Commands type;
    int key;
};

typedef uint32_t hash_t;
const size_t HASHMAP_SIZE = 1000000;

hash_t hashfunc(uint64_t key);

long run_cmds_chains(Command *cmds, size_t cmds_amount);
long run_cmds_open  (Command *cmds, size_t cmds_amount);

#endif