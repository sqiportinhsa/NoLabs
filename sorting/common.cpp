#include "common.h"

void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}