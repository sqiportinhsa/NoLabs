#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int TESTS_AMOUNT = 1e6;

struct Fenwick {
    int *fen = 0;
    int size = 1;

    void construct(int size) {
        size = size + 1;
        fen = (int*) calloc(size, sizeof(int));
    }

    int pref(int position) {
        int ans = 0;
        for (int i = position + 1; i > 0; i -= i & -i) ans += fen[i];
        return ans;
    }

    void update(int position, int value) {
        for (int i = position + 1; i < size; i += i & -i) fen[i] += value;
    }

    int get(int left, int right) {
        return pref(right) - pref(left-1);
    }

    void destroy() {
        free(fen);
    }
};

struct SegmentTree {
    int *tsum = 0;
    int size = 1;

    void construct(int *array, int sz) {
        while (size < sz) size *= 2;
        tsum = (int*) calloc(2*size, sizeof(int));

        for (int i = 0; i < sz; ++i) {
            tsum[i + size] = array[i];
        }

        for (int i = size - 1; i > 0; --i) {
            tsum[i] = tsum[i * 2] + tsum[i * 2 + 1];
        }
    }

    void update(int pos, int value) {
        pos += size;
        tsum[pos] = value;
        pos >>= 1;
        while (pos > 0) {
            tsum[pos] = tsum[pos * 2] + tsum[pos * 2 + 1];
            pos /= 2;
        }
    }

    int get(int left, int right, int u, int tleft, int tright) {
        if (tright < left || tleft  >  right) return 0;
        if (left <= tleft && tright <= right) return tsum[u];

        int med = (tleft + tright) / 2;
        return get(left, right, u * 2, tleft, med) + get(left, right, u * 2 + 1, med + 1, tright);
    }

    int get(int left, int right) {
        return get(left, right, 1, 0, size-1);
    }

    void destroy() {
        free(tsum);
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
        tests->array[i] = rand() % (1000);
        tests->left[i] = rand() % (TESTS_AMOUNT);
        tests->right[i] = rand() % (TESTS_AMOUNT);

        if (tests->right[i] < tests->left[i]) {
            int temp   = tests->left[i];
            tests->left[i] = tests->right[i];
            tests->right[i] = temp;
        }
    }
}

int get_fenwick_time(Fenwick *ftree, Tests tests) {
    clock_t begin = clock();
    for (int i = 0; i < TESTS_AMOUNT; ++i) {
        ftree->get(tests.left[i], tests.right[i]);
    }
    clock_t end = clock();

    return (end - begin) * 1000 / CLOCKS_PER_SEC;
}

int get_stree_time(SegmentTree *stree, Tests tests) {
    clock_t begin = clock();
    for (int i = 0; i < TESTS_AMOUNT; ++i) {
        stree->get(tests.left[i], tests.right[i]);
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

    SegmentTree stree = {};
    stree.construct(tests.array, TESTS_AMOUNT);

    Fenwick ftree = {};
    ftree.construct(TESTS_AMOUNT);
    for (int i = 0; i < TESTS_AMOUNT; ++i) {
        ftree.update(i, tests.array[i]);
    }

    printf("fenwick: %d\n", get_fenwick_time(&ftree, tests));
    printf("stree:   %d\n", get_stree_time(&stree, tests));

    free_tests(tests);
    ftree.destroy();
    stree.destroy();
    return 0;
}