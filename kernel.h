#ifndef __KERNEL_H__
#define __KERNEL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

/* 界面循环线程 */
void kernelThreadProc();

/* 执行操作码 */
int executeOpcode(WORD opcode);

/* 取下一个操作码 */
WORD getNextOpcode();

#ifdef __cplusplus
}
#endif

#endif
