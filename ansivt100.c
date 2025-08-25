// ANSIVT100_256_LOOKUP

#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "./../DAVELIB/davelib.h"
#include "./colour.h"
#include "./schemes.h"
#include "./ansivt100.h"


struct ANSIVT100* ansivt100 = NULL;
void InitANSIVT100();
void DeInitANSIVT100();


static void InitANSIVT100_I();
static void DeInitANSIVT100_I();
static int ansivt100_initialised = 0;

void InitANSIVT100()	{

	InitANSIVT100_I();

	return;
}

void DeInitANSIVT100()	{
	
	DeInitANSIVT100_I();
	
	return;
}




static void DeInitANSIVT100_I()	{
	
	if( ansivt100_initialised==0 )
		return;

	ansivt100_initialised = 0;

	if( ansivt100==NULL )
		return;

	free( ansivt100 );

	return;
}

static const char* _dummyname = "";
static const char* _dummycode = "";

static void up( int h );
static void up( int h ) { return; }
static void down( int h );
static void down( int h ) { return; }

static void left( int d );
static void left( int d ) { return; }

static void br();
static void br()	{ return; }
static void tl();
static void tl()	{ return; }
static void leftmost();
static void leftmost()	{ return; }
static void rightmost();
static void right( int d );
static void right( int d ) { return; }
static void clear();
static void clear() { return; }
static void nl();
static void nl() { printf("\n"); }
static void fixpos();
static void fixpos() { return; }


static void InitANSIVT100_I()	{
	
	if( ansivt100_initialised==1 )
		return;

	if( ansivt100 != NULL )	{
		
		free( ansivt100 );
	}
		
	ansivt100 = (struct ANSIVT100*)calloc( 1,sizeof(struct ANSIVT100) );
	
	ansivt100->up = up;
	ansivt100->down = down;
	ansivt100->left = left;
	ansivt100->br = br;
	ansivt100->tl = tl;
	ansivt100->leftmost = leftmost;
	ansivt100->rightmost;
	ansivt100->right = right;
	ansivt100->clear = clear;
	ansivt100->nl = nl;
	ansivt100->fixpos = fixpos;
	
	
	ansivt100_initialised = 1;
	
	return;
}


typedef struct ColorLookup {

    const char *name;
    const char *code;

} ColorLookup;

static ColorLookup getColour( char* hint );

static ColorLookup bg_colour_table[] = {

    {"aliceblue",  ESC "[48;5;15m"},
    {"antiquewhite", ESC "[48;5;224m"},
    {"aqua", ESC "[48;5;14m"},
    {"aquamarine", ESC "[48;5;122m"},
    {"azure", ESC "[48;5;15m"},
    {"beige", ESC "[48;5;230m"},
    {"bisque", ESC "[48;5;224m"},
    {"black", ESC "[48;5;0m"},
    {"blanchedalmond", ESC "[48;5;224m"},
    {"blue", ESC "[48;5;12m"},
    {"blueviolet", ESC "[48;5;92m"},
    {"brown", ESC "[48;5;124m"},
    {"burlywood", ESC "[48;5;180m"},
    {"cadetblue", ESC "[48;5;73m"},
    {"chartreuse", ESC "[48;5;118m"},
    {"chocolate", ESC "[48;5;166m"},
    {"coral", ESC "[48;5;209m"},
    {"cornflowerblue", ESC "[48;5;69m"},
    {"cornsilk", ESC "[48;5;230m"},
    {"crimson", ESC "[48;5;161m"},
    {"cyan", ESC "[48;5;14m"},
    {"darkblue", ESC "[48;5;18m"},
    {"darkcyan", ESC "[48;5;30m"},
    {"darkgoldenrod", ESC "[48;5;136m"},
    {"darkgray", ESC "[48;5;248m"},
    {"darkgreen", ESC "[48;5;22m"},
    {"darkgrey", ESC "[48;5;248m"},
    {"darkkhaki", ESC "[48;5;143m"},
    {"darkmagenta", ESC "[48;5;90m"},
    {"darkolivegreen", ESC "[48;5;239m"},
    {"darkorange", ESC "[48;5;208m"},
    {"darkorchid", ESC "[48;5;98m"},
    {"darkred", ESC "[48;5;88m"},
    {"darksalmon", ESC "[48;5;174m"},
    {"darkseagreen", ESC "[48;5;108m"},
    {"darkslateblue", ESC "[48;5;60m"},
    {"darkslategray", ESC "[48;5;238m"},
    {"darkslategrey", ESC "[48;5;238m"},
    {"darkturquoise", ESC "[48;5;44m"},
    {"darkviolet", ESC "[48;5;92m"},
    {"deeppink", ESC "[48;5;198m"},
    {"deepskyblue", ESC "[48;5;39m"},
    {"dimgray", ESC "[48;5;242m"},
    {"dimgrey", ESC "[48;5;242m"},
    {"dodgerblue", ESC "[48;5;33m"},
    {"firebrick", ESC "[48;5;124m"},
    {"floralwhite", ESC "[48;5;15m"},
    {"forestgreen", ESC "[48;5;28m"},
    {"fuchsia", ESC "[48;5;13m"},
    {"gainsboro", ESC "[48;5;253m"},
    {"ghostwhite", ESC "[48;5;15m"},
    {"gold", ESC "[48;5;220m"},
    {"goldenrod", ESC "[48;5;178m"},
    {"gray", ESC "[48;5;8m"},
    {"green", ESC "[48;5;2m"},
    {"greenyellow", ESC "[48;5;154m"},
    {"grey", ESC "[48;5;8m"},
    {"honeydew", ESC "[48;5;255m"},
    {"hotpink", ESC "[48;5;205m"},
    {"indianred", ESC "[48;5;167m"},
    {"indigo", ESC "[48;5;54m"},
    {"ivory", ESC "[48;5;15m"},
    {"khaki", ESC "[48;5;222m"},
    {"lavender", ESC "[48;5;255m"},
    {"lavenderblush", ESC "[48;5;15m"},
    {"lawngreen", ESC "[48;5;118m"},
    {"lemonchiffon", ESC "[48;5;230m"},
    {"lightblue", ESC "[48;5;152m"},
    {"lightcoral", ESC "[48;5;210m"},
    {"lightcyan", ESC "[48;5;195m"},
    {"lightgoldenrodyellow", ESC "[48;5;230m"},
    {"lightgray", ESC "[48;5;252m"},
    {"lightgreen", ESC "[48;5;120m"},
    {"lightgrey", ESC "[48;5;252m"},
    {"lightpink", ESC "[48;5;217m"},
    {"lightsalmon", ESC "[48;5;216m"},
    {"lightseagreen", ESC "[48;5;37m"},
    {"lightskyblue", ESC "[48;5;117m"},
    {"lightslategray", ESC "[48;5;102m"},
    {"lightslategrey", ESC "[48;5;102m"},
    {"lightsteelblue", ESC "[48;5;152m"},
    {"lightyellow", ESC "[48;5;230m"},
    {"lime", ESC "[48;5;10m"},
    {"limegreen", ESC "[48;5;77m"},
    {"linen", ESC "[48;5;255m"},
    {"magenta", ESC "[48;5;13m"},
    {"maroon", ESC "[48;5;1m"},
    {"mediumaquamarine", ESC "[48;5;79m"},
    {"mediumblue", ESC "[48;5;20m"},
    {"mediumorchid", ESC "[48;5;134m"},
    {"mediumpurple", ESC "[48;5;98m"},
    {"mediumseagreen", ESC "[48;5;71m"},
    {"mediumslateblue", ESC "[48;5;99m"},
    {"mediumspringgreen", ESC "[48;5;48m"},
    {"mediumturquoise", ESC "[48;5;80m"},
    {"mediumvioletred", ESC "[48;5;162m"},
    {"midnightblue", ESC "[48;5;4m"},
    {"mintcream", ESC "[48;5;15m"},
    {"mistyrose", ESC "[48;5;224m"},
    {"moccasin", ESC "[48;5;223m"},
    {"navajowhite", ESC "[48;5;223m"},
    {"navy", ESC "[48;5;4m"},
    {"oldlace", ESC "[48;5;230m"},
    {"olive", ESC "[48;5;3m"},
    {"olivedrab", ESC "[48;5;64m"},
    {"orange", ESC "[48;5;214m"},
    {"orangered", ESC "[48;5;202m"},
    {"orchid", ESC "[48;5;170m"},
    {"palegoldenrod", ESC "[48;5;223m"},
    {"palegreen", ESC "[48;5;120m"},
    {"paleturquoise", ESC "[48;5;159m"},
    {"palevioletred", ESC "[48;5;168m"},
    {"papayawhip", ESC "[48;5;230m"},
    {"peachpuff", ESC "[48;5;223m"},
    {"peru", ESC "[48;5;173m"},
    {"pink", ESC "[48;5;218m"},
    {"plum", ESC "[48;5;182m"},
    {"powderblue", ESC "[48;5;152m"},
    {"purple", ESC "[48;5;5m"},
    {"rebeccapurple", ESC "[48;5;60m"},
    {"red", ESC "[48;5;9m"},
    {"rosybrown", ESC "[48;5;138m"},
    {"royalblue", ESC "[48;5;62m"},
    {"saddlebrown", ESC "[48;5;94m"},
    {"salmon", ESC "[48;5;209m"},
    {"sandybrown", ESC "[48;5;215m"},
    {"seagreen", ESC "[48;5;29m"},
    {"seashell", ESC "[48;5;255m"},
    {"sienna", ESC "[48;5;130m"},
    {"silver", ESC "[48;5;7m"},
    {"skyblue", ESC "[48;5;116m"},
    {"slateblue", ESC "[48;5;62m"},
    {"slategray", ESC "[48;5;66m"},
    {"slategrey", ESC "[48;5;66m"},
    {"snow", ESC "[48;5;15m"},
    {"springgreen", ESC "[48;5;48m"},
    {"steelblue", ESC "[48;5;67m"},
    {"tan", ESC "[48;5;180m"},
    {"teal", ESC "[48;5;6m"},
    {"thistle", ESC "[48;5;182m"},
    {"tomato", ESC "[48;5;203m"},
    {"turquoise", ESC "[48;5;80m"},
    {"violet", ESC "[48;5;213m"},
    {"wheat", ESC "[48;5;223m"},
    {"white", ESC "[48;5;15m"},
    {"whitesmoke", ESC "[48;5;255m"},
    {"yellow", ESC "[48;5;11m"},
    {"yellowgreen", ESC "[48;5;113m"},
    {NULL, NULL}  // Sentinel for end of table
};

static ColorLookup fg_colour_table[] = {

    {"aliceblue", ESC "[38;5;15m"},
    {"antiquewhite", ESC "[38;5;224m"},
    {"aqua", ESC "[38;5;14m"},
    {"aquamarine", ESC "[38;5;122m"},
    {"azure", ESC "[38;5;15m"},
    {"beige", ESC "[38;5;230m"},
    {"bisque", ESC "[38;5;224m"},
    {"black", ESC "[38;5;0m"},
    {"blanchedalmond", ESC "[38;5;224m"},
    {"blue", ESC "[38;5;12m"},
    {"blueviolet", ESC "[38;5;92m"},
    {"brown", ESC "[38;5;124m"},
    {"burlywood", ESC "[38;5;180m"},
    {"cadetblue", ESC "[38;5;73m"},
    {"chartreuse", ESC "[38;5;118m"},
    {"chocolate", ESC "[38;5;166m"},
    {"coral", ESC "[38;5;209m"},
    {"cornflowerblue", ESC "[38;5;69m"},
    {"cornsilk", ESC "[38;5;230m"},
    {"crimson", ESC "[38;5;161m"},
    {"cyan", ESC "[38;5;14m"},
    {"darkblue", ESC "[38;5;18m"},
    {"darkcyan", ESC "[38;5;30m"},
    {"darkgoldenrod", ESC "[38;5;136m"},
    {"darkgray", ESC "[38;5;248m"},
    {"darkgreen", ESC "[38;5;22m"},
    {"darkgrey", ESC "[38;5;248m"},
    {"darkkhaki", ESC "[38;5;143m"},
    {"darkmagenta", ESC "[38;5;90m"},
    {"darkolivegreen", ESC "[38;5;239m"},
    {"darkorange", ESC "[38;5;208m"},
    {"darkorchid", ESC "[38;5;98m"},
    {"darkred", ESC "[38;5;88m"},
    {"darksalmon", ESC "[38;5;174m"},
    {"darkseagreen", ESC "[38;5;108m"},
    {"darkslateblue", ESC "[38;5;60m"},
    {"darkslategray", ESC "[38;5;238m"},
    {"darkslategrey", ESC "[38;5;238m"},
    {"darkturquoise", ESC "[38;5;44m"},
    {"darkviolet", ESC "[38;5;92m"},
    {"deeppink", ESC "[38;5;198m"},
    {"deepskyblue", ESC "[38;5;39m"},
    {"dimgray", ESC "[38;5;242m"},
    {"dimgrey", ESC "[38;5;242m"},
    {"dodgerblue", ESC "[38;5;33m"},
    {"firebrick", ESC "[38;5;124m"},
    {"floralwhite", ESC "[38;5;15m"},
    {"forestgreen", ESC "[38;5;28m"},
    {"fuchsia", ESC "[38;5;13m"},
    {"gainsboro", ESC "[38;5;253m"},
    {"ghostwhite", ESC "[38;5;15m"},
    {"gold", ESC "[38;5;220m"},
    {"goldenrod", ESC "[38;5;178m"},
    {"gray", ESC "[38;5;8m"},
    {"green", ESC "[38;5;2m"},
    {"greenyellow", ESC "[38;5;154m"},
    {"grey", ESC "[38;5;8m"},
    {"honeydew", ESC "[38;5;255m"},
    {"hotpink", ESC "[38;5;205m"},
    {"indianred", ESC "[38;5;167m"},
    {"indigo", ESC "[38;5;54m"},
    {"ivory", ESC "[38;5;15m"},
    {"khaki", ESC "[38;5;222m"},
    {"lavender", ESC "[38;5;255m"},
    {"lavenderblush", ESC "[38;5;15m"},
    {"lawngreen", ESC "[38;5;118m"},
    {"lemonchiffon", ESC "[38;5;230m"},
    {"lightblue", ESC "[38;5;152m"},
    {"lightcoral", ESC "[38;5;210m"},
    {"lightcyan", ESC "[38;5;195m"},
    {"lightgoldenrodyellow", ESC "[38;5;230m"},
    {"lightgray", ESC "[38;5;252m"},
    {"lightgreen", ESC "[38;5;120m"},
    {"lightgrey", ESC "[38;5;252m"},
    {"lightpink", ESC "[38;5;217m"},
    {"lightsalmon", ESC "[38;5;216m"},
    {"lightseagreen", ESC "[38;5;37m"},
    {"lightskyblue", ESC "[38;5;117m"},
    {"lightslategray", ESC "[38;5;102m"},
    {"lightslategrey", ESC "[38;5;102m"},
    {"lightsteelblue", ESC "[38;5;152m"},
    {"lightyellow", ESC "[38;5;230m"},
    {"lime", ESC "[38;5;10m"},
    {"limegreen", ESC "[38;5;77m"},
    {"linen", ESC "[38;5;255m"},
    {"magenta", ESC "[38;5;13m"},
    {"maroon", ESC "[38;5;1m"},
    {"mediumaquamarine", ESC "[38;5;79m"},
    {"mediumblue", ESC "[38;5;20m"},
    {"mediumorchid", ESC "[38;5;134m"},
    {"mediumpurple", ESC "[38;5;98m"},
    {"mediumseagreen", ESC "[38;5;71m"},
    {"mediumslateblue", ESC "[38;5;99m"},
    {"mediumspringgreen", ESC "[38;5;48m"},
    {"mediumturquoise", ESC "[38;5;80m"},
    {"mediumvioletred", ESC "[38;5;162m"},
    {"midnightblue", ESC "[38;5;4m"},
    {"mintcream", ESC "[38;5;15m"},
    {"mistyrose", ESC "[38;5;224m"},
    {"moccasin", ESC "[38;5;223m"},
    {"navajowhite", ESC "[38;5;223m"},
    {"navy", ESC "[38;5;4m"},
    {"oldlace", ESC "[38;5;230m"},
    {"olive", ESC "[38;5;3m"},
    {"olivedrab", ESC "[38;5;64m"},
    {"orange", ESC "[38;5;214m"},
    {"orangered", ESC "[38;5;202m"},
    {"orchid", ESC "[38;5;170m"},
    {"palegoldenrod", ESC "[38;5;223m"},
    {"palegreen", ESC "[38;5;120m"},
    {"paleturquoise", ESC "[38;5;159m"},
    {"palevioletred", ESC "[38;5;168m"},
    {"papayawhip", ESC "[38;5;230m"},
    {"peachpuff", ESC "[38;5;223m"},
    {"peru", ESC "[38;5;173m"},
    {"pink", ESC "[38;5;218m"},
    {"plum", ESC "[38;5;182m"},
    {"powderblue", ESC "[38;5;152m"},
    {"purple", ESC "[38;5;5m"},
    {"rebeccapurple", ESC "[38;5;60m"},
    {"red", ESC "[38;5;9m"},
    {"rosybrown", ESC "[38;5;138m"},
    {"royalblue", ESC "[38;5;62m"},
    {"saddlebrown", ESC "[38;5;94m"},
    {"salmon", ESC "[38;5;209m"},
    {"sandybrown", ESC "[38;5;215m"},
    {"seagreen", ESC "[38;5;29m"},
    {"seashell", ESC "[38;5;255m"},
    {"sienna", ESC "[38;5;130m"},
    {"silver", ESC "[38;5;7m"},
    {"skyblue", ESC "[38;5;116m"},
    {"slateblue", ESC "[38;5;62m"},
    {"slategray", ESC "[38;5;66m"},
    {"slategrey", ESC "[38;5;66m"},
    {"snow", ESC "[38;5;15m"},
    {"springgreen", ESC "[38;5;48m"},
    {"steelblue", ESC "[38;5;67m"},
    {"tan", ESC "[38;5;180m"},
    {"teal", ESC "[38;5;6m"},
    {"thistle", ESC "[38;5;182m"},
    {"tomato", ESC "[38;5;203m"},
    {"turquoise", ESC "[38;5;80m"},
    {"violet", ESC "[38;5;213m"},
    {"wheat", ESC "[38;5;223m"},
    {"white", ESC "[38;5;15m"},
    {"whitesmoke", ESC "[38;5;255m"},
    {"yellow", ESC "[38;5;11m"},
    {"yellowgreen", ESC "[38;5;113m"},
    {NULL, NULL}  // Sentinel for end of table
};

static ColorLookup getColour( char* hint )	{

	int i;
	for ( i = 0; fg_colour_table[i].name != NULL; i++ )
        if ( !strcmp(fg_colour_table[i].name, hint) || !strcmp(fg_colour_table[i].code, hint) )
				return fg_colour_table[i];

	ColorLookup c;
	c.name = _dummyname;
	c.code = _dummycode;
	
	return c;
}

const char *getColourCode( char* cn ) {

	ColorLookup cl;
	cl = getColour( cn );
	return strdup( cl.code );
}

const char* getColourString( char* cc )	{
	
    ColorLookup cl;
	cl = getColour( cc );
	return strdup( cl.name );
}

unsigned getColourCount();

int test();
int test()	{
	
	InitColour();
	printf( "Attempting to print colour names in colour table.\n\n" );
	printANSIVTLookupColours();
	
	return 1;
}

void printANSIVTLookupColours()	{
	
	unsigned x = 0;
	char* _ = (char*)calloc( 128, 1 );

	ColorLookup cl;
	
	while( (cl = fg_colour_table[x++]), cl.name != NULL )
		sprintf( _, "%s%s%s\t", cl.code, cl.name, NORMAL ), printf( _ ), free( _ ), _ = (char*)calloc( 128,1 );
	
	free( _ );
	return;
}

char* selectRandomColourCode( char* buf )	{
	
	static unsigned y = 0;
	unsigned x = 0;
	ColorLookup cl;

	if( y==0 )
		y = getColourCount();

	if( buf==NULL )
		buf = (char*)calloc( 16,1 );

	x = ceil( rand()*y );
	cl = fg_colour_table[x];
	
	buf[0] = 0;
	strcat( buf, cl.code );

	return buf;
}

unsigned getColourCount()	{

	static unsigned y = 0;
	if( y!=0 )
		return y;

	ColorLookup cl;

	while(1)	{

		cl = fg_colour_table[y++];
		if( cl.name==NULL )
			break;

		continue;
	}

	return y;
}

char* selectRandomColourString( char* buf )	{

	static unsigned y = 0;
	unsigned x = 0;
	ColorLookup cl;

	if( y==0 )
		y = getColourCount();


	if( buf==NULL )
		buf = (char*)calloc( 16,1 );

	x = ceil( rand()%y + 1 );

	cl = fg_colour_table[x];
	
	buf[0] = 0;
	strcat( buf, cl.name );
	return buf;

}

