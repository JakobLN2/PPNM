CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm
CSLIBS = -reference:System.Numerics.dll #Complex numbers in C#

#For C#:
CODE = $(filter %.cs,$^)
DLLS = $(addprefix -reference:,$(filter $.dll,$^))
MKEXE = mcs -target:exe -out:$@ $(CSLIBS) $(DLLS) $(CODE)
MKLIB = mcs -target:library -out:$@ $(CSLIBS) $(DLLS) $(CODE)

Out.txt : main.exe ; mono $< > $@
main.exe : main.cs ; $(MKEXE)
