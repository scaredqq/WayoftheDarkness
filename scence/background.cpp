#include "background.h"

void BackGround::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void BackGround::anim(sf::RenderWindow& window, float time, float CurrentFrame)
{
	CurrentFrame += 0.005 * time; 
	if (CurrentFrame > 6) CurrentFrame -= 6;
	sprite.setTextureRect(sf::IntRect(480 * int(CurrentFrame), 0, 482, 271));

}
