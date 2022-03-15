#pragma once
#include "Entity.h"
#include <string>

class Rectangle;

class Player :
    public Entity
{
private:

    int moveSpeed{ 3 };
    int diagonalSpeed = sqrt((pow(moveSpeed, 2) / 2));
    int m_fireSpeed;
    int m_projectileTime;
    
    int m_damageTime;
    int m_damageSpeed;

public:

    Player(const std::string& currentSprite, int posX, int posY);
    ~Player() override final;

    void Update(World* world) override final;
    void checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType type) override final;

};
