#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

typedef enum {
    KEY_NORMAL,
    KEY_SPECIAL,
    KEY_CONTROL,
    KEY_INVALID
} KeyType;

enum {
    KEY_F1 = 1000,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_HOME,
    KEY_END,
    KEY_ESCAPE
};

typedef struct {
    KeyType type;
    int code;
    int ctrl;
    int alt;
    int shift;
} KeyEvent;

void console_init(void);
void console_restore(void);
KeyEvent console_read_key(int non_blocking, int timeout_ms);

#endif

