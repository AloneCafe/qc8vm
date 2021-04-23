#include "common.h"

BYTE RAM[0xFFF];    /* 4KB内存 */
BYTE V[16]; /* 16个8位通用寄存器 */
WORD I; /* 16位地址寄存器 */
WORD PC;    /* 程序计数器 */
BYTE delayTimer;    /* 延时定时器 */
BYTE beepTimer;    /* 蜂鸣定时器 */
WORD opcode;    /* 操作码opcode */

/* 16位堆栈 */
stack s;
BYTE gfx[320][640];   /* 屏幕显示（64 x 32 分辨率），纵横各扩大10倍空间以防止栈溢出 */
BYTE keyState[16];  /* 按键状态集 */
char *programPath;  /* 程序文件路径 */

SDL_Thread *kernelThread;   /* 内核线程 */
SDL_Thread *timerThread;    /* 定时器线程 */
SDL_Thread *renderThread;   /* 图形渲染线程 */
SDL_Thread *debugThread;    /* 调试线程 */

SDL_Window *window; /* SDL 窗口 */
SDL_Renderer *renderer; /* SDL 渲染器 */
SDL_Event event;    /* SDL 事件 */

/* SDL矩形，用于绘图到render上 */
SDL_Rect box[32 * 64];

SIGNAL needRenderSignal;    /* 绘图信号，0为保持，1为绘图 */
SIGNAL cycleSignal; /* 指令周期信号，1为周期完成 */
SIGNAL quitSignal;  /* 程序退出信号，0为运行，1为退出 */
SIGNAL keyBlockSignal;    /* 按键阻塞信号，0为畅通，1为阻塞 */

int keyCode;    /* CHIP-8键码，用于kernel线程和event线程的消息传递 */

/* 一些设置变量（调试模式、颜色、主频、像素大小），用于接收命令行参数，控制程序行为 */
int cfgDebug;
int cfgColorMode;
int cfgFreq;
int cfgPixelSize;

/* 4 字节高，5 字节宽，内置字符数据 */
const BYTE fontSet[16][5] = {
        {0xF0, 0x90, 0x90, 0x90, 0xF0}, /* 0 */
        {0x20, 0x60, 0x20, 0x20, 0x70}, /* 1 */
        {0xF0, 0x10, 0xF0, 0x80, 0xF0}, /* 2 */
        {0xF0, 0x10, 0xF0, 0x10, 0xF0}, /* 3 */
        {0x90, 0x90, 0xF0, 0x10, 0x10}, /* 4 */
        {0xF0, 0x80, 0xF0, 0x10, 0xF0}, /* 5 */
        {0xF0, 0x80, 0xF0, 0x90, 0xF0}, /* 6 */
        {0xF0, 0x10, 0x20, 0x40, 0x40}, /* 7 */
        {0xF0, 0x90, 0xF0, 0x90, 0xF0}, /* 8 */
        {0xF0, 0x90, 0xF0, 0x10, 0xF0}, /* 9 */
        {0xF0, 0x90, 0xF0, 0x90, 0x90}, /* A */
        {0xE0, 0x90, 0xE0, 0x90, 0xE0}, /* B */
        {0xF0, 0x80, 0x80, 0x80, 0xF0}, /* C */
        {0xE0, 0x90, 0x90, 0x90, 0xE0}, /* D */
        {0xF0, 0x80, 0xF0, 0x80, 0xF0}, /* E */
        {0xF0, 0x80, 0xF0, 0x80, 0x80}  /* F */
};