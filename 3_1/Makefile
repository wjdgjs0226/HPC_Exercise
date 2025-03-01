CC = g++

default: main dbg_test

main: main.o dbg.o

dbg_test: dbg_test.o dbg.o

.PHONY: clean

clean:
	rm -f *.o
