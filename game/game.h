#pragma once

#include <SFML/Graphics.hpp>
#include "hero/hero.h"
#include "scence/scence.h"
#include <iostream>


float playerX = 250;
float playerY = 151;



void game(sf::RenderWindow& window) {

    window.setFramerateLimit(60);


    sf::Clock clock;

    while (window.isOpen()) {


        std::cout << time<< std::endl;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }




        window.clear();
        scence(window, playerX, playerY);
        window.display();
    }
}
