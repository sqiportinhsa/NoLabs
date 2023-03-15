#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "../bubble/bubble.h"
#include "../insertion/insertion.h"
#include "../selection/selection.h"

const size_t min_size = 1000;
const size_t max_size = 1000000;
const size_t step     = 100000;

int measures_num = 5;

struct Arrs {
    int *bubble    = nullptr;
    int *insertion = nullptr;
    int *selection = nullptr;     
};

struct Times {
    long bubble    = 0;
    long insertion = 0;
    long selection = 0;    
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

    times->bubble    = get_sort_time(arrs->bubble,    arr_size, bubble_sort);
    times->insertion = get_sort_time(arrs->insertion, arr_size, insertion_sort);
    times->selection = get_sort_time(arrs->selection, arr_size, selection_sort);

    free(arrs->bubble);
    free(arrs->insertion);
    free(arrs->selection);
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

    arrs->bubble    = (int*) calloc(size, sizeof(int));
    arrs->insertion = (int*) calloc(size, sizeof(int));
    arrs->selection = (int*) calloc(size, sizeof(int));

    for (size_t i = 0; i < size; i++) {
        int num = rand();

        arrs->bubble[i]    = num;
        arrs->insertion[i] = num;
        arrs->selection[i] = num;
    }

    return arrs;
}

void print_results(Times **times, size_t arr_size) {
    printf("Bubble sort,%zu,", arr_size);
    for (int i = 0; i < measures_num; i++) {
        printf("%ld,", times[i]->bubble);
    }
    printf("%ld\n", times[measures_num-1]->bubble);

    printf("Insertion sort,%zu,", arr_size);
    for (int i = 0; i < measures_num - 1; i++) {
        printf("%ld,", times[i]->insertion);
    }
    printf("%ld\n", times[measures_num-1]->insertion);

    printf("Selection sort,%zu,", arr_size);
    for (int i = 0; i < measures_num; i++) {
        printf("%ld,", times[i]->selection);
    }
    printf("%ld\n", times[measures_num-1]->selection);
}