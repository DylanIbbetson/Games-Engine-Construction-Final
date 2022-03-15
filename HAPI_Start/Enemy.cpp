#include "Enemy.h"
#include "World.h"
#include "Rectangle.h"
#include <iostream>
#include <string>

Enemy::Enemy(const std::string& currentSprite, int posX, int posY) :
	Entity(currentSprite, posX, posY)
{
	//Sets default values of enemy entity
	m_side = Side::eEnemy;
	m_type = EntityType::eEnemy;
	Rectangle hitbox;
	m_hitBoxes.push_back(hitbox);

	m_alive = false;
}
Enemy::~Enemy()
{
}

void Enemy::Update(World* world)
{
	//Updates hitboxes
	m_hitBoxes[0].left = m_posX + 25;
	m_hitBoxes[0].right = m_posX + world->getWindow()->getFrameWidth(m_currentSprite) - 25;
	m_hitBoxes[0].top = m_posY + 30;
	m_hitBoxes[0].bottom = m_posY + world->getWindow()->getTextureHeight(m_currentSprite);

	//Enemy AI that chases the player hitboxes
	if (m_hitBoxes[0].left > world->GetEntities()[1]->getHitBoxes()[0].right - 10)
	{
		m_posX -= moveSpeed;
		m_currentSprite = "EnemyLeft";
		m_moving = true;
	}

	else if (m_hitBoxes[0].right < world->GetEntities()[1]->getHitBoxes()[0].left + 10)
	{
		m_posX += moveSpeed;
		m_currentSprite = "EnemyRight";
		m_moving = true;
	}

	else if (m_hitBoxes[0].top > world->GetEntities()[1]->getHitBoxes()[0].bottom - 10)
	{
		m_posY -= moveSpeed;
		m_currentSprite = "EnemyUp";
		m_moving = true;
	}
	else if (m_hitBoxes[0].bottom < world->GetEntities()[1]->getHitBoxes()[0].top + 10)
	{
		m_posY += moveSpeed;
		m_currentSprite = "EnemyDown";
		m_moving = true;
	}

	//If the enemy dies
	if (Health <= 0)
	{
		//Play one of 3 death sounds and increase score
		switch (rand() % 3)
		{
		case 0:
			HAPI.PlaySound("Data\\Sounds\\Death1.wav", HAPI_TSoundOptions(0.2));
			world->scoreIncrease(1);
			Kill();
			break;

		case 1:
			HAPI.PlaySound("Data\\Sounds\\Death2.wav", HAPI_TSoundOptions(0.2));
			world->scoreIncrease(1);
			Kill();
			break;

		case 2:
			HAPI.PlaySound("Data\\Sounds\\Death3.wav", HAPI_TSoundOptions(0.2));
			world->scoreIncrease(1);
			Kill();
			break;

		default:
			break;
		}
		
	}

}

void Enemy::checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType team)
{
	//Checks against any hitboxes that are passed into the function
	for (auto& Rectangle : otherHitbox)
	{
		if ((m_hitBoxes[0].right < Rectangle.left || m_hitBoxes[0].left > Rectangle.right || m_hitBoxes[0].top > Rectangle.bottom || m_hitBoxes[0].bottom < Rectangle.top))
		{
			//Returns false
		}

		else
		{
			//Background collisions
			if (otherSide == Side::eNeutral && team == EntityType::eBackground)
			{
				switch (m_currentDirection)
				{
				case Direction::eDown:
					m_posY = ((Rectangle.top - m_hitBoxes[0].Height() * 2) - 1);
					break;

				case Direction::eLeft:
					m_posX = Rectangle.right + m_hitBoxes[0].Width() - 55;
					break;

				case Direction::eRight:
					m_posX = Rectangle.left - m_hitBoxes[0].Width() - 1;
					break;

				case Direction::eUp:
					m_posY = Rectangle.bottom - m_hitBoxes[0].Height() + 1;
					break;

				default:
					break;
				}
			}

			
			//Player projectile collisions
			if (otherSide == Side::eFriendly && team == EntityType::eProjectile)
			{
				//Plays one of 2 pain sounds and decreases health
				switch (rand() % 2)
				{
				case 0:
					HAPI.PlaySound("Data\\Sounds\\Pain1.wav", HAPI_TSoundOptions(0.2));
					Health--;
					break;

				case 1:
					HAPI.PlaySound("Data\\Sounds\\Pain2.wav", HAPI_TSoundOptions(0.2));
					Health--;
					break;

				default:
					break;
				}
			}


			/*else if (otherSide == Side::eEnemy)
			{
				switch (m_currentDirection)
				{
				case Direction::eDown:
					if (m_hitBoxes[0].bottom > Rectangle.top)
					{
						m_posY = ((Rectangle.top - m_hitBoxes[0].Height() * 2) - 1);
					}
					break;

				case Direction::eLeft:
					if (m_hitBoxes[0].left > Rectangle.right)
					{
						m_posX = Rectangle.right + 1;
					}
					break;

				case Direction::eRight:
					if (m_hitBoxes[0].right > Rectangle.left)
					{
						m_posX = Rectangle.left - m_hitBoxes[0].Width() - 1;
					}
					break;

				case Direction::eUp:
					if (m_hitBoxes[0].top > Rectangle.bottom)
					{

					}
					break;

				default:
					break;
				}
			}*/

			
		}
	}
}


