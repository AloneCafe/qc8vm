#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

/* 初始化虚拟机 */
int initialize(int argc, char **argv);

/* Ctrl-C 中断处理 */
void terminate();

/* 退出程序 */
void quit(int exitCode);

/* 虚拟机退出前的资源释放处理 */
void finalize();

/* 事件循环线程 */
void mainLoop();

#ifdef __cplusplus
}
#endif

#endif
