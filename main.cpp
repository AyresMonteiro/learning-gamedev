#include <iostream>

#include <SFML/Graphics.hpp>

#include "./src/headers/RPGGame.header.hpp"

int main () {
    // int width = 800;
    // int height = 600;
    // float triangleSize = 200.f;

    // sf::RenderWindow window(sf::VideoMode(width, height), "Hello World, SFML!");

    // RPGGame::GameScreen screen = RPGGame::GameScreen();

    // while (window.isOpen()) {
    //     sf::Event event;

    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) window.close();
    //     }

    //     screen.render(window);
    // }

    RPGGame::Map map;

    RPGGame::MapData base(
        (uint8_t) 16,
        (uint8_t) 16,
        (uint8_t) 64,
        (uint8_t) 64,
        std::string("./src/resources/textures/wooden_house.png"),
        std::vector<std::vector<uint8_t>>(16, std::vector<uint8_t>(16, 0)),
        std::vector<std::vector<uint16_t>>(16, std::vector<uint16_t>(16, 0))
    );

    base.permeabilityMap[0][0] = 1;
    base.permeabilityMap[base.mapWidth - 1][base.mapHeight - 1] = 1;

    base.graphicalMap[0][0] = 1;
    base.graphicalMap[base.mapWidth - 1][base.mapHeight - 1] = 1;
    base.debug();

    map.writeMap("./src/resources/maps/first_map.gamemap", base);
    map.readFromFile("./src/resources/maps/first_map.gamemap").debug();

    return 0;
}