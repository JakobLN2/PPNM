CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm

Out.txt : main
# Task 1: Create input file for task 1 and emulate(?) a command line call:
#	echo "-n 9 -n 1 -n 3.14159 -n 1.57 -n 0.01" > inputfile_1.txt
#	./main $(cat inputfile_1.txt) > $@
# Task 2: Feed inputfile to main via the standard input:
#	echo "1.40 3.14 1.57 0 7" > inputfile_2.txt
#	./main < inputfile_2.txt > $@
# Task 3: Put input stream from input_file3 into Out.txt
	./main --input inputfile_3.txt --output $@

clean:
	$(RM) [Oo]ut.txt inputfile.txt *.o main
