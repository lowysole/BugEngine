#pragma once
#include "Globals.h"
#include "Module.h"
#include "UI.h"
#include "UIConsole.h"
#include "UIInspector.h"
#include "UIConfiguration.h"
#include "imgui.h"
#include <vector>

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status Update();
	bool CleanUp();

	//UI Modules
	void UIMainMenuBar();
	void UIAbout(bool* p_open);
	void CheckUIWindows();
	bool CheckUIInputs();

public:
	//Modules
	std::vector<UI*> windowsUI;
	UIConsole* console = nullptr;
	UIInspector* inspector = nullptr;
	UIConfiguration* config = nullptr;

private:
	//UI Modules activation
	bool exit = false;
	bool showUIAbout = false;
	bool showUIConsole = true;
	bool showUIInspector = true;
	bool showUIConfig = true;

};