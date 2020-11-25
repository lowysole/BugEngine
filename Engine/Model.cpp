#include "Model.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleCamera.h"
#include "Mesh.h"
#include "GL/glew.h"
#include <string>
#include <iostream>


bool Model::Init() {

	Load("BakerHouse.fbx");


	return true;
}

void Model::Load(const char* file) {

	fileName = file;
	const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadMaterials(scene);
		LoadMeshes(scene);
	}
	else
	{
		LOG("Error loading %s: %s", file, aiGetErrorString());
	}
	UpdateCameraDistance();
}

void Model::LoadMaterials(const aiScene* scene)
{
		aiString file;
		materials.reserve(scene->mNumMaterials);
		for (unsigned i = 0; i < scene->mNumMaterials; ++i)
		{
			if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
			{
				GLuint texture = App->texture->LoadTexture(file.data);
				if (texture) {
					materials.push_back(texture);
				}
			}
		}
		if (materials.size() == 0) {

			char defaultFolder[100];
			App->editor->config->GetTextureFolder(defaultFolder);
			char textureExt[10];
			App->editor->config->GetTextureExt(textureExt);
			std::string s = fileName;
			std::string path = s.substr(0, s.find(".")) + textureExt;
			LOG("[INFO] Diffusse texture not found. Checking in the Model folder: %d", path.c_str());
			GLuint texture = App->texture->LoadTexture(path.c_str());
			if (texture) {
				materials.push_back(texture);
			}
			else {
				if (defaultFolder == "") {
					GetCurrentDirectoryA(MAX_BUFF_FOLDER, defaultFolder);
				}
				std::string filename = s.substr(s.rfind('\\'), s.length());
				std::string defaultPath = defaultFolder + filename.substr(0, filename.rfind(".")) + textureExt;
				LOG("[INFO] Diffusse texture not found. Checking in the Default Texture folder: %d", defaultPath.c_str());
				texture = App->texture->LoadTexture(defaultPath.c_str());
				if (texture) {
					materials.push_back(texture);
				}
				else {
					LOG("[WARNING] Impossible to Load a Texture for this model.");
					materials.push_back(0);
				}
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

void Model::UpdateCameraDistance() {
	ModuleCamera* camera = App->camera;
	float fov = camera->GetFOV();
	//Taking into account Model Matrix in origin
	float radius = 0.0f;
	for (std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		float3 max = (*it)->GetMaxDistance();
		if (radius < max.x){
			radius = max.x;
		}
		if (radius < max.y) {
			radius = max.y;
		}
		if (radius < max.z) {
			radius = max.z;
		}
	}
	float3 pos = camera->GetPosition();
	float dist = radius / sin(fov /2);
	camera->SetPosition(float3(0, 1, -dist));
	camera->UpdateFrontFrustum(float3::unitZ);
	camera->UpdateUpFrustum(float3::unitY);
}

bool Model::CleanUp() {
	for (std::vector<GLuint>::iterator it = materials.begin(); it != materials.end(); it++) {

		App->texture->DeleteTexture(*it);
	}

	meshes.clear();
	materials.clear();

	return true;
}