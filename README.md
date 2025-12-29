# Connect Four (C Programming Project)

**University of Central Florida**  
**COP 3223 – Intro to Programming in C**  
**Assignment 7**

This project implements a fully functional **Connect Four** game in the C programming language.  
The program recreates the classic two-player board game using arrays, structures, user-defined functions, and header files.

---

## 📅 Due Dates & Grading

- **Sunday, December 3, 2023** — max **100**
- **Monday, December 4, 2023** — max **90**
- **Tuesday, December 5, 2023** — max **80**
- **Wednesday, December 6, 2023** — max **70**

---

## 📦 Deliverables

The following files must be submitted:

```text
connectfour.c
connectfour.h
🎮 Project Description
The goal of this assignment is to generate a Connect Four game board and replicate the full gameplay experience, including:

Game setup

Player turns

Valid and invalid moves

Win detection

Game over display

The project emphasizes fundamental C programming concepts such as:

Primitive data types

Arrays

Structures

User-defined functions

Header files

Standard C libraries

🧩 Game Components
Two players: Yellow and Red

Board size: 6 rows × 7 columns

Players drop discs into columns

Discs stack vertically from the bottom

🏆 Object of the Game
Players alternate turns placing discs in the grid.
The first player to connect four discs of the same color:

Horizontally

Vertically

Diagonally

wins the game.

▶️ Game Play Rules
Yellow always goes first

Players take turns selecting a column

Valid columns: {A, B, C, D, E, F, G} (case-insensitive)

Invalid input is rejected and re-prompted

Columns cannot exceed capacity

Player statistics are displayed after each move

🛑 End of Game
The game ends when:

A player achieves four in a row (horizontal, vertical, or diagonal)

A Game Over message is displayed along with final player statistics.

📂 Assignment File Structure
text
Copy code
.
├── connectfour.c   # Main game logic
└── connectfour.h   # Header file with macros, structs, and prototypes
🧠 Assignment Scope
This project required students to:

Copy and extend existing C source code

Create and use a header file

Move macros, structs, and prototypes to the header

Add new functions

Use structures

Compile and run a multi-file C program

Submit correctly named files to Webcourses

🛠 Required Functions
The following functions were implemented or updated:

Win Checking Functions
c
Copy code
int checkHorizontal(char board[ROW][COL]);
int checkVertical(char board[ROW][COL]);
int checkDiagonal(char board[ROW][COL]);
Game Flow Functions
c
Copy code
void displayGameOver(void);
Updated Logic
checkWin() calls all three check functions

playGame() controls game flow and display order

🧪 Test Cases
The program was tested against 11 required test cases, including:

Program startup and welcome message

Player name input

Invalid and valid column selection

Column full detection

Horizontal, vertical, and diagonal wins

Proper game over messaging

All test cases passed successfully.

✅ Compilation & Execution
Compile using gcc:

bash
Copy code
gcc connectfour.c -o connectfour
Run the program:

bash
Copy code
./connectfour
📚 References
Example source code provided in Webcourses:

dataTypes.c

variables.c

constants.c

operators.c

decisionMaking.c

looping.c

arrays.c

structures.c

header.h

📌 Notes
Source code compiles with no warnings or errors

Program runs correctly for all required scenarios

Code includes meaningful comments

File naming conventions were followed to avoid submission issues