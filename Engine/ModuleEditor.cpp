#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "SDL/include/SDL.h"
#include "GL/glew.h"


ModuleEditor::ModuleEditor() {
	modules.push_back(console = new UIConsole());
	modules.push_back(inspector = new UIInspector());
}

bool ModuleEditor::Init() {

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();


	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	return true;
}

update_status ModuleEditor::Update() {

	glViewport(0, 0, *App->window->currentWidth, *App->window->currentHeight );
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	CheckUIWindows();
	UIMainMenuBar();
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp() {

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}

void ModuleEditor::UIMainMenuBar() {

	if(ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Windows")) {

			ImGui::MenuItem("Console", NULL, &showUIConsole);
			ImGui::MenuItem("Inspector", NULL, &showUIInspector);
			ImGui::EndMenu();
		}
		ImGui::MenuItem("About", NULL, &showUIAbout);
		ImGui::EndMainMenuBar();
	}
}

void ModuleEditor::UIAbout(bool* p_open) {

	ImGui::Begin("About", &showUIAbout);
	ImGui::Text("Here we will have About Info");
	ImGui::End();
	
}

void ModuleEditor::CheckUIWindows() {

	if (showUIAbout)			UIAbout(&showUIAbout);
	if (showUIConsole)			console->Draw("Console", &showUIConsole);
	if (showUIInspector)		inspector->Draw("Inspector", &showUIInspector);

}