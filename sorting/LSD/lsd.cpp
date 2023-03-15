#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lsd.h"

void lsd_sort(u_int32_t *arr, size_t size) {
    size_t counts[256];
    u_int32_t *temp_arr_ptr = 0;
    u_int32_t *original_arr = arr;

    u_int32_t *arr2 = (u_int32_t*) calloc(size, sizeof(u_int32_t));

    for (size_t i = 0; i < sizeof(u_int32_t); i++) {
        memset(counts, 0, sizeof(counts));
        for (size_t j = 0; j < size; j++) {
            unsigned char byte = *((unsigned char*) (arr + j) + i);
            counts[byte]++;
        }

        size_t temp = 0;
        size_t prefsum = 0;
        for (int j = 0; j < 256; j++) {
            prefsum += temp;
            temp = counts[j];
            counts[j] = prefsum;
        }

        for (size_t j = 0; j < size; j++) {
            unsigned char byte = *((unsigned char*) (arr + j) + i);
            arr2[counts[byte]] = arr[j];
            counts[byte]++;
        }

        temp_arr_ptr = arr2;
        arr2 = arr;
        arr = temp_arr_ptr;
    }

    if (arr != original_arr) {
        memcpy(arr, arr2, size * sizeof(u_int32_t));
    }
}
