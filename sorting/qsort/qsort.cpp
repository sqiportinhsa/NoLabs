#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "qsort.h"
#include "../common.h"

static void quick_sort(size_t (*getpiv)(int *arr, const size_t left, const size_t right),
                                        int *arr, const size_t left, const size_t right);

static size_t get_median (int *arr, const size_t left, const size_t right);
static size_t get_central(int *arr, const size_t left, const size_t right);
static size_t get_random (int *arr, const size_t left, const size_t right);

//-----------------------------------------------------------------------------------------------//

void quick_sort_median(int *arr, size_t size) {
    quick_sort(get_median, arr, 0, size - 1);
}

void quick_sort_central(int *arr, size_t size) {
    quick_sort(get_central, arr, 0, size - 1);
}

void quick_sort_random(int *arr, size_t size) {
    quick_sort(get_random, arr, 0, size - 1);
}

//-----------------------------------------------------------------------------------------------//

static void quick_sort(size_t (*getpiv)(int *arr, const size_t left, const size_t right),
                                        int *arr, const size_t left, const size_t right) {

    if (left == right) {
        return;
    }

    size_t pivot = getpiv(arr, left, right);
    int piv_val = arr[pivot];

    size_t left_pos  = left;
    size_t right_pos = right;

    while (true) {
        for(; left_pos < right_pos && arr[left_pos] < piv_val; left_pos++);
        for(; left_pos < right_pos && arr[right_pos] > piv_val; right_pos--);

        if (left_pos >= right_pos) {
            break;
        }

        swap(arr + left_pos, arr + right_pos);

        if (left_pos == pivot) {
            pivot = right_pos;
            left_pos++;
        } else if (right_pos == pivot) { 
            pivot = left_pos;
            right_pos--;
        } else {
            left_pos++;
            right_pos--;
        }
    }
    
    if (pivot > left + 1)
        quick_sort(getpiv, arr, left, pivot - 1);
    if (pivot < right - 1)
        quick_sort(getpiv, arr, pivot + 1, right);
}

static size_t get_median(int *arr, const size_t left, const size_t right) {
    size_t mid = (left + right) / 2;
    if (arr[left] < arr[right]) {
        if (arr[right] < arr[mid]) return right;
        return (arr[mid] < arr[left]) ? left : mid;
    }
    if (arr[left] < arr[mid]) return left;
    return (arr[mid] < arr[right]) ? right : mid;
}

static size_t get_central(int *arr, const size_t left, const size_t right) {
    return (left + right) / 2;
} 

static size_t get_random(int *arr, const size_t left, const size_t right) {
    return left + rand() % (right - left + 1);
}