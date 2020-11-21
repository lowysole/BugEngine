#pragma once
#include "UI.h"

class UIConfiguration : public UI
{
public:

	void Draw(const char* title, bool* p_open);
	void SetMaxWidht(int widht) { maxWidth = widht; };
	void SetMaxHeight(int height) { maxHeight = height; };

private:

	// Window
	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
	bool fullDesktop = false;
	int brightness = 100;
	int* windowWidth;
	int maxWidth = 0;
	int* windowHeight;
	int maxHeight = 0;
};

