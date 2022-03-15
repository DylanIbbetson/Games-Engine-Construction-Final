#pragma once

#include <vector>
#include <HAPI_lib.h>
#include "Visualisation.h"

using namespace HAPISPACE;

class Rectangle;
class Entity;

enum class Direction;
enum class EntityType;
enum class Side;

class World
{
private:

	int m_tickSpeed;
	int m_projectileIndex;
	int m_enemyIndexStart;
	int m_enemyIndexEnd;
	int m_projectileIndexStart;
	int m_projectileIndexEnd;
	int m_score;
	int m_time;

	bool m_lose;
	bool m_menu;
	
	Visualisation* m_Visualise = nullptr;

	std::vector<Entity*> m_entityVector;

	HAPI_TKeyboardData keyboard;
	HAPI_TControllerData controller;

public:
	World();
	~World();

	void Run();
	void LoadLevel();
	void FireProjectile(int posX, int posY, Direction currentDirection);
	void SpawnEnemy();
	void Reset();

	void setLose(bool lose) { m_lose = lose; }
	void scoreIncrease(int score) { m_score += score; }

	const HAPI_TKeyboardData& getKeyboardData() const { return keyboard; }

	const HAPI_TControllerData& getControllerData() const { return controller; }

	std::vector<Entity*> GetEntities() const { return m_entityVector; }

	Visualisation* getWindow() const { return m_Visualise; }

	
};

