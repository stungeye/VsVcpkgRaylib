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
#include "imgui.h"
#include "rlImGui.h"

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
    const int screenWidth{ 1280 };
    const int screenHeight{ 720 };

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(120);               // Set our game to run at 60 frames-per-second
    rlImGuiSetup(true);
    //--------------------------------------------------------------------------------------
	bool open{ true };
	float scale{ 35.0f };

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

		// Draw a circle that we can click on to toggle the ImGui demo window.
        // Circle radius will be controlled by a second ImGui window.
		int circleX = screenWidth / 5;
		int circleY = 120;
        DrawCircle(circleX, circleY, scale, DARKBLUE);
		DrawText("Click me!", circleX - 40, circleY + scale + 20, 20, DARKGRAY);

        // Toggle the ImgGui demo window if we click on the circle:
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePos = GetMousePosition();
			if (CheckCollisionPointCircle(mousePos, { (float)circleX, (float)circleY }, scale)) {
				open = !open;
			}
		}

		rlImGuiBegin();
		if (open) ImGui::ShowDemoWindow(&open);
        
        ImGui::Begin("Scale the Circle", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SliderFloat("Circle Radius", &scale, 5.0f, 70.0f);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();

		rlImGuiEnd();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rlImGuiShutdown();		// cleans up ImGui
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}