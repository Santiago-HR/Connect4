#ifndef CONNECTFOUR_H_INCLUDED
#define CONNECTFOUR_H_INCLUDED

#define NAME 20
#define YELLOW 1
#define RED 2
#define ZERO 0
#define FOUR 4
#define ROW 6
#define COL 7
#define ONE 1
#define TWO 2
#define SPACE ' '
#define TRUE 1
#define FALSE 0
#define INVALID -1
#define DISC 21

struct Player
{
    int playerNum;
    char playerName[NAME];
    int numDisc;
    char playChar;
};

void welcomeScreen ();
void displayEmptyBoard();
void playGame();
void initializeBoard(char board[ROW][COL]);
void displayBoard(char board[ROW][COL]);
void makeMove(struct Player *player, char board[ROW][COL]);
int getMoveCol(char move[TWO]);
void displayStats(struct Player player);

int isColFull(char move[TWO], char board[ROW][COL]);
void updateBoard(char move[TWO], char board[ROW][COL], struct Player *player);
int gameOver(char board[ROW][COL], struct Player yellow, struct Player red);
int checkWin(char board[ROW][COL]);

int checkDiagonal(char board[ROW][COL]);
int checkVertical(char board[ROW][COL]);
int checkHorizontal(char board[ROW][COL]);

void displayGameOver();

#endif
