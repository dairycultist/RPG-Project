// https://www.raylib.com/cheatsheet/cheatsheet.html
#include "raylib.h"

#define DEFAULT_WINDOW_WIDTH 600
#define DEFAULT_WINDOW_HEIGHT 400

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

#define TRUE 1
#define FALSE 0

// game states are pushed onto, and popped from, a (quite short) stack
// ex. worldmap -> battle -> dialogue -> pause menu
// game states are internally represented as structs!!!!!! with methods!!!!!!!! abstraction!!!!!!!!!!!

struct GameState {

	void (*process)(struct GameState *self);
	void (*render)(struct GameState *self);
	void *data;
	bool renders_over_prev_state;

};

typedef struct GameState GameState;

// states:
// - world map
// - dialogue (overlaid on top of previous state; can have a character portrait + name or not)
// - pause menu (overlaid on top of previous state; manage items/party and quit to main menu)
// - battle
// - shop

// custom sprites for scene backgrounds, in-scene sprites, and dialogue portraits. tilemap for world map

// Camera2D camera = {0};
// camera.zoom = 1.0f;
// BeginMode2D(camera);
// // draw calls
// EndMode2D();

#include <math.h>

void recompute_letterbox(Rectangle *screen_dest) {

	float virtual_ratio = (float) GetScreenWidth() / (float) SCREEN_WIDTH;
	*screen_dest = (Rectangle) { -virtual_ratio, -virtual_ratio, GetScreenWidth() + (virtual_ratio * 2), GetScreenHeight() + (virtual_ratio * 2) };
}

int main(void) {

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "RPG Project");
	SetTargetFPS(60);
	// GetFrameTime(); // deltaTime

    // screen texture
    RenderTexture2D screen_texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

	Rectangle screen_src = { 0.0f, 0.0f, (float) screen_texture.texture.width, -(float) screen_texture.texture.height }; // texture height is flipped bc OpenGL
	Rectangle screen_dest;
	recompute_letterbox(&screen_dest);

    Vector2 screen_origin = { 0.0f, 0.0f };

	// test rect
	Rectangle rect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 200.0f, 200.0f };
	Vector2 rect_origin = { 100.0f, 100.0f };

    float rotation = 0.0f;

	// game loop
    while (!WindowShouldClose()) {

		if (IsWindowResized()) {

			recompute_letterbox(&screen_dest);
		}

        // process
        rotation += 60.0f * GetFrameTime();

        // draw to screen
        BeginTextureMode(screen_texture);
		ClearBackground(RAYWHITE);

		DrawRectanglePro(rect, rect_origin, rotation, BLACK);
		DrawText("text", 10, 10, 20, LIGHTGRAY);

        EndTextureMode();

		// draw to window
        BeginDrawing();
		ClearBackground(RED);

		DrawTexturePro(screen_texture.texture, screen_src, screen_dest, screen_origin, 0.0f, WHITE);

        EndDrawing();
    }

	// clean up
    UnloadRenderTexture(screen_texture);
    CloseWindow();

    return 0;
}