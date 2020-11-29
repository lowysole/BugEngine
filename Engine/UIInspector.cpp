#include "UIInspector.h"
#include "MathGeoLib.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "Model.h"
#include "imgui.h"
#include <math.h>
#include <vector>
#include "leak.h"

void UIInspector::Draw(const char* title, bool* p_open) {

    // TODO: Create file with common UI features 
    ImVec4 color = ImVec4(0.35f, 0.69f, 0.87f, 1.0f);

    float3 cameraPos = App->camera->GetPosition();
    cameraPosition[0] = cameraPos.x;
    cameraPosition[1] = cameraPos.y;
    cameraPosition[2] = cameraPos.z;
    float2 cameraRotation = App->camera->GetAnglesRotation() * RADTODEG;
    cameraPitch = cameraRotation.x;
    cameraYaw = cameraRotation.y;
    if (cameraYaw > 180) cameraYaw = cameraYaw - 360;
    if (cameraYaw < -180) cameraYaw = cameraYaw + 360;

    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::CollapsingHeader("Camera Settings")) {

        ImGui::TextColored(color, "Transformation");
        ImGui::DragFloat3("Position", cameraPosition, 0.1f, -inf, +inf, "%.2f");
        ImGui::DragFloat("Pitch", &cameraPitch, 0.5f, -89.0f, +89.0f, "%.2f");
        ImGui::DragFloat("Yaw", &cameraYaw, 0.5f, -inf, +inf, "%.2f");
        ImGui::Separator();
        ImGui::TextColored(color, "Movement Settings");
        ImGui::SameLine();
        if(ImGui::Button("Reset")){
            cameraSpeed = 3.0f;
            angleSpeed = 2.0f;
            zoomSpeed = 10.0f;
            nearPlane = 0.1f;
            farPlane = 30.f;
            App->camera->ResetVFOV();
        }


        float3 frustumFront = App->camera->GetFrustumFront();
        float frustumFrontArray[] = {frustumFront.x, frustumFront.y, frustumFront.z};
        float3 frustumUp = App->camera->GetFrustumUp();
        float frustumUpArray[] = { frustumUp.x, frustumUp.y, frustumUp.z };
        float vFov = App->camera->GetFOV() * 180/pi;
        ImGui::DragFloat("Camera Speed", &cameraSpeed, 0.5f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Angle Speed", &angleSpeed, 0.5f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Zoom Speed", &zoomSpeed, 0.2f, 5.0f, 15.0f, "%.2f");
        ImGui::TextColored(color, "Frustum");
        ImGui::InputFloat3("Front", frustumFrontArray);
        ImGui::InputFloat3("Up", frustumUpArray);
        ImGui::DragFloat("Near Plane", &nearPlane, 0.1f, 0.0f, 10.0f, "%.2f");
        ImGui::DragFloat("Far Plane", &farPlane, 1.0f, 10.0f, 200.0f, "%.2f");
        ImGui::InputFloat("vFOV", &vFov, 0.0F, 0.0F, "%.2f");
        ImGui::Separator();
    }

    if(cameraPos.x != cameraPosition[0] && cameraPos.y != cameraPosition[1] && cameraPos.z != cameraPosition[2])
        App->camera->SetPosition(float3(cameraPosition[0], cameraPosition[1], cameraPosition[2]));

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

                ImGui::TextColored(color, "Transformation (X,Y,Z)");
                ImGui::InputFloat3("Position", pos);
                ImGui::InputFloat3("Scale", scale);
                ImGui::InputFloat3("Rotation", rotation);
                ImGui::Separator();
                ImGui::TextColored(color, "Geometry");
                ImGui::TextWrapped("Num Vertices:   %d", nVertices);
                ImGui::TextWrapped("Num Triangles:   %d", nFaces);
                ImGui::Separator();
                ImGui::TextColored(color, "Texture");
                ImGui::TextWrapped("Path: ");
                ImGui::SameLine();
                ImGui::TextWrapped(App->model->GetTexturePath().c_str());
                ImGui::TextWrapped("Size: ");
                ImGui::SameLine();
                ImGui::TextWrapped("%d x %d", App->model->GetTextureWidth(), App->model->GetTextureHeight());
                ImGui::Image((void*)App->model->GetMaterials()[(*it)->GetMaterialIndex()], ImVec2(200,200));
                ImGui::Separator();
                ImGui::TreePop();
            }
            count++;
        }
    }
    ImGui::End();

}
