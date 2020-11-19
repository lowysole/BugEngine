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
	modules.push_back(config = new UIConfiguration());
}

bool ModuleEditor::Init() {

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();


	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	return true;
}

update_status ModuleEditor::Update() {

	if (exit) {
		return UPDATE_STOP;
	}

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
	//delete &modules;
	return true;
}

void ModuleEditor::UIMainMenuBar() {

	if(ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("Menu")) {

			if (ImGui::MenuItem("GitHub")) {
				ShellExecuteA(NULL, "open", "https://github.com/lowysole/master_exercises/tree/main/Engine", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::Separator();
			ImGui::MenuItem("Quit", NULL, &exit);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Windows")) {

			ImGui::MenuItem("Configuration", NULL, &showUIConfig);
			ImGui::MenuItem("Inspector", NULL, &showUIInspector);
			ImGui::MenuItem("Console", NULL, &showUIConsole);
			ImGui::EndMenu();
		}
		ImGui::MenuItem("About", NULL, &showUIAbout);
		ImGui::EndMainMenuBar();
	}
}

void ModuleEditor::UIAbout(bool* p_open) {

	ImGui::Begin("About", &showUIAbout);
	ImGui::TextWrapped(TITLE " v1.0" );
	ImGui::Separator();
	ImGui::Text(u8"By Llorenç (Lowy) Solé.");
	ImGui::TextWrapped("Engine developed during the Master in Advanced Programming for AAA Video Games by UPC.");
	ImGui::TextWrapped("Bug Engine licensed under the MIT License.");
	ImGui::Separator();

	static bool showLibrary = false;
	ImVec2 child_size = ImVec2(0, ImGui::GetTextLineHeightWithSpacing()*6);

	ImGui::Checkbox("Libraries", &showLibrary);
	if (showLibrary){

		ImGui::BeginChildFrame(ImGui::GetID("cfg_infos"), child_size);
		ImGui::Text("MathGeoLib v1.5 ");
		ImGui::Text("Simple DirectMedia Layer (SDL) v2.0");
		ImGui::Text("ImGui Docking");
		ImGui::Text("OpenGL Extension Wrangler Library 2.1.0");
		ImGui::Text("DevIL 1.8.0");
		ImGui::Text("Assimp 1.4.1");

		ImGui::EndChildFrame();
	}
	ImGui::End();
	
}

void ModuleEditor::CheckUIWindows() {

	if (showUIAbout)			UIAbout(&showUIAbout);
	if (showUIConsole)			console->Draw("Console", &showUIConsole);
	if (showUIInspector)		inspector->Draw("Inspector", &showUIInspector);
	if (showUIConfig)			config->Draw("Configuration", &showUIConfig);

}