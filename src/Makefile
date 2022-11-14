EXECUTABLE = ./webserv

# TODO: Add an actual list of sources and headers here

SOURCES = $(shell find . -name "*.cpp")
HEADERS = $(shell find . -name "*.hpp")

OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
DEPENDS = $(patsubst %.cpp, %.d, $(SOURCES))

CCFLAGS = --std=c++98 -g -Ofast -Wall -Wextra -Werror
LDFLAGS = 

%.o: %.cpp
	$(CXX) $(CCFLAGS) -MMD -MP -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

all: $(EXECUTABLE)

.phony: run
run: all
	$(EXECUTABLE) ../web/basic.conf

.phony: eval
eval: all
	$(EXECUTABLE) ../web/eval.conf

.phony: debug
debug: all
		gdb $(EXECUTABLE)

.phony: leaks
leaks: all
		valgrind --leak-check=full $(EXECUTABLE)

.phony: clean
clean:
	- $(RM) $(OBJECTS) $(DEPENDS)

.phony: fclean
fclean: clean
	- $(RM) $(EXECUTABLE)

.phony: re
re: fclean
	- $(MAKE) all

-include $(DEPENDS)
