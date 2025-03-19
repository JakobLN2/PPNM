CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized #ignore maybe uninitialized warnings
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"
# %U"

SRC_DIR := ../src/
LIB_DIR := ../include/

Out.txt : main
	./$< -n 4 -m 4 > $@

#something is major league wrong with my makefile, i can change the header files without it thinking it should recompile those??? But it perfectly works for the .cc file?????
main : main.o vector.o matrix.o qrsolver.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o main $^
main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc


plot.times.svg : out.times.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "size of matrix n x n"; \
		  set ylabel "algorithm runtime (s)"; \
		  f(x) = a*x*x*x ; \
		  a = 0.01; \
		  fit f(x) "$<" via a; \
		  plot \
		  	"$<" index 0 with points title "Runtime of QR factorization",\
		   f(x) title "a*n^3 fit"\
	' | gnuplot


out.times.txt: factorizer
	>$@
	for n in $$(seq 100 100 2000); \
		do $(TIME) ./factorizer -n $$n;\
	done

factorizer : factorizer.o vector.o matrix.o qrsolver.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o factorizer $^
factorizer.o : factorizer.cc
	$(CXX) $(CXXFLAGS) -c -o factorizer.o factorizer.cc


vector.o : vector.cc vector.h
	$(CXX) $(CXXFLAGS) -c -o vector.o vector.cc

matrix.o : matrix.cc matrix.h vector.o
	$(CXX) $(CXXFLAGS) -c -o matrix.o matrix.cc

qrsolver.o : qrsolver.cc qrsolver.h
	$(CXX) $(CXXFLAGS) -c -o qrsolver.o qrsolver.cc

matrix_test : matrix_test.o matrix.o vector.o 
vector_test : vector_test.o vector.o

clean:
	$(RM) [Oo]ut*.txt *.o main vector_test matrix_test factorizer *.png *.svg

