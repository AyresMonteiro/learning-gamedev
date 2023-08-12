#ifndef GAME_SCREEN
#define GAME_SCREEN

#include <SFML/Graphics.hpp>

namespace RPGGame {
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