/*
 * sudoku.c - sudoku solver with backtracking
 *
 * Bailey Forrest - baileycforrest@gmail.com
 *
 */

#include "sudoku.h"

static const char* usage = "Usage: %s [-h] [-s] <subgrid size> <input file>\n";
static const char* fileError = "Error opening file %s\n";

int main(int argc, char** argv) {
    int bSize; // Size of a sub-grid
    int totalNum; // total number of elements
    FILE *inFile;

    int opt;

    bSize = 0;
    while((opt = getopt(argc, argv, "hs:")) != -1) {
        switch(opt) {
        case 'h':
            printf(usage, argv[0]);
            exit(0);
            break;
        case 's':
            if((bSize = atoi(optarg)) <= 0) {
                fprintf(stderr, "Invalid sub block size\n");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            fprintf(stderr, usage, argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }

    if(!bSize) bSize = DEFAULT_SIZE;

    if(argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        fprintf(stderr, usage, argv[0]);
        exit(EXIT_FAILURE);
    }
    

    if((inFile = fopen(argv[argc - 1], "r")) == NULL)
    {
        fprintf(stderr, fileError, argv[1]);
        fprintf(stderr, usage, argv[0]);
        exit(EXIT_FAILURE);
    }

    totalNum = bSize * bSize * bSize * bSize; // total number of numbers

    stack *s = malloc(sizeof(stack));
    s->top = NULL;

    board *b = newBoard(bSize);

    int input;
    int cnt = 0;
    int *p = b->numbers;

    do {
        if(fscanf(inFile, "%d", &input) != 1)
            break;

        *p = input;
        p++;
        if(++cnt > totalNum) {
            fprintf(stderr, "Too many numbers in input file\n");
            exit(EXIT_FAILURE);
            printf("%d\n", cnt);
        }
    } while(!feof(inFile));

    if(cnt < totalNum) {
        fprintf(stderr, "Not enough numbers in input file\n");
        exit(EXIT_FAILURE);
    }

    printf("Solving:\n");
    printBoard(b);
    printf("\n");

    push(s, b);
    
    bool results = solve(s, bSize);

    printResults(s, results);

    freeStack(s);
    fclose(inFile);

    return 0;
}

// Attempt to solve sudoku puzzle on the stack.  Returns true if success,
// false if failure
bool solve(stack *s, int bSize) {
    int bWidth = bSize * bSize;
    int x, y, testVal;
    board *b = s->top;

    for(y = 0; y < bWidth; y++) {
        for(x = 0; x < bWidth; x++) {
            if((*getVal(b, x, y))) {
                continue; // skip over covered squares
            }
            board *cpy = copyBoard(b);
            int *val = getVal(cpy, x, y);
            push(s, cpy);
            for(testVal = 1; testVal <= bWidth; testVal++) {
                *val = testVal;
                if(isConflict(cpy, x, y)) // Invalid partial solution, continue
                   continue;
                else {
                    if(solve(s, bSize))
                        return true;
                }
            }
            pop(s);
            freeBoard(cpy);
            return false; // Tried all numbers in a square, no solutions
        }
    }
    return true; // Completed a valid board
}

// Returns if the value at (x, y) causes a conflict
bool isConflict(board *b, int x, int y) {
    return isRowConf(b, x, y) || isColConf(b, x, y) || isSubGridConf(b, x, y);
}

// Check if position in question causes a row conflict
bool isRowConf(board *b, int x, int y) {
    int bWidth = b->bSize * b->bSize;
    bool *seen = calloc(bWidth + 1, sizeof(int));
    int val;
    
    // Check non zero (nonempty) values in a row, marking them.
    // If found twice, a there is a conflict 
    int tx;
    for(tx = 0; tx < bWidth; tx++)
    {
        val = *getVal(b, tx, y);
        if(val) {
            if(seen[val]) {
                free(seen);
                return true;
            }
            seen[val] = true;
        }
    }

    free(seen);
    return false;
}

// Check if position in question causes a row conflict
bool isColConf(board *b, int x, int y) {
    int bWidth = b->bSize * b->bSize;
    bool *seen = calloc(bWidth + 1, sizeof(bool));
    int val;
    
    // Check non zero (nonempty) values in a col, marking them.
    // If found twice, a there is a conflict 
    int ty;
    for(ty = 0; ty < bWidth; ty++)
    {
        val = *getVal(b, x, ty);
        if(val) {
            if(seen[val]) {
                free(seen);
                return true;
            }
            seen[val] = true;
        }
    }

    free(seen);
    return false;
}


bool isSubGridConf(board *b, int x, int y) {
    int bSize = b->bSize;
    int blockX = x - x % bSize;
    int blockY = y - y % bSize;

    bool *seen = calloc(bSize * bSize + 1, sizeof(bool));

    int tx, ty;
    for(tx = blockX; tx < blockX + bSize; tx++)
        for(ty = blockY; ty < blockY + bSize; ty++) {
            int val = *getVal(b, tx, ty);
            if(val) {
                if(seen[val]) {
                    free(seen);
                    return true;
                }
                seen[val] = true;
            }            
        }
            
    free(seen);
    return false;
}

void printResults(stack *s, bool result) {
    if(!result) {
        printf("No solutions found!\n");
        return;
    }

    board *b = s->top;
    printf("Result:\n");
    printBoard(b);
}
