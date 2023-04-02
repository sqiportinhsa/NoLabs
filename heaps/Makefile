.PHONY: all

Folders = binary_heap/obj/ benchmarks/build benchmarks/data

OPT_FLAGS = -O3 -march=native -mtune=native -flto

DEBUG_FLAGS = -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -fsanitize=address,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: bench1

clean:
	find . -name "*.o" -delete

folders:
	mkdir -p $(Folders)


bench1: binary_heap/obj/benchmark_1.o binary_heap/obj/binary_heap.o
	gcc $(OPT_FLAGS) binary_heap/obj/benchmark_1.o binary_heap/obj/binary_heap.o -o benchmarks/build/benchmark_1

binary_heap/obj/benchmark_1.o: binary_heap/benchmark_1.cpp binary_heap/binary_heap.h
	gcc $(OPT_FLAGS) -c binary_heap/benchmark_1.cpp -o binary_heap/obj/benchmark_1.o


binary_heap/obj/binary_heap.o: binary_heap/binary_heap.cpp binary_heap/binary_heap.h
	gcc $(OPT_FLAGS) -c binary_heap/binary_heap.cpp -o binary_heap/obj/binary_heap.o
