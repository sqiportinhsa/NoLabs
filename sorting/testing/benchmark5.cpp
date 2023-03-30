#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "../insertion/insertion.h"

const size_t min_size = 10000;
const size_t max_size = 100000;
const size_t step     = 1000;

int measures_num = 5;

struct Arrs {
    int *no_opt    = nullptr;
    int *move      = nullptr;
    int *binsearch = nullptr;     
};

struct Times {
    long no_opt    = 0;
    long move      = 0;
    long binsearch = 0;    
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
        for (int i = 0; i < measures_num; i++) {
            free(measures[i]);
        }
    }
    return 0;
}

Times *test(size_t arr_size) {
    Times *times = (Times*) calloc(1, sizeof(Times));
    Arrs  *arrs  = create_arr(arr_size);

    times->no_opt    = get_sort_time(arrs->no_opt,    arr_size, insertion_sort);
    times->move      = get_sort_time(arrs->move, arr_size, insertion_sort_move);
    times->binsearch = get_sort_time(arrs->binsearch, arr_size, insertion_sort_binsearch);

    free(arrs->no_opt);
    free(arrs->move);
    free(arrs->binsearch);
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

    arrs->no_opt    = (int*) calloc(size, sizeof(int));
    arrs->move = (int*) calloc(size, sizeof(int));
    arrs->binsearch = (int*) calloc(size, sizeof(int));

    for (size_t i = 0; i < size; i++) {
        int num = rand();

        arrs->no_opt[i]    = num;
        arrs->move[i] = num;
        arrs->binsearch[i] = num;
    }

    return arrs;
}

void print_results(Times **times, size_t arr_size) {
    printf("No optimization insertion sort,%zu,", arr_size);
    for (int i = 0; i < measures_num; i++) {
        printf("%ld,", times[i]->no_opt);
    }
    printf("%ld\n", times[measures_num-1]->no_opt);

    printf("Move optimization insertion sort,%zu,", arr_size);
    for (int i = 0; i < measures_num - 1; i++) {
        printf("%ld,", times[i]->move);
    }
    printf("%ld\n", times[measures_num-1]->move);

    printf("Binsearch optimization insertion sort,%zu,", arr_size);
    for (int i = 0; i < measures_num; i++) {
        printf("%ld,", times[i]->binsearch);
    }
    printf("%ld\n", times[measures_num-1]->binsearch);
    fflush(stdout);
}