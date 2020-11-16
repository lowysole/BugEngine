#pragma once
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>

class Mesh
{
public:
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures);

	//Getters & Setters
	void SetMaterialIndex(const unsigned num) { materialIndex = num; };

private:
	unsigned vbo;
	unsigned ebo;
	unsigned vao;
	unsigned numVertices;
	unsigned numIndices;
	unsigned materialIndex;
};

