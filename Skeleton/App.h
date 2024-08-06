#pragma once

#include "Spiral.h"
#include "framework.h"
#include "Textures.h"

class App
{
private:
	Spiral spiral;
	HWND hwnd;
	GPUProgram foreground;
	GPUProgram background;
	Textures textures;
	vec3 foregroundColor;
	vec3 backgroundColor;
	float rotationSpeed;
	mat4 rotationMat;

	void makeWindowTransparent(int alpha);

public:
	App();

	void setWindowHandle(HWND handle) { hwnd = handle; }
	const vec3 getForegroundColor() const { return foregroundColor; }
	const vec3 getBackroundColor() const { return backgroundColor; }

	void create();
	void loadFromFile(const char* filePath);
	void render();

	~App();
};

extern App* app;

