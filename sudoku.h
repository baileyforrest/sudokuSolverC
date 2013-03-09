/*
 * sudoku.h
 *
 * Bailey Forrest - baileycforrest@gmail.com
 *
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "util.h"

#define DEFAULT_SIZE 3

bool solve(stack *s, int bSize);
bool isConflict(board *b, int x, int y);
bool isRowConf(board *b, int x, int y);
bool isColConf(board *b, int x, int y);
bool isSubGridConf(board *b, int x, int y);

void printResults(stack *s, bool result);


#endif
