#include <iostream>
#include "hero.h"
#include <SFML/Audio/Sound.hpp>



int dir = 0;

void Hero::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}


void Hero::colizion(float& playerX, float& playerY, int& health, float npcY, float npcX, int& damageTimer, int& maxDamageTimer, sf::Sound sDamage) {
	if (playerX > 1700)
	{
		playerX = 1701;
	}
	if (playerX < 40)
	{
		playerX = 39;
	}

}




void Hero::move(sf::RenderWindow& window, float&  playerX, float& playerY, float time, float& CurrentFrame, bool& Idle)
{

	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		dir = 1;
		CurrentFrame += 0.005 * time; 
		if (CurrentFrame > 4) CurrentFrame -= 3; 
		if (CurrentFrame != 0) {
			sprite.setTextureRect(sf::IntRect(1024 * int(CurrentFrame), 3072, 1024, 1024));
		}
		Idle = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		dir = 2;
		CurrentFrame += 0.005 * time; 
		if (CurrentFrame > 4) CurrentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(1024 * int(CurrentFrame), 3072, -1024, 1024));
		Idle = false;
	}
	else {
		if (Idle == true) {
			CurrentFrame += 0.005 * time; 
			if (CurrentFrame > 3) CurrentFrame -= 2; 
			sprite.setTextureRect(sf::IntRect(1024 * int(CurrentFrame), 2048, 1024, 1024));
		}
		if (Idle == false) {
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 2; 
			sprite.setTextureRect(sf::IntRect(1024 * int(CurrentFrame), 2048, -1024, 1024));
		}
	}


    sprite.setPosition(playerX, playerY);

}




void Hero::healthIndicator(sf::RenderWindow& window, int& health)
{
	sf::Texture healthB;
	healthB.loadFromFile("otherData/health/0.png");
	sf::Sprite healthBar(healthB);
	healthBar.setPosition(0, 900);
	healthBar.scale(sf::Vector2f(0.5, 0.5));
	switch (health)
	{
	case 0:
		healthB.loadFromFile("otherData/health/0.png");
		window.draw(healthBar);
		break;
	case 1:
		healthB.loadFromFile("otherData/health/1.png");
		window.draw(healthBar);
		break;
	case 2:
		healthB.loadFromFile("otherData/health/2.png");
		window.draw(healthBar);
		break;
	case 3:
		healthB.loadFromFile("otherData/health/3.png");
		window.draw(healthBar);
		break;
	case 4:
		healthB.loadFromFile("otherData/health/5.png");
		window.draw(healthBar);
		break;
	case 5:
		healthB.loadFromFile("otherData/health/4.png");
		window.draw(healthBar);
		break;
	default:
		break;
	}
}

void Hero::update(float& playerX, float& playerY, float time)
{
	switch (dir) {
	case 1:
		playerX -= 0.2 * time;
		break;
	case 2:
		playerX += 0.2 * time;
		break;
	}

}
