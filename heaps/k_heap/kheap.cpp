#include <stdlib.h>

#include "kheap.h"

static KHeap *init_heap(int *arr, size_t arr_size, size_t k);
static void build_heap(KHeap *heap);
static void shift_down(KHeap *heap, size_t shift_index);
static void swap(int *el1, int *el2);
static size_t get_max(int *arr, size_t k);

void heap_sort(int *arr, size_t size, size_t k) {
    KHeap *heap = init_heap(arr, size, k);

    for (size_t i = size - 1; i > 0; --i) {
        swap(heap->data, heap->data + i);
        --heap->size;
        shift_down(heap, 0);
    }
    free(heap);
}

static KHeap *init_heap(int *arr, size_t arr_size, size_t k) {
    KHeap *heap = (KHeap*) calloc(1, sizeof(KHeap));
    heap->data = arr;
    heap->size = arr_size;
    heap->k    = k;
    build_heap(heap);
    return heap;
}

static void build_heap(KHeap *heap) {
    size_t leaves_bord = heap->size / heap->k;
    for (size_t i = leaves_bord; i > 0; --i) {
        shift_down(heap, i);
    }

    shift_down(heap, 0);
}

static void shift_down(KHeap *heap, size_t shift_index) {
    if (heap->size * heap->k > heap->size)
        return;

    size_t last = (shift_index + 1) * heap->k;
    if (last >= heap->size) {
        last  = heap->size - 1;
    }

    size_t child_amount = last - shift_index * heap->k;
    size_t max = shift_index * heap->k + get_max(heap->data, child_amount) + 1;

    if (heap->data[max] > heap->data[shift_index]) {                           
        swap(heap->data + max, heap->data + shift_index);
        shift_down(heap, max);
    }
}

static void swap(int *el1, int *el2) {
    int temp = *el1;
    *el1 = *el2;
    *el2 = temp;
}

static size_t get_max(int *arr, size_t k) {
    size_t imax = 0;
    int max = arr[imax];

    for (size_t i = 0; i < k; ++i) {
        if (arr[i] > max) {
            max  = arr[i];
            imax = i;
        }
    }

    return imax;
}
