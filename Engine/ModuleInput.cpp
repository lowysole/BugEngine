#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "Model.h"
#include "SDL/include/SDL.h"
#include "ImGui/imgui_impl_sdl.h"
#include "leak.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput()
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system\n");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleInput::PreUpdate() {
	static SDL_Event event;
	mouse_motion = { 0, 0 };
	memset(windowEvents, false, WE_COUNT * sizeof(bool));
	char* droppedFile;

	if (!App->editor->CheckUIInputs()) {
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		for (int i = 0; i < MAX_KEYS; ++i)
		{
			if (keys[i] == 1)
			{
				if (keyboard[i] == KEY_IDLE)
					keyboard[i] = KEY_DOWN;
				else
					keyboard[i] = KEY_REPEAT;
			}
			else
			{
				if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
					keyboard[i] = KEY_UP;
				else
					keyboard[i] = KEY_IDLE;
			}
		}

		for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
		{
			if (mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_REPEAT;

			if (mouse_buttons[i] == KEY_UP)
				mouse_buttons[i] = KEY_IDLE;
		}
	}
	while (SDL_PollEvent(&event) != 0)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);

		if (!App->editor->CheckUIInputs()) {
			switch (event.type)
			{
			case SDL_QUIT:
				windowEvents[WE_QUIT] = true;
				break;

			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
					//case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_FOCUS_LOST:
					windowEvents[WE_HIDE] = true;
					break;

					//case SDL_WINDOWEVENT_ENTER:
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED:
					windowEvents[WE_SHOW] = true;
					break;
				}
				break;

			case SDL_DROPFILE:
				droppedFile = event.drop.file;
				App->model->Load(droppedFile);
				SDL_free(droppedFile);
				break;

			case SDL_MOUSEWHEEL:
				if (event.wheel.y > 0) {
					mouseWheel = 1;
				}
				else if (event.wheel.y < 0) {
					mouseWheel = -1;
				}
				else {
					mouseWheel = 0;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = KEY_DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				mouse_buttons[event.button.button - 1] = KEY_UP;
				break;

			case SDL_MOUSEMOTION:
				mouse_motion.x = event.motion.xrel / SCREEN_SIZE;
				mouse_motion.y = event.motion.yrel / SCREEN_SIZE;
				mouse.x = event.motion.x / SCREEN_SIZE;
				mouse.y = event.motion.y / SCREEN_SIZE;
				break;
			}
		}
	}

	if (GetWindowEvent(EventWindow::WE_QUIT) == true)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem\n");
	RELEASE(keyboard);
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}