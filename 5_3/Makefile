CXX = g++
CC = g++
CXXFLAGS = -Wall -O3 -g
TARGET = svd
LDLIBS = -llapack -lblas -ljpeg -lboost_program_options

default:main 

main: main.o

.PHONY: clean

clean:
	-rm -f *.o $(TARGET) output.jpg