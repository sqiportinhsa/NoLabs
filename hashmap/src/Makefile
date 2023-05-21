.PHONY: all

Folders = ../obj/ ../build/

OPT_FLAGS = -O3

DEBUG_FLAGS = -march=native -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -fsanitize=address,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

FLAGS = $(DEBUG_FLAGS)

CC = gcc

all: hashmap

clean:
	find .. -name "*.o" -delete

folders:
	mkdir -p $(Folders)

bench: part2/open.cpp part2/chains.cpp part2/main.cpp part2/common.h
	$(CC) part2/open.cpp part2/chains.cpp part2/main.cpp -o ../build/bench $(FLAGS)

distr: ../obj/hashmap.o ../obj/distr.o ../obj/list.o ../obj/hash.o ../obj/distr_main.o 
	$(CC) ../obj/hashmap.o ../obj/distr.o ../obj/list.o ../obj/hash.o ../obj/distr_main.o -o ../build/hashstat $(FLAGS)

../obj/hashmap.o: part1/hashmap.cpp part1/hashmap.h part1/hash.h part1/list.h
	$(CC) -c part1/hashmap.cpp -o ../obj/hashmap.o  $(FLAGS)

../obj/hash.o: part1/hash.cpp part1/hash.h
	$(CC) -c part1/hash.cpp -o ../obj/hash.o  $(FLAGS)

../obj/distr_main.o: distr/main.cpp part1/hashmap.h part1/hash.h
	$(CC) -c distr/main.cpp -o ../obj/distr_main.o  $(FLAGS)

../obj/list.o: part1/list.cpp part1/list.h part1/hash.h
	$(CC) -c part1/list.cpp -o ../obj/list.o $(FLAGS)

../obj/distr.o: distr/distr.cpp distr/distr.h
	$(CC) -c distr/distr.cpp -o ../obj/distr.o $(FLAGS)

