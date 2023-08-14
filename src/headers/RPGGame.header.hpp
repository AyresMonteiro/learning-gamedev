#ifndef GAME_SCREEN
#define GAME_SCREEN

#include <vector>

#include <SFML/Graphics.hpp>

namespace RPGGame {
    struct DrawableUnion { sf::VertexArray vertex; sf::Text text; sf::Sprite sprite; };
    struct CommonShapeData { bool fade; bool isVertex; bool isSprite; RPGGame::DrawableUnion shape; int points; };
    class CommonDrawingFX {
        public:
            void fade(sf::RenderWindow&, std::vector<RPGGame::CommonShapeData>, int speed);
    };
    class GameScreen {
        public:
            bool started;
            bool finished;
            sf::Font mainFont;
            sf::Color mainColor;
            sf::Color secondaryColor;
            sf::Text getMainColorText(sf::String);
            sf::Text getSecondaryColorText(sf::String);
            void renderStart(sf::RenderWindow&);
            bool renderGame(sf::RenderWindow&);
            void render(sf::RenderWindow&);
            GameScreen();
    };
    class Character {
        public:
            enum Direction {
                down,
                right,
                left,
                up,
            };
            enum AnimationStage {
                first,
                second,
                third
            };
            sf::Texture texture;
            sf::Sprite sprite;
            sf::Vector2f position;
            Character::Direction direction;
            Character::AnimationStage stage;
            void draw(sf::RenderWindow&);
            void setDirection(Character::Direction);
            void setStage(Character::AnimationStage);
            void setPositionX(int, sf::RenderWindow&);
            void setPositionY(int, sf::RenderWindow&);
            Character(std::string);
    };
}

#endif