// TEST_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./colour.h"
#include "./schemes.h"

int main( int argc, char** argv )	{

	InitColour();
	
	char* str;
	
	char* temp;
	printf( (temp=colour->fmt( GAZA )) );
	free( temp );
	printf( "\n" );

	if( argc==1 )	{
		
		str = colour->fmt( "A random [yellow]string [magenta]containing any [blue]Colour_c [magenta]codes you like." );
		printf( str );
		free( str );
		str = colour->fmt( "[reset]" );
		printf( str );
		free( str );
		printf( "\n" );

		exit(0);
	}

	char* in;
	argv++;

	while( argc>1 )	{

		in = strdup( *argv );
		str = colour->fmt( in );
		free( in );
		
		printf( str );
		free( str );
		
		str = colour->fmt( "[reset]" );
		printf( str );
		free( str );
		
		printf( "\n" );
		argc--;
		argv++;
	}

	return 0;
}

