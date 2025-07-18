// COLOUR_H

#ifndef DAVELIB_COLOUR
#define DAVELIB_COLOUR

#include <stdint.h>
/*
The Colour Library Interface.

Usage:

colour->fmt( char* ); // Pass in a ColourLib-formatted string, and this member function will replace the code hints with the ANSI/VT literals.
*/
typedef struct Colour	{

	char ansivt;

	char* (*fmt)( char* in );
	const char** codes;

	char* (*setcodevalues)( int c, int v, ... );
	void (*reset)();
	void (*bg)( uint8_t cc );
	void (*fg)( uint8_t cc );
	void (*bold)();
	void (*b)();
	void (*up)( int h );
	void (*down)( int h );
	void (*left)( int d );
	void (*bwd)( int d );
	void (*right)( int d );
	void (*fwd)( int d );

	void (*clear)();
	void (*cls)();
	void (*nl)();
	

	void (*fixpos)(void);

} Colour;

/*
An instance of the Colour Library Interface.
Initialised by InitColour().
*/
extern struct Colour* colour;

/*
The only public (non-interface-wrapped) function to the Colour Library.
Must be called before the Colour Interface can be used, as the Init function initialises the Library runtime requirements.
*/
extern void InitColour();

/*
These are global copies of the strings representing the ANSI/VT control code sequences.
Populated after InitColor() has been called, and optionally accessible as globals,
they can also be accessed via the Interface colour.codes[] Array.
*/
extern char FG_BLACK[8];
extern char FG_RED[8];
extern char FG_GREEN[8];
extern char FG_YELLOW[8];
extern char FG_BLUE[8];
extern char FG_MAGENTA[8];
extern char FG_CYAN[8];
extern char FG_WHITE[8];

extern char FG_BRIGHT_BLACK[8];
extern char FG_BRIGHT_RED[8];
extern char FG_BRIGHT_GREEN[8];
extern char FG_BRIGHT_YELLOW[8];
extern char FG_BRIGHT_BLUE[8];
extern char FG_BRIGHT_MAGENTA[8];
extern char FG_BRIGHT_CYAN[8];
extern char FG_BRIGHT_WHITE[8];

extern char BG_BLACK[8];
extern char BG_RED[8];
extern char BG_GREEN[8];
extern char BG_YELLOW[8];
extern char BG_BLUE[8];
extern char BG_MAGENTA[8];
extern char BG_CYAN[8];
extern char BG_WHITE[8];

extern char BG_BRIGHT_BLACK[8];
extern char BG_BRIGHT_RED[8];
extern char BG_BRIGHT_GREEN[8];
extern char BG_BRIGHT_YELLOW[8];
extern char BG_BRIGHT_BLUE[8];
extern char BG_BRIGHT_MAGENTA[8];
extern char BG_BRIGHT_CYAN[8];
extern char BG_BRIGHT_WHITE[8];

extern char NORMAL[8];

extern char BOLD[8];
extern char ITALIC[8];
extern char UNDERLINE[8];
extern char STRIKETHROUGH[8];

extern char COLOUR[16]; // Allows a palette of 256 colours, 0 to 255.
extern char RGB_FG[32];
extern char RGB_BG[32];

extern char DEL[8];


#endif
