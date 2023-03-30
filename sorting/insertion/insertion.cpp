#include "insertion.h"
#include "../common.h"

static void move(int *dest, size_t size, int num);
static size_t search(const int *arr, size_t size, int elem);

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

void insertion_sort_move(int *arr, const size_t size) {
    for (size_t first_unsorted = 1; first_unsorted < size; first_unsorted++) {
        int elem = arr[first_unsorted];
        size_t actual_pos = 0;

        for (; actual_pos < first_unsorted; actual_pos++) {
            if (arr[actual_pos] >= elem) {
                break;
            }
        }

        move(arr + actual_pos, first_unsorted - actual_pos, elem);
    }
}

void insertion_sort_binsearch(int *arr, const size_t size) {
    for (size_t first_unsorted = 1; first_unsorted < size; first_unsorted++) {
        int elem = arr[first_unsorted];
        size_t actual_pos = search(arr, first_unsorted, elem);
        move(arr + actual_pos, first_unsorted - actual_pos, elem);
    }
}

static void move(int *dest, const size_t size, int num) {
    for (size_t i = size; i > 0; i--) {
        *(dest + i) = *(dest + i - 1);
    }

    *dest = num;
}

static size_t search(const int *arr, size_t size, int elem) {
    const int *start = arr;
    const int *end   = arr + size - 1;

    while (end - start > 1) {
        const int *mid = start + (end - start) / 2;
        int mid_elem = *mid;

        if (elem >= mid_elem) {
            start = mid;
            continue;
        }

        end = mid;
    }

    if (*end <= elem) {     // elem is greater or eq than all elements
        return size;
    }

    if (*start <= elem) {  // elem should be placed between start and end
        return end - arr;
    }

    return start - arr;    // elem should be placed before start
}
