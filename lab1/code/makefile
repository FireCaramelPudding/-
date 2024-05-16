# Makefile for building the parser from lexical.l and syntax.y

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall

# Flex and Bison options
FLEX = flex
BISON = bison -d

# Source files
LEXER_SOURCE = lexical.l
PARSER_SOURCE = syntax.y
MAIN_SOURCE = main.c
TREE_SOURCE = tree.c

# Object files
LEXER_OBJECT = $(LEXER_SOURCE:.l=.o)PARSER_OBJECT = $(PARSER_SOURCE:.y=.tab.o)
MAIN_OBJECT = $(MAIN_SOURCE:.c=.o)TREE_OBJECT = $(TREE_SOURCE:.c=.o)

# Target executable
EXECUTABLE = parser

# Default target
all: $(EXECUTABLE)# Rule to build the executable$(EXECUTABLE): $(LEXER_OBJECT) $(PARSER_OBJECT) $(MAIN_OBJECT) $(TREE_OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

# Rule to generate lexer object file from .l file using Flex
$(LEXER_OBJECT): $(LEXER_SOURCE)
	$(FLEX) -o $@ $<# Rule to generate parser object file from .y file using Bison$(PARSER_OBJECT): $(PARSER_SOURCE)	$(BISON) -o $@ $<

# Rule to compile main.c to an object file
$(MAIN_OBJECT): $(MAIN_SOURCE)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to compile tree.c to an object file
$(TREE_OBJECT): $(TREE_SOURCE)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up target and object files
clean:
	rm -f $(EXECUTABLE) $(LEXER_OBJECT) $(PARSER_OBJECT) $(MAIN_OBJECT) $(TREE_OBJECT) *.tab.h *.output