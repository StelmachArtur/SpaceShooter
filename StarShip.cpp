#include "StarShip.h"



StarShip::StarShip(Texture* texture)
{
	this->texture_ = texture;
	this->sprite_.setTexture(*(this->texture_));
	this->sprite_.setScale(0.1, 0.1);
	this->sprite_.setPosition(400, 500);

	std::fstream config("config.txt", std::ios::in);

	std::vector<std::string> configData;
	std::string l;
	while (config.good()) {
		std::getline(config, l);
		configData.push_back(l);
	}
	this->shootingSpeed_ = std::stoi(configData[1]);
	this->upTimeer_ = 10000;
	//this->bulletTime_.asMicroseconds();
	this->hpMax_ = std::stoi(configData[3]);
	this->hp_ = std::stoi(configData[5]);
	this->up_ = false;
	this->bulletDmg_ = std::stoi(configData[7]);

	this->timeBullet_.asMilliseconds();

	if (!this->font.loadFromFile("Fonts\\arial.ttf")) {
		std::cout << "Failed to load arial font";
	}
	this->text_.setString("HP: 10/10");
	this->text_.setFont(this->font);
	this->text_.setCharacterSize(20);
	this->text_.setFillColor(Color(255, 255, 255, 192));
	this->text_.setPosition(700.f, 0.f);
}

void StarShip::Move(RenderTarget &window) {
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if(this->sprite_.getPosition().x>0){
			this->sprite_.move(-10, 0.0);
		}
	
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (this->sprite_.getPosition().x + this->sprite_.getGlobalBounds().width < window.getSize().x ) {
			this->sprite_.move(+10, 0.0);
		}
	}
	Time a = clockBullet_.getElapsedTime();
	if (a.asMilliseconds() - bulletTime_.asMilliseconds() >= this->shootingSpeed_) {
	if (Keyboard::isKeyPressed(Keyboard::Space)){
		
			if (this->bulletDmg_<15) {
				Bullet* bullet = new Bullet(false,this->bulletDmg_);
				bullet->bullet_.setPosition(this->sprite_.getPosition().x + this->sprite_.getGlobalBounds().width / 2 - bullet->bullet_.getGlobalBounds().width / 2, this->sprite_.getPosition().y);
				this->bullets_.push_back(bullet);
			}
			
			else{
				Bullet* bullet = new Bullet(true, this->bulletDmg_);

				bullet->bullet_.setPosition(this->sprite_.getPosition().x + this->sprite_.getGlobalBounds().width / 2 - bullet->bullet_.getGlobalBounds().width / 2, this->sprite_.getPosition().y);
				this->bullets_.push_back(bullet);
			}
			
			bulletTime_ = clockBullet_.getElapsedTime();
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::P)) {
		this->shootingSpeed_ -= 20;
		
	}
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		this->shootingSpeed_ += 20;
	}
}

StarShip::~StarShip()
{
}

void StarShip::Draw(RenderTarget &window) {

	for (auto itr = bullets_.begin(); itr != bullets_.end(); itr++) {
		(*itr)->Draw(window);
	}
	window.draw(sprite_);
	window.draw(text_);
	
}
void StarShip::Update(Clock* clock, RenderTarget &window) {
	this->Move(window);
	for (auto itr = bullets_.begin(); itr != bullets_.end(); itr++) {
	(*itr)->Update();
	}
	text_.setString(std::to_string(this->hp_) + "/" + std::to_string(this->hpMax_)+"hp");
}