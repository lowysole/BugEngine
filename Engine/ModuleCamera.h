#pragma once
#include "Module.h"
#include "Globals.h"
#include "Geometry/Frustum.h"
#include "MathGeoLib.h"
#include "Time/Clock.h"

#define DEGTORAD 0.01745329252f 
#define EPSILON 0.001f

class ModuleCamera : public Module 
{
public:

	ModuleCamera();
	~ModuleCamera();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	float4x4 GetProjectionMatrix() const { return projectionGL; };
	float4x4 GetViewMatrix() const { return viewMatrix; };
	void MoveHoritzontalPlane();
	void MoveVerticalAxis();
	void RotateCamera();
	void SetCameraSpeed();
	void SetPosition(float3 other) { cameraPosition = other; };
	void SetOrentation(float x, float y) { angleX = x; angleY = y; };
	void SetPlaneDistance(float nearP, float farP) { nearPlane = nearP; farPlane = farP; }
	void SetFOV();
	void SetAspectRatio();

private:

	Clock clock;
	unsigned deltaTime;
	unsigned previousTime;
	Frustum frustum;
	float4x4 projectionGL;
	float4x4 viewMatrix;
	float3 cameraPosition = float3(0, 1, -2);
	float moveSpeed = 0.004f;
	float angleX = 0.0f, angleY = 0.0f;
	float angleSpeed = 0.001f;
	float nearPlane = 0.1f, farPlane = 30.f;
	float aspectRatio;
};

