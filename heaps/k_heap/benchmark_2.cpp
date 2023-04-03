#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "kheap.h"

const size_t min_size = 1000000;
const size_t max_size = 100000000;
const size_t step     = 1000000;

const size_t measures_num = 5;

const size_t k_values[] = {5,10,25, 50, 100, 200, 300, 400, 500, 1000};

long test(int *arr, size_t arr_size, size_t k_value);
long get_sort_time(void (*sorting)(int *arr, size_t arr_size, size_t k_value), 
                                   int *arr, size_t arr_size, size_t k_value); 
int  *create_arr(size_t size);
void print_results(long *times, size_t arr_size);


int main() {
    srand((unsigned int)time(NULL));
    size_t opt_sizes_num = sizeof(k_values) / sizeof(size_t);
    long *measures = (long*) calloc (measures_num * opt_sizes_num, sizeof(long));

    for (size_t size = min_size; size < max_size; size += step) {
        for (size_t i = 0; i < measures_num; i++) {
            int *arr  = create_arr(size);
            for (size_t j = 0; j < opt_sizes_num; j++) {
                measures[i * opt_sizes_num + j] = test(arr, size, k_values[j]);
            }
            free(arr);
        }
        print_results(measures, size);
    }
    free(measures);
    return 0;
}

long test(int *arr, size_t arr_size, size_t k_value) {
    int *copy = (int*) calloc(arr_size, sizeof(int));
    memcpy(copy, arr, arr_size * sizeof(int));

    long time = get_sort_time(heap_sort, arr, arr_size, k_value);

    free(copy);
    return time;
}

long get_sort_time(void (*sorting)(int *arr, size_t arr_size, size_t k_value), 
                                   int *arr, size_t arr_size, size_t k_value) {
    clock_t begin = clock();                      
    sorting(arr, arr_size, k_value);           
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
    size_t opt_sizes_size = sizeof(k_values) / sizeof(size_t);
    for (size_t j = 0; j < opt_sizes_size; j++) {
        printf("K-heap sort,%zu,%zu,", k_values[j], arr_size);
        for (size_t i = 0; i < measures_num-1; i++) {
            printf("%ld,", times[i*opt_sizes_size + j]);
        }
        printf("%ld\n", times[measures_num-1]);
    }
    fflush(stdout);
}
