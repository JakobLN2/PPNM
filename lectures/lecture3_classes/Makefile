CXXFLAGS += -Wall -Wextra -std=c++23 -ferror-limit=1
#-Wall and -Wextra makes a long program create a lot of warnings, this is good for debugging since we add a limit -ferror-limit=1 stops the prgram after one error

LDLIBS += -lstdc++ -lm
#add std and the mathematical library

CODE = $(filter %.cs, $^)
# = defines a macro (a function) which does not happen until we call it
#CODE :=    HEre the assignment happens immidiately
#This means that anything with .cs in the name, are passed to the compiler automatically

DLLS = $(addprefix -reference:,$(filter %.dll, $^))
#This is now a function with two arguments:
#Anything with .dll in the name are prepended with --reference: and passed to the compiler

MKLIB = mcs -out:$@ -target:library $(DLLS) $(CODE)
#Doing this, we only have write this once. This automatically builds our library(?)

MKEXE = mcs -out:$@ -target:exe $(DLLS) $(CODE)

Out.txt: main.exe ; 
	mono main.exe > $@
	./main > $@

main.exe: main.cs ; $(MKEXE)
#This code automatically adds libraries, compiles the code and runs main
