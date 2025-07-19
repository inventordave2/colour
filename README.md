# Colour

ANSI/VT virtual terminal support for win32 console.

For use in your presumably lesser, but still lovingly-attempted, console programs (especially for Win32).

To Compile the simple test driver:

	'make colourtest'

Then, you can either just type 'colourtest' in the console, or perhaps type something like:

	colourtest "A random [yellow]string [magenta]containing any [blue]Colour_c [magenta] string you like!"

You can pass multiple strings on the command line to the 'colourtest' test app if you wish. BUT REMEMBER!!! TOO MUCH COLOUR, WILL KILL YOU, EVERY TIME!!! Ask Freddie Mercury! Ask my Mother!

To compile the library:

	make colour

Or, for debug symbols, not that you'll ever need them:

	make colour_d

Use "./path/to/colour.h" in your referencing source file, and link the colour.o or colour_d.o lib file when compiling/linking your, frankly, miraculously-improved console app.


Dave.
