#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../headers/RPGGame.header.hpp"

#define STEP_SIZE 16

using namespace RPGGame;

sf::Text GameScreen::getMainColorText(sf::String text) {
    sf::Text newText;
    newText.setString(text);
    newText.setFillColor(this->mainColor);
    newText.setFont(this->mainFont);
    newText.setStyle(sf::Text::Regular);
    newText.setCharacterSize(16);
    return newText;
}

sf::Text GameScreen::getSecondaryColorText(sf::String text) {
    sf::Text newText = this->getMainColorText(text);
    newText.setFillColor(this->secondaryColor);
    return newText;
}

void GameScreen::renderStart(sf::RenderWindow& window) {
    sf::Music entranceSound;

    if(!entranceSound.openFromFile("./src/resources/mp3/musical-march-4312.wav")) {
        std::cout << "Entrance music not loaded" << std::endl;
    }

    std::cout << "Entrance music loaded" << std::endl;

    entranceSound.setVolume(20.f);

    entranceSound.setLoop(true);

    std::cout << "Playing..." << std::endl;

    entranceSound.play();

    RPGGame::CommonDrawingFX drawingFx;

    sf::Text gameTitle, gameTitle2;
    sf::VertexArray initialFrame(sf::TriangleStrip, 4);

    float width = float(window.getSize().x);
    float height = float(window.getSize().y);

    initialFrame[0].position = sf::Vector2f(0.f, 0.f);
    initialFrame[1].position = sf::Vector2f(width, 0.f);
    initialFrame[2].position = sf::Vector2f(0.f, height);
    initialFrame[3].position = sf::Vector2f(width, height);

    initialFrame[0].color = sf::Color(sf::Color::White);
    initialFrame[1].color = initialFrame[0].color;
    initialFrame[2].color = initialFrame[0].color;
    initialFrame[3].color = initialFrame[0].color;

    gameTitle = this->getSecondaryColorText(L"O Cupuaçu de Henri");
    gameTitle.setStyle(sf::Text::Bold);
    gameTitle.setCharacterSize(50);
    gameTitle.setPosition(int(width) / 2 - 214, int(height) / 2 - 60);

    gameTitle2 = this->getSecondaryColorText(L"A Origem");
    gameTitle2.setCharacterSize(40);
    gameTitle2.setStyle(sf::Text::Bold);
    gameTitle2.setPosition(int(width) / 2 - 86, int(height) / 2 + 20);

    for (int i = 0; i < 256; i++) {
        sf::Uint8 param = sf::Uint8(i % 256);
        sf::Uint8 opposite = sf::Uint8((255 - param) % 256);

        initialFrame[0].color.r = param;
        initialFrame[0].color.g = param;
        initialFrame[0].color.b = param;

        for(int j = 0; j < 4;j++) initialFrame[j].color = initialFrame[0].color;

        sf::Color faded = sf::Color(this->mainColor);

        faded.a = param;

        gameTitle.setFillColor(faded);

        window.clear();
        window.draw(initialFrame);
        window.draw(gameTitle);
        window.display();

        sf::sleep(sf::milliseconds(10));
    }

    for (int i = 0; i < 256; i++) {
        sf::Uint8 param = sf::Uint8(i % 256);
        sf::Uint8 opposite = sf::Uint8((255 - param) % 256);

        sf::Color faded = sf::Color(this->mainColor);

        faded.a = param;

        gameTitle2.setFillColor(faded);

        window.clear();
        window.draw(initialFrame);
        window.draw(gameTitle);
        window.draw(gameTitle2);
        window.display();

        sf::sleep(sf::milliseconds(10));
    }

    float gameTitleWidth = int(width) / 2 - 214;
    float gameTitle2Width = int(width) / 2 - 86;

    for (int i = 0; i < 190; i++) {
        sf::Uint8 param = sf::Uint8(i % 256);

        gameTitle.setPosition(gameTitleWidth, int(height) / 2 - 60 - param);
        gameTitle2.setPosition(gameTitle2Width, int(height) / 2 + 20 - param);

        window.clear();
        window.draw(initialFrame);
        window.draw(gameTitle);
        window.draw(gameTitle2);
        window.display();

        sf::sleep(sf::milliseconds(3));
    }

    sf::Texture menuBoxAsset;

    if(!menuBoxAsset.loadFromFile("./src/resources/png/menuBox.png")) {
        std::cout << "Menu box asset not loaded" << std::endl;
    }

    std::cout << "Menu box asset loaded" << std::endl;

    sf::Sprite menuBox;

    menuBox.setTexture(menuBoxAsset);
    menuBox.setPosition(sf::Vector2f(200.f, 260.f));

    std::vector<RPGGame::CommonShapeData> screenItems = std::vector<RPGGame::CommonShapeData>();

    screenItems.push_back({ .fade = false, .isVertex = true, .isSprite = false, {.vertex = initialFrame}, .points = 4});
    screenItems.push_back({ .fade = false, .isVertex = false, .isSprite = false, {.text = gameTitle}, .points = 0});
    screenItems.push_back({ .fade = false, .isVertex = false, .isSprite = false, {.text = gameTitle2}, .points = 0});
    screenItems.push_back({ .fade = true, .isVertex = false, .isSprite = true, {.sprite = menuBox}, .points = 0});

    drawingFx.fade(window, screenItems, 2);
    
    screenItems.pop_back();
    screenItems.push_back({ .fade = false, .isVertex = false, .isSprite = true, {.sprite = menuBox}, .points = 0});

    sf::Text instructionsText0, instructionsText1;

    int option = 0;

    instructionsText0 = this->getSecondaryColorText(L"Iniciar");
    instructionsText0.setCharacterSize(30);
    instructionsText0.setOutlineColor(this->mainColor);
    instructionsText0.setPosition(295, 360);
    
    instructionsText1 = this->getSecondaryColorText(L"Sair");
    instructionsText1.setCharacterSize(30);
    instructionsText1.setOutlineColor(this->mainColor);
    instructionsText1.setPosition(295, 400);

    screenItems.push_back({ .fade = true, .isVertex = false, .isSprite = false, {.text = instructionsText0}, .points = 0});
    screenItems.push_back({ .fade = false, .isVertex = false, .isSprite = false, {.text = instructionsText1}, .points = 0});

    bool canExit = false;

    while(!canExit) {
        bool pressed = false;
        sf::Event event;

        while (window.pollEvent(event)) {
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Key::Enter) {
                    canExit = true;

                    if(option == 1) break;
                }
            }
            
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Key::Up || event.key.code == sf::Keyboard::Key::Down) {
                    option = int(!option);
                    pressed = true;
                }
            }
        }

        if(canExit && option == 1) break;

        screenItems.pop_back();
        screenItems.pop_back();

        screenItems.push_back({ .fade = option == 0, .isVertex = false, .isSprite = false, {.text = instructionsText0}, .points = 0});
        screenItems.push_back({ .fade = option == 1, .isVertex = false, .isSprite = false, {.text = instructionsText1}, .points = 0});

        if(!pressed) drawingFx.fade(window, screenItems, 1);
    }

    window.clear();
    entranceSound.stop();

    if (option == 1) {
        window.close();
        this->finished = true;
    }
}

bool GameScreen::renderGame(sf::RenderWindow& window) {
    if(this->finished) return false;

    sf::VertexArray initialFrame(sf::TriangleStrip, 4);

    float width = float(window.getSize().x);
    float height = float(window.getSize().y);

    RPGGame::Map baseMap("./src/resources/maps/first_map.gamemap");

    initialFrame[0].position = sf::Vector2f(0.f, 0.f);
    initialFrame[1].position = sf::Vector2f(width, 0.f);
    initialFrame[2].position = sf::Vector2f(0.f, height);
    initialFrame[3].position = sf::Vector2f(width, height);

    initialFrame[0].color = sf::Color(sf::Color::White);
    initialFrame[1].color = initialFrame[0].color;
    initialFrame[2].color = initialFrame[0].color;
    initialFrame[3].color = initialFrame[0].color;

    Character henri("./src/resources/png/henri.png");

    bool canExit = false;
    bool canWalk = false;

    window.setKeyRepeatEnabled(false);

    while(!canExit) {
        sf::Event event;

        if (window.pollEvent(event)) {
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Key::Escape) {
                    canExit = true;
                    break;
                }
                
                bool upPressed = event.key.code == sf::Keyboard::Key::Up;
                bool downPressed = event.key.code == sf::Keyboard::Key::Down;
                bool rightPressed = event.key.code == sf::Keyboard::Key::Right;
                bool leftPressed = event.key.code == sf::Keyboard::Key::Left;

                canWalk = upPressed || downPressed || rightPressed || leftPressed;

                if (upPressed) {
                    henri.setDirection(Character::Direction::up);
                } else if (downPressed) {
                    henri.setDirection(Character::Direction::down);
                } else if (rightPressed) {
                    henri.setDirection(Character::Direction::right);
                } else if (leftPressed) {
                    henri.setDirection(Character::Direction::left);
                }
            }
            
            if(event.type == sf::Event::KeyReleased) {    
                bool upReleased = event.key.code == sf::Keyboard::Key::Up;
                bool downReleased = event.key.code == sf::Keyboard::Key::Down;
                bool rightReleased = event.key.code == sf::Keyboard::Key::Right;
                bool leftReleased = event.key.code == sf::Keyboard::Key::Left;

                canWalk = canWalk && !(
                    (upReleased && henri.direction == Character::Direction::up) ||
                    (downReleased && henri.direction == Character::Direction::down) ||
                    (rightReleased && henri.direction == Character::Direction::right) ||
                    (leftReleased && henri.direction == Character::Direction::left)
                );
            }
        }

        if(!canWalk) {
            window.clear();
            window.draw(initialFrame);
            baseMap.draw(window);
            henri.draw(window);
            window.display();
        } else {
            for(int j = 0; j < 4; j++) {
                window.clear();
                window.draw(initialFrame);
                baseMap.draw(window);
                henri.setStage(Character::AnimationStage(j % 3));
                henri.draw(window);
                window.display();

                sf::sleep(sf::milliseconds(50));

                if (henri.direction == Character::Direction::up) {
                    henri.setPositionY(int(henri.position.y) - STEP_SIZE, window);
                } else if (henri.direction == Character::Direction::down) {
                    henri.setPositionY(int(henri.position.y) + STEP_SIZE, window);
                } else if (henri.direction == Character::Direction::right) {
                    henri.setPositionX(int(henri.position.x) + STEP_SIZE, window);
                } else if (henri.direction == Character::Direction::left) {
                    henri.setPositionX(int(henri.position.x) - STEP_SIZE, window);
                }
            }
        }
    }

    this->finished = true;

    return false;
}

void GameScreen::render(sf::RenderWindow& baseWindow) {
    if(this->finished) {
        baseWindow.close();
        return;
    }
    
    sf::Event event;

    while (baseWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            baseWindow.close();
            return;
        }
    }

    if (this->started == false) {
        this->started = true;

        this->renderStart(baseWindow);
    }

    if(this->finished) {
        if (baseWindow.isOpen()) baseWindow.close();
        return;
    }

    while(this->renderGame(baseWindow));
}

GameScreen::GameScreen() {
    if(!this->mainFont.loadFromFile("./src/resources/fonts/Future n0t Found Regular.ttf")) {
        std::cout << "Main Font not loaded" << std::endl;
    }

    std::cout << "Main Font loaded" << std::endl;
    std::cout << "GameScreen constructed" << std::endl;
    this->started = false;
    this->finished = false;
    this->mainColor = sf::Color(39, 27, 0, 255);
    this->secondaryColor = sf::Color(255, 223, 120, 255);
}
