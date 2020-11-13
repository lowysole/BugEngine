#pragma once
#include "Module.h"
#include "IL/ilu.h"
#include "IL/il.h"
#include "GL/glew.h"

class ModuleTexture : public Module
{
public:
	bool Init();
	update_status Update();
	bool CleanUp();

	GLuint GetImage() { return image; };

private:
	unsigned imageId;
	GLuint image;
};

