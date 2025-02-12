CXXFLAGS += -Wall -Wextra -std=c++23 -fwrapv # -ferror-limit=1
#-Wall and -Wextra makes a long program create a lot of warnings, this is good for debugging since we add a limit -ferror-limit=1 stops the prgram after one error
#-fwrapv defines integer overflow to wrap around such that maxint + 1 = minint - not a good idea allegedly, behaviour is still unpredictable

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

out.txt : main ; ./main > $@
main: main.o 
main.o: main.cc