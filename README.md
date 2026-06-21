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

A complete, fully playable Connect Four game running in the terminal. Two players compete head-to-head on a 6×7 grid — dropping colored discs into columns, stacking upward, and racing to connect four before the other player does.

```
|-------------------------------------|
|  A  |  B  |  C  |  D  |  E  |  F  |  G  |
|-------------------------------------|
|     |     |     |     |     |     |     |
|-------------------------------------|
|     |     |     |     |     |     |     |
|-------------------------------------|
|     |     |  Y  |     |     |     |     |
|-------------------------------------|
|     |  R  |  Y  |     |     |     |     |
|-------------------------------------|
|     |  R  |  Y  |  R  |     |     |     |
|-------------------------------------|
|  Y  |  R  |  Y  |  R  |     |     |     |
|-------------------------------------|

Karin, enter the column to place disc (e.g. B):
```

---

## Features

- 🎮 &nbsp;**Two-player local gameplay** — Yellow vs. Red, names entered at start
- 🪂 &nbsp;**Gravity physics** — discs fall to the lowest open row automatically
- 🚫 &nbsp;**Input validation** — only A–G accepted, re-prompts on bad input
- 📦 &nbsp;**Full-column detection** — blocks illegal moves with a clear message
- 🏆 &nbsp;**Win detection** — checks horizontal, vertical, and both diagonals after every move
- 📊 &nbsp;**Live stats** — player disc count and character displayed after each turn
- 🎨 &nbsp;**ASCII art welcome screen** with game rules on launch

---

## Build & Run

```bash
gcc -o connectfour connectfour.c
./connectfour
```

**Requirements:** GCC · Any Unix terminal or Windows with MinGW

---

## How It Works

Each turn runs through a clean pipeline:

```
Player input
    │
    ▼
makeMove() ──► validate length == 1
    │          validate char in {A-G}
    │          isColFull() == false
    │
    ▼
updateBoard() ──► scan column bottom-up for first empty row
    │             place Y or R
    │             decrement player's disc count
    ▼
gameOver() ──► numDiscs == 0?  ──► TRUE
    │          checkWin()?     ──► TRUE
    │          otherwise       ──► FALSE
    ▼
switch players → repeat
```

Invalid input loops back to the prompt silently — no crashes, no undefined behavior.

---

## Code Structure

```
connectfour.c
│
├── welcome()          ASCII art header + rules display
├── setupPlayers()     Name prompts, assign Y/R, init disc counts
├── playGame()         Main game loop — runs until gameOver() == TRUE
├── makeMove()         Input capture + 3-condition validation gate
├── isColFull()        Scans top row of column for vacancy
├── updateBoard()      Bottom-up column scan, places disc, updates struct
├── gameOver()         Evaluates disc count and win conditions
├── checkWin()         Four-in-a-row scan across all directions
└── printStats()       Formatted player statistics after each turn
```

---

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![2D Arrays](https://img.shields.io/badge/2D_Arrays-informational?style=flat-square)
![Structs](https://img.shields.io/badge/Structs-informational?style=flat-square)
![Game Loop](https://img.shields.io/badge/Game_Loop-Design-blueviolet?style=flat-square)
![Input Validation](https://img.shields.io/badge/Input_Validation-passing-success?style=flat-square)

*UCF COP 3223 Intro to Programming in C — Fall 2023*

</div>