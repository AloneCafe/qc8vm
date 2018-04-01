#include "stack.h"

void stackInit(stack *s, int capacity) {
    s->p = (uint16_t *) malloc(sizeof(uint16_t) * capacity);
    s->capacity = capacity;
    s->length = 0;
}

void stackClear(stack *s) {
    s->length = 0;
}

void stackFree(stack *s) {
    s->length = 0;
    s->capacity = 0;
    free(s->p);
}

void stackPush(stack *s, uint16_t elem) {
    if (s->length >= s->capacity) {
        fputs("stack overflow.\n", stderr);
        exit(1);
    }

    *(s->p + s->length) = elem;
    s->length++;
}

uint16_t stackPop(stack *s) {
    if (s->length <= 0) {
        fputs("stack overflow.\n", stderr);
        exit(1);
    }

    s->length--;
    return *(s->p + s->length);
}

uint16_t stackTop(stack *s) {
    if (s->length <= 0) {
        fputs("stack overflow.\n", stderr);
        exit(1);
    }

    return *(s->p + s->length - 1);
}