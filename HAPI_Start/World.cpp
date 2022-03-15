#include "World.h"
#include "Visualisation.h"
#include "Player.h"
#include "Rectangle.h"
#include "Entity.h"
#include "Enemy.h"
#include "Background.h"
#include "Projectile.h"
#include "ctime"
#include <iostream>


World::World()
{
	m_Visualise = new Visualisation;
	
	m_menu = true;

	m_lose = false;
	m_tickSpeed = 20;
	m_time = 0;
	m_score = 0;
	m_projectileIndex = 0;
	m_enemyIndexStart = 0;
	m_enemyIndexEnd = 0;
	m_projectileIndexStart = 0;
	m_projectileIndexEnd = 0;

	//Initialising the window
	if (!m_Visualise->Initialise(m_Visualise->getScreenWidth(), m_Visualise->getScreenHeight()))
		return;
}

World::~World()
{
	delete m_Visualise;

	//Deleting the entities from the entity vector
	for (auto& entity : m_entityVector)
	{
		delete entity;
	}
}

void World::LoadLevel()
{
	//Loading in textures and creating sprites
	if (!m_Visualise->CreateSprite("Background", "Data\\UnfinishedMap.png", 0))
		return;

	if (!m_Visualise->CreateSprite("PlayerDown", "Data\\Character\\Character_Down.png", 4))
		return;

	if (!m_Visualise->CreateSprite("PlayerRight", "Data\\Character\\Character_Right.png", 4))
		return;

	if (!m_Visualise->CreateSprite("PlayerUp", "Data\\Character\\Character_Up.png", 4))
		return;

	if (!m_Visualise->CreateSprite("PlayerLeft", "Data\\Character\\Character_Left.png", 4))
		return;

	if (!m_Visualise->CreateSprite("EnemyLeft", "Data\\Enemy\\Enemy_Left.png", 4))
		return;

	if (!m_Visualise->CreateSprite("EnemyUp", "Data\\Enemy\\Enemy_Up.png", 4))
		return;

	if (!m_Visualise->CreateSprite("EnemyRight", "Data\\Enemy\\Enemy_Right.png", 4))
		return;

	if (!m_Visualise->CreateSprite("EnemyDown", "Data\\Enemy\\Enemy_Down.png", 4))
		return;

	if (!m_Visualise->CreateSprite("ArrowUp", "Data\\Projectiles\\Arrow_Up.png", 0))
		return;

	if (!m_Visualise->CreateSprite("ArrowDown", "Data\\Projectiles\\Arrow_Down.png", 0))
		return;

	if (!m_Visualise->CreateSprite("ArrowLeft", "Data\\Projectiles\\Arrow_Left.png", 0))
		return;

	if (!m_Visualise->CreateSprite("ArrowRight", "Data\\Projectiles\\Arrow_Right.png", 0))
		return;

	 //Loading sounds
	if (!HAPI.LoadSound("Data\\Sounds\\ArrowFire.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\Hit.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\Jab.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\Death1.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\Death2.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\Death3.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\Pain1.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\Pain2.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\BackgroundMusic.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\PlayerDeath.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\PlayerHurt1.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\PlayerHurt2.wav"))
		return;

	if (!HAPI.LoadSound("Data\\Sounds\\PlayerHurt3.wav"))
		return;
	
	//Changing the font
	if (!HAPI.ChangeFontFromFile("Data\\Fonts\\White Storm.otf"))
		return;


	//Creating and pushing back the background entity
	Background* newBackground = new Background("Background", 0, 0);
	m_entityVector.push_back(newBackground);

	//Creating and pushing back a player entity
	Player* newPlayer = new Player("PlayerDown", 460, 320);
	m_entityVector.push_back(newPlayer);


	//Object pool for enemies
	m_enemyIndexStart = m_entityVector.size();

	for (int enemy = 0; enemy <  10; enemy++)
	{
		m_entityVector.push_back(new Enemy("EnemyRight", 0, 0));
	}
	m_enemyIndexEnd = m_entityVector.size();


	//Object pool for projectiles
	m_projectileIndexStart = m_entityVector.size();
	for (int i = 0; i < 10; i++)
	{
		m_entityVector.push_back(new Projectile("ArrowRight", 0, 0));
	}
	m_projectileIndexEnd = m_entityVector.size();
}

void World::FireProjectile(int posX, int posY, Direction currentDirection)
{
	//Loop that looks for projectiles that aren't alive and sets the new positions and direction to them and sets them to be alive
	for (int i = m_projectileIndexStart; i < m_projectileIndexEnd; i++)
	{
		if (!m_entityVector[i]->getIsAlive())
		{
			m_entityVector[i]->setCurrentPosition(posX, posY);
			m_entityVector[i]->setCurrentDirection(currentDirection);
			m_entityVector[i]->setIsAlive(true);
			return;
		}
	}
}

void World::SpawnEnemy()
{
	//Loop finds enemy entities that aren't alive
	for (int i = m_enemyIndexStart; i < m_enemyIndexEnd; i++)
	{
		if (!m_entityVector[i]->getIsAlive())
		{
			//Randomises which of the 4 channels the enemy spawns from, and in random positions within that channel
			switch (rand() % 4)
			{
				//Left spawn
			case 0:
				m_entityVector[i]->setCurrentPosition(-80, rand() % 200 + 250);
				break;

				//Top spawn
			case 1:
				m_entityVector[i]->setCurrentPosition((rand() % 300) + 350, -80);
				break;

				//Bottom spawn
			case 2:
				m_entityVector[i]->setCurrentPosition(rand() % 300 + 350, 780);
				break;

				//Right spawn
			case 3:
				m_entityVector[i]->setCurrentPosition(1024, rand() % 200 + 250);
				break;

			default:
				break;
			}
			
			//Sets the direction, sets the entity to alive and gives it a random health value
			m_entityVector[i]->setCurrentDirection(Direction::eDown);
			m_entityVector[i]->setIsAlive(true);
			m_entityVector[i]->setHealth(rand() % 3 + 1);
		
			return;
		}
	}
}

void World::Reset()
{
	//Resets everything to it's default value to allow the game to reset properly
	m_lose = false;
	m_time = 0;
	m_score = 0;
	
	m_entityVector[1]->setCurrentPosition(460, 320);


	//Loops through every entity that isn't the background or player entity and kills them 
	for (auto& entity : m_entityVector)
	{
		if (entity != m_entityVector[1] && entity != m_entityVector[0])
		{
			entity->Kill();
		}
	}

	//Sets the player to alive and resets health value
	m_entityVector[1]->setIsAlive(true);
	m_entityVector[1]->setHealth(10);
}

void World::Run()
{
	srand(time(NULL));
	DWORD previousTime, currentTime;
	DWORD previousClockTime, currentClockTime;

	//Time variable for the game tick
	previousTime = HAPI.GetTime();

	//Time varible for in-game timer
	previousClockTime = HAPI.GetTime();

	int frameRate = 0;

	//Plays background music
	HAPI.PlaySound("Data\\Sounds\\BackgroundMusic.wav", HAPI_TSoundOptions(0.025, true));

	while (HAPI.Update())
	{
		currentTime = HAPI.GetTime();
		currentClockTime = HAPI.GetTime();

		keyboard = HAPI.GetKeyboardData();
		controller = HAPI.GetControllerData(0);

		//Main menu display
		if (m_menu)
		{
			m_Visualise->RenderSprite("Background", 0, 0, false);

			HAPI.RenderText(360, 200, HAPI_TColour::BLACK, "Orc Onslaught", 70);

			HAPI.RenderText(360, 340, HAPI_TColour::BLACK, "Press Enter to play", 50);

			if (getKeyboardData().scanCode[HK_RETURN])
			{
				m_menu = false;
			}
		}

		//Lose screen 
		else if (m_lose)
		{
			//Renders an empty background sprite with no entities on it
			m_Visualise->RenderSprite("Background", 0, 0, false);
			
			HAPI.RenderText(430, 200, HAPI_TColour::BLACK, "You died!", 60);
			HAPI.RenderText(350, 280, HAPI_TColour::BLACK, "You killed  " + std::to_string(m_score) + " orcs!", 50);

			HAPI.RenderText(350, 340, HAPI_TColour::BLACK, "Press Enter to play again", 50);
			HAPI.RenderText(350, 400, HAPI_TColour::BLACK, "Press Escape to return to menu", 50);

			if (getKeyboardData().scanCode[HK_RETURN])
			{
				Reset();
			}

			else if (getKeyboardData().scanCode[HK_ESCAPE])
			{
				m_menu = true;
			}

		}

		//If not in a lose state or in the main menu, the game runs
		else
		{
			//Game tick
			if (currentTime - previousTime >= m_tickSpeed)
			{
				//Updating every entity
				for (Entity* entity : m_entityVector)
				{
					entity->Update(this);
				}

				SpawnEnemy();

				//Player against background
				m_entityVector[1]->checkCollisions(m_entityVector[0]->getHitBoxes(), Side::eNeutral, EntityType::eBackground);

				//Enemy against Enemy, projectile and background
				for (int enemy1 = m_enemyIndexStart; enemy1 < m_enemyIndexEnd; enemy1++)
				{
					m_entityVector[1]->checkCollisions(m_entityVector[enemy1]->getHitBoxes(), Side::eEnemy, EntityType::eEnemy);
					m_entityVector[enemy1]->checkCollisions(m_entityVector[0]->getHitBoxes(), Side::eNeutral, EntityType::eBackground);

					if (m_entityVector[enemy1]->getIsAlive())
					{
						for (int arrow = m_projectileIndexStart; arrow < m_projectileIndexEnd; arrow++)
						{
							if (m_entityVector[arrow]->getIsAlive())
							{
								m_entityVector[enemy1]->checkCollisions(m_entityVector[arrow]->getHitBoxes(), Side::eFriendly, EntityType::eProjectile);
							}
						}
					}
				}

				//Arrow against background and enemy
				for (int arrow = m_projectileIndexStart; arrow < m_projectileIndexEnd; arrow++)
				{
					if (m_entityVector[arrow]->getIsAlive())
					{
						m_entityVector[arrow]->checkCollisions(m_entityVector[0]->getHitBoxes(), Side::eNeutral, EntityType::eBackground);
						for (int enemy = m_enemyIndexStart; enemy < m_enemyIndexEnd; enemy++)
						{
							if (m_entityVector[enemy]->getIsAlive())
							{
								m_entityVector[arrow]->checkCollisions(m_entityVector[enemy]->getHitBoxes(), Side::eEnemy, EntityType::eEnemy);
							}
						}
					}
				}
				previousTime = currentTime;
			}

			//Clears the screen
			m_Visualise->clearScreen();

			//Loops through each entity
			for (Entity* entity : m_entityVector)
			{
				//Checks if the entity is alive
				if (entity->getIsAlive())
				{
					//Checks whether the frame index is greater than the max frame index, which in this case is 3
					if (entity->getCurrentFrame() > m_Visualise->getMaxFrames(entity->getCurrentSprite()) - 1)
					{
						entity->setCurrentFrame(0);
					}

					//Creates screen and texture rectangles used for texture clipping
					Rectangle screenRectangle(0, m_Visualise->getScreenWidth(), 0, m_Visualise->getScreenHeight());
					Rectangle textureRectangle(0, m_Visualise->getFrameWidth(entity->getCurrentSprite()), 0, m_Visualise->getTextureHeight(entity->getCurrentSprite()));

					//Passing the current sprites and rectangles into the graphics system to clip them
					m_Visualise->Clip(entity->getCurrentSprite(), screenRectangle, textureRectangle, entity->getPosX(), entity->getPosY(), entity->getCurrentFrame());

					//Resets the framerate to 0 to keep animation running normally
					if (frameRate >= 10)
					{
						entity->setCurrentFrame(entity->getCurrentFrame() + 1);
						frameRate = 0;
					}
					else
					{
						frameRate++;
					}
				}
			}

			//Game tick management
			if (currentClockTime - previousClockTime >= 1000)
			{
				m_time++;
				previousClockTime = currentClockTime;
			}

			//Rendering the UI on the screen during gameplay
			HAPI.RenderText(325, 0, HAPI_TColour::BLACK, "Health: " + std::to_string(m_entityVector[1]->getHealth()), 30);
			HAPI.RenderText(325, 30, HAPI_TColour::BLACK, "Orcs killed: " + std::to_string(m_score), 30);
			HAPI.RenderText(325, 60, HAPI_TColour::BLACK, "Time: " + std::to_string(m_time), 30);
		}
	}
}




