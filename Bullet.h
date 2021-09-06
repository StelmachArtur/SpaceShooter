#pragma once
#include "up.h"

class Bullet
{
public:
	
	Sprite bullet_;
	Texture bulletTexture_;

	int dmg_;
	
	void Draw(RenderTarget &window);
	void Update();
	void Move();
	Bullet(bool up,int dmg);
	~Bullet();
};

