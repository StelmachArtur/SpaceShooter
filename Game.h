#pragma once

#include "StarShip.h"


class Game
{
public:
	//Window
	RenderWindow *window_;

	//Starship
	StarShip* starship_;
	Texture starshipTexture_;

	bool active;
	//Enemys
	std::vector<Enemy> enemys_;
	Texture enemyTexture1_;
	Texture enemyTexture2_;
	
	//game clock
	Clock clock_;
	Time time_;
	
	int sheduledUpAppear;
	Time lastSpawn_;
	Time lastUpSpawn_;
	//Fonts
	Font font_;
	Text text_;

	//Upgrades
	up* myUp;
	//Background
	Sprite background_;
	Texture backgroundTexture_;

	Texture laserTexture_;
	Texture bulletTexture_;

	//Player stats
	int score_;

	//functions
	void Draw();
	void spawnEnemys();
	void Update();

	//constructor
	Game(RenderWindow* window);
	~Game();
};

