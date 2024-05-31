

#include <SFML/Graphics.hpp>

class BackGround {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float x, y;

public:
    BackGround(std::string spritePath, float posX, float posY) {
        sprite.setTextureRect(sf::IntRect(0, 0, 480, 270));
        sprite.scale(sf::Vector2f(4, 4));
        if (!texture.loadFromFile(spritePath)) {
        }

        sprite.setTexture(texture);
        x = posX;
        y = posY;
        sprite.setPosition(x, y);
    }



    void anim(sf::RenderWindow& window, float, float);

    void draw(sf::RenderWindow& window);







};

