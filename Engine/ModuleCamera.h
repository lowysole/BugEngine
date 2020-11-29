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

class ModuleCamera : public Module
{
public:

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
	void CalculateFrameRate();
	void ResetVFOV() { vFOV = pi / 2; }
	void UpdateFrontFrustum(const float3& other) { frustum.SetFront(other); };
	void UpdateUpFrustum(const float3& other) { frustum.SetUp(other); };
	float3 GetModelPosition(const float4x4& model) const;
	float3 GetModelRotation(const float4x4& model) const;
	float3 GetModelScale(const float4x4& model) const;
	void LookAt(const float3& pos, const float3& target);

	//Getters & Setters
	float4x4 GetProjectionMatrix() const { return projectionGL; };
	float4x4 GetViewMatrix() const { return viewMatrix; };
	int GetMaxFPS() const { return fpsMax; };
	void SetTime(int other) { time = other; };
	float GetFOV() const { return vFOV; };
	float3 GetPosition() const { return cameraPosition; };
	void SetPosition(const float3 other) { cameraPosition = other; };
	float3 GetFrustumUp() const { return frustum.Up(); };
	float3 GetFrustumFront() const { return frustum.Front(); };
	float2 GetAnglesRotation() const { return float2(angleX, angleY); };

	float fpsLog[25] = {};

private:

	//Time
	Clock clock;
	float deltaTime = 0.0f;
	float previousTime = 0.0f;
	int frames = 0;
	float lastTime = 0.0f;
	int time = 1;
	int fpsMax = 0;

	//Camera
	Frustum frustum;
	float4x4 projectionGL;
	float4x4 viewMatrix;
	float3 cameraPosition;
	float cameraSpeed = 0.0f;
	float angleX = 0.0f, angleY = 0.0f;
	float angleSpeed = 0.0f;
	float nearPlane = 0.0f;
	float farPlane = 0.0f;
	float aspectRatio = 0.0f;
	float vFOV = pi / 2;
	float zoomSpeed = 0.0f;
};

