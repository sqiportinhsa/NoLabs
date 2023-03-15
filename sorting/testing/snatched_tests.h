#ifndef ALGO_TESTS_H
#define ALGO_TESTS_H

#include <stdlib.h>
#include "../merge/merge.h"

typedef void (*sort_func_t)(int* array, size_t len);

void bubble_sort    (int *array, size_t len);
void selection_sort (int *array, size_t len);
void insertion_sort (int *array, size_t len);

void quick_sort_median  (int *arr, size_t size);
void quick_sort_central (int *arr, size_t size);
void quick_sort_random  (int *arr, size_t size);

int test_sort_func (sort_func_t func);

#endif //ALGO_TESTS_H