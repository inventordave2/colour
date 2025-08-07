# Colour Lib Makefile

compiler=gcc
analysis=-g -DDEBUG -O0
noexe=-c
name=colour
target=-DWIN32

colourtest: ./test.c ./test.h colour_d
	$(compiler) $(analysis) $(target) -o ./colourtest.exe ./test.c $(name)_d.o

colour: ./colour.c ./colour.h
	$(compiler) $(noexe) $(target) ./colour.c -o $(name).o

colour_d: ./colour.c ./colour.h

	$(compiler) $(analysis) $(noexe) $(target) ./colour.c -o $(name)_d.o

all: colour colour_d colourtest

clean:
	del ./*.o
	
wipe: clean

	