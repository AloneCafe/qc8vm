#include "renderer.h"

/* 图形渲染线程 */
void renderThreadProc() {
    /* 大循环 */
    while (1) {
        /* 令屏幕刷新频率保持在 60Hz 左右 */
        usleep(16000);
        /* 屏幕绘图信号为 1 时，启动屏幕绘图 */
        if (needRenderSignal == 1) {

            /* 背景颜色设置 */
            if (cfgColorMode == 1)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            else
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            /* 清除 renderer */
            SDL_RenderClear(renderer);

            /* 清空 SDL 矩形数据 */
            memset(box, 0, sizeof(box));

            int i, j;
            for (i = 0; i < 320; i++) {
                for (j = 0; j < 640; j++) {
                    if (gfx[i][j] == 1) {
                        /* 将gfx存放的像素排列，转换成 SDL 矩形数组（x，y：坐标、w，h：宽高） */
                        box[i * 64 + j].x = j * cfgPixelSize;
                        box[i * 64 + j].y = i * cfgPixelSize;
                        box[i * 64 + j].w = cfgPixelSize;
                        box[i * 64 + j].h = cfgPixelSize;
                    }
                }
            }

            /* 前景颜色设置 */
            if (cfgColorMode == 1)
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

            /* 填充、渲染 SDL 矩形到 renderer 上 */
            SDL_RenderFillRects(renderer, box, 64 * 32);

            /* 将 renderer 显示到 UI 上 */
            SDL_RenderPresent(renderer);

            /* 关闭屏幕绘图信号 */
            needRenderSignal = 0;
        }
    }
}