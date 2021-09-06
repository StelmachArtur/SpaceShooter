#include "Enemy.h"

Enemy::Enemy(Texture* texture, Time& a)
{
		
		this->hp_ = a.asSeconds() / 3 + 1;
		this -> enemy_.setTexture(*texture);
		this->enemy_.setScale(0.12f, 0.12f);
		this->enemy_.setPosition(rand() % 750, -50.f);
		std::cout << this->hp_ << " ";
}
void Enemy::Draw(RenderTarget & window) {
	window.draw(this->enemy_);
}
void Enemy::Update(RenderTarget & window) {

	float pos = this->enemy_.getPosition().x;
	if (this->id_ == 1) {
		if (pos >= 3 && this->enemy_.getGlobalBounds().width + pos + 3 < window.getSize().x)
			this->enemy_.move(rand() % 7 - 3, 1);
		else if (!(pos >= 3))
			this->enemy_.move(rand() % 4, 1);
		else
			this->enemy_.move(rand() % 4 - 3, 1);
	}
	else {
		if (pos <= 1 && cos(phase_++ % 360 * M_PI / 180.0) < 0)
			this->enemy_.move(0, 1);
		else if(pos + this->enemy_.getGlobalBounds().width >=800 && cos(phase_++ % 360 * M_PI / 180.0) > 0)
			this->enemy_.move(0, 1);
		else
			this->enemy_.move(cos(phase_++ % 360 *M_PI/180.0),1);
	}
}


Enemy::~Enemy()
{
}
