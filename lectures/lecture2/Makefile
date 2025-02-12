#Add flags to the c++ compiler?
CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
#Look at all warnings (Wall), all extra warnings (Wextra) and turn them into full errors (Werror)

#Add some libraries
LDLIBS += -lstdc++ -lm

.PHONEY : all
all : Out.txt Out++.txt

Out.txt : main.exe
	mono $< > $@
#mono main.exe > Out.txt
#one arrow means override, two is append. This is also written as "mono $< > $@" this is called "automatic variables". $< is the first prerequisite (main.exe) and >@ is the target.
#This prevents having to type ethe same thing several times

#In UNIX languages, there are no file extensions, just main
Out++.txt : main
	./main > Out++.txt
#./main means that the program will also search the current directory for other functions we call. By default it only checks the PATH repository

main : main.o sfuns.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^
#$ shows that it is a variable, so we ask the system for the variable which contains the C++ compiler
#$^ Means that we buiild it from all prerequisites

#We dont have to make a rule for make sfuns.o, c++ knows how to do this, which by default is
#sfuns.o : sfuns.cc
#	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c sfuns.cc
#We simply define the flags at the beginning of the Makefile and it just works.
#In principle, as it is now we can remove everything about c++, just leaving "main : main.o sfuns.o"

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc
#-c means "compile only", dont make an executable out of it

#Build main.exe from main.cs which also requies the library sfuns.dll
main.exe : main.cs sfuns.dll
	mcs -target:exe -reference:sfuns.dll -out:main.exe main.cs
#Compile main.cs, put it into main.exe and use sfuns.dll

#Create the library file sfuns.dll
sfuns.dll : sfuns.cs
	mcs -target:library -out:sfuns.dll sfuns.cs
#Target:library means that we dont want an executable made of it, there is no main function in there

#The clean target has to remove all files, which have been produved during the building of the project.
#We only clean when we move the project into new architecture
#Watch out that you donøt have a file called "clean", then it gets confused. This can be insured by writing ".PHONEY" which states that it is not a file
#.PHONEY: clean
clean:
	$(RM) sfuns.dll main.exe Out.txt

test:
	@echo $(RM)
	@echo $(CXX)