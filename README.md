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
| **Player 1** (Left) | `A` | `Z` |
| **Player 2** (Right) | `K` | `M` |

**Special Controls:**
- `Space Bar` - Advance to next step in turn-based mode

## 🚀 How to Run

### Prerequisites
- GCC compiler (or any C compiler)
- Terminal with at least 80x25 character resolution

### Compilation
```bash
gcc src/pong.c -o pong