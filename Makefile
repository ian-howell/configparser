.PHONY: all clean

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -w -pedantic-errors -Wextra -Wconversion -std=c++11

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)

OBJECTS = $(SOURCES:%.cpp=%.o)
DEPS := $(OBJECTS:%.o=%.d)


default: driver

-include $(DEPS)

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) -c $(CXXFLAGS) -MMD -o $@ $<

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
	-@rm -f $(DEPS)
