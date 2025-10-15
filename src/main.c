#include "raylib.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RPG Project");

    while (!WindowShouldClose()) {

        BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}