#include "opcode.h"

/* 调用 RCA 1802 程序, 这将不会被实现 */
void _0NNN(WORD opcode) {

}

/* 清空屏幕 */
void _00E0(WORD opcode) {
    memset(gfx, 0, sizeof(gfx));
    CF = 1;
}

/* 从子例程中返回，堆栈弹出该子例程被调用前PC的地址 */
void _00EE(WORD opcode) {
    PC = stackPop(&s);
}

/* PC 跳转到地址 NNN */
void _1NNN(WORD opcode) {
    PC = opcode & 0x0FFF;
}

/* 调用处于地址 NNN 处的子例程 */
void _2NNN(WORD opcode) {
    stackPush(&s, PC);
    PC = opcode & 0x0FFF;
}

/* 如果寄存器 X 的值等于 NN，则跳过下一条指令 */
void _3XNN(WORD opcode) {
    int vx = V[(opcode & 0x0F00) >> 8];
    int nn = opcode & 0x00FF;
    if (vx == nn) {
        PC += 2;
    }
}

/* 如果寄存器 X 的值不等于 NN，则跳过下一条指令 */
void _4XNN(WORD opcode) {
    int vx = V[(opcode & 0x0F00) >> 8];
    int nn = opcode & 0x00FF;
    if (vx != nn) {
        PC += 2;
    }
}

/* 如果寄存器 X 的值等于寄存器 Y 的值，则跳过下一条指令 */
void _5XY0(WORD opcode) {
    int vx = V[(opcode & 0x0F00) >> 8];
    int vy = V[(opcode & 0x00F0) >> 4];
    if (vx == vy) {
        PC += 2;
    }
}

/* VX = NN */
void _6XNN(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
}

/* VX += NN. 不考虑进位 */
void _7XNN(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
}

/* VX = VY */
void _8XY0(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
}

/* VX = VX | VY */
void _8XY1(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
}

/* VX = VX & VY */
void _8XY2(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
}

/* VX = VX ^ VY */
void _8XY3(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
}

/* VX += VY, 发生溢出则将 CF 置为 1，否则置为 0 */
void _8XY4(WORD opcode) {
    CF = 0;
    int value = V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4];
    if (value > 0xFF) {
        CF = 1;
    }

    V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
}

/* VX -= VY, set carry to 0 if borrow otherwise 1 */
void _8XY5(WORD opcode) {
    CF = 1;
    if (V[(opcode & 0x0F00) >> 8] < V[(opcode & 0x00F0) >> 4]) {
        CF = 0;
    }

    V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
}

/* VX = VX >> 1，将 CF 置为移位之前，寄存器 X 的最低有效位 */
void _8XY6(WORD opcode) {
    CF = V[(opcode & 0x0F00) >> 8] & 0x01;
    V[(opcode & 0x0F00) >> 8] >>= 1;
}

/* VX = VY - VX, set carry to 0 if borrow otherwise 1 */
void _8XY7(WORD opcode) {
    CF = 1;
    if (V[(opcode & 0x00F0) >> 4] < V[(opcode & 0x0F00) >> 8]) {
        CF = 0;
    }

    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
}

/* VX = VX << 1. set carry to the most significant bit of VX before the shift */
void _8XYE(WORD opcode) {
    CF = V[(opcode & 0x0F00) >> 8] & 0x80;
    V[(opcode & 0x0F00) >> 8] <<= 1;
}

/* Skip the next instruction if VX doesn't equal VY */
void _9XY0(WORD opcode) {
    if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) {
        PC += 2;
    }
}

/* 将地址寄存器置为 NNN，I = NNN */
void _ANNN(WORD opcode) {
    I = opcode & 0x0FFF;
}

/* PC = V0 + NNN */
void _BNNN(WORD opcode) {
    PC = V[0x0] + (opcode & 0x0FFF);
}

/* VX = rand([0, 255]) & NN */
void _CXNN(WORD opcode) {

    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);

    srand(tv.tv_usec);

    V[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
}

/* 将 RAM[I] ~ RAM[I + n] 的 n 行数据，绘制在屏幕的 (VX, VY) 坐标上 */
void _DXYN(WORD opcode) {

    int x = V[(opcode & 0x0F00) >> 8];
    int y = V[(opcode & 0x00F0) >> 4];
    int n = opcode & 0x000F;

    CF = 0;
    /* 绘制算法 */
    for (int yl = 0; yl < n; yl++) {
        for (int xl = 0; xl < 8; xl++) {
            BYTE pixel = RAM[I + yl];
            if ((pixel & (0x80 >> xl)) != 0) {
                /* 取余操作，以防止画面渲染溢出，保持在 64 x 32 的矩阵中 */
                if (gfx[(y + yl) % 32][(x + xl) % 64] == 1) {
                    CF = 1;
                }
                gfx[(y + yl) % 32][(x + xl) % 64] ^= 1;
            }
        }
    }

    /* 置绘图信号为 1，使render线程在 UI 上绘图 */
    needRenderSignal = 1;

}

/* 如果寄存器 X 的值指定的某个按键是被按下的状态，则跳过下一条指令 */
void _EX9E(WORD opcode) {
    if (keyState[V[(opcode & 0x0F00) >> 8]] == 1) {
        PC += 2;
    }
}

/* 如果寄存器 X 的值指定的某个按键是被松开的状态，则跳过下一条指令 */
void _EXA1(WORD opcode) {
    if (keyState[V[(opcode & 0x0F00) >> 8]] == 0) {
        PC += 2;
    }
}

/* 寄存器 X = delayTimer */
void _FX07(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] = delayTimer;
}

/* 等待用户按键（阻塞操作），然后存入寄存器 X 中 */
void _FX0A(WORD opcode) {
    keyBlockSignal = 1;
    while (keyBlockSignal);
    /* 等待event主线程，阻塞信号取消则从全局变量keycode获取值 */
    V[(opcode & 0x0F00) >> 8] = keyCode;
}

/* delayTimer = 寄存器 X */
void _FX15(WORD opcode) {
    delayTimer = V[(opcode & 0x0F00) >> 8];
}

/* beepTimer = 寄存器 X */
void _FX18(WORD opcode) {
    beepTimer = V[(opcode & 0x0F00) >> 8];
}

/* I += 寄存器 X */
void _FX1E(WORD opcode) {
    I += V[(opcode & 0x0F00) >> 8];
}

/* set I to the fontset address which is stored in VX */
void _FX29(WORD opcode) {
    I = V[(opcode & 0x0F00) >> 8] * 0x5;
}

/* BCD code of VX stored in RAM which to the I + 0 ~ I + 2 */
void _FX33(WORD opcode) {
    int value = V[(opcode & 0x0F00) >> 8];
    RAM[I] = value / 100;
    RAM[I + 1] = (value / 10) % 10;
    RAM[I + 2] = value % 10;
}

/* reg_dump([V0 ~ VX], &I), I += (X - 0) + 1 */
void _FX55(WORD opcode) {
    int x = (opcode & 0x0F00) >> 8;
    for (int i = 0; i <= x; i++) {
        RAM[I + i] = V[i];
    }

    I += (x + 1);
}

/* reg_load([V0 ~ VX], &I), I += (X - 0) + 1 */
void _FX65(WORD opcode) {
    int x = (opcode & 0x0F00) >> 8;
    for (int i = 0; i <= x; i++) {
        V[i] = RAM[I + i];
    }

    I += (x + 1);
}
