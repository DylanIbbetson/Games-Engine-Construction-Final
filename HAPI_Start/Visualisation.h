#pragma once
#include <HAPI_lib.h>
#include <unordered_map>

using namespace HAPISPACE;
class Entity;
class Rectangle;
class Sprite;

class Visualisation
{

private:

	//Creating an unordered map
	std::unordered_map<std::string, Sprite*> m_spriteMap;
	int m_screenWidth{ 1024 };
	int m_screenHeight{ 768 };
	BYTE* m_screen{ nullptr };
	

public:
	Visualisation();
	~Visualisation();

	bool CreateSprite(const std::string& spriteName, const std::string& filename, int maxFrames);
	void RenderSprite(const std::string& spriteName, int m_posX, int m_posY, bool m_alpha);

	void Clip(const std::string& spriteName, const Rectangle& m_screenRect, const Rectangle& m_textureRect, int m_posX, int m_posY, int currentFrame);

	bool Initialise(int m_screenWidth, int m_screenHeight);

	int getScreenWidth() const { return m_screenWidth; }
	int getScreenHeight() const { return m_screenHeight; }

	int getTextureWidth(const std::string& spriteName);
	int getTextureHeight(const std::string& spriteName);

	int getFrameWidth(const std::string& spriteName);
	int getMaxFrames(const std::string& spriteName);

	void clearScreen();

};

