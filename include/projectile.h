#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"
#include "renderwindow.h"
#include <vector>

class Projectile {
	public:
		std::vector<int> color; 
		void shootFrom(Entity &entity, int increment);
		void renderProjectiles(RenderWindow window, Entity &entity);
};

#endif
