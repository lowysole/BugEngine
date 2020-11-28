#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"
#include "UIConfiguration.h"


bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface\n");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {

		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else {

		SDL_DisplayMode dm;

		if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {

			SDL_Log("SDL_GetDesktopDisplayMode failed: %s\n", SDL_GetError());
			return 1;
		}

		currentWidth = &dm.w;
		currentHeight = &dm.h;
		App->editor->config->SetMaxWidht(*currentWidth);
		App->editor->config->SetMaxHeight(*currentHeight);

		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(fullscreen == true) {

			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (resizable == true) {

			flags |= SDL_WINDOW_RESIZABLE;
		}
		if (borderless == true) {

			flags |= SDL_WINDOW_BORDERLESS;
		}
		if (fullDesktop == true) {

			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, 0, 0, *currentWidth * 0.8, *currentHeight * 0.8, flags);

		if(window == NULL) {

			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else {

			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

void ModuleWindow::SetFullScreen(bool flag) {

	if (flag)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(window, 0);
	fullscreen = flag;
}

void ModuleWindow::SetResizable(bool flag) {

	SDL_SetWindowResizable(window, (SDL_bool)flag);
	resizable = flag;
}

void ModuleWindow::SetBoderless(bool flag) {
	
	SDL_SetWindowBordered(window, (SDL_bool)!flag);
	borderless = !flag;
}
void ModuleWindow::SetFullDesktop(bool flag) {

	if (flag)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(window, 0);
	fullDesktop = flag;
}

void ModuleWindow::SetBrightness(int value) {

	SDL_SetWindowBrightness(window, (float)value / 100);
}

bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems\n");

	//Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}