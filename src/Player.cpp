#include"Player.h"
#include<iostream>

extern bool Keystates[255];
static const double g = 9.2f;

Player::Player(int FloorHeight) {
	float width = GetScreenWidth();
	float height = GetScreenHeight();

	PlayerTexture = LoadTexture("GameData/Textures/player.png");

	Position = Vector2{ width/2, height/2 };
	Size = Vector2{ height/6, height/6 };

	PlayerAcceleration = Vector2{ 0, 0 };
	PlayerVelocity = Vector2{ 0, 0 };

	JumpSfx = LoadSound("GameData/Audio/jump.wav");
	SetSoundVolume(JumpSfx, 0.1f);

	Floor = FloorHeight;
}

void Player::Render() {
	DrawTexturePro(PlayerTexture, Rectangle{ (float)(Facing ? PlayerTexture.width : 0), 0, (float)(Facing ? -PlayerTexture.width : PlayerTexture.width), (float)PlayerTexture.height },
				   Rectangle{ Position.x, Position.y, Size.x, Size.y }, Vector2{ Size.x/2, Size.y/2 }, 0.0f,
				   RAYWHITE);
}

#include"Button.h"

void Player::Move(Button *Button1, Button *Button2) {
	Position = CalculatePhys(Position, Size, g, PlayerMass, Floor);
	Player::MovePlayer(Keystates, Floor);

	Button1->CanClick(Position);
	Button2->CanClick(Position);
}

Vector2 Player::CalculatePhys(Vector2 StartingPosition, Vector2 Size, double g, double Mass, int GroundLevel) {
	double DeltaTime = GetFrameTime();
	
	// f.y = mg
	PlayerAcceleration.y = (Mass * g)/100;
	// Use x acceleration to simulate friction
	PlayerAcceleration.x = StartingPosition.y + Size.y/2 == GroundLevel ? PlayerVelocity.x * -0.05 : PlayerVelocity.x * -0.01;

	PlayerVelocity.x += PlayerAcceleration.x;
	PlayerVelocity.y += PlayerAcceleration.y;

	StartingPosition.x += PlayerVelocity.x * DeltaTime;
	StartingPosition.y += PlayerVelocity.y * DeltaTime;

	if (StartingPosition.y > GroundLevel - Size.y/2) {
		StartingPosition.y = GroundLevel - Size.y/2;
		PlayerVelocity.y = 0;
	}

	if (StartingPosition.x - Size.y/2 < 0) {
		PlayerVelocity.x *= -0.5;
		StartingPosition.x = Size.y/2;
	}
	if (StartingPosition.x + Size.y/2 > GetScreenWidth()) {
		PlayerVelocity.x *= -0.5;
		StartingPosition.x = GetScreenWidth() - Size.y/2;
	}
	return StartingPosition;
}

void Player::MovePlayer(bool Keystates[255], int GroundLevel) {
	// std::cout << "called\n";
	// if (Keystates[KEY_SPACE] && Position.y - Size.y/2 != GroundLevel) PlayerVelocity.y += -100;
	// if (Keystates[KEY_A]) PlayerVelocity.x -= 10;
	// if (Keystates[KEY_D]) PlayerVelocity.y += 10;
	if (IsKeyDown(KEY_SPACE) && Position.y + Size.y/2 == GroundLevel) { PlayerVelocity.y += -400; PlaySound(JumpSfx); }
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) return;
	if (IsKeyDown(KEY_A)) {PlayerVelocity.x -= 10; Facing = false; }
	if (IsKeyDown(KEY_D)) {PlayerVelocity.x += 10; Facing = true; }
}