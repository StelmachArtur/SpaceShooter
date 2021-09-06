#include "up.h"



up::up(int hp):hp_(hp)
{
	if (!upTexture_.loadFromFile("Textures\\up.png")) {
		std::cout << " Failed to load a up png texture.";
	}
	upSprite_.setTexture(upTexture_);
	time = 0;
	this->upSprite_.setScale(0.5f, 0.5f);
	this->upSprite_.setPosition(rand() % 750, -50.f);
}
void up::Draw(RenderTarget& window) {
	window.draw(this->upSprite_);
}

void up::Update() {
	this->Move();
}

void up::Move() {
	this->upSprite_.move(0.f, 5.f);
}

up::~up()
{
}
