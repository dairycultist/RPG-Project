// https://www.raylib.com/cheatsheet/cheatsheet.html
#include <stdlib.h>
#include "raylib.h"

#define DEFAULT_WINDOW_WIDTH 600
#define DEFAULT_WINDOW_HEIGHT 400

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

#define TRUE 1
#define FALSE 0

// SaveState, which contains stuff like party info, items, and whatever (persistent between states!)
typedef struct {

} SaveState;

// GameStates are pushed onto, and popped from, a (quite short) stack (abstraction :D)
// ex. worldmap -> battle -> dialogue -> pause menu
struct GameState {

	void (*process)(struct GameState *self, SaveState *save);
	void (*draw)(struct GameState *self, SaveState *save);
	void (*destroy)(struct GameState *self, SaveState *save);
	void *data;
	bool draws_over_prev_state;

};
typedef struct GameState GameState;

GameState curr_game_state;

// states:
// - map.c
// - dialogue.c (overlaid on top of previous state; can have a character portrait + name or not)
// - pause.c (overlaid on top of previous state; manage items/party and quit to main menu)
// - battle.c
// - shop.c

// custom sprites for scene backgrounds, in-scene sprites, and dialogue portraits. tilemap for world map

// Camera2D camera = {0};
// camera.zoom = 1.0f;
// BeginMode2D(camera);
// // draw calls
// EndMode2D();

#include "test.c"

void get_window_letterbox(Rectangle *screen_dest) {

	float screen_ratio = SCREEN_HEIGHT / (float) SCREEN_WIDTH;
	float window_ratio = GetScreenHeight() / (float) GetScreenWidth();

	if (screen_ratio < window_ratio) {

		*screen_dest = (Rectangle) {
			0,
			(GetScreenHeight() - screen_ratio * GetScreenWidth()) / 2,
			GetScreenWidth(),
			screen_ratio * GetScreenWidth()
		};

	} else {

		screen_ratio = SCREEN_WIDTH / (float) SCREEN_HEIGHT;

		*screen_dest = (Rectangle) {
			(GetScreenWidth() - screen_ratio * GetScreenHeight()) / 2,
			0,
			screen_ratio * GetScreenHeight(),
			GetScreenHeight()
		};
	}
}

int main(void) {

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "RPG Project");
	SetTargetFPS(60);
	// GetFrameTime(); // deltaTime

    // screen texture
    RenderTexture2D screen_texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

	Rectangle screen_src = { 0.0f, 0.0f, (float) SCREEN_WIDTH, -(float) SCREEN_HEIGHT }; // texture height is flipped bc OpenGL
	Rectangle screen_dest;
	get_window_letterbox(&screen_dest);

    Vector2 screen_origin = { 0.0f, 0.0f };

	// initial game state
	create_test_game_state(&curr_game_state);

	// game loop
    while (!WindowShouldClose()) {

		if (IsWindowResized())
			get_window_letterbox(&screen_dest);

        // process current state
		curr_game_state.process(&curr_game_state, NULL);

        // draw current state to screen
        BeginTextureMode(screen_texture);
		curr_game_state.draw(&curr_game_state, NULL);
        EndTextureMode();

		// draw screen to window
        BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(screen_texture.texture, screen_src, screen_dest, screen_origin, 0.0f, WHITE);
        EndDrawing();
    }

	// clean up
	curr_game_state.destroy(&curr_game_state, NULL);
    UnloadRenderTexture(screen_texture);
    CloseWindow();

    return 0;
}