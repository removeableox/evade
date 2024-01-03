#include "entity.h"
#include "renderwindow.h"
#include "gravity.h"
#include "projectile.h"
#include "text.h"
#include "sounds.h"

#include <iostream>
#include <random>

RenderWindow window;
TextHandler text;
Camera camera;
Sounds sounds;

int WIDTH = 900;
int HEIGHT = 500;

bool running = true;
bool startMenu = true;
int score = 0;
int highScore = 0;

SDL_Texture *startMenuTex;

TTF_Font* font;

Mix_Chunk* song;
Mix_Chunk* killSound;
Mix_Chunk* laserShoot;

bool init()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	window.create("Game Jam", WIDTH, HEIGHT);

	font = TTF_OpenFont("res/fonts/pixels.ttf", 36);

	song = Mix_LoadWAV("res/sounds/song.wav");
	killSound = Mix_LoadWAV("res/sounds/kill.wav");
	laserShoot = Mix_LoadWAV("res/sounds/laserShoot.wav");

	sounds.playSound(song, -1, 128);

	startMenuTex = window.loadTexture("res/textures/startMenu.png");

	return true;
}

bool load = init();

Projectile projectile;

std::vector<Entity> tiles;

Entity startMenuElement(0, 0, 900, 500, {0, 0, 0, 255});

std::vector<int> tileColor = {57, 97, 128, 255};
std::vector<int> spriteColor = {217, 238, 255, 255};

Entity player(WIDTH/2-25, HEIGHT-150, 50, 50, spriteColor);
Gravity playerGravity(player);

Entity ground(0, HEIGHT - 100, WIDTH, 100, {tileColor});
Entity ceiling(0, 0, WIDTH, 100, {tileColor});

std::vector<Entity> ais;

void preLoop()
{
	tiles.push_back(ground);
	tiles.push_back(ceiling);
	projectile.color = tileColor;
	startMenuElement.texture = startMenuTex;
}

int speedX = 10;
int jumps = 0;
int frames = 0;
int projectileSpeed = 20;
int projectileIncrement;

int projectileDelayAmount = 120;
int projectileDelayCounter = 0;

int numberOfAis = 0;

void end()
{
	startMenu = true;
	if (score > highScore) {highScore = score;}
	frames = 0;
	projectileDelayCounter = 0;
	numberOfAis = 0;

	player.projectiles = {};
	ais = {};
}

void gameLoop()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
		else if (event.key.keysym.sym == SDLK_SPACE && startMenu)
		{
			startMenu = false;
			score = 0;
			player.projectiles = {};
			ais = {};

		}
		else if (event.key.keysym.sym == SDLK_w && jumps < 4)
		{
			playerGravity.initialVelocity = 40;
			playerGravity.initialY = player.y;
			playerGravity.time = 0;
			player.y -= 10;
			jumps += 1;
		}
		else if (event.key.keysym.sym == SDLK_SPACE && !startMenu && projectileDelayCounter == projectileDelayAmount)
		{
			projectileDelayAmount = 30;
			projectileDelayCounter = 0;
			projectile.shootFrom(player, projectileIncrement);
			sounds.playSound(laserShoot, 0, 128);
		}
	}

	if (projectileDelayCounter < projectileDelayAmount)
	{
		projectileDelayCounter++;
	}

	if (startMenu)
	{
		window.clear();
		window.render(startMenuElement);
		text.render(window.renderer, font, "SCORE:" + std::to_string(score), {57, 97, 128, 255}, 62.5, 365);
		text.render(window.renderer, font, "HIGHSCORE:" + std::to_string(highScore), {57, 97, 128, 255}, 62.5, 400);
		text.render(window.renderer, font, "MADE BY", {57, 97, 128, 255}, WIDTH-212.5, 365);
		text.render(window.renderer, font, "CALEB COSTA", {57, 97, 128, 255}, WIDTH-300, 400);
	}
	else
	{
		std::vector<std::vector<Entity>> allEntities = {tiles};
		camera.cameraUpdate(allEntities);

		if (frames<30) {frames++;}
		int keys;
		const Uint8 *K = SDL_GetKeyboardState(&keys);

		int keysPressed = 0;

		for (int i = 0; i < keys; i++)
		{
			if (K[i])
			{
				keysPressed++;
			}
		}

		if (keysPressed > 0)
		{
			if (K[SDL_SCANCODE_A])
			{
				player.x -= speedX;
				projectileIncrement = projectileSpeed * -1;
			}
			else if (K[SDL_SCANCODE_D])
			{
				player.x += speedX;
				projectileIncrement = projectileSpeed;
			}

			player.checkBorders(WIDTH);
		}

		window.clear();

		if (frames == 30 && numberOfAis < 6)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(0,2);
			int random = dist(gen);
			if (random == 0)
			{
				Entity ai(0, HEIGHT - ground.h - 50, 25, 50, {57, 97, 128, 255});
				ais.push_back(ai);
			}
			else
			{
				Entity ai(WIDTH, HEIGHT - ground.h - 50, 25, 50, {57, 97, 128, 255});
				ais.push_back(ai);
			}
			frames = 0;
			numberOfAis++;
		}

		for (size_t i = 0; i < ais.size(); i++)
		{
			for (size_t j = 0; j < player.projectiles.size(); j++)
			{
				if (player.projectiles[j].isColliding(ais[i]))
				{
					player.projectiles.erase(player.projectiles.begin() + j);
					ais.erase(ais.begin() + i);
					score++;
					sounds.playSound(killSound, 0, 50);
					numberOfAis -= 1;
				}
				if (player.projectiles[j].isColliding(player))
				{
					end();
				}
			}
			if (ais[i].isColliding(player))
			{
				end();
			}
			if (player.x > ais[i].x)
			{
				ais[i].x += speedX / 4;
			}
			else if (player.x < ais[i].x)
			{
				ais[i].x -= speedX / 4;
			}
			window.render(ais[i]);
		}

		bool colliding = false;

		for (Entity &tile : tiles)
		{
			if (player.isOnTop(tile))
			{
				colliding = true;
			}
		}
		if (!colliding)
		{
			playerGravity.increment();
		}
		else
		{
			jumps = 0;
			player.y = ground.y - player.h;
		}

		projectile.renderProjectiles(window, player);

		window.render(ground);
		window.render(ceiling);
		window.render(player);
	}

	text.render(window.renderer, font, "SCORE:" + std::to_string(score), {134, 166, 191, 255}, WIDTH-150, 0);

	window.display();
}

int main(int argc, char *argv[])
{
	preLoop();

	while (running)
	{
		window.gameLoop(gameLoop);
	}


	window.cleanUp();
	text.cleanUp();

	return 0;
}
