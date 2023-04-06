#include <stdlib.h>

#include "binary_heap.h"

static BinaryHeap *init_heap(int *arr, size_t arr_size);
static void build_heap(BinaryHeap *heap);
static void shift_down(BinaryHeap *heap, size_t shift_index);
static void swap(int *el1, int *el2);

void heap_sort(int *arr, size_t size) {
    BinaryHeap *heap = init_heap(arr, size);

    for (size_t i = size - 1; i > 0; --i) {
        swap(heap->data, heap->data + i);
        --heap->size;
        shift_down(heap, 0);
    }
    free(heap);
}

static BinaryHeap *init_heap(int *arr, size_t arr_size) {
    BinaryHeap *binheap = (BinaryHeap*) calloc(1, sizeof(BinaryHeap));
    binheap->data = arr;
    binheap->size = arr_size;
    build_heap(binheap);
    return binheap;
}

static void build_heap(BinaryHeap *heap) {
    size_t med = heap->size / 2;
    for (size_t i = med; i > 0; --i) {
        shift_down(heap, i);
    }

    shift_down(heap, 0);
}

static void shift_down(BinaryHeap *heap, size_t shift_index) {
    if (shift_index * 2 + 1 >= heap->size)
        return;

    if (shift_index * 2 + 2 >= heap->size) {
        if (heap->data[shift_index] < heap->data[shift_index * 2 + 1]) {
            swap(heap->data + shift_index, heap->data + shift_index * 2 + 1);
        }
        return;
    }

    size_t left  = 2*shift_index + 1;
    size_t right = 2*shift_index + 2;

    int left_val  = heap->data[left];
    int right_val = heap->data[right];
    int shift_val = heap->data[shift_index];

    if (shift_val < left_val) {
        if (right_val < left_val) {                             // s, r < l
            swap(heap->data + left, heap->data + shift_index);
            shift_down(heap, left);
            return;
        }
    }

    if (shift_val < right_val) {                                // l, s < r
        swap(heap->data + right, heap->data + shift_index);
        shift_down(heap, right);
        return;
    }
}

static void swap(int *el1, int *el2) {
    int temp = *el1;
    *el1 = *el2;
    *el2 = temp;
}
