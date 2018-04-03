#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

/* 定时器循环线程 */
void timerThreadProc();

/* 振铃操作 */
void playBeep();

#ifdef __cplusplus
}
#endif

#endif
