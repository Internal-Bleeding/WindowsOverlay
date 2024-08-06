#pragma once
class MyTexture
{
private:
	unsigned int textureId;
	float aspectRatio;

public:
	MyTexture(const char* filename);

	const unsigned int GetId() const { return textureId; }


	const float GetRatio() const { return aspectRatio; }
};

