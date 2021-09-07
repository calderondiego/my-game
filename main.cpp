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

typedef struct Sprite {
     Texture2D texture;
     Vector2 frameSize;
     int maxFrame;
     int framesWide;
     int frame;
 } Sprite;

class Player {
    public:
        Sprite sprite;
        bool isRunning = false;
};

void drawSprite(Sprite* sprite, Vector2 position, Color color) 
{
    float ox, oy;
    ox = (sprite->frame % sprite->framesWide) * sprite->frameSize.x;
    oy = (int)(sprite->frame / sprite->framesWide) * sprite->frameSize.y;

    DrawTextureRec(sprite->texture, (Rectangle){ox, oy, sprite->frameSize.x,sprite->frameSize.y}, position, color);  
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "My Game");

    Vector2 idlePosition = (Vector2){ 300, 360};
    Vector2 runPosition = (Vector2){ 300, 400};

    Sprite idle = { 0 };
    idle.texture = LoadTexture("assets/pixel-adventure/characters/pink-dude/idle.png");
    idle.frameSize = (Vector2){ 32, 32 };
    idle.maxFrame = 10;
    idle.framesWide = 11;
    idle.frame = 0;

    Sprite run = { 0 };
    run.texture = LoadTexture("assets/pixel-adventure/characters/pink-dude/run.png");
    run.frameSize = (Vector2){ 32, 32 };
    run.maxFrame = 11;
    run.framesWide = 12;
    run.frame = 0;
    
    Player player;
    player.sprite = idle;

    int runFrame = 0;
    int idleFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 20;            // Number of spritesheet frames shown by second

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
        {
            if (player.isRunning)
            {
                player.sprite = idle;
                player.isRunning = false;
            } else 
            {
                player.sprite = run;
                player.isRunning = true;
            }
        }
        
        framesCounter++;
        
        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            runFrame++;
            // idleFrame++;
            player.sprite.frame++;
            if (runFrame > 11) runFrame = 0;
            if (player.sprite.frame > player.sprite.maxFrame) player.sprite.frame = 0;

            // idle.frame = idleFrame;
            // player.sprite.frame = idleFrame;
            run.frame = runFrame;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawSprite(&player.sprite, idlePosition, WHITE);
            drawSprite(&run, runPosition, WHITE);
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(run.texture);       
    UnloadTexture(idle.texture);         

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}