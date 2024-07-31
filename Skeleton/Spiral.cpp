#include "Spiral.h"

Spiral::Spiral(size_t size, float width) :size(size), width(1 / width) {}

void Spiral::Create()
{
	glGenVertexArrays(1, &vao);	// get 1 vao id
	glBindVertexArray(vao);		// make it active

	unsigned int vbo;		// vertex buffer object
	glGenBuffers(1, &vbo);	// Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	vec2* vertices = new vec2[size];

	float a = 100 * M_PI / 180;
	int n = 0;
	float b = 1 / tanf(a);
	for (float t = 0.0f; t < 40; t += 0.1f)
	{
		if (n < size)
		{
			float r = a * pow(M_E, b * t);
			float x = r * cosf(t);
			float y = r * sinf(t);
			vertices[n] = vec2(x, y);
			n++;

			r *= width;
			x = r * cosf(t);
			y = r * sinf(t);
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

}

void Spiral::Update()
{
	glBindVertexArray(vao);  // Draw call
	glDrawArrays(GL_TRIANGLE_STRIP, 0 /*startIdx*/, size /*# Elements*/);
}