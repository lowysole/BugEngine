#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		SDL_DisplayMode dm;

		if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
		{
			SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
			return 1;
		}

		currentWidth = &dm.w;
		currentHeight = &dm.h;

		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (SCREEN_RESIZE == true) 
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}
		if (SCREEN_BORDERLESS == true) {

			flags |= SDL_WINDOW_BORDERLESS;
		}

		int offset = 100;
		window = SDL_CreateWindow(TITLE, 0, 0, *currentWidth - offset, *currentHeight - offset, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

update_status ModuleWindow::PreUpdate() {
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

