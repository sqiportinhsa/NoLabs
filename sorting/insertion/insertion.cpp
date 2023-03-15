#include "insertion.h"
#include "../common.h"

void insertion_sort(int *arr, size_t size) {
    for (size_t first_unsorted = 1; first_unsorted < size; first_unsorted++) {
        for (size_t actual_pos = first_unsorted; actual_pos > 0; actual_pos--) {
            if (arr[actual_pos] >= arr[actual_pos - 1]) {
                break;
            }
            swap(arr + actual_pos - 1, arr + actual_pos);
        }
    }
}