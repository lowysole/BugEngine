#include "ModuleRender.h"
#include "Application.h"
#include "ModuleProgram.h" 
#include "ModuleTexture.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "Model.h"
#include "GL/glew.h"
#include "SDL.h"
#include "Geometry/Frustum.h"
#include "debugdraw.h" 

bool ModuleRender::Init() {

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	context = SDL_GL_CreateContext(App->window->window);
	GLenum err = glewInit();

	return true;
}

update_status ModuleRender::PreUpdate() {

	ModuleWindow* window = App->window;
	SDL_GetWindowSize(window->window, window->currentWidth, window->currentHeight);
	//glViewport(0, 0, 640, 480);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

update_status ModuleRender::Update() {

	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-50, 50, 0.0f, 1.0f, dd::colors::Gray);
	App->debug_draw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMatrix(), *App->window->currentWidth, *App->window->currentHeight);

	unsigned program_id = App->program->GetProgramId();

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate() {

	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp() {

	return true;
}