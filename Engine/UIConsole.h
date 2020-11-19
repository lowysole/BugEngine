#pragma once
#include "UI.h"
#include "imgui.h"


class UIConsole : public UI
{
public:
	UIConsole();
	void Draw(const char* title, bool* p_open);
	//void AddLog(const char file[], int line, const char* format, ...);
	void Clear();

private:
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
	bool                AutoScroll;

};

extern UIConsole* console;

