#ifndef CONNECTFOUR_H_INCLUDED
#define CONNECTFOUR_H_INCLUDED

/* ── Board dimensions ─────────────────────────────────────────── */
#define ROW  6
#define COL  7

/* ── Player identifiers ───────────────────────────────────────── */
#define YELLOW 1
#define RED    2

/* ── Numeric constants ────────────────────────────────────────── */
#define ZERO  0
#define ONE   1
#define TWO   2
#define FOUR  4
#define DISC  21        /* each player starts with 21 discs (6×7 / 2) */

/* ── Input buffer ─────────────────────────────────────────────── */
/* BUG FIX: original TWO (2) was too small — a 1-char input + null
   terminator already fills it, so any accidental 2-char input caused
   a buffer overflow in scanf.  10 bytes is plenty for safe reads.   */
#define INPUT_BUF 10

/* ── Other constants ──────────────────────────────────────────── */
#define NAME    20
#define SPACE   ' '
#define TRUE    1
#define FALSE   0
#define INVALID -1

/* ── Player structure ─────────────────────────────────────────── */
struct Player
{
    int  playerNum;
    char playerName[NAME];
    int  numDisc;
    char playChar;
};

/* ── Function prototypes ──────────────────────────────────────── */
void welcomeScreen(void);
void playGame(void);
void initializeBoard(char board[ROW][COL]);
void displayBoard(char board[ROW][COL]);
void makeMove(struct Player *player, char board[ROW][COL]);
int  getMoveCol(char move[INPUT_BUF]);
void displayStats(struct Player player);
int  isColFull(char move[INPUT_BUF], char board[ROW][COL]);
void updateBoard(char move[INPUT_BUF], char board[ROW][COL], struct Player *player);
int  gameOver(char board[ROW][COL], struct Player yellow, struct Player red);
int  checkWin(char board[ROW][COL]);
int  checkHorizontal(char board[ROW][COL]);
int  checkVertical(char board[ROW][COL]);
int  checkDiagonal(char board[ROW][COL]);

/* BUG FIX: displayGameOver now takes board + both players so it can
   identify the winner instead of just printing a generic banner.     */
void displayGameOver(char board[ROW][COL], struct Player yellow, struct Player red);

#endif /* CONNECTFOUR_H_INCLUDED */