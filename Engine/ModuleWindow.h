#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include <vector>
#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();
	SDL_Window* GetWindow() const { return window; };

	//std::vector<int*> GetWindowsSize() const { return std::vector<int*>(&w, &h); };
	//void SetWindowsSize(int* w1, int* h1) { *w= *w1 , *h = *h1; };

public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;
};

#endif // __ModuleWindow_H__