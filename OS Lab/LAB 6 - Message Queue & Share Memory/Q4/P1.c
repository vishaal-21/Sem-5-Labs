#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#define filepath "/home/student/Desktop/210905037_OS/Week6/Q4/P1.c"
#define SIZE 1024

typedef struct
{
    char board[3][3];
} Board;

void initialize_board(Board *board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board->board[i][i] = ' ';
        }
    }
}

void display_board(Board *board)
{
    printf(" %c | %c | %c\n", board->board[0][0], board->board[0][1], board->board[0][2]);
    printf("-------------\n");
    printf(" %c | %c | %c\n", board->board[1][0], board->board[1][1], board->board[1][2]);
    printf("-------------\n");
    printf(" %c | %c | %c\n", board->board[2][0], board->board[2][1], board->board[2][2]);
}

int check_win_conditions(Board *board)
{
    if (board->board[0][0] == board->board[1][0] && board->board[1][0] == board->board[2][0] ||
        board->board[0][1] == board->board[1][1] && board->board[1][1] == board->board[2][1] ||
        board->board[0][2] == board->board[1][2] && board->board[1][2] == board->board[2][2] ||
        board->board[0][0] == board->board[0][1] && board->board[0][1] == board->board[0][2] ||
        board->board[1][0] == board->board[1][1] && board->board[1][1] == board->board[1][2] ||
        board->board[2][0] == board->board[2][1] && board->board[2][1] == board->board[2][2] ||
        board->board[0][0] == board->board[1][1] && board->board[1][1] == board->board[2][2] ||
        board->board[0][2] == board->board[1][1] && board->board[1][1] == board->board[2][0])
    {
        return 1;
    }
    else
        return 0;
}

void main()
{
    key_t key = ftok(filepath, 'A');
    int shmflag = IPC_CREAT | 0666;
    int shmid = shmget(key, SIZE, shmflag);

    Board *shared_board = (Board *)shmat(shmid, NULL, 0);

    initialize_board(shared_board);
    int moves = 0;
    char currentPlayer='X';
    int row, col;

    while (1)
    {
        printf("Enter row and column number(0-2) : ");
        scanf("%d%d",&row,&col);

        if(row<0 || col<0 || row>2 || col>2)
            printf("Error! Enter in range\n");
        if (moves == 9)
        {
            system("clear");
            display_board(shared_board);
            printf("\nDraw\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    shmdt(shared_board);
}