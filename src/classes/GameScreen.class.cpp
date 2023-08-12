#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/GameScreen.header.hpp"

using namespace RPGGame;

void GameScreen::renderStart(sf::RenderWindow& window) {
    sf::Text gameTitle, gameTitle2;
    sf::VertexArray initialFrame(sf::TriangleStrip, 4);

    float width = float(window.getSize().x);
    float height = float(window.getSize().y);

    initialFrame[0].position = sf::Vector2f(0.f, 0.f);
    initialFrame[1].position = sf::Vector2f(width - 1, 0.f);
    initialFrame[2].position = sf::Vector2f(0.f, height - 1);
    initialFrame[3].position = sf::Vector2f(width - 1, height - 1);

    initialFrame[0].color = sf::Color::Black;
    initialFrame[1].color = sf::Color::Black;
    initialFrame[2].color = sf::Color::Black;
    initialFrame[3].color = sf::Color::Black;

    gameTitle.setString(L"O Cupuaçu de Henri");
    gameTitle.setStyle(sf::Text::Bold); 
    gameTitle.setFont(this->mainFont);
    gameTitle.setCharacterSize(50);
    gameTitle.setFillColor(sf::Color::Black);
    gameTitle.setPosition(int(width) / 2 - 220, int(height) / 2 - 60);

    gameTitle2.setString(L"A Origem");
    gameTitle2.setStyle(sf::Text::Bold); 
    gameTitle2.setFont(this->mainFont);
    gameTitle2.setCharacterSize(40);
    gameTitle2.setFillColor(sf::Color::White);
    gameTitle2.setPosition(int(width) / 2 - 100, int(height) / 2 + 20);

    for (int i = 0; i < 256; i++) {
        sf::Uint8 param = sf::Uint8(i % 256);
        sf::Uint8 opposite = sf::Uint8((255 - param) % 256);
        initialFrame[0].color.r = param;
        initialFrame[0].color.g = param;
        initialFrame[0].color.b = param;

        initialFrame[1].color = initialFrame[0].color;
        initialFrame[2].color = initialFrame[0].color;
        initialFrame[3].color = initialFrame[0].color;

        gameTitle.setFillColor(sf::Color(opposite, opposite, opposite));

        window.clear();
        window.draw(initialFrame);
        window.draw(gameTitle);
        window.display();

        sf::sleep(sf::milliseconds(15));
    }

    for (int i = 0; i < 256; i++) {
        sf::Uint8 param = sf::Uint8(i % 256);
        sf::Uint8 opposite = sf::Uint8((255 - param) % 256);

        gameTitle2.setFillColor(sf::Color(opposite, opposite, opposite));

        window.clear();
        window.draw(initialFrame);
        window.draw(gameTitle);
        window.draw(gameTitle2);
        window.display();

        sf::sleep(sf::milliseconds(10));
    }

    float gameTitleWidth = int(width) / 2 - 220;
    float gameTitle2Width = int(width) / 2 - 100;

    for (int i = 0; i < 220; i++) {
        sf::Uint8 param = sf::Uint8(i % 256);

        gameTitle.setPosition(gameTitleWidth, int(height) / 2 - 60 - param);
        gameTitle2.setPosition(gameTitle2Width, int(height) / 2 + 20 - param);

        window.clear();
        window.draw(initialFrame);
        window.draw(gameTitle);
        window.draw(gameTitle2);
        window.display();

        sf::sleep(sf::milliseconds(8));
    }
}

void GameScreen::render(sf::RenderWindow& baseWindow) {
    if (this->started == false) {
        this->started = true;

        this->renderStart(baseWindow);
    }

    baseWindow.clear();
}

GameScreen::GameScreen() {
    if(!this->mainFont.loadFromFile("./src/resources/fonts/Future n0t Found Regular.ttf")) {
        std::cout << "Main Font not loaded" << std::endl;
    }

    std::cout << "Main Font loaded" << std::endl;
    std::cout << "GameScreen constructed" << std::endl;
    this->started = false;
}
