#include "raylib.h"
#include <iostream>

// VARIABLES

const int screenWidth = 800;
const int screenHeight = 450;

// player variables
int playerX = 400;
int playerY = 280;
float playerR = 20.0;
Color playerColor = BLACK;
Color playerColors[] = {BLACK, DARKBLUE, RED, PINK};
int playerColorIndex = 0;
bool touchingGround = true;
int playerTerminalSpeed = 10;
float playerVelocityY = 0;
float playerVelocityX = 0;
int playerJumpHeight = 8.5;
float yVelPerFrame = 0.2;
float xVelPerFrame = 0.3;
float playerSpriteRotation = 0.0f;

// ground variables  
int groundX = 0;
int groundY = 300;
int groundW = 800;
int groundH = 200;
Color groundColor = GREEN;

// word vars
const float gravity = 5.5;
float fricion = 0.97;

// Images


bool isPositive(float num) 
{
    return num > 0;
}


int main(void)
{

    InitWindow(screenWidth, screenHeight, "Ball Game");

    SetTargetFPS(120);   // Set my game to run at 60 frames-per-second

    Texture2D skyTexture = LoadTexture("resources/sky.jpg");
    Texture2D groundTexture = LoadTexture("resources/terrain.png");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawFPS(7, 7);  // draw FPS
            
            // Drawing
            DrawTexturePro
            (
                skyTexture,
                Rectangle{0, 0, (float)skyTexture.width, (float)skyTexture.height}, // source rect (full image)
                Rectangle{0, 0, (float)screenWidth, (float)skyTexture.height},     // dest rect (full screen)
                Vector2{0, 0},                                                    // origin (no rotation/scaling offset)
                0.0f,                                                            // rotation (no rotation)
                WHITE                                                           // tint (no tint)
            );

            DrawTexturePro
            (
                groundTexture,
                Rectangle{0, 0, (float)groundTexture.width, (float)groundTexture.height},       // source rect (full image)
                Rectangle{(float)groundX, (float)groundY, (float)groundW, (float)groundH},     // dest rect (full screen)
                Vector2{0, 0},                                                                // origin (no rotation/scaling offset)
                0.0f,                                                                        // rotation (no rotation)
                WHITE                                                                       // tint (no tint)
            );
            DrawCircle(playerX, playerY, playerR, playerColors[playerColorIndex]);  // draw player
            // DrawRectangle(groundX, groundY, groundW, groundH, groundColor); // draw ground  

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

            if (playerVelocityX > playerTerminalSpeed)
            {
                playerVelocityX = playerTerminalSpeed;  // Cap the velocity to terminal speed
            }
            if (playerVelocityX < -playerTerminalSpeed)
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
                xVelPerFrame = 0.07;
            }
            else
            {
                xVelPerFrame = 0.2;
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
                playerVelocityX += xVelPerFrame;  
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
                playerVelocityX -= xVelPerFrame;  
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

    UnloadTexture(skyTexture);  // Unload texture
    CloseWindow();        // Close window 

    return 0;
}