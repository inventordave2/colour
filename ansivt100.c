// ANSIVT100_256_LOOKUP

#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "./colour.h"
#include "./schemes.h"
#include "./ansivt100.h"

static const char* _dummyname = "";
static const char* _dummycode = "";

typedef struct ColorLookup {

    const char *name;
    const char *code;

} ColorLookup;
static ColorLookup getColour( char* hint );

static ColorLookup bg_colour_table[] = {
    {"aliceblue", "\033[48;5;15m"},
    {"antiquewhite", "\033[48;5;224m"},
    {"aqua", "\033[48;5;14m"},
    {"aquamarine", "\033[48;5;122m"},
    {"azure", "\033[48;5;15m"},
    {"beige", "\033[48;5;230m"},
    {"bisque", "\033[48;5;224m"},
    {"black", "\033[48;5;0m"},
    {"blanchedalmond", "\033[48;5;224m"},
    {"blue", "\033[48;5;12m"},
    {"blueviolet", "\033[48;5;92m"},
    {"brown", "\033[48;5;124m"},
    {"burlywood", "\033[48;5;180m"},
    {"cadetblue", "\033[48;5;73m"},
    {"chartreuse", "\033[48;5;118m"},
    {"chocolate", "\033[48;5;166m"},
    {"coral", "\033[48;5;209m"},
    {"cornflowerblue", "\033[48;5;69m"},
    {"cornsilk", "\033[48;5;230m"},
    {"crimson", "\033[48;5;161m"},
    {"cyan", "\033[48;5;14m"},
    {"darkblue", "\033[48;5;18m"},
    {"darkcyan", "\033[48;5;30m"},
    {"darkgoldenrod", "\033[48;5;136m"},
    {"darkgray", "\033[48;5;248m"},
    {"darkgreen", "\033[48;5;22m"},
    {"darkgrey", "\033[48;5;248m"},
    {"darkkhaki", "\033[48;5;143m"},
    {"darkmagenta", "\033[48;5;90m"},
    {"darkolivegreen", "\033[48;5;239m"},
    {"darkorange", "\033[48;5;208m"},
    {"darkorchid", "\033[48;5;98m"},
    {"darkred", "\033[48;5;88m"},
    {"darksalmon", "\033[48;5;174m"},
    {"darkseagreen", "\033[48;5;108m"},
    {"darkslateblue", "\033[48;5;60m"},
    {"darkslategray", "\033[48;5;238m"},
    {"darkslategrey", "\033[48;5;238m"},
    {"darkturquoise", "\033[48;5;44m"},
    {"darkviolet", "\033[48;5;92m"},
    {"deeppink", "\033[48;5;198m"},
    {"deepskyblue", "\033[48;5;39m"},
    {"dimgray", "\033[48;5;242m"},
    {"dimgrey", "\033[48;5;242m"},
    {"dodgerblue", "\033[48;5;33m"},
    {"firebrick", "\033[48;5;124m"},
    {"floralwhite", "\033[48;5;15m"},
    {"forestgreen", "\033[48;5;28m"},
    {"fuchsia", "\033[48;5;13m"},
    {"gainsboro", "\033[48;5;253m"},
    {"ghostwhite", "\033[48;5;15m"},
    {"gold", "\033[48;5;220m"},
    {"goldenrod", "\033[48;5;178m"},
    {"gray", "\033[48;5;8m"},
    {"green", "\033[48;5;2m"},
    {"greenyellow", "\033[48;5;154m"},
    {"grey", "\033[48;5;8m"},
    {"honeydew", "\033[48;5;255m"},
    {"hotpink", "\033[48;5;205m"},
    {"indianred", "\033[48;5;167m"},
    {"indigo", "\033[48;5;54m"},
    {"ivory", "\033[48;5;15m"},
    {"khaki", "\033[48;5;222m"},
    {"lavender", "\033[48;5;255m"},
    {"lavenderblush", "\033[48;5;15m"},
    {"lawngreen", "\033[48;5;118m"},
    {"lemonchiffon", "\033[48;5;230m"},
    {"lightblue", "\033[48;5;152m"},
    {"lightcoral", "\033[48;5;210m"},
    {"lightcyan", "\033[48;5;195m"},
    {"lightgoldenrodyellow", "\033[48;5;230m"},
    {"lightgray", "\033[48;5;252m"},
    {"lightgreen", "\033[48;5;120m"},
    {"lightgrey", "\033[48;5;252m"},
    {"lightpink", "\033[48;5;217m"},
    {"lightsalmon", "\033[48;5;216m"},
    {"lightseagreen", "\033[48;5;37m"},
    {"lightskyblue", "\033[48;5;117m"},
    {"lightslategray", "\033[48;5;102m"},
    {"lightslategrey", "\033[48;5;102m"},
    {"lightsteelblue", "\033[48;5;152m"},
    {"lightyellow", "\033[48;5;230m"},
    {"lime", "\033[48;5;10m"},
    {"limegreen", "\033[48;5;77m"},
    {"linen", "\033[48;5;255m"},
    {"magenta", "\033[48;5;13m"},
    {"maroon", "\033[48;5;1m"},
    {"mediumaquamarine", "\033[48;5;79m"},
    {"mediumblue", "\033[48;5;20m"},
    {"mediumorchid", "\033[48;5;134m"},
    {"mediumpurple", "\033[48;5;98m"},
    {"mediumseagreen", "\033[48;5;71m"},
    {"mediumslateblue", "\033[48;5;99m"},
    {"mediumspringgreen", "\033[48;5;48m"},
    {"mediumturquoise", "\033[48;5;80m"},
    {"mediumvioletred", "\033[48;5;162m"},
    {"midnightblue", "\033[48;5;4m"},
    {"mintcream", "\033[48;5;15m"},
    {"mistyrose", "\033[48;5;224m"},
    {"moccasin", "\033[48;5;223m"},
    {"navajowhite", "\033[48;5;223m"},
    {"navy", "\033[48;5;4m"},
    {"oldlace", "\033[48;5;230m"},
    {"olive", "\033[48;5;3m"},
    {"olivedrab", "\033[48;5;64m"},
    {"orange", "\033[48;5;214m"},
    {"orangered", "\033[48;5;202m"},
    {"orchid", "\033[48;5;170m"},
    {"palegoldenrod", "\033[48;5;223m"},
    {"palegreen", "\033[48;5;120m"},
    {"paleturquoise", "\033[48;5;159m"},
    {"palevioletred", "\033[48;5;168m"},
    {"papayawhip", "\033[48;5;230m"},
    {"peachpuff", "\033[48;5;223m"},
    {"peru", "\033[48;5;173m"},
    {"pink", "\033[48;5;218m"},
    {"plum", "\033[48;5;182m"},
    {"powderblue", "\033[48;5;152m"},
    {"purple", "\033[48;5;5m"},
    {"rebeccapurple", "\033[48;5;60m"},
    {"red", "\033[48;5;9m"},
    {"rosybrown", "\033[48;5;138m"},
    {"royalblue", "\033[48;5;62m"},
    {"saddlebrown", "\033[48;5;94m"},
    {"salmon", "\033[48;5;209m"},
    {"sandybrown", "\033[48;5;215m"},
    {"seagreen", "\033[48;5;29m"},
    {"seashell", "\033[48;5;255m"},
    {"sienna", "\033[48;5;130m"},
    {"silver", "\033[48;5;7m"},
    {"skyblue", "\033[48;5;116m"},
    {"slateblue", "\033[48;5;62m"},
    {"slategray", "\033[48;5;66m"},
    {"slategrey", "\033[48;5;66m"},
    {"snow", "\033[48;5;15m"},
    {"springgreen", "\033[48;5;48m"},
    {"steelblue", "\033[48;5;67m"},
    {"tan", "\033[48;5;180m"},
    {"teal", "\033[48;5;6m"},
    {"thistle", "\033[48;5;182m"},
    {"tomato", "\033[48;5;203m"},
    {"turquoise", "\033[48;5;80m"},
    {"violet", "\033[48;5;213m"},
    {"wheat", "\033[48;5;223m"},
    {"white", "\033[48;5;15m"},
    {"whitesmoke", "\033[48;5;255m"},
    {"yellow", "\033[48;5;11m"},
    {"yellowgreen", "\033[48;5;113m"},
    {NULL, NULL}  // Sentinel for end of table
};

static ColorLookup fg_colour_table[] = {
    {"aliceblue", "\033[38;5;15m"},
    {"antiquewhite", "\033[38;5;224m"},
    {"aqua", "\033[38;5;14m"},
    {"aquamarine", "\033[38;5;122m"},
    {"azure", "\033[38;5;15m"},
    {"beige", "\033[38;5;230m"},
    {"bisque", "\033[38;5;224m"},
    {"black", "\033[38;5;0m"},
    {"blanchedalmond", "\033[38;5;224m"},
    {"blue", "\033[38;5;12m"},
    {"blueviolet", "\033[38;5;92m"},
    {"brown", "\033[38;5;124m"},
    {"burlywood", "\033[38;5;180m"},
    {"cadetblue", "\033[38;5;73m"},
    {"chartreuse", "\033[38;5;118m"},
    {"chocolate", "\033[38;5;166m"},
    {"coral", "\033[38;5;209m"},
    {"cornflowerblue", "\033[38;5;69m"},
    {"cornsilk", "\033[38;5;230m"},
    {"crimson", "\033[38;5;161m"},
    {"cyan", "\033[38;5;14m"},
    {"darkblue", "\033[38;5;18m"},
    {"darkcyan", "\033[38;5;30m"},
    {"darkgoldenrod", "\033[38;5;136m"},
    {"darkgray", "\033[38;5;248m"},
    {"darkgreen", "\033[38;5;22m"},
    {"darkgrey", "\033[38;5;248m"},
    {"darkkhaki", "\033[38;5;143m"},
    {"darkmagenta", "\033[38;5;90m"},
    {"darkolivegreen", "\033[38;5;239m"},
    {"darkorange", "\033[38;5;208m"},
    {"darkorchid", "\033[38;5;98m"},
    {"darkred", "\033[38;5;88m"},
    {"darksalmon", "\033[38;5;174m"},
    {"darkseagreen", "\033[38;5;108m"},
    {"darkslateblue", "\033[38;5;60m"},
    {"darkslategray", "\033[38;5;238m"},
    {"darkslategrey", "\033[38;5;238m"},
    {"darkturquoise", "\033[38;5;44m"},
    {"darkviolet", "\033[38;5;92m"},
    {"deeppink", "\033[38;5;198m"},
    {"deepskyblue", "\033[38;5;39m"},
    {"dimgray", "\033[38;5;242m"},
    {"dimgrey", "\033[38;5;242m"},
    {"dodgerblue", "\033[38;5;33m"},
    {"firebrick", "\033[38;5;124m"},
    {"floralwhite", "\033[38;5;15m"},
    {"forestgreen", "\033[38;5;28m"},
    {"fuchsia", "\033[38;5;13m"},
    {"gainsboro", "\033[38;5;253m"},
    {"ghostwhite", "\033[38;5;15m"},
    {"gold", "\033[38;5;220m"},
    {"goldenrod", "\033[38;5;178m"},
    {"gray", "\033[38;5;8m"},
    {"green", "\033[38;5;2m"},
    {"greenyellow", "\033[38;5;154m"},
    {"grey", "\033[38;5;8m"},
    {"honeydew", "\033[38;5;255m"},
    {"hotpink", "\033[38;5;205m"},
    {"indianred", "\033[38;5;167m"},
    {"indigo", "\033[38;5;54m"},
    {"ivory", "\033[38;5;15m"},
    {"khaki", "\033[38;5;222m"},
    {"lavender", "\033[38;5;255m"},
    {"lavenderblush", "\033[38;5;15m"},
    {"lawngreen", "\033[38;5;118m"},
    {"lemonchiffon", "\033[38;5;230m"},
    {"lightblue", "\033[38;5;152m"},
    {"lightcoral", "\033[38;5;210m"},
    {"lightcyan", "\033[38;5;195m"},
    {"lightgoldenrodyellow", "\033[38;5;230m"},
    {"lightgray", "\033[38;5;252m"},
    {"lightgreen", "\033[38;5;120m"},
    {"lightgrey", "\033[38;5;252m"},
    {"lightpink", "\033[38;5;217m"},
    {"lightsalmon", "\033[38;5;216m"},
    {"lightseagreen", "\033[38;5;37m"},
    {"lightskyblue", "\033[38;5;117m"},
    {"lightslategray", "\033[38;5;102m"},
    {"lightslategrey", "\033[38;5;102m"},
    {"lightsteelblue", "\033[38;5;152m"},
    {"lightyellow", "\033[38;5;230m"},
    {"lime", "\033[38;5;10m"},
    {"limegreen", "\033[38;5;77m"},
    {"linen", "\033[38;5;255m"},
    {"magenta", "\033[38;5;13m"},
    {"maroon", "\033[38;5;1m"},
    {"mediumaquamarine", "\033[38;5;79m"},
    {"mediumblue", "\033[38;5;20m"},
    {"mediumorchid", "\033[38;5;134m"},
    {"mediumpurple", "\033[38;5;98m"},
    {"mediumseagreen", "\033[38;5;71m"},
    {"mediumslateblue", "\033[38;5;99m"},
    {"mediumspringgreen", "\033[38;5;48m"},
    {"mediumturquoise", "\033[38;5;80m"},
    {"mediumvioletred", "\033[38;5;162m"},
    {"midnightblue", "\033[38;5;4m"},
    {"mintcream", "\033[38;5;15m"},
    {"mistyrose", "\033[38;5;224m"},
    {"moccasin", "\033[38;5;223m"},
    {"navajowhite", "\033[38;5;223m"},
    {"navy", "\033[38;5;4m"},
    {"oldlace", "\033[38;5;230m"},
    {"olive", "\033[38;5;3m"},
    {"olivedrab", "\033[38;5;64m"},
    {"orange", "\033[38;5;214m"},
    {"orangered", "\033[38;5;202m"},
    {"orchid", "\033[38;5;170m"},
    {"palegoldenrod", "\033[38;5;223m"},
    {"palegreen", "\033[38;5;120m"},
    {"paleturquoise", "\033[38;5;159m"},
    {"palevioletred", "\033[38;5;168m"},
    {"papayawhip", "\033[38;5;230m"},
    {"peachpuff", "\033[38;5;223m"},
    {"peru", "\033[38;5;173m"},
    {"pink", "\033[38;5;218m"},
    {"plum", "\033[38;5;182m"},
    {"powderblue", "\033[38;5;152m"},
    {"purple", "\033[38;5;5m"},
    {"rebeccapurple", "\033[38;5;60m"},
    {"red", "\033[38;5;9m"},
    {"rosybrown", "\033[38;5;138m"},
    {"royalblue", "\033[38;5;62m"},
    {"saddlebrown", "\033[38;5;94m"},
    {"salmon", "\033[38;5;209m"},
    {"sandybrown", "\033[38;5;215m"},
    {"seagreen", "\033[38;5;29m"},
    {"seashell", "\033[38;5;255m"},
    {"sienna", "\033[38;5;130m"},
    {"silver", "\033[38;5;7m"},
    {"skyblue", "\033[38;5;116m"},
    {"slateblue", "\033[38;5;62m"},
    {"slategray", "\033[38;5;66m"},
    {"slategrey", "\033[38;5;66m"},
    {"snow", "\033[38;5;15m"},
    {"springgreen", "\033[38;5;48m"},
    {"steelblue", "\033[38;5;67m"},
    {"tan", "\033[38;5;180m"},
    {"teal", "\033[38;5;6m"},
    {"thistle", "\033[38;5;182m"},
    {"tomato", "\033[38;5;203m"},
    {"turquoise", "\033[38;5;80m"},
    {"violet", "\033[38;5;213m"},
    {"wheat", "\033[38;5;223m"},
    {"white", "\033[38;5;15m"},
    {"whitesmoke", "\033[38;5;255m"},
    {"yellow", "\033[38;5;11m"},
    {"yellowgreen", "\033[38;5;113m"},
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

static int main( int argc, char** argv )	{
	
	InitColour();
	printf( "Attempting to print colour names in colour table.\n\n" );
	printANSIVTLookupColours();
	
	return 0;
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

