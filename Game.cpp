#include "Game.h"



Game::Game(RenderWindow * window) : window_(window),score_(0)
{
	this->window_->setFramerateLimit(60);
	if (!starshipTexture_.loadFromFile("Textures\\ship.png")) {
		std::cout << " Failed to load a starship.";
	}
	if (!backgroundTexture_.loadFromFile("Textures\\tlo.png")) {
		std::cout << " Failed to load a background.";
	}
	if (!this->enemyTexture1_.loadFromFile("Textures\\enemy1.png")) {
		std::cout << "Failed to load enemy1 texture";
	}
	if (!this->enemyTexture2_.loadFromFile("Textures\\enemy2.png")) {
		std::cout << "Failed to load enemy2 texture";
	}
	if (!this->font_.loadFromFile("Fonts\\arial.ttf")) {
		std::cout << "Failed to load arial font";
	}
	
	if (!this->bulletTexture_.loadFromFile("Textures\\bullet.png")) {
		std::cout << "Failed to load arial font";
	}
	if (!this->laserTexture_.loadFromFile("Textures\\laser.png")) {
		std::cout << "Failed to load arial font";
	}
	
	this->sheduledUpAppear = rand() % 30 + 5;
	this->active = true;
	this->text_.setString("Score: 0");
	this->text_.setFont(this->font_);
	this->text_.setCharacterSize(20);
	this->text_.setFillColor(Color(255,255,255,192));

	this->myUp = nullptr;
	this->starship_ = new StarShip(&(this->starshipTexture_));
	this->background_.setTexture(backgroundTexture_);
	}


Game::~Game()
{
}
//to do zycie, bonus, rozny ruch.
void Game::spawnEnemys() {
	Time time;
	time = this->clock_.getElapsedTime();
	if (time.asMilliseconds() - this->lastSpawn_.asMilliseconds() >= 1000) {
		if (this->enemys_.size() <= 120) {
			this->lastSpawn_ = time;
			if (rand() % 2) {
				Enemy temp = Enemy(&this->enemyTexture1_,time);
				temp.id_ = 1;
				temp.enemy_.setPosition((rand() % 750), -150.f);
				this->enemys_.push_back(temp);
			}
			else {
				Enemy temp = Enemy(&this->enemyTexture2_,time);
				temp.id_ = 2;
				temp.enemy_.setPosition((rand() % 750), -150);
				this->enemys_.push_back(temp);
			}
		}
	}
}

void Game::Draw() {
	window_->clear();
	//this->background_.setScale(window_->getSize().x / background_.getScale().x, window_->getSize().y / background_.getScale().y);
	this->window_->draw(this->background_);
	this->starship_->Draw(*window_);
	for (auto itr = enemys_.begin(); itr != enemys_.end(); itr++) {
		itr->Draw(*window_);
	}
	window_->draw(this->text_);
	if (myUp!=nullptr) {
		myUp->Draw(*window_);
	}
	if (myUp != nullptr) {
		this->myUp->Draw(*window_);
	}
	window_->display();
}

void Game::Update() {
	starship_->Update(&this->clock_,*this->window_);
	//sprawdzamy czy jest upgrade jezli tak sprawdzamy czy zlapany

	if (myUp==nullptr && this->clock_.getElapsedTime().asSeconds() - lastUpSpawn_.asSeconds() > sheduledUpAppear) {
			myUp = new up(this->starship_->bulletDmg_*5);
			lastUpSpawn_ = this->clock_.getElapsedTime();
			this->sheduledUpAppear = rand() % 30 + 5;
	}


	for (auto itr = enemys_.begin(); itr != enemys_.end();) {
		//sprawdzamy czy hit ze statkiem
		if (this->starship_->sprite_.getGlobalBounds().intersects(itr->enemy_.getGlobalBounds())) {
			if (this->starship_->hp_<=5) {
				this->starship_->hp_ -=5;
			
				this->text_.setString("YOU LOST\n Your score was " + std::to_string(score_));
				this->text_.setCharacterSize(50);
				this->text_.setOrigin(text_.getGlobalBounds().width/2, text_.getGlobalBounds().height/2);
				this->text_.setPosition(window_->getSize().x / 2.0, window_->getSize().y / 2.0);
				this->active = false;

			} 
			else {
				this->starship_->hp_ -= 5;
				itr = enemys_.erase(itr);
			}
		}
		//sprawdzamy czy jakis bullet z danym enemy
		for (auto itr2 = starship_->bullets_.begin(); itr2 != starship_->bullets_.end();) {
			if ((itr2)!=starship_->bullets_.end()&&itr->enemy_.getGlobalBounds().intersects((*itr2)->bullet_.getGlobalBounds())) {
				//jezeli enemy ma wiecej zycia niz bullet dmg
				if (itr->hp_ <= this->starship_->bulletDmg_) {
					score_++;
					itr = enemys_.erase(itr);
					itr2 = starship_->bullets_.erase(itr2);
					this->text_.setString("Score: " + std::to_string(score_));
				}
				//jezeli nie
				else {
					itr->enemy_.move(0.f, -10.f);
					itr->hp_ -= this->starship_->bulletDmg_;
					itr2 = starship_->bullets_.erase(itr2);
				}
			}
		
			else {
				itr2++;	
				//std::cout << "xdd" << std::endl;
			}
		}
		if (itr != enemys_.end()) {
			itr->Update(*this->window_);
			itr++;
		}
		
	}
	if (myUp != nullptr) {
		for (auto itr2 = starship_->bullets_.begin(); itr2 != starship_->bullets_.end();) {
			
			if (this->myUp->upSprite_.getGlobalBounds().intersects((*itr2)->bullet_.getGlobalBounds()))
			{
				//jezeli enemy ma wiecej zycia niz bullet dmg
				if (myUp->hp_ <= this->starship_->bulletDmg_) {
					delete myUp;
					myUp = nullptr;
					itr2 = starship_->bullets_.erase(itr2);
					this->starship_->bulletDmg_ += 5;
					break;
				}
				//jezeli nie
				else {
					myUp->upSprite_.move(0.f, -100.f);
					myUp->hp_ -= this->starship_->bulletDmg_;
					itr2 = starship_->bullets_.erase(itr2);
				}
			}

			else {
				itr2++;
				//std::cout << "xdd" << std::endl;
			}
		}
	}
		if (starship_->bullets_ .size()!=0 && starship_->bullets_[0]->bullet_.getPosition().y<=0) {
			starship_->bullets_.erase(starship_->bullets_.begin());
			//std::cout<<"Erased"<<std::endl;
			//this->text_.setString("Score: " + std::to_string(score_++));
			}
		if (enemys_.size() != 0 && this->enemys_[0].enemy_.getPosition().y >= 600) {
			enemys_.erase(enemys_.begin());
			std::cout<<"Erased"<<std::endl;
			//this->text_.setString("Score: " + std::to_string(score_++));
		}
	this->spawnEnemys();

	if (myUp != nullptr && myUp->upSprite_.getPosition().y<=600) {
		this->myUp->Update();
	}
	else if (myUp != nullptr) {
		delete myUp;
		myUp = nullptr;

		std::cout << "Erased myup";
	}

}