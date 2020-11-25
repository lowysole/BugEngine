#pragma once
#include "UI.h"


#define MAX_BUFF_EXT 10
#define MAX_BUFF_FOLDER 100

class UIConfiguration : public UI
{
public:

	void Draw(const char* title, bool* p_open);
	void GetFrameRatePlotTimed();

	//Getters & Setters
	void SetMaxWidht(int widht) { maxWidth = widht; };
	void SetMaxHeight(int height) { maxHeight = height; };
	void GetTextureFolder(char* other);
	void GetTextureExt(char* other);

private:

	//App
	float fpsLog[25] = {};
	int plotSeconds = 1;
	int time = 1;

	// Window
	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
	bool fullDesktop = false;
	int brightness = 100;
	int* windowWidth;
	int maxWidth = 0;
	int* windowHeight;
	int maxHeight = 0;

	//Texture
	char textureFolder[MAX_BUFF_FOLDER];
	char textureExt[MAX_BUFF_EXT] = ".png";
};

