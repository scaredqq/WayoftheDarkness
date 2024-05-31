#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <random>
#include <ctime>
#include <sstream>
#include "hero/hero.h"
#include "background.h"
#include "dataBase/dataBase.h"
#include "npc/npc.h"
#include "game/game.h"
#include "menu/mainMenu.h"







float CurrentFrame = 0;
float Frame = 0;
bool Idle;
float backGroundY = 0;
const int numFrames = 6;
float speed;
int health = 5;
int damageTimer = 0;
int maxDamageTimer = 60;
int save = 0;
bool choice;
float npcX = 500;
float npcY = 300;
int spawn;
float dy = 0;
float height = 150;
int score = 0;
const int playerLeftPositioin = 20;
const int playerRightPosition = 80;
const int playerBottomPosition = 100;
int direction;



void scence(sf::RenderWindow& window, float& playerX, float& playerY) {

	srand(static_cast<unsigned>(time(0)));
	sf::Clock clock;

	Hero hero("otherData/ALL/images/heroAnimation.png", 100, 100);
	BackGround BG("otherData/ALL/images/last100.jpg", 0, 0);
	Npc npc("otherData/ALL/idle.png", npcX, npcY);

	sf::Texture damage;
	damage.loadFromFile("otherData/ALL/images/dd.png");
	sf::Sprite damageWall(damage);
	damageWall.setPosition(0, 0);

	sf::Texture platformTexture;
	platformTexture.loadFromFile("otherData/ALL/images/Platforms.png");
	sf::Sprite platform(platformTexture);

	sf::RectangleShape gameoverBackground(sf::Vector2f(1920, 1080));
	gameoverBackground.setFillColor(sf::Color::Black);

	sf::Font font;
	font.loadFromFile("otherData/Fonts/mago2.ttf");

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::Red);

	sf::Text gameoverText, Best, exit;
	gameoverText.setFont(font);
	gameoverText.setString("Game Over!");
	gameoverText.setCharacterSize(80);
	gameoverText.setFillColor(sf::Color::Red);

	Best.setFont(font);
	Best.setString("New Record!");
	Best.setCharacterSize(80);
	Best.setFillColor(sf::Color::Red);

	exit.setFont(font);
	exit.setString("exiT");
	exit.setCharacterSize(50);
	exit.setFillColor(sf::Color::Red);

	sf::RectangleShape rect(sf::Vector2f(1920, 1080));
	rect.setFillColor(sf::Color::Black);
	rect.setPosition(0, 0);

	sf::Clock timer;

	sf::SoundBuffer buffer;
	buffer.loadFromFile("otherData//sound/jump.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);

	sf::SoundBuffer damag3;
	damag3.loadFromFile("otherData/music/damage.wav");
	sf::Sound sDamage;
	sDamage.setBuffer(damag3);

	sf::Music music;
	music.openFromFile("otherData/ALL/sound/Sound.wav");
	music.play();
	music.setLoop(true);

	sf::Vector2u platformPosition[10];
	std::uniform_int_distribution<unsigned> x(50, 1600);    
	std::uniform_int_distribution<unsigned> y(100, 900);
	std::default_random_engine e(time(0));
	for (size_t i = 0; i < 10; ++i)
	{
		platformPosition[i].x = x(e);
		platformPosition[i].y = y(e);
	}





	while (window.isOpen())
	{
		direction = rand() % 10000;


		float time = clock.restart().asMicroseconds();
		time = time / 800;
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			playerX -= 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerX += 10;
		}

		hero.colizion(playerX, playerY, health, npcY, npcX, damageTimer, maxDamageTimer, sDamage);
		if ((playerX > 1700 or ((abs(playerX - npcX) < 200 and abs(playerX - npcX) > 0) and (abs(playerY - npcY) < 70 and abs(playerY - npcY) > 0))) && damageTimer >= maxDamageTimer)
		{
			health -= 1;
			damageTimer = 0;
			sDamage.play();

		}
		if (playerX < 40 && damageTimer >= maxDamageTimer)
		{
			health -= 1;
			damageTimer = 0;
			sDamage.play();

		}
		damageTimer++;

		if (playerY == height && dy < (-1.62))
		{
			score += 1;
			scoreText.setString("Score: " + std::to_string(score));
			std::cout << score << std::endl;
		}

		dy += 1;
		playerY += dy;
		
		if (playerY < height)
			for (size_t i = 0; i < 10; ++i)
			{

				playerY = height;
				npcY -= dy/10;
				platformPosition[i].y -= dy; 
				if (platformPosition[i].y > 1080) 
				{
					platformPosition[i].y = 0;
					platformPosition[i].x = x(e);
				}

			}
			for (size_t i = 0; i < 10; ++i)
			{
				if ((playerX + playerRightPosition > platformPosition[i].x) && (playerX + playerLeftPositioin < platformPosition[i].x + platformTexture.getSize().x)        // player's horizontal range can touch the platform
					&& (playerY + playerBottomPosition > platformPosition[i].y) && (playerY + playerBottomPosition < platformPosition[i].y + platformTexture.getSize().y)  // player's vertical   range can touch the platform
					&& (dy > 0)) 
				{
					sound.play();
					dy = -35;
				}

			}

		hero.move(window, playerX, playerY, time, CurrentFrame, Idle);
		hero.healthIndicator(window, health);
		BG.anim(window, time, CurrentFrame);
		BG.draw(window);
		window.draw(damageWall);
		npc.animation(window, npcX, npcY, time, CurrentFrame, direction);
		hero.draw(window);

		int npcSpawn = rand() % 1000;

		if (npcSpawn == 1) {
			npcX = playerX + 10;
			npcY = playerY - 1000;
		}
		spawn += 1;
		if (spawn > 60) {
			npc.draw(window);
		}

		for (size_t i = 0; i < 10; ++i)
		{
			platform.setPosition(platformPosition[i].x, platformPosition[i].y);
			window.draw(platform);
		}

		hero.healthIndicator(window, health);
		window.draw(scoreText);
		float elapsedTime = timer.getElapsedTime().asSeconds();

		if (elapsedTime <= 30.0f)
		{
			int alpha = 0 + (elapsedTime / 30.0f) * 255;
			rect.setFillColor(sf::Color(0, 0, 0, alpha));
		}

		window.draw(rect);

		if (playerY > 1080 or health <= 0 or elapsedTime > 30.0f)
		{

			saveDataBase(score, save);
			if (save > score) {
				gameoverText.scale(sf::Vector2f(2, 2));
				gameoverText.setPosition(720, 300);
				scoreText.setPosition(720, 350);
				exit.setPosition(1120, 350);
				choice = 1;
			}
			else {
				Best.scale(sf::Vector2f(2, 2));
				Best.setPosition(720, 300);
				scoreText.setPosition(720, 350);
				exit.setPosition(1120, 350);
				choice = 0;
			} 
			goto gameover;

		}

		window.display();
	}
	
	bool menu1;

gameover:
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (choice == 0) {
			window.draw(gameoverBackground);
			window.draw(scoreText);
			window.draw(Best);
			exit.setPosition(1175, 350);
			window.draw(exit);
			if (IntRect(1175, 350, 50, 50).contains(Mouse::getPosition(window))) { 
				exit.setFillColor(sf::Color::White);  menu1 = 1;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menu1 == 1) {
					menu(window);
				}
			}
		}
		if (choice == 1) {
			window.draw(gameoverBackground);
			window.draw(gameoverText);
			window.draw(scoreText);
			window.draw(exit);
			if (IntRect(1120, 350, 50, 50).contains(Mouse::getPosition(window))) {
				exit.setFillColor(sf::Color::White);  menu1 = 1;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menu1 == 1) {
					menu(window);
				}
			}

		}
		window.display();
	}
	

}