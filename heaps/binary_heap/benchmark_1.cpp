#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "binary_heap.h"

const size_t min_size = 1000000;
const size_t max_size = 100000000;
const size_t step     = 1000000;

const size_t measures_num = 5;

long test(int *arr, size_t arr_size);
long get_sort_time(int *arr, size_t arr_size); 
int  *create_arr(size_t size);
void print_results(long *times, size_t arr_size);


int main() {
    srand((unsigned int)time(NULL));
    long *measures = (long*) calloc (measures_num, sizeof(long));

    for (size_t size = min_size; size < max_size; size += step) {
        for (size_t i = 0; i < measures_num; i++) {
            int *arr  = create_arr(size);
            measures[i] = test(arr, size);
            free(arr);
        }
        print_results(measures, size);
    }
    free(measures);
    return 0;
}

long test(int *arr, size_t arr_size) {
    int *copy = (int*) calloc(arr_size, sizeof(int));
    memcpy(copy, arr, arr_size * sizeof(int));

    long time = get_sort_time(arr, arr_size);

    free(copy);
    return time;
}

long get_sort_time(int *arr, size_t arr_size) {
    clock_t begin = clock();                      
    heap_sort(arr, arr_size);           
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
    printf("Heap sort,%zu,", arr_size);
    for (size_t i = 0; i < measures_num-1; i++) {
        printf("%ld,", times[i]);
    }
    printf("%ld\n", times[measures_num-1]);
    fflush(stdout);
}