#pragma once
#include "Module.h"
#include "Mesh.h"
#include "GL/glew.h"
#include "Math/float2.h"
#include <vector>
#include <string>

class Model: public Module
{
public:

	~Model();

	bool Init();
	update_status Update();
	void Load(const char* file_name);
	void LoadScene(const char* file_name);
	void LoadMeshes(const aiScene* scene);
	void LoadMaterials(const aiScene* scene);
	void LoadMaterialFromModelPath();
	void LoadExternalMaterial();
	void UpdateCameraDistance();
	void CleanMeshes();
	void CleanMaterials();
	bool CleanUp();

	//Getter & Setters
	std::vector<Mesh*> GetMeshes() const { return meshes; };
	std::vector<GLuint> GetMaterials() const{ return materials; };
	std::string GetTexturePath() const { return texturePath; };
	int GetTextureWidth() const { return textureSize[0]; };
	int GetTextureHeight() const { return textureSize[1]; };
	void SetTextureSize(int w, int h) { textureSize[0] = w, textureSize[1] = h; };

private:
	std::vector<Mesh*> meshes;
	std::vector<GLuint> materials;
	std::string fileName;
	std::string texturePath;
	int textureSize[2] = {0,0};
	int textureHeight = 0;
};

