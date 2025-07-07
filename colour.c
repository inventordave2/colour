// COLOUR_C

#include <stdlib.h>
#include <string.h>
#include "./colour.h"

const struct Colour colour;

const unsigned ansivt;

const char FG_BLACK[8];
const char FG_RED[8];
const char FG_GREEN[8];
const char FG_YELLOW[8];
const char FG_BLUE[8];
const char FG_MAGENTA[8];
const char FG_CYAN[8];
const char FG_WHITE[8];

const char FG_BRIGHT_BLACK[8];
const char FG_BRIGHT_RED[8];
const char FG_BRIGHT_GREEN[8];
const char FG_BRIGHT_YELLOW[8];
const char FG_BRIGHT_BLUE[8];
const char FG_BRIGHT_MAGENTA[8];
const char FG_BRIGHT_CYAN[8];
const char FG_BRIGHT_WHITE[8];

const char BG_BLACK[8];
const char BG_RED[8];
const char BG_GREEN[8];
const char BG_YELLOW[8];
const char BG_BLUE[8];
const char BG_MAGENTA[8];
const char BG_CYAN[8];
const char BG_WHITE[8];

const char BG_BRIGHT_BLACK[8];
const char BG_BRIGHT_RED[8];
const char BG_BRIGHT_GREEN[8];
const char BG_BRIGHT_YELLOW[8];
const char BG_BRIGHT_BLUE[8];
const char BG_BRIGHT_MAGENTA[8];
const char BG_BRIGHT_CYAN[8];
const char BG_BRIGHT_WHITE[8];

const char NORMAL[8];

static const unsigned _black_;
static const unsigned _red_;
static const unsigned _green_;
static const unsigned _blue_;
static const unsigned _yellow_;
static const unsigned _magenta_;
static const unsigned _cyan_;
static const unsigned _white_;


static void reset();
static void bg( uint8_t cc );
static void fg( uint8_t cc );
static void bold();
static void up( int h );
static void down( int h );
static void left( int d );
static void right( int d );
static void clear();
static void nl();
static void fixpos();

static char* fmt( char* in );
static char* getANSIVTSeq( char* str );


static char* codes[256];

static char* getANSIVTSeq( char* str )	{

	if( !strcmp( str,"reset" ) )
		return (char*)NORMAL;

	
	char* prefix[4];
	
	prefix[0] = str[0];
	prefix[1] = str[1];
	prefix[2] = str[2];
	prefix[3] = '\0';
	
	uint8_t fb = 0;
	uint8_t f = 0;
	uint8_t bg = 0;
	
	
	if( !strcmp( prefix,"fg:" ) || bg=!strcmp( prefix,"bg:" ) )
		str += 3;
	

	char** codes = colour.codes;
	
	if( b )
		codes += 15;
	
	if( !strcmp( str,"white" ) )
		return (char*) codes+_white_;

	if( !strcmp( str,"red" ) )
		return (char*) codes+_red_;
	
	if( !strcmp( str,"blue" ) )
		return (char*) codes+_blue_;
	
	if( !strcmp( str,"green" ) )
		return (char*) codes+_green_;
	
	if( !strcmp( str,"yellow" ) )
		return (char*) codes+_yellow_;
	
	
	if( !strcmp( str,"magenta" ) )
		return (char*) codes+_magenta_;

	if( !strcmp( str,"cyan" ) )
		return (char*) codes+_cyan_;
	
	if( !strcmp( str,"black" ) )
		return (char*) codes+_black_;
}

void InitColour()	{
	
	const unsigned r = resetAnsiVtCodes( 1 );
	
	if( r==0 )
		fprintf( stderr, "The Colour Library was unable to initialise the ANSI VT code table!\n" ), return;
	
	colour.codes = (const char**) codes;

	colour.reset = reset;
	colour.bg = bg;
	colour.fg = fg;
	colour.bold = bold;
	colour.b = bold;
	colour.up = up;
	coulour.down = down;
	colour.left = left;
	colour.bwd = left;
	
	colour.right = right;
	colour.fwd = right;
	colour.clear = clear;
	colour.cls = clear;
	colour.nl = n;
	colour.fixpos = fixpos;
	
	colour.fmt = fmt;


	return;
}

static char* codes[256] = { NULL };

static char* fmt( char* in )	{
	
	unsigned x = 0;
	uint8_t escaped = 0;
	char c = 0;
	char* out = (char*)calloc( 1024, 1 );
	
	while( (c = in[x]) )	{
	
		if( c=='\\' && !escaped )
			escaped = 1, x++, continue;
		
		if( c=='\\' && escaped )
			escaped = 0, out[x-1] = '\\', out[x] = '\\', x++, continue;
		
		
		char** seq = (char**)calloc( 10, sizeof(char*) );
		
		unsigned y = 0;
		unsigned z = 0;
					
		if( escaped )	{
			
			switch( c )	{
				
				case 'n':
				
					strcat( out, "\n" );
					x++;
					break;

				case '[':
					
					x++;
					char _[200] = { 0 };
					
					char ch;
					while( (ch=in[x]) != ']' && ch!='\0' )	{
						
						_[y] = ch;
						x++;
						y++;
					}
					
					
					char* entry = (char*)calloc( 32, 1 );
					char* entry_copy;
					
					y = 0;
					
					loop:
					
					entry_copy = entry;
					while( (ch=_[y]) != ',' && ch != '\0' )
						*entry_copy = ch, y++, entry_copy++;
					
					*entry_copy = '\0';
					
					seq[z] = getANSIVTSeq( entry );

					z++;
					if( z == 10 || ch == '\0' )
						escaped = 0, break;
				
					// Arriving here heavily implies that 'ch' contains a comma ','
					y++;
					
					goto loop;
			
					// codegraph never gets here, but if I edit this case block, they may come into control-flow scope at that point.
					escaped = 0;
					break;
				
				default:
					
					break;
			}
			
			escaped = 0;
		}
		
		if( z>0 )	{
			
			unsigned n = 0;
			// attach the seq[] array of char* control codes to the 'char* out' buffer.
			while( n < z )
				strcat( out, seq[n++] );
			
			
		}
		else	{
			
			char* tbuf = " \0";
			tbuf[0] = c;
			strcat( out, tbuf );
		}
		
		
		x += y;
	}
}

static const unsigned resetAnsiVtCodes(unsigned f)	{
	
	if(f == 0)	{

		strcpy((char *)FG_BLACK, "");
		strcpy((char *)FG_RED, "");
		strcpy((char *)FG_GREEN, "");
		strcpy((char *)FG_YELLOW, "");
		strcpy((char *)FG_BLUE, "");
		strcpy((char *)FG_MAGENTA, "");
		strcpy((char *)FG_CYAN, "");
		strcpy((char *)FG_WHITE, "");

		strcpy((char *)FG_BRIGHT_BLACK, "");
		strcpy((char *)FG_BRIGHT_RED, "");
		strcpy((char *)FG_BRIGHT_GREEN, "");
		strcpy((char *)FG_BRIGHT_YELLOW, "");
		strcpy((char *)FG_BRIGHT_BLUE, "");
		strcpy((char *)FG_BRIGHT_MAGENTA, "");
		strcpy((char *)FG_BRIGHT_CYAN, "");
		strcpy((char *)FG_BRIGHT_WHITE, "");

		strcpy((char *)BG_BLACK, "");
		strcpy((char *)BG_RED, "");
		strcpy((char *)BG_GREEN, "");
		strcpy((char *)BG_YELLOW, "");
		strcpy((char *)BG_BLUE, "");
		strcpy((char *)BG_MAGENTA, "");
		strcpy((char *)BG_CYAN, "");
		strcpy((char *)BG_WHITE, "");

		strcpy((char *)BG_BRIGHT_BLACK, "");
		strcpy((char *)BG_BRIGHT_RED, "");
		strcpy((char *)BG_BRIGHT_GREEN, "");
		strcpy((char *)BG_BRIGHT_YELLOW, "");
		strcpy((char *)BG_BRIGHT_BLUE, "");
		strcpy((char *)BG_BRIGHT_MAGENTA, "");
		strcpy((char *)BG_BRIGHT_CYAN, "");
		strcpy((char *)BG_BRIGHT_WHITE, "");

		strcpy((char *)NORMAL, "");
	}
	
	else if(f == 1)	{
		
		strcpy((char *)FG_BLACK, "\e[30m");
		strcpy((char *)FG_RED, "\e[31m");
		strcpy((char *)FG_GREEN, "\e[32m");
		strcpy((char *)FG_YELLOW, "\e[33m");
		strcpy((char *)FG_BLUE, "\e[34m");
		strcpy((char *)FG_MAGENTA, "\e[35m");
		strcpy((char *)FG_CYAN, "\e[36m");
		strcpy((char *)FG_WHITE, "\e[37m");

		strcpy((char *)FG_BRIGHT_BLACK, "\e[90m");
		strcpy((char *)FG_BRIGHT_RED, "\e[91m");
		strcpy((char *)FG_BRIGHT_GREEN, "\e[92m");
		strcpy((char *)FG_BRIGHT_YELLOW, "\e[93m");
		strcpy((char *)FG_BRIGHT_BLUE, "\e[94m");
		strcpy((char *)FG_BRIGHT_MAGENTA, "\e[95m");
		strcpy((char *)FG_BRIGHT_CYAN, "\e[96m");
		strcpy((char *)FG_BRIGHT_WHITE, "\e[97m");

		strcpy((char *)BG_BLACK, "\e[40m");
		strcpy((char *)BG_RED, "\e[41m");
		strcpy((char *)BG_GREEN, "\e[42m");
		strcpy((char *)BG_YELLOW, "\e[43m");
		strcpy((char *)BG_BLUE, "\e[44m");
		strcpy((char *)BG_MAGENTA, "\e[45m");
		strcpy((char *)BG_CYAN, "\e[46m");
		strcpy((char *)BG_WHITE, "\e[47m");

		strcpy((char *)BG_BRIGHT_BLACK, "\e[100m");
		strcpy((char *)BG_BRIGHT_RED, "\e[101m");
		strcpy((char *)BG_BRIGHT_GREEN, "\e[102m");
		strcpy((char *)BG_BRIGHT_YELLOW, "\e[103m");
		strcpy((char *)BG_BRIGHT_BLUE, "\e[104m");
		strcpy((char *)BG_BRIGHT_MAGENTA, "\e[105m");
		strcpy((char *)BG_BRIGHT_CYAN, "\e[106m");
		strcpy((char *)BG_BRIGHT_WHITE, "\e[107m");

		strcpy((char *)NORMAL, "\e[0m");
	}
	
	
	unsigned x = 0;

	_black_ = x;
	codes[x++] = FG_BLACK;

	_red_ = x;
	codes[x++] = FG_RED;

	_green_ = x;
	codes[x++] = FG_GREEN;

	_blue_ = x;
	codes[x++] = FG_BLUE;

	_yellow_ = x;
	codes[x++] = FG_YELLOW;

	_magenta_ = x;
	codes[x++] = FG_MAGENTA;

	_cyan_ = x;
	codes[x++] = FG_CYAN;

	_white_ = x;
	codes[x++] = FG_WHITE;

	codes[x++] = FG_BRIGHT_BLACK;
	codes[x++] = FG_BRIGHT_RED;
	codes[x++] = FG_BRIGHT_GREEN;
	codes[x++] = FG_BRIGHT_BLUE;
	codes[x++] = FG_BRIGHT_YELLOW;
	codes[x++] = FG_BRIGHT_MAGENTA;
	codes[x++] = FG_BRIGHT_CYAN;
	codes[x++] = FG_BRIGHT_WHITE;

	codes[x++] = BG_BLACK;
	codes[x++] = BG_RED;
	codes[x++] = BG_GREEN;
	codes[x++] = BG_BLUE;
	codes[x++] = BG_YELLOW;
	codes[x++] = BG_MAGENTA;
	codes[x++] = BG_CYAN;
	codes[x++] = BG_WHITE;

	codes[x++] = BG_BRIGHT_BLACK;
	codes[x++] = BG_BRIGHT_RED;
	codes[x++] = BG_BRIGHT_GREEN;
	codes[x++] = BG_BRIGHT_BLUE;
	codes[x++] = BG_BRIGHT_YELLOW;
	codes[x++] = BG_BRIGHT_MAGENTA;
	codes[x++] = BG_BRIGHT_CYAN;
	codes[x++] = BG_BRIGHT_WHITE;
	
	codes[x++] = NORMAL;
	
	unsigned y = x;
	for( ; y < 256; y++ )
		codes[y] = NULL;

	if( f==0 )
		x = 0;
	
	return ( ansivt = (const unsigned) x );
}

static void swap4color( char * fg, char * bg )	{
	
	if( fg==NULL || strlen(fg)==0 || !strcmp(fg,"0") )
		goto _bg;
	
	if( !strcmp( fg, "black" ) )	{
		strcpy( fg, FG_BLACK );
		goto _bg;
	}
	if( !strcmp( fg, "red" ) )	{
		strcpy( fg, FG_RED );
		goto _bg;
	}
	if( !strcmp( fg, "green" ) )	{
		strcpy( fg, FG_GREEN );
		goto _bg;
	}
	if( !strcmp( fg, "yellow" ) )	{
		strcpy( fg, FG_YELLOW );
		goto _bg;
	}
	if( !strcmp( fg, "blue" ) )	{
		strcpy( fg, FG_BLUE );
		goto _bg;
	}
	if( !strcmp( fg, "magenta" ) )	{
		strcpy( fg, FG_MAGENTA );
		goto _bg;
	}
	if( !strcmp( fg, "cyan" ) )	{
		strcpy( fg, FG_CYAN );
		goto _bg;
	}
	if( !strcmp( fg, "white" ) )	{
		strcpy( fg, FG_WHITE );
		goto _bg;
	}
	if( !strcmp( fg, "bright_black" ) )	{
		strcpy( fg, FG_BRIGHT_BLACK );
		goto _bg;
	}
	if( !strcmp( fg, "bright_red" ) )	{
		strcpy( fg, FG_BRIGHT_RED );
		goto _bg;
	}
	if( !strcmp( fg, "bright_green" ) )	{
		strcpy( fg, FG_BRIGHT_GREEN );
		goto _bg;
	}
	if( !strcmp( fg, "bright_yellow" ) )	{
		strcpy( fg, FG_BRIGHT_YELLOW );
		goto _bg;
	}
	if( !strcmp( fg, "bright_blue" ) )	{
		strcpy( fg, FG_BRIGHT_BLUE );
		goto _bg;
	}
	if( !strcmp( fg, "bright_magenta" ) )	{
		strcpy( fg, FG_BRIGHT_MAGENTA );
		goto _bg;
	}
	if( !strcmp( fg, "bright_cyan" ) )	{
		strcpy( fg, FG_BRIGHT_CYAN );
		goto _bg;
	}
	if( !strcmp( fg, "bright_white" ) )	{
		strcpy( fg, FG_BRIGHT_WHITE );
		goto _bg;
	}

		return; // non-null invalid entry
	
	_bg:
	
	if( bg==NULL || strlen(bg)==0 || !strcmp( bg,"0") )	{
	
		return;
	}
	
	if( !strcmp( bg, "black" ) )	{
		strcpy( bg, BG_BLACK );

	}
	if( !strcmp( bg, "red" ) )	{
		strcpy( bg, BG_RED );
		
	}
	if( !strcmp( bg, "green" ) )	{
		strcpy( bg, BG_GREEN );
		
	}
	if( !strcmp( bg, "yellow" ) )	{
		strcpy( bg, BG_YELLOW );
		
	}
	if( !strcmp( bg, "blue" ) )	{
		strcpy( bg, BG_BLUE );
		
	}
	if( !strcmp( bg, "magenta" ) )	{
		strcpy( bg, BG_MAGENTA );
		
	}
	if( !strcmp( bg, "cyan" ) )	{
		strcpy( bg, BG_CYAN );
		
	}
	if( !strcmp( bg, "white" ) )	{
		strcpy( bg, BG_WHITE );
		
	}
	if( !strcmp( bg, "bright_black" ) )	{
		strcpy( bg, BG_BRIGHT_BLACK );
		
	}
	if( !strcmp( bg, "bright_red" ) )	{
		strcpy( bg, BG_BRIGHT_RED );
		
	}
	if( !strcmp( bg, "bright_green" ) )	{
		strcpy( bg, BG_BRIGHT_GREEN );
	
	}
	if( !strcmp( bg, "bright_yellow" ) )	{
		strcpy( bg, BG_BRIGHT_YELLOW );
	
	}
	if( !strcmp( bg, "bright_blue" ) )	{
		strcpy( bg, BG_BRIGHT_BLUE );
		
	}
	if( !strcmp( bg, "bright_magenta" ) )	{
		strcpy( bg, BG_BRIGHT_MAGENTA );
		
	}
	if( !strcmp( bg, "bright_cyan" ) )	{
		strcpy( bg, BG_BRIGHT_CYAN );
		
	}
	if( !strcmp( bg, "bright_white" ) )	{
		strcpy( bg, BG_BRIGHT_WHITE );
		
	}
	
	return;
}
