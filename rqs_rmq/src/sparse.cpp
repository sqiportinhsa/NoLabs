#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int TESTS_AMOUNT = 1e6;

int min(int a, int b) {
    return a < b ? a : b;
}

struct SparseTable1 {
    int *log2_;
    int **sparse;
    int size;

    void construct(int *a, int size_) {
        size = size_;
        log2_ = (int*) calloc(size + 1, sizeof(int));
        log2_[0] = -1;

        for (int i = 1; i <= size; ++i) {
            log2_[i] = log2_[i / 2] + 1;
        }

        sparse = (int**) calloc(log2_[size] + 1, sizeof(int*));
        for (int i = 0; i <= log2_[size]; ++i) {
            sparse[i] = (int*) calloc(size, sizeof(int));
        }

        for (int i = 0; i < size; ++i) {
            sparse[0][i] = a[i];
        }

        for (int k = 1; k <= log2_[size]; ++k) {
            for (int i = 0; i + (1 << k) - 1 < size; ++i) {
                sparse[k][i] = min(sparse[k-1][i], sparse[k-1][i + (1 << (k - 1))]);
            }
        }
    }

    int get(int l, int r) {
        int k = log2_[r - l + 1];
        return min(sparse[k][l], sparse[k][r - (1 << k) + 1]);
    }

    void destroy() {
        for (int i = 0; i <= log2_[size]; ++i) {
            free(sparse[i]);
        }
        free(sparse);
        free(log2_);
    }
};

struct SparseTable2 {
    int *log2_;
    int **sparse;
    int size;

    void construct(int *a, int size_) {
        size = size_;
        log2_ = (int*) calloc(size + 1, sizeof(int));
        log2_[0] = -1;

        for (int i = 1; i <= size; ++i) {
            log2_[i] = log2_[i / 2] + 1;
        }

        sparse = (int**) calloc(size, sizeof(int*));
        for (int i = 0; i < size; ++i) {
            sparse[i] = (int*) calloc(log2_[size] + 1, sizeof(int));
        }

        for (int i = 0; i < size; ++i) {
            sparse[i][0] = a[i];
        }
        
        for (int k = 1; k <= log2_[size]; ++k) {
            for (int i = 0; i + (1 << k) - 1 < size; ++i) {
                sparse[i][k] = min(sparse[i][k-1], sparse[i + (1 << (k - 1))][k-1]);
            }
        }
    }

    int get(int l, int r) {
        int k = log2_[r - l + 1];
        return min(sparse[l][k], sparse[r - (1 << k) + 1][k]);
    }

    void destroy() {
        for (int i = 0; i < size; ++i) {
            free(sparse[i]);
        }
        free(sparse);
        free(log2_);
    }
};

struct Tests {
    int *array = nullptr;
    int *left  = nullptr;
    int *right = nullptr;
};

void generate_tests(Tests *tests) {
    tests->array = (int*) calloc(TESTS_AMOUNT, sizeof(int));
    tests->left  = (int*) calloc(TESTS_AMOUNT, sizeof(int));
    tests->right = (int*) calloc(TESTS_AMOUNT, sizeof(int));

    for (int i = 0; i < TESTS_AMOUNT; ++i) {
        tests->array[i] = rand() % (1'000'000'000);
        tests->left[i]  = rand() % (TESTS_AMOUNT);
        tests->right[i] = rand() % (TESTS_AMOUNT);

        if (tests->right[i] < tests->left[i]) {
            int temp        = tests->left[i];
            tests->left[i]  = tests->right[i];
            tests->right[i] = temp;
        }
    }
}

int get_time1(SparseTable1 *stable1, Tests tests) {
    clock_t begin = clock();
        for (int i = 0; i < TESTS_AMOUNT; ++i) {
            stable1->get(tests.left[i], tests.right[i]);
        }
    clock_t end = clock();

    return (end - begin) * 1000 / CLOCKS_PER_SEC;
}

int get_time2(SparseTable2 *stable2, Tests tests) {
    clock_t begin = clock();
        for (int i = 0; i < TESTS_AMOUNT; ++i) {
            stable2->get(tests.left[i], tests.right[i]);
        }
    clock_t end = clock();

    return (end - begin) * 1000 / CLOCKS_PER_SEC;
}

void free_tests(Tests tests) {
    free(tests.array);
    free(tests.left);
    free(tests.right);
}

int main() {
    Tests tests = {};
    generate_tests(&tests);

    SparseTable1 st1;
    st1.construct(tests.array, TESTS_AMOUNT);

    SparseTable2 st2;
    st2.construct(tests.array, TESTS_AMOUNT);

    printf("stable1,%d\n", get_time1(&st1, tests));
    printf("stable2,%d\n", get_time2(&st2, tests));

    free_tests(tests);
    st1.destroy();
    st2.destroy();

    return 0;
}