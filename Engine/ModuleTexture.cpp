#include "ModuleTexture.h"
#include "Application.h"
#include "IL/il.h"
#include "GL/glew.h"

bool ModuleTexture::Init() {

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		LOG("Incorrect IL version installed");
		return false;
	}
	ilInit();
	image = LoadTexture("lenna.png");

	return true;
}

GLuint ModuleTexture::LoadTexture(const char* shader_file_name) {

	unsigned imageId;
	GLuint image;
	ilGenImages(1, &imageId);
	ilBindImage(imageId);
	if (!ilLoadImage(shader_file_name)) {

		LOG("The texture hasn't been loaded corectly");
		return false;
	}
	ILinfo info;
	iluGetImageInfo(&info);

	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */

	ilDeleteImages(1, &imageId);
	return image;
}

bool ModuleTexture::DeleteTexture(GLuint &image) {

	glDeleteTextures(1, &image);
	return true;
}
bool ModuleTexture::CleanUp() {
	DeleteTexture(image);
	return true;
}

