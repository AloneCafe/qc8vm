#include "timer.h"

/* 振铃操作 */
void playBeep() {
    /* TODO: OpenAL call */
}

/* 60Hz 定时器循环线程 */
void timerThreadProc() {
    while (1) {
        /* 将定时器的频率控制在60Hz */
        usleep(16000);

        /* 延时定时器，非 0 递减 */
        if (delayTimer > 0)
            delayTimer--;

        /* 声音定时器，非 0 递减 */
        if (soundTimer > 0)
            soundTimer--;

        /* 声音定时器，非 0 则报警 */
        if (soundTimer > 0)
            playBeep();
    }
}
