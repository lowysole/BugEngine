#pragma once
#include <vector>
#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	bool Init();
	bool CleanUp();

	void SetFullScreen(bool flag);
	void SetResizable(bool flag);
	void SetBoderless(bool flag);
	void SetFullDesktop(bool flag);
	void SetBrightness(int value);

	//Getters & Setters
	SDL_Window* GetWindow() const { return window; };
	int GetCurrentWidth() const { return currentWidth; };
	void SetCurrentWidth(int other) { currentWidth = other;  };
	int GetCurrentHeight() const { return currentHeight; };
	void SetCurrentHeight(int other) { currentHeight = other; };

private:

	SDL_Window* window = NULL;
	int currentWidth;
	int currentHeight;
	SDL_Surface* screen_surface = NULL;
	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
	bool fullDesktop = true;

};