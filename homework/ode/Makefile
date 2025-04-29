CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized -Wno-unused-parameter #ignore maybe uninitialized warnings and unused parameter
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"
# %U"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h ode.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)
.PHONY: all clean



all: Out.txt Plot.sinwave.svg Plot.dampedoscillator.svg Plot.bessel.svg Plot.circularPreces.svg

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o main $^

Plot.sinwave.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "t"; \
		  set ylabel "y"; \
		  plot \
		  	"$<" index 1 with points title "numerical solution y",\
		  	"$<" index 2 with points title "numerical solution dy/dt",\
	' | gnuplot

Plot.dampedoscillator.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "t"; \
		  set ylabel "theta"; \
		  set title "Driven harmonic oscillator with friction"; \
		  plot \
		  	"$<" index 3 with lines title "numerical solution theta",\
		  	"$<" index 4 with lines title "numerical solution omega",\
	' | gnuplot

Plot.bessel.png : Out.txt Makefile
	echo 'set terminal png background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "R(x)"; \
		  set title "Radial schrödinger equation for a free particle"; \
		  f(x) = sin(x)/x/x-cos(x)/x; \
		  plot \
		  	"$<" index 5 with points title "numerical solution",\
			f(x) with lines title "spherical bessel function l = 2" \
	' | gnuplot

Plot.circularPreces.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "angle phi"; \
		  set ylabel "reduced-circumference 1/r"; \
		  set title "Equatorial motion with u(0) = 1, du(0) = 0"; \
		  set size square; \
		  plot "$<" index 6 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle \
	' | gnuplot


#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@


clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg main

