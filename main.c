#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ntsid.h>
#include <time.h>


#define COLS 9
#define ROWS 9


void final(int **grid, int remain){
    int k, i, j;
    int max = 9;
    time_t tt;
    srand(time(&tt));
    for( k = 0; k < remain ; k++)
    {
        i = rand() % max;
        j = rand() % max;
        if( grid[i][j] != 0 ){
            grid[i][j] = 0;
        }
    }
}

int checkZeros(int **board){

    int zeroCount = 0;

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j] == 0){
                zeroCount++;
            }
        }
    }

    return zeroCount;
}


int hasConflict(int **board, int row, int col, int num){

    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;
    int i;

    for(i=0; i<9; ++i)
    {
        if (board[row][i] == num)
            return 0;
        if (board[i][col] == num)
            return 0;
        if (board[rowStart + (i%3)][colStart + (i/3)] == num)
            return 0;
    }
    return 1;
}

void hard(int **board, int holes){
    int i=0, j = 0, iterctr = 0, k;
    time_t tt;
    srand(time(&tt));

    for (k = 0; k < holes; k++)
    {
        if(i % 2 == 0)
            j = j + 2;
        else
            j = j - 2;
        if(j == 10){
            i = i + 1;
            j = j - 3;
        }
        if(j == 9){
            i = i + 1;
            j = j - 1;
        }
        if(j == -1){
            i = i + 1;
            j = j + 1;
        }
        if(j == -2){
            i = i + 1;
            j = j + 3;
        }
        if( i > 8){
            if(iterctr > 1)
                return;
            else{
                i = 0;
                j = 1;
                iterctr++;
            }

        }

        printf("Test Medium Level-------board[%d][%d]\n",i, j);
        if(board[i][j] == 0){
            k--;
            continue;
        }
        int temp = board[i][j];
        board[i][j] = 0;
        int num, count = 0;
        for( num = 1; num < 10; num++ )
        {
            if(hasConflict(board, i, j, num))
                count++;
        }

        if(count > 2){
            board[i][j] = temp;
            k--;
        }
        // Check the numbers in one box should be greater than or equal to 5 holes
        else{
            int x, cnt = 0, cnt1 = 0;
            for(x = 0; x < 9; x++)
            {
                if(board[i][x]) // Check the row if it has number, increasing the count
                    cnt++;
                if(board[x][j]) // Check the column if it has number, increasing the count
                    cnt1++;
            }
            if(cnt < 3 || cnt1 < 3){
                board[i][j] = temp;
                k--;
            }
            else
                board[i][j] = 0;
        }
    }
    return;
}


bool findEmptyLocation(int **board, int row, int col){
    for(int i=0; i < ROWS; i++){
        for(int j=0; j< COLS; j++){
            if(board[i][j] == 0){
                return true;
            }
        }
    }

    return false;
}


int solveSudoku(int **grid, int row, int col) // Depth-first Search
{
    int i;
    if(row<9 && col<9)
    {
        if(grid[row][col] != 0)
        {
            if((col+1)<9)
                return solveSudoku(grid, row, col + 1);
            else if((row+1)<9)
                return solveSudoku(grid, row + 1, 0);
            else
                return 1;
        }
        else
        {
            for(i=0; i<9; ++i)
            {
                if(hasConflict(grid, row, col, i+1))
                {
                    grid[row][col] = i+1;
                    if((col+1)<9)
                    {
                        if(solveSudoku(grid, row, col + 1))
                            return 1;
                        else
                            grid[row][col] = 0;
                    }
                    else if((row+1) < 9)
                    {
                        if(solveSudoku(grid, row + 1, 0))
                            return 1;
                        else
                            grid[row][col] = 0;
                    }
                    else
                        return 1;
                }
            }
        }
        return 0;
    }
    else return 1;
}

void generateEmptyBoard(int **board){
    int i, j;
    for (i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            board[i][j] = 0;
        }
    }
}

void permutation_row(int i, int j){

}

void permutation_col(int i, int j){

}


void generatePuzzle(int **board){

    int max = 9;
    time_t tt;
    srand(time(&tt));

    int k;
    for( k = 0; k < 12 ; k++ ){
        int i, j;
        i = rand() % max;
        j = rand() % max;
        if( !board[i][j] ){
            int num = rand() % max + 1;
            while(1) {
                if( hasConflict(board, i, j, num) )
                {
                    board[i][j] = num;
                    break;
                }
                else
                {
                    num = (num + 1)	% max;
                }
            }
        }
    }

}

void normal(int **board){
    int i, j, k;
    int max = 14;
    time_t tt;
    srand(time(&tt));

    int holes = 45 - (rand() % max);

    for(k = 0; k < holes; k++){
        i = rand() % 9;
        j = rand() % 9;

        if(board[i][j] == 0){
            i = (i + 1) % 9;
            j = (j + 1) % 9;
        }

        int temp = board[i][j];
        board[i][j] = 0;
        int num, count=0;
        for(num = 1; num < 10; ++num){
            if(hasConflict(board, i, j, num)){
                count++;
            }
        }

        if(count > 1){
            board[i][j] = temp;
            k--;
        } else {

            int x, cnt1=0, cnt2=0;
            for(x =0; x< 9; ++x){
                if(board[i][x])
                    cnt1++;
                if(board[x][j])
                    cnt2++;
            }

            if(cnt1 < 4 || cnt2 < 4){
                board[i][j] = temp;
                k--;
            }
            else
                board[i][j] = 0;
        }
    }
    return;
}

void easy(int **board){
    int i, j, k;
    int max = 9;
    time_t tt;
    srand(time(&tt));

    int holes = 31 - (rand() % max);

    for(k = 0; k < holes; ++k){
        i = rand() % max;
        j = rand() % max;

        if(board[i][j] == 0){
            k--;
            continue;
        }
        int temp = board[i][j];
        board[i][j] = 0;
        int num, count=0;
        for(num = 1; num < 10; ++num) {
            if (hasConflict(board, i, j, num)) {
                count++;
            }
        }

        if(count > 1){
            board[i][j] = temp;
            k--;
        } else {
            int x, cnt1=0, cnt2=0;
            for(x =0; x<9; ++x){
                if(board[i][x]){
                    cnt1++;
                }
                if(board[x][j]){
                    cnt2++;
                }
            }
            if(cnt1 < 5 || cnt2 < 5){
                board[i][j] = temp;
                k--;
            } else {
                board[i][j] = 0;
            }
        }
    }
    return;
}

void printBoard(int **board){
    int i, j;
//    printf("-----------------------\n");
    for(i = 0; i < ROWS; i++){
        if(i % 3 == 0){
            printf("-------------------------\n");
        }
        for(j = 0; j < COLS; j++){
            if( j % 3 == 0){
                printf("| ");
            }
            printf("%d ", board[i][j]);
        }
        printf("|\n");
    }
}

int main() {

    int i;
    int j;

    time_t tt;
    srand(time(&tt));

    int **board =(int **)malloc( ROWS * sizeof(int *));
    if(board == NULL){
        printf("\nError allocating board\n");
        exit(1);
    }


    for(i = 0; i < ROWS; i++){
        board[i] = malloc(COLS * sizeof(int));
    }

    if(board[i] - 1 == NULL){
        printf("\nError allocating board\n");
        exit(1);
    }

    generateEmptyBoard(board);

    generatePuzzle(board);

    printf("Before solved-------------");
    printBoard(board);

    printf("\n\n");
//    printBoard(board);
//    printf("\n\n");
    solveSudoku(board, 0, 0);

    int holes = 49 - rand() % 4;
//    hard(board, holes);
    easy(board);
//    printf("Before Final-----------\n\n");
    printBoard(board);
//    int zeros = checkZeros(board);
//    printf("\n\nZeros Before final: %d\n\n", zeros);
//    int remain = holes - zeros;
//    final(board, remain);
//    printf("\n\nZeros after final: %d", checkZeros(board));

//    printf("\n\nAfter Final\n\n");
//    printBoard(board);
//    solveSudoku(board, 0, 0);

//    printBoard(board);


    printf("\n\n--------This is the solved puzzle!!!--------\n\n");
    solveSudoku(board, 0, 0);
    printBoard(board);

    free(board);

//    printf("%d", 2%9);


    return EXIT_SUCCESS;
}