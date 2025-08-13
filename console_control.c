#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl>
#endif

// Define constants
#define MAX_WIDTH 80
#define MAX_HEIGHT 24
#define PIXEL_HEIGHT (MAX_HEIGHT * 2)  // For bitmap mode, using half-blocks

// Color enums (basic 16 colors)
typedef enum {
    COLOR_BLACK = 0, COLOR_RED, COLOR_GREEN, COLOR_YELLOW,
    COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE,
    COLOR_BRIGHT_BLACK, COLOR_BRIGHT_RED, COLOR_BRIGHT_GREEN, COLOR_BRIGHT_YELLOW,
    COLOR_BRIGHT_BLUE, COLOR_BRIGHT_MAGENTA, COLOR_BRIGHT_CYAN, COLOR_BRIGHT_WHITE
} Color;

// Screen buffer for text mode: char and attributes
typedef struct {
    char ch;
    Color fg;
    Color bg;
    int dirty;  // Flag if changed
} Cell;

Cell text_buffer[MAX_HEIGHT][MAX_WIDTH];

// Pixel buffer for bitmap mode: 0-15 color, or -1 for transparent/off
int pixel_buffer[PIXEL_HEIGHT][MAX_WIDTH];

// Mode flag
int is_bitmap_mode = 0;

// Platform-specific handles
#ifdef _WIN32
HANDLE hConsole;
#else
struct termios orig_termios;
#endif

// Helper: Get terminal size (fallback to defaults)
void get_terminal_size(int *width, int *height) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    *width = ws.ws_col;
    *height = ws.ws_row;
#endif
    if (*width > MAX_WIDTH) *width = MAX_WIDTH;
    if (*height > MAX_HEIGHT) *height = MAX_HEIGHT;
}

// Initialize console
void init_console() {
#ifdef _WIN32
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Enable ANSI escape codes on Windows (for colors)
    DWORD dwMode = 0;
    GetConsoleMode(hConsole, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);
#else
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
#endif
    // Clear buffers
    memset(text_buffer, 0, sizeof(text_buffer));
    memset(pixel_buffer, -1, sizeof(pixel_buffer));
    clear_screen();
}

// Cleanup console
void cleanup_console() {
#ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
#endif
}

// Clear screen
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J");
#endif
    // Reset buffers
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            text_buffer[y][x].ch = ' ';
            text_buffer[y][x].fg = COLOR_WHITE;
            text_buffer[y][x].bg = COLOR_BLACK;
            text_buffer[y][x].dirty = 1;
        }
    }
    memset(pixel_buffer, -1, sizeof(pixel_buffer));
}

// Set cursor position (0-based)
void set_cursor_pos(int x, int y) {
#ifdef _WIN32
    COORD coord = { (short)x, (short)y };
    SetConsoleCursorPosition(hConsole, coord);
#else
    printf("\033[%d;%dH", y + 1, x + 1);
#endif
}

// Set color (ANSI 16 colors)
void set_color(Color fg, Color bg) {
    int f = fg < 8 ? 30 + fg : 90 + (fg - 8);
    int b = bg < 8 ? 40 + bg : 100 + (bg - 8);
    printf("\033[%d;%dm", f, b);
}

// Reset color
void reset_color() {
    printf("\033[0m");
}

// Switch to text mode
void set_text_mode() {
    is_bitmap_mode = 0;
    clear_screen();
}

// Switch to bitmap mode
void set_bitmap_mode() {
    is_bitmap_mode = 1;
    clear_screen();
}

// Write text at position in text mode
void write_text(int x, int y, const char *text, Color fg, Color bg) {
    if (is_bitmap_mode || x < 0 || y < 0 || y >= MAX_HEIGHT) return;
    int len = strlen(text);
    for (int i = 0; i < len && x + i < MAX_WIDTH; i++) {
        text_buffer[y][x + i].ch = text[i];
        text_buffer[y][x + i].fg = fg;
        text_buffer[y][x + i].bg = bg;
        text_buffer[y][x + i].dirty = 1;
    }
}

// Set pixel in bitmap mode (px, py are pixel coords)
void set_pixel(int px, int py, Color color) {
    if (!is_bitmap_mode || px < 0 || py < 0 || px >= MAX_WIDTH || py >= PIXEL_HEIGHT) return;
    pixel_buffer[py][px] = color;
    // Mark corresponding text cell dirty
    int ty = py / 2;
    text_buffer[ty][px].dirty = 1;
}

// Read char from text buffer
char read_char(int x, int y) {
    if (x < 0 || y < 0 || y >= MAX_HEIGHT || x >= MAX_WIDTH) return ' ';
    return text_buffer[y][x].ch;
}

// Read pixel from bitmap buffer
int read_pixel(int px, int py) {
    if (px < 0 || py < 0 || px >= MAX_WIDTH || py >= PIXEL_HEIGHT) return -1;
    return pixel_buffer[py][px];
}

// Flush screen buffer to console
void flush_screen() {
    int width, height;
    get_terminal_size(&width, &height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (text_buffer[y][x].dirty) {
                set_cursor_pos(x, y);
                if (is_bitmap_mode) {
                    // Render two pixels as half-block
                    int top = pixel_buffer[y * 2][x];
                    int bot = pixel_buffer[y * 2 + 1][x];
                    Color fg = (top >= 0) ? top : COLOR_BLACK;
                    Color bg = (bot >= 0) ? bot : COLOR_BLACK;
                    set_color(fg, bg);
                    if (top >= 0 && bot >= 0) {
                        if (fg == bg) {
                            putchar(' ');
                        } else {
                            putchar('\xdb');  // Full block █ (assuming codepage supports)
                        }
                    } else if (top >= 0) {
                        putchar('\xdf');  // Upper half ▀
                    } else if (bot >= 0) {
                        putchar('\xdc');  // Lower half ▄
                    } else {
                        putchar(' ');
                    }
                } else {
                    // Text mode
                    set_color(text_buffer[y][x].fg, text_buffer[y][x].bg);
                    putchar(text_buffer[y][x].ch);
                }
                text_buffer[y][x].dirty = 0;
            }
        }
    }
    reset_color();
    fflush(stdout);
}

// Example usage
int main() {
    init_console();

    // Text mode example
    set_text_mode();
    write_text(10, 5, "Hello, Text Mode!", COLOR_GREEN, COLOR_BLACK);
    flush_screen();

    // Wait for key
    getchar();

    // Bitmap mode example
    set_bitmap_mode();
    for (int px = 0; px < 20; px++) {
        set_pixel(px, 10, COLOR_RED);
        set_pixel(px, 11, COLOR_BLUE);
    }
    flush_screen();

    // Wait for key
    getchar();

    cleanup_console();
    return 0;
}

