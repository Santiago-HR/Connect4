#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "connect4.h"

// main function
int main(void)
{
    // call function welcomeScreen
    welcomeScreen();

    // call function playGame
    playGame();

    // program executed successfully
    return 0;
}

// welcomeScreen function displays the Connect Four logo and rules of the game
void welcomeScreen(void)
{
    printf(" CCCC  OOOO  N   N  N   N  EEEEE  CCCC  TTTTT  FFFFF  OOOO  U   U  RRRR \n");
    printf("C     O    O NN  N  NN  N  EE    C        T    F     O    O U   U  R   R\n");
    printf("C     O    O N N N  N N N  EEEE  C        T    FFF   O    O U   U  RRRR \n");
    printf("C     O    O N  NN  N  NN  EE    C        T    F     O    O U   U  R  R \n");
    printf(" CCCC  OOOO  N   N  N   N  EEEEE  CCCC    T    F     OOOO   UUU   R   R\n");
    printf("\n");

    printf("CONNECT FOUR GAME RULES\n\n");
    printf("\t1. The board is 6 rows and 7 columns.\n");
    printf("\t2. The player with the yellow discs goes first.\n");
    printf("\t3. Players drop 1 disc in the grid at a time.\n");
    printf("\t4. Players alternate turns.\n");
    printf("\t5. Once a player has four discs in a row vertically, horizontally or diagonally,\n");
    printf("\t   they have won the game!\n");
}

// function displayEmptyBoard displays a hardcoded version of a Connect Four board
void displayEmptyBoard(void)
{
    printf("|------------------------------------------\n");
    printf("| A | B | C | D | E | F | G |\n");
    printf("|------------------------------------------\n");
    printf("|------------------------------------------\n");
    printf("| | | | | | | |\n");
    printf("|------------------------------------------\n");
    printf("| | | | | | | |\n");
    printf("|------------------------------------------\n");
    printf("| | | | | | | |\n");
    printf("|------------------------------------------\n");
    printf("| | | | | | | |\n");
    printf("|------------------------------------------\n");
    printf("| | | | | | | |\n");
    printf("|------------------------------------------\n");
    printf("| | | | | | | |\n");
    printf("|------------------------------------------\n");
}

void playGame(void)
{
    // declare variable for each player as a struct
    struct Player yellow;
    struct Player red;

    // yellow (Y) always goes first
    int currentPlayer = YELLOW;
    int loop = ZERO;

    char board[ROW][COL]; // board[0][0] is the start of the 2D array

    // create struct for each player
    printf("Player Yellow, please enter your name\n");
    scanf("%s", yellow.playerName);
    yellow.playerNum = YELLOW;
    yellow.playChar = 'Y';
    yellow.numDisc  = DISC;

    printf("Player Red, please enter your name\n");
    scanf("%s", red.playerName);
    red.playerNum = RED;
    red.playChar = 'R';
    red.numDisc  = DISC;

    printf("%s and %s, let's play Connect Four!\n", yellow.playerName, red.playerName);

    // call function initializeBoard
    initializeBoard(board);

    // initial display before loop
    displayBoard(board);

    while (gameOver(board, yellow, red) == FALSE)
    {
        // switch players for each move
        if (currentPlayer == YELLOW)
        {
            makeMove(&yellow, board);
            currentPlayer = RED;
        }
        else if (currentPlayer == RED)
        {
            makeMove(&red, board);
            currentPlayer = YELLOW;
        }

        displayStats(yellow);
        displayStats(red);
        displayBoard(board);

        loop++;
    }

    displayStats(yellow);
    displayStats(red);
    displayGameOver();
}

void initializeBoard(char board[ROW][COL])
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COL; col++)
        {
            board[row][col] = SPACE;
        }
    }
}

void displayBoard(char board[ROW][COL])
{
    printf("|-----------------------------------------|\n");
    printf("| A | B | C | D | E | F | G |\n");
    printf("|-----------------------------------------|\n");

    for (int row = 0; row < ROW; row++)
    {
        printf("|-----------------------------------------|\n");
        printf("|");
        for (int col = 0; col < COL; col++)
        {
            printf(" %c |", board[row][col]);
        }
        printf("\n");
    }

    printf("|-----------------------------------------|\n");
}

void makeMove(struct Player *player, char board[ROW][COL])
{
    char move[TWO]; // e.g., "A"
    int valid = FALSE;

    while (valid == FALSE)
    {
        printf("%s, enter the column to place disc (e.g. B)\n", player->playerName);
        scanf("%s", move);

        printf("%s, you entered %s\n\n", player->playerName, move);

        int length = (int)strlen(move);

        if (length == ONE &&
            getMoveCol(move) != INVALID &&
            isColFull(move, board) == FALSE)
        {
            valid = TRUE;
            updateBoard(move, board, player);
        }
        else
        {
            valid = FALSE;
            printf("Invalid move, try again\n\n");
        }
    }
}

int getMoveCol(char move[TWO])
{
    int colInt = INVALID;

    // 0 1 2 3 4 5 6
    char cols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

    for (int col = 0; col < COL; col++)
    {
        if (toupper(move[ZERO]) == cols[col])
            colInt = col;
    }

    return colInt;
}

void displayStats(struct Player player)
{
    printf("****** %s's Statistics ******\n", player.playerName);
    printf("Player number: %d\n", player.playerNum);
    printf("Player character: %c\n", player.playChar);
    printf("Player discs: %d\n\n", player.numDisc);
}

int isColFull(char move[TWO], char board[ROW][COL])
{
    int full = FALSE;
    int count = 0;

    int col = getMoveCol(move);

    for (int row = 0; row < ROW; row++)
    {
        if (board[row][col] != SPACE)
            count++;
    }

    if (count == ROW)
    {
        full = TRUE;
        printf("\nColumn is full!\n");
    }
    else
    {
        full = FALSE;
    }

    return full;
}

void updateBoard(char move[TWO], char board[ROW][COL], struct Player *player)
{
    int col = getMoveCol(move);

    for (int row = (ROW - 1); row >= ZERO; row--)
    {
        if (board[row][col] == SPACE)
        {
            board[row][col] = player->playChar;
            player->numDisc--;
            break;
        }
    }
}

int gameOver(char board[ROW][COL], struct Player yellow, struct Player red)
{
    int over = FALSE;

    if (yellow.numDisc == ZERO || red.numDisc == ZERO)
        over = TRUE;
    else if (checkWin(board) == TRUE)
        over = TRUE;
    else
        over = FALSE;

    return over;
}

int checkWin(char board[ROW][COL])
{
    if (checkHorizontal(board) == TRUE ||
        checkVertical(board) == TRUE ||
        checkDiagonal(board) == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}

int checkHorizontal(char board[ROW][COL])
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col <= COL - 4; col++)
        {
            if (board[row][col] != SPACE &&
                board[row][col] == board[row][col + 1] &&
                board[row][col] == board[row][col + 2] &&
                board[row][col] == board[row][col + 3])
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int checkVertical(char board[ROW][COL])
{
    for (int col = 0; col < COL; col++)
    {
        for (int row = 0; row <= ROW - 4; row++)
        {
            if (board[row][col] != SPACE &&
                board[row][col] == board[row + 1][col] &&
                board[row][col] == board[row + 2][col] &&
                board[row][col] == board[row + 3][col])
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int checkDiagonal(char board[ROW][COL])
{
    for (int row = 0; row <= ROW - 4; row++)
    {
        for (int col = 0; col <= COL - 4; col++)
        {
            // Top-left to bottom-right
            if (board[row][col] != SPACE &&
                board[row][col] == board[row + 1][col + 1] &&
                board[row][col] == board[row + 2][col + 2] &&
                board[row][col] == board[row + 3][col + 3])
            {
                return TRUE;
            }

            // Bottom-left to top-right
            if (board[row + 3][col] != SPACE &&
                board[row + 3][col] == board[row + 2][col + 1] &&
                board[row + 3][col] == board[row + 1][col + 2] &&
                board[row + 3][col] == board[row][col + 3])
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void displayGameOver(void)
{
    printf("\n****************************************\n");
    printf("************* GAME OVER ****************\n");
    printf("****************************************\n");
    printf("****************************************\n");
}
