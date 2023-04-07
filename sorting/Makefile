.PHONY: all

Folders = bubble/obj/ insertion/obj selection/obj testing/obj testing/build qsort/obj/ merge/obj/ LSD/obj

OPT_FLAGS = -O3 -march=native -mtune=native -flto

DEBUG_FLAGS = -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -fsanitize=address,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: bench1

clean:
	find . -name "*.o" -delete

folders:
	mkdir -p $(Folders)


bench1: testing/obj/benchmark1.o bubble/obj/bubble.o insertion/obj/insertion.o selection/obj/selection.o testing/obj/common.o
	g++ $(OPT_FLAGS) testing/obj/benchmark1.o bubble/obj/bubble.o insertion/obj/insertion.o selection/obj/selection.o testing/obj/common.o -o testing/build/benchmark1

bench2: testing/obj/benchmark2.o qsort/obj/qsort.o testing/obj/common.o
	g++ $(OPT_FLAGS) testing/obj/benchmark2.o qsort/obj/qsort.o testing/obj/common.o -o testing/build/benchmark2

bench3: testing/obj/benchmark3.o merge/obj/merge.o testing/obj/common.o insertion/obj/insertion.o
	g++ $(OPT_FLAGS) testing/obj/benchmark3.o merge/obj/merge.o testing/obj/common.o insertion/obj/insertion.o -o testing/build/benchmark3

bench4: testing/obj/benchmark4.o LSD/obj/lsd.o testing/obj/common.o
	g++ $(OPT_FLAGS) testing/obj/benchmark4.o LSD/obj/lsd.o testing/obj/common.o -o testing/build/benchmark4

bench5: testing/obj/benchmark5.o insertion/obj/insertion.o testing/obj/common.o
	g++ $(OPT_FLAGS) testing/obj/benchmark5.o insertion/obj/insertion.o testing/obj/common.o -o testing/build/benchmark5

bench6: testing/obj/benchmark6.o qsort/obj/qsort.o testing/obj/common.o
	g++ $(OPT_FLAGS) testing/obj/benchmark6.o qsort/obj/qsort.o testing/obj/common.o -o testing/build/benchmark6

testing/obj/benchmark1.o: testing/benchmark1.cpp bubble/bubble.h insertion/insertion.h selection/selection.h
	g++ $(OPT_FLAGS) -c testing/benchmark1.cpp -o testing/obj/benchmark1.o

testing/obj/benchmark2.o: testing/benchmark2.cpp qsort/qsort.h
	g++ $(OPT_FLAGS) -c testing/benchmark2.cpp -o testing/obj/benchmark2.o

testing/obj/benchmark3.o: testing/benchmark3.cpp merge/merge.h insertion/insertion.h
	g++ $(OPT_FLAGS) -c testing/benchmark3.cpp -o testing/obj/benchmark3.o

testing/obj/benchmark4.o: testing/benchmark4.cpp LSD/lsd.h
	g++ $(OPT_FLAGS) -c testing/benchmark4.cpp -o testing/obj/benchmark4.o

testing/obj/benchmark5.o: testing/benchmark5.cpp insertion/insertion.h
	g++ $(OPT_FLAGS) -c testing/benchmark5.cpp -o testing/obj/benchmark5.o

testing/obj/benchmark6.o: testing/benchmark6.cpp qsort/qsort.h
	g++ $(OPT_FLAGS) -c testing/benchmark6.cpp -o testing/obj/benchmark6.o

bubble/obj/bubble.o: bubble/bubble.cpp bubble/bubble.h common.h
	g++ $(OPT_FLAGS) -c bubble/bubble.cpp -o bubble/obj/bubble.o

insertion/obj/insertion.o: insertion/insertion.cpp insertion/insertion.h common.h
	g++ $(OPT_FLAGS) -c insertion/insertion.cpp -o insertion/obj/insertion.o

selection/obj/selection.o: selection/selection.cpp selection/selection.h common.h
	g++ $(OPT_FLAGS) -c selection/selection.cpp -o selection/obj/selection.o	

qsort/obj/qsort.o: qsort/qsort.cpp qsort/qsort.h common.h
	g++ $(OPT_FLAGS) -c qsort/qsort.cpp -o qsort/obj/qsort.o

merge/obj/merge.o: merge/merge.cpp merge/merge.h common.h
	g++ $(OPT_FLAGS) -c merge/merge.cpp -o merge/obj/merge.o

LSD/obj/lsd.o: LSD/lsd.cpp LSD/lsd.h common.h
	g++ $(OPT_FLAGS) -c LSD/lsd.cpp -o LSD/obj/lsd.o

testing/obj/common.o: common.cpp common.h
	g++ $(OPT_FLAGS) -c common.cpp -o testing/obj/common.o