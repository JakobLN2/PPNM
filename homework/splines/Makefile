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
all: Out.txt Plot.linspline.svg Plot.quadspline.svg Plot.cubspline.svg

Out.txt : main
	./$< > $@

main : main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o main $^


Plot.linspline.svg : out.linspline.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = cos(x) ; \
		  plot \
			f(x) title "sampled function",\
		  	"$<" index 1 with points title "sample points",\
		  	"$<" index 2 with lines title "linear spline",\
		  	"$<" index 3 with lines title "linear spline antiderivative"\
	' | gnuplot


out.linspline.txt: main
	./$< -p "lin" > $@

Plot.quadspline.svg : out.quadspline.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = cos(x) ; \
		  plot \
			f(x) title "sampled function",\
		  	"$<" index 1 with points title "sample points",\
		  	"$<" index 2 with lines title "quadratic spline",\
		  	"$<" index 3 with lines title "spline derivative",\
		  	"$<" index 4 with lines title "spline antiderivative"\
	' | gnuplot

out.quadspline.txt: main
	./$< -p "quad" > $@

Plot.cubspline.svg : out.cubspline.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  f(x) = cos(x) ; \
		  plot \
			f(x) with lines linestyle "dashed" title "sampled function",\
		  	"$<" index 1 with points title "sample points", \
			"" using 1:2 smooth csplines title "gnuplot spline",\
		  	"$<" index 2 with lines title "cubic spline",\
		  	"$<" index 3 with lines title "spline derivative",\
		  	"$<" index 4 with lines title "spline antiderivative"\
	' | gnuplot

out.cubspline.txt: main
	./$< -p "cubic" > $@
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

