#include "UIInspector.h"
#include "MathGeoLib.h"
#include <math.h>

UIInspector::UIInspector() {

}

void UIInspector::Draw(const char* title, bool* p_open) {

    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::CollapsingHeader("Camera Settings")) {

        //ImGui::DragFloat3("Position", &cameraPosition, 0.2f, 2.0f, 72.0f, "%.0f");
        ImGui::DragFloat("Camera Speed", &cameraSpeed, 0.5f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Angle Speed", &angleSpeed, 0.5f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Zoom Speed (WIP)", &zoomSpeed, 0.2f, 2.0f, 72.0f, "%.4f");
        ImGui::Text("Frustum");
        //ImGui::DragFloat3("Front", &cameraPosition, 0.2f, 2.0f, 72.0f, "%.0f");
        //ImGui::DragFloat3("Up", &cameraPosition, 0.2f, 2.0f, 72.0f, "%.0f");
        ImGui::DragFloat("Near Plane", &nearPlane, 0.1f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Far Plane", &farPlane, 1.0f, 10.0f, 200.0f, "%.2f");
    }
    ImGui::End();

}
