#include "debug.h"

void debugThreadProc() {
    while (cfgDebug) {
        if (cycleSignal == 0) {

            printf("Opcode: 0x%x PC: 0x%x I: 0x%x DT: %d BT: %d\n", opcode, PC, I, delayTimer, beepTimer);
            printf("V[0x0 ~ 0xF]: |");
            int i;
            for (i = 0; i < 16; i++) {
                printf("0x%x|", V[i]);
            }
            printf("\n\n");

            cycleSignal = 1;
        }
    }
}