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


The currently-implemented options (colour_tzing, but not other formatting yet) are:

black
red
green
blue
yellow
cyan
magenta
white

As well as their derivable forms:

bright_black
bright_red
bright_green
bright_blue
bright_yellow
bright_cyan
bright_magenta
bright_white

And the additional options of:

bg:colour_name
fg:colour_name


Not to mention that in any user inserted colourlib delimeters '[' and ']' (unescaped. If you want the literal printable character '[', escape it as such: \\\\[ ) you can have comma-delimeted multiple options, for example:

[bg:bright_yellow,bright_blue] ( This is the same as [bg:bright_yellow,fg:bright_blue], because the prefix "fg:" can be implicit, whereas "bg:"cannot. )

My mommy calls me scoochy-woochy-mccuteface, but you can call me Dave.


Dave.
