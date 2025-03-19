CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized #ignore maybe uninitialized warnings
# CPPFLAGS += '-I ~/projects/PPNM/homework'
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
# main : main.o vector.o matrix.o qrsolver.o
# 	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o main $^
main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<


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

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
# $(OBJ_DIR)/%.o : $(SRCS)
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@


# $(OBJ_DIR)/vector.o : $(SRC_DIR)/vector.cc $(I_DIR)/vector.h
# 	$(CXX) $(CXXFLAGS) -c -o $< $@

# $(OBJ_DIR)/matrix.o : $(SRC_DIR)/matrix.cc $(I_DIR)/matrix.h $(OBJ_DIR)/vector.o
# 	$(CXX) $(CXXFLAGS) -c -o $< $@

# qrsolver.o : qrsolver.cc qrsolver.h
# 	$(CXX) $(CXXFLAGS) -c -o $< $@

matrix_test : matrix_test.o matrix.o vector.o 
vector_test : vector_test.o vector.o

clean:
	$(RM) [Oo]ut*.txt main vector_test matrix_test factorizer *.png *.svg *.log $(OBJS)

# -include $(OBJ:.o=.d)