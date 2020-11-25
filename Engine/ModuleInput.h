#pragma once
#include <vector>
#include "Module.h"
#include "Globals.h"
#include "Point.h"

#include "SDL/include/SDL_scancode.h"

typedef unsigned __int8 Uint8;

#define NUM_MOUSE_BUTTONS 5

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	void CreateNewModel(char* file);
	bool CleanUp();


	// Getters & Setters
	KeyState GetKey(int id) const { return keyboard[id]; };
	KeyState GetMouseButtonDown(int id) const {return mouse_buttons[id - 1];};
	bool GetWindowEvent(EventWindow code) const { return windowEvents[code]; };
	const iPoint& GetMouseMotion() const { return mouse_motion; };
	const iPoint& GetMousePosition() const { return mouse; };
	const int GetMouseWheel() const { return mouseWheel; };
	void SetMouseWheelTo0() { mouseWheel = 0; };

private:
	bool windowEvents[WE_COUNT];
	KeyState* keyboard;
	KeyState mouse_buttons[NUM_MOUSE_BUTTONS];
	iPoint mouse_motion;
	iPoint mouse;
	int mouseWheel = 0;
};