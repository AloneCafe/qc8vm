#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

/* 按下键操作 */
void keyPress(int key);

/* 松开键操作 */
void keyRelease(int key);

#ifdef __cplusplus
}
#endif

#endif
