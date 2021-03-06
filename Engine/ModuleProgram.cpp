#include "ModuleProgram.h"
#include "Application.h"
#include "GL/glew.h";
#include "leak.h"

bool ModuleProgram::Init() {

	char* defaultVertex = LoadShaderSource(".\\Game\\Resources\\default_vertex.glsl");
	char* defaultFragment = LoadShaderSource(".\\Game\\Resources\\default_fragment.glsl");
	unsigned vertexShaderID = CompileShader(GL_VERTEX_SHADER, defaultVertex);
	unsigned fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, defaultFragment);
	programId = CreateProgram(vertexShaderID, fragmentShaderID);
	delete defaultVertex;
	delete defaultFragment;

	return true;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		fseek(file, 0, SEEK_SET);
		data = (char*)malloc(size + 1);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}

unsigned ModuleProgram::CompileShader(unsigned type, const char* source)
{
	unsigned shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, 0);
	glCompileShader(shader_id);
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			LOG("Log Info: %s\n", info);
			free(info);
		}
	}
	return shader_id;
}

unsigned ModuleProgram::CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
	unsigned programId = glCreateProgram();
	glAttachShader(programId, vtx_shader);
	glAttachShader(programId, frg_shader);
	glLinkProgram(programId);
	int res;
	glGetProgramiv(programId, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(programId, len, &written, info);
			LOG("Program Log Info: %s\n", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	return programId;
}

bool ModuleProgram::CleanUp() {


	glDeleteProgram(programId);
	return true;
}
