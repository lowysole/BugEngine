#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "UIConsole.h"

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);

	App->editor->console->AddLog(tmp_string2);
	OutputDebugString(tmp_string2);
}