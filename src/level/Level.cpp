#include "level/Level.h"

#include <fstream>

#include "engine/Application.h"
#include "SFML/Graphics/RenderTarget.hpp"

Level::Level(unsigned int tileSize, unsigned int width, unsigned int height) {
    this->tileSize = tileSize;
    this->width = width;
    this->height = height;
    grids[0] = new Grid(tileSize, Vector2i(width, height));
    background = new BackgroundGrid(tileSize, width, height, this);
}

Level::~Level() {
    for (auto [key,grid]: grids) {
        delete grid;
    }
    delete background;
}

void Level::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    for (auto [index, grid]: grids) {
        if (f_showOnly && index != layerToShow) continue;
        for (int x = 0; x < grid->getGridSize().x; x++) {
            for (int y = 0; y < grid->getGridSize().y; y++) {
                int index = x + grid->getGridSize().x*y;

                if (!(*grid)[index]->has_value()) continue;

                Sprite *sprite = (*grid)[index]->value().getSprite();
                target.draw(*sprite, states);
            }
        }
    }
}

BackgroundGrid * Level::getBackgroundGrid() {
    return background;
}

void Level::ShowOnly(int layer_index) {
    layerToShow = layer_index;
}

void Level::clearGrids() {
    for (auto [key,grid]: grids) {
        delete grid;
    }
    grids.clear();
}

map<string, char>  getTilesetMap(map<int, Grid*> grids) {
    set<std::string> tilesets;
    for (auto [key, grid]: grids) {
        auto set = grid->getTileset();
        tilesets.insert(set.begin(), set.end());
    }
    map<string, char> tilesetMap;
    char i = 1;
    for (std::string s: tilesets) {
        tilesetMap.insert(std::make_pair(s, i++));
    }
    return tilesetMap;
}

int getMapLength(map<string, char> map) {
    int l = 0;
    for (auto [val, key]: map) {
        l += val.length();
        l++;
    }
    return l;
}

void Level::saveFile(std::string filePath) const {
    ofstream file(filePath, std::ios::binary);
    map<string, char> tilesetMap = getTilesetMap(grids);
    int dataIndex = getMapLength(tilesetMap) + 4;
    write_raw(file,dataIndex);
    for (auto [key, s]: tilesetMap) {
        file << key;
        write_raw(file, static_cast<char>(0x00));
    }
    write_raw(file, static_cast<char>(0x00));
    for (auto [key, grid]: grids) {
        write_raw(file, key);
        write_raw(file, grid->getGridSize().x);
        write_raw(file, grid->getGridSize().y);
        for (int x = 0; x < grid->getGridSize().x; x++) {
            for (int y = 0; y < grid->getGridSize().y; y++) {
                std::optional<Tile> t = grid->getTile(x, y);
                if (t.has_value()) {
                    char key = tilesetMap.find(t.value().getAtlasID())->second;
                    write_raw(file, key);
                    write_raw(file, t.value().getRect().position.x);
                    write_raw(file, t.value().getRect().position.y);
                    write_raw(file, t.value().getRect().size.x);
                    write_raw(file, t.value().getRect().size.y);
                } else {
                    char key = 0;
                    write_raw(file, key);
                    write_raw(file, 0);
                    write_raw(file, 0);
                    write_raw(file, 0);
                    write_raw(file,0);
                }
            }
        }
    }
    file.close();
}

bool Level::loadFile(std::string filePath) {
    std::ifstream in(filePath, std::ios::binary);
    if (!in) return false;
    in.seekg (0, in.end);
    int length = in.tellg();
    in.seekg (0, in.beg);
    uint8_t *buffer = new uint8_t [length];
    in.read(reinterpret_cast<char*>(buffer), length);

    unsigned int i = 3;
    int index = 1;
    map<char, string> tilesetMap;
    string s = "";
    do {
        i++;
        if (buffer[i] == '\0') {
            tilesetMap.insert(std::make_pair(index++,s));
            s = "";
        }
        else
            s += buffer[i];
    } while (!(buffer[i] == '\0' && buffer[i+1] == '\0'));

    clearGrids();
    i = read_32(buffer, 0x00)+1;
    while (i < length-1) {
        int layer = read_32(buffer, i);
        int gridSizeX = read_32(buffer, i+4);
        int gridSizeY = read_32(buffer, i+8);
        i+=12;
        for (int x = 0; x < gridSizeX; x++) {
            for (int y = 0; y < gridSizeY; y++) {
                char MapKeyID = read_8(buffer, i);
                if (MapKeyID != '\0') {
                    IntRect r({static_cast<int>(read_32(buffer,i+1)),static_cast<int>(read_32(buffer,i+5))},{static_cast<int>(read_32(buffer,i+9)),static_cast<int>(read_32(buffer,i+13))});
                    getGrid(layer)->setTile(x,y,Tile(r,tilesetMap.find(MapKeyID)->second));
                }
                i+=17;
            }
        }
    }


    return true;
}
