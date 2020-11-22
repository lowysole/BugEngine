#include "UIInspector.h"
#include "MathGeoLib.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "Model.h"
#include "imgui.h"
#include <math.h>
#include <vector>

UIInspector::UIInspector() {

}

void UIInspector::Draw(const char* title, bool* p_open) {

    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::CollapsingHeader("Camera Settings")) {

        ImGui::Text("Transformation");
        ImGui::SameLine();
        if (ImGui::Button("Blabla")) {
            //TODO
        }
        ImGui::Separator();
        ImGui::Text("Movement Settings");
        ImGui::SameLine();
        if(ImGui::Button("Reset")){
            cameraSpeed = 3.0f;
            angleSpeed = 2.0f;
            zoomSpeed = 10.0f;
            nearPlane = 0.1f;
            farPlane = 30.f;
            App->camera->ResetVFOV();
        }

        ImGui::DragFloat("Camera Speed", &cameraSpeed, 0.5f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Angle Speed", &angleSpeed, 0.5f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Zoom Speed", &zoomSpeed, 0.2f, 5.0f, 15.0f, "%.2f");
        ImGui::Text("Frustum");
        //ImGui::DragFloat3("Front", &cameraPosition, 0.2f, 2.0f, 72.0f, "%.0f");
        //ImGui::DragFloat3("Up", &cameraPosition, 0.2f, 2.0f, 72.0f, "%.0f");
        ImGui::DragFloat("Near Plane", &nearPlane, 0.1f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Far Plane", &farPlane, 1.0f, 10.0f, 200.0f, "%.2f");
        ImGui::Separator();
    }

    if (ImGui::CollapsingHeader("Model Information")) {
        std::vector<Mesh*> meshes = App->model->GetMeshes();
        int count = 0;
        for (std::vector<Mesh*>::iterator it= meshes.begin(); it != meshes.end(); it++){

            float4x4 model = (*it)->GetModelMatrix();
            float3 pos3 = App->camera->GetModelPosition(model);
            float pos[] = { pos3[0], pos3[1], pos3[2] };
            float3 scale3 = App->camera->GetModelScale(model);
            float scale[] = { scale3[0], scale3[1], scale3[2] };
            float3 rotation3 = App->camera->GetModelRotation(model);
            float rotation[] = { rotation3[0], -rotation3[1], rotation3[2] };
                               
            char name[10];
            sprintf_s(name, 10, "Mesh %d", count);
            char nVertices[5];
            sprintf_s(nVertices, 5, "%d", (*it)->GetNumVertices());
            char nFaces[5];
            sprintf_s(nFaces, 5, "%d", (*it)->GetNumFaces());

            if (ImGui::TreeNode(name)) {

                ImGui::TextWrapped("Transformation (X,Y,Z)");
                ImGui::InputFloat3("Position", pos);
                ImGui::InputFloat3("Scale", scale);
                ImGui::InputFloat3("Rotation", rotation);
                ImGui::Separator();
                ImGui::TextWrapped("Geometry");
                ImGui::LabelText("Num Vertices", nVertices);
                ImGui::LabelText("Num Triangles", nFaces);
                ImGui::Separator();
                ImGui::TextWrapped("Texture:");
                ImGui::Image((void*)App->model->GetMaterials()[(*it)->GetMaterialIndex()], ImVec2(200,200));
                ImGui::Separator();
                ImGui::TreePop();
            }
            count++;
        }

    
    }
    ImGui::End();

}
