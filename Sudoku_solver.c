#include <stdio.h>

int isValid(int board[9][9], int row, int col, int num)
{
    // Check row
    for (int i = 0; i < 9; i++)
        if (board[row][i] == num)
            return 0;

    // Check column
    for (int j = 0; j < 9; j++)
        if (board[j][col] == num)
            return 0;

    // Check 3x3 subgrid
    int sRow = (row / 3) * 3;
    int sCol = (col / 3) * 3;
    for (int i = sRow; i < sRow + 3; i++)
        for (int j = sCol; j < sCol + 3; j++)
            if (board[i][j] == num)
                return 0;

    return 1; // valid
}

void printBoard(int board[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

int solveSudoku(int board[9][9], int row, int col)
{
    if (row == 9)
    {
        printBoard(board);
        return 1; // STOP after 1 solution
    }

    if (board[row][col] != 0)
    {
        if (col != 8)
            return solveSudoku(board, row, col + 1);
        else
            return solveSudoku(board, row + 1, 0);
    }

    for (int num = 1; num <= 9; num++)
    {
        if (isValid(board, row, col, num))
        {
            board[row][col] = num;

            int solved;
            if (col != 8)
                solved = solveSudoku(board, row, col + 1);
            else
                solved = solveSudoku(board, row + 1, 0);

            if (solved)
                return 1; // STOP completely

            board[row][col] = 0; // backtrack
        }
    }

    return 0; // no valid number found
}

int main()
{
    int board[9][9] = {
        {5, 3, 5, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},

        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},

        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    printf("\n\n SUDOKU SOLVER \n");
    printf("\nInput Sudoku:\n");
    printBoard(board);

    printf("Solved Sudoku:\n");
    if (solveSudoku(board, 0, 0) == 0)
        printf("No solution exists\n");
    return 0;
}
