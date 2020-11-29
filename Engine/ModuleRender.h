#pragma once
#include "Module.h"

class ModuleRender : public Module
{
public:
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	//Getters & Setters
	void* GetContext() { return context; };

private:
	void* context;
};