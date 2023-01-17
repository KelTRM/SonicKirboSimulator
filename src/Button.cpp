#include"Button.h"
#include<cmath>

Button::Button(int x, int y, std::string Label, std::string ButtonName) {
	ButtonPosition = Vector2{ (float)x, (float)y };
	// Size = Vector2{ 150, 300 };
	Size = Vector2{ 492/2, 553/2 };

	ButtonLabel = Label;
	Filename = "GameData/Textures/btn_" + ButtonName + ".png";
	texture = LoadTexture(Filename.c_str());
}

int PythagTimes = 0;

double Pythag(Vector2 a, Vector2 b) {
	double lx = b.x - a.x;
	double ly = b.y - a.y;


	double dist = sqrt((lx*lx) + (ly*ly));

	return dist;
}

#define MAX_CLICK_DISTANCE	300.0f

static Font ComicSans = LoadFont("C:\\Windows\\Fonts\\comic.tff");

#define min(x, y) (x > y ? y : x)

bool Button::CanClick(Vector2 pos) {
	const int width = GetScreenWidth();
	const int height = GetScreenHeight();

	if (Pythag(pos, ButtonPosition) < MAX_CLICK_DISTANCE) {
		float x = min(ButtonPosition.x - Size.x/2, width-500);
		DrawRectangleRounded(Rectangle{ x, ButtonPosition.y - Size.y/3, 500, 100 },
							 0.6f, 100, BLACK);

		DrawTextEx(ComicSans, ButtonLabel.c_str(), Vector2{ x, ButtonPosition.y - Size.y/3 }, 100.0f, 1, WHITE);

		return true;
	}
	return false;
};

void Button::Render() {
	DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
				   Rectangle{ ButtonPosition.x, ButtonPosition.y, Size.x, Size.y }, Vector2{ Size.x/2, Size.y/2 }, 0.0f, RAYWHITE);
}