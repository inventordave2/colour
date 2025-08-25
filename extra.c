// SOME COLOURLIB EXTRA FNC'S

// Scan a string for a word (not inside an unescaped [ ] colour selector), and colourize it according to rule.
// Example: colour->colourizeFromKeyValuePair( str );
{
	{ "Colour_c", "brightblue" }
	{ "DaveLib", "brightgreen" }
}

#include "./colour.h"


/*

A nonregex linear search&match algorithm.

STR
SUBSTR

x=0;
y=0;

while( (STR[x] != '\0') && (SUBSTR[y] != '\0') )	{

	if( STR[x]==SUBSTR[y] )
		y+=1;
	else
		y=0;
	
	
}
*/




