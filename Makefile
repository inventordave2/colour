# Colour Lib Makefile

compiler=gcc
analysis=-g -DDEBUG -O0
noexe=-c
name=colour


colourtest: ./test.c colour_d
	$(compiler) $(analysis) -o ./colourtest.exe ./test.c colour_d.o

colour: ./colour.c ./colour.h
	$(compiler) $(noexe) ./colour.c -o $(name).o

colour_d: ./colour.c ./colour.h

	$(compiler) $(analysis) $(noexe) ./colour.c -o $(name)_d.o

all: colour colour_d colourtest

clean:
	del *.o
	
		