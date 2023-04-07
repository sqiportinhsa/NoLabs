#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "../qsort/qsort.h"
#include "../common.h"

const size_t min_size = 2500000;
const size_t max_size = 10000000;
const size_t step     = 250000;

const char *identical = "identical";
const char *sorted = "sorted";
const char *reversed = "reversed";
const char *random_arr = "random";
const char *antimid = "anti-mid";

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


void   test(size_t size,     Arrs* (*create)(size_t size), const char *type);
Times *test(size_t arr_size, Arrs* (*create)(size_t size));

long get_sort_time(int *arr, size_t arr_size, void (*sorting)(int *array, size_t size));
void print_results(Times **times, size_t arr_size, const char *type);

Arrs *create_arr        (size_t size);
Arrs *create_indentical (size_t size);
Arrs *create_sorted     (size_t size);
Arrs *create_reversed   (size_t size);
Arrs *create_anti_mid   (size_t size);


int main() {
    srand((unsigned int)time(NULL));

    for (size_t size = min_size; size < max_size; size += step) {
        test(size, create_arr, random_arr);
        test(size, create_indentical, identical);
        test(size, create_sorted, sorted);
        test(size, create_reversed, reversed);
        //test(size, create_anti_mid, antimid);
    }
}

void test(size_t size, Arrs* (*create)(size_t size), const char *type) {
    Times *measures[measures_num] = {};
    for (int i = 0; i < measures_num; i++) {
        measures[i] = test(size, create);
    }
    print_results(measures, size, type);
    for (int i = 0; i < measures_num; i++) {
        free(measures[i]);
    }
}

Times *test(size_t arr_size, Arrs* (*create)(size_t size)) {
    Times *times = (Times*) calloc(1, sizeof(Times));
    Arrs  *arrs  = create(arr_size);

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

Arrs *create_indentical(size_t size) {
    int num = 1;

    Arrs *arrs = (Arrs*) calloc(1, sizeof(Arrs));

    arrs->median  = (int*) calloc(size, sizeof(int));
    arrs->central = (int*) calloc(size, sizeof(int));
    arrs->random  = (int*) calloc(size, sizeof(int));

    for (size_t i = 0; i < size; i++) {
        arrs->median[i]  = num;
        arrs->central[i] = num;
        arrs->random[i]  = num;
    }

    return arrs;
}

Arrs *create_sorted(size_t size) {
    Arrs *arrs = (Arrs*) calloc(1, sizeof(Arrs));

    arrs->median  = (int*) calloc(size, sizeof(int));
    arrs->central = (int*) calloc(size, sizeof(int));
    arrs->random  = (int*) calloc(size, sizeof(int));

    for (size_t i = 0; i < size; i++) {
        arrs->median[i]  = i;
        arrs->central[i] = i;
        arrs->random[i]  = i;
    }

    return arrs;
} 

Arrs *create_reversed(size_t size) {
    Arrs *arrs = (Arrs*) calloc(1, sizeof(Arrs));

    arrs->median  = (int*) calloc(size, sizeof(int));
    arrs->central = (int*) calloc(size, sizeof(int));
    arrs->random  = (int*) calloc(size, sizeof(int));

    for (size_t i = 0; i < size; i++) {
        arrs->median[i]  = size - i;
        arrs->central[i] = size - i;
        arrs->random[i]  = size - i;
    }

    return arrs;
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

Arrs *create_anti_mid(size_t size) {
    Arrs *arrs = (Arrs*) calloc(1, sizeof(Arrs));

    arrs->median  = (int*) calloc(size, sizeof(int));
    arrs->central = (int*) calloc(size, sizeof(int));
    arrs->random  = (int*) calloc(size, sizeof(int));

    for (size_t i = 0; i < size; ++i) {
        arrs->median[i] = (int) i;
    }

    for (size_t i = 0; i < size; ++i) {
        swap(arrs->median + i, arrs->median + i / 2);
    }

    for (size_t i = 0; i < size; ++i) {
        arrs->central[i] = arrs->median[i];
        arrs->random[i]  = arrs->median[i];
    }

    return arrs;
}


void print_results(Times **times, size_t arr_size, const char *type) {
    printf("Median pivot qsort,%s,%zu,", type, arr_size);
    for (int i = 0; i < measures_num; i++) {
        printf("%ld,", times[i]->median);
    }
    printf("%ld\n", times[measures_num-1]->median);

    printf("Central pivot qsort,%s,%zu,", type, arr_size);
    for (int i = 0; i < measures_num - 1; i++) {
        printf("%ld,", times[i]->central);
    }
    printf("%ld\n", times[measures_num-1]->central);

    printf("Random pivot qsort,%s,%zu,", type, arr_size);
    for (int i = 0; i < measures_num; i++) {
        printf("%ld,", times[i]->random);
    }
    printf("%ld\n", times[measures_num-1]->random);
    fflush(stdout);
}