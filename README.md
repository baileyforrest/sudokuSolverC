sudokuSolverC
=============

Sudoku solver using backtracking.  Works for arbitrary size sudokus

Usage: ./sudoku [-h] [-s] <subgrid size> <input file>

<subgrid size> is the size of a subgrid (ie 3 in a standard 9x9 sudoku)

<input file> should have the correct amount of numbers, all in the correct
range (1 - <subgrid size> ^ 2).  Empty spaces are represented by zero.

