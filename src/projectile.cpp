#include "projectile.h"

void Projectile::shootFrom(Entity &entity, int increment) {
	std::vector<int> c = {color[0], color[1], color[2], color[3]};
	Entity projectile(
			entity.x + increment * 3,
			entity.y + entity.h/2 - 12.5f,
			25, 25, c
			);
	projectile.increment = increment;
	entity.projectiles.push_back(projectile);
}
void Projectile::renderProjectiles(RenderWindow window, Entity &entity) {
	for (Entity &p : entity.projectiles) {
		p.x += p.increment;
		window.render(p);
	}
}
