#pragma once
#include "UI.h"
#include "imgui.h"


class UIConsole : public UI
{
public:
	UIConsole();
	void Draw(const char* title, bool* p_open);
	void AddLog(const char file[], ...);
	void Clear();


private:
	ImGuiTextBuffer     buffer;
	ImGuiTextFilter     filter;
	ImVector<int>       lineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
	bool                autoScroll;

};

extern UIConsole* console;

