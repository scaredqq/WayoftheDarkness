#include <iostream>
#include "npc.h"




void Npc::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}




void Npc::animation(sf::RenderWindow& window, float& playerX, float& playerY, float time, float& CurrentFrame, int& direction)
{
	if (direction < 5000) {
		playerX -= 0.2 * time;
	}
	else {
		playerX += 0.2 * time;
	}
	if (CurrentFrame > 4) CurrentFrame -= 4; //если пришли к третьему кадру - откидываемся назад.
	sprite.setTextureRect(sf::IntRect(100 * int(CurrentFrame), 0, 100, 100));
	sprite.setPosition(playerX, playerY);

}






