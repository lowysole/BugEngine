#include "UIConfiguration.h"
#include "Application.h"
#include "ModuleWindow.h"

void UIConfiguration::Draw(const char* title, bool* p_open) {

    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }
    ImGui::Text("Options");


    if (ImGui::CollapsingHeader("Window")) {

        ImGui::Text("Window Settings");

        if (ImGui::SliderInt("Brightness", &brightness, 0, 100)) {
            App->window->SetBrightness(brightness);
        }
        // TODO: Add weight and height

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

        ImGui::Text("Here will App info");
        //TODO: Complete
    }

    if (ImGui::CollapsingHeader("Hardware")) {

        ImGui::Text("Here will hardware config");
        //TODO: Complete
    }
    ImGui::End();


}
