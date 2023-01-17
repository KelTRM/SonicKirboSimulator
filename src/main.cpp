#include<iostream>
#include"raylib.h"

#include<thread>

#include"Player.h"
#include"Button.h"

bool Keystates[255];

int main() {
	const int small_width = 800;
	const int small_height = 600;

	const int width = 1920;
	const int height = 1080;

	SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(width, height, "SonicKirbo Simulator");
	InitAudioDevice();
	SetTargetFPS(60);

	time_t OpenTime = time(NULL);

	Player *player = new Player(height-height/6);
	Texture2D Background = LoadTexture("GameData/Textures/bg.png");

	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawText("Loading...", width/2, height/2, 100, BLACK);
	EndDrawing();

	Music GameMusic = LoadMusicStream("GameData/Audio/music.wav");
	SetMusicVolume(GameMusic, 0.2f);
	PlayMusicStream(GameMusic);
	SetMusicPitch(GameMusic, 2.0f);

	Button *ButtonDoSomething = new Button(250, (height - height/6)-150, "Do nothing", "do_nthing");
	Button *ButtonDoNothing = new Button(1920-75-250, (height - height/6)-150, "Do Something", "do_smthng");

	while (!WindowShouldClose()) {
		UpdateMusicStream(GameMusic);
		for (int i = 0; i < 255; i++) {
			Keystates[i] = IsKeyDown(i);
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawTexturePro(Background, Rectangle{ 0, 0, (float)Background.width, (float)Background.height }, Rectangle{ 0, 0, width, height }, Vector2{ 0, 0 }, 0.0f, RAYWHITE);
		player->Render();
		player->Move(ButtonDoSomething, ButtonDoNothing);

		ButtonDoNothing->Render();
		ButtonDoSomething->Render();

		EndDrawing();
	}

	CloseWindow();
}