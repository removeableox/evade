#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"
#include <iostream>

class TextHandler {
	public:
		SDL_Surface* text;
		SDL_Texture* text_texture;
		void render(SDL_Renderer* renderer, TTF_Font* font, std::string msg, SDL_Color color, int x, int y);
		void cleanUp();
};

#endif
