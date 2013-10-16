#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include "linux/input.h"

enum KeyEvent {
    KNONE,
    KHOME = 28,
    KCAMERA = 27,
    KOPTION = 59,
    KSEARCH = 82,
    KVOLUMEDOWN = 114 ,
    KVOLUMEUP = 115,
    KPOWER = 116,
    KBACK = 158,
};

class InputEvent {
public:
    static InputEvent *getInstance();
    struct input_event getKeyEvent();
    static void *inputEventThreadFunc(void *arg);
    int ui_wait_key();
    ~InputEvent();
protected:
    InputEvent();
private:
    void despatchThreadLoop();
    struct input_event  inputevent;
    static InputEvent *mInstance;
    int mInputFd;
    int bShortPress;
};
#endif
