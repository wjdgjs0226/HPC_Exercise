CC = mpicxx
CXX = mpicxx
CXXFLAGS = -Wall -O3 -pedantic
TARGET = main

default:$(TARGET)

$(TARGET): $(TARGET).o

.PHONY: clean run

clean:
	-rm -f *.o $(TARGET)

run:
	mpiexec -np 32 ./$(TARGET)

