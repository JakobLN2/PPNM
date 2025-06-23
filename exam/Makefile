CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2 -Wno-maybe-uninitialized -Wno-unused-parameter
CPPFLAGS += '-I ~/projects/PPNM/homework'
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

SRC_DIR := ../homework/src
OBJ_DIR := ../homework/obj
I_DIR := ../homework/include

#Header files to be compiled:
INCS = $(I_DIR)/vector.h $(I_DIR)/matrix.h svd.h ../homework/linearEquations/qrsolver.h

SRCS = $(INCS:$(I_DIR)/%.h=$(SRC_DIR)/%.cc)
SRCS := $(SRCS:.h=.cc)

OBJS := $(INCS:$(I_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:.h=.o)


.PHONY: all clean
all: Out.txt

Out.txt : main
	./$< -n 3 1> $@ 2> log.txt
	./$< -n 4 -m 2 1>> $@ 2>> log.txt
	./$< 1>> $@ 2>> log.txt


main : main.o $(OBJS) $(INCS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(CPPFLAGS) -o $@ $^


%.o : %.cc %.h $(INCS)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#Create all object files from their corresponding .cc file. Also check if the obj folder even exists
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo MAKING $@ WITH $^
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#If the obj directory does not exist, create it.
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) [Oo]ut*.txt *.o *.png *.svg main $(OBJ_DIR)/*.o

