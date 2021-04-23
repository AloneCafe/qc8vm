#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <zconf.h>
#include <unistd.h>
#include <signal.h>
#include <SDL2/SDL.h>

/* 当前程序版本 */
#define VERSION "1.1.4"

/* 虚拟机默认参数常量 */
#define DEFAULT_FREQ 800
#define DEFAULT_COLOR 1 /* dark: 1, light: 0 */
#define DEFAULT_PIXEL_SIZE 10
#define DEFAULT_DEBUG_FLAG 0

#define CF V[0xF]    /* 进位标志寄存器，第16个通用寄存器 */

/* 类型别名 */
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef int SIGNAL;

typedef struct stack {
    int capacity;   // 总容量
    int length; // 当前长度
    WORD *p;    // 栈
} stack;

/* 本地头文件包含 */
#include "stack.h"
#include "kernel.h"
#include "renderer.h"
#include "timer.h"
#include "keyboard.h"
#include "opcode.h"
#include "debug.h"
#include "main.h"

extern BYTE RAM[0xFFF];    /* 4KB内存 */
extern BYTE V[16]; /* 16个8位通用寄存器 */
extern WORD I; /* 16位地址寄存器 */
extern WORD PC;    /* 程序计数器 */
extern BYTE delayTimer;    /* 延时定时器 */
extern BYTE beepTimer;    /* 蜂鸣定时器 */
extern WORD opcode;    /* 操作码opcode */

/* 16位堆栈 */
extern stack s;
extern BYTE gfx[320][640];   /* 屏幕显示（64 x 32 分辨率），纵横各扩大10倍空间以防止栈溢出 */
extern BYTE keyState[16];  /* 按键状态集 */
extern char *programPath;  /* 程序文件路径 */

extern SDL_Thread *kernelThread;   /* 内核线程 */
extern SDL_Thread *timerThread;    /* 定时器线程 */
extern SDL_Thread *renderThread;   /* 图形渲染线程 */
extern SDL_Thread *debugThread;    /* 调试线程 */

extern SDL_Window *window; /* SDL 窗口 */
extern SDL_Renderer *renderer; /* SDL 渲染器 */
extern SDL_Event event;    /* SDL 事件 */

/* SDL矩形，用于绘图到render上 */
extern SDL_Rect box[32 * 64];

extern SIGNAL needRenderSignal;    /* 绘图信号，0为保持，1为绘图 */
extern SIGNAL cycleSignal; /* 指令周期信号，1为周期完成 */
extern SIGNAL quitSignal;  /* 程序退出信号，0为运行，1为退出 */
extern SIGNAL keyBlockSignal;    /* 按键阻塞信号，0为畅通，1为阻塞 */

extern int keyCode;    /* CHIP-8键码，用于kernel线程和event线程的消息传递 */

/* 一些设置变量（调试模式、颜色、主频、像素大小），用于接收命令行参数，控制程序行为 */
extern int cfgDebug;
extern int cfgColorMode;
extern int cfgFreq;
extern int cfgPixelSize;

/* 4 字节高，5 字节宽，内置字符数据 */
extern const BYTE fontSet[16][5];

#endif
