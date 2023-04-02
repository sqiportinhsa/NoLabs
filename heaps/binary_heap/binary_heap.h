#pragma once

#include <stdio.h>

struct BinaryHeap {
    int   *data = nullptr;
    size_t size = 0;
};

void heap_sort(int *arr, size_t size);