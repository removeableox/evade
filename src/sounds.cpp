#include "sounds.h"

void Sounds::playSound(Mix_Chunk* chunk, int loops, int volume)
{
    Mix_VolumeChunk(chunk, volume); 
    Mix_PlayChannel(-1, chunk, loops);
}

