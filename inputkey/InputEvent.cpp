#include "InputEvent.h"
#include "stdio.h"
#include "string.h"

#include "fcntl.h"
#include "unistd.h"
#include "pthread.h"
#include <sys/time.h>

#define INPUTEVNETPATH "/dev/input/event1"
#define UI_WAIT_KEY_TIMEOUT_SEC  100*1000*1000
InputEvent *InputEvent::mInstance = 0;
// Key event input queue
static pthread_mutex_t key_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t key_queue_cond = PTHREAD_COND_INITIALIZER;
static int key_queue[256], key_queue_len = 0;
static volatile char key_pressed[256];

InputEvent::InputEvent() {
    mInputFd= open(INPUTEVNETPATH, O_RDONLY);
    if(mInputFd < 0) {
        printf("open %s failed\n", INPUTEVNETPATH);
    }
    int ret;
    pthread_t pid;
    ret = pthread_create(&pid,NULL,InputEvent::inputEventThreadFunc,this);
    printf("create success\n");
    if(ret <0){
        printf("inputEvent thread init failed\n");
    }
    bShortPress = 1;
}

InputEvent::~InputEvent() {
    if (mInputFd > 0) {
        close(mInputFd);
    }
}

InputEvent *InputEvent::getInstance() {
    if (!mInstance)
        mInstance = new InputEvent();
    return mInstance;
}

struct input_event InputEvent::getKeyEvent() {
    int ret;
    fd_set rds;
    FD_ZERO(&rds);
    FD_SET(mInputFd, &rds);
    printf("InputEvent::getKeyEvent\n");
    do {
        printf("select before\n");
        ret = select(mInputFd + 1, &rds, NULL, NULL, NULL);
        printf("select after\n");
        if (ret > 0) {
            if (FD_ISSET(mInputFd, &rds)) {   
                ret = read(mInputFd, &inputevent, sizeof(inputevent));
                if (ret == sizeof(inputevent)) {
                    if ((inputevent.type == EV_KEY) && ((inputevent.value == 1)  || (inputevent.value == 0))) {
                        key_pressed[inputevent.code] = inputevent.value;
                        printf("key %d %s,time=%d\n", inputevent.code, inputevent.value ? "Pressed" : "Released",inputevent.time);
                    }
                } else {
                    printf("read device failde\n");
                }
            }
        }
    } while(false);
    return inputevent;
}

//new a thread to listen key
void* InputEvent::inputEventThreadFunc(void* arg){
    printf("inputEventThreadFunc\n");

    pthread_detach(pthread_self());//set detached state
    InputEvent *  inputEvent  = (InputEvent *)arg;
    for(;;){
        printf("loop\n");
        inputEvent->getKeyEvent();
        inputEvent-> despatchThreadLoop();
    }
    return (void*)NULL;
}

void InputEvent::despatchThreadLoop( ){
    pthread_mutex_lock(&key_queue_mutex);
    const int queue_max = sizeof(key_queue) / sizeof(key_queue[0]);
    if (inputevent.value > 0 && key_queue_len < queue_max) {
    key_queue[key_queue_len++] = inputevent.code;
        pthread_cond_signal(&key_queue_cond);
    }
    pthread_mutex_unlock(&key_queue_mutex);
}

// exporse a interface to othrer thread to controller the input thread
// 

int InputEvent::ui_wait_key(){
    pthread_mutex_lock(&key_queue_mutex);
    KeyEvent key = KNONE;
    int rc = 0;
    while (key_queue_len == 0 ) {
        {
            rc = pthread_cond_timedwait(&key_queue_cond, &key_queue_mutex,NULL);
        }
    }
    if (key_queue_len > 0) {
        bShortPress = 1;
        key = (KeyEvent)key_queue[0];
        memcpy(&key_queue[0], &key_queue[1],sizeof(int) * --key_queue_len);
    }
    pthread_mutex_unlock(&key_queue_mutex);
    return key;
}
