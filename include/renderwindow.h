#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "SDL2/SDL.h"
#include <iostream>
#include "./entity.h"

class RenderWindow
{
public:
  SDL_Window *window;
  SDL_Renderer *renderer;

  void create(std::string title, int width, int height);
  void clear();
  void render(Entity &entity);
  void display();
  void cleanUp();
  SDL_Texture *loadTexture(std::string path);
  void gameLoop(void (*loop)());
};

#endif
