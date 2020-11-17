#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include <vector>
#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	bool Init();
	void SetFullScreen(bool flag);
	void SetResizable(bool flag);
	void SetBoderless(bool flag);
	void SetFullDesktop(bool flag);
	void SetBrightness(int value);
	bool CleanUp();



public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	int* currentWidth;
	int* currentHeight;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;

private:
	bool fullscreen = false;
	bool resizable = false;
	bool borderless = false;
	bool fullDesktop = false;

};

#endif // __ModuleWindow_H__