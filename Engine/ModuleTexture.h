#pragma once
#include "Module.h"
#include "IL/ilu.h"
#include "IL/il.h"
#include "GL/glew.h"

class ModuleTexture : public Module
{
public:
	bool Init();
	GLuint LoadTexture(const char* shader_file_name);
	GLuint GetImage() { return image; };
	bool DeleteTexture(GLuint& image);
	bool CleanUp();
	
private:
	GLuint image;
};

