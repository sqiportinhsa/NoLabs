#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "../merge/merge.h"

const size_t min_size = 1000;
const size_t max_size = 10000000;
const size_t step     = 10000;

int measures_num = 5;


long test(size_t arr_size);
long get_sort_time(int *arr, size_t arr_size, void (*sorting)(int *array, size_t size));
int  *create_arr(size_t size);
void print_results(long *jtimes, size_t arr_size);


int main() {
    srand((unsigned int)time(NULL));

    for (size_t size = min_size; size < max_size; size += step) {
        long measures[measures_num] = {};
        for (int i = 0; i < measures_num; i++) {
            measures[i] = test(size);
        }
        print_results(measures, size);
    }
}

long test(size_t arr_size) {
    int  *arr  = create_arr(arr_size);

    long time = get_sort_time(arr, arr_size, merge_sort);

    free(arr);
    return time;
}

long get_sort_time(int *arr, size_t arr_size, void (*sorting)(int *array, size_t size)) {
    clock_t begin = clock();                      
    sorting(arr, arr_size);           
    clock_t end = clock(); 
    long time = end - begin;
    time = (time * 1000) / CLOCKS_PER_SEC; // time in msec           
    return time;
}

int *create_arr(size_t size) {
    int *arr = (int*) calloc(size, sizeof(int));
    for (size_t i = 0; i < size; i++) {
        arr[i] = rand();
    }

    return arr;
}

void print_results(long *times, size_t arr_size) {
    printf("Merge sort,%zu,", arr_size);
    for (int i = 0; i < measures_num-1; i++) {
        printf("%ld,", times[i]);
    }
    printf("%ld\n", times[measures_num-1]);
}