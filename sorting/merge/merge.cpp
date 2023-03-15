#include <stdlib.h>
#include <string.h>

#include "merge.h"
#include "../common.h"

static void merge_sort_internal(int *arr, int* tmp, size_t size);

void merge_sort(int *arr, size_t size) {
    if (size == 1) {
        return;
    }

    if (size == 2) {
        if (arr[0] > arr[1]) {
            swap(arr, arr + 1);
        }
        return;
    }

    int *temp = (int*) calloc(size, sizeof(int));
    merge_sort_internal(arr, temp, size);
    free(temp);
}

static void merge_sort_internal(int *arr, int* tmp, size_t size) {
    if (size == 1) {
        return;
    }

    if (size == 2) {
        if (arr[0] > arr[1]) {
            swap(arr, arr + 1);
        }
        return;
    }

    size_t sizeof_sub1 = size / 2;
    size_t sizeof_sub2 = size - sizeof_sub1;

    merge_sort_internal(arr,               tmp, sizeof_sub1);
    merge_sort_internal(arr + sizeof_sub1, tmp, sizeof_sub2);

    size_t isub1 = 0;
    size_t isub2 = 0;
    size_t itemp = 0;

    while (isub1 < sizeof_sub1 && isub2 < sizeof_sub2) {
        if (arr[isub1] < arr[sizeof_sub1 + isub2]) {
            tmp[itemp] = arr[isub1]; 
            ++isub1;
            ++itemp;

        } else {
            tmp[itemp] = arr[sizeof_sub1 + isub2];
            ++isub2;
            ++itemp;
        }
    }

    while (isub1 < sizeof_sub1) {
        tmp[itemp] = arr[isub1];
        ++isub1;
        ++itemp;
    }

    while (isub2 < sizeof_sub2) {
        tmp[itemp] = arr[sizeof_sub1 + isub2];
        ++isub2;
        ++itemp;
    }

    memcpy(arr, tmp, size * sizeof(int));
}