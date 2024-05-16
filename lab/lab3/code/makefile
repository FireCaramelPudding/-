CC = gcc
CFLAGS = -g
LIBS = -lfl
SRC = main.c tree.c sematic.c syntax.tab.c ir.c
TARGET = parser

.PHONY: all clean

all: $(TARGET)

$(TARGET): lexical.l syntax.y $(SRC)
	flex lexical.l
	bison -d -o syntax.tab.c syntax.y
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(TARGET)

clean:
	rm -f lex.yy.c syntax.tab.c syntax.tab.h $(TARGET)
