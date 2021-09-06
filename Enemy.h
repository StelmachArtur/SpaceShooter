#pragma once
#include "Bullet.h"
class Enemy
{
public:
	Texture enemyTexture_;
	Sprite enemy_;
	int id_;
	int hp_;

	int phase_;
	
	
	void Draw(RenderTarget& window);
	void Update(RenderTarget& window);
	
	Enemy() = default;
	Enemy(Texture * texture, Time& a);
	~Enemy();
};

