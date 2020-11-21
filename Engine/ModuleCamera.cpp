#include <algorithm>
#include "Globals.h"
#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h" 
#include "ModuleEditor.h"
#include "UIInspector.h"


ModuleCamera::ModuleCamera() {

}

bool ModuleCamera::Init() {
	
	clock = Clock();
	GetUIInformation();
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);
	frustum.SetPos(float3(cameraPosition));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	projectionGL = frustum.ProjectionMatrix();
	viewMatrix = frustum.ViewMatrix();

	return true;
}

update_status ModuleCamera::PreUpdate() {
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update() 
{

	float currentTime = clock.Time();
	deltaTime = (currentTime - previousTime) / 1000.0;
	previousTime = currentTime;

	GetUIInformation();
	SetAspectRatio();
	SetFOV();
	
	frustum.SetPos(cameraPosition);
	ModifyCameraSpeed();
	MoveHoritzontalPlane();
	MoveVerticalAxis();


	RotateCamera();
	projectionGL = frustum.ProjectionMatrix();
	viewMatrix = frustum.ViewMatrix();

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModuleCamera::SetFOV() {

	frustum.SetVerticalFovAndAspectRatio(DEGTORAD * 90.0f, aspectRatio);
}

void ModuleCamera::SetAspectRatio() {
	aspectRatio = (float)*App->window->GetCurrentWidth() / (float)*App->window->GetCurrentHeight();
}

void ModuleCamera::MoveHoritzontalPlane() {
	float shift = deltaTime * cameraSpeed;
	if (App->input->GetKey(SDL_SCANCODE_W)) {

		cameraPosition = frustum.Front() * shift + cameraPosition;
	}
	if (App->input->GetKey(SDL_SCANCODE_S)) {
		cameraPosition = -frustum.Front() * shift + cameraPosition;
	}
	if (App->input->GetKey(SDL_SCANCODE_A)) {
		cameraPosition = -frustum.WorldRight() * shift + cameraPosition;
	}
	if (App->input->GetKey(SDL_SCANCODE_D)) {
		cameraPosition = frustum.WorldRight() * shift + cameraPosition;
	}
}

void ModuleCamera::MoveVerticalAxis() {
	float shift = deltaTime * cameraSpeed;
	if (App->input->GetKey(SDL_SCANCODE_Q)) {
		cameraPosition = float3::unitY * shift + cameraPosition;
	}
	if (App->input->GetKey(SDL_SCANCODE_E)) {
		cameraPosition = -float3::unitY * shift + cameraPosition;
	}
}

void ModuleCamera::RotateCamera() {
	float angleShift = deltaTime * angleSpeed;
	float aX = 0, aY = 0;
	float3x3 rotationMatrix;

	if (App->input->GetKey(SDL_SCANCODE_UP)) {
		aX = -angleShift;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
		aX = angleShift;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT)) {
		aY = angleShift;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT)) {
		aY = -angleShift;
	}

	// Check Vertical Clamp
	angleX += aX;
	angleY += aY;
	if (angleX >= 1.553343) {
		angleX = 1.553343;
		aX = 0;
	}
	else if(angleX <= -1.553343){
		angleX = -1.553343;
		aX = 0;
	}

	vec oldUp = frustum.Up().Normalized();
	vec oldFront = frustum.Front().Normalized();
	frustum.SetUp(rotationMatrix.RotateY(aY) * oldUp);
	frustum.SetFront(rotationMatrix.RotateY(aY) * oldFront);
	oldUp = frustum.Up().Normalized();
	oldFront = frustum.Front().Normalized();
	frustum.SetUp(rotationMatrix.RotateAxisAngle(- frustum.WorldRight(), aX) * oldUp);
	frustum.SetFront(rotationMatrix.RotateAxisAngle(-frustum.WorldRight(), aX) * oldFront);
}

void ModuleCamera::ModifyCameraSpeed(){
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT)) {
		cameraSpeed *= 2;
		angleSpeed *= 2;
		// TODO: Print updated velocity
	}
}

void ModuleCamera::GetUIInformation() {
	UIInspector* inspector = App->editor->inspector;
	cameraSpeed = inspector->GetCameraSpeed();
	angleSpeed = inspector->GetAngleSpeed();
	float nPlan = inspector->GetNearPlane();
	float fPlan = inspector->GetFarPlane();
	nearPlane = nPlan;
	farPlane = fPlan;
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
}

float3 ModuleCamera::GetModelPosition(const float4x4& model) const {

	return float3(model[3][0], model[3][1], model[3][2]);
}

float3 ModuleCamera::GetModelRotation(const float4x4& model) const {

	return float3(atan2(model[3][2], model[3][3]),
				  atan2(-model[3][1], sqrt(model[3][2] * model[3][2] + model[3][3] * model[3][3])),
				  atan2(model[2][1], model[1][1]));
}

float3 ModuleCamera::GetModelScale(const float4x4& model) const {

	return model.GetScale();
}

ModuleCamera::~ModuleCamera(){

}