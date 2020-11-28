#pragma once
#include "UI.h"
#include "Math/float4.h"
#include "GL/glew.h"


#define MAX_BUFF_EXT 10
#define MAX_BUFF_FOLDER 100

class UIConfiguration : public UI
{
public:

	void Draw(const char* title, bool* p_open);

	//Getters & Setters
	void SetMaxWidht(int widht) { maxWidth = widht; };
	void SetMaxHeight(int height) { maxHeight = height; };
	void GetTextureFolder(char* other);
	void GetTextureExt(char* other);
	float4 GetBgColor() const { return float4(bgColor[0],
											  bgColor[1],
											  bgColor[2],
											  bgColor[3]); };
	float3 GetGridColor() const { return float3(gridColor[0], 
												gridColor[1], 
												gridColor[2]); };
	const char* GetWrapFilter() const { return wrap[wrapCurrent]; };
	const char* GetMagFilter() const;
	const char* GetMinFilter() const;

private:

	//App
	float fpsLog[25] = {};
	int plotSeconds = 1;
	int time = 1;

	// Window
	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
	bool fullDesktop = true;
	int brightness = 100;
	int* windowWidth;
	int maxWidth = 0;
	int* windowHeight;
	int maxHeight = 0;

	//Texture
	char textureFolder[MAX_BUFF_FOLDER];
	char textureExt[MAX_BUFF_EXT] = ".png";
	bool minmapActivated = false;
	const char* magnification[2] = { "GL_LINEAR", "GL_NEAREST" };
	int magnificationCurrent = 0;
	const char* minification[2] = { "GL_LINEAR", "GL_NEAREST" };
	int minificationCurrent = 0;
	const char* magMinmap[4] = { "GL_NEAREST_MIPMAP_NEAREST",
								"GL_LINEAR_MIPMAP_NEAREST",
								"GL_NEAREST_MIPMAP_LINEAR",
								"GL_LINEAR_MIPMAP_LINEAR" };
	int magMinmapCurrent = 4;
	const char* minMinmap[4] = { "GL_NEAREST_MIPMAP_NEAREST",
							     "GL_LINEAR_MIPMAP_NEAREST",
							     "GL_NEAREST_MIPMAP_LINEAR",
							     "GL_LINEAR_MIPMAP_LINEAR" };
	int minMinmapCurrent = 4;
	const char* wrap[4] = { "GL_REPEAT",
						   "GL_CLAMP",
						   "GL_CLAMP_TO_BORDER",
						   "GL_MIRRORED_REPEAT" };
	int wrapCurrent = 0;

	//Render
	float bgColor[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	float gridColor[3] = { 0.501961f, 0.501961f, 0.501961f};
};

