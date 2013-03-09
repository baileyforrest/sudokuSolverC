/*
 * util.h
 *
 * utilities for sudoku solver
 *
 */

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Boards which are also linked list nodes
typedef struct board {
    int *numbers;
    int bSize;
    struct board *next;
} board;

typedef struct stack {
    board *top;
} stack;



board *newBoard(int bSize);
void freeBoard(board *b);
void freeStack(stack *s);
void push(stack *s, board *b);
board *pop(stack *s);
int *getVal(board *b, int x, int y);
board *copyBoard(board* b);
void printBoard(board *b);


#endif
