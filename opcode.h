#ifndef __OPCODE_H__
#define __OPCODE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

/* CHIP-8 标准操作码处理函数 */
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
