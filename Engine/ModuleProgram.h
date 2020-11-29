#pragma once
#include "Module.h"
class ModuleProgram : public Module
{
public: 

	bool Init();
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);
	unsigned GetProgramId() const { return programId; };
	bool CleanUp();

private:
	unsigned programId;

};

