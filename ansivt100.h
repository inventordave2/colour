// DAVELIB_ANSIVT100_H

#ifndef DAVELIB_ANSIVT100_H
#define DAVELIB_ANSIVT100_H

#include <stdint.h>


typedef struct ANSIVT100	{

	void (*topleft)();
	void (*tl)();
	void (*bottomright)();
	void (*br)();

	void (*bottom)();
	void (*top)();

	void (*leftmost)();
	void (*rightmost)();

	void (*up)( int h );
	void (*down)( int h );
	void (*left)( int d );
	void (*bwd)( int d );
	void (*right)( int d );
	void (*fwd)( int d );

	void (*clear)();
	void (*cls)();
	void (*nl)();
	void (*tab)();
	void (*ws)();

	char* (*getbuffer)( uint16_t x, uint16_t y, uint16_t length );

	void (*fixpos)(void);

}	ANSIVT100;


extern ANSIVT100* ansivt100;
extern void InitANSIVT100();
extern void DeInitANSIVT100();


extern unsigned getColourCount();
extern const char* getColourCode( char* cn );
extern const char* getColourString( char* cc );
extern char* selectRandomColourCode( char* buf );
extern char* selectRandomColourString( char* buf );

extern void printANSIVTLookupColours();

#endif
