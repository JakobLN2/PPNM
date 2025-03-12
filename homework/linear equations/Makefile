CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized #ignore maybe uninitialized warnings
LDLIBS += -lstdc++ -lm

Out.txt : main
	./$< > $@

Out_matrix_test.txt : matrix_test
	./$< > $@

main : main.o vector.o matrix.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

vector.o : vector.cc vector.h
	$(CXX) $(CXXFLAGS) -c -o vector.o vector.cc

matrix.o : matrix.cc matrix.h vector.o
	$(CXX) $(CXXFLAGS) -c -o matrix.o matrix.cc


clean:
	$(RM) [Oo]ut.txt *.o main vector_test matrix_test

vector_test : vector_test.o vector.o

matrix_test : matrix_test.o matrix.o