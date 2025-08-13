// COLOUR_C

#ifdef _cplusplus_
extern C {
#endif


#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "./colour.h"
#define COLOUR_MAX_CODES_COUNT 256

struct ColourI* colour;
void InitColour();
static void InitColourI();


static uint8_t colourlib_initialised = 0;

static void InitColourI();

unsigned _black_;
unsigned _red_;
unsigned _green_;
unsigned _blue_;
unsigned _yellow_;
unsigned _magenta_;
unsigned _cyan_;
unsigned _white_;
unsigned _bright_;
unsigned _reset_;

char FG_BLACK[8];
char FG_RED[8];
char FG_GREEN[8];
char FG_YELLOW[8];
char FG_BLUE[8];
char FG_MAGENTA[8];
char FG_CYAN[8];
char FG_WHITE[8];

char FG_BRIGHT_BLACK[8];
char FG_BRIGHT_RED[8];
char FG_BRIGHT_GREEN[8];
char FG_BRIGHT_YELLOW[8];
char FG_BRIGHT_BLUE[8];
char FG_BRIGHT_MAGENTA[8];
char FG_BRIGHT_CYAN[8];
char FG_BRIGHT_WHITE[8];

char BG_BLACK[8];
char BG_RED[8];
char BG_GREEN[8];
char BG_YELLOW[8];
char BG_BLUE[8];
char BG_MAGENTA[8];
char BG_CYAN[8];
char BG_WHITE[8];

char BG_BRIGHT_BLACK[8];
char BG_BRIGHT_RED[8];
char BG_BRIGHT_GREEN[8];
char BG_BRIGHT_YELLOW[8];
char BG_BRIGHT_BLUE[8];
char BG_BRIGHT_MAGENTA[8];
char BG_BRIGHT_CYAN[8];
char BG_BRIGHT_WHITE[8];

char NORMAL[8];
char ITALIC[8];

static char** codes;

static char* setCodePage( char* );
static const char* getCodePage( );
static const unsigned resetAnsiVtCodes(unsigned f);
static char* reset();
static void bg( uint8_t cc );

static void bg( uint8_t cc ) { (cc); return; }

static void fg( uint8_t cc );

static void fg( uint8_t cc ) { (cc); return; }
static void bold();
static void bold() { return; }
static void up( int h );
static void up( int h ) { (h); return; }
static void down( int h );
static void down( int h ) { (h); return; }

static void left( int d );
static void left( int d ) { (d); return; }

static void br();
static void tl();
static void leftmost();
static void rightmost();
static void right( int d );
static void right( int d ) { (d); return; }
static void clear();
static void clear() { (1); return; }
static void nl();
static void nl() { printf("\n"); }
static void fixpos();
static void fixpos() { (1); return; }
static char* fmt( char* in );
static char* getANSIVTSeq( char* str );
static char* reset()	{ char* str = getANSIVTSeq( "reset" ); printf( str ); return str; }


/*
Some Windows configs require a manual invocation of VT processing.
*/

static HANDLE StdHandle;

#ifndef STD_OUTPUT_HANDLE
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#endif
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#ifdef WIN32
static BOOL color_win32_vt;
int win32_color()	{

	StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	color_win32_vt = SetConsoleMode(
		StdHandle,
		0x0001 | 0x0002 | ENABLE_VIRTUAL_TERMINAL_PROCESSING
	);

	//fprintf( stderr, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );
	if(color_win32_vt == 0)
		fprintf( stderr, "ANSIVT mode could not be activated in this Win32 process.\n" );

	return (int) color_win32_vt;	
}
#endif
static char* getANSIVTSeq( char* str )	{

	if( !strcmp( str,"reset" ) )
		return (char*)NORMAL;

	char prefix[4];
	prefix[0] = str[0];
	prefix[1] = str[1];
	prefix[2] = str[2];
	
	prefix[3] = '\0';
	
	uint8_t fb = 0;
	uint8_t f = 0;
	uint8_t bg = 0;
	
	const char** codes = colour->codes;
	char ch;

	
	int n = 6;
	
	if( !strcmp( prefix,"fg:" ) || (bg=(!strcmp( prefix,"bg:" ))) )
		str += 3;

	ch = str[n];
	str[n] = '\0';
	
	if( !strcmp( str,"bright" ) )
		codes += _bright_, str[n] = ch, str += n;
	else
		str[n] = ch;
	
	if( bg )
		codes += 16;
	
	if( !strcmp( str,"white" ) )
		return (char*) codes[_white_];

	if( !strcmp( str,"red" ) )
		return (char*) codes[_red_];
	
	if( !strcmp( str,"blue" ) )
		return (char*) codes[_blue_];
	
	if( !strcmp( str,"green" ) )
		return (char*) codes[_green_];
	
	if( !strcmp( str,"yellow" ) )
		return (char*) codes[_yellow_];

	if( !strcmp( str,"magenta" ) )
		return (char*) codes[_magenta_];

	if( !strcmp( str,"cyan" ) )
		return (char*) codes[_cyan_];
	
	if( !strcmp( str,"black" ) )
		return (char*) codes[_black_];

	int a = strlen( str );
	char* errmsg = (char*)malloc( a+2+1 );
	strcpy( errmsg, "[" );
	strcat( errmsg, str );
	strcat( errmsg, "]" );

	return errmsg;
}

static void InitColourI()	{
	
	#ifdef COLOURMODE
	#if COLOURMODE==0
	colour = (struct ColourI*) calloc( sizeof( struct ColourI ) );
	return;
	#endif
	#endif
	
	codes = (char**)calloc( 256, sizeof(char*) );
	
	const unsigned r = resetAnsiVtCodes( 1 );
	
	if( r==0 )	{
		
		fprintf( stderr, "The Colour Library was unable to initialise the ANSI VT code table!\n" );
		return;
	}
	
	#ifdef WIN32
	uint8_t r2 = (uint8_t) win32_color();
	char* msg = "%sWin32 VT Mode was %sactivated.\n";
	char* output = (char*)malloc( strlen(msg)+15+1 );
	
	r2==1?sprintf( ouput, msg, "[bright_green]", "" ):sprintf( output, msg, "[bright_red]", "not " );
	fprintf( stderr, output );
	#endif

	colour = (struct ColourI*) malloc( sizeof( struct ColourI ) );
	
	colour->codes = (const char**) codes;
	colour->reset = reset;
	colour->bg = bg;
	colour->fg = fg;
	colour->bold = bold;
	colour->b = bold;
	colour->up = up;
	colour->down = down;
	colour->left = left;
	colour->bwd = left;
	
	colour->right = right;
	colour->fwd = right;
	colour->clear = clear;
	colour->cls = clear;
	colour->nl = nl;
	colour->fixpos = fixpos;
	
	colour->fmt = fmt;
	
	
	colour_initialised = 1;
	return;
	
	#endif
}

static char* fmt( char* in )	{
	
	unsigned x = 0;
	unsigned y = 0;
	unsigned w = 0;
	
	uint8_t escaped = 0;
	char c = 0;
	char* out = (char*)calloc( 1024, 1 );
	uint8_t detected_seq = 0;
	char tbuf[2];
	tbuf[1] = '\0';
	char _[200] = { 0 };

	while( (c = in[x]) )	{
		
		x++;
		
		if( c=='\\' && !escaped )	{
			
			escaped = 1;
			continue;
		}
		if( c=='\\' && escaped )	{
			
			escaped = 0;
			out[x-1] = '\\';
			out[x] = '\\';
			continue;
		}
		if( c=='\e' )	{
			
			out[ x-1 ] = c;
			escaped = 1;
			continue;
		}
		
		char** seq;
		
		unsigned z = 0;

		isescaped:

		if( escaped )	{
			
			char t[2];
			t[0] = c;
			t[1] = '\0';
			strcat( out, (char*)t );
			escaped = 0;
			continue;
		}
		else if( c=='[' )	{


			detected_seq = 1;
			
			seq = (char**)malloc( 10 * sizeof(char*) );
			z=0;

			char ch;
			y=0;

			while( (ch=in[x]) != ']' && ch!='\0' )	{
				
				_[y] = ch;
				x++;
				y++;
			}
			
			if( ch==']' )
				x++;
			
			_[y] = '\0';
			
			char* entry = (char*)calloc( 32, 1 );
			char* entry_copy;
			
			w = 0;
			
			loop: 
			
			entry_copy = entry;
			while( (ch=_[w]) != ',' && ch != '\0' )
				*entry_copy = ch, w++, entry_copy++;
			
			*entry_copy = '\0';
			
			seq[z] = getANSIVTSeq( entry );

			z++;
			if( ch == ',' )	{
				
				w++;
				goto loop;
			}
			free( entry );
		}

		if( z>0 )	{
			
			unsigned n = 0;
			// attach the seq[] array of char* control codes to the 'char* out' buffer.
			while( n < z )
				strcat( out, seq[n++] );						
		}
		else	{

			tbuf[0] = c;
			strcat( out, tbuf );
		}
				
		if( detected_seq )	{
			
			free( seq );
			detected_seq = 0;
		}

	}
	
	return out;
}

static const char* setcodevalues( int c, int v, ... )	{

	//va_arg vargs;
	//va_list vlist;
	
	char* _ = (char*)calloc( 64, 1 );
	
	/*
		Those codestrings that support user-defined values have a string-qualifier at each location where a replacement number can be inserted.
		The ANSI char '%'might be a good COLOUR_H internal code, being free as it is under the ANSI/VT specification, marker for inserting a value. Some codepoints take
		Hexadecimal, some decimal.
		Perhaps "%%" might indicate that the value is required to be Hexadecimal. Then, a single '%', "%", could indicate Decimal.
		Perhaps 'R', 'G', 'B'might indicate the components of an RGB colourspace.
	*/
	
	return (const char*) _;
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
		strcpy((char*)ITALIC, "");
	}
	
	else if(f == 1)	{
		
		strcpy(FG_BLACK, "\e[30m");
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
		strcpy((char*)ITALIC, "\e[" );

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

	_bright_ = x;
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
	
	_reset_ = x;
	codes[x++] = NORMAL;
	
	unsigned y = x;
	for( ; y < COLOUR_MAX_CODES_COUNT; y++ )
		codes[y] = NULL;

	if( f==0 )
		x = 0;
	
	return ( (const unsigned) x );
}

static void swap4color( char* fg, char* bg )	{
	
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

#ifdef _cplusplus_
}
#endif