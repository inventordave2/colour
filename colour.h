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

	int (*print)( char* );
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
extern void DeInitColour();
/*
These are global copies of the strings representing the ANSI/VT control code sequences.
Populated after InitColor() has been called, and optionally accessible as globals,
they can also be accessed via the Interface colour.codes[] Array.
*/

extern char* FG_BLACK;
extern char* FG_RED;
extern char* FG_GREEN;
extern char* FG_YELLOW;
extern char* FG_BLUE;
extern char* FG_MAGENTA;
extern char* FG_CYAN;
extern char* FG_WHITE;

extern char* FG_BRIGHT_BLACK;
extern char* FG_BRIGHT_RED;
extern char* FG_BRIGHT_GREEN;
extern char* FG_BRIGHT_YELLOW;
extern char* FG_BRIGHT_BLUE;
extern char* FG_BRIGHT_MAGENTA;
extern char* FG_BRIGHT_CYAN;
extern char* FG_BRIGHT_WHITE;

extern char* BG_BLACK;
extern char* BG_RED;
extern char* BG_GREEN;
extern char* BG_YELLOW;
extern char* BG_BLUE;
extern char* BG_MAGENTA;
extern char* BG_CYAN;
extern char* BG_WHITE;

extern char* BG_BRIGHT_BLACK;
extern char* BG_BRIGHT_RED;
extern char* BG_BRIGHT_GREEN;
extern char* BG_BRIGHT_YELLOW;
extern char* BG_BRIGHT_BLUE;
extern char* BG_BRIGHT_MAGENTA;
extern char* BG_BRIGHT_CYAN;
extern char* BG_BRIGHT_WHITE;

extern char* NORMAL;

extern char* BOLD;
extern char* ITALIC;
extern char* UNDERLINE;
extern char* STRIKETHROUGH;

extern char* COLOUR; // Allows a palette of 256 colours, 0 to 255.
extern char* RGB_FG;
extern char* RGB_BG;

extern char* DEL;


#endif

