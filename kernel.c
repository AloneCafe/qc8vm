#include "kernel.h"

// 图形渲染子线程
void subRenderLoopThread() {
//    while(1) {
//
//    }
}

// 图形渲染主线程
void mainRenderLoopThread() {
    while (1) {
        usleep(16000);
        // 屏幕绘图信号为 1 时，启动屏幕绘图
        if (needRenderSignal == 1) {

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            memset(box, 0, sizeof(box));
            int i, j;
            for (i = 0; i < 32; i++) {
                for (j = 0; j < 64; j++) {
                    if (gfx[i][j] == 1) {
                        box[i * 64 + j].x = j * 10;
                        box[i * 64 + j].y = i * 10;
                        box[i * 64 + j].w = 10;
                        box[i * 64 + j].h = 10;
                    }
                }
            }

            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
            SDL_RenderFillRects(renderer, box, 64 * 32);
            SDL_RenderPresent(renderer);

            // 关闭屏幕绘图信号
            needRenderSignal = 0;
        }
    }
}

// 内核线程
void kernelLoopThread() {
    // 大while循环
    while (1) {
        usleep(1600);
        WORD opcode = getNextOpcode();
        // 执行操作码opcode，执行失败，返回 EXIT_FAILURE
        if (excuteOpcode(opcode) == EXIT_FAILURE) {
            quit();
        }
    }
}

// 60Hz 定时器循环线程
void timerLoopThread() {
    while (1) {
        usleep(16000);

        // 延时定时器，非 0 递减
        if (delayTimer > 0)
            delayTimer--;

        // 声音定时器，非 0 递减
        if (soundTimer > 0)
            soundTimer--;

        // 声音定时器，非 0 则报警
        if (soundTimer > 0)
            playBeep();
    }
}

void mainLoopThread() {
    quitSignal = 0;
    while (!quitSignal) {
        SDL_FlushEvent(SDL_KEYUP);
        SDL_FlushEvent(SDL_KEYDOWN);
        while (SDL_PollEvent(&event))   //从队列里取出事件
        {
            switch (event.type) // 判断事件类型
            {
                case SDL_QUIT:
                    quitSignal = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_1:
                            keyPress(0x1);
                            break;
                        case SDLK_2:
                            keyPress(0x2);
                            break;
                        case SDLK_3:
                            keyPress(0x3);
                            break;
                        case SDLK_4:
                            keyPress(0xC);
                            break;
                        case SDLK_q:
                            keyPress(0x4);
                            break;
                        case SDLK_w:
                            keyPress(0x5);
                            break;
                        case SDLK_e:
                            keyPress(0x6);
                            break;
                        case SDLK_r:
                            keyPress(0xD);
                            break;
                        case SDLK_a:
                            keyPress(0x7);
                            break;
                        case SDLK_s:
                            keyPress(0x8);
                            break;
                        case SDLK_d:
                            keyPress(0x9);
                            break;
                        case SDLK_f:
                            keyPress(0xE);
                            break;
                        case SDLK_z:
                            keyPress(0xA);
                            break;
                        case SDLK_x:
                            keyPress(0x0);
                            break;
                        case SDLK_c:
                            keyPress(0xB);
                            break;
                        case SDLK_v:
                            keyPress(0xF);
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_1:
                            keyCode = 0x1;
                            keyRelease(0x1);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_2:
                            keyCode = 0x2;
                            keyRelease(0x2);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_3:
                            keyCode = 0x3;
                            keyRelease(0x3);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_4:
                            keyCode = 0xC;
                            keyRelease(0xC);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_q:
                            keyCode = 0x4;
                            keyRelease(0x4);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_w:
                            keyCode = 0x5;
                            keyRelease(0x5);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_e:
                            keyCode = 0x6;
                            keyRelease(0x6);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_r:
                            keyCode = 0xD;
                            keyRelease(0xD);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_a:
                            keyCode = 0x7;
                            keyRelease(0x7);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_s:
                            keyCode = 0x8;
                            keyRelease(0x8);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_d:
                            keyCode = 0x9;
                            keyRelease(0x9);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_f:
                            keyCode = 0xE;
                            keyRelease(0xE);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_z:
                            keyCode = 0xA;
                            keyRelease(0xA);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_x:
                            keyCode = 0x0;
                            keyRelease(0x0);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_c:
                            keyCode = 0xB;
                            keyRelease(0xB);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;
                        case SDLK_v:
                            keyCode = 0xF;
                            keyRelease(0xF);
                            if (keyBlockSignal)
                                keyBlockSignal = 0;
                            break;

                    }
                    break;
            }
        }
    }
}

int excuteOpcode(WORD opcode) {
    // 从左到右
    // o1: 操作码opcode的第一位
    // o2: 操作码opcode的第二位
    // o3: 操作码opcode的第三位
    // o4: 操作码opcode的第四位
    // o3o4：操作码opcode的后两位
    WORD o1 = (opcode & 0xF000) >> 12;
    WORD o2 = (opcode & 0x0F00) >> 8;
    //WORD o3 = (opcode & 0x00F0) >> 4;
    WORD o4 = opcode & 0x000F;
    WORD o3o4 = opcode & 0x00FF;

    // 判断操作码类型
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
            // 未知操作码，报错提示。
            fprintf(stderr, "[ERROR] Illegal Opcode: %x", opcode);
    }


    return EXIT_SUCCESS;
}

// 取下一个操作码
WORD getNextOpcode() {
    // 初值 0x0000
    WORD opcode = 0x0000;

    // 将PC所在的RAM位置，取出高位BYTE
    opcode = RAM[PC];

    // 将opcode的高位左移一个BYTE
    opcode <<= 8;

    // 得到低位BYTE，与高位BYTE做或运算，得到整个WORD大小的opcode
    opcode |= RAM[PC + 1];

    // 程序计数器加2
    PC += 2;

    // 返回操作码 opcode
    return opcode;
}

// key（0x0 ～ 0xF）按下操作, 键状态置 1。
void keyPress(int key) {
    keyState[key] = 1;
}

// key（0x0 ～ 0xF）松开操作, 键状态置 0。
void keyRelease(int key) {
    keyState[key] = 0;
}

// 振铃操作
void playBeep() {
    //TODO: OpenAL call
}

void quit() {
    SDL_DetachThread(kernelThread);
    SDL_DetachThread(timerThread);
    SDL_DetachThread(mainRenderThread);
    //SDL_DetachThread(subRenderThread);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// 初始化虚拟机
int init(char **argv) {
    // 判定路径是否正确，为空则返回 EXIT_FAILURE
    if ((programPath = argv[1]) == (void *) 0) {
        printf("Quick CHIP-8 Virtual Machine\nUsage: %s <binary file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 延时定时器、声音定时器、地址寄存器置 0；
    // 程序计数器置为 0x200（512字节处），程序从此运行；
    delayTimer = 0;
    soundTimer = 0;
    I = 0;
    PC = 0x200;

    // 将屏幕数据、寄存器组（0x0 ～ 0xF）、RAM内存、键位状态集，全部置为 0；
    memset(gfx, 0, sizeof(gfx));
    memset(V, 0, sizeof(V));
    memset(RAM, 0, sizeof(RAM));
    memset(keyState, 0, sizeof(keyState));

    // 将字体集（16x5）装入（0x00 ～ 0x80）的RAM内存中
    memcpy(RAM, fontSet, 80);

    // 信号Flag初始化
    needRenderSignal = 0;
    //doRendringSignal = 0;
    keyBlockSignal = 0;
    quitSignal = 0;

    // 清空堆栈
    stackInit(&s, 256);

    // 以只读的二进制方式打开目标程序文件，打开错误则返回 EXIT_FAILURE
    FILE *in;
    if ((in = fopen(programPath, "rb")) == (void *) 0) {
        fprintf(stderr, "[ERROR] Can not load the program file!");
        return EXIT_FAILURE;
    }

    // 从RAM内存地址0x200开始，装入二进制的程序文件
    fread(&RAM[0x200], 0xfff, 1, in);

    // 关闭文件句柄
    fclose(in);

    // SDL 初始化
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Quick CHIP-8 Virtual Machine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320,
                              SDL_WINDOW_FOREIGN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    memset(box, 0, sizeof(box));

    kernelThread = SDL_CreateThread(kernelLoopThread, NULL, NULL);
    timerThread = SDL_CreateThread(timerLoopThread, NULL, NULL);
    mainRenderThread = SDL_CreateThread(mainRenderLoopThread, NULL, NULL);
    //subRenderThread = SDL_CreateThread(subRenderLoopThread, NULL, NULL);

    // 主线程（事件处理）
    mainLoopThread();

    return EXIT_SUCCESS;
}

// 调用 RCA 1802 程序, 这将不会被实现
void _0NNN(WORD opcode) {

}

// 清空屏幕
void _00E0(WORD opcode) {
    memset(gfx, 0, sizeof(gfx));
    CF = 1;
}

// 从子例程中返回，堆栈弹出该子例程被调用前PC的地址
void _00EE(WORD opcode) {
    PC = stackPop(&s);
}

// PC 跳转到地址 NNN
void _1NNN(WORD opcode) {
    PC = opcode & 0x0FFF;
}

// 调用处于地址 NNN 处的子例程
void _2NNN(WORD opcode) {
    stackPush(&s, PC);
    PC = opcode & 0x0FFF;
}

// 如果寄存器 X 的值等于 NN，则跳过下一条指令
void _3XNN(WORD opcode) {
    int vx = V[(opcode & 0x0F00) >> 8];
    int nn = opcode & 0x00FF;
    if (vx == nn) {
        PC += 2;
    }
}

// 如果寄存器 X 的值不等于 NN，则跳过下一条指令
void _4XNN(WORD opcode) {
    int vx = V[(opcode & 0x0F00) >> 8];
    int nn = opcode & 0x00FF;
    if (vx != nn) {
        PC += 2;
    }
}

// 如果寄存器 X 的值等于寄存器 Y 的值，则跳过下一条指令
void _5XY0(WORD opcode) {
    int vx = V[(opcode & 0x0F00) >> 8];
    int vy = V[(opcode & 0x00F0) >> 4];
    if (vx == vy) {
        PC += 2;
    }
}

// VX = NN
void _6XNN(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
}

// VX += NN. 不考虑进位
void _7XNN(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
}

// VX = VY
void _8XY0(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
}

// VX = VX | VY.
void _8XY1(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
}

// VX = VX & VY.
void _8XY2(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
}

// VX = VX ^ VY
void _8XY3(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
}

// VX += VY, 发生溢出则将 CF 置为 1，否则置为 0
void _8XY4(WORD opcode) {
    CF = 0;
    int value = V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4];
    if (value > 0xFF) {
        CF = 1;
    }

    V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
}

// VX -= VY, set carry to 0 if borrow otherwise 1.
void _8XY5(WORD opcode) {
    CF = 1;
    if (V[(opcode & 0x0F00) >> 8] < V[(opcode & 0x00F0) >> 4]) {
        CF = 0;
    }

    V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
}

// VX = VX >> 1，将 CF 置为移位之前，寄存器 X 的最低有效位
void _8XY6(WORD opcode) {
    CF = V[(opcode & 0x0F00) >> 8] & 0x01;
    V[(opcode & 0x0F00) >> 8] >>= 1;
}

// VX = VY - VX, set carry to 0 if borrow otherwise 1.
void _8XY7(WORD opcode) {
    CF = 1;
    if (V[(opcode & 0x00F0) >> 4] < V[(opcode & 0x0F00) >> 8]) {
        CF = 0;
    }

    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
}

// VX = VX << 1. set carry to the most significant bit of VX before the shift.
void _8XYE(WORD opcode) {
    CF = V[(opcode & 0x0F00) >> 8] & 0x80;
    V[(opcode & 0x0F00) >> 8] <<= 1;
}

// Skip the next instruction if VX doesn't equal VY.
void _9XY0(WORD opcode) {
    if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) {
        PC += 2;
    }
}

// 将地址寄存器置为 NNN，I = NNN
void _ANNN(WORD opcode) {
    I = opcode & 0x0FFF;
}

// PC = V0 + NNN
void _BNNN(WORD opcode) {
    PC = V[0x0] + (opcode & 0x0FFF);
}

// VX = rand([0, 255]) & NN
void _CXNN(WORD opcode) {

    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);

    srand(tv.tv_usec);

    V[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
}

// 将 RAM[I] ~ RAM[I + n] 的 n 行数据，绘制在屏幕的 (VX, VY) 坐标上。
void _DXYN(WORD opcode) {
    int x = V[(opcode & 0x0F00) >> 8];
    int y = V[(opcode & 0x00F0) >> 4];
    int n = opcode & 0x000F;

    CF = 0;
    for (int yl = 0; yl < n; yl++) {
        for (int xl = 0; xl < 8; xl++) {
            BYTE pixel = RAM[I + yl];
            if ((pixel & (0x80 >> xl)) != 0) {
                if (gfx[y + yl][x + xl] == 1) {
                    CF = 1;
                }

                gfx[y + yl][x + xl] ^= 1;
            }
        }
    }

    needRenderSignal = 1;

}

// 如果寄存器 X 的值指定的某个按键是被按下的状态，则跳过下一条指令
void _EX9E(WORD opcode) {
    if (keyState[V[(opcode & 0x0F00) >> 8]] == 1) {
        PC += 2;
    }
}

// 如果寄存器 X 的值指定的某个按键是被松开的状态，则跳过下一条指令
void _EXA1(WORD opcode) {
    if (keyState[V[(opcode & 0x0F00) >> 8]] == 0) {
        PC += 2;
    }
}

// 寄存器 X = delayTimer
void _FX07(WORD opcode) {
    V[(opcode & 0x0F00) >> 8] = delayTimer;
}

// 等待用户按键（阻塞操作），然后存入寄存器 X 中
void _FX0A(WORD opcode) {
    keyBlockSignal = 1;
    while (keyBlockSignal);
    // 等待event主线程，阻塞信号取消则从全局变量keycode获取值
    V[(opcode & 0x0F00) >> 8] = keyCode;
}

// delayTimer = 寄存器 X
void _FX15(WORD opcode) {
    delayTimer = V[(opcode & 0x0F00) >> 8];
}

// soundTimer = 寄存器 X
void _FX18(WORD opcode) {
    soundTimer = V[(opcode & 0x0F00) >> 8];
}

// I += 寄存器 X
void _FX1E(WORD opcode) {
    I += V[(opcode & 0x0F00) >> 8];
}

// set I to the fontset address which is stored in VX.
void _FX29(WORD opcode) {
    I = V[(opcode & 0x0F00) >> 8] * 0x5;
}

// BCD code of VX stored in RAM which to the I + 0 ~ I + 2.
void _FX33(WORD opcode) {
    int value = V[(opcode & 0x0F00) >> 8];
    RAM[I] = value / 100;
    RAM[I + 1] = (value / 10) % 10;
    RAM[I + 2] = value % 10;
}

// reg_dump([V0 ~ VX], &I), I += (X - 0) + 1.
void _FX55(WORD opcode) {
    int x = (opcode & 0x0F00) >> 8;
    for (int i = 0; i <= x; i++) {
        RAM[I + i] = V[i];
    }

    I += (x + 1);
}

// reg_load([V0 ~ VX], &I), I += (X - 0) + 1.
void _FX65(WORD opcode) {
    int x = (opcode & 0x0F00) >> 8;
    for (int i = 0; i <= x; i++) {
        V[i] = RAM[I + i];
    }

    I += (x + 1);
}
