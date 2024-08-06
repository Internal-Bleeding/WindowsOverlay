#include "Textures.h"


Textures::Textures() :index(0)
{

	

}

Textures::~Textures()
{
	textures.clear();
}

void Textures::add(const MyTexture& texture)
{
	textures.push_back(texture);
}

void Textures::create()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	float vertices[] = {
			-1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, -1.0f,    1.0f, 1.0f,
			-1.0f,  1.0f,   0.0f, 0.0f,
			1.0f, 1.0f,     1.0f,  0.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2, (void*)(sizeof(vec2)));
}


void Textures::render()
{
	glBindTexture(GL_TEXTURE_2D, textures[index].GetId());
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}