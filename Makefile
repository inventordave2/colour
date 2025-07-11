# Colour Lib Makefile

compiler=gcc
debug=-g -DDEBUG

colour: colour.c colour.h
	$(compiler) -c colour.c -o colour.o

colourd: colour.c colour.h
	$(compiler) -c colour.c -O0 $(debug) -o colourd.o

all: colour


		