CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized #ignore maybe uninitialized warnings
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"
# %U"

SRC_DIR := ../src
OBJ_DIR := ../obj
I_DIR := ../include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h interp.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)

.PHONY: all clean
all: Out.txt plot.times.svg

Out.txt : main
	./$< -n 3 > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o main $^


plot.linspline.svg : out.linspline.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = cos(x) ; \
		  plot \
		  	"$<" index 0 with points title "sample points",\
		   f(x) title "sampled function"\
	' | gnuplot


out.linspline.txt: main
	./$< > $@
# >$@
# for n in $$(seq 100 100 2000); \
# 	do $(TIME) ./factorizer -n $$n;\
# done


#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

# vector.o : vector.cc vector.h
# 	$(CXX) $(CXXFLAGS) -c -o vector.o vector.cc

# matrix.o : matrix.cc matrix.h vector.o
# 	$(CXX) $(CXXFLAGS) -c -o matrix.o matrix.cc

# EVD.o : EVD.cc EVD.h
# 	$(CXX) $(CXXFLAGS) -c -o EVD.o EVD.cc


clean:
	$(RM) [Oo]ut*.txt *.o main vector_test matrix_test factorizer *.png *.svg

