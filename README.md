<div align="center">

# 🔴 Connect Four 🟡
### Terminal-based · Two Player · Written in C

<img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white"/>
<img src="https://img.shields.io/badge/Terminal-Game-black?style=for-the-badge&logo=gnometerminal&logoColor=white"/>
<img src="https://img.shields.io/badge/UCF-COP3223-BA9B37?style=for-the-badge&logo=academia&logoColor=white"/>
<img src="https://img.shields.io/badge/2_Player-Local-critical?style=for-the-badge&logo=twitch&logoColor=white"/>

<br/>

> *Drop your disc. Block your opponent. Get four in a row.*

</div>

---

## The Game

A complete, fully playable Connect Four game running in the terminal. Two players compete head-to-head on a 6×7 grid — dropping colored discs into columns, stacking upward by gravity, and racing to connect four before the other player does.

```
|-----------------------------------------|
| A | B | C | D | E | F | G |
|-----------------------------------------|
|-----------------------------------------|
|   |   |   |   |   |   |   |
|-----------------------------------------|
|   |   |   |   |   |   |   |
|-----------------------------------------|
|   |   |   |   |   |   |   |
|-----------------------------------------|
|   |   |   |   |   |   |   |
|-----------------------------------------|
| Y | R |   |   |   |   |   |
|-----------------------------------------|
| Y | R |   |   |   |   |   |
|-----------------------------------------|

Alice, enter the column to place disc (e.g. B):
```

---

## Features

- 🎮 &nbsp;**Two-player local gameplay** — Yellow vs. Red, names entered at start
- 🪂 &nbsp;**Gravity physics** — discs fall to the lowest open row automatically
- 🚫 &nbsp;**Input validation** — only A–G accepted, re-prompts on bad or multi-character input
- 📦 &nbsp;**Full-column detection** — blocks illegal moves with a clear message
- 🏆 &nbsp;**Win detection** — checks horizontal, vertical, and both diagonals after every move
- 🎉 &nbsp;**Winner announcement** — displays the winning player's name at game over
- 📊 &nbsp;**Live stats** — player disc count and character displayed after each turn
- 🎨 &nbsp;**ASCII art welcome screen** with game rules on launch

---

## Build & Run

```bash
gcc -o connect4 connect4.c
./connect4
```

**Requirements:** GCC · Any Unix terminal or Windows with MinGW

---

## How It Works

Each turn runs through a clean validation pipeline before anything touches the board:

```
Player input
    │
    ▼
makeMove() ──► length == 1?          no  ──► "Invalid move, try again"
    │          char in {A–G}?        no  ──► "Invalid move, try again"
    │          isColFull() == FALSE?  no  ──► "Column is full! Invalid move..."
    │
    ▼ yes to all
updateBoard() ──► scan column bottom-up for first empty row
    │             place Y or R at that row
    │             decrement player's disc count
    ▼
gameOver() ──► checkWin()?       ──► TRUE  (win takes priority)
    │          numDiscs == 0?    ──► TRUE  (draw — all discs placed)
    │          otherwise         ──► FALSE
    ▼
switch players → repeat
```

---

## Code Structure

```
connect4.h                  Macros, Player struct, all function prototypes
connect4.c
│
├── main()                  Entry point — calls welcomeScreen then playGame
├── welcomeScreen()         ASCII logo + rules display
├── playGame()              Player setup + main game loop
├── initializeBoard()       Fills board[6][7] with spaces
├── displayBoard()          Renders the current board state to terminal
├── makeMove()              Input loop with 3-stage validation
├── getMoveCol()            Maps letter A–G (case-insensitive) → column index
├── isColFull()             Counts filled rows in a column; returns TRUE if full
├── updateBoard()           Bottom-up column scan; places disc, decrements count
├── gameOver()              Checks win condition then disc exhaustion
├── checkWin()              Delegates to horizontal, vertical, diagonal checks
├── checkHorizontal()       Scans rows for 4 consecutive matching discs
├── checkVertical()         Scans columns for 4 consecutive matching discs
├── checkDiagonal()         Scans both diagonals for 4 consecutive matching discs
├── displayStats()          Prints player number, character, and disc count
└── displayGameOver()       Announces winner by name, or declares a draw
```

---

## Bugs Fixed

| # | Issue | Fix |
|---|-------|-----|
| 1 | `char move[2]` buffer overflow — multi-char input wrote past the array | Changed to `char move[INPUT_BUF]` (10 bytes); `scanf` limited with `%9s` |
| 2 | `scanf("%s", playerName)` with no width limit — names > 19 chars overflowed | Changed to `scanf("%19s", ...)` |
| 3 | When column was full, both `"Column is full!"` and `"Invalid move"` printed on the same path | Restructured `makeMove` with separate `if/else if/else` branches — one message per case |
| 4 | `gameOver` checked disc count before win — last disc placed as a winning move could be misidentified as a draw | Reordered: `checkWin` is evaluated first |
| 5 | `displayGameOver` printed a generic banner with no winner info | Now scans the board to identify the winning character, then prints the player's name |

---

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![2D Arrays](https://img.shields.io/badge/2D_Arrays-informational?style=flat-square)
![Structs](https://img.shields.io/badge/Structs-informational?style=flat-square)
![Game Loop](https://img.shields.io/badge/Game_Loop_Design-blueviolet?style=flat-square)
![Input Validation](https://img.shields.io/badge/Input_Validation-passing-success?style=flat-square)
![Win Detection](https://img.shields.io/badge/Win_Detection-All_Directions-orange?style=flat-square)

*UCF COP 3223 Intro to Programming in C — Fall 2023*

</div>