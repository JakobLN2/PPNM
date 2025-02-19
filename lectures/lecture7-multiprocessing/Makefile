CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm
CSLIBS = -reference:System.Numerics.dll #Complex numbers in C#

#For C#:
# CODE = $(filter %.cs,$^)
# DLLS = $(addprefix -reference:,$(filter $.dll,$^))
# MKEXE = mcs -target:exe -out:$@ $(CSLIBS) $(DLLS) $(CODE)
# MKLIB = mcs -target:library -out:$@ $(CSLIBS) $(DLLS) $(CODE)

# Out.txt : main.exe ; mono $< > $@
# main.exe : main.cs ; $(MKEXE)
Out.txt : main

main : main.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

	
clean:
	$(RM) [Oo]ut.txt *.o *.exe main


#Makefile can automatically see when files do not depend on each other - here out1234 can be made simmultaneously
#make --job x &
#Uses x threads to make the file - if x = 4 then it can make all outs at once. & means that it runs in the background
test : ou1 out2 out3 out4

out1 : main.exe ; mono $< -terms 5e8 > $@
out2 : main.exe ; mono $< -terms 5e8 > $@
out3 : main.exe ; mono $< -terms 5e8 > $@
out4 : main.exe ; mono $< -terms 5e8 > $@

#Works just like test -> they are considered background processes (&) and therefore run simultaneously.
test2 : main.exe
	mono $< -terms 5e8 > out1 &
	mono $< -terms 5e8 > out2 &
	mono $< -terms 5e8 > out3 &
	mono $< -terms 5e8 > out4 &

#Bash for-loop - does the same as the previous tests (almost if it worked innit)
test3 : main.exe
	for n in 1 2 3 4; do mono main.exe -terms 5e8 > out$$n &; done
#$n means the variable n - make strips the first dollar, therefore we add another so there is still one left when it is sent to bash
