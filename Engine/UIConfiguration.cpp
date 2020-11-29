#include "UIConfiguration.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "SDL.h"
#include "GL/glew.h"
#include "IL/il.h"
#include "imgui.h"
#include "leak.h"

void UIConfiguration::Draw(const char* title, bool* p_open) {

	// TODO: Create file with common UI features 
	ImVec4 colorTitle = ImVec4(0.35f, 0.69f, 0.87f, 1.0f);
	ImVec4 colorText = ImVec4(0.14f, 0.47f, 0.60f, 1.0f);

	if (!ImGui::Begin(title, p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::Text("Options");

	if (ImGui::CollapsingHeader("Application")) {
		ImGui::Text("Engine name");
		ImGui::SameLine();
		ImGui::TextColored(colorText, TITLE);
		ImGui::Text("Organization");
		ImGui::SameLine();
		ImGui::TextColored(colorText, "UPC TechSchool");
		ImGui::Separator();
		if (ImGui::Button("1s")) {
			time = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("5s")) {
			time = 5;
		}
		ImGui::SameLine();
		if (ImGui::Button("10s")) {
			time = 10;
		}
		ImGui::SameLine();
		if (ImGui::Button("20s")) {
			time = 20;
		}
		App->camera->SetTime(time);
		char name[25];
		sprintf_s(name, 25, "Framerate(FPS) %.1f", App->camera->fpsLog[IM_ARRAYSIZE(App->camera->fpsLog) - 1]);
		ImGui::PlotHistogram("##framerate", &App->camera->fpsLog[0], IM_ARRAYSIZE(App->camera->fpsLog), 0, name, 0.0f, App->camera->GetMaxFPS() + 50, ImVec2(300, 100));
	}

	if (ImGui::CollapsingHeader("System")) {

		SDL_version compiled;
		SDL_VERSION(&compiled);
		GLint vGlMajor;
		GLint vGlMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &vGlMajor);
		glGetIntegerv(GL_MINOR_VERSION, &vGlMinor);
		int devILv = (int)ilGetInteger(IL_VERSION_NUM);
		const char* gpuVendor = (const char*)glGetString(GL_VENDOR);
		const char* gpuRenderer = (const char*)glGetString(GL_RENDERER);
		ImGui::TextColored(colorTitle, "Software ");
		ImGui::Text("SDL Version: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, "%d.%d", compiled.major, compiled.minor);
		ImGui::Text("OpenGL Version: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, "%d.%d", vGlMajor, vGlMinor);
		ImGui::Text("DevIL Version: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, "%d.%d.%d", devILv / 100, devILv / 10 % 10, devILv % 10);
		ImGui::Separator();
		ImGui::TextColored(colorTitle, "Hardware ");
		ImGui::Text("CPUs: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, "%d, (Cache: %d kb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
		ImGui::Text("System RAM: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, "%.2d GB", SDL_GetSystemRAM() / 1024);
		ImGui::Text("");
		ImGui::Text("GPU: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, gpuVendor);
		ImGui::Text("Brand: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, gpuRenderer);
		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Window")) {
		ModuleWindow window = *App->window;
		ImGui::TextColored(colorTitle, "Window Settings");

		if (ImGui::SliderInt("Brightness", &brightness, 0, 100)) {
			App->window->SetBrightness(brightness);
		}
		if (resizable && !borderless) {
			windowWidth = App->window->GetCurrentWidth();
			windowHeight = App->window->GetCurrentHeight();
			if (ImGui::SliderInt("Width", &windowWidth, 800, maxWidth) ||
				ImGui::SliderInt("Heigth", &windowHeight, 600, maxHeight)) {

				SDL_SetWindowSize(App->window->GetWindow(), windowWidth, windowHeight);
			}
		}

		if (ImGui::Checkbox("Fullscreen", &fullscreen)) {

			App->window->SetFullScreen(fullscreen);
		}

		ImGui::SameLine();

		if (!borderless) {

			if (ImGui::Checkbox("Resizable", &resizable)) {
				App->window->SetResizable(resizable);
			}
		}
		else {
			ImGui::TextDisabled("No resizable");
			ImGui::SameLine(); HelpMarker("Option disabled when Borderless activated.");
		}

		if (ImGui::Checkbox("Borderless", &borderless)) {

			App->window->SetBoderless(borderless);
		}

		ImGui::SameLine();

		if (ImGui::Checkbox("Full Desktop", &fullDesktop)) {

			App->window->SetFullDesktop(fullDesktop);
		}
		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Texture")) {


		ImGui::SameLine(); HelpMarker(
			"Drag&drop a FBX file into the Engine to load a new texture.\n"
			"The previous one will be removed.\n"
			"Steps to find the texture:\n"
			"1- First check on the path described in the FBX.\n"
			"2- Check on the same folder you loaded the FBX.\n"
			"3- Check in the folder described in this field.\n"
			"If empty, we will take the path of execution.");
		ImGui::TextWrapped("Default folder");
		ImGui::InputText("##folder", textureFolder, IM_ARRAYSIZE(textureFolder));
		ImGui::SameLine(); HelpMarker("Folder from the texture to load. Format C:\\User\\folder");
		ImGui::TextWrapped("Default extension");
		ImGui::InputText("##ext", textureExt, IM_ARRAYSIZE(textureExt));
		ImGui::SameLine(); HelpMarker("Extension from the texture to load");
		ImGui::Separator();
		ImGui::TextColored(colorTitle, "Texture Filtering");
		ImGui::Combo("Wrap", &wrapCurrent, wrap, IM_ARRAYSIZE(wrap));

		ImGui::Checkbox("Activate Minmap", &minmapActivated);
		if (minmapActivated) {
			ImGui::Combo("Magnification##mag", &magMinmapCurrent, magMinmap, IM_ARRAYSIZE(magMinmap));
			ImGui::Combo("Minification##min", &minMinmapCurrent, minMinmap, IM_ARRAYSIZE(magMinmap));
		}
		else {
			ImGui::Combo("Magnification##mag_minmap", &magnificationCurrent, magnification, IM_ARRAYSIZE(magnification));
			ImGui::Combo("Minification##min_minmap", &minificationCurrent, minification, IM_ARRAYSIZE(minification));
		}
		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Input")) {

		ImGui::TextColored(colorTitle, "Mouse Position");
		ImGui::Text("X: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, "%d", App->input->GetMousePosition().x);
		ImGui::SameLine();
		ImGui::Text(" Y: ");
		ImGui::SameLine();
		ImGui::TextColored(colorText, "%d", App->input->GetMousePosition().y);
		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Render")) {

		ImGui::TextColored(colorTitle, "Background Color");
		ImGui::ColorEdit4("##bg_color", bgColor);
		ImGui::SameLine();
		if (ImGui::Button("Reset##bg_reset")) {
			bgColor[0] = bgColor[1] = bgColor[2] = 0.1f;
			bgColor[3] = 1.0f;
		}
		ImGui::TextColored(colorTitle, "Grid Color");
		ImGui::ColorEdit3("##grid_color", gridColor);
		ImGui::SameLine();
		if (ImGui::Button("Reset##grid_reset")) {
			gridColor[0] = gridColor[1] = gridColor[2] = 0.501961f;
		}
		ImGui::Separator();
	}

	ImGui::End();

}

const char* UIConfiguration::GetMagFilter() const {
	if (minmapActivated)
		return magMinmap[magMinmapCurrent];
	else
		return magnification[magnificationCurrent];
}

const char* UIConfiguration::GetMinFilter() const {
	if (minmapActivated)
		return minMinmap[minMinmapCurrent];
	else
		return minification[minificationCurrent];
}

void UIConfiguration::GetTextureFolder(char* other) {
	for (int i = 0; i < IM_ARRAYSIZE(textureFolder) - 1; i++) {
		other[i] = textureFolder[i];
	}
}

void UIConfiguration::GetTextureExt(char* other) {
	for (int i = 0; i < IM_ARRAYSIZE(textureExt) - 1; i++) {
		other[i] = textureExt[i];
	}
}
