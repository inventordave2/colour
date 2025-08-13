#include <stdio.h>
#include <stdlib.h>
#include "console_input.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#endif

#ifdef _WIN32
static HANDLE hStdin;
static DWORD old_mode;
#else
static struct termios old_term, new_term;
#endif

// Initialize console for raw input
void console_init(void) {
#ifdef _WIN32
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &old_mode);
    SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
#else
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    new_term.c_cc[VMIN] = 1;
    new_term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
#endif
}

// Restore console settings
void console_restore(void) {
#ifdef _WIN32
    SetConsoleMode(hStdin, old_mode);
#else
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
#endif
}

// Read a single key event (blocking or non-blocking)
KeyEvent console_read_key(int non_blocking) {
    KeyEvent event = {KEY_INVALID, 0, 0, 0, 0};

#ifdef _WIN32
    INPUT_RECORD ir;
    DWORD num_read;
    while (1) {
        if (non_blocking) {
            if (!PeekConsoleInput(hStdin, &ir, 1, &num_read) || num_read == 0) {
                return event; // No input available
            }
        }
        if (!ReadConsoleInput(hStdin, &ir, 1, &num_read) || num_read != 1) {
            return event;
        }
        if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
            WORD vk = ir.Event.KeyEvent.wVirtualKeyCode;
            DWORD ctrl = ir.Event.KeyEvent.dwControlKeyState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED);
            DWORD alt = ir.Event.KeyEvent.dwControlKeyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED);
            DWORD shift = ir.Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED;
            char c = ir.Event.KeyEvent.uChar.AsciiChar;

            if (ctrl && c >= 1 && c <= 26) { // Ctrl+A to Ctrl+Z
                event.type = KEY_CONTROL;
                event.code = c + 'A' - 1;
                event.ctrl = 1;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (vk >= VK_F1 && vk <= VK_F11) {
                event.type = KEY_SPECIAL;
                event.code = KEY_F1 + (vk - VK_F1);
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (vk == VK_UP) {
                event.type = KEY_SPECIAL;
                event.code = KEY_UP;
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (vk == VK_DOWN) {
                event.type = KEY_SPECIAL;
                event.code = KEY_DOWN;
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (vk == VK_LEFT) {
                event.type = KEY_SPECIAL;
                event.code = KEY_LEFT;
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (vk == VK_RIGHT) {
                event.type = KEY_SPECIAL;
                event.code = KEY_RIGHT;
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (vk == VK_ESCAPE) {
                event.type = KEY_SPECIAL;
                event.code = KEY_ESCAPE;
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (c >= 32 && c <= 126) { // Printable ASCII
                event.type = KEY_NORMAL;
                event.code = c;
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            }
        }
    }
#else
    char buf[10] = {0};
    int len = 0;

    // Non-blocking check
    if (non_blocking) {
        struct timeval tv = {0, 0};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) <= 0) {
            return event; // No input available
        }
    }

    // Read first character
    if (read(STDIN_FILENO, &buf[len], 1) <= 0) {
        return event; // No input or error
    }
    len++;

    if (buf