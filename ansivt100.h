// COLORCODES_256_ANSIVT100_H

#ifndef COLORCODES_256_ANSIVT100_H
#define COLORCODES_256_ANSIVT100_H

extern unsigned getColourCount();
extern const char* getColourCode( char* cn );
extern const char* getColourString( char* cc );
extern char* selectRandomColourCode( char* buf );
extern char* selectRandomColourString( char* buf );

extern void printANSIVTLookupColours();

#endif
