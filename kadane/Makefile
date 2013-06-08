.PHONY: clean all

CXX      = g++
CXXFLAGS = -ansi -Wall -pedantic
CXXFILES = $(wildcard *.cpp)
OFILES   = $(CXXFILES:%.cpp=%.o)
PROG     = kadane

all: depend $(PROG)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	
$(PROG): $(OFILES)
	$(CXX) $(CXXFLAGS) $^ -o $@
	
depend: .makedeps

.makedeps: $(CXXFILES)
	$(CXX) $(CXXFLAGS) -MM $(CXXFILES) > .makedeps
	
-include .makedeps

clean:
	rm -f *.o .makedeps *~ kadane
