#include "selection.h"
#include "../common.h"

void selection_sort(int *arr, size_t size) {
    size_t min_index = 0;
    int    min_val   = 0;

    for (size_t first_unsorted = 0; first_unsorted < size - 1; first_unsorted++) {
        min_val   = arr[first_unsorted];
        min_index = first_unsorted;

        for (size_t compairing = first_unsorted; compairing < size; compairing++) {
            if (arr[compairing] < min_val) {
                min_index = compairing;
                min_val   = arr[compairing];
            }
        }

        swap(arr + first_unsorted, arr + min_index);
    }
}