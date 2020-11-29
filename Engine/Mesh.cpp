#include "Mesh.h"
#include "GL/glew.h"
#include "Math/float2.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "leak.h"

void Mesh::LoadVBO(const aiMesh* mesh)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	unsigned vertexSize = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned bufferSize = vertexSize * mesh->mNumVertices;
	float* data = new float[bufferSize];
	float xMax = 0.0f;
	float yMax = 0.0f;
	float zMax = 0.0f;
	for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
		int j = i * 5;
		data[j] = mesh->mVertices[i].x;
		data[j+1] = mesh->mVertices[i].y;
		data[j+2] = mesh->mVertices[i].z;
		data[j+3] = mesh->mTextureCoords[0][i].x;
		data[j+4] = mesh->mTextureCoords[0][i].y;

		if (data[j] > abs(xMax)) xMax = abs(data[j]);
		if (data[j + 1] > abs(yMax)) yMax = abs(data[j + 1]);
		if (data[j + 2] > abs(zMax)) zMax = abs(data[j + 2]);
	}
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW);
	delete[] data;
	numVertices = mesh->mNumVertices;
	maxX = xMax;
	maxY = yMax;
	maxZ = zMax;
}

void Mesh::LoadEBO(const aiMesh* mesh)
{
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	for (unsigned i = 0; i < mesh->mNumFaces; ++i)
	{
		assert(mesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		*(indices++) = mesh->mFaces[i].mIndices[0];
		*(indices++) = mesh->mFaces[i].mIndices[1];
		*(indices++) = mesh->mFaces[i].mIndices[2];
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	numIndices = index_size;
	numFaces = mesh->mNumFaces;
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 5), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (sizeof(float) * 5), (void*)(sizeof(float) * 3));
	glBindVertexArray(0);
}

void Mesh::Draw(const std::vector<unsigned>& model_textures)
{
	unsigned program = App->program->GetProgramId();
	const float4x4& view = App->camera->GetViewMatrix();
	const float4x4& proj = App->camera->GetProjectionMatrix();
	model = float4x4::identity;
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model_textures[materialIndex]);
	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}