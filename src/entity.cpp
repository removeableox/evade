#include "entity.h"
#include <random>
#include <iostream>
#include <vector>

Entity::Entity(float x, float y, int w, int h, SDL_Texture *tex)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    texture = tex;
}
Entity::Entity(float x, float y, int w, int h, std::vector<int> color)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->color = color;
}
bool Entity::isColliding(Entity entity)
{
    if (
        x < entity.x + entity.w &&
        x + w > entity.x &&
        y < entity.y + entity.h &&
        y + h > entity.y)
    {
        return true;
    }
    return false;
}
void Entity::checkBorders(int WIDTH)
{
    if (x < w * -1)
    {
        x = WIDTH;
    }
    if (x > WIDTH)
    {
        x = w * -1;
    }
}
bool Entity::isOnTop(Entity entity) 
{
	if (
			y + h >= entity.y &&
			y < entity.y + entity.h  
		 )
	{
		return true;
	}
	return false;
}
