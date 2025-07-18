
				    ANSICON
				  Version 1.81

This is a complete list of the ANSI/VT escape sequences recognised by ANSICON,
roughly ordered by function.  The initial escape character is assumed.	The
display consists of the buffer width and window height; add '+' before the
final character to use the buffer height (e.g. "[2J" will erase the window,
whilst "[2+J" will erase the buffer).  BEL will also be recognised, playing
the Windows default beep (but only if it's not already playing).


[m	restore default color (and intensity)
[0m	as above
[...m	set attributes (any of these numbers, separated by semicolons):
		 0	all attributes off
		 1	bold (foreground is intense)
		 4	underline (background is intense)
		 5	blink (background is intense)
		 7	reverse video
		 8	concealed (foreground becomes background)
		22	bold off (foreground is not intense)
		24	underline off (background is not intense)
		25	blink off (background is not intense)
		27	normal video
		28	concealed off
		30	foreground black
		31	foreground red
		32	foreground green
		33	foreground yellow
		34	foreground blue
		35	foreground magenta
		36	foreground cyan
		37	foreground white
		38;2;#	foreground based on index (0-255)
		38;5;#;#;# foreground based on RGB
		39	default foreground (using current intensity)
		40	background black
		41	background red
		42	background green
		43	background yellow
		44	background blue
		45	background magenta
		46	background cyan
		47	background white
		48;2;#	background based on index (0-255)
		48;5;#;#;# background based on RGB
		49	default background (using current intensity)
	       106	background bright cyan
	       107	background bright white

	  Index is 0-7 for the normal colors and 8-15 for the bright; 16-231
	  are a 6x6x6 color cube; and 232-255 are a grayscale ramp (without
		90	foreground bright black
		91	foreground bright red
		92	foreground bright green
		93	foreground bright yellow
		94	foreground bright blue
		95	foreground bright magenta
		96	foreground bright cyan
		97	foreground bright white
	       100	background bright black
	       101	background bright red
	       102	background bright green
	       103	background bright yellow
	       104	background bright blue
	       105	background bright magenta
	  black or white).  Indices 16-255 and RGB colors will find the nearest
	  color from the first 16.

/**
		38;2;#	foreground based on index (0-255)
		38;5;#;#;# foreground based on RGB

		48;2;#	background based on index (0-255)
		48;5;#;#;# background based on RGB

[2J	erase display and move cursor to the top-left


*/


[J	erase from cursor to the end of display
[0J	as above
[1J	erase from the start of diplay to cursor (inclusive)
[2J	erase display and move cursor to the top-left

[K	erase from cursor to the end of line
[0K	as above
[1K	erase from the start of line to cursor (inclusive)
[2K	erase line

[X	erase one character
[#X	erase # characters

[L	insert one blank line
[#L	insert # blank lines

[M	DEL one line
[#M	DEL # lines

[P	DEL one character
[#P	DEL # characters

[@	insert one blank character
[#@	insert # blank characters

[b	repeat the previous character
[#b	repeat the previous character # times

D	move cursor down one line (scroll if necessary; always uses buffer)
E	same as LF
M	move cursor up one line (scroll if necessary; always uses buffer)

[A	move cursor up one line
[#A	move cursor up # lines
[B	move cursor down one line
[#B	move cursor down # lines
[C	move cursor right one character
[#C	move cursor right # characters
[D	move cursor left one character
[#D	move cursor left # characters

H	set tab stop
[g	remove tab stop at cursor
[0g	as above
[3g	remove all tab stops
[8g	restore console tab handling (ANSICON extension)
[?5W	set tab stops every 8 columns
[?5;#W	set tab stops every # columns (ANSICON extension)
[I	move cursor forward one tab
[#I	move cursor forward # tabs
[Z	move cursor back one tab
[#Z	move cursor back # tabs

[k	move cursor up one line
[#k	move cursor up # lines
[e	move cursor down one line
[#e	move cursor down # lines
[a	move cursor right one character
[#a	move cursor right # characters
[j	move cursor left one character
[#j	move cursor left # characters

[E	move cursor down one line and to first column
[#E	move cursor down # lines and to first column
[F	move cursor up one line and to first column
[#F	move cursor up # lines and to first column

[G	move cursor to first column
[#G	move cursor to column #

[`	move cursor to first column
[#`	move cursor to column #

[d	move cursor to first line
[#d	move cursor to line #

[H	move cursor to top-left
[#H	move cursor to line # and first column
[#;#H	move cursor to line #, column #

[f	move cursor to top-left
[#f	move cursor to line # and first column
[#;#f	move cursor to line #, column #

[s	save cursor position (buffer only)
[u	move cursor to saved position (or top-left, if nothing was saved)
7	save cursor position (buffer only), attributes and G0 character set
8	restore above (if nothing was saved only moves cursor to top-left)

[+r	remove top and bottom margins
[r	set top and bottom margins to the window
[#r	set top margin to line #, bottom margin to the window
[#;#r	set top margin to line #, bottom margin to line #

[S	scroll up (pan down) one line
[#S	scroll up (pan down) # lines
[T	scroll down (pan up) one line
[#T	scroll down (pan up) # lines

(0	select the DEC Special Graphics Character Set
(B	select ASCII

[1+h	flush immediately on write
[1+l	flush only when necessary
[3h	display control characters (LF is also performed)
[3l	perform control functions (the only such recognised during above)
[4h	insert characters
[4l	replace characters
[?3h	set 132 columns
[?3l	restore original columns
[?6h	set origin to top margin
[?6l	set origin to top line
[?7h	wrap lines at screen edge
[?7l	don't wrap lines at screen edge
[?25h	show cursor
[?25l	hide cursor
[?95h	don't clear screen when changing columns
[?95l	clear screen when changing columns

[!p	soft reset:
	  show cursor
	  perform control functions
	  replace characters
	  set origin to top line
	  wrap lines at screen edge
	  select ASCII
	  remove margins
	  default SGR
	  set the saved cursor to the top-left
c	hard reset:
	  as above
	  restore console tab handling
	  restore the entire palette
	  restore original columns
	  clear screen when changing columns
	  clear the buffer
	  home the cursor

[c	sends "\e[?62;1c" to console input (where \e is escape)
[0c	as above
[5n	sends "\e[0n" to console input
[6n	sends "\e[#;#R" (line & column) to console input
[21t	sends "\e]lTitle\e\" (the console's window title) to console input
]0;TitleST
]2;TitleST
	sets the console title to "Title"; ST (string terminator) is either
	 character 7 (BEL) or escape and backslash
]4;#;spec,spec...;#...ST
	set or query the palette:
	  # is the ANSI index (0-7, or 8-15 for bright)
	  spec is:
		?		    send the current value to console input
		*		    send the current and all subsequent values
				      (up to 15 if index is less than that)
		#RGB		    set the color (hexadecimal)
		#RRGGBB 	    set the color (hexadecimal)
		R,G,B		    set the color (decimal)
		rgb:RR/GG/BB	    set the color (hexadecimal)
		rgb:RRRR/GGGG/BBBB  set the color (hexadecimal, high byte)
]104ST	restore the entire palette
]104;#...ST
	restore the color of each index

[#;#;#...,~
	play sound (beep):
	  the first value is volume: 0 is silence, anything else is ignored
	  the second value is duration: up to and including 48 is in 1/32 of a
	   second; anything else is milliseconds (maximum of 8000)
	  the remaining values (if any; 14 allowed) are notes or frequencies:
	    Value  Note     Freq   Value  Note	   Freq   Value  Note	  Freq
		0  silence     0       9  G#5/Ab5   830      18  F6	  1396
		1  C5	     524      10  A5	    880      19  F#6/Gb6  1480
		2  C#5/Db5   554      11  A#5/Bb5   932      20  G6	  1568
		3  D5	     588      12  B5	    988      21  G#6/Ab6  1662
		4  D#5/Eb5   622      13  C6	   1046      22  A6	  1760
		5  E5	     660      14  C#6/Db6  1108      23  A#6/Bb6  1864
		6  F5	     698      15  D6	   1174      24  B6	  1976
		7  F#5/Gb5   740      16  D#6/Eb6  1244      25  C7	  2094
		8  G5	     784      17  E6	   1318

P...ST	ignored (Device Control String)
X...ST	ignored (Start Of String)
^...ST	ignored (Privacy Message)
_...ST	ignored (Application Program Command)

Any of space and !"#$%&'()*+,-./, possibly repeated, followed by anything else,
will be ignored.
