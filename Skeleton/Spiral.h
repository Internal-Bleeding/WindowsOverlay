#pragma once

#include "framework.h"

class Spiral
{
private:
	unsigned int vao;
	unsigned int vbo;
	size_t size;
	float width;

public:

	Spiral(size_t size, float width = 1.25f);

	void Create();
	void Update();
};

