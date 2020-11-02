#pragma once
#include "Module.h"
#include "Globals.h"
#include "Geometry/Frustum.h"
#include "MathGeoLib.h"

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
	void SetFOV();
	void SetAspectRatio();
	float4x4 GetProjectionMatrix() const { return projectionGL; };
	float4x4 GetViewMatrix() const { return viewMatrix; };
	void MoveHoritzontalPlane();
	void MoveVerticalAxis();
	void RotateCamera();
	void SetCameraSpeed();

private:

	Frustum frustum;
	float4x4 projectionGL;
	float4x4 viewMatrix;
	float3 camera_position = float3(0, 1, -2);
	float move_speed = 0.004f;
	float angleX = 0.0f, angleY = 0.0f;
	float angle_speed = 0.001f;
	float aspectRatio;
};

