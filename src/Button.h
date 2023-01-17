#pragma once

#include"raylib.h"
#include<string>

class Button {
	Vector2 ButtonPosition;
	Vector2 Size;

	std::string Filename;
	std::string ButtonLabel;

	Texture2D texture;
public:
	Button(int x, int y, std::string Label, std::string ButtonName);

	bool CanClick(Vector2 Position);
	void Render();
};