# Makefile for shell program using ncurses

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Directory locations
ODIR = obj
IDIR = private
PDIR = public

INCLUDES = -I $(IDIR)

# Source files, header files, and object files

# Get a list of .cpp files in the other directory
CPP_FILES = $(wildcard $(PDIR)/*.cpp)
# Create the full paths to the files using addprefix
SRCS = main.cpp $(addprefix $(PDIR)/,$(notdir $(CPP_FILES)))

# SRCS = main.cpp 

_OBJS = $(SRCS:.cpp=.o)
CPP_OBJS = $(patsubst $(PDIR)/%,%, $(_OBJS))
OBJS = $(patsubst %,$(ODIR)/%,$(CPP_OBJS))

_DEPS = parser.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

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
$(ODIR)/%.o: $(SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)

# We have all as a dependency to ensure that the project 
# is built first before running.
run: all
	./$(TARGET)

view:
	@echo EXLIBS: $(EXLIBS)
	@echo INCLUDES: $(INCLUDES)
	@echo SRCS: $(SRCS)
	@echo CPP_FILES: $(CPP_FILES)
	@echo OBJS: $(OBJS)