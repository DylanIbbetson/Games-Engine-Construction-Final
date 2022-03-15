#pragma once
#include "Entity.h"

class Rectangle;


class Enemy :
    public Entity
{
private:

    int moveSpeed{  1 };

public:

    Enemy(const std::string& currentSprite, int posX, int posY);
    ~Enemy() override final;

    void Update(World* world) override final;
    void checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType type) override final;

    Direction m_direction{ Direction::eDown };
};

