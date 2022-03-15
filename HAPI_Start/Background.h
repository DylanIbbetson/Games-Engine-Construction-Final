#pragma once
#include "Entity.h"

class Rectangle;

class Background :
    public Entity
{
private:

public:
    Background(const std::string& currentSprite, int posX, int posY);
    ~Background() override final;

    void checkCollisions(std::vector<Rectangle> otherHitbox, Side otherSide, EntityType type) override final;
    
    void Update(World* world) override final;

};

