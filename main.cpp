#include <iostream>

#include <SFML/Graphics.hpp>

#include "./src/headers/GameScreen.header.hpp"

int main () {
    int width = 800;
    int height = 600;
    float triangleSize = 200.f;

    sf::RenderWindow window(sf::VideoMode(width, height), "Hello World, SFML!");

    RPGGame::GameScreen screen = RPGGame::GameScreen();

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        screen.render(window);
    }

    return 0;
}