CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm


TIME = time --portability --append --output=$@ --format "$$nthreads %e %U"

Times.png : out.times.txt Makefile
	echo '\
		set term png ;\
		set out "$@" ;\
		set title "program running time as function of number of threads" ;\
		set xlabel "number of threads" ;\
		set ylabel "running time [sec]" ;\
		plot "$<" index 0 with linespoints title "C++" \
	'|tee log.gpi|gnuplot

N=2e8
out.times.txt: main
	>$@
	for nthreads in `seq 10`; \
		do $(TIME) ./main -threads $$nthreads -terms $(N) ;\
	done

main : main.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

	
clean:
	$(RM) [Oo]ut.txt *.o *.exe main *.txt *.png