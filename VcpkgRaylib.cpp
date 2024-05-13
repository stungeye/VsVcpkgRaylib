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
#include <vector>
#include <algorithm>

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
    int screenWidth{ 1280 };
    int screenHeight{ 720 };

    // Config Flags: 
	// FLAG_MSAA_4X_HINT: Enable Multi Sampling Anti Aliasing 4x (if available).
	// FLAG_VSYNC_HINT: Enable V-Sync to synchronize frame rate with monitor refresh rate.
    // FLAG_WINDOW_RESIZABLE: Window is resizable by user.
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

	// Initialize window to a specific width and height, with a title.
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
 
    
    // Set our app to run at 120 frames-per-second
    SetTargetFPS(120);
    
	// Setup ImGui Backend
    rlImGuiSetup(true);
    //--------------------------------------------------------------------------------------
	bool open{ true };
	float scale{ 35.0f };

	// Create velocity vector for the squares


	int numberOfSquares{ 500 };
	std::vector<Rectangle> squares;
	std::vector<Vector2> squareVelocities;
	// Create a vector of squares of size scale at random positions
    for (int i = 0; i < numberOfSquares; i++) {
		squares.push_back({ (float)GetRandomValue(0, screenWidth - scale), (float)GetRandomValue(0, screenHeight - scale), scale, scale });
		squareVelocities.push_back({ (float)GetRandomValue(-5, 5), (float)GetRandomValue(-5, 5) });
    }

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

		// Update screen width and height if the window is resized
		screenWidth = GetScreenWidth();
		screenHeight = GetScreenHeight();

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

		// If nubmerOfSquares has changed, resize the vectors
		if (numberOfSquares != squares.size()) {
			if (numberOfSquares > squares.size()) {
				for (int i = squares.size(); i < numberOfSquares; i++) {
					squares.push_back({ (float)GetRandomValue(0, screenWidth - scale), (float)GetRandomValue(0, screenHeight - scale), scale, scale });
					squareVelocities.push_back({ (float)GetRandomValue(-5, 5), (float)GetRandomValue(-5, 5) });
				}
			}
			else {
				squares.resize(numberOfSquares);
				squareVelocities.resize(numberOfSquares);
			}
		}

		// Resize and draw the squares.
		for (int i = 0; i < numberOfSquares; i++) {
			squares[i].width = scale;
			squares[i].height = scale;

			// Move the squares
            squares[i].x += squareVelocities[i].x;
			squares[i].y += squareVelocities[i].y;

			// Bounce the squares off the walls, with boundary constraints in case they go off screen.
			if (squares[i].x < 0 || squares[i].x + squares[i].width > screenWidth) {
				squareVelocities[i].x *= -1;
				squares[i].x = std::clamp(squares[i].x, 0.0f, (float)screenWidth - squares[i].width);
			}
			if (squares[i].y < 0 || squares[i].y + squares[i].height > screenHeight) {
				squareVelocities[i].y *= -1;
				squares[i].y = std::clamp(squares[i].y, 0.0f, (float)screenHeight - squares[i].height);
			}


			DrawRectangleRec(squares[i], RED);
		}

		rlImGuiBegin();
		if (open) ImGui::ShowDemoWindow(&open);
        
        ImGui::Begin("Scale the Circle", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SliderFloat("Circle Radius", &scale, 5.0f, 70.0f);
        ImGui::SliderInt("Square Count", &numberOfSquares, 1, 150000);
        ImGui::Text("ImGui FPS: %.1f Raylib FPS: %d", ImGui::GetIO().Framerate, GetFPS());
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