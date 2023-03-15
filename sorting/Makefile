.PHONY: all

Folders = bubble/obj/ insertion/obj selection/obj testing/obj testing/build qsort/obj/ merge/obj/ LSD/obj

OPT_FLAGS = -O3 -march=native -mtune=native -flto

all: bench1

clean:
	find . -name "*.o" -delete

folders:
	mkdir -p $(Folders)


bench1: testing/obj/benchmark1.o bubble/obj/bubble.o insertion/obj/insertion.o selection/obj/selection.o testing/obj/common.o
	gcc $(OPT_FLAGS) testing/obj/benchmark1.o bubble/obj/bubble.o insertion/obj/insertion.o selection/obj/selection.o testing/obj/common.o -o testing/build/benchmark1

bench2: testing/obj/benchmark2.o qsort/obj/qsort.o testing/obj/common.o
	gcc $(OPT_FLAGS) testing/obj/benchmark2.o qsort/obj/qsort.o testing/obj/common.o -o testing/build/benchmark2

bench3: testing/obj/benchmark3.o merge/obj/merge.o testing/obj/common.o
	gcc $(OPT_FLAGS) testing/obj/benchmark3.o merge/obj/merge.o testing/obj/common.o -o testing/build/benchmark3

bench4: testing/obj/benchmark4.o LSD/obj/lsd.o testing/obj/common.o
	gcc $(OPT_FLAGS) testing/obj/benchmark4.o LSD/obj/lsd.o testing/obj/common.o -o testing/build/benchmark4

testing/obj/benchmark1.o: testing/benchmark1.cpp bubble/bubble.h insertion/insertion.h selection/selection.h
	gcc $(OPT_FLAGS) -c testing/benchmark1.cpp -o testing/obj/benchmark1.o

testing/obj/benchmark2.o: testing/benchmark2.cpp qsort/qsort.h
	gcc $(OPT_FLAGS) -c testing/benchmark2.cpp -o testing/obj/benchmark2.o

testing/obj/benchmark3.o: testing/benchmark3.cpp merge/merge.h
	gcc $(OPT_FLAGS) -c testing/benchmark3.cpp -o testing/obj/benchmark3.o

testing/obj/benchmark4.o: testing/benchmark4.cpp LSD/lsd.h
	gcc $(OPT_FLAGS) -c testing/benchmark4.cpp -o testing/obj/benchmark4.o

bubble/obj/bubble.o: bubble/bubble.cpp bubble/bubble.h common.h
	gcc $(OPT_FLAGS) -c bubble/bubble.cpp -o bubble/obj/bubble.o

insertion/obj/insertion.o: insertion/insertion.cpp insertion/insertion.h common.h
	gcc $(OPT_FLAGS) -c insertion/insertion.cpp -o insertion/obj/insertion.o

selection/obj/selection.o: selection/selection.cpp selection/selection.h common.h
	gcc $(OPT_FLAGS) -c selection/selection.cpp -o selection/obj/selection.o	

qsort/obj/qsort.o: qsort/qsort.cpp qsort/qsort.h common.h
	gcc $(OPT_FLAGS) -c qsort/qsort.cpp -o qsort/obj/qsort.o

merge/obj/merge.o: merge/merge.cpp merge/merge.h common.h
	gcc $(OPT_FLAGS) -c merge/merge.cpp -o merge/obj/merge.o

LSD/obj/lsd.o: LSD/lsd.cpp LSD/lsd.h common.h
	gcc $(OPT_FLAGS) -c LSD/lsd.cpp -o LSD/obj/lsd.o

testing/obj/common.o: common.cpp common.h
	gcc $(OPT_FLAGS) -c common.cpp -o testing/obj/common.o