#include "raylib.h"
#include <iostream>

// VARIABLES

const int screenWidth = 800;
const int screenHeight = 450;

// player variables
int playerX = 400;
int playerY = 250;
float playerR = 20.0;
Color playerColor = BLACK;
Color playerColors[] = {BLACK, BLUE, RED, PINK};
int playerColorIndex = 0;
bool touchingGround = true;
int playerTerminalSpeed = 20;
float playerVelocityY = 0;
float playerVelocityX = 0;
float playerDampening  = 0.9f;
int playerJumpHeight = 10;
float yVelPerFrame = 0.7;


// ground variables
int groundX = 0;
int groundY = 270;
int groundW = 800;
int groundH = 200;
Color groundColor = GREEN;

// word vars
const float gravity = 6;
float fricion = 0.97;


bool isPositive(float num) 
{
    return num > 0;
}


int main(void)
{

    InitWindow(screenWidth, screenHeight, "Ball Game");

    SetTargetFPS(60);   // Set my game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawFPS(7, 7);  // draw FPS

            DrawCircle(playerX, playerY, playerR, playerColors[playerColorIndex]);  // draw player
            DrawRectangle(groundX, groundY, groundW, groundH, groundColor);

            // Update player's velocity to gravity
            playerVelocityY += yVelPerFrame;
            if (playerVelocityY > gravity)
            {
                playerVelocityY = gravity;  // Cap the velocity to gravity
            }
            // Update player's Y position based on velocity
            playerY += playerVelocityY;

            // Update player's X position based on velocity
            playerX += playerVelocityX;

            if (playerVelocityX > playerTerminalSpeed - 0.5f)
            {
                playerVelocityX = playerTerminalSpeed;  // Cap the velocity to terminal speed
            }
            if ( playerVelocityX < -playerTerminalSpeed - 0.5f)
            {
                playerVelocityX = -playerTerminalSpeed;  // Cap the velocity to terminal speed
            }

            // checking if player is touching the ground
            if (playerY + playerR >= groundY)
            {
                touchingGround = true; 
                playerY = groundY - playerR;  // Reset player's position to be on top of the ground
                playerVelocityY = 0;  // Reset vertical velocity when touching the ground
            }
            else
            {
                touchingGround = false;
            }

            if (!touchingGround)
            {
                yVelPerFrame = 0.4;
            }


            if (IsKeyPressed(KEY_C))
            {
                playerColorIndex++;
                if (playerColorIndex > 3)
                {
                    playerColorIndex = 0;
                }
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                playerVelocityX += 0.5f;  
            }
            if (!IsKeyDown(KEY_RIGHT))
            {
                if (playerVelocityX < 0.5 && isPositive(playerVelocityX) && touchingGround)
                {
                    playerVelocityX = 0;
                }
                if (playerVelocityX > 0 && touchingGround)
                {
                    playerVelocityX *= fricion;
                }
            }
            if (IsKeyDown(KEY_LEFT))
            {
                playerVelocityX -= 0.5f;  
            }
            if (!IsKeyDown(KEY_LEFT))
            {
                if (playerVelocityX > -0.5 && !isPositive(playerVelocityX))
                {
                    playerVelocityX = 0;
                }
                if (playerVelocityX < 0 && touchingGround)
                {
                    playerVelocityX *= fricion;
                }  
            }
            if (IsKeyPressed(KEY_SPACE) && touchingGround)
            {
                playerVelocityY = -playerJumpHeight;  // Set the player's velocity to jump height
                touchingGround = false;  
            }

            // debug

            std::cout << "Y: " << playerY << " | X: " << playerX << " | VY: " << playerVelocityY << " | VX: " << playerVelocityX << "| TG: " << touchingGround << "\n";


        EndDrawing();
    }


    CloseWindow();        // Close window 

    return 0;
}