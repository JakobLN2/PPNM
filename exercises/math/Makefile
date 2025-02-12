#Purists would write
CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm
.PHONEY : all
all : Out++.txt

#Order in declaration shouldn't matter too much - also need to specify main for Out++.txt, as ./ looks for the current directory but cannot find it due to security reasons
Out++.txt : main
	./main > Out++.txt

main : main.o sfuns.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

#Clean target removs all files used for the building of the project
#If you have a file named clean, it will not make it so purists write
#.PHONEY : clean
clean:
	$(RM) [Oo]ut.txt *.o main

test:
	@echo $(RM)
	@echo $(CXX)

