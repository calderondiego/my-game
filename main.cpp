/*******************************************************************************************
*
*   raylib [textures] example - Texture loading and drawing a part defined by a rectangle
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D frog_run = LoadTexture("assets/pixel-adventure/characters/frog/run.png");        // Texture loading
    Texture2D frog_wall_jump = LoadTexture("assets/pixel-adventure/characters/frog/wall_jump.png");        // Texture loading


    Vector2 position = { 350.0f, 280.0f };
    Vector2 wall_position = { 350.0f, 320.0f };

    Rectangle frameRec = { 0.0f, 0.0f, (float)frog_run.width/12, (float)frog_run.height };
    Rectangle jump_frameRec = { 0.0f, 0.0f, (float)frog_wall_jump.width/5, (float)frog_wall_jump.height };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 20;            // Number of spritesheet frames shown by second

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;
        
        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 11) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)frog_run.width/12;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(frog_run, 15, 40, WHITE);
            DrawTexture(frog_wall_jump, 15, 75, WHITE);
            DrawRectangleLines(15, 40, frog_run.width, frog_run.height, LIME);
            DrawRectangleLines(15 + (int)frameRec.x, 40 + (int)frameRec.y, (int)frameRec.width, (int)frameRec.height, RED);
            DrawTextureRec(frog_run, frameRec, position, WHITE);  // Draw part of the texture
            DrawTextureRec(frog_wall_jump, frameRec, wall_position, WHITE);  // Draw part of the texture

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(frog_run);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}