TARGET = strucit-backend

SRCS = strucit-backend.c lex.yy.c y.tab.c

CFLAGS = -Wall -Wno-implicit-function-declaration
LDFLAGS = -lfl

CC = gcc
LEX = flex
YACC = yacc

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

lex.yy.c: ANSI-C.l
	$(LEX) $^

y.tab.c y.tab.h: structbe.y
	$(YACC) -d $^

clean:
	rm -f $(TARGET) lex.yy.c y.tab.c y.tab.h

.PHONY: all clean