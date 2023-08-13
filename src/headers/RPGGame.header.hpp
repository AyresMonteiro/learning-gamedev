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
            sf::Font mainFont;
            sf::Color mainColor;
            sf::Color secondaryColor;
            sf::Text getMainColorText(sf::String);
            sf::Text getSecondaryColorText(sf::String);
            void renderStart(sf::RenderWindow&);
            void renderGame(sf::RenderWindow&);
            void render(sf::RenderWindow&);
            GameScreen();
    };
}

#endif