/*
 * util.c - utilities for sudoku solver
 *
 * Bailey Forrest - baileycforrest@gmail.com 
 *
 */

#include "util.h"

board *newBoard(int bSize) {
    int total = bSize * bSize * bSize * bSize;

    board *b = malloc(sizeof(board));
    b->numbers = malloc(sizeof(int) * total);
    b->bSize = bSize;
    b->next = NULL;

    return b;
}

void freeBoard(board *board) {
    free(board->numbers);
    free(board);
}

void freeStack(stack *s) {
    board *next, *b = s->top;

    while(b) {
        next = b->next;
        freeBoard(b);
        b = next;
    }

    free(s);
}

// Push a board onto the stack
void push(stack *s, board *b) {
    b->next = s->top;
    s->top = b;
}

// Pop a board off the stack.  Returns NULL if stack is empty
board *pop(stack *s) {
    board *result = s->top;
    if(!result) return result;
    s->top = s->top->next;

    return result;
}

// Get value from coords (x, y).  Return NULL if out of bounds
inline int *getVal(board *b, int x, int y) {
    int bWidth = b->bSize * b->bSize;
    int idx = y * bWidth + x;
    if(idx >= bWidth * bWidth || idx < 0)
        return NULL;

    return b->numbers + idx;
}

board *copyBoard(board *b) {
    board *new = newBoard(b->bSize);
    int total = b->bSize * b->bSize * b->bSize * b->bSize;
    memcpy(new->numbers, b->numbers, sizeof(int) * total);

    return new;
}

void printBoard(board *b) {
    int bWidth = b->bSize * b->bSize;
    int *p = b->numbers;
    int x, y;
    for(y = 0; y < bWidth; y++) {
        for(x = 0; x < bWidth; x++) {
            printf("%d ", *(p++));
        }
        printf("\n");
    }

}
