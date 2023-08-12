#ifndef GAME_SCREEN
#define GAME_SCREEN

#include <vector>

#include <SFML/Graphics.hpp>

namespace RPGGame {
    struct DrawableUnion { sf::VertexArray vertex; sf::Text text; };
    struct CommonShapeData { bool fade; bool isVertex; RPGGame::DrawableUnion shape; int points; };
    class CommonDrawingFX {
        public:
            void fade(sf::RenderWindow&, std::vector<RPGGame::CommonShapeData>);
    };
    class GameScreen {
        public:
            bool started;
            sf::Font mainFont;
            void renderStart(sf::RenderWindow&);
            void render(sf::RenderWindow&);
            GameScreen();
    };
}

#endif