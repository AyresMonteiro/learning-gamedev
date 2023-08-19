#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../headers/RPGGame.header.hpp"

using namespace RPGGame;

typedef struct SplittedUInt16 {
    unsigned int second: 8;
    unsigned int first: 8;
} SplittedUInt16;

typedef union {
    SplittedUInt16 splitted;
    uint16_t whole;
} FlexibleUInt16;

uint8_t extractY(uint16_t index, int mapHeight) {
    if (index == 0) return 0;

    return (int) index / (int) mapHeight;
}

uint8_t extractX(uint16_t index, int mapWidth) {
    if (index == 0) return 0;

    return (int) index % (int) mapWidth;
}

void MapData::debug() {
    std::cout << "Width: " << (int) this->mapWidth << std::endl;
    std::cout << "Height: " << (int) this->mapHeight << std::endl;
    std::cout << "TextureWidth: " << (int) this->mapTextureWidth << std::endl;
    std::cout << "TextureHeight: " << (int) this->mapTextureHeight << std::endl;
    std::cout << "TextureBlockWidth: " << (int) this->mapTextureBlockWidth << std::endl;
    std::cout << "TextureBlockHeight: " << (int) this->mapTextureBlockHeight << std::endl;
    std::cout << "TexturePath: " << this->texturePath << std::endl;

    std::cout << "Permeability Map:" << std::endl;
    for(int i = 0; i < this->mapHeight; i++) {
        for(int j = 0; j < this->mapWidth; j++) {
            std::cout << (int) this->permeabilityMap[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << "Graphical Map:" << std::endl;
    for(int i = 0; i < this->mapHeight; i++) {
        for(int j = 0; j < this->mapWidth; j++) {
            std::cout << this->graphicalMap[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

MapData::MapData() {
};

MapData::MapData(
    uint8_t mapWidth,
    uint8_t mapHeight,
    uint8_t mapTextureWidth,
    uint8_t mapTextureHeight,
    uint8_t mapTextureBlockWidth,
    uint8_t mapTextureBlockHeight,
    std::string texturePath,
    std::vector<std::vector<uint8_t>> permeabilityMap,
    std::vector<std::vector<uint16_t>> graphicalMap
) {
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    this->mapTextureWidth = mapTextureWidth;
    this->mapTextureHeight = mapTextureHeight;
    this->mapTextureBlockWidth = mapTextureBlockWidth;
    this->mapTextureBlockHeight = mapTextureBlockHeight;
    this->texturePath = texturePath;
    this->permeabilityMap = permeabilityMap;
    this->graphicalMap = graphicalMap;
};

void Map::writeMap(std::string mapPath, RPGGame::MapData data) {
    std::ofstream mapFile(mapPath, std::ios::out | std::ios::binary);

    if(!mapFile.is_open()) {
        std::cout << "Map file was not opened" << std::endl;
        return;
    }

    std::cout << data.texturePath << std::endl;
    std::cout << "Map file was opened" << std::endl;

    std::vector<uint8_t> buffer;

    buffer.push_back(data.mapWidth);
    buffer.push_back(data.mapHeight);

    buffer.push_back(data.mapTextureWidth);
    buffer.push_back(data.mapTextureHeight);

    buffer.push_back(data.mapTextureBlockWidth);
    buffer.push_back(data.mapTextureBlockHeight);

    for(int i = 0; i < data.texturePath.size(); i++) buffer.push_back((uint8_t) data.texturePath[i]);

    buffer.push_back((uint8_t) '\0');

    for(uint8_t i = 0; i < data.mapHeight; i++) {
        for(uint8_t j = 0; j < data.mapWidth; j++) {
            buffer.push_back(data.permeabilityMap[i][j]);
        }
    }

    for(uint8_t i = 0; i < data.mapHeight; i++) {
        for(uint8_t j = 0; j < data.mapWidth; j++) {
            FlexibleUInt16 graphicalMapBlock =  { .whole = data.graphicalMap[i][j] };

            buffer.push_back(graphicalMapBlock.splitted.first);
            buffer.push_back(graphicalMapBlock.splitted.second);
        }
    }

    mapFile.write((char *) buffer.data(), buffer.size());

    std::cout << "Map file was writed" << std::endl;

    mapFile.close();
}

MapData Map::readFromFile(std::string path) {
    MapData data;

    std::ifstream mapFile(path, std::ios::in | std::ios::binary);

    if (!mapFile.is_open()) {
        std::cout << "Map file was not opened" << std::endl;
        return data;
    }

    std::cout << "Map file was opened" << std::endl;


    uint8_t buf;
    char * bufChar = (char *) &buf;

    mapFile.read(bufChar, 1);
    data.mapWidth = buf;

    mapFile.read(bufChar, 1);
    data.mapHeight = buf;

    mapFile.read(bufChar, 1);
    data.mapTextureWidth = buf;
    
    mapFile.read(bufChar, 1);
    data.mapTextureHeight = buf;

    mapFile.read(bufChar, 1);
    data.mapTextureBlockWidth = buf;
    
    mapFile.read(bufChar, 1);
    data.mapTextureBlockHeight = buf;

    std::vector<char> texturePath;

    while (buf != '\0') {
        mapFile.read(bufChar, 1);
        texturePath.push_back(buf);
    }

    texturePath.push_back('\0');

    data.texturePath = std::string(texturePath.begin(), texturePath.end()); 

    data.permeabilityMap = std::vector<std::vector<uint8_t>>(data.mapHeight, std::vector<uint8_t>(data.mapWidth, 1));

    for(uint8_t i = 0; i < data.mapHeight; i++) {
        for(uint8_t j = 0; j < data.mapWidth; j++) {
            mapFile.read(bufChar, 1);
            data.permeabilityMap[i][j] = buf;
        }
    }

    data.graphicalMap = std::vector<std::vector<uint16_t>>(data.mapHeight, std::vector<uint16_t>(data.mapWidth, 1));

    for(uint8_t i = 0; i < data.mapHeight; i++) {
        for(uint8_t j = 0; j < data.mapWidth; j++) {
            FlexibleUInt16 graphicalMapBlock;

            mapFile.read(bufChar, 1);
            graphicalMapBlock.splitted.first = buf;
            mapFile.read(bufChar, 1);
            graphicalMapBlock.splitted.second = buf;

            data.graphicalMap[i][j] = graphicalMapBlock.whole;
        }
    }

    std::cout << "Map file was read" << std::endl;

    mapFile.close();

    return data;
}

Map::Map() {

}

Map::Map(std::string mapPath) {
    this->mapData = this->readFromFile(mapPath);
    this->mapTexture = sf::Texture();

    if(!this->mapTexture.loadFromFile(this->mapData.texturePath)) {
        std::cout << "Texture not loaded" << std::endl;
    }
    
    std::cout << "Texture loaded" << std::endl;

    this->tiles = std::vector<std::vector<sf::Sprite>>(
        this->mapData.mapHeight,
        std::vector<sf::Sprite>(
            this->mapData.mapWidth,
            sf::Sprite()
        )
    );

    this->mapData.debug();

    for(int i = 0; i < this->mapData.mapHeight; i++) {
        // this->tiles.push_back(std::vector<sf::Sprite>());
        for(int j = 0; j < this->mapData.mapWidth; j++) {
            // this->tiles[i].push_back(sf::Sprite());
            uint16_t index = this->mapData.graphicalMap[i][j];

            std::cout << "index: " << index << std::endl;

            int x = extractX(index, this->mapData.mapTextureWidth);
            int y = extractY(index, this->mapData.mapTextureHeight);

            std::cout << "index: " << index << " x: " << x << " y: " << y << std::endl;

            this->tiles[i][j].setTexture(this->mapTexture);
            this->tiles[i][j].scale(2.f, 2.f);

            std::cout <<
                "offset x: " << int(this->mapData.mapTextureBlockWidth * x) <<
                " offset y: " << int(this->mapData.mapTextureBlockHeight * y) <<
                " x block size: " << int(this->mapData.mapTextureBlockWidth) <<
                " y block size: " << int(this->mapData.mapTextureBlockHeight) <<
                " x: " << x <<
                " y: " << y <<
            std::endl;
            this->tiles[i][j].setTextureRect(sf::IntRect(
                (this->mapData.mapTextureBlockWidth * x),
                (this->mapData.mapTextureBlockHeight * y),
                this->mapData.mapTextureBlockWidth,
                this->mapData.mapTextureBlockHeight
            ));

            this->tiles[i][j].setPosition(sf::Vector2f(
                16.f + float(this->mapData.mapTextureBlockWidth * 2 * j),
                16.f + float(this->mapData.mapTextureBlockHeight * 2 * i)
            ));
        }
    }
}

void Map::draw(sf::RenderWindow& window) {
    for(int i = 0; i < this->mapData.mapHeight; i++) {
        for(int j = 0; j < this->mapData.mapWidth; j++) {
            window.draw(this->tiles[i][j]);
        }
    }
}
