#pragma once
#include <HAPI_lib.h>
using namespace HAPISPACE;
class Rectangle;

class Sprite


{
private:

	BYTE* m_texture{ nullptr };

	int m_textureWidth = 0;
	int m_textureHeight = 0;

	int m_frameWidth = 0;
	int m_maxFrames;
	

public:
	Sprite(int maxFrames);
	~Sprite();

	bool Load(const std::string& filename);
	void Render(BYTE* m_screen, int m_screenWidth, int m_screenHeight, int posX, int posY, bool m_alpha);
	
	void Clip(BYTE* m_screen, const Rectangle& screenRectangle, const Rectangle& textureRectangle, int posX, int posY, int currentFrame);

	int getTextureWidth() const { return m_textureWidth; }
	int getTextureHeight() const { return m_textureHeight; }
	int getMaxFrames() const { return m_maxFrames; }
	int getFrameWidth() const { return m_frameWidth; }
};

