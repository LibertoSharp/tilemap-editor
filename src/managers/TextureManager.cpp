#include "managers/TextureManager.h"

TextureManager::TextureManager(const std::filesystem::path &path, sf::Vector2i tileSize) : tileSize(tileSize), AssetLoader(path) {

}

const sf::Texture* TextureManager::getAtlasTexture(const std::string& atlasName) const {
    return resources.find(atlasName)->second;
}

sf::Sprite TextureManager::createTileSprite(const std::string& atlasName, int x, int y) const {
    sf::Texture* tx = resources.find(atlasName)->second;
    sf::Vector2i position(x*tileSize.x,y*tileSize.y);
    sf::Vector2i size = tileSize;
    return {*tx, sf::IntRect(position, size)};
}

sf::Sprite TextureManager::getSprite(const std::string &atlasName, sf::IntRect rect) const {
    sf::Texture* tx = resources.find(atlasName)->second;
    return {*tx, rect};
}
