// COLOUR_H

#ifndef DAVELIB_COLOUR
#define DAVELIB_COLOUR

#include <stdint.h>

/*
The Colour Library Interface.
Usage:
colour->fmt( char* ); // Pass in a ColourLib-formatted string, and this member function will replace the code hints with the ANSI/VT literals.
*/
typedef struct colour_t	{

	const char* desc;

	uint8_t colourMode;
	const uint8_t codeAlign: 8; /* A fixed width for any of the control code strings.
								With ANSIVT100, we can be sure of control substrings being of length 
								(bytes) or less,
								however	for simple usage, a length of 8 (bytes/chars unpacked) suffices. */

	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
	uint8_t RGBA[4];
	const char** codes;
	
	const unsigned (*resetAnsiVtCodes)(unsigned f);

	uint16_t NUMROWS;
	uint16_t NUMCOLS;
	uint16_t** screen; /* 2d (rows and columns) screen buffer */
	uint16_t x; /* column */
	uint16_t y; /* row    */
	
	uint16_t codepage; /* Such as UTF8, UCS4, ASCII, etc. */
	uint8_t mode; /* charmode = 1, bitmapmode = 2, unverified = 0 */

	char* (*wrap)( char*, char* cc );
	char* (*fmt)( char* in );
	char* (*setcodevalues)( int c, int v, ... );
	char* (*reset)();
	void (*bg)( uint8_t cc );
	void (*fg)( uint8_t cc );
	void (*bold)();
	void (*b)();
	void (*italic)();
	void (*i)();
	void (*underline)();
	void (*ul)();
	
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

} colour_t;

/*
An instance of the Colour Library Interface.
Initialised by InitColour().
*/
extern struct colour_t* colour;

/*
The only public (non-interface-wrapped) function to the Colour Library.
Must be called before the Colour Interface can be used, as the Init function initialises the Library runtime requirements.
*/
extern void InitColour();
extern void DeInitColour();
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
