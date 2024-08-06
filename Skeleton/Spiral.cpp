#include "Spiral.h"

Spiral::Spiral(float turn, float width, float pitch, size_t resolution) :turn(turn), width(1 / width), pitch(pitch), resolution(resolution)
{
	rotationMat = mat4{ 1, 0, 0, 0,    // MVP matrix, 
							0, 1, 0, 0,    // row-major!
							0, 0, 1, 0,
							0, 0, 0, 0.8 };

	size = resolution * turn;
}

void Spiral::create()
{

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate and bind VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	vec2* vertices = new vec2[size];

	float a = 0.003f;
	int n = 0;
	float t;
	while (n < size)
	{
		float t = n * M_PI * 2 * turn / size;
		//theta = t* t*  size;
		float r = a * pow(M_E, pitch * t);
		float x = r * cosf(t);
		float y = r * sinf(t);
		vertices[n] = vec2(x, y);
		n++;

		r *= width;
		x = r * cosf(t);
		y = r * sinf(t);
		if (n < size)
		{
			vertices[n] = vec2(x, y);
			n++;
		}
		else {
			break;
		}

	}

	glBufferData(GL_ARRAY_BUFFER, 	// Copy to GPU target
		sizeof(vec2) * size,  // # bytes
		vertices,	      	// address
		GL_STATIC_DRAW);	// we do not change later

	glEnableVertexAttribArray(0);  // AttribArray 0
	glVertexAttribPointer(0,       // vbo -> AttribArray 0
		2, GL_FLOAT, GL_FALSE, // two floats/attrib, not fixed-point
		0, NULL); 		     // stride, offset: tightly packed

	delete[] vertices;



}

void Spiral::update(float _turn, float _width, float _pitch, size_t _resolution)
{
	turn = _turn;
	resolution = _resolution;
	width = _width;
	pitch = _pitch;

	size = resolution * turn;

	glBindVertexArray(vao);

	vec2* vertices = new vec2[size];

	float a = 0.003f;
	int n = 0;
	float t;
	while (n < size)
	{
		float t = n * M_PI * 2 / resolution;
		//theta = t* t*  size;
		float r = a * pow(M_E, pitch * t);
		float x = r * cosf(t);
		float y = r * sinf(t);
		vertices[n] = vec2(x, y);
		n++;

		r *= width;
		x = r * cosf(t);
		y = r * sinf(t);
		if (n < size)
		{
			vertices[n] = vec2(x, y);
			n++;
		}
		else {
			break;
		}

	}

	std::cout << size << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vec2) * size,
		vertices,
		GL_STATIC_DRAW);

	delete[] vertices;

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}

}

void Spiral::render()
{
	glBindVertexArray(vao);  // Draw call
	glDrawArrays(GL_TRIANGLE_STRIP, 0 /*startIdx*/, size /*# Elements*/);
}