// TEST_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./colour.h"

int main( int argc, char** argv )	{

	InitColour();
	
	char* str; // = colour->fmt( "This string should have some [green]COLOUR[blue]!!!![reset]\n" );
	//printf( str );
	//free( str );
	
	str = colour->fmt( "A random [yellow]string [magenta]containing any [blue]Colour_c [magenta]string you like!" );
	printf( str );
	printf( "\n" );
	free( str );
	str = colour->fmt("[reset]");
	printf( str );
	printf( "\n" );
	free( str );

	if( argc>1 )	{

		char* in;
		argv++;

		while( argc>1 )	{

			in = strdup( *argv );
			str = colour->fmt( in );
			printf( str );
			free( str );
			str = colour->fmt( "[reset]" );
			printf( str );
			free( str );
			printf( "\n" );
			argc--;
			argv++;

			free( in );
		}
	}

	return 0;
}

