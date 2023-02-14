#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "stack.h"

const int Magic_const_big     = 1000000;
const int Magic_const         =  100000;
const int Magic_const_lower   =   10000;
const int Magic_const_rly_low =     100;

static void run_test_1();
static void run_test_2();
static void run_test_3();

static void push_many_times(Stack *stk, int times);
static void pop__many_times(Stack *stk, int times);

int main() {

    srand((unsigned int)time(NULL));

    run_test_1();
    run_test_2();
    run_test_3();
}

static void run_test_1() {
    Stack *stk = stack_ctr(Magic_const_big, sizeof(int));

    int range = Magic_const_big / 2;

    printf("Start test 1.\n");
    clock_t begin = clock();

    push_many_times(stk, Magic_const_big);

    while (stk->size > Magic_const) {
        range = stk->size / 2;
        pop__many_times(stk, range);
        range /= 2;
        push_many_times(stk, range);
    }

    clock_t end = clock();
    printf("Test 1 finished. time: %lf\n", (double) (end - begin));

    stack_dtr(stk);
}

static void run_test_2() {
    Stack *stk = stack_ctr(Magic_const_big, sizeof(int));
    int range = Magic_const_big / 2;

    printf("Start test 2.\n");
    clock_t begin = clock();

    push_many_times(stk, Magic_const_big);

    for (int i = 0; i < Magic_const_rly_low; i++) {
        push_many_times(stk, Magic_const_lower);
        pop__many_times(stk, Magic_const_lower);
    }

    printf("%d %d\n", range);

    while (stk->size > Magic_const) {
        range = stk->size / 2;
        pop__many_times(stk, range);
        range /= 2;
        push_many_times(stk, range);
    }

    for (int i = 0; i < Magic_const_rly_low; i++) {
        push_many_times(stk, Magic_const_lower);
        pop__many_times(stk, Magic_const_lower);
    }

    clock_t end = clock();
    printf("Test 2 finished. time: %lf\n", (double) (end - begin));

    stack_dtr(stk);
}

static void run_test_3() {
    Stack *stk = stack_ctr(Magic_const_big, sizeof(int));
    int num = 0;

    push_many_times(stk, Magic_const_big);

    printf("Start test 3.\n");
    clock_t begin = clock();

    for(int i = 0; i < Magic_const_big; i++) {
        if (rand() % 2) {
            num = i;
            push(stk, &num);
        } else {
            pop(stk);
        }
    }

    clock_t end = clock();
    printf("Test 3 finished. time: %lf\n", (double) (end - begin));

    stack_dtr(stk);
}

static void push_many_times(Stack *stk, int times) {
    int num = 0;

    for (int i = 0; i < times; i++) {
        if (i % 100000 == 0) {
            //printf("in push many times i = %d\n", i);
            //printf("stk size     %d\n", stk->size);
            //printf("stk capacity %d\n", stk->capacity);
        }
        num = i;
        push(stk, &num);
    }
}

static void pop__many_times(Stack *stk, int times) {
    for (int i = 0; i < times; i++) {
        pop(stk);
    }
}