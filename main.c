#include "main.h"

/* 初始化虚拟机 */
int initialize(int argc, char **argv) {

    /*
     * 参数配置
     * -f: 指定虚拟机主频，指令数/每秒（默认800Hz）
     * -d: 虚拟机运行过程的详细输出（用于调试）
     * -c: 颜色模式，light（0） 和 dark（1）
     * -p: 方格的像素大小，默认为10
     * -v: 显示虚拟机程序版本
     * -h: 显示帮助
     */

    /* 参数设置成默认值 */
    cfgDebug = DEFAULT_DEBUG_FLAG;
    cfgColorMode = DEFAULT_COLOR;
    cfgFreq = DEFAULT_FREQ;
    cfgPixelSize = DEFAULT_PIXEL_SIZE;

    /* 命令行参数处理 */
    int ch;
    opterr = 0;
    while ((ch = getopt(argc, argv, ":f:c:p:dvh")) != EOF) {
        switch (ch) {
            case 'f':
                cfgFreq = atoi(optarg);
                if (!cfgFreq) {
                    fprintf(stderr, "[ERROR] Illegal argument after option \"%c\".\n", ch);
                    return EXIT_FAILURE;
                }
                break;

            case 'c':
                if (strcmp(optarg, "light") == 0) {
                    cfgColorMode = 0;
                } else if (strcmp(optarg, "dark") == 0) {
                    cfgColorMode = 1;
                } else {
                    fprintf(stderr, "[ERROR] Illegal argument after option \"%c\".\n", ch);
                    return EXIT_FAILURE;
                }
                break;

            case 'p':
                cfgPixelSize = atoi(optarg);
                if (!cfgPixelSize) {
                    fprintf(stderr, "[ERROR] Illegal argument after option \"%c\".\n", ch);
                    return EXIT_FAILURE;
                }
                break;

            case 'd':
                cfgDebug = 1;
                break;

            case 'v':
                printf("Quick CHIP-8 Virtual Machine %s\n", VERSION);
                exit(EXIT_SUCCESS);

            case 'h':
                printf("Quick CHIP-8 Virtual Machine\n");
                printf("Usage: %s [-f <main-frequence>] [-c dark | light] [-p <pixel-size>] [-d] [-v] [-h] [filepath]\n\n",
                       argv[0]);
                printf("Options:\n\t-f: Set the main frequency while running. (default set to %dHz)\n",
                       DEFAULT_FREQ);
                printf("\t-d: Run virtual machine in debug mode. (default set to %d)\n", DEFAULT_DEBUG_FLAG);
                printf("\t-c: Set the render of theme to light or dark. (default set to %s)\n",
                       DEFAULT_COLOR == 1 ? "dark" : "light");
                printf("\t-p: Set the size of every pixel. (default set to %d)\n", DEFAULT_PIXEL_SIZE);
                printf("\t-v: Print version of the virtual machine.\n");
                printf("\t-h: Print help information.\n\n");
                printf("Filepath:\n\tThe path of a CHIP-8 binary file (ROM) which can be run on the virtual machine.\n");

                exit(EXIT_SUCCESS);

            default:
                fprintf(stderr,
                        ch == ':' ? "[ERROR] None argument after option \"%c\".\n" : "[ERROR] Illegal option \"%c\".\n",
                        optopt);
                return EXIT_FAILURE;
        }
    }

    /* 判定文件路径参数，若无文件路径参数，则返回 EXIT_FAILURE */
    if (argc == 1 || (programPath = (argv + optind)[0]) == (void *) 0) {
        printf("Quick CHIP-8 Virtual Machine\nUsage: %s [-f <main-frequence>] [-c dark | light] [-p <pixel-size>] [-d] [-v] [-h] [filepath]\n",
               argv[0]);
        return EXIT_FAILURE;
    }


    /* 延时定时器、声音定时器、地址寄存器置 0 */
    /* 程序计数器置为 0x200（512字节处），程序从此运行 */
    delayTimer = 0;
    beepTimer = 0;
    I = 0;
    PC = 0x200;

    /* 将屏幕数据、寄存器组（0x0 ～ 0xF）、RAM内存、键位状态集，全部置为 0 */
    memset(gfx, 0, sizeof(gfx));
    memset(V, 0, sizeof(V));
    memset(RAM, 0, sizeof(RAM));
    memset(keyState, 0, sizeof(keyState));

    /* 将字体集（16x5）装入（0x00 ～ 0x80）的RAM内存中 */
    memcpy(RAM, fontSet, 80);

    /* 信号量初始化 */
    needRenderSignal = 0;
    cycleSignal = 0;
    keyBlockSignal = 0;
    quitSignal = 0;

    /* 初始化堆栈 */
    stackInit(&s, 256);

    /* 以只读的二进制方式打开目标程序文件，打开错误则返回 EXIT_FAILURE */
    FILE *in;
    if ((in = fopen(programPath, "rb")) == (void *) 0) {
        fprintf(stderr, "[ERROR] Can not load the binary file!\n");
        return EXIT_FAILURE;
    }

    /* 从RAM内存地址0x200开始，装入二进制的程序文件 */
    fread(&RAM[0x200], 0xfff, 1, in);

    /* 关闭文件句柄 */
    fclose(in);

    /* SDL 初始化 */
    SDL_Init(SDL_INIT_VIDEO);

    /* 创建 SDL 窗口 */
    window = SDL_CreateWindow("Quick CHIP-8 Virtual Machine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              64 * cfgPixelSize, 32 * cfgPixelSize,
                              SDL_WINDOW_SHOWN);
    /* 创建 SDL Renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    /* 清空 SDL 矩形 */
    memset(box, 0, sizeof(box));

    /* 调试线程、内核线程、定时器线程、绘图渲染线程 */
    debugThread = SDL_CreateThread((SDL_ThreadFunction) debugThreadProc, NULL, NULL);
    kernelThread = SDL_CreateThread((SDL_ThreadFunction) kernelThreadProc, NULL, NULL);
    timerThread = SDL_CreateThread((SDL_ThreadFunction) timerThreadProc, NULL, NULL);
    renderThread = SDL_CreateThread((SDL_ThreadFunction) renderThreadProc, NULL, NULL);

    /* 主线程（事件处理）*/
    mainLoop();

    return EXIT_SUCCESS;
}

/* Ctrl-C 中断处理 */
void terminate() {
    finalize();
    raise(SIGKILL);
}

void quit(int exitCode) {
    finalize();
    exit(exitCode);
}

/* 虚拟机退出前的资源释放处理 */
void finalize() {
    /* 释放其他线程 */
    SDL_DetachThread(renderThread);
    SDL_DetachThread(timerThread);
    SDL_DetachThread(kernelThread);
    SDL_DetachThread(debugThread);

    /* 销毁Renderer、销毁窗口、退出SDL */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    /* 释放堆栈 */
    stackFree(&s);
}

void mainLoop() {

    /* 置退出信号为 0 */
    quitSignal = 0;
    /* 若退出信号为 1 则跳出循环 */
    while (!quitSignal) {
        /* 刷新事件队列 */
        SDL_FlushEvent(SDL_KEYUP);
        SDL_FlushEvent(SDL_KEYDOWN);

        while (SDL_PollEvent(&event))   /* 从队列里取出事件，直到队列清空 */
        {
            switch (event.type) /* 判断事件类型 */
            {
                /* 若用户退出，则置退出信号为 1 */
                case SDL_QUIT:
                    quitSignal = 1;
                    quit(EXIT_SUCCESS);
                    /* 用户按下键，执行对应的按下键处理 */
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
                    /* 用户松开键，执行对应的松开键处理；
                     * 如果按键阻塞信号为阻塞，则取消按键阻塞
                     * 实现等待用户输入按键的操作（阻塞操作）
                     */
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

int main(int argc, char **argv) {

    /* SIGINT 中断处理，使用quit()函数 */
    signal(SIGINT, terminate);

    if (initialize(argc, argv) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    quit(EXIT_SUCCESS);

    return 0;
}