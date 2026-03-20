#include <stdio.h>  

int bounceWalls(int ballY, int dBallY);     // Check if ball bounces off top/bottom wall
int bouncePad(int ballX, int ballY, int dBallX, int PadY, int PadX);  // Check if ball bounces off paddle
int score(int ballX);                        // Check if a goal is scored
int winner(int leftScore, int rightScore);   // Check if someone has won
int moveBallX(int ballX, int dBallX);        // Move ball horizontally
int moveBallY(int ballY, int dBallY);        // Move ball vertically
int drawBorders();                           // Draw field borders
int drawRow(int row, int ballX, int ballY, int rightPadX, int rightPadY, 
            int leftPadX, int leftPadY);     // Draw one row of the field
int drawField(int ballX, int ballY, int rightPadX, int rightPadY, 
              int leftPadX, int leftPadY, int player1Score, int player2Score);  // Draw entire field
int moveLeftPad(char cmd, int leftPadY);     // Move left paddle
int moveRightPad(char cmd, int rightPadY);   // Move right paddle
char getInput();                              // Get command from player

int main() {
    int ballX = 40;        // Initial ball X position
    int ballY = 12;        // Initial ball Y position
    int dBallX = 1;        // Ball X direction: +1 right, -1 left
    int dBallY = 1;        // Ball Y direction: +1 down, -1 up
    int rightPadX = 70;    // Right paddle X position 
    int rightPadY = 12;    // Initial right paddle Y position 
    int leftPadX = 10;     // Left paddle X position 
    int leftPadY = 12;     // Initial left paddle Y position
    int player1Score = 0;  // Player 1 score (left)
    int player2Score = 0;  // Player 2 score (right)
    int gameActive = 1;    // Game active flag: 1 - game running, 0 - game over

    while (gameActive) {
        // Step 1: Draw current field state
        drawField(ballX, ballY, rightPadX, rightPadY, leftPadX, leftPadY, 
                  player1Score, player2Score);
        
        // Step 2: Get command from player
        char cmd = getInput();
        
        // Step 3: Move paddles according to command
        leftPadY = moveLeftPad(cmd, leftPadY);    // Update left paddle position
        rightPadY = moveRightPad(cmd, rightPadY);  // Update right paddle position
        // Step 4: Move ball
        ballX = moveBallX(ballX, dBallX);  // New X position
        ballY = moveBallY(ballY, dBallY);  // New Y position
        // Step 5: Check collisions and change direction
        dBallY = bounceWalls(ballY, dBallY);      // Check wall collision
        dBallX = bouncePad(ballX, ballY, dBallX, leftPadY, leftPadX);   // Check left paddle collision
        dBallX = bouncePad(ballX, ballY, dBallX, rightPadY, rightPadX); // Check right paddle collision
        // Step 6: Check for goal
        int scored = score(ballX);  // scored = 0 (no goal), 1 (goal for right player), 2 (goal for left player)
        
        if (scored == 1) {  // Goal for right player (ball at left edge)
            player2Score++;  // Increase right player's score
            // Reset ball and paddles to initial positions
            ballX = 40;       // Ball to center X
            ballY = 12;       // Ball to center Y
            dBallX = -1;      // After goal for right, ball moves left
            dBallY = 1;       // Y direction - down
            leftPadY = 12;    // Left paddle to center
            rightPadY = 12;   // Right paddle to center
        } else if (scored == 2) {  // Goal for left player (ball at right edge)
            player1Score++;   // Increase left player's score
            // Reset ball and paddles to initial positions
            ballX = 40;       
            ballY = 12;
            dBallX = 1;       // After goal for left, ball moves right
            dBallY = 1;
            leftPadY = 12;
            rightPadY = 12;
        }
        // Step 7: Check for victory
        int win = winner(player1Score, player2Score);  // win = 0 (no), 1 (left), 2 (right)
        
        if (win == 1) {  // Left player wins
            // Final field rendering
            drawField(ballX, ballY, rightPadX, rightPadY, leftPadX, leftPadY, 
                      player1Score, player2Score);
            printf("Player 1 wins!\n");  // Display victory message
            gameActive = 0;  // End game loop
        } else if (win == 2) {  // Right player wins
            drawField(ballX, ballY, rightPadX, rightPadY, leftPadX, leftPadY, 
                      player1Score, player2Score);
            printf("Player 2 wins!\n");
            gameActive = 0;
        }
    }
    
    return 0;
}


// Moves ball horizontally
int moveBallX(int ballX, int dBallX) {
    ballX += dBallX; 
    return ballX;
}

// Moves ball vertically
int moveBallY(int ballY, int dBallY) {
    ballY += dBallY; 
    return ballY; 
}

// Checks ball collision with top and bottom walls
int bounceWalls(int ballY, int dBallY) {
       if (ballY == 1 || ballY == 23) {
        dBallY *= -1;
        return dBallY;
    } else {
        return dBallY;
    }
}

// Checks ball collision with paddle
int bouncePad(int ballX, int ballY, int dBallX, int PadY, int PadX) {
    if (((ballX + 1) == PadX && (ballY == PadY || ballY == PadY + 1 || ballY == PadY - 1)) ||
        ((ballX - 1) == PadX && (ballY == PadY || ballY == PadY + 1  || ballY == PadY - 1))) {
        dBallX *= -1; 
        return dBallX;
    } else {
        return dBallX;    // No change
    }
}

// Checks if a goal is scored
int score(int ballX) {
    if (ballX == 10) {   
        return 1;
    }
    if (ballX == 70) { 
        return 2;
    }
    return 0;         
}

// Checks if someone has reached 21 points
int winner(int leftScore, int rightScore) {
    if (leftScore == 21) {  
        return 1;
    }
    if (rightScore == 21) {   
        return 2;
    }
    return 0;            
}

// Gets command from player via keyboard
char getInput() {
    char cmd;    
    char flush; 
    
    cmd = getchar();      
    flush = getchar();   

    while (flush != '\n') {
        flush = getchar();
    }
    
    return cmd;  
}

// Moves left paddle according to command
int moveLeftPad(char cmd, int leftPadY) {
    if (cmd == 'a' || cmd == 'A') {
        if (leftPadY > 2)           
            return leftPadY - 1;   
    }
    if (cmd == 'z' || cmd == 'Z') {
        if (leftPadY < 22)          
            return leftPadY + 1;    
    }
    return leftPadY; 
}

// Moves right paddle according to command
int moveRightPad(char cmd, int rightPadY) {
    if (cmd == 'k' || cmd == 'K') {
        if (rightPadY > 2)          
            return rightPadY - 1;    
    }
    if (cmd == 'm' || cmd == 'M') {
        if (rightPadY < 22)        
            return rightPadY + 1; 
    }
    return rightPadY; 
}

int drawBorders() {
    for (int i = 0; i < 80; i++) {  
        printf("—");                 
    }
    printf("\n");                    
    return 0;
}

int drawRow(int row, int ballX, int ballY, int rightPadX, int rightPadY, 
            int leftPadX, int leftPadY) {
    for (int col = 0; col < 80; col++) {
        if (col == 0 || col == 79) {
            printf("|");
        }
        else if (col == ballX && row == ballY) {
            printf("*");
        }
        else if (col == 40) {
            printf("|");
        }
        else if ((col == rightPadX && (row >= rightPadY - 1 && row <= rightPadY + 1)) ||
                 (col == leftPadX && (row >= leftPadY - 1 && row <= leftPadY + 1))) {
            printf("|");
        }
        else {
            printf(" ");
        }
    }
    printf("\n"); 
    return 0;
}

// Draws the entire playing field
int drawField(int ballX, int ballY, int rightPadX, int rightPadY, int leftPadX, int leftPadY,
              int player1Score, int player2Score) {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
    
    printf(" Player 1: %d%56sPlayer 2: %d\n", player1Score, "", player2Score);
    
    drawBorders();  // Top border
    
    // Draw field rows from 1 to 23 (rows 0 and 24 are borders)
    for (int row = 1; row < 24; row++) {
        drawRow(row, ballX, ballY, rightPadX, rightPadY, leftPadX, leftPadY);
    }
    
    drawBorders();  // Bottom border
    
    return 0;
}