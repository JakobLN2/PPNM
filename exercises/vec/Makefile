CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm

Out.txt : main
	./$< > $@

main: main.o vec.o

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

clean:
	$(RM) [Oo]ut.txt *.o main
