#pragma once
#include "Enemy.h"
class Game;
class StarShip
{
public:

	//starship
	Vector2f position_;
	Sprite sprite_;
	Texture *texture_;
	Time bulletTime_;

	Font font;
	Text text_;


	//bullets
	std::vector<Bullet*> bullets_;
	
	Clock clockBullet_;
	Time timeBullet_;
	double shootingSpeed_;
	double upTimeer_;
	bool up_;
	int hp_;
	int hpMax_;

	Time upTime_;
		
	int bulletDmg_;
	
	StarShip(Texture* texture);
	~StarShip();
	void Draw(RenderTarget &window);
	void Move(RenderTarget &window);
	void Update(Clock * clock, RenderTarget &window);
};

