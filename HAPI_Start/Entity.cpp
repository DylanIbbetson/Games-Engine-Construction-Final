#include "Entity.h"
#include "Rectangle.h"

Entity::Entity(const std::string& currentSprite, int posX, int posY)
{
	//Sets default values for entities
	m_currentSprite = currentSprite;

	m_posX = posX;
	m_posY = posY;

	m_currentFrame = 0;

	m_moving = false;

}

void Entity::setCurrentPosition(int posX, int posY)
{
	m_posX = posX;
	m_posY = posY;
}

void Entity::setCurrentDirection(Direction direction)
{
	m_currentDirection = direction;
}

void Entity::setIsAlive(bool alive)
{
	m_alive = alive;
}

void Entity::setHealth(int HP)
{
	Health = HP;
}
