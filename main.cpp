#include <SFML/Graphics.hpp>
#include "hero/hero.h"
#include "game/game.h"
#include "menu/mainMenu.h"
#include "snowFlake/snowFlake.h"
#include <iostream>



int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "WayofDarkness");


    menu(window);
    game(window);

   

    return 0;
}