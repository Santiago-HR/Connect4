# Connect Four (C) — Terminal Game

This repository contains a command-line implementation of the classic **Connect Four** game written in **C**.  
Two players (Yellow and Red) take turns dropping discs into a **6×7** grid until one player connects **four** in a row **horizontally, vertically, or diagonally**.

The project is split into two files:

- `connect4.c` — main program and all game logic
- `connect4.h` — constants, `Player` struct, and function prototypes

---

## 📁 File Layout

```text
.
├── connect4.c   # Game logic + main program
└── connect4.h   # Macros, struct definitions, function prototypes
🎮 How the Game Works
1) Startup & Rules
When the program starts, it calls:

welcomeScreen()
Prints an ASCII Connect Four title and displays the rules.

Then it calls:

playGame()
Runs the full game loop until the game ends.

🧩 Board Representation
The board is stored as a 2D character array:

c
Copy code
char board[ROW][COL];
Where:

ROW = 6

COL = 7

Empty spaces are stored as ' ' (SPACE)

The board is initialized by:

initializeBoard(board)
Fills the entire board with SPACE.

The board is displayed after important events by:

displayBoard(board)
Prints the board with column labels A through G.

👤 Player Representation
Players are stored using a struct Player:

c
Copy code
struct Player {
    int playerNum;
    char playerName[NAME];
    int numDisc;
    char playChar;
};
Yellow always starts (YELLOW = 1, playChar = 'Y')

Red is player 2 (RED = 2, playChar = 'R')

Each player starts with DISC = 21 discs

🔁 Turn Logic (Main Game Loop)
playGame() controls turns:

Prompts Yellow and Red for their names

Displays the empty board

Repeats turns until the game is over:

During each turn:

makeMove(&player, board)
Prompts the current player to choose a column.

After a move:

displayStats(yellow) and displayStats(red) show each player’s stats

displayBoard(board) prints the updated board

✅ Input Validation & Moves
Valid Input
Players choose a column using one letter:

Valid columns: A B C D E F G (case-insensitive)

Move handling is done by:

getMoveCol(move)
Converts the entered letter into a column index (0–6) or returns INVALID.

isColFull(move, board)
Prevents placing a disc into a full column.

updateBoard(move, board, player)
Drops the disc into the lowest available row in that column and decreases the player's disc count.

If the move is invalid, the user is re-prompted until a valid move is entered.

🏁 Win Detection & Game Over
Game Over Conditions
The game ends when:

A player runs out of discs, or

A win is detected by checkWin(board)

Win Checking
Win checking is handled by:

checkWin(board)
Returns TRUE if any of the following return TRUE:

checkHorizontal(board)

checkVertical(board)

checkDiagonal(board)

Diagonal detection checks both directions:

top-left → bottom-right

bottom-left → top-right

Game Over Output
When the game ends:

displayGameOver() prints a “GAME OVER” banner

Final player stats are printed

🛠 Build & Run
Compile:

bash
Copy code
gcc connect4.c -o connect4
Run:

bash
Copy code
./connect4
📌 Notes
The game runs in the terminal and uses standard input (scanf) for player moves.

The header file (connect4.h) defines all macros, the Player struct, and the function prototypes so connect4.c stays clean and organized.

Input expects names without spaces (since %s is used).

📄 What’s in Each File?
connect4.c
Contains:

main()

Board setup and rendering

Player turn system

Input handling + validation

Win checking (horizontal/vertical/diagonal)

Game over display

connect4.h
Contains:

Macro constants (board size, players, TRUE/FALSE, etc.)

struct Player definition

Function prototypes used by connect4.c