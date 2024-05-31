#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

class Npc {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float x, y;

public:
    Npc(std::string spritePath, float posX, float posY) {
        sprite.setTextureRect(sf::IntRect(0, 2048, 1024, 1024));
        sprite.scale(sf::Vector2f(4, 4));
        if (!texture.loadFromFile(spritePath)) {
        }

        sprite.setTexture(texture);
        x = posX;
        y = posY;
        sprite.setPosition(x, y);
    }


    void draw(sf::RenderWindow& window);

    void animation(sf::RenderWindow& window, float&, float&, float, float&, int&);



    








};

#endif NPC_H