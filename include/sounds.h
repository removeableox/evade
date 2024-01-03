#ifndef SOUNDS_H
#define SOUNDS_H

#include "SDL2/SDL_mixer.h"

class Sounds {
	public:
		void playSound(Mix_Chunk* chunk, int loops, int volume);
};

#endif
