#pragma once
#include "UI.h"

class UIInspector  : public UI
{
public:
	UIInspector();
	void Draw(const char* title, bool* p_open);

	//Camera
	float GetCameraSpeed() { return cameraSpeed; };
	float SetCameraSpeed(float other) { cameraSpeed = other; };
	float GetAngleSpeed() { return angleSpeed; };
	float SetAngleSpeed(float other) { angleSpeed = other; };
	float GetNearPlane() { return nearPlane; };
	float GetFarPlane() { return farPlane; };

private:

	//Camera
	float cameraPosition[3];
	float angleX = 0.0f, angleY = 0.0f;
	float cameraSpeed = 3.0f;
	float angleSpeed = 2.0f;
	float zoomSpeed = 0.0f;
	float nearPlane = 0.1f, farPlane = 30.f;

};

