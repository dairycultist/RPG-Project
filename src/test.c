
// GetFrameTime(); // deltaTime

// custom sprites for scene backgrounds, in-scene sprites, and dialogue portraits. tilemap for world map

// Camera2D camera = {0};
// camera.zoom = 1.0f;
// BeginMode2D(camera);
// // draw calls
// EndMode2D();

void test_process(GameState *self, SaveState *save) {

}

void test_draw(GameState *self, SaveState *save) {

	ClearBackground(RAYWHITE);

	DrawText("test", 10, 10, 20, LIGHTGRAY);

	DrawTexture(*(Texture2D *) self->data, 0, 0, WHITE);
}

void test_destroy(GameState *self, SaveState *save) {

	UnloadTexture(*(Texture2D *) self->data);
}

void create_test_game_state(GameState *game_state) {

	game_state->process = test_process;
	game_state->draw = test_draw;
	game_state->destroy = test_destroy;

	game_state->data = malloc(sizeof(Texture2D));
	*(Texture2D *) game_state->data = LoadTexture("src/zombie.png");

	game_state->draws_over_prev_state = false;
}