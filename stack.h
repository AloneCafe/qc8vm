#ifndef __STACK_H__
#define __STACK_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct stack {
    int capacity;   // 总容量
    int length; // 当前长度
    uint16_t *p;    // 栈
} stack;

void stackInit(stack *s, int capacity);

void stackClear(stack *s);

void stackFree(stack *s);

void stackPush(stack *s, uint16_t elem);

uint16_t stackPop(stack *s);

uint16_t stackTop(stack *s);


#endif
