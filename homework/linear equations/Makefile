CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm

Out.txt : main
	./$< > $@

main : main.o vector.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

vector.o : vector.cc vector.h
	$(CXX) $(CXXFLAGS) -c -o vector.o vector.cc

clean:
	$(RM) [Oo]ut.txt *.o main
