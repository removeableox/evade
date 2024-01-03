#ifndef ENTITY_H
#define ENTITY_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>

class Entity
{
public:
  float x, y;
  int w, h;
  int angle = 0;
  SDL_Texture *texture;
  std::vector<int> color;
	std::vector<Entity> projectiles;
	int increment;

  Entity(float x, float y, int w, int h, SDL_Texture *tex);
  Entity(float x, float y, int w, int h, std::vector<int> color);
  bool isColliding(Entity entity);
  void checkBorders(int WIDTH);
	bool isOnTop(Entity entity);
};

#endif // ENTITY_H
