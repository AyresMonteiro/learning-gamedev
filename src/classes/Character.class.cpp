#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/RPGGame.header.hpp"

using namespace RPGGame;

void Character::draw(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

Character::Character(std::string texturePath) {
    this->texture = sf::Texture();
    this->position = sf::Vector2f(0, 0);
    this->direction = Character::Direction::down;
    this->stage = Character::AnimationStage::first;

    if(!this->texture.loadFromFile(texturePath)) {
        std::cout << "Texture not loaded" << std::endl;
    }
    
    std::cout << "Texture loaded" << std::endl;

    this->sprite = sf::Sprite();
    this->sprite.scale(2.f, 2.f);
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(
        0 + (64 * int(this->direction)),
        0 + (64 * int(this->stage)),
        64,
        64
    ));
}

void Character::setDirection(Character::Direction direction) {
    this->direction = direction;
    this->sprite.setTextureRect(sf::IntRect(
        0 + (64 * int(this->direction)),
        0 + (64 * int(this->stage)),
        64,
        64
    ));
}

void Character::setStage(Character::AnimationStage stage) {
    this->stage = stage;
    this->sprite.setTextureRect(sf::IntRect(
        0 + (64 * int(this->direction)),
        0 + (64 * int(this->stage)),
        64,
        64
    ));
}

void Character::setPositionX(int x, sf::RenderWindow& window) {
    int width = window.getSize().x;

    this->position = sf::Vector2f(
        float((x < 0 ? width + x : x) % width),
        this->position.y
    );

    this->sprite.setPosition(this->position);
}

void Character::setPositionY(int y, sf::RenderWindow& window) {
    int height = window.getSize().y;

    this->position = sf::Vector2f(
        this->position.x,
        float((y < 0 ? height + y : y) % height)
    );

    this->sprite.setPosition(this->position);
}

int Character::getPositionX() {
    return (int) this->position.x;
}

int Character::getPositionY() {
    return (int) this->position.y;
}
