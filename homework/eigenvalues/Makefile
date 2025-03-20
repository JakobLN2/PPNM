CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized #ignore maybe uninitialized warnings
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"
# %U"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h EVD.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt plot.dr_convergence.svg plot.rmax_convergence.svg plot.eigenfuncs.svg plot.n_times.svg

Out.txt : main
	./$< -n 4 > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^
swave : swave.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^
factorizer : factorizer.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^


out.dr_convergence.txt: swave
	>$@
	for n in $$(seq 0.05 0.05 2); \
		do ./swave -rmax 15 -dr $$n >> $@; \
	done
plot.dr_convergence.svg : out.dr_convergence.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set key left; \
		  set xlabel "dr (r_0)"; \
		  set ylabel "ε_0"; \
		  set title "convergence of ground state energy in Δr"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 0 using 2:3 with linespoints title "ground state energy"; \
	' | gnuplot


out.rmax_convergence.txt: swave
	>$@
	for n in $$(seq 0.7 0.1 7); \
		do ./swave -rmax $$n -dr 0.1 >> $@; \
	done
plot.rmax_convergence.svg : out.rmax_convergence.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set key right; \
		  set xlabel "rmax (r_0)"; \
		  set ylabel "ε_0"; \
		  set title "convergence of ground state energy in r_{max}"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 0 using 1:3 with linespoints title "ground state energy"; \
	' | gnuplot

out.eigenfuncs.txt: swave
	./$< -rmax 20 -dr 0.1 -wf 4 > $@

plot.eigenfuncs.svg : out.eigenfuncs.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set key right; \
		  set xlabel "r"; \
		  set ylabel "f(r)"; \
		  set title "numerical eigen-functions"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 1 using 1:2 with lines title "f_1", \
		  	"$<" index 2 using 1:2 with lines title "f_2", \
		  	"$<" index 3 using 1:2 with lines title "f_3", \
		  	"$<" index 4 using 1:2 with lines title "f_4"; \
	' | gnuplot

#Im not sure how to prevent the parallel threads from thinking it is done and trying to fit without out.times.txt being finished (or even begun)
out.times.txt: factorizer
	>$@
	for n in $$(seq 100 100 1400); \
		do ($(TIME) ./factorizer -n $$n &); \
	wait; \
	done

plot.n_times.svg : out.times.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "size of matrix n x n"; \
		  set ylabel "algorithm runtime (s)"; \
		  f(x) = a*x*x*x ; \
		  a = 0.01; \
		  fit f(x) "$<" via a; \
		  plot \
		  	"$<" index 0 with points title "Runtime of EVD",\
		   f(x) title sprintf("a = %3.5f ns",a*1e9)\
	' | gnuplot





#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg *.log main swave factorizer

