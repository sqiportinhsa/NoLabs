#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

const size_t START_SIZE = 1000;
const size_t  STOP_SIZE = 10000;
const size_t       STEP = 1000;

hash_t hashfunc(uint64_t key) {
    srand((unsigned) time(0));
    return (hash_t) key;
}

Command *create_commands(size_t amount) {
    Command *commands = (Command*) calloc(amount, sizeof(Command));
    for (size_t i = 0; i < amount; ++i) {
        int cmd = rand() % 4;
        switch (cmd) {
            case 0:
                commands[i].type = ERASE;
            break;
            case 1:
                commands[i].type = FIND;
            break;
            default:
                commands[i].type = INSERT;
            break;
        }
        commands[i].key  = rand();
    }

    return commands;
}

int main() {
    for (size_t size = START_SIZE; size <= STOP_SIZE; size += STEP) {
        Command *cmds = create_commands(size);
        printf("chains,%zu,%ld\n", size, run_cmds_chains(cmds, size));
        printf("open,%zu,%ld\n",   size, run_cmds_open  (cmds, size));
        free(cmds);
    }
    return 0;
}