CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized -Wno-unused-parameter
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h ../minimization/minimizer.h ../linearEquations/qrsolver.h ann.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)


.PHONY: all clean
all: Out.txt Plot.cosexp.svg Plot.cosexp_2.svg Plot.square.svg

Out.txt : main
	> Out.txt
	./$< 1>> $@ 2>> $@


main : main.o $(OBJS) $(INCS)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

main.o : main.cc $(INCS)

%.o : %.cc %.h $(INCS)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

cosexp_data.txt : main
	./main
cosexp_data_2.txt : main
	./main
square_data.txt : main
	./main

Plot.cosexp.svg : cosexp_data.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "cos(5x-1)exp(-x*x) ANN using gaussian wavelet activation function"; \
		  plot[-2:2][-1.1:1.1] \
		  	"$<" index 0 with lines dashtype 2 title "function",\
		  	"$<" index 1 with lines title "training region",\
			"$<" index 2 with lines title "fit"\
	' | gnuplot
Plot.cosexp_2.svg : cosexp_data_2.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "cos(5x-1)exp(-x*x) ANN using gaussian activation function"; \
		  plot[-2:2][-1.1:1.1] \
		  	"$<" index 0 with lines dashtype 2 title "function",\
		  	"$<" index 1 with lines title "training region",\
			"$<" index 2 with lines title "fit"\
	' | gnuplot
Plot.square.svg : square_data.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "5*x using gaussian wavelet activation function"; \
		  set key bottom center; \
		  plot[-2:2][-9:9] \
		  	"$<" index 0 with lines dashtype 2 title "function",\
		  	"$<" index 1 with lines title "training region",\
			"$<" index 2 with lines title "fit",\
			"$<" index 3 with lines title "deriv",\
			"$<" index 4 with lines title "2. deriv",\
			"$<" index 5 with lines title "anti-deriv"\
	' | gnuplot

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg main ../obj/*.o *_data*.txt

