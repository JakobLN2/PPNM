CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized #ignore maybe uninitialized warnings
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h qrsolver.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: main Out.txt plot.times.svg

test:
	$(info INCS is $(INCS))
	$(info SRCS is $(SRCS))
	$(info OBJS is $(OBJS))
	@echo "Linking command: $(CXX) $(CXXFLAGS) $(OBJS) $(LDLIBS) $(CPPFLAGS) -o $@ $^"


Out.txt : main
	./$< -n 4 -m 4 > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^


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
		   f(x) title sprintf("a = %3.5f ns",a*1e9)\
	' | gnuplot


out.times.txt: factorizer
	>$@
	for n in $$(seq 100 100 2000); \
		do $(TIME) ./factorizer -n $$n;\
	done

factorizer : factorizer.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $@ $^

#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

matrix_test : matrix_test.o matrix.o vector.o 
vector_test : vector_test.o vector.o

clean:
	$(RM) [Oo]ut*.txt main vector_test matrix_test factorizer *.png *.svg *.log $(OBJS)
