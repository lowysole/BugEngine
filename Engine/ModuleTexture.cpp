#include "ModuleTexture.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "UIConfiguration.h"
#include "Model.h"
#include "IL/il.h"
#include "GL/glew.h"
#include "Math/float2.h"


bool ModuleTexture::Init() {

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		LOG("Incorrect IL version installed\n");
		return false;
	}
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	return true;
}

GLuint ModuleTexture::LoadTexture(const char* shader_file_name) {
	unsigned imageId;
	GLuint image;
	ilGenImages(1, &imageId);
	ilBindImage(imageId);
	if (!ilLoadImage(shader_file_name)) {

		LOG("The texture hasn't been loaded correctly\n");
		App->model->SetTextureSize(0, 0);
		return false;
	}
	ILinfo info;
	iluGetImageInfo(&info);
	App->model->SetTextureSize(info.Width, info.Height);
	glGenTextures(1, &image);
	ApplyFilters(image);

	ilDeleteImages(1, &imageId);
	return image;
}

void ModuleTexture::ApplyFilters(GLuint image) {

	//TODO: Optimize this function
	bool minmap = false;
	const char* wrap = App->editor->config->GetWrapFilter();
	const char* mag = App->editor->config->GetMagFilter();
	const char* min = App->editor->config->GetMinFilter();
	glBindTexture(GL_TEXTURE_2D, image);
	int _wrap = 0;
	if (wrap == "GL_REPEAT")
		_wrap = GL_REPEAT;
	else if (wrap == "GL_CLAMP")
		_wrap = GL_CLAMP;
	else if (wrap == "GL_CLAMP_TO_BORDER")
		_wrap = GL_CLAMP_TO_BORDER;
	else if (wrap == "GL_MIRRORED_REPEAT")
		_wrap = GL_MIRRORED_REPEAT;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, _wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap);

	if (mag == "GL_LINEAR")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	else if (mag == "GL_NEAREST")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	else if (mag == "GL_NEAREST_MIPMAP_NEAREST") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		minmap = true;
	}
	else if (mag == "GL_LINEAR_MIPMAP_NEAREST") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		minmap = true;
	}
	else if (mag == "GL_NEAREST_MIPMAP_LINEAR") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		minmap = true;
	}
	else if (mag == "GL_LINEAR_MIPMAP_LINEAR") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		minmap = true;
	}

	if (min == "GL_LINEAR")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	else if (min == "GL_NEAREST")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	else if (min == "GL_NEAREST_MIPMAP_NEAREST") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		minmap = true;
	}
	else if (min == "GL_LINEAR_MIPMAP_NEAREST") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		minmap = true;
	}
	else if (min == "GL_NEAREST_MIPMAP_LINEAR") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		minmap = true;
	}
	else if (min == "GL_LINEAR_MIPMAP_LINEAR") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		minmap = true;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
	if (minmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
		glGenerateTextureMipmap(image);
	}
}


bool ModuleTexture::DeleteTexture(GLuint& image) {

	glDeleteTextures(1, &image);
	return true;
}
bool ModuleTexture::CleanUp() {
	return true;
}

