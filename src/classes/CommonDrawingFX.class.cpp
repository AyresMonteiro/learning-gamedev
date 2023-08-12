#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/RPGGame.header.hpp"

using namespace RPGGame;

void CommonDrawingFX::fade(sf::RenderWindow& window, std::vector<RPGGame::CommonShapeData> shapes) {
    for (int i = 0; i < 256; i++) {
        sf::Uint8 param = sf::Uint8(i % 256);

        for (RPGGame::CommonShapeData & data : shapes) {
            if(!data.fade) continue;

            if(data.isVertex) for (int i = 0; i < data.points; i++) data.shape.vertex[i].color.a = param;
            else {
                sf::Color c = data.shape.text.getFillColor();
                c.a = param;
                data.shape.text.setFillColor(c);
            }
        }
        
        window.clear();

        for (RPGGame::CommonShapeData data : shapes) {
            if(data.isVertex) window.draw(data.shape.vertex);
            else window.draw(data.shape.text);
        }

        window.display();

        sf::sleep(sf::milliseconds(15));
    }
}
