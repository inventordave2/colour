# Colour Lib Makefile

compiler=gcc
debug=-g -DDEBUG
analysis=-Wall
optim=-O0
noexe=-c
name=colour
target=-D_WIN32

window: ./windowing_test.c ./test.h colour_d ansivt100_d
	$(compiler) $(debug) $(analysis) $(optim) ./windowing_test.c -o testw.exe

colourtest: ./test.c ./test.h ansivt100_d colour_d
	$(compiler) $(analysis) $(debug) $(optim) $(target) -o ./colourtest.exe ./test.c ./$(name)_d.o ./ansivt100_d.o
	
test: ./testwregexgrok.c
	make -C ./../werner_stoop_wregex/ lib
	gcc -g -o ./ft1.exe ./testwregexgrok.c ./../werner_stoop_wregex/libwregex.a


ansivt100_d: ./ansivt100.c ./ansivt100.h
	$(compiler) $(debug) $(analysis) $(optim) $(noexe) $(target) ./ansivt100.c -o ansivt100_d.o



colour: ./colour.c ./colour.h
	$(compiler) $(noexe) $(target) ./colour.c -o $(name).o

colour_d: ./colour.c ./colour.h

	$(compiler) $(debug) $(analysis) $(noexe) $(target) ./colour.c -o $(name)_d.o

all: colour colour_d colourtest

clean:
	del *.o
	
wipe: clean
	del *.exe

	