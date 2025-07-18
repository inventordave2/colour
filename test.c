// TEST_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./colour.h"

int main( int argc, char** argv )	{

	InitColour();
	
	char* str = colour->fmt( "This string should have some [bright_green]COLOUR[bright_blue]!!!![reset]\n" );
	printf( str );
	free( str );
	
	if( argc>1 )	{
		
		char* in;
		argv++;
		
		while( argc>1 )	{
			
			in = strdup( *argv );
			str = colour->fmt( in );
			printf( str );
			printf( "\n" );
			argc--;
			argv++;
			
			free( str );
			free( in );
		}
		
		str = colour->fmt( "[reset]" );
		printf( str );
		free( str );
	}
	
	return 0;
}

