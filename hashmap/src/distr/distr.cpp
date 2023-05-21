#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "distr.h"

static double get_time(hashfunc_t hashfunc, key_type *arr);

static void fill_hashmap(key_type *array, ChainsHashMap *hashmap);
static void get_and_report_distribution(hashfunc_t hashfunc, key_type *array, const char *hashfunc_name);
static void          print_distribution(const char *hashfunc_name, size_t *sizes);
static void            get_distribution(List *lists,         size_t *sizes);


void get_times(double *times, key_type *arr) {
    for (size_t i = 0;  i < HASHFUNCS_SIZE; ++i) {
        times[i] = get_time(HASHFUNCS[i], arr);
    }
}

void print_times(double *times) {
    for (size_t i = 0; i < HASHFUNCS_SIZE; ++i) {
        printf("%s,%lf\n", HASHFUNC_NAMES[i], times[i]);
    }
}

void get_and_report_all_distributions(key_type *array) {
    // for (size_t i = 0; i < HASHFUNCS_SIZE; ++i) {
        // get_and_report_distribution(HASHFUNCS[i], array, HASHFUNC_NAMES[i]);
    // }

    get_and_report_distribution(HASHFUNCS[1], array, HASHFUNC_NAMES[1]);
}

static void get_and_report_distribution(hashfunc_t hashfunc, key_type *array, const char *hashfunc_name) {
    ChainsHashMap *hashmap = hashmap_create(hashfunc, HASHMAP_SIZE);
    fill_hashmap(array, hashmap);
    size_t sizes[HASHMAP_SIZE] = {};
    get_distribution(hashmap->array, sizes);
    print_distribution(hashfunc_name, sizes);
    hashmap_dtor(hashmap);
}

static void fill_hashmap(key_type *array, ChainsHashMap *hashmap) {
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        hashmap_insert(hashmap, array[i]);
    }
}

static void print_distribution(const char *hashfunc_name, size_t *sizes) {
    for (size_t i = 0; i < HASHMAP_SIZE; ++i) {
        printf("%s,%zu,%zu\n", hashfunc_name, i, sizes[i]);
    }
}

static void get_distribution(List *lists, size_t *sizes) {
    for (size_t i = 0; i <  HASHMAP_SIZE; ++i) {
        sizes[i] = lists[i].size;
    }
}

static double get_time(hashfunc_t hashfunc, key_type *array) {
    volatile hash_t hash = 0;

    clock_t begin = clock();
    for (size_t t = 0; t < REPEAT_TIMES; ++t) {
        for (size_t i = 0; i < ARRAY_SIZE; ++i) {
            hash = hashfunc(array[i]);
        }
    }
    clock_t end = clock();

    double time =  (double)(end - begin) / CLOCKS_PER_MS;
    return time;
}

#ifdef INT_KEY

key_type *get_arr(size_t size) {
    int *arr = (int*) calloc(size, sizeof(int));
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() * (-1);
    }
    return arr;
}

#elif defined FLOAT_KEY

key_type *get_arr(size_t size) {
    float *arr = (float*) calloc(size, sizeof(float));
    for (size_t i = 0; i < size; ++i) {
        arr[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/1000);
    }
    return arr;
}

#else 

key_type *get_arr(size_t size) {
    char **arr = (char**) calloc(size, sizeof(char*));
    for (size_t i = 0; i < size; ++i) {
        size_t len = rand() % 998 + 2;
        arr[i] = (char*) calloc(len + 1, sizeof(char));
        for (size_t j = 0; j < len; ++j) {
            arr[i][j] = rand() % 254 + 1;
        }
    }
    return arr;
}

#endif