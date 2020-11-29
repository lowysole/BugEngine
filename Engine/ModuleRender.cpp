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
#include "leak.h"

bool ModuleRender::Init() {

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	context = SDL_GL_CreateContext(App->window->GetWindow());
	GLenum err = glewInit();

	return true;
}

update_status ModuleRender::PreUpdate() {
	int w = App->window->GetCurrentWidth();
	int h = App->window->GetCurrentHeight();
	SDL_GetWindowSize(App->window->GetWindow(), &w, &h);
	App->window->SetCurrentWidth(w);
	App->window->SetCurrentHeight(h);
	float4 bgColor = App->editor->config->GetBgColor();
	glClearColor(bgColor.x,  bgColor.y, bgColor.z, bgColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

update_status ModuleRender::Update() {

	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-50, 50, 0.0f, 1.0f, App->editor->config->GetGridColor());
	App->debug_draw->Draw(App->camera->GetViewMatrix(),
		App->camera->GetProjectionMatrix(),
		App->window->GetCurrentWidth(),
		App->window->GetCurrentHeight());

	unsigned programId = App->program->GetProgramId();

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate() {

	SDL_GL_SwapWindow(App->window->GetWindow());
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp() {

	return true;
}