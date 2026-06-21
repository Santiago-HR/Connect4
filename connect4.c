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

// welcomeScreen: displays the Connect Four ASCII logo and game rules
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
    printf("\t   they have won the game!\n\n");
}

// playGame: sets up players, runs the main game loop until game over
void playGame(void)
{
    struct Player yellow;
    struct Player red;

    // Yellow always goes first
    int currentPlayer = YELLOW;

    char board[ROW][COL];

    // Set up yellow player
    printf("Player Yellow, please enter your name\n");
    scanf("%19s", yellow.playerName);
    yellow.playerNum = YELLOW;
    yellow.playChar  = 'Y';
    yellow.numDisc   = DISC;

    // Set up red player
    printf("Player Red, please enter your name\n");
    scanf("%19s", red.playerName);
    red.playerNum = RED;
    red.playChar  = 'R';
    red.numDisc   = DISC;

    printf("\n%s and %s, let's play Connect Four!\n\n", yellow.playerName, red.playerName);

    initializeBoard(board);
    displayBoard(board);

    // Game loop — continues until a win or all discs are used
    while (gameOver(board, yellow, red) == FALSE)
    {
        if (currentPlayer == YELLOW)
        {
            makeMove(&yellow, board);
            currentPlayer = RED;
        }
        else
        {
            makeMove(&red, board);
            currentPlayer = YELLOW;
        }

        displayStats(yellow);
        displayStats(red);
        displayBoard(board);
    }

    // Final stats and game over announcement
    displayStats(yellow);
    displayStats(red);
    displayGameOver(board, yellow, red);
}

// initializeBoard: fills every cell with a space character
void initializeBoard(char board[ROW][COL])
{
    for (int row = 0; row < ROW; row++)
        for (int col = 0; col < COL; col++)
            board[row][col] = SPACE;
}

// displayBoard: prints the current state of the 6x7 board
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
            printf(" %c |", board[row][col]);
        printf("\n");
    }

    printf("|-----------------------------------------|\n");
}

// makeMove: prompts the current player for a valid column and places their disc
void makeMove(struct Player *player, char board[ROW][COL])
{
    // BUG FIX: original buffer was char[2] — too small for input + null terminator
    // when user types more than 1 char. Using INPUT_BUF (10) prevents overflow.
    char move[INPUT_BUF];
    int valid = FALSE;

    while (valid == FALSE)
    {
        printf("%s, enter the column to place disc (e.g. B)\n", player->playerName);
        scanf("%9s", move);

        printf("%s, you entered %s\n\n", player->playerName, move);

        int length = (int)strlen(move);

        if (length != ONE || getMoveCol(move) == INVALID)
        {
            // BUG FIX: separated invalid-character/length message from full-column
            // message so user only sees one relevant error at a time
            printf("Invalid move, try again\n\n");
        }
        else if (isColFull(move, board) == TRUE)
        {
            // isColFull already prints "Column is full!" — no extra message needed
            printf("Invalid move, try again\n\n");
        }
        else
        {
            valid = TRUE;
            updateBoard(move, board, player);
        }
    }
}

// getMoveCol: converts a column letter (A-G, case-insensitive) to a 0-based index
// Returns INVALID (-1) if the letter is not a valid column
int getMoveCol(char move[INPUT_BUF])
{
    int colInt = INVALID;
    char cols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

    for (int col = 0; col < COL; col++)
    {
        if (toupper(move[ZERO]) == cols[col])
            colInt = col;
    }

    return colInt;
}

// displayStats: prints a player's current number, character, and disc count
void displayStats(struct Player player)
{
    printf("****** %s's Statistics ******\n", player.playerName);
    printf("Player number:    %d\n", player.playerNum);
    printf("Player character: %c\n", player.playChar);
    printf("Player discs:     %d\n\n", player.numDisc);
}

// isColFull: returns TRUE if every row in the chosen column is occupied
int isColFull(char move[INPUT_BUF], char board[ROW][COL])
{
    int count = 0;
    int col   = getMoveCol(move);

    for (int row = 0; row < ROW; row++)
        if (board[row][col] != SPACE)
            count++;

    if (count == ROW)
    {
        printf("\nColumn is full!\n");
        return TRUE;
    }

    return FALSE;
}

// updateBoard: places the player's disc in the lowest available row of the column
void updateBoard(char move[INPUT_BUF], char board[ROW][COL], struct Player *player)
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

// gameOver: returns TRUE if a player has won or all discs have been placed
int gameOver(char board[ROW][COL], struct Player yellow, struct Player red)
{
    // BUG FIX: check win FIRST, then disc count
    // Original order could declare the game over on a disc-exhaustion draw
    // even when the last move was actually a winning move
    if (checkWin(board) == TRUE)
        return TRUE;

    if (yellow.numDisc == ZERO || red.numDisc == ZERO)
        return TRUE;

    return FALSE;
}

// checkWin: returns TRUE if any four-in-a-row exists on the board
int checkWin(char board[ROW][COL])
{
    return (checkHorizontal(board) == TRUE ||
            checkVertical(board)   == TRUE ||
            checkDiagonal(board)   == TRUE) ? TRUE : FALSE;
}

// checkHorizontal: scans each row for four consecutive matching discs
int checkHorizontal(char board[ROW][COL])
{
    for (int row = 0; row < ROW; row++)
        for (int col = 0; col <= COL - 4; col++)
            if (board[row][col] != SPACE &&
                board[row][col] == board[row][col + 1] &&
                board[row][col] == board[row][col + 2] &&
                board[row][col] == board[row][col + 3])
                return TRUE;

    return FALSE;
}

// checkVertical: scans each column for four consecutive matching discs
int checkVertical(char board[ROW][COL])
{
    for (int col = 0; col < COL; col++)
        for (int row = 0; row <= ROW - 4; row++)
            if (board[row][col] != SPACE &&
                board[row][col] == board[row + 1][col] &&
                board[row][col] == board[row + 2][col] &&
                board[row][col] == board[row + 3][col])
                return TRUE;

    return FALSE;
}

// checkDiagonal: scans both diagonal directions for four consecutive matching discs
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
                return TRUE;

            // Bottom-left to top-right
            if (board[row + 3][col] != SPACE &&
                board[row + 3][col] == board[row + 2][col + 1] &&
                board[row + 3][col] == board[row + 1][col + 2] &&
                board[row + 3][col] == board[row][col + 3])
                return TRUE;
        }
    }
    return FALSE;
}

// displayGameOver: announces the winner or a draw at the end of the game
// BUG FIX: original printed a generic "GAME OVER" with no winner info
// Now detects who won (or if it's a draw) and announces accordingly
void displayGameOver(char board[ROW][COL], struct Player yellow, struct Player red)
{
    printf("\n****************************************\n");
    printf("************* GAME OVER ****************\n");
    printf("****************************************\n");

    if (checkWin(board) == TRUE)
    {
        // Determine winner by checking whose disc appears in a winning line
        // The last disc placed belonged to whoever just moved; check whose char won
        char winner = SPACE;

        // Scan horizontal
        for (int row = 0; row < ROW && winner == SPACE; row++)
            for (int col = 0; col <= COL - 4 && winner == SPACE; col++)
                if (board[row][col] != SPACE &&
                    board[row][col] == board[row][col+1] &&
                    board[row][col] == board[row][col+2] &&
                    board[row][col] == board[row][col+3])
                    winner = board[row][col];

        // Scan vertical
        for (int col = 0; col < COL && winner == SPACE; col++)
            for (int row = 0; row <= ROW - 4 && winner == SPACE; row++)
                if (board[row][col] != SPACE &&
                    board[row][col] == board[row+1][col] &&
                    board[row][col] == board[row+2][col] &&
                    board[row][col] == board[row+3][col])
                    winner = board[row][col];

        // Scan diagonal
        for (int row = 0; row <= ROW - 4 && winner == SPACE; row++)
            for (int col = 0; col <= COL - 4 && winner == SPACE; col++)
            {
                if (board[row][col] != SPACE &&
                    board[row][col] == board[row+1][col+1] &&
                    board[row][col] == board[row+2][col+2] &&
                    board[row][col] == board[row+3][col+3])
                    winner = board[row][col];

                if (board[row+3][col] != SPACE &&
                    board[row+3][col] == board[row+2][col+1] &&
                    board[row+3][col] == board[row+1][col+2] &&
                    board[row+3][col] == board[row][col+3])
                    winner = board[row+3][col];
            }

        if (winner == yellow.playChar)
            printf("🏆  %s (Yellow) wins! Congratulations!\n", yellow.playerName);
        else if (winner == red.playChar)
            printf("🏆  %s (Red) wins! Congratulations!\n", red.playerName);
    }
    else
    {
        // All discs placed with no winner
        printf("It's a draw! Well played by both sides.\n");
    }

    printf("****************************************\n\n");
}