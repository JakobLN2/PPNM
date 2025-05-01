CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized -Wno-unused-parameter #ignore maybe uninitialized warnings and unused parameter
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h ode.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

# INC_DIR := ../inc
# INCS := $(wildcard $(INC_DIR)/*.h)
# SRCS := $(wildcard $(INC_DIR)/*.cc)
# OBJS := $(INCS:.h=.o)


.PHONY: all clean
all: Out.txt Plot.sinwave.svg Plot.dampedoscillator.svg Plot.bessel.png Plot.circular.svg Plot.elliptical.svg Plot.circularPreces.svg Plot.P3.svg

Out.txt : main
	./$< > $@

test : test.o $(OBJS)

main : main.o $(OBJS) $(INCS)
	@echo MAKING MAIN WITH $^
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

# Proper dependencies on the header file do not work, it claims to recompile but it does not change the default parameter value ._.
ode.o : ode.cc ode.h
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

%.o : %.cc %.h
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


Plot.sinwave.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "t"; \
		  set ylabel "y"; \
		  plot \
		  	"$<" index 1 with linespoints title "numerical solution y",\
		  	"$<" index 2 with linespoints title "numerical solution dy/dt",\
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

Plot.circular.svg : grData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "angle phi"; \
		  set ylabel "reduced-circumference 1/r"; \
		  set title "Equatorial motion with u(0) = 1, du(0) = 0.01, eps = 0"; \
		  set size square; \
		  plot[-1.2:1.2][-1.2:1.2] "$<" index 0 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle \
	' | gnuplot

Plot.elliptical.svg : grData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "angle phi"; \
		  set ylabel "reduced-circumference 1/r"; \
		  set title "Equatorial motion with u(0) = 1, du(0) = -0.25, eps = 0"; \
		  plot "$<" index 1 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle \
	' | gnuplot

Plot.circularPreces.svg : grData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "angle phi"; \
		  set ylabel "reduced-circumference 1/r"; \
		  set title "Equatorial motion with u(0) = 1, du(0) = -0.5, eps = 0.1"; \
		  plot "$<" index 2 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle \
	' | gnuplot

Plot.P3.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = x*x*x/3.0; \
		  plot \
		  	"$<" index 6 with points title "numerical solution",\
			f(x) with lines title "Third order polynomial" \
	' | gnuplot

grData.txt : grSolve
	./$< > $@

grSolve : grSolve.o $(INCS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) $(OBJS) -o $@ $^

#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg main grSolve ../inc/*.o

