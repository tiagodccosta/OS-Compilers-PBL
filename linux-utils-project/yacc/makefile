CC = gcc
LEX = flex
YACC = yacc
CFLAGS = -Wall -g

all: command_parser

command_parser: y.tab.o lex.yy.o main.o
	$(CC) $(CFLAGS) -o $@ $^

y.tab.c y.tab.h: command_parser.y
	$(YACC) -d command_parser.y

lex.yy.c: command_lexer.l y.tab.h
	$(LEX) command_lexer.l

main.o: main.c command.h y.tab.h
	$(CC) $(CFLAGS) -c main.c

y.tab.o: y.tab.c command.h
	$(CC) $(CFLAGS) -c y.tab.c

lex.yy.o: lex.yy.c y.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	rm -f command_parser y.tab.c y.tab.h lex.yy.c *.o