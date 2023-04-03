#pragma once

#include <stdio.h>

struct KHeap {
    int   *data = nullptr;
    size_t size = 0;
    size_t    k = 0;
};

void heap_sort(int *arr, size_t size, size_t k);