#pragma once
#include "UI.h"
#include "Math/float3.h"

class UIInspector  : public UI
{
public:
	UIInspector();
	void Draw(const char* title, bool* p_open);

	//Camera
	float3 GetCameraPosition() const { return float3(cameraPosition[0], cameraPosition[1], cameraPosition[2]); };
	float GetCameraSpeed() const { return cameraSpeed; };
	float GetAngleSpeed() const{ return angleSpeed; };
	float GetNearPlane() const { return nearPlane; };
	float GetFarPlane() const { return farPlane; };
	float GetZoomSpeed() const { return zoomSpeed; };

private:

	//Camera
	float cameraPosition[3];
	float cameraRotation[3];
	float angleX = 0.0f, angleY = 0.0f;
	float cameraSpeed = 3.0f;
	float angleSpeed = 2.0f;
	float zoomSpeed = 10.0f;
	float nearPlane = 0.1f, farPlane = 30.f;

};

