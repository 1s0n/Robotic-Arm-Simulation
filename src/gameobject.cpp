#include "gameobject.h"

GameObject::GameObject()
{
    x = 0;
    y = 0;
    hitboxWidth = 0;
    hitboxHeight = 0;
}

GameObject::~GameObject()
{
    
}

bool hasCollided(GameObject other)
{
    if (other.hitboxHeight == 0 || other.hitboxWidth == 0)
    {

        return false;
    }

    return false;
}