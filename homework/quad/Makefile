CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h quad.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)


.PHONY: all clean
all: Out.txt Plot.erf.svg Plot.erf_acc.svg

Out.txt : main
	./$< > $@

test : test.o

main : main.o $(OBJS) $(INCS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

%.o : %.cc %.h
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


Plot.erf.svg : Out.txt Makefile erf.data
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "Error function"; \
		  set key left; \
		  plot [][-1.1 : 1.1] \
		  	"$<" index 1 with points pointtype 4 title "calculated erf(x)"\
		   ,"erf.data" with lines title "tabulated erf(x)" \
	' | gnuplot
Plot.erf_acc.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "acc"; \
		  set ylabel "absolute error"; \
		  set title "Error function absolute error between tabulated and calculated value at x = 1"; \
		  set key left; \
		  set logscale x 2; \
		  set logscale y 2; \
		  f(x) = x; \
		  plot \
		  	"$<" index 2 with linespoints pointtype 1 title "absolute error", \
			f(x) with lines title "error = acc" \
	' | gnuplot

#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg main ../obj/*.o

