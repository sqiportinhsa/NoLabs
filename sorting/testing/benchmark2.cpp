#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "../qsort/qsort.h"

const size_t min_size = 1000;
const size_t max_size = 10000000;
const size_t step     = 100000;

int measures_num = 5;

struct Arrs {
    int *median  = nullptr;
    int *central = nullptr;
    int *random  = nullptr;     
};

struct Times {
    long median  = 0;
    long central = 0;
    long random  = 0;    
};


Times *test(size_t arr_size);
long get_sort_time(int *arr, size_t arr_size, void (*sorting)(int *array, size_t size));
Arrs *create_arr(size_t size);
void print_results(Times **times, size_t arr_size);


int main() {
    srand((unsigned int)time(NULL));

    for (size_t size = min_size; size < max_size; size += step) {
        Times *measures[measures_num] = {};
        for (int i = 0; i < measures_num; i++) {
            measures[i] = test(size);
        }
        print_results(measures, size);
    }
}

Times *test(size_t arr_size) {
    Times *times = (Times*) calloc(1, sizeof(Times));
    Arrs  *arrs  = create_arr(arr_size);

    times->median  = get_sort_time(arrs->median,  arr_size, quick_sort_median);
    times->central = get_sort_time(arrs->central, arr_size, quick_sort_central);
    times->random  = get_sort_time(arrs->random,  arr_size, quick_sort_random);

    free(arrs->median);
    free(arrs->central);
    free(arrs->random);
    free(arrs);

    return times;
}

long get_sort_time(int *arr, size_t arr_size, void (*sorting)(int *array, size_t size)) {
    clock_t begin = clock();                      
    sorting(arr, arr_size);           
    clock_t end = clock(); 
    long time = end - begin;
    time = (time * 1000) / CLOCKS_PER_SEC; // time in msec           
    return time;
}

Arrs *create_arr(size_t size) {
    Arrs *arrs = (Arrs*) calloc(1, sizeof(Arrs));

    arrs->median  = (int*) calloc(size, sizeof(int));
    arrs->central = (int*) calloc(size, sizeof(int));
    arrs->random  = (int*) calloc(size, sizeof(int));

    for (size_t i = 0; i < size; i++) {
        int num = rand();

        arrs->median[i]  = num;
        arrs->central[i] = num;
        arrs->random[i]  = num;
    }

    return arrs;
}

void print_results(Times **times, size_t arr_size) {
    printf("Median pivot qsort,%zu,", arr_size);
    for (int i = 0; i < measures_num; i++) {
        printf("%ld,", times[i]->median);
    }
    printf("%ld\n", times[measures_num-1]->median);

    printf("Central pivot qsort,%zu,", arr_size);
    for (int i = 0; i < measures_num - 1; i++) {
        printf("%ld,", times[i]->central);
    }
    printf("%ld\n", times[measures_num-1]->central);

    printf("Random pivot qsort,%zu,", arr_size);
    for (int i = 0; i < measures_num; i++) {
        printf("%ld,", times[i]->random);
    }
    printf("%ld\n", times[measures_num-1]->random);
}