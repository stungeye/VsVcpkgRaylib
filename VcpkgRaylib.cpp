/*******************************************************************************************
*
*   raylib Basic Window Exampl using vcpkg and Visual Studio
*
*   This demo code was originally written by Ramon Santamaria (@raysan5) with the following 
*   license and copyright information:
* 
*       Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*       BSD-like license that allows static linking with closed source software
*
*       Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
// 
// To remove the console window that opens with the app:
//   - Open the project properties. (Project Menu => Properties)
//   - Navigate to Linker => System
//   - Change the SubSystem to Windows (/SUBSYSTEM:WINDOWS)
//   - Navigate with properties to Linker => Advanced
//   - Change the Entry Point to mainCRTStartup 
// 
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}