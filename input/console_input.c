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

void console_init(void) {
#ifdef _WIN32
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &old_mode);
    SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
#else
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    new_term.c_cc[VMIN] = 1;
    new_term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
#endif
}

void console_restore(void) {
#ifdef _WIN32
    SetConsoleMode(hStdin, old_mode);
#else
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
#endif
}

KeyEvent console_read_key(int non_blocking, int timeout_ms) {
    KeyEvent event = {KEY_INVALID, 0, 0, 0, 0};

#ifdef _WIN32
    INPUT_RECORD ir;
    DWORD num_read;
    DWORD start_time = GetTickCount();
    DWORD timeout = timeout_ms >= 0 ? timeout_ms : INFINITE;

    while (1) {
        if (non_blocking || timeout_ms >= 0) {
            if (!PeekConsoleInput(hStdin, &ir, 1, &num_read) || num_read == 0) {
                if (timeout_ms >= 0 && (GetTickCount() - start_time) >= timeout) {
                    return event;
                }
                Sleep(1);
                continue;
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

            if (ctrl && c >= 1 && c <= 26) {
                event.type = KEY_CONTROL;
                event.code = c + 'A' - 1;
                event.ctrl = 1;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (vk >= VK_F1 && vk <= VK_F12) {
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
            } else if (vk == VK_HOME) {
                event.type = KEY_SPECIAL;
                event.code = KEY_HOME;
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            } else if (vk == VK_END) {
                event.type = KEY_SPECIAL;
                event.code = KEY_END;
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
            } else if (c >= 32 && c <= 126) {
                event.type = KEY_NORMAL;
                event.code = c;
                event.ctrl = ctrl ? 1 : 0;
                event.alt = alt ? 1 : 0;
                event.shift = shift ? 1 : 0;
                return event;
            }
        }
        if (timeout_ms >= 0 && (GetTickCount() - start_time) >= timeout) {
            return event;
        }
    }
#else
    char buf[10] = {0};
    int len = 0;

    if (non_blocking || timeout_ms >= 0) {
        struct timeval tv = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        if (select(STDIN_FILENO + 1, &fds, NULL, NULL, timeout_ms >= 0 ? &tv : NULL) <= 0) {
            return event;
        }
    }

    if (read(STDIN_FILENO, &buf[len], 1) <= 0) {
        return event;
    }
    len++;

    if (buf[0] == 27) {
        event.type = KEY_SPECIAL;
        event.code = KEY_ESCAPE;

        int next_char = read(STDIN_FILENO, &buf[len], 1);
        if (next_char > 0 && buf[len] >= 32 && buf[len] <= 126) {
            event.type = KEY_NORMAL;
            event.code = buf[len];
            event.alt = 1;
            return event;
        } else if (next_char > 0 && buf[len] == '[') {
            len++;
            while (len < 9 && read(STDIN_FILENO, &buf[len], 1) > 0) {
                len++;
                if (buf[len-1] >= 64 && buf[len-1] <= 126) break;
            }

            if (len >= 3 && buf[1] == '[') {
                if (buf[2] == 'A') event.code = KEY_UP;
                else if (buf[2] == 'B') event.code = KEY_DOWN;
                else if (buf[2] == 'C') event.code = KEY_RIGHT;
                else if (buf[2] == 'D') event.code = KEY_LEFT;
                else if (buf[2] == 'H') event.code = KEY_HOME;
                else if (buf[2] == 'F') event.code = KEY_END;
                else if (len >= 4 && buf[2] == '1' && buf[len-1] == '~') {
                    int n = buf[3] - '0';
                    if (n >= 1 && n <= 5) event.code = KEY_F1 + (n - 1);
                    else if (n == 7) event.code = KEY_F6;
                    else if (n == 8) event.code = KEY_F7;
                    else if (n == 9) event.code = KEY_F8;
                } else if (len == 5 && buf[2] == '2' && buf[4] == '~') {
                    int n = atoi(&buf[3]);
                    if (n >= 0 && n <= 4) event.code = KEY_F9 + (n - 0);
                    else if (n == 5) event.code = KEY_F12;
                }
                if (len > 3 && buf[len-2] == ';') {
                    int mod = atoi(&buf[3]);
                    if (mod == 2) event.shift = 1;
                    else if (mod == 3) event.alt = 1;
                    else if (mod == 5) event.ctrl = 1;
                    else if (mod == 6) { event.shift = 1; event.alt = 1; }
                    else if (mod == 7) { event.ctrl = 1; event.alt = 1; }
                    else if (mod == 8) { event.ctrl = 1; event.shift = 1; }
                }
            }
            return event;
        }
    } else if (buf[0] >= 1 && buf[0] <= 26) {
        event.type = KEY_CONTROL;
        event.code = buf[0] + 'A' - 1;
        event.ctrl = 1;
        return event;
    } else if (buf[0] >= 32 && buf[0] <= 126) {
        event.type = KEY_NORMAL;
        event.code = buf[0];
        return event;
    }

    return event;
#endif
}

int main() {
    console_init();
    printf("Press keys (Ctrl+C to exit, 500ms timeout):\n");

    while (1) {
        KeyEvent event = console_read_key(1, 500);
        if (event.type == KEY_INVALID) {
            printf("No input or timeout\n");
            continue;
        }

        if (event.type == KEY_CONTROL && event.code == 'C' && event.ctrl) {
            printf("Ctrl+C detected, exiting...\n");
            break;
        }

        printf("Type: %s, Code: ", event.type == KEY_NORMAL ? "Normal" :
                              event.type == KEY_CONTROL ? "Control" :
                              event.type == KEY_SPECIAL ? "Special" : "Invalid");
        if (event.type == KEY_NORMAL || event.type == KEY_CONTROL) {
            printf("%c", event.code);
        } else {
            switch (event.code) {
                case KEY_F1: printf("F1"); break;
                case KEY_F2: printf("F2"); break;
                case KEY_F3: printf("F3"); break;
                case KEY_F4: printf("F4"); break;
                case KEY_F5: printf("F5"); break;
                case KEY_F6: printf("F6"); break;
                case KEY_F7: printf("F7"); break;
                case KEY_F8: printf("F8"); break;
                case KEY_F9: printf("F9"); break;
                case KEY_F10: printf("F10"); break;
                case KEY_F11: printf("F11"); break;
                case KEY_F12: printf("F12"); break;
                case KEY_UP: printf("Up"); break;
                case KEY_DOWN: printf("Down"); break;
                case KEY_LEFT: printf("Left"); break;
                case KEY_RIGHT: printf("Right"); break;
                case KEY_HOME: printf("Home"); break;
                case KEY_END: printf("End"); break;
                case KEY_ESCAPE: printf("Escape"); break;
                default: printf("Unknown");
            }
        }
        if (event.ctrl) printf(" (Ctrl)");
        if (event.alt) printf(" (Alt)");
        if (event.shift) printf(" (Shift)");
        printf("\n");
    }

    console_restore();
    return 0;
}