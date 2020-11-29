#pragma once
#include "Globals.h"

class UI
{
public:

	virtual void Draw(const char* title, bool* p_open) {};
    void HelpMarker(const char* desc);	

};