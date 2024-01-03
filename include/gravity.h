#ifndef GRAVITY_H
#define GRAVITY_H

#include "entity.h"

class Gravity
{
public:
	Entity &entity;
	float time = 0;
	float a = 4.9;
	int initialVelocity = 0;
	int initialY = 0;

	Gravity(Entity &entity);
	void increment();
};

#endif
