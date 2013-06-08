.PHONY: clean depend

PROG     = test_closestpair
CXXFILES = $(wildcard *.cpp)
CXXHEADS = $(wildcard *.h)
OFILES   = $(CXXFILES:%.cpp=%.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(PROG): $(OFILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test:$(PROG)
	./$(PROG)
	
all: depend $(PROG)
	
depend: .makedeps

.makedeps: $(CXXFILES) $(CXXHEADS)
	$(CXX) $(CXXFLAGS) -MM $(CXXFILES) > .makedeps
	
-include .makedeps

clean:
	rm -f *.o *~ .makedeps $(PROG)
