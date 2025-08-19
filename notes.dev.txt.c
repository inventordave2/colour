// DESIGN CONSIDERATIONS.

Instead of allocating multiple function-time heap-based buffers, causing time and space overhead, a fixed buffer at loadtime could be used to sequentially generate a VT100 formatted string from a provided user input string. Essentially, if the scanner encounters an unescaped '[' symbol (escape chars are \e and \\), it scans through into a seperate small buffer the delimeted colourlib string (e.g. "bright_red"), then identify the vt100 code, and copy that fixed buffer char by char into the large fixed function-time generator buffer. Then, when the corresponding ']' symbol is encountered in the user inputted string, switch back to copying the subsequent chars in that string into the fixed buffer.
Once this process has completed, and we therefore the VT100 processed string, and we know exactly how many bytes we need for the buffer, we generate a buffer that size (remember that the buffer needs to be strlen( newstr ) + 1 for the NULL char '\0'), and copy ito it byte-wise from the fixed buffer. The newstr buffer can then be passed back to the library user.

Whatever the length of the largest VT100 control code sequence, we round it up to a division of 8. The individual fixed control code buffers can then be generated and alocated equal-sized arrays on the heap, and the offset from one to the next is always that size, whatever it is (It would probably be 16)

Assume a maximum length transformed string. 4096 and 8192 are canonical page sizes.

Let's say 4096 chars for string transform buffer, and the other 4096 chars can be used for the VT100 table etc.


#include <stdlib.h>
static char* vt100_buf = (char*)malloc( 8192 );

vt100_buf[0] = 0;
vt100_buf[4095] = 0;
vt100_buf[8191] = 0;


#define CODESTRWIDTHMAX 32

uint32_t y = 0;
for( int x=0; ; x++ )
	
	if( fg_color_table[x].code==NULL )
		break;
	else
		y++;

uint32_t totalCodes = y;

static char** vt100_tabletray = vt100_buf+4096;
vt100_tabletray[ totalCodes*2 ] = 0;

uint32_t z = 0;
for( y=0; y<totalCodes; y++ )
	vt100_tabletray[z++] = fg_color_table.name, vt100_tabletray[z++] = fg_color_table.code;

