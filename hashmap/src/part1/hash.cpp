#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

const hash_t CRC32_CONST = 0x04C11DB7;
const hash_t polynomial_var = 13;
const hash_t mult_base = 5381;


//----------------------------------------- INT HASHSES ------------------------------------------//

hash_t int_remainder_hash(int key) {
    return key;
}

hash_t int_bit_hash(int key) {
    return *((hash_t*)(&key));
}

hash_t int_miltiplication_hash(int key) {
    hash_t hash = mult_base;

    while (key != 0) {
        hash  = (hash << 5) + hash;
        hash += key % 10;
        key /= 10;
    }

    return hash;
}

//------------------------------------------ FLOAT HASHSES ---------------------------------------//

hash_t float_to_int_hash(float key) {
    return (hash_t) key;
}

hash_t float_bit_hash(float key) {
    return *((hash_t*)(&key));
}

//------------------------------------------ STRING HASHES ---------------------------------------//

hash_t string_len_hash(char *key) {
    return strlen(key);
}

hash_t string_sum_hash(char *key) {
    assert(key);
    hash_t sum = 0;
    char symbol = *key;

    while (symbol != 0) {
        sum += symbol;
        ++key;
        symbol = *key;
    }

    return sum;
}

hash_t string_sum_hash_other(char *key) {
    hash_t sum = 0;

    while(*key) {
        sum += *key;
        key++;
    }

    return sum;
}

hash_t string_polynomial_hash(char *key) {
    hash_t hash = 0;
    hash_t var  = 1;
    size_t len = strlen(key);

    for (size_t i = 0; i < len; ++i) {
        hash += var * *(key + i);
        var  *= polynomial_var;
    }

    return hash;
}

hash_t string_crc32_hash(char *key) {
    unsigned char sym = *key;
    unsigned int  crc = 0xFFFFFFFF; 
    unsigned int mask = 0;

    while (sym != 0) {
        crc = crc ^ sym;

        for (int j = 7; j >= 0; j--) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (CRC32_CONST & mask);
        }

        ++key;
        sym = *key;
    }

    return ~crc;
}