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

void MapData::debug() {
    std::cout << "Width: " << (int) this->mapWidth << std::endl;
    std::cout << "Height: " << (int) this->mapHeight << std::endl;
    std::cout << "TextureBlockWidth: " << (int) this->mapTextureBlockWidth << std::endl;
    std::cout << "TextureBlockHeight: " << (int) this->mapTextureBlockHeight << std::endl;
    std::cout << "TexturePath: " << this->texturePath << std::endl;

    std::cout << "Permeability Map:" << std::endl;
    for(int i = 0; i < this->mapWidth; i++) {
        for(int j = 0; j < this->mapHeight; j++) {
            std::cout << (int) this->permeabilityMap[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << "Graphical Map:" << std::endl;
    for(int i = 0; i < this->mapWidth; i++) {
        for(int j = 0; j < this->mapHeight; j++) {
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
    uint8_t mapTextureBlockWidth,
    uint8_t mapTextureBlockHeight,
    std::string texturePath,
    std::vector<std::vector<uint8_t>> permeabilityMap,
    std::vector<std::vector<uint16_t>> graphicalMap
) {
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
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

    buffer.push_back(data.mapTextureBlockWidth);
    buffer.push_back(data.mapTextureBlockHeight);

    for(int i = 0; i < data.texturePath.size(); i++) buffer.push_back((uint8_t) data.texturePath[i]);

    buffer.push_back((uint8_t) '\0');

    for(uint8_t i = 0; i < data.mapWidth; i++) {
        for(uint8_t j = 0; j < data.mapHeight; j++) {
            buffer.push_back(data.permeabilityMap[i][j]);
        }
    }

    for(uint8_t i = 0; i < data.mapWidth; i++) {
        for(uint8_t j = 0; j < data.mapHeight; j++) {
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

    // checkpoint

    data.permeabilityMap = std::vector<std::vector<uint8_t>>(data.mapWidth, std::vector<uint8_t>(data.mapHeight, 1));

    for(uint8_t i = 0; i < data.mapWidth; i++) {
        for(uint8_t j = 0; j < data.mapHeight; j++) {
            mapFile.read(bufChar, 1);
            data.permeabilityMap[i][j] = buf;
        }
    }

    data.graphicalMap = std::vector<std::vector<uint16_t>>(data.mapWidth, std::vector<uint16_t>(data.mapHeight, 1));

    for(uint8_t i = 0; i < data.mapWidth; i++) {
        for(uint8_t j = 0; j < data.mapHeight; j++) {
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
