#include "stack.h"

void stackInit(stack *s, int capacity) {
    s->p = (WORD *) malloc(sizeof(WORD) * capacity);
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

void stackPush(stack *s, WORD elem) {
    if (s->length >= s->capacity) {
        fputs("stack overflow.\n", stderr);
        exit(1);
    }

    *(s->p + s->length) = elem;
    s->length++;
}

WORD stackPop(stack *s) {
    if (s->length <= 0) {
        fputs("stack overflow.\n", stderr);
        exit(1);
    }

    s->length--;
    return *(s->p + s->length);
}

WORD stackTop(stack *s) {
    if (s->length <= 0) {
        fputs("stack overflow.\n", stderr);
        exit(1);
    }

    return *(s->p + s->length - 1);
}