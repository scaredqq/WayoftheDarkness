#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>


class Hero {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float x, y;

public:
    int dir = 0;

    Hero(std::string spritePath, float posX, float posY) {
        sprite.scale(sf::Vector2f(0.15, 0.15));
        if (!texture.loadFromFile(spritePath)) {
        }

        sprite.setTexture(texture);
        x = posX;
        y = posY;
        sprite.setPosition(x, y);
    }


    void draw(sf::RenderWindow& window);

    void colizion(float&, float&, int&, float, float, int&, int&, sf::Sound);


    void move(sf::RenderWindow& window, float&, float&, float, float&, bool&);

    void healthIndicator(sf::RenderWindow& window, int& health);

    void update(float& playerX, float& playerY, float time);
    




};

#endif HERO_H
