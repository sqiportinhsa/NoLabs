#include "../part1/hashmap.h"
#include <time.h>

const size_t HASHMAP_SIZE = 255000; 
const size_t   ARRAY_SIZE = 1000000;
const double CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;
const size_t REPEAT_TIMES = 100;

void get_times  (double *times, key_type *arr);
void print_times(double *times);

void get_and_report_all_distributions(key_type *array);

key_type *get_arr(size_t size);