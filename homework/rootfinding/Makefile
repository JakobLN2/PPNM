CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized -Wno-unused-parameter
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h roots.h ../linearEquations/qrsolver.h ../ode/ode.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)


.PHONY: all clean
all: Out.txt Plot.rmax_conv.svg Plot.rmin_conv.svg Plot.acceps_conv.svg

Out.txt : main
	./$< 1> $@


main : main.o $(OBJS) $(INCS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^


%.o : %.cc %.h $(INCS)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

rmax_conv.txt : main
	./main
rmin_conv.txt : main
	./main
acceps_conv.txt : main
	./main

Plot.rmax_conv.svg : rmax_conv.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "r_{max} convergence with r_min = 1e-5, acc=eps=1e-5"; \
		  f(x) = x*exp(-x); \
		  plot[0:10][-0.05:0.4] \
			f(x) with lines title "analytical solution", \
		  	"$<" index 0 with lines title "r_{max} = 1",\
		  	"$<" index 1 with lines title "r_{max} = 2",\
		  	"$<" index 2 with lines title "r_{max} = 4",\
		  	"$<" index 3 with lines title "r_{max} = 8",\
		  	"$<" index 4 with lines title "r_{max} = 20"\
	' | gnuplot
Plot.rmin_conv.svg : rmin_conv.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "r_{min} convergence with r_max = 8, acc=eps=1e-5"; \
		  f(x) = x*exp(-x); \
		  plot[0:10][-0.01:0.4] \
			f(x) with lines title "analytical solution", \
		  	"$<" index 0 with lines title "r_{min} = 1e-3",\
		  	"$<" index 1 with lines title "r_{min} = 1e-2",\
		  	"$<" index 2 with lines title "r_{min} = 0.1",\
		  	"$<" index 3 with lines title "r_{min} = 0.5"\
	' | gnuplot
Plot.acceps_conv.svg : acceps_conv.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "acc/eps convergence with r_min = 1e-5, r_max = 8"; \
		  f(x) = x*exp(-x); \
		  plot[0:10][-0.05:0.6] \
			f(x) with lines title "analytical solution", \
		  	"$<" index 0 with lines title "acc=eps = 1e-5",\
		  	"$<" index 1 with lines title "acc=eps = 1e-3",\
		  	"$<" index 2 with lines title "acc=eps = 0.1",\
		  	"$<" index 3 with lines title "acc=eps = 1"\
	' | gnuplot

#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg main ../obj/*.o *conv.txt

