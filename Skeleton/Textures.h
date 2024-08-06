#pragma once

#include "framework.h"
#include <vector>
#include "MyTexture.h"

class Textures
{
private:
	unsigned int vao, vbo;
	std::vector<MyTexture> textures;
	size_t index;
public:
	Textures();

	void add(const MyTexture& texture);

	const MyTexture& current() const { return textures[index]; }

	void create();

	void render();

	~Textures();
};

