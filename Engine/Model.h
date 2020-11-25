#pragma once
#include "Module.h"
#include "Mesh.h"
#include "GL/glew.h"
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>

class Model: public Module
{
public:
	bool Init();
	update_status Update();
	void Load(const char* file_name);
	void LoadMeshes(const aiScene* scene);
	void LoadMaterials(const aiScene* scene);
	void UpdateCameraDistance();
	bool CleanUp();

	//Getter & Setters
	std::vector<Mesh*> GetMeshes() { return meshes; };
	std::vector<GLuint> GetMaterials() { return materials; };

private:
	std::vector<Mesh*> meshes;
	std::vector<GLuint> materials;
	const char* fileName;
};

