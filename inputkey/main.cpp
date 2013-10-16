/*
 *InputEvent Test 
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "InputEvent.h"

int main(int argc, char *argv[]) {
    InputEvent *mInputEvent = InputEvent::getInstance();
    while (1) {
        int key=0;
        mInputEvent->getKeyEvent();
        key = mInputEvent->ui_wait_key();
        printf("key=%d\n",key);
    }
}
