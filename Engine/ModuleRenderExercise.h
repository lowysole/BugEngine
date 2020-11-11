#pragma once
#include "Module.h"

class ModuleRenderExercise : public Module
{
	public:
		bool Init();
		update_status PreUpdate();
		update_status Update();
		update_status PostUpdate();
		void RenderVBO(unsigned vbo, unsigned program);
		unsigned CreateTriangleVBO();
		void DestroyVBO(unsigned vbo);
		bool CleanUp();

		unsigned vbo1;
		void* context;
};

