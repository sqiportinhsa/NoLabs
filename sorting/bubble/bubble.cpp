#include "bubble.h"
#include "../common.h"

void bubble_sort(int *arr, size_t size) {
    for (size_t sorted_counter = 0; sorted_counter < size-1; ++sorted_counter) {
        for (size_t i = 0; i < size - 1 - sorted_counter; ++i) {
            if (arr[i] > arr[i+1]) {
                 swap(arr + i, arr + i + 1);
            }
        }
    }
}
