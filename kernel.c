#include "kernel.h"

/* 内核线程 */
void kernelThreadProc() {
    /* 大while循环 */
    while (1) {
        /* 将虚拟机运行频率控制在指定的Hz */
        usleep(1000000 / cfgFreq);

        /* 取指令 */
        WORD opcode = getNextOpcode();
        /* 执行操作码opcode，若执行失败，则执行quit()，结束程序 */
        if (executeOpcode(opcode) == EXIT_FAILURE) {
            quit(EXIT_FAILURE);
        }
    }
}

/* 执行操作码opcode */
int executeOpcode(WORD opcode) {
    /*
     * 从左到右
     * o1: 操作码opcode的第一位
     * o2: 操作码opcode的第二位
     * o3: 操作码opcode的第三位
     * o4: 操作码opcode的第四位
     * o3o4：操作码opcode的后两位
     */
    WORD o1 = (opcode & 0xF000) >> 12;
    WORD o2 = (opcode & 0x0F00) >> 8;
    /* WORD o3 = (opcode & 0x00F0) >> 4; */
    WORD o4 = opcode & 0x000F;
    WORD o3o4 = opcode & 0x00FF;

    /* 判断操作码类型，执行相应的原子操作（35个）*/
    switch (o1) {
        case 0x0:
            switch (o2) {
                case 0x0:
                    switch (o3o4) {
                        case 0xEE:
                            _00EE(opcode);
                            break;
                        case 0xE0:
                            _00E0(opcode);
                            break;
                    }
                    break;
                default:
                    _0NNN(opcode);
                    break;
            }
            break;
        case 0x1:
            _1NNN(opcode);
            break;
        case 0x2:
            _2NNN(opcode);
            break;
        case 0x3:
            _3XNN(opcode);
            break;
        case 0x4:
            _4XNN(opcode);
            break;
        case 0x5:
            _5XY0(opcode);
            break;
        case 0x6:
            _6XNN(opcode);
            break;
        case 0x7:
            _7XNN(opcode);
            break;
        case 0x8:
            switch (o4) {
                case 0x0:
                    _8XY0(opcode);
                    break;
                case 0x1:
                    _8XY1(opcode);
                    break;
                case 0x2:
                    _8XY2(opcode);
                    break;
                case 0x3:
                    _8XY3(opcode);
                    break;
                case 0x4:
                    _8XY4(opcode);
                    break;
                case 0x5:
                    _8XY5(opcode);
                    break;
                case 0x6:
                    _8XY6(opcode);
                    break;
                case 0x7:
                    _8XY7(opcode);
                    break;
                case 0xE:
                    _8XYE(opcode);
                    break;
            }
            break;
        case 0x9:
            _9XY0(opcode);
            break;
        case 0xA:
            _ANNN(opcode);
            break;
        case 0xB:
            _BNNN(opcode);
            break;
        case 0xC:
            _CXNN(opcode);
            break;
        case 0xD:
            _DXYN(opcode);
            break;
        case 0xE:
            switch (o3o4) {
                case 0x9E:
                    _EX9E(opcode);
                    break;
                case 0xA1:
                    _EXA1(opcode);
                    break;
            }
            break;
        case 0xF:
            switch (o3o4) {
                case 0x07:
                    _FX07(opcode);
                    break;
                case 0x0A:
                    _FX0A(opcode);
                    break;
                case 0x15:
                    _FX15(opcode);
                    break;
                case 0x18:
                    _FX18(opcode);
                    break;
                case 0x1E:
                    _FX1E(opcode);
                    break;
                case 0x29:
                    _FX29(opcode);
                    break;
                case 0x33:
                    _FX33(opcode);
                    break;
                case 0x55:
                    _FX55(opcode);
                    break;
                case 0x65:
                    _FX65(opcode);
                    break;
            }
            break;
        default:
            /* 未知操作码，报错提示，opcode执行失败 */
            fprintf(stderr, "[ERROR] Illegal Opcode: %x, the virtual machine halted!\n", opcode);
            quit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/* 取下一个操作码 */
WORD getNextOpcode() {
    /* 初值 0x0000 */
    WORD opcode = 0x0000;

    /* 将PC所在的RAM位置，取出高位BYTE */
    opcode = RAM[PC];

    /* 将opcode的高位左移一个BYTE */
    opcode <<= 8;

    /* 得到低位BYTE，与高位BYTE做或运算，得到整个WORD大小的opcode */
    opcode |= RAM[PC + 1];

    /* 程序计数器加2 */
    PC += 2;

    /* 返回操作码 opcode */
    return opcode;
}