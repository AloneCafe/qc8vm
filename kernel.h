#ifndef __KERNEL_H__
#define __KERNEL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <zconf.h>
#include <SDL2/SDL.h>
#include "stack.h"

#define CF V[0xF]    // 进位标志寄存器

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef int SIGNAL;

BYTE RAM[0xFFF];    // 4KB内存
BYTE V[16]; // 16个8位通用寄存器
WORD I; // 16位地址寄存器
WORD PC;    // 程序计数器
BYTE delayTimer;    // 延时定时器
BYTE soundTimer;    // 声音定时器
stack s;    // 16位堆栈
BYTE gfx[32 + 10][64 + 10];   // 屏幕显示（64 x 32 分辨率），多 10 像素以防止栈溢出
BYTE keyState[16];  // 按键状态集
char *programPath;  // 程序文件路径

SDL_Thread *kernelThread;   // 内核线程
SDL_Thread *timerThread;    // 定时器线程
SDL_Thread *mainRenderThread;   // 图形渲染主线程
SDL_Thread *subRenderThread;   // 图形渲染子线程

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

SDL_Rect box[32 * 64];

SIGNAL needRenderSignal;    // 绘图信号，0为无行为信号，1为绘图信号
//SIGNAL doRendringSignal;    // 绘图中信号，0为未在绘图，1为正在绘图
SIGNAL quitSignal;  // 程序退出信号，0为运行信号，1为退出信号
SIGNAL keyBlockSignal;    // 按键阻塞信号，0为畅通信号，1为阻塞信号
int keyCode;    // CHIP-8键码，用于kernel线程和event线程的消息传递

// 4 字节高，5 字节宽，内置字符数据
static const BYTE fontSet[16][5] =
        {
                {0xF0, 0x90, 0x90, 0x90, 0xF0}, //0
                {0x20, 0x60, 0x20, 0x20, 0x70}, //1
                {0xF0, 0x10, 0xF0, 0x80, 0xF0}, //2
                {0xF0, 0x10, 0xF0, 0x10, 0xF0}, //3
                {0x90, 0x90, 0xF0, 0x10, 0x10}, //4
                {0xF0, 0x80, 0xF0, 0x10, 0xF0}, //5
                {0xF0, 0x80, 0xF0, 0x90, 0xF0}, //6
                {0xF0, 0x10, 0x20, 0x40, 0x40}, //7
                {0xF0, 0x90, 0xF0, 0x90, 0xF0}, //8
                {0xF0, 0x90, 0xF0, 0x10, 0xF0}, //9
                {0xF0, 0x90, 0xF0, 0x90, 0x90}, //A
                {0xE0, 0x90, 0xE0, 0x90, 0xE0}, //B
                {0xF0, 0x80, 0x80, 0x80, 0xF0}, //C
                {0xE0, 0x90, 0x90, 0x90, 0xE0}, //D
                {0xF0, 0x80, 0xF0, 0x80, 0xF0}, //E
                {0xF0, 0x80, 0xF0, 0x80, 0x80}  //F
        };

// 初始化虚拟机
int init(char **argv);

// 退出
void quit();

// 界面循环线程
void kernelLoopThread();

// 图形渲染主线程（刷新界面）
void mainRenderLoopThread();

// 定时器循环线程
void timerLoopThread();

// 事件循环线程
void mainLoopThread();

// 图形渲染子线程（绘图）
void subRenderLoopThread();

//执行操作码
int excuteOpcode(WORD opcode);

// 取下一个操作码
WORD getNextOpcode();

// 按下键操作
void keyPress(int key);

// 松开键操作
void keyRelease(int key);

// 振铃操作
void playBeep();

// 清屏操作
void clearScreen();

// CHIP-8 标准操作码处理函数
void _0NNN(WORD opcode);

void _00E0(WORD opcode);

void _00EE(WORD opcode);

void _1NNN(WORD opcode);

void _2NNN(WORD opcode);

void _3XNN(WORD opcode);

void _4XNN(WORD opcode);

void _5XY0(WORD opcode);

void _6XNN(WORD opcode);

void _7XNN(WORD opcode);

void _8XY0(WORD opcode);

void _8XY1(WORD opcode);

void _8XY2(WORD opcode);

void _8XY3(WORD opcode);

void _8XY4(WORD opcode);

void _8XY5(WORD opcode);

void _8XY6(WORD opcode);

void _8XY7(WORD opcode);

void _8XYE(WORD opcode);

void _9XY0(WORD opcode);

void _ANNN(WORD opcode);

void _BNNN(WORD opcode);

void _CXNN(WORD opcode);

void _DXYN(WORD opcode);

void _EX9E(WORD opcode);

void _EXA1(WORD opcode);

void _FX07(WORD opcode);

void _FX0A(WORD opcode);

void _FX15(WORD opcode);

void _FX18(WORD opcode);

void _FX1E(WORD opcode);

void _FX29(WORD opcode);

void _FX33(WORD opcode);

void _FX55(WORD opcode);

void _FX65(WORD opcode);

#ifdef __cplusplus
}
#endif

#endif
