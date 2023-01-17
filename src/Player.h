#pragma once

#include"raylib.h"
#include"Button.h"

class Player {
	Vector2 Position;
	Vector2 Size;

	Texture2D PlayerTexture;

	double PlayerMass = 100;

	// false = left
	// true = right
	bool Facing = false;

	Sound JumpSfx;

	Vector2 PlayerAcceleration;
	Vector2 PlayerVelocity;

	int Floor;

	Vector2 CalculatePhys(Vector2 StartingPosition, Vector2 Size, double g, double Mass, int GroundLevel);
	void MovePlayer(bool Keystates[255], int GroundLevel);
public:
	Player(int FloorHeight);

	void Render();
	void Move(Button *Button1, Button *Button2);
};