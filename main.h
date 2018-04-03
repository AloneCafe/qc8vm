#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

/* 初始化虚拟机 */
int init(int argc, char **argv);

/* 退出 */
void quit();

/* 事件循环线程 */
void mainLoopThread();

#ifdef __cplusplus
}
#endif

#endif
