/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "libraries/raylib/include/raylib.h"
#include "raylib.h"
#include <stdio.h>

Sound soundArray[10];

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitAudioDevice();

    soundArray[0] = LoadSound("resources/raylib_audio_resources/sound.wav");

    Music music = LoadMusicStream("resources/raylib_audio_resources/country.mp3");

    music.looping = true;
    float pitch = 0.5f;

    PlayMusicStream(music);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    static double x= 120, y = 35;
    static double speed_x = 5, speed_y = 5;
    const float gravity = 0.5f;
    static bool isGrounded = false;
    static int enemyLife = 3;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        if (IsKeyDown(KEY_RIGHT)) x += speed_x;
        if (IsKeyDown(KEY_LEFT)) x -= speed_x;
        if (IsKeyDown(KEY_DOWN)) y += speed_y;
        if (IsKeyDown(KEY_UP)) y -= speed_y;

        if (y > 350){
            y = 350;
            speed_y = 0.0f;
            isGrounded = true;
        }
        else if (y < 350) {
            isGrounded = false;
        }
        if (y < 0) y = 0;
        if (x > screenWidth) x = screenWidth;
        if (x < 0) x = 0;

        if (IsKeyPressed(KEY_SPACE) && isGrounded == true) {
            speed_y -= 10.0f;
            PlaySound(soundArray[0]);
        }

        speed_y += gravity; // Aplica gravedad
        y += speed_y;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

       
        //DrawCircle(x, y, 35, DARKBLUE);
        Rectangle rec1;
        Rectangle rec2;
        rec1.x = x + 20;
        rec2.x = 600;
        rec1.y = y + 20;
        rec2.y = 300;
        rec1.width = 50;
        rec2.width = 80;
        rec1.height = 70;
        rec2.height = 130;

        DrawRectangleRec(rec1, RED);
        DrawRectangleRec(rec2, GREEN);
        //DrawText("Enemy HP: " + enemyLife, 0, 0, 20, RED);

        if (IsKeyPressed(KEY_D)) {
            Rectangle rec3;
            rec3.x = x + 60;
            rec3.y = y + 40;
            rec3.width = 70;
            rec3.height = 10;
            DrawRectangleRec(rec3, BLUE);
            if (CheckCollisionRecs(rec3, rec2)) {
                DrawText("Collision!!", 0, 0, 20, RED);
                enemyLife -= 1;
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
// raylib example source code