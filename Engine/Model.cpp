#include "Model.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleCamera.h"
#include "ModuleEditor.h"
#include "UIInspector.h"
#include "Mesh.h"
#include "GL/glew.h"
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "leak.h"

void myCallback(const char* msg, char* userData) {
	LOG(msg);
}

Model::~Model() {

	meshes.clear();
}

bool Model::Init() {

	Load(".\\Game\\Textures\\BakerHouse.fbx");
	struct aiLogStream stream;
	stream.callback = myCallback;
	aiAttachLogStream(&stream);
	return true;

}

void Model::Load(const char* file) {
	std::string s = file;
	if (s.substr(s.rfind('.'), s.length()) == ".fbx" || s.substr(s.rfind('.'), s.length()) == ".FBX") {

		CleanUp();
		LoadScene(file);
	}
	else {
		CleanMaterials();
		texturePath = file;
		LoadExternalMaterial();
	}
}

void Model::LoadScene(const char* file) {
	fileName = file;
	const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadMaterials(scene);
		LoadMeshes(scene);
	}
	else
	{
		LOG("Error loading %s: %s\n", file, aiGetErrorString());
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
			std::string filename = fileName.substr(0, fileName.rfind('\\'));
			texturePath = filename + "\\" + file.data;
			GLuint texture = App->texture->LoadTexture(texturePath.c_str());
			if (texture) {
				materials.push_back(texture);
				LOG("[INFO] Texture loaded correctly\n");
			}
		}
	}
	if (materials.size() == 0) {

		LoadMaterialFromModelPath();
	}
}

void Model::LoadMaterialFromModelPath() {

	char defaultFolder[MAX_BUFF_FOLDER];
	char textureExt[MAX_BUFF_EXT];
	App->editor->config->GetTextureFolder(defaultFolder);
	App->editor->config->GetTextureExt(textureExt);
	texturePath = fileName.substr(0, fileName.find(".")) + textureExt;
	LOG("[INFO] Checking in the folder where the model was loaded: %s\n", texturePath.c_str());
	GLuint texture = App->texture->LoadTexture(texturePath.c_str());
	if (texture) {
		materials.push_back(texture);
		LOG("[INFO] Texture loaded correctly\n");
	}
	else {
		if (defaultFolder[0] == '\0') {
			GetCurrentDirectoryA(MAX_BUFF_FOLDER, defaultFolder);
		}
		std::string filename = fileName.substr(fileName.rfind('\\'), fileName.length());
		texturePath = defaultFolder + filename.substr(0, filename.rfind(".")) + textureExt;
		LOG("[INFO] Checking in the Default Texture folder: %s\n", texturePath.c_str());
		GLuint texture = App->texture->LoadTexture(texturePath.c_str());
		if (texture) {
			materials.push_back(texture);
			LOG("[INFO] Texture loaded correctly\n");
		}
		else {
			LOG("[WARNING] Impossible to Load a Texture for this model.\n");
			materials.push_back(0);
			texturePath = "";
		}
	}
}

void Model::LoadExternalMaterial() {

	GLuint texture = App->texture->LoadTexture(texturePath.c_str());
	if (texture) {
		materials.push_back(texture);
		LOG("[INFO] Texture loaded correctly\n");
	}
	else {
		LOG("[WARNING] Impossible to Load this Texture.\n");
		materials.push_back(0);
		texturePath = "";
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
	//TODO : Change bouncing box calculation - Use MathGeoLib for instance 
	float radius = 0.0f;
	for (std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		float3 max = (*it)->GetMaxDistance();
		if (radius < max.x) {
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
	float dist = radius / sin(fov / 2);
	App->editor->inspector->SetCameraPosition(float3(0, 1, -dist));
	camera->UpdateFrontFrustum(float3::unitZ);
	camera->UpdateUpFrustum(float3::unitY);
}

void Model::CleanMeshes() {
	for (std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		RELEASE(*it);
	}
	meshes.clear();
}

void Model::CleanMaterials() {
	for (std::vector<GLuint>::iterator it = materials.begin(); it != materials.end(); it++) {

		App->texture->DeleteTexture(*it);
	}
	materials.clear();
}

bool Model::CleanUp() {

	CleanMeshes();
	CleanMaterials();

	return true;
}