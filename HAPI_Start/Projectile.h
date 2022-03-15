#pragma once
#include "Entity.h"

class Rectangle;
class World;

class Projectile :
    public Entity
{


private:
    int m_moveAmount = 5;

   

public:
    Projectile(const std::string& currentSprite, int posX, int posY);
    ~Projectile() override final;

    void Update(World* world) override final;
    void checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType type) override final;

    
};

