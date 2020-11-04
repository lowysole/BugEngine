#include <algorithm>
#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h" 

ModuleCamera::ModuleCamera() {

}

bool ModuleCamera::Init() {

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 30.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);
	frustum.SetPos(float3(camera_position));
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
	move_speed = 0.004f;
	angle_speed = 0.001f;

	SetAspectRatio();
	SetFOV();
	SetCameraSpeed();
	MoveHoritzontalPlane();
	MoveVerticalAxis();
	frustum.SetViewPlaneDistances(0.1f, 30.0f);
	frustum.SetPos(camera_position);

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

	SDL_Surface* screen = App->window->screen_surface;
	SDL_Window* window = App->window->GetWindow();
	aspectRatio = (float)screen->w / (float)screen->h;

}

void ModuleCamera::MoveHoritzontalPlane() {

	if (App->input->GetKey(SDL_SCANCODE_W)) {

		camera_position = frustum.Front() * move_speed + camera_position;
	}
	if (App->input->GetKey(SDL_SCANCODE_S)) {
		camera_position = -frustum.Front() * move_speed + camera_position;
	}
	if (App->input->GetKey(SDL_SCANCODE_A)) {
		camera_position = -frustum.WorldRight() * move_speed + camera_position;
	}
	if (App->input->GetKey(SDL_SCANCODE_D)) {
		camera_position = frustum.WorldRight() * move_speed + camera_position;
	}
}

void ModuleCamera::MoveVerticalAxis() {
	if (App->input->GetKey(SDL_SCANCODE_Q)) {
		camera_position = float3::unitY * move_speed + camera_position;
	}
	if (App->input->GetKey(SDL_SCANCODE_E)) {
		camera_position = -float3::unitY * move_speed + camera_position;
	}
}

void ModuleCamera::RotateCamera() {

	float aX = 0, aY = 0;
	float3x3 rotationXmatrix;
	float3x3 rotationYmatrix;
	if (App->input->GetKey(SDL_SCANCODE_UP)) {
		aX = angle_speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
		aX = -angle_speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT)) {
		aY = angle_speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT)) {
		aY = -angle_speed;
	}
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
	frustum.SetUp(rotationXmatrix.RotateX(aX) * oldUp);
	frustum.SetFront(rotationXmatrix.RotateX(aX) * oldFront);

	oldUp = frustum.Up().Normalized();
	oldFront = frustum.Front().Normalized();
	frustum.SetFront(rotationYmatrix.RotateY(aY) * oldFront);
	frustum.SetUp(rotationYmatrix.RotateY(aY) * oldUp);


}

void ModuleCamera::SetCameraSpeed(){
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT)) {
		move_speed *= 2;
		angle_speed *= 2;
	}
}

ModuleCamera::~ModuleCamera(){

}