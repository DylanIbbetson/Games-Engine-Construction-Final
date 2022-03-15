#include "Player.h"
#include "World.h"
#include "Rectangle.h"

Player::Player(const std::string& currentSprite, int posX, int posY) :
	Entity(currentSprite, posX, posY)

{
	//Sets default values
	m_fireSpeed = 30;
	m_projectileTime = 0;

	m_damageTime = 0;
	m_damageSpeed = 45;

	Rectangle Hitbox;
	m_hitBoxes.push_back(Hitbox);

	m_side = Side::eFriendly;
	m_type = EntityType::ePlayer;

	Health = 10;

}

Player::~Player()
{
}




void Player::Update(World* world)
{

	//Handles controller inputs
	if (world->getControllerData().isAttached)
	{
		//Movement
		if ((world->getControllerData().digitalButtons[HK_DIGITAL_DPAD_UP]))
		{
			m_posY -= moveSpeed;
		}

		else if ((world->getControllerData().digitalButtons[HK_DIGITAL_DPAD_LEFT]))
		{
			m_posX -= moveSpeed;

		}

		else if ((world->getControllerData().digitalButtons[HK_DIGITAL_DPAD_DOWN]))
		{
			m_posY += moveSpeed;
		}

		else if ((world->getControllerData().digitalButtons[HK_DIGITAL_DPAD_RIGHT]))
		{
			m_posX += moveSpeed;
		}

		//Firing projectiles
		if ((world->getControllerData().digitalButtons[HK_DIGITAL_Y]))
		{
			m_currentSprite = "PlayerUp";
			if (m_projectileTime >= m_fireSpeed)
			{
				world->FireProjectile(m_posX + 30, m_posY - 5, Direction::eUp);
				HAPI.PlaySound("Data\\Sounds\\ArrowFire.wav", HAPI_TSoundOptions(0.1));
				m_projectileTime = 0;
			}

		}
		else if ((world->getControllerData().digitalButtons[HK_DIGITAL_A]))
		{
			m_currentSprite = "PlayerDown";
			if (m_projectileTime >= m_fireSpeed)
			{
				world->FireProjectile(m_posX + 30, m_posY + 35, Direction::eDown);
				HAPI.PlaySound("Data\\Sounds\\ArrowFire.wav", HAPI_TSoundOptions(0.1));
				m_projectileTime = 0;
			}
		}
		else if ((world->getControllerData().digitalButtons[HK_DIGITAL_X]))
		{
			m_currentSprite = "PlayerLeft";
			if (m_projectileTime >= m_fireSpeed)
			{
				world->FireProjectile(m_posX - 10, m_posY + 35, Direction::eLeft);
				HAPI.PlaySound("Data\\Sounds\\ArrowFire.wav", HAPI_TSoundOptions(0.1));
				m_projectileTime = 0;
			}
		}

		else if ((world->getControllerData().digitalButtons[HK_DIGITAL_B]))
		{
			m_currentSprite = "PlayerRight";
			if (m_projectileTime >= m_fireSpeed)
			{
				world->FireProjectile(m_posX + 40, m_posY + 35, Direction::eRight);
				HAPI.PlaySound("Data\\Sounds\\ArrowFire.wav", HAPI_TSoundOptions(0.2));
				m_projectileTime = 0;
			}
		}
	}
	//Handles keyboard inputs
//////////////////////////////////////////////////////////

	//Movement
	if(world->getKeyboardData().scanCode['W'])
	{
		m_moving = true;

		m_posY -= moveSpeed;
		m_currentSprite = "PlayerUp";
		
		m_currentDirection = Direction::eUp;
	}

	else if (world->getKeyboardData().scanCode['A'])
	{
		m_moving = true;

		m_posX -= moveSpeed;
		m_currentSprite = "PlayerLeft";
		
		m_currentDirection = Direction::eLeft;
	}

	else if (world->getKeyboardData().scanCode['S'])
	{
		m_moving = true;

		m_posY += moveSpeed;
		m_currentSprite = "PlayerDown";

		m_currentDirection = Direction::eDown;
	}

	else if (world->getKeyboardData().scanCode['D'])
	{
		m_moving = true;

		m_posX += moveSpeed;
		m_currentSprite = "PlayerRight";

		m_currentDirection = Direction::eRight;
	}

	else
	{
		m_moving = false;
		if (m_moving == false)
		{
			setCurrentFrame(0);
		}
	}

	//Projectile firing
	if (world->getKeyboardData().scanCode[HK_RIGHT])
	{
		m_currentSprite = "PlayerRight";
		if (m_projectileTime >= m_fireSpeed)
		{
			world->FireProjectile(m_posX + 40, m_posY + 35, Direction::eRight);
			HAPI.PlaySound("Data\\Sounds\\ArrowFire.wav", HAPI_TSoundOptions(0.2));
			m_projectileTime = 0;
		}
	}

	else if (world->getKeyboardData().scanCode[HK_LEFT])
	{
		m_currentSprite = "PlayerLeft";
		if (m_projectileTime >= m_fireSpeed)
		{
			world->FireProjectile(m_posX - 10, m_posY + 35, Direction::eLeft);
			HAPI.PlaySound("Data\\Sounds\\ArrowFire.wav", HAPI_TSoundOptions(0.1));
			m_projectileTime = 0;
		}
	}

	else if (world->getKeyboardData().scanCode[HK_UP])
	{
		m_currentSprite = "PlayerUp";
		if (m_projectileTime >= m_fireSpeed)
		{
			world->FireProjectile(m_posX + 30, m_posY - 5, Direction::eUp);
			HAPI.PlaySound("Data\\Sounds\\ArrowFire.wav", HAPI_TSoundOptions(0.1));
			m_projectileTime = 0;
		}
	}

	else if (world->getKeyboardData().scanCode[HK_DOWN])
	{
		m_currentSprite = "PlayerDown";
		if (m_projectileTime >= m_fireSpeed)
		{
			world->FireProjectile(m_posX + 30, m_posY + 35, Direction::eDown);
			HAPI.PlaySound("Data\\Sounds\\ArrowFire.wav", HAPI_TSoundOptions(0.1));
			m_projectileTime = 0;
		}
	}


	//Kill key for testing purposes
	else if (world->getKeyboardData().scanCode['K'])
	{
		setHealth(0);
	}

	//If player health reaches 0, sets the player hitbox to 0,0 and kills the player entity
	if (Health == 0)
	{
		m_hitBoxes[0].left = 0;
		m_hitBoxes[0].right = 0;
		m_hitBoxes[0].top = 0;
		m_hitBoxes[0].bottom = 0;

		HAPI.PlaySound("Data\\Sounds\\PlayerDeath.wav", HAPI_TSoundOptions(0.1));
		Kill();

		//Sets game to a lose state
		world->setLose(true);
	}

	m_projectileTime++;
	m_damageTime++;

	//Updates player hitboxes
	m_hitBoxes[0].left = m_posX - 5;
	m_hitBoxes[0].right = m_posX + world->getWindow()->getFrameWidth(m_currentSprite) - 5;
	m_hitBoxes[0].top = (m_posY + world->getWindow()->getTextureHeight(m_currentSprite) / 2);
	m_hitBoxes[0].bottom = m_posY + world->getWindow()->getTextureHeight(m_currentSprite);

}

void Player::checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType team)
{
	//Loops through the hitboxes that are passed into the function
	for (auto& Rectangle : otherHitbox)
	{
		if ((m_hitBoxes[0].right < Rectangle.left || m_hitBoxes[0].left > Rectangle.right || m_hitBoxes[0].top > Rectangle.bottom || m_hitBoxes[0].bottom < Rectangle.top))
		{
			//Returns false
		}
		else
		{
			//Collisions against background hitboxes
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
			

			//Collisions against enemy hitboxes
			if (otherSide == Side::eEnemy && team == EntityType::eEnemy)
			{
				if (m_damageTime >= m_damageSpeed)
				{
					switch (rand() % 3)
					{
					case 0:
						HAPI.PlaySound("Data\\Sounds\\PlayerHurt1.wav", HAPI_TSoundOptions(0.2));
						Health--;
						m_damageTime = 0;
						break;

					case 1:
						HAPI.PlaySound("Data\\Sounds\\PlayerHurt2.wav", HAPI_TSoundOptions(0.2));
						Health--;
						m_damageTime = 0;
						break;

					case 2:
						HAPI.PlaySound("Data\\Sounds\\PlayerHurt3.wav", HAPI_TSoundOptions(0.2));
						Health--;
						m_damageTime = 0;
						break;

					default:
						break;

					}
				}
				
			}



		}
	}


}

