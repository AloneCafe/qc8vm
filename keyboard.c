#include "keyboard.h"

/* key（0x0 ～ 0xF）按下操作, 键状态置 1 */
void keyPress(int key) {
    keyState[key] = 1;
}

/* key（0x0 ～ 0xF）松开操作, 键状态置 0 */
void keyRelease(int key) {
    keyState[key] = 0;
}