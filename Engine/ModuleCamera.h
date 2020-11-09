#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleEditor.h"
#include "UIInspector.h"
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
	void ModifyCameraSpeed();
	void SetFOV();
	void SetAspectRatio();
	void GetUIInformation();


	float3 GetPosition() { return cameraPosition; };
	void SetPosition(float3 other) { cameraPosition = other; };
	float GetCameraSpeed() { return cameraSpeed; };
	void SetCameraSpeed(float other) { cameraSpeed = other; };
	float2 GetOrentation() { return float2(angleX, angleY); };
	void SetOrentation(float x, float y) { angleX = x; angleY = y; };
	float GetAngleSpeed() { return angleSpeed; };
	float SetAngleSpeed(float other) { angleSpeed = other; };
	float3 GetFrontFrustum() { return frustum.Front(); };
	void SetFrontFrustum(float3 other) { frustum.SetFront(other); };
	float3 GetUpFrustum() { return frustum.Up(); };
	void SetUpFrustum(float3 other) { frustum.SetUp(other); };
	float2 GetPlaneDistance() { return float2(nearPlane, farPlane); };
	void SetPlaneDistance(float nearP, float farP) { nearPlane = nearP; farPlane = farP; }

private:

	Clock clock;
	float deltaTime;
	float previousTime = 0.0f;
	Frustum frustum;
	float4x4 projectionGL;
	float4x4 viewMatrix;
	float3 cameraPosition = float3(0, 1, -2);
	float cameraSpeed;
	float angleX = 0.0f, angleY = 0.0f;
	float angleSpeed;
	float nearPlane = 0.1f, farPlane = 30.f;
	float aspectRatio;
};

