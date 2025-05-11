CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized -Wno-unused-parameter
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h mcInt.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)


.PHONY: all clean
all: Out.txt Plot.err.svg Plot.errquasi.svg

Out.txt : main
	./$< -t all > $@


main : main.o $(OBJS) $(INCS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

%.o : %.cc %.h
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


Plot.err.svg : err.data Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "sample points N"; \
		  set ylabel "error"; \
		  set logscale x 2; \
		  f(x) = a/sqrt(x); \
		  a = 0.01; \
		  fit f(x) "$<" index 0 skip 3 using 1:3 via a; \
		  set title "Area of unit circle error estimate using uniform sampling"; \
		  plot \
		  	"$<" index 0 using 1:2 with points pointtype 4 title "estimated error",\
			f(x) title sprintf("a/sqrt(N) fit, a = %3.5f",a), \
			"$<" index 0 using 1:3 with points pointtype 1 title "actual error" \
	' | gnuplot

err.data : main
	./$< -t errData > $@

Plot.errquasi.svg : errquasi.data Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "sample points N"; \
		  set ylabel "error"; \
		  set logscale x 2; \
		  f(x) = a/sqrt(x); \
		  a = 0.01; \
		  fit f(x) "$<" index 0 using 1:3 via a; \
		  set title "Area of unit circle error estimate using quasi-random sampling"; \
		  plot \
		  	"$<" index 0 using 1:2 with points pointtype 4 title "estimated error",\
			f(x) title sprintf("a/sqrt(N) fit, a = %3.5f",a), \
			"$<" index 0 using 1:3 with points pointtype 1 title "actual error" \
	' | gnuplot

errquasi.data : main
	./$< -t errQuasiData > $@

#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg main ../obj/*.o mcInt

