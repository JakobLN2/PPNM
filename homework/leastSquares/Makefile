CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized -Wno-unused-parameter #ignore maybe uninitialized warnings
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"
# %U"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h lsfit.h ../linearEquations/qrsolver.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt plot.fit.svg

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^

plot.fit.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key right; \
		  set xlabel "Time (day)"; \
		  set ylabel "Activity (counts)"; \
		  l = 0.170624; \
		  a = 4.95866; \
		  lerr = 0.007157; \
		  aerr = 0.035402; \
		  f(x) = exp(-l*x + a) ; \
		  g(x) = exp(-(l + lerr)*x + a - aerr) ; \
		  h(x) = exp(-(l - lerr)*x + a + aerr) ; \
		  plot \
		  	"$<" index 1 with yerrorbars title "datapoints",\
		   f(x) title sprintf("F_c = exp(-%3.4f * x + %3.4f)",l,a),\
		   g(x) title sprintf("F_{c - dc}",a),\
		   h(x) title sprintf("F_{c + dc}",a)\
	' | gnuplot


#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg *.log main 

