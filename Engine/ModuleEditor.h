#pragma once
#include "Module.h"
#include "ImGui/imgui.h"

class ModuleEditor : public Module
{
public:
	bool Init();
	//update_status PreUpdate();
	update_status Update();
	//update_status ProUpdate();
	bool CleanUp();

private:
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

