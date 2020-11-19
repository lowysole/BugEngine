#include "Model.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "Mesh.h"
#include "GL/glew.h"


bool Model::Init() {

	Load("BakerHouse.fbx");

	return true;
}

void Model::Load(const char* file_name) {

	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadMaterials(scene);
		LoadMeshes(scene);
	}
	else
	{
		LOG("Error loading %s: %s", file_name, aiGetErrorString());
	}
}

void Model::LoadMaterials(const aiScene* scene)
{
	aiString file;
	materials.reserve(scene->mNumMaterials);
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->texture->LoadTexture(file.data));
		}
	}
}

void Model::LoadMeshes(const aiScene* scene)
{
	meshes.reserve(scene->mNumMeshes);
	for (unsigned i = 0; i < scene->mNumMeshes; ++i) {

		Mesh* mesh = new Mesh();
		mesh->LoadVBO(scene->mMeshes[i]);
		mesh->LoadEBO(scene->mMeshes[i]);
		mesh->CreateVAO();
		mesh->SetMaterialIndex(materials.size() - 1);
		meshes.push_back(mesh);
	}
}

update_status Model::Update() {

	for (std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); it++) {

		(*it)->Draw(materials);
	}
	return UPDATE_CONTINUE;
}

bool Model::CleanUp() {
	for (std::vector<GLuint>::iterator it = materials.begin(); it != materials.end(); it++) {

		App->texture->DeleteTexture(*it);
	}

	meshes.clear();
	materials.clear();

	return true;
}