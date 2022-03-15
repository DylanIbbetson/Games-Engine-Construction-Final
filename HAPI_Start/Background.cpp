#include "Background.h"
#include "Rectangle.h"

Background::Background(const std::string& currentSprite, int posX, int posY) :
	Entity(currentSprite, posX, posY)
{
	//Sets default values
	//Pushes back hitbox positions on the background

	Rectangle TopLeft(0, 298, 0, 242);
	m_hitBoxes.push_back(TopLeft);

	Rectangle TopRight(725, 1024, 0, 242);
	m_hitBoxes.push_back(TopRight);

	Rectangle BottomLeft(0, 298, 520, 768);
	m_hitBoxes.push_back(BottomLeft);

	Rectangle BottomRight(725, 1024, 520, 768);
	m_hitBoxes.push_back(BottomRight);

	m_side = Side::eNeutral;
}

Background::~Background()
{
}

void Background::checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType team)
{
}



void Background::Update(World* world)
{
}
