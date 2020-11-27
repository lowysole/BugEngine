#include "UIConfiguration.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "SDL.h"
#include "GL/glew.h"
#include "IL/il.h"
#include "imgui.h"


void UIConfiguration::Draw(const char* title, bool* p_open) {

    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }
    ImGui::Text("Options");


    if (ImGui::CollapsingHeader("Window")) {
        ModuleWindow window = *App->window;
        ImGui::Text("Window Settings");

        if (ImGui::SliderInt("Brightness", &brightness, 0, 100)) {
            App->window->SetBrightness(brightness);
        }
        if (resizable) {
            windowWidth = App->window->GetCurrentWidth();
            windowHeight = App->window->GetCurrentHeight();
            if (ImGui::SliderInt("Width", windowWidth, 800, maxWidth) || 
                ImGui::SliderInt("Heigth", windowHeight, 600, maxHeight)) {

                SDL_SetWindowSize(App->window->GetWindow(), *windowWidth, *windowHeight);
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

            App->window->SetFullDesktop(fullscreen);
        }
    }

    if (ImGui::CollapsingHeader("Application")) {
        ImGui::Text("Engine name");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), TITLE);
        ImGui::Text("Organization");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), "UPC TechSchool");
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
        ImGui::PlotHistogram("##framerate", &App->camera->fpsLog[0], IM_ARRAYSIZE(App->camera->fpsLog), 0, name, 0.0f, App->camera->GetMaxFPS() +50 , ImVec2(300,100));
    }

    if (ImGui::CollapsingHeader("System")) {

        //TODO: Completes
        SDL_version compiled;
        SDL_VERSION(&compiled);
        GLint vGlMajor;
        GLint vGlMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &vGlMajor);
        glGetIntegerv(GL_MINOR_VERSION, &vGlMinor);
        int devILv = (int)ilGetInteger(IL_VERSION_NUM);
        const char* gpuVendor = (const char*) glGetString(GL_VENDOR);
        const char* gpuRenderer = (const char*)glGetString(GL_RENDERER);
        ImGui::Text("Software ");
        ImGui::Text("SDL Version: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), "%d.%d", compiled.major, compiled.minor);
        ImGui::Text("OpenGL Version: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), "%d.%d", vGlMajor, vGlMinor);
        ImGui::Text("DevIL Version: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), "%d.%d.%d", devILv/100, devILv/10%10, devILv%10);
        ImGui::Separator();
        ImGui::Text("Hardware ");
        ImGui::Text("CPUs: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), "%d, (Cache: %d kb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize() );
        ImGui::Text("System RAM: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), "%.2d GB", SDL_GetSystemRAM()/1024);
        ImGui::Separator();
        ImGui::Text("GPU: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), gpuVendor);
        ImGui::Text("Brand: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.14f, 0.47f, 0.60f, 1.0f), gpuRenderer);
        ImGui::Separator();

    }
    if (ImGui::CollapsingHeader("Texture Configuration")) {
        ImGui::SameLine(); HelpMarker(
            "Drag&drop a FBX file into the Engine to load a new texture.\n"
            "The previous one will be removed.\n"
            "Steps to find the texture:\n"
            "1- First check on the path described in the FBX.\n"
            "2- Check on the same folder you loaded the FBX.\n"
            "3- Check in the folder described in this field.\n"
            "If empty, we will take the path of execution.");
        ImGui::TextWrapped("Default folder");
        ImGui::InputText("", textureFolder, IM_ARRAYSIZE(textureFolder));
        ImGui::SameLine(); HelpMarker("Folder from the texture to load. Format C:\\User\\folder");
        ImGui::TextWrapped("Default extension");
        ImGui::InputText(" ", textureExt, IM_ARRAYSIZE(textureExt)); 
        ImGui::SameLine(); HelpMarker("Extension from the texture to load");
    }
    ImGui::End();
}

void UIConfiguration::GetTextureFolder(char* other) {
    for (int i = 0; i < IM_ARRAYSIZE(textureFolder) -1 ; i++) {
        other[i] = textureFolder[i];
    }
}

void UIConfiguration::GetTextureExt(char* other) {
    for (int i = 0; i < IM_ARRAYSIZE(textureExt) - 1; i++) {
        other[i] = textureExt[i];
    }
}
