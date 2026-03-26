# Pong Game - Terminal-Based Table Tennis
A classic Pong implementation using the ncurses library for terminal-based graphics and real-time keyboard input.

## 🎮 Game Description
This is a two-player Pong game where players control paddles to hit a ball back and forth. The game runs entirely in the terminal and features:

* Real-time non-blocking keyboard input

* Smooth ball movement with adjustable speed

* Score tracking

* Win condition at 21 points

* Terminal-based graphics using ncurses

## 🕹️ Controls
|Player|Action|Key|
|---|---|---|
|Left Player|Move paddle up|`A` or `a`|
|Left Player|Move paddle down|`Z` or `z`|
|Right Player|Move paddle up|`K` or `k`|
|Right Player|Move paddle down|`M` or `m`|

## 🚀 How to Compile and Run
### Prerequisites
- GCC compiler (or any C compiler)
- Terminal with at least 80x25 character resolution
- Make (optional, for using the Makefile)

### Project Structure
```text
pet-projects/c/pong-live/
├── pong-live.c # Main game source code
├── Makefile # Build automation
└── README.md # This file
```

### Compilation and Execution

#### Using Make (Recommended)
```bash
cd pet-projects/c/pong-live
make          # Compile the game
make run      # Compile and run
make clean	# Remove the compiled executable
make rebuild	# Clean and rebuild from scratch
make debug	# Build with debug symbols for debugging
make help	# Show all available commands
```
#### Manual Compilation (Without Make)
```bash
cd pet-projects/c/pong-live
gcc -Wall -Wextra -std=c11 -o pong-live pong-live.c
./pong-live
```
## 🎨 Game Specifications
* Playing Field: 80 characters wide × 25 characters tall

* Paddle Size: 3 characters

* Ball Size: 1 character

* Winning Score: 21 points

## 🕹️ How to Play
1. Run the program to start the game

2. Player 1 (left side) uses A (up) and Z (down) to move their paddle

3. Player 2 (right side) uses K (up) and M (down) to move their paddle

4. Press Space Bar to advance each turn

5. The ball will move after each turn - try to hit it with your paddle

6. Score points when the ball passes your opponent's paddle

7. First player to reach 21 points wins!

## 🔧 Game Mechanics
* Wall Collision: Ball bounces off the top and bottom walls

* Paddle Collision: Ball reverses direction when hitting a paddle

* Scoring: A point is scored when the ball reaches the left or right edge of the field

* Reset: After each goal, the ball and paddles return to their starting positions

## ⚙️ Technical Features
### `ncurses` Implementation
* Non-blocking input using nodelay() for responsive controls

* Screen buffering with clear() and refresh() for smooth rendering

* No echo of typed characters

* Real-time input without requiring Enter key

### Ball Movement Timing
* The game uses a timer-based movement system:

    * Ball moves every 130ms for smoother gameplay

    * Frame rate controlled by napms(10) for 100 FPS rendering

    * Separates rendering from physics updates

## 🔧 Customization
You can modify these constants in the code to change gameplay:

```c
// Game speed
ballTimer >= 130;  // Increase for slower ball, decrease for faster
napms(10);         // Frame rate (lower = smoother, higher = less CPU)

// Paddle boundaries
leftPadY > 2;      // Upper limit
leftPadY < 22;     // Lower limit

// Winning score
if (leftScore == 21)  // Change to any number
```

## 🐛 Troubleshooting
## Compilation Errors
* `Undefined symbols for architecture arm64`: Make sure to link ncurses with -lncurses

* `ncurses.h file not found`: Install ncurses development package

### Runtime Issues
* `Screen flickering`: Ensure clear() and refresh() are used correctly

* `Input not working`: Check that cbreak() and nodelay() are called

* `Terminal left in weird state`: If program crashes, run reset command

## 📝 Notes
* The game requires a terminal window with at least 80×25 characters

* Both players can play simultaneously on the same keyboard

* The game uses 100% CPU during gameplay (due to constant rendering loop)

* Press `Ctrl+C` to exit if needed (will leave terminal in ncurses mode - use reset to fix)

## 🤝 Contributing
* Feel free to modify and enhance the game! Some ideas:

* Add ball speed increase after each hit

* Add sound effects (using `printf("\a")` for beep)

* Add AI opponent for single-player mode

* Add different difficulty levels

* Add power-ups

* Add score display animation

## 📄 License
This project is open source and free to use for educational purposes.