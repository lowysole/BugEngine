#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleEditor.h"
#include "UIInspector.h"
#include "Geometry/Frustum.h"
#include "MathGeoLib.h"
#include "Time/Clock.h"
#include "Math/float2.h"

#define DEGTORAD 0.01745329252f 
#define RADTODEG 57.295779
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
	void Orbit();
	void FocusCenterObject();
	void ModifyCameraSpeed();
	void GetUIInformation(); 
	void SetUIInformation();
	void CalculateFrameRate();
	void ResetVFOV() { vFOV = pi / 2; }
	void UpdateFrontFrustum(float3 other) { frustum.SetFront(other); };
	void UpdateUpFrustum(float3 other) { frustum.SetUp(other); };

	float3 GetModelPosition(const float4x4& model) const;
	float3 GetModelRotation(const float4x4& model) const;
	float3 GetModelScale(const float4x4& model) const;

	//Getters & Setters
	float4x4 GetProjectionMatrix() const { return projectionGL; };
	float4x4 GetViewMatrix() const { return viewMatrix; };
	int GetMaxFPS() { return fpsMax; };
	void SetTime(int other) { time = other; };
	float GetFOV() { return vFOV; };
	float3 GetPosition() { return cameraPosition; };
	void SetPosition(float3 other) { cameraPosition = other; };
	float3 GetFrustumUp() { return frustum.Up(); };
	float3 GetFrustumFront() { return frustum.Front(); };
	float2 GetAnglesRotation() { return float2(angleX, angleY); };


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
	float3 cameraPosition;
	float cameraSpeed;
	float angleX = 0.0f, angleY = 0.0f;
	float angleSpeed;
	float nearPlane;
	float farPlane;
	float aspectRatio;
	float vFOV = pi / 2;
	float zoomSpeed;
};

