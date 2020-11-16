#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleCamera;
class ModuleProgram;
class ModuleTexture;
class ModuleEditor;
class ModuleDebugDraw;
class Model;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleProgram* program = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleDebugDraw* debug_draw = nullptr;
	Model* model = nullptr;


private:

	std::list<Module*> modules;

};

extern Application* App;
