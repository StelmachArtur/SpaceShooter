#include "Bullet.h"



Bullet::Bullet(bool up, int dmg):dmg_(dmg)
{
	if (up) {
		if (!this->bulletTexture_.loadFromFile("Textures\\laser.png")) {
			std::cout << " Failed to load a bullet.";
		}
	}
	else {
		if (!this->bulletTexture_.loadFromFile("Textures\\bullet.png")) {
			std::cout << " Failed to load a bullet.";
		}
	}

	this->bullet_.setTexture(bulletTexture_);
	this->bullet_.setScale(0.1f, 0.1f);
}

void Bullet::Draw(RenderTarget &window) {
	window.draw(this->bullet_);
}

void Bullet::Move() {
	this->bullet_.move(0, -10.f);
}

void Bullet::Update() {
	this->Move();
}

Bullet::~Bullet()
{
}
