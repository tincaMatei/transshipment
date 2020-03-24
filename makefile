# Main compiler
CC=g++
SRCEXT=cpp

# All important subdirectories
# include contains all .h/.hpp files
IDIR=include

# object files
ODIR=obj

# libraries
LDIR=lib

# source files
SDIR=src

# binaries files
BDIR=bin

# test files
TESTDIR=tests

# Compilation flags
FLAGS=-Wall -std=c++17 -O2 -I $(IDIR) -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# List of all sources and objects
SRC=$(shell find $(SDIR) -type f -name *.$(SRCEXT))
OBJ=$(patsubst $(SDIR)/%.$(SRCEXT), $(ODIR)/%.o, $(SRC))

# Main project
TARGET=$(SDIR)/main.cpp

$(ODIR)/%.o: $(SDIR)/%.$(SRCEXT)
	$(CC) -c -o $@ $^ $(FLAGS)

transshipment: $(OBJ)
	echo "Compile transshipment"
	$(CC) -o $(BDIR)/$@ $^ $(FLAGS)

.PHONY: clean

clean:
	rm $(shell find $(ODIR) -type f -name *.o)
