#pragma once
#define _USE_MATH_DEFINES
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include <cmath>
#include <vector>
#include<iostream>
#include<cstdlib>
#include <fstream>
#include <string>
using namespace sf;

class up
{
public:
	Texture upTexture_;
	Sprite upSprite_;
	double time;	
	int hp_;

	void Move();
	void Draw(RenderTarget& window);
	void Update();
	up(int hp);
	~up();
};

