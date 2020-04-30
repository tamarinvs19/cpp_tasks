CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude
LDFLAGS = 

EXE = lab_16
SRCDIR = src
OBJDIR = obj

all: 
	$(CXX) $(CXXFLAGS) -c include/parallel_sort.hpp 

clean:
	rm -rf $(OBJDIR) $(EXE)

.PHONY: clean all
