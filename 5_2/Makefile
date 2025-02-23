CC = g++
CXXFLAGS = -Wall -g
TARGET = main
HDRS = LAPACK_bandedsym_matrix_gen.h
OBJS = main.o LAPACK_bandedsym_matrix_gen.o
LIBS = -llapack -lblas -lboost_program_options -lboost_timer


%.o : %.cpp $(HDRS)
	$(CC) $(CXXFLAGS) -o $@ -c $<

compiler : $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f *.o compiler 