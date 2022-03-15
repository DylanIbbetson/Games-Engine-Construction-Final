#include "Visualisation.h"
#include "Sprite.h"
#include "entity.h"
#include "Rectangle.h"

using namespace HAPISPACE;


Visualisation::Visualisation()
{

}

Visualisation::~Visualisation()
{
	//A destructor to delete the data of the unordered map
	for (auto& p : m_spriteMap)
		delete p.second;
}

bool Visualisation::CreateSprite(const std::string& spriteName, const std::string& filename, int maxFrames)
{
	Sprite* newSprite = new Sprite(maxFrames);

	if (!newSprite->Load(filename))
	{
		delete newSprite;
		return false;
	}
	//Inserting new sprites into the unordered map
	m_spriteMap[spriteName] = newSprite;
	
	return true;
}

void Visualisation::RenderSprite(const std::string& spriteName, int posX, int posY, bool m_alpha)
{
	

	if (m_spriteMap.find(spriteName) == m_spriteMap.end())
		return;
	//Calling the render function on the contents of the unordered map
	m_spriteMap[spriteName]->Render(m_screen, m_screenWidth, m_screenHeight, posX, posY, m_alpha);
}

void Visualisation::Clip(const std::string& spriteName, const Rectangle& m_screenRect, const Rectangle& m_textureRect, int posX, int posY, int currentFrame)
{
	if (m_spriteMap.find(spriteName) == m_spriteMap.end())
		return;

	m_spriteMap[spriteName]->Clip(m_screen, m_screenRect, m_textureRect, posX, posY, currentFrame);

}

bool Visualisation::Initialise(int m_screenWidth, int m_screenHeight)
{
	//Initialising the window
	if (!HAPI.Initialise(m_screenWidth, m_screenHeight))
		return false;

	m_screen = HAPI.GetScreenPointer();

	HAPI.SetShowFPS(true);
	
	return true;
}

//Getter functions to return data
////////////////////////////////////////

int Visualisation::getTextureWidth(const std::string& spriteName)
{
	return (m_spriteMap[spriteName]->getTextureWidth());
}

int Visualisation::getTextureHeight(const std::string& spriteName)
{
	return (m_spriteMap[spriteName]->getTextureHeight());
}
int Visualisation::getFrameWidth(const std::string& spriteName)
{
	return (m_spriteMap[spriteName]->getFrameWidth());
}
int Visualisation::getMaxFrames(const std::string& spriteName)
{
	return (m_spriteMap[spriteName]->getMaxFrames());
}
void Visualisation::clearScreen()
{
	for (int i = 0; i < m_screenWidth * m_screenHeight; i++)
	{
		memcpy(m_screen + (size_t)i * 4, &HAPI_TColour::BLACK, 4);
	}


}
