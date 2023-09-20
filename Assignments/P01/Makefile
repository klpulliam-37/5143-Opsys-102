# Makefile for shell program using ncurses

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = main.cpp manager.cpp parser.cpp command.cpp cmdtypes.cpp

# SRCS = main.cpp 

OBJS = $(SRCS:.cpp=.o)

DEPS = manager.h parser.h command.h cmdtypes.h

# External libraries
EXLIBS = -lncurses

# Executable name
TARGET = shell

# Targets and rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(EXLIBS) -o $(TARGET)

# Pattern rule to compile every .cpp file into a .o file.
# The % checks for matching strings.
# If you have duplicate files, this will cause an error.
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean run view

clean:
	rm -f $(OBJS) $(TARGET)

# We have all as a dependency to ensure that the project 
# is built first before running.
run: all
	./$(TARGET)

view:
	@echo EXLIBS: $(EXLIBS)
	@echo SRCS: $(SRCS)
	@echo OBJS: $(OBJS)