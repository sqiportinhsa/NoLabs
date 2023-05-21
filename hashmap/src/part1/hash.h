#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include <stdio.h>

#define STRING_KEY

#ifdef INT_KEY
typedef int key_type;
#elif defined FLOAT_KEY
typedef float key_type;
#else 
typedef char* key_type;
#endif

typedef uint32_t hash_t;
typedef hash_t (*hashfunc_t)(key_type key);

#ifdef INT_KEY
hash_t int_remainder_hash      (int key);
hash_t int_bit_hash            (int key);
hash_t int_miltiplication_hash (int key);

const hashfunc_t HASHFUNCS[] = {int_remainder_hash,
                                int_bit_hash,
                                int_miltiplication_hash};

const char* const HASHFUNC_NAMES[] = {"int_remainder_hash",
                                      "int_bit_hash",
                                      "int_miltiplication_hash"};

#elif defined FLOAT_KEY

hash_t float_to_int_hash (float key);
hash_t float_bit_hash    (float key);

const hashfunc_t HASHFUNCS[] = {float_to_int_hash,
                                float_bit_hash};

const char* const HASHFUNC_NAMES[] = {"float_to_int_hash",
                                      "float_bit_hash"};

#else 

hash_t string_len_hash        (char *key);
hash_t string_sum_hash        (char *key);
hash_t string_polynomial_hash (char *key);
hash_t string_crc32_hash      (char *key);

const hashfunc_t HASHFUNCS[] = {string_len_hash,
                                string_sum_hash,
                                string_polynomial_hash,
                                string_crc32_hash};

const char* const HASHFUNC_NAMES[] = {"string_len_hash",
                                      "string_sum_hash",
                                      "string_polynomial_hash",
                                      "string_crc32_hash"};
#endif

const size_t HASHFUNCS_SIZE = sizeof(HASHFUNCS) / sizeof(hashfunc_t);

#endif