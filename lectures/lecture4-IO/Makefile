CSC = mcs
CXXFLAGS += -std=c++23 -Wall -O2

Out.txt : Makefile main.exe input.txt
	>log
	echo "hello" > $@
	echo 1,2, 3,4, 5,6 | sed --expression "s/,/\./g" >> $@
	echo "greetings humans! from stdin" | mono main.exe 23,23 44,44 19,10 1>> $@ 2> log
	cat input.txt | mono main.exe 1>> $@ 2>> log
	mono main.exe <input.txt 1>> $@ 2>> log
	echo " " | mono main.exe -input:input.txt -output:$@ 2>>log
	./main --input input.txt --output $@ 2>> log
#1: Empty the log, redirect nothing to the log
#3: This is 3 different input parameters
#4: Send standard out to the target, send standard error stream to "log" file
#Furthermore, send "greetings humans!" as stdin to main.exe
#5: Send the input from input.txt as parameters to main.exe
#6: Does the same as 4?, this is how we read file

#echo "1,2,3,4,5" > $@
#Input "hello" into the target "out.txt"

input.txt : Makefile
	echo "This is sent to $@" > $@

main.exe : main.cs
	$(CSC) -target:exe -out:$@ $<

test:
	echo $@
	echo '$@'
	echo "$@"