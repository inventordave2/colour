// COLOUR_H

#ifndef DAVELIB_COLOUR
#define DAVELIB_COLOUR

/*
The Colour Library Interface.

Usage:

colour.fmt( char* ); // Pass in a ColourLib-formatted string, and this member function will replace the code hints with the ANSI/VT literals.
*/
typedef struct Colour	{

	const char ansivt;

	char* (*fmt)( char* in );
	const char* codes[256];

	void (*reset)();
	void (*bg)( uint8_t cc );
	void (*fg)( uint8_t cc );
	void (*bold)();
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
extern const struct Colour colour;

/*
The only public (non-interface-wrapped) function to the Colour Library.
Must be called before the Colour Interface can be used, as the Init function initialises the Library runtime requirements.
*/
void InitColour();

/*
These are global copies of the strings representing the ANSI/VT control code sequences.
Populated after InitColor() has been called, and optionally accessible as globals,
they can also be accessed via the Interface colour.codes[] Array.
*/
extern const char FG_BLACK[8];
extern const char FG_RED[8];
extern const char FG_GREEN[8];
extern const char FG_YELLOW[8];
extern const char FG_BLUE[8];
extern const char FG_MAGENTA[8];
extern const char FG_CYAN[8];
extern const char FG_WHITE[8];

extern const char FG_BRIGHT_BLACK[8];
extern const char FG_BRIGHT_RED[8];
extern const char FG_BRIGHT_GREEN[8];
extern const char FG_BRIGHT_YELLOW[8];
extern const char FG_BRIGHT_BLUE[8];
extern const char FG_BRIGHT_MAGENTA[8];
extern const char FG_BRIGHT_CYAN[8];
extern const char FG_BRIGHT_WHITE[8];

extern const char BG_BLACK[8];
extern const char BG_RED[8];
extern const char BG_GREEN[8];
extern const char BG_YELLOW[8];
extern const char BG_BLUE[8];
extern const char BG_MAGENTA[8];
extern const char BG_CYAN[8];
extern const char BG_WHITE[8];

extern const char BG_BRIGHT_BLACK[8];
extern const char BG_BRIGHT_RED[8];
extern const char BG_BRIGHT_GREEN[8];
extern const char BG_BRIGHT_YELLOW[8];
extern const char BG_BRIGHT_BLUE[8];
extern const char BG_BRIGHT_MAGENTA[8];
extern const char BG_BRIGHT_CYAN[8];
extern const char BG_BRIGHT_WHITE[8];

extern const char NORMAL[8];

#endif
