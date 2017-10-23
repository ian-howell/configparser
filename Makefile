.PHONY: all clean

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -w -pedantic-errors -Wextra -Wconversion -std=c++11

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)

OBJECTS = $(SOURCES:%.cpp=%.o)

default: driver

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

driver: $(OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

profile: CXXFLAGS = -g -Wall -w -pedantic-errors -Wextra -Wconversion -std=c++11 -pg
profile: driver

clean:
	-@rm -f core
	-@rm -f driver
	-@rm -f "depend"
	-@rm -f $(OBJECTS)

# Automatically generate dependencies and include them in Makefile
depend: $(SOURCES) $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) -std=c++11 -MM $(SOURCES) > $@


-include depend
