#include "raylib.h"
#include <iostream>

// VARIABLES

const int screenWidth = 800;
const int screenHeight = 450;

// player variables
float playerX = 400;
float playerY = 280;
float playerS = 1.0f;
float playerR = 20.0;
Color playerColor = BLACK;
Color playerColors[] = {BLACK, DARKBLUE, RED, PINK};
int playerColorIndex = 0;
bool touchingGround = true;
int playerTerminalSpeed = 10;
float playerVelocityY = 0;
float playerVelocityX = 0;
const float basePlayerJumpHeight = 8.5f;
float yVelPerFrame = 0.2;
float xVelPerFrame = 0.3;
float playerSpriteRotation = 0.0f;
bool isMovingR = false;
const float baseRadius = 20.0f;
float playerJumpHeight = 8.5f;

// ground variables  
int groundX = 0;
int groundY = 300;
int groundW = 800;
int groundH = 200;

// ground 2 variables
int ground2X = groundX + groundW;
int ground2Y = groundY;
int ground2W = groundW;
int ground2H = groundH;

// world vars
const float gravity = 5.5;
float friction = 0.97;
Rectangle leftWall = { -50, 0, 50, screenHeight }; 
Texture2D ground2Texture;

void drawNextGround()
{
    groundX = 0;
}

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
    ground2Texture = LoadTexture("resources/terrain.png");      

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        ground2X = groundX + groundW;


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
                Rectangle{0, 0, (float)ground2Texture.width, (float)ground2Texture.height},                       // source rect (full image)
                Rectangle{(float)groundX, (float)groundY, (float)ground2W, (float)groundH},     // dest rect (full screen)
                Vector2{0, 0},                                                                                  // origin (no rotation/scaling offset)
                0.0f,                                                                                          // rotation (no rotation)
                WHITE                                                                                         // tint (no tint)
            );
            DrawTexturePro
            (
                ground2Texture,
                Rectangle{0, 0, (float)ground2Texture.width, (float)ground2Texture.height},       // source rect (full image)
                Rectangle{(float)ground2X, (float)ground2Y, (float)ground2W, (float)ground2H},     // dest rect (full screen)
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

            if (playerVelocityX > 0)
            {
                isMovingR = true;
            }
            else
            {
                isMovingR = false;
            }

            // invisible wall check
            if (CheckCollisionCircleRec((Vector2){(float)playerX, (float)playerY}, playerR, leftWall)) 
            {
                if (playerVelocityX < 0)
                {
                    playerVelocityX = 0;
                }
                
                playerX = (int)(leftWall.x + leftWall.width + playerR); // push player right, outside the left wall
            }

            
            if (playerX + playerR > screenWidth && isMovingR)
            {
                playerX = playerX - (playerX - (screenWidth - playerR));
                groundX -= playerVelocityX;
            }

            if (groundX < -screenWidth)
            {

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

            if (ground2X < 0)
            {
                ground2X = ground2X + groundW;
                drawNextGround();
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
                    playerVelocityX *= friction;
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
                    playerVelocityX *= friction;
                }  
            }
            if (IsKeyPressed(KEY_SPACE) && touchingGround)
            {
                playerVelocityY = -playerJumpHeight;  // Set the player's velocity to jump height
                touchingGround = false;  
            }
            if (IsKeyDown(KEY_UP))
            {
                playerS += 0.045f;
                if (playerS > 5)
                {
                    playerS = 5;
                }
            }
            if (IsKeyDown(KEY_DOWN))
            {
                playerS -= 0.045f;

                if (playerS < 0.3)
                {
                    playerS = 0.3;
                }
            }
            playerR = baseRadius * playerS;
            friction = 0.97f + (playerS * 0.01f); // more friction at bigger sizes, but clamp it
            playerTerminalSpeed = 10 / (playerS);
            playerJumpHeight = basePlayerJumpHeight;
            xVelPerFrame = 0.2 / playerS;
            if (friction < 0.85f) friction = 0.85f;
            if (friction > 0.99f) friction = 0.99f;
            if (playerTerminalSpeed < 3.5f) playerTerminalSpeed = 3.5f;
            
            

            playerJumpHeight = basePlayerJumpHeight - (playerS / 2);


            // debug

            std::cout << "Y: " << playerY << " | X: " << playerX << " | VY: " << playerVelocityY << " | VX: " << playerVelocityX << "| TG: " << touchingGround << "| GX: " << groundX << "| G2X: " << ground2X << "\n";


        EndDrawing();
    }

    UnloadTexture(skyTexture);  // Unload texture
    UnloadTexture(ground2Texture);
    UnloadTexture(ground2Texture);
    CloseWindow();        // Close window 

    return 0;
}

