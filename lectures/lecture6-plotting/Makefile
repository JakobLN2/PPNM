CXXFLAGS += -std=c++23 -Wall -Wextra -O2

# C# commands
CODE = $(filter %.cs,$^)
LIBS = $(addprefix -reference:,$(filter %.dll,$^))
MKEXE = mcs -target:exe -out:$@ $(LIBS) $(CODE)
MKLIB = mcs -target:library -out:$@ $(LIBS) $(CODE)

all: plot.test.svg

#Make the plot directly in the Makefile
plot.erf.svg : data.txt erf.data Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  plot \
		  	"$<" index 0 with points title "erf(x)"\
		   ,"erf.data" with points pointtype 4 title "tabulated erf(x)" \
	' | tee log.erf.gp | gnuplot
#tee means that it recieves from the standard input and sends the same to a standrad output -> into a file and also to gnuplot

plot.gamma.svg : data.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key bottom; \
		  plot \
		  	"$<" index 1 with lines title "gamma(x)"\
	' | tee log.erf.gp | gnuplot


#gpi is a gnuplot file (gnuplot instructions?)
plot.test.svg : test.gp
	gnuplot $<

data.txt : main
	./main > $@

main : main.o sfuns.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc


clean:	
	$(RM) *.exe *.dll [Oo]ut* [Ll]og*