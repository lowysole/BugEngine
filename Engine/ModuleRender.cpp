#include "ModuleRender.h"
#include "Application.h"
#include "ModuleProgram.h" 
#include "ModuleTexture.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "GL/glew.h"
#include "SDL.h"
#include "Geometry/Frustum.h"
#include "debugdraw.h" 

bool ModuleRender::Init() {

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

#ifdef DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
#endif // DEBUG

	context = SDL_GL_CreateContext(App->window->window);
	GLenum err = glewInit();
	vbo1 = CreateTriangleVBO();

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

	RenderVBO(vbo1, program_id);

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate() {
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}


void ModuleRender::RenderVBO(unsigned vbo, unsigned program)
{

	float4x4 model, view, projection;
	// TODO: retrieve model view and projection
	view = App->camera->GetViewMatrix();
	projection = App->camera->GetProjectionMatrix();
	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), float4x4::RotateZ(pi / 4), float3(2.0f, 1.0f, 1.0f));

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projection[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 6));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, App->texture->GetImage());
	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);
}

unsigned ModuleRender::CreateTriangleVBO()
{
	float vtx_data[] = { 0.0f, 0.0f, 0.0f, // ← v0 pos
						1.0f, 0.0f, 0.0f, // ← v1 pos
						0.5f, 1.0f, 0.0f, // ← v2 pos
						1.0f, 0.0f, 0.0f, // ← v1 pos
						0.0f, 0.0f, 0.0f, // ← v0 pos
						0.5f, -1.0f, 0.0f, // ← v3 pos
						0.0f, 1.0f, // ← v0 texcoord
						1.0f, 0.0f, // ← v1 texcoord
						0.0f, 0.0f, // ← v2 texcoord
						1.0f, 0.0f, // ← v0 texcoord
						0.0f, 1.0f, // ← v2 texcoord
						1.0f, 1.0f, // ← v1 texcoord
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
	return vbo;
}

void ModuleRender::DestroyVBO(unsigned vbo)
{
	glDeleteBuffers(1, &vbo);
}

bool ModuleRender::CleanUp() {
	DestroyVBO(vbo1);

	return true;
}

static void APIENTRY openglCallbackFunction(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
) {
	(void)source; (void)type; (void)id;
	(void)severity; (void)length; (void)userParam;
	fprintf(stderr, "%s\n", message);
	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		fprintf(stderr, "Aborting...\n");
		abort();
	}
}
