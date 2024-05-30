#include <SFML/Graphics.hpp>
#include "hero.h"
#include "game.h"
#include "mainMenu.h"
#include "snowFlake.h"
#include <iostream>



int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "WayofDarkness");


    menu(window);
    game(window);

   

    return 0;
}