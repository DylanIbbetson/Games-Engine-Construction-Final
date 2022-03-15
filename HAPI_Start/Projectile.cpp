#include "Projectile.h"
#include "Rectangle.h"
#include "World.h"


Projectile::Projectile(const std::string& currentSprite, int posX, int posY) :
	Entity(currentSprite, posX, posY)

{
	//Sets default values
	m_alive = false;
	m_side = Side::eFriendly;
	m_type = EntityType::eProjectile;
	Rectangle Hitbox;
	m_hitBoxes.push_back(Hitbox);

}

Projectile::~Projectile()
{
}


void Projectile::Update(World* world)
{
	//Checks if the projectile entity is alive
	if (m_alive)
	{
		if (m_currentDirection == Direction::eRight)
		{
			m_posX += m_moveAmount;
			m_currentSprite = "ArrowRight";
		}

		else if (m_currentDirection == Direction::eLeft)
		{
			m_posX -= m_moveAmount;
			m_currentSprite = "ArrowLeft";
		}

		else if (m_currentDirection == Direction::eUp)
		{
			m_posY -= m_moveAmount;
			m_currentSprite = "ArrowUp";
		}

		else if (m_currentDirection == Direction::eDown)
		{
			m_posY += m_moveAmount;
			m_currentSprite = "ArrowDown";
		}
		
		//Checks projectile position against window dimensions to kill it once it leaves the screen
		if (m_posX >= world->getWindow()->getScreenWidth() || 
			m_posX <= (0 - world->getWindow()->getTextureWidth(m_currentSprite)) || 
			m_posY >= world->getWindow()->getScreenHeight() || 
			m_posY <= (0 - world->getWindow()->getTextureHeight(m_currentSprite)))
		{
			Kill();
		}

	}

	//Updates hitbox positions
	m_hitBoxes[0].left = m_posX;
	m_hitBoxes[0].right = m_posX + world->getWindow()->getTextureWidth(m_currentSprite);
	m_hitBoxes[0].top = m_posY;
	m_hitBoxes[0].bottom = m_posY + world->getWindow()->getTextureHeight(m_currentSprite);
	
}

void Projectile::checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType team)
{
	//Checks the hitbox that is passed in
	for (auto& Rectangle : otherHitbox)
	{
		//If the hitboxes don't match
		if ((m_hitBoxes[0].right < Rectangle.left || m_hitBoxes[0].left > Rectangle.right || m_hitBoxes[0].top > Rectangle.bottom || m_hitBoxes[0].bottom < Rectangle.top))
		{
			//Returns false
		}
		else
		{
			Kill();
		}
	}

}

