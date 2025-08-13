#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro to define ESC character
#define ESC "\e"

// Macros for common ANSI VT100 sequences with parameter injection
#define ANSI_CUU(n)          ESC "[" #n "A"        // Cursor Up
#define ANSI_CUD(n)          ESC "[" #n "B"        // Cursor Down
#define ANSI_CUF(n)          ESC "[" #n "C"        // Cursor Forward
#define ANSI_CUB(n)          ESC "[" #n "D"        // Cursor Backward
#define ANSI_CUP(row, col)   ESC "[" #row ";" #col "H" // Cursor Position
#define ANSI_HOME            ESC "[H"              // Cursor Home
#define ANSI_ED(n)           ESC "[" #n "J"        // Erase Display
#define ANSI_EL(n)           ESC "[" #n "K"        // Erase Line
#define ANSI_SU(n)           ESC "[" #n "S"        // Scroll Up
#define ANSI_SD(n)           ESC "[" #n "T"        // Scroll Down
#define ANSI_SGR(...)        ESC "[" #__VA_ARGS__ "m" // Select Graphic Rendition
#define ANSI_SCP             ESC "[s"              // Save Cursor Position
#define ANSI_RCP             ESC "[u"              // Restore Cursor Position
#define ANSI_SHOW_CURSOR     ESC "[?25h"           // Show Cursor
#define ANSI_HIDE_CURSOR     ESC "[?25l"           // Hide Cursor
#define ANSI_ALT_SCREEN_ON   ESC "[?1049h"         // Enable Alternate Screen Buffer
#define ANSI_ALT_SCREEN_OFF  ESC "[?1049l"         // Disable Alternate Screen Buffer

// Helper function to dynamically generate parameterized sequences
char *ansi_sequence(const char *fmt, int n, int m) {
    char *buf = (char*)malloc(32); // Sufficient for most ANSI sequences
    if (!buf) return NULL;
    if (m == -1) {
        snprintf(buf, 32, ESC "[%d%s", n, fmt);
    } else {
        snprintf(buf, 32, ESC "[%d;%d%s", n, m, fmt);
    }
    return buf;
}

// Helper functions for specific sequences
char *ansi_cuu(int n) { return ansi_sequence("A", n, -1); }
char *ansi_cud(int n) { return ansi_sequence("B", n, -1); }
char *ansi_cuf(int n) { return ansi_sequence("C", n, -1); }
char *ansi_cub(int n) { return ansi_sequence("D", n, -1); }
char *ansi_cup(int row, int col) { return ansi_sequence("H", row, col); }
char *ansi_ed(int n) { return ansi_sequence("J", n, -1); }
char *ansi_el(int n) { return ansi_sequence("K", n, -1); }
char *ansi_su(int n) { return ansi_sequence("S", n, -1); }
char *ansi_sd(int n) { return ansi_sequence("T", n, -1); }
char *ansi_sgr(int code1, int code2) {
    char *buf = (char*)malloc(32);
    if (code2 == -1) {
        snprintf(buf, 32, ESC "[%dm", code1);
    } else {
        snprintf(buf, 32, ESC "[%d;%dm", code1, code2);
    }
    return buf;
}

// Print lookup table
void print_ansi_vt100_table() {
    printf("ANSI VT100 Escape Sequences:\n");
    printf("------------------------------------------------------------\n");
    printf("| Sequence            | Name                     | Behavior                              | Parameters                     |\n");
    printf("------------------------------------------------------------\n");
    printf("| ESC [ n A          | Cursor Up (CUU)         | Move cursor up n lines               | n: lines (default 1)          |\n");
    printf("| ESC [ n B          | Cursor Down (CUD)       | Move cursor down n lines             | n: lines (default 1)          |\n");
    printf("| ESC [ n C          | Cursor Forward (CUF)    | Move cursor right n columns          | n: columns (default 1)        |\n");
    printf("| ESC [ n D          | Cursor Backward (CUB)   | Move cursor left n columns           | n: columns (default 1)        |\n");
    printf("| ESC [ n ; m H      | Cursor Position (CUP)   | Move cursor to row n, column m       | n: row, m: column (1-based)   |\n");
    printf("| ESC [ H            | Cursor Home             | Move cursor to (1,1)                 | None                          |\n");
    printf("| ESC [ n J          | Erase Display (ED)      | Clear screen (0=below, 1=above, 2=all)| n: 0, 1, 2 (default 0)       |\n");
    printf("| ESC [ n K          | Erase Line (EL)         | Clear line (0=right, 1=left, 2=all)  | n: 0, 1, 2 (default 0)       |\n");
    printf("| ESC [ n S          | Scroll Up (SU)          | Scroll screen up n lines             | n: lines (default 1)          |\n");
    printf("| ESC [ n T          | Scroll Down (SD)        | Scroll screen down n lines           | n: lines (default 1)          |\n");
    printf("| ESC [ n ; m ; ...m | Select Graphic Rendition| Set text attributes (color, bold)    | n,m: attribute codes          |\n");
    printf("| ESC [ s            | Save Cursor Position    | Save cursor position                 | None                          |\n");
    printf("| ESC [ u            | Restore Cursor Position | Restore saved cursor position        | None                          |\n");
    printf("| ESC [ ? 25 h       | Show Cursor            | Show cursor                          | None                          |\n");
    printf("| ESC [ ? 25 l       | Hide Cursor            | Hide cursor                          | None                          |\n");
    printf("| ESC [ ? 1049 h     | Alt Screen On          | Enable alternate screen buffer       | None                          |\n");
    printf("| ESC [ ? 1049 l     | Alt Screen Off         | Disable alternate screen buffer      | None                          |\n");
    printf("------------------------------------------------------------\n");
    printf("SGR Codes:\n");
    printf("  0: Reset, 1: Bold, 4: Underline, 7: Reverse\n");
    printf("  30–37: Foreground (Black, Red, ..., White)\n");
    printf("  40–47: Background (Black, Red, ..., White)\n");
    printf("  90–97: Bright Foreground, 100–107: Bright Background\n");
}

// Example usage
int main() {
    // Print the lookup table
    print_ansi_vt100_table();

    // Demonstrate macros
    printf("\nUsing macros:\n");
    printf(ANSI_CUP(5, 10) "Text at row 5, column 10\n");
    printf(ANSI_SGR(1;31) "Bold Red Text" ANSI_SGR(0) "\n");

    // Demonstrate helper functions
    char *seq;
    seq = ansi_cup(3, 7);
    printf("\nUsing helper functions:\n");
    printf("%sText at row 3, column 7\n", seq);
    free(seq);

    seq = ansi_sgr(4, 34);
    printf("%sUnderlined Blue Text%s\n", seq, ANSI_SGR(0));
    free(seq);

    return 0;
}

