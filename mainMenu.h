#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "snowFlake.h"
#include "game.h"
#include "hero.h"
#include <ctime>
#include "scenceUpdete.h"
#include "npc.h"




using namespace sf;




void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground, menu;
	menu.loadFromFile("textures/mainMenuText/animationBG.jpg");
	menuTexture1.loadFromFile("textures/mainMenuText/START.png");
	menuTexture2.loadFromFile("textures/mainMenuText/EXIT.png");
	menuTexture3.loadFromFile("textures/mainMenuText/credits.png");
	menuBackground.loadFromFile("textures/mainMenuText/BG");
	aboutTexture.loadFromFile("textures/mainMenuText/about.png");
	Sprite start(menuTexture1), exit(menuTexture2), credits(menuTexture3), menuBg(menuBackground), about(aboutTexture), menuBack(menu);
	menuBack.setPosition(0, 0);
	menuBg.setScale(1.5f, 1.2f);
	menuBack.setScale(1.5f, 1.2f);

	const int numFrames = 3;


	// Set the current frame
	int currentFrame = 0;

	float cd;

	const float timePerFrame = 0.1f;

	sf::Clock clock;
	sf::RectangleShape gameoverBackground(sf::Vector2f(1920, 1080));
	gameoverBackground.setFillColor(sf::Color::Black);

	SoundBuffer targetBuffer, pressBuffer;
	targetBuffer.loadFromFile("music/gameMenu/target.wav");
	Sound target(targetBuffer);

	pressBuffer.loadFromFile("music/gameMenu/press.wav");
	Sound press(pressBuffer);

	Music music;
	music.openFromFile("music/gameMenu/hiddenScroll.wav");
	music.play();
	music.setLoop(true);

	sf::Font font;
	font.loadFromFile("Fonts/mago2.ttf");
	sf::Text credit;
	credit.setFont(font);
	credit.setCharacterSize(50);
	credit.setString("Thank you!");
	credit.setFillColor(sf::Color::White);
	credit.setPosition(850, 450);

	bool isMenu = 1;
	int menuNum = 0;



	start.setPosition(680, 300);
	credits.setPosition(680, 400);
	exit.setPosition(680, 500);
	menuBg.setPosition(0, 0);
	about.setPosition(0, 0);
	sf::IntRect hoverArea(780, 370, 300, 60);
	sf::IntRect hoverArea2(780, 470, 300, 60);
	sf::IntRect hoverArea3(780, 570, 300, 60);
	bool isHovering = false;

	std::vector<Snowflake> snowflakes;
	snowflakes.reserve(number_of_snowflakes);
	for (int i = 0; i < number_of_snowflakes; ++i)
	{
		float x = generate_random(0, window.getSize().x);
		float y = generate_random(0, window.getSize().y) - 20.F;
		sf::Vector2f start_position(x, y);
		snowflakes.emplace_back(Snowflake(start_position));
	}

	while (isMenu)
	{
		start.setColor(Color::White);
		credits.setColor(Color::White);
		exit.setColor(Color::White);

		start.setScale(1.f, 1.f);


		menuNum = 0;

		for (auto&& snow : snowflakes)
		{
			snow.fall(window.getSize());
		}
		window.clear(Color(100, 181, 221));

		if (IntRect(780, 370, 300, 60).contains(Mouse::getPosition(window))) { start.setColor(Color::Color(128, 128, 128));  menuNum = 1; }
		if (IntRect(780, 470, 300, 60).contains(Mouse::getPosition(window))) { credits.setColor(Color::Color(128, 128, 128)); menuNum = 2; }
		if (IntRect(780, 570, 300, 60).contains(Mouse::getPosition(window))) { exit.setColor(Color::Color(128, 128, 128)); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				press.play();
				isMenu = false;
			}
			if (menuNum == 2) { press.play();  window.draw(gameoverBackground);  window.draw(credit); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { press.play();   window.close(); isMenu = false; }

		}


		float time = clock.getElapsedTime().asSeconds();
		if (time >= timePerFrame)
		{
			currentFrame = (currentFrame + 1) % numFrames;

			menuBack.setTextureRect(sf::IntRect(currentFrame * 4050 / numFrames, 0, 4050 / numFrames, 900));

			clock.restart();
		}

	





		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (hoverArea.contains(mousePosition) or hoverArea2.contains(mousePosition) or hoverArea3.contains(mousePosition))
		{
			if (!isHovering)
			{
				isHovering = true;
				target.play();
			}
		}
		else
		{
			isHovering = false;
			target.stop();
		}

		window.draw(menuBack);
		for (auto&& snow : snowflakes)
		{
			snow.draw(window);
		}


		window.draw(start);
		window.draw(credits);
		window.draw(exit);
		window.display();
	}
}