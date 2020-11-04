#include <algorithm>
#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h" 


ModuleCamera::ModuleCamera() {

}

bool ModuleCamera::Init() {
	
	clock = Clock();
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);
	frustum.SetPos(float3(cameraPosition));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	projectionGL = frustum.ProjectionMatrix().Transposed();
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
	return true;
}

update_status ModuleCamera::PreUpdate() {
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update() 
{
	unsigned currentTime = clock.Time();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
	moveSpeed = 0.004f;
	angleSpeed = 0.001f;

	SetAspectRatio();
	SetFOV();
	SetCameraSpeed();
	MoveHoritzontalPlane();
	MoveVerticalAxis();
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetPos(cameraPosition);

	RotateCamera();
	projectionGL = frustum.ProjectionMatrix().Transposed();
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModuleCamera::SetFOV() {

	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, aspectRatio);
}

void ModuleCamera::SetAspectRatio() {
	std::vector<int> windowSize = App->input->GetWindowsSize();

	aspectRatio = (float)windowSize[1] / (float)windowSize[2];

}

void ModuleCamera::MoveHoritzontalPlane() {
	float shift = deltaTime * moveSpeed;
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
	float shift = deltaTime * moveSpeed;
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

void ModuleCamera::SetCameraSpeed(){
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT)) {
		moveSpeed *= 2;
		angleSpeed *= 2;
	}
}

ModuleCamera::~ModuleCamera(){

}