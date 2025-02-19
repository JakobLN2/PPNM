CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm

Out.txt : main input.txt
	./$< < input.txt > $@

main: main.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc



clean:
	$(RM) [Oo]ut.txt *.o main
