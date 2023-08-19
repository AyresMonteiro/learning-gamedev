#include <iostream>

#include <SFML/Graphics.hpp>

#include "./src/headers/RPGGame.header.hpp"

void handleMap() {
    RPGGame::Map map;

    uint8_t mapWidth = 12;
    uint8_t mapHeight = 9;

    RPGGame::MapData base(
        (uint8_t) mapWidth,
        (uint8_t) mapHeight,
        (uint8_t) 12,
        (uint8_t) 12,
        (uint8_t) 32,
        (uint8_t) 32,
        std::string("./src/resources/textures/cupuacu_plains.png"),
        std::vector<std::vector<uint8_t>>(mapHeight, std::vector<uint8_t>(mapWidth, 1)),
        std::vector<std::vector<uint16_t>>(mapHeight, std::vector<uint16_t>(mapWidth, 13))
    );

    base.graphicalMap[0][0] = 0;
    base.graphicalMap[0][base.mapWidth - 1] = 2;
    base.graphicalMap[base.mapHeight - 1][0] = 24;
    base.graphicalMap[base.mapHeight - 1][base.mapWidth - 1] = 26;
    
    base.permeabilityMap[0][0] = 0;
    base.permeabilityMap[0][base.mapWidth - 1] = 0;
    base.permeabilityMap[base.mapHeight - 1][0] = 0;
    base.permeabilityMap[base.mapHeight - 1][base.mapWidth - 1] = 0;

    for (int i = 1; i < base.mapWidth - 1; i++) {
        base.graphicalMap[0][i] = 1;
        base.graphicalMap[base.mapHeight - 1][i] = 25;
        base.permeabilityMap[0][i] = 0;
        base.permeabilityMap[base.mapHeight - 1][i] = 0;
    }

    for (int i = 1; i < base.mapHeight - 1; i++) {
        base.graphicalMap[i][0] = 12;
        base.graphicalMap[i][base.mapWidth - 1] = 14;
        base.permeabilityMap[i][0] = 0;
        base.permeabilityMap[i][base.mapWidth - 1] = 0;
    }

    base.debug();

    map.writeMap("./src/resources/maps/first_map.gamemap", base);
    map.readFromFile("./src/resources/maps/first_map.gamemap").debug();
}

void handleGame() {
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
}

int main () {
    handleGame();

    return 0;
}
