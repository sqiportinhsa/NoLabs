#include <stdlib.h>

#include "distr.h"

int main() {
    srand(22342342354);

    key_type *arr = get_arr(ARRAY_SIZE);
    double times[HASHFUNCS_SIZE] = {};
    get_times(times, arr);
    print_times(times);
    get_and_report_all_distributions(arr);
    free(arr);
    return 0;
}