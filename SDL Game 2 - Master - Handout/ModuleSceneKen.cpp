#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://youtu.be/OEhmUuehGOA?t=72



ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// move_coordinates
	for(int i = 0; i < MOVE_STEPS; i++)
		move_coordinates.frames.push_back({ 0, -i, 0, 0 });
	for (int i = MOVE_STEPS; i > 0 ; i--)
		move_coordinates.frames.push_back({ 0, -i, 0, 0 });
	move_coordinates.speed = 0.01f;

	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// DONE -- TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	ship.x = 8;
	ship.y = 25;
	ship.w = 522;
	ship.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	// DONE -- TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	girl.frames.push_back({ 623, 16, 35, 55 });
	girl.frames.push_back({ 623, 80, 35, 55 });
	girl.frames.push_back({ 623, 144, 35, 55 });
	girl.speed = 0.01f;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// DONE -- TODO 7: Enable the player module
	App->player->Enable();

	// DONE -- TODO 0: trigger background music
	//App->audio->PlayMusic("ken.ogg");
	
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}


// Update: draw background
update_status ModuleSceneKen::Update()
{
	// DONE -- TODO 5: make sure the ship goes up and down
	SDL_Rect current_move_coordinates = move_coordinates.GetCurrentFrame();
	// Draw everything --------------------------------------
	// DONE -- TODO 1: Tweak the parallax movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, 1.1f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 1.1f); // flag animation

	// DONE -- TODO 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(graphics, 0, current_move_coordinates.y, &ship, 1.1f); // ship

	// DONE -- TODO 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(graphics, 192, current_move_coordinates.y + 103, &(girl.GetCurrentFrame()), 1.1f); // girl animation

	App->renderer->Blit(graphics, 0, 170, &ground);

	// WIP --TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// WIP -- TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module

	if (true /*Space button*/) {
		App->fade->FadeToBlack(App->scene_honda, App->scene_ken, 10.0f);
	}

	return UPDATE_CONTINUE;
}