.PHONY: clean all

CXX      = g++
CXXFLAGS = -ansi -Wall -pedantic 
PROG1    = test_rmqdp

all: $(PROG1)

$(PROG1): $(PROG1).cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
	
clean:
	rm -rf *~ *.o $(PROG1) 
