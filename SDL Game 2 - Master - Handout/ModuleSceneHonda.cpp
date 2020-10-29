#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{

	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// roof
	roof.x = 8;
	roof.y = 25;
	roof.w = 522;
	roof.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// bath
	bath.x = 72;
	bath.y = 208;
	bath.w = 768;
	bath.h = 176;
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage.png");

	App->player->Enable();
	//App->audio->PlayMusic("honda.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	App->renderer->Blit(graphics, 0, 0, &background); // wall
	App->renderer->Blit(graphics, 0, 0, &ground); // ground
	App->renderer->Blit(graphics, 192, 0, &roof); // roof
	App->renderer->Blit(graphics, 0, 170, &bath); // bath

	return UPDATE_CONTINUE;
}