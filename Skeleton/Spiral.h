#pragma once

#include "framework.h"

class Spiral
{
private:
	unsigned int vao;
	unsigned int vbo;
	size_t size;
	float width;
	float pitch;
	float turn;
	float resolution;
	mat4 rotationMat;

public:

	Spiral(float turn = 3, float width = 1.0f, float pitch = 0.2f, size_t resolution = 100);

	float GetWidth() { return width; }

	void SetWidth(float w) { width += w; }
	void SetSteepnes(float d) { pitch += d; }

	void create();
	void update(float _turn, float _width, float _pitch, size_t _resolution);
	void animate();
	void render();
};

