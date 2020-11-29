#pragma once
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>
#include "Math/float4x4.h"

class Mesh
{
public:
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures);

	//Getters & Setters
	void SetMaterialIndex(const unsigned num) { materialIndex = num; };
	unsigned GetNumVertices() const { return numVertices; };
	unsigned GetNumFaces() const { return numFaces; };
	unsigned GetMaterialIndex() const { return materialIndex; };
	const float4x4 GetModelMatrix() const { return model; };
	float3 GetMaxDistance() const { return float3(maxX, maxY, maxZ); };


private:
	unsigned vbo;
	unsigned ebo;
	unsigned vao;
	unsigned numVertices;
	unsigned numIndices;
	unsigned numFaces;
	unsigned materialIndex;
	float4x4 model;
	float maxX = 0.0f;
	float maxY = 0.0f;
	float maxZ = 0.0f;
};

