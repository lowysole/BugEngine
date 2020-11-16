#pragma once
#include "Module.h"
#include "IL/ilu.h"
#include "IL/il.h"
#include "GL/glew.h"
#include <vector>

class ModuleTexture : public Module
{
public:
	bool Init();
	GLuint LoadTexture(const char* shader_file_name);
	bool DeleteTexture(GLuint& image);
	bool CleanUp();
	
};

