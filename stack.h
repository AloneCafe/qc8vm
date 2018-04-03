#ifndef __STACK_H__
#define __STACK_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

void stackInit(stack *s, int capacity);

void stackClear(stack *s);

void stackFree(stack *s);

void stackPush(stack *s, WORD elem);

WORD stackPop(stack *s);

#ifdef __cplusplus
}
#endif

#endif
