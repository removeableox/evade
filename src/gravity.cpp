#include "gravity.h"
#include <iostream>

Gravity::Gravity(Entity &entity) : entity(entity), initialY(entity.y)
{
	this->entity = entity;
	this->initialY = entity.y;
}
void Gravity::increment()
{
	entity.y = a * (time * time) - initialVelocity * time + initialY;
	time += 0.1;
}
