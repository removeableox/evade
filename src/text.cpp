#include "text.h"

void TextHandler::render(SDL_Renderer* renderer, TTF_Font* font, std::string msg, SDL_Color color, int x, int y) {
	text = TTF_RenderText_Solid(font, msg.c_str(), color);

	text_texture = SDL_CreateTextureFromSurface( renderer, text );

	SDL_Rect dest = { x, y, text->w, text->h };

	SDL_RenderCopy(renderer, text_texture, nullptr, &dest);
}
void TextHandler::cleanUp() {
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(text);
}
