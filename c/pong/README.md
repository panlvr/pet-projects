# Pong Game (ASCII)

A classic two-player Pong game implemented in C using ASCII graphics in the terminal. This is a turn-based version where players control paddles to hit a ball and score points.

## 📜 Description

This program implements a simplified version of the classic Pong game using only ASCII characters for graphics. The game is played in the terminal on a 80x25 character grid. Two players compete to score 21 points by bouncing the ball past their opponent's paddle.

## 🎮 Game Features

- **Two-player gameplay** with keyboard controls
- **Turn-based mechanics** - each move advances the game state
- **ASCII graphics** displayed in the terminal
- **Score tracking** with win condition at 21 points
- **Simple, clean interface** using only standard C library

## 🎯 Controls

| Player | Move Up | Move Down |
|--------|---------|-----------|
| **Player 1** (Left) | `A` / `a` | `Z` / `z` |
| **Player 2** (Right) | `K` / `k` | `M` / `m` |

**Special Controls:**
- `Space Bar` - Advance to next step in turn-based mode

## 🚀 How to Run

### Prerequisites
- GCC compiler (or any C compiler)
- Terminal with at least 80x25 character resolution
- Make (optional, for using the Makefile)

### Project Structure
```text
pet-projects/c/pong/
├── pong.c # Main game source code
├── Makefile # Build automation
└── README.md # This file
```

### Compilation and Execution

#### Using Make (Recommended)
```bash
cd projects/pong
make          # Compile the game
make run      # Compile and run
Available Make Commands
Command	Description
make or make all	Compile the game
make run	Compile (if needed) and run the game
make clean	Remove the compiled executable
make rebuild	Clean and rebuild from scratch
make debug	Build with debug symbols for debugging
make help	Show all available commands
```
#### Manual Compilation (Without Make)
```bash
cd projects/pong
gcc -Wall -Wextra -std=c99 -o pong src/pong.c
./pong
```
### 🎨 Game Specifications
* Playing Field: 80 characters wide × 25 characters tall

* Paddle Size: 3 characters

* Ball Size: 1 character

* Winning Score: 21 points

### 🕹️ How to Play
1. Run the program to start the game

2. Player 1 (left side) uses A (up) and Z (down) to move their paddle

3. Player 2 (right side) uses K (up) and M (down) to move their paddle

4. Press Space Bar to advance each turn

5. The ball will move after each turn - try to hit it with your paddle

6. Score points when the ball passes your opponent's paddle

7. First player to reach 21 points wins!

### 🔧 Game Mechanics
* Wall Collision: Ball bounces off the top and bottom walls

* Paddle Collision: Ball reverses direction when hitting a paddle

* Scoring: A point is scored when the ball reaches the left or right edge of the field

* Reset: After each goal, the ball and paddles return to their starting positions

### 🛠️ Technical Details
* Written entirely in C

* Uses only standard library functions

* Terminal-based ASCII graphics

* No external graphics libraries required

* Modular function-based design

### 🐛 Debugging
If you encounter issues:

- Terminal size: Ensure your terminal window is at least 80x25 characters

- Input not working: Make sure you're pressing lowercase letters (a, z, k, m) or space

- Compilation errors: Try make clean then make to rebuild

- Debug build: Use make debug for detailed error messages

### 📝 Notes
* The game is turn-based - action only progresses when you press Space

* All inputs are case-insensitive (both uppercase and lowercase work)

* The screen clears before each turn for a cleaner display

### 🏆 Win Condition
The game ends when either player reaches 21 points. The winner is announced, and the program terminates.

### 📄 License
This project is created for educational purposes as part of a programming course.
