#pragma once
#include <cmath>
#include <string>
#include <vector>

class World;
class Rectangle;


enum class Direction
{
	eUp,
	eDown,
	eRight,
	eLeft
};

enum class Side
{
	eEnemy,
	eFriendly,
	eNeutral
};


enum class EntityType
{
	ePlayer,
	eEnemy,
	eProjectile,
	eBackground
};

class Entity
{
protected:

	std::vector<Rectangle> m_hitBoxes;

	Direction m_currentDirection = Direction::eDown;

	int m_posX;
	int m_posY;
	int Health{ 1 };
	int m_currentFrame;

	bool m_moving;
	bool m_alive{ true };

	Side m_side;
	EntityType m_type;

	std::string m_currentSprite;
	

public:


	Entity(const std::string& currentSprite, int posX, int posY);
	virtual ~Entity() = default;


	virtual void Update(World* world) = 0;
	virtual void checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType type) = 0;
	
	void Kill() { m_alive = false; }

	void setCurrentFrame(int currentFrame) { m_currentFrame = currentFrame; }
	void setCurrentPosition(int posX, int posY);
	void setCurrentDirection(Direction direction);
	void setIsAlive(bool m_alive);
	void setHealth(int HP);

	bool getMoving() const { return m_moving; }
	bool getIsAlive() const { return m_alive; }
	int getPosX() { return m_posX; }
	int getPosY() { return m_posY; }
	int getCurrentFrame() const { return m_currentFrame; }
	int getHealth() { return Health; }
	

	std::string getCurrentSprite() const { return m_currentSprite; }
	std::vector<Rectangle> getHitBoxes() const { return m_hitBoxes; }


};

