#include "raylib.h"
#include <iostream>


int main(void)
{
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
    int playerTerminalSpeed = 10;
    float playerVelocity = 0;

    // ground variables
    int groundX = 0;
    int groundY = 270;
    int groundW = 800;
    int groundH = 100;
    Color groundColor = GREEN;

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

            if (playerY + playerR >= groundY)
            {
                touchingGround = true;
                std::cout << "\nTouching ground is True\n";
            }
            else
            {
                std::cout << "\nTouching ground is falsen\n";
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
                playerX += playerTerminalSpeed;
            }
            if (IsKeyDown(KEY_LEFT))
            {
                playerX -= playerTerminalSpeed;
            }



        EndDrawing();
    }


    CloseWindow();        // Close window 

    return 0;
}