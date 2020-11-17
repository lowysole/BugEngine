#pragma once
#include "imgui.h"
#include "UI.h"

class UIConfiguration : public UI
{
public:
	void Draw(const char* title, bool* p_open);
private:

	// Window
	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
	bool fullDesktop = false;
	int brightness = 100;

};

