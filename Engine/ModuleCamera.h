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
	update_status Update();
	update_status PostUpdate();

	void UpdateFOV();
	void UpdateAspectRatio();
	void FlythroughMode();
	void RotateCamera(float aX, float aY);
	void ZoomCamera();
	void ModifyCameraSpeed();
	void GetUIInformation(); 
	void SetUIInformation();
	void CalculateFrameRate();
	void ResetVFOV() { vFOV = pi / 2; }

	//Getters & Setters
	float4x4 GetProjectionMatrix() const { return projectionGL; };
	float4x4 GetViewMatrix() const { return viewMatrix; };
	int GetMaxFPS() { return fpsMax; };
	void SetTime(int other) { time = other; };
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

	float3 GetModelPosition(const float4x4& model) const;
	float3 GetModelRotation(const float4x4& model) const;
	float3 GetModelScale(const float4x4& model) const;

	float fpsLog[25] = {};

private:

	//Time
	Clock clock;
	float deltaTime;
	float previousTime = 0.0f;
	int frames = 0;
	float lastTime = 0.0f;
	int time = 1;
	int fpsMax;

	//Camera
	Frustum frustum;
	float4x4 projectionGL;
	float4x4 viewMatrix;
	float3 cameraPosition = float3(0, 1, -2);
	float cameraSpeed;
	float angleX = 0.0f, angleY = 0.0f;
	float angleSpeed;
	float nearPlane = 0.1f, farPlane = 50.f;
	float aspectRatio;
	float vFOV = pi / 2;
	float zoomSpeed;
};

