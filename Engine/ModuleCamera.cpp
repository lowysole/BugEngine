#include <algorithm>
#include "Globals.h"
#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h" 
#include "ModuleEditor.h"
#include "Model.h"
#include "UIInspector.h"
#include "Math/float3x3.h"


ModuleCamera::ModuleCamera() {

}

bool ModuleCamera::Init() {
	
	clock = Clock();
	GetUIInformation();
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	UpdateFOV();
	frustum.SetPos(float3(cameraPosition));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	projectionGL = frustum.ProjectionMatrix();
	viewMatrix = frustum.ViewMatrix();

	return true;
}

update_status ModuleCamera::Update() 
{
	float currentTime = clock.Time();
	deltaTime = (currentTime - previousTime) / 1000.0;
	previousTime = currentTime;
	CalculateFrameRate();
	GetUIInformation();
	UpdateFOV();

	frustum.SetPos(cameraPosition);
	ModifyCameraSpeed();
	FlythroughMode();
	ZoomCamera();
	FocusCenterObject();
	Orbit();

	projectionGL = frustum.ProjectionMatrix();
	viewMatrix = frustum.ViewMatrix();

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModuleCamera::UpdateFOV() {
	UpdateAspectRatio();
	frustum.SetVerticalFovAndAspectRatio(vFOV, aspectRatio);
}

void ModuleCamera::UpdateAspectRatio() {
	aspectRatio = (float)*App->window->GetCurrentWidth() / (float)*App->window->GetCurrentHeight();
}

void ModuleCamera::FlythroughMode() {

	float shift = deltaTime * cameraSpeed;
	float angleShift = deltaTime * angleSpeed;
	float aX = 0, aY = 0;

	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) && 
		!App->input->GetKey(SDL_SCANCODE_LALT) && 
		!App->input->GetKey(SDL_SCANCODE_RALT)) {

		if (App->input->GetKey(SDL_SCANCODE_W)) 
			cameraPosition = frustum.Front() * shift + cameraPosition;
		
		if (App->input->GetKey(SDL_SCANCODE_S)) 
			cameraPosition = -frustum.Front() * shift + cameraPosition;
		
		if (App->input->GetKey(SDL_SCANCODE_A)) 
			cameraPosition = -frustum.WorldRight() * shift + cameraPosition;
		
		if (App->input->GetKey(SDL_SCANCODE_D)) 
			cameraPosition = frustum.WorldRight() * shift + cameraPosition;
		
		if (App->input->GetKey(SDL_SCANCODE_Q)) 
			cameraPosition = float3::unitY * shift + cameraPosition;
		
		if (App->input->GetKey(SDL_SCANCODE_E)) 
			cameraPosition = -float3::unitY * shift + cameraPosition;	


		if (App->input->GetMouseMotion().y < 0) {
			aX = -angleShift;
		}
		if (App->input->GetMouseMotion().y > 0) {
			aX = angleShift;
		}
		if (App->input->GetMouseMotion().x < 0) {
			aY = angleShift;
		}
		if (App->input->GetMouseMotion().x > 0) {
			aY = -angleShift;
		}
		RotateCamera(aX, aY);
	}	
}

void ModuleCamera::RotateCamera(float aX, float aY) {

	float3x3 rotationMatrix;
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

void ModuleCamera::ZoomCamera(){
	int wheel = App->input->GetMouseWheel();
	bool changed = false;
	if (wheel) {

		if (wheel == 1) vFOV -= deltaTime * zoomSpeed;
		else if (wheel == -1) vFOV += deltaTime * zoomSpeed;
		App->input->SetMouseWheelTo0();
		changed = true;
	}
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) && App->input->GetKey(SDL_SCANCODE_LALT)) {

		if (App->input->GetMouseMotion().y > 0) {
			vFOV += deltaTime * zoomSpeed * 0.6;
		}
		if (App->input->GetMouseMotion().y < 0) {
			vFOV -= deltaTime * zoomSpeed * 0.6;
		}
		changed = true;
	}
	if (changed) {
		//Limit Zoom from 40º to 140º vFOV Angle (Rad)
		if (vFOV < 0.6981) {
			vFOV = 0.6981;
		}
		else if (vFOV > 2.4434) {
			vFOV = 2.4434;
		}
		UpdateFOV();
	}
}

void ModuleCamera::Orbit() {
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) && App->input->GetKey(SDL_SCANCODE_LALT)) {

	float3 up = float3::unitY;
	float3 front = frustum.Front();
	float3 focusPoint = GetModelPosition(App->model->GetMeshes()[0]->GetModelMatrix());
	float3 focusDirection = (frustum.Pos() - focusPoint);
	float aX = 0, aY = 0;
	float angleShift = deltaTime * angleSpeed;
	if (App->input->GetMouseMotion().y < 0) {
		aX = -angleShift;
	}
	if (App->input->GetMouseMotion().y > 0) {
		aX = angleShift;
	}
	if (App->input->GetMouseMotion().x < 0) {
		aY = angleShift;
	}
	if (App->input->GetMouseMotion().x > 0) {
		aY = -angleShift;
	}
	angleX += aX;
	angleY += aY;
	float3x3 rotationYaw = float3x3::RotateAxisAngle(up, angleY);
	float3x3 rotationPitch = float3x3::RotateAxisAngle(front, angleX);
	float3 newCamPosDirection = (focusDirection * rotationPitch) * rotationYaw ;
	float3 newCamPos = newCamPosDirection + focusPoint;
	//float3x3 rotationMatrix = float3x3::LookAt(front, newCamPosDirection, up, float3::unitY);
	frustum.SetPos(newCamPos);
	LookAt(newCamPos, focusPoint);
	//frustum.SetFront((rotationMatrix * front).Normalized());
	//frustum.SetUp((rotationMatrix * up).Normalized());


	}
}

void ModuleCamera::FocusCenterObject() {
	if (App->input->GetKey(SDL_SCANCODE_F)) {

		float4x4 model = App->model->GetMeshes()[0]->GetModelMatrix();
		float3 position = GetModelPosition(model);
		LookAt(frustum.Pos(),position);
	}
}


void ModuleCamera::ModifyCameraSpeed(){
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT)) {
		cameraSpeed *= 2;
		angleSpeed *= 2;
		// TODO: Print updated velocity
	}
}

void ModuleCamera::GetUIInformation() {
	//Transformation
	UIInspector* inspector = App->editor->inspector;
	cameraPosition = inspector->GetCameraPosition();
	cameraSpeed = inspector->GetCameraSpeed();
	angleSpeed = inspector->GetAngleSpeed();
	nearPlane = inspector->GetNearPlane();
	farPlane = inspector->GetFarPlane();
	zoomSpeed = inspector->GetZoomSpeed();
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetPos(cameraPosition);
	float2 cameraRot = inspector->GetCameraRotation() * DEGTORAD;
	if (cameraRot.x != angleX || cameraRot.y != angleY) {
		RotateCamera(cameraRot.x - angleX, cameraRot.y - angleY);
	}
}

void ModuleCamera::SetUIInformation(){
}



void ModuleCamera::CalculateFrameRate() {

	float currentTime = clock.Time();
	++frames;
	if (currentTime - lastTime > 1000.0f * time){

		lastTime = currentTime;
		int fps = frames / time;
		if (fps > fpsMax) {
			fpsMax = fps;
		}
		frames = 0;

		for (size_t i = 1; i < IM_ARRAYSIZE(fpsLog); i++) {
			fpsLog[i - 1] = fpsLog[i];
		}
		fpsLog[IM_ARRAYSIZE(fpsLog) - 1] = fps;
	}
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

void ModuleCamera::LookAt(float3 pos, float3 target) {
	float3 targetDir = target - pos;
	float3 oldUp = frustum.Up();
	float3 oldFront = frustum.Front();
	float3x3 rotationMatrix = float3x3::LookAt(oldFront, targetDir.Normalized(), oldUp, float3::unitY);
	frustum.SetFront((rotationMatrix * oldFront).Normalized());
	frustum.SetUp((rotationMatrix * oldUp).Normalized());
}

ModuleCamera::~ModuleCamera(){

}